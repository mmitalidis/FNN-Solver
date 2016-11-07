/*
 * =======================================================================
 *  This file is part of FNN-Solver.
 *  Copyright (C) 2016 Marios Mitalidis
 *
 *  FNN-Solver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  FNN-Solver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with FNN-Solver.  If not, see <http://www.gnu.org/licenses/>.
 * =======================================================================
 */ 


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <string>
#include "fnn_solver_par.h"
#include "search_space.h"
#include "result_par.h"
#include "print_utils.h"
#include "mpi.h"

#define DEBUG 0

// constructor
Fnn_solver_par::Fnn_solver_par(int argc, char* argv[], bool print) {

	int rank, numtasks;

	MPI_Init(&argc,&argv); 
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	srand(time(nullptr) + rank);

	World C(argc, argv, numtasks);
	MPI_Barrier(MPI_COMM_WORLD);

	share_boxes(C, rank, numtasks);
	MPI_Barrier(MPI_COMM_WORLD);

	Search_space Q( C.getN() );

	// check numtasks < K
	if ( numtasks > C.getK() && rank == mpi_settings::root ) {
		std::cout << "P should be less than or equal to K." << std::endl;
		MPI_Abort(MPI_COMM_WORLD,2);
	}

	// for time measurements - only for root use
	struct timeval startwtime, endwtime;
	double run_time;

	// start measuring time
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == mpi_settings::root) {
		gettimeofday(&startwtime,nullptr);
	}

	// Run the parallel algorithm
	Result_par R(C,Q,rank,numtasks);

	// stop measuring time
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == mpi_settings::root) {
		gettimeofday(&endwtime,nullptr);

		// calculate run time
		run_time = (double) ( (endwtime.tv_usec - startwtime.tv_usec) / 1.0e6
              		+ endwtime.tv_sec - startwtime.tv_sec );

		std::cout << run_time << std::endl;
	}

	if (print) {
		std::string Cstr = "C.csv";
		std::string Qstr = "Q.csv";
		std::string Rstr = "R.csv";

		for (int i = 0; i < numtasks; i++) {
			MPI_Barrier(MPI_COMM_WORLD);
	
			if (rank == i) {
				std::ofstream foutC( Cstr.c_str(), std::fstream::out|std::fstream::app );
				std::ofstream foutQ( Qstr.c_str(), std::fstream::out|std::fstream::app );
				std::ofstream foutR( Rstr.c_str(), std::fstream::out|std::fstream::app );

				foutC << C;
				foutQ << Q;
				foutR << R;

				foutC.close();	
				foutQ.close();	
				foutR.close();	
			}
		}
	}

	MPI_Finalize();
}

// share boxes between processes (world, rank, numtasks)
void Fnn_solver_par::share_boxes(World& C, const int& rank, const int& numtasks) {

	for (int incr = (numtasks-1) + (numtasks-2); incr >= 0; --incr) {

		int partner = get_partner(rank,incr,numtasks);
		if ( partner != -1) {
		
			if (rank > partner) {
				send_boxes_to_proc(C, rank, partner, numtasks);
				recv_boxes_from_proc(C, rank, partner, numtasks);
			}
			else {
				recv_boxes_from_proc(C, rank, partner, numtasks);
				send_boxes_to_proc(C, rank, partner, numtasks);
			}

		}

		MPI_Barrier(MPI_COMM_WORLD);
	}
}

// get partner to send box (rank, incr, numtasks)
int Fnn_solver_par::get_partner(const int& rank, const int& incr, const int& numtasks) {

	int partner;
	
	if ( (incr - rank < numtasks) && (incr - rank >= 0) && (incr - rank != rank ) )
		partner = incr - rank;
	else
		partner = -1;

	return partner;
}

// send boxes to a process (world, rank, partner, numtasks)
void Fnn_solver_par::send_boxes_to_proc(World& C, const int& rank, const int& partner, const int& numtasks) {

	// boxes per process
	int kpp = C.getK() / numtasks;

	for (int ind = partner*kpp; ind < (partner+1)*kpp; ++ind) {
		send_box_to_proc(C, partner, ind);
	}
}

// receive boxes from process (world, rank, source, numtasks)
void Fnn_solver_par::recv_boxes_from_proc(World& C, const int& rank, const int& partner, const int& numtasks) {

	// boxes per process
	int kpp = C.getK() / numtasks;

	for (int ind = rank*kpp; ind < (rank+1)*kpp; ++ind) {
		recv_box_from_proc(C, partner, ind);
	}
}

// send box to process (world, partner, ind)
void Fnn_solver_par::send_box_to_proc(World& C, const int& partner, const int& ind) {

		std::vector<int>  meta = C[ind].get_metadata();
		std::vector<double> vp = C[ind].serialize();
		
		MPI_Ssend(&meta[0], 5      , MPI_INT   , partner, mpi_tags::box_meta_tag, MPI_COMM_WORLD);

		if (meta[0] != 0) {
			MPI_Ssend(&vp[0]  , meta[0], MPI_DOUBLE, partner, mpi_tags::box_data_tag, MPI_COMM_WORLD);
		}

		C.clear_box(ind);

}

// receive box from process (world, source, ind)
void Fnn_solver_par::recv_box_from_proc(World& C, const int& source, const int& ind) {

		std::vector<int> meta(5,0);
		MPI_Recv(&meta[0], 5, MPI_INT, source, mpi_tags::box_meta_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

		int size = meta[0];

		if (size != 0) {
			std::vector<double> vp(size,0);
			
			MPI_Recv(&vp[0], size, MPI_DOUBLE, source, mpi_tags::box_data_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
				
			Box b(meta, vp);
			C.append_box(b);
		}
}
	

#if DEBUG
	void print_boxes(const World& C, int rank, int comm_size) {

		for(int i = 0; i < comm_size; i++) {
			MPI_Barrier(MPI_COMM_WORLD);
			if (i == rank) {
				std::cout << "Task " << i << std::endl;
				for (int j = 0; j < C.getK(); j++) {
					std::cout << "C[" << j << "] = " << C[j].size() << std::endl;
				}
				std::cout << std::endl;
			}

		}

	}

	void print_box(World& C, int rank, int comm_size) {

		for(int i = 0; i < comm_size; i++) {
			MPI_Barrier(MPI_COMM_WORLD);
			if (i == rank) {
				std::cout << "Task " << i << std::endl;
				std::cout << "C[" << 0 << "]" << std::endl;

				Box b( C[0] );
				std::cout << b << std::endl;
				std::cout << std::endl;
			}

		}

	}
#endif
