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


#include "result_par.h"
#include "fnn_solver_par.h"
#include <set>
#include <algorithm>
#include <iostream>
#include <cstdlib>

Result_par::Result_par(const World& C, const Search_space& Q, const int& _rank, const int& _numtasks) :
Result(C,Q), rank(_rank), numtasks(_numtasks) {

	//check mpi is running
	int initialized;
	MPI_Initialized(&initialized);
	if (!initialized) {
		std::cout << "MPI is not running." << std::endl;
		exit(4);
	}

	// prepare messages for other processes
	prepare_msg(C,Q);

	// communicate and solve the problem
	comm_and_solve(C);
}

void Result_par::prepare_msg(const World& C, const Search_space& Q) {

	int id = 0;
	for (auto const& p : Q) {
		Neighbourhood nb = C.get_neighbourhood(p);

		std::set<int> prev_proc;
		prev_proc.insert(rank);
		for (auto const& box : nb) {

			int proc = get_box_owner(C,box);
			if (prev_proc.find(proc) == prev_proc.end() )
				pm[proc].push_back( std::make_pair(p,id) );

			prev_proc.insert(proc);

		}	
		id++;
	}	
}

void Result_par::comm_and_solve(const World& C) {

	for (int incr = (numtasks-1) + (numtasks-2); incr >= 0; --incr) {

		int partner = get_partner(incr);
		if ( partner != -1) {
		
			if (rank > partner) {
				send_msg_to_proc(C, partner);
				recv_msg_from_proc(C, partner);
			}
			else {
				recv_msg_from_proc(C, partner);
				send_msg_to_proc(C, partner);
			}

		}
	}

}

int Result_par::get_box_owner(const World& C, const Box& b) {

	int kpp = C.getK() / numtasks;
	int owner = b.getId() / kpp;

	return (owner);

}

// get partner to send box (rank, incr, numtasks)
int Result_par::get_partner(const int& incr) {

	int partner;
	
	if ( (incr - rank < numtasks) && (incr - rank >= 0) && (incr - rank != rank ) )
		partner = incr - rank;
	else
		partner = -1;

	return partner;
}


// send messages to a process (world, rank, partner, numtasks)
void Result_par::send_msg_to_proc(const World& C, const int& partner) {

	// prepare request message
	std::vector<double> send_points;
	for (int i = 0; i < pm[partner].size(); ++i) {

		send_points.push_back( (pm[partner])[i].first.getX() );
		send_points.push_back( (pm[partner])[i].first.getY() );
		send_points.push_back( (pm[partner])[i].first.getZ() );
	}

	// send request message
	int size = send_points.size();
	MPI_Send(&size          , 1   , MPI_INT   , partner, mpi_tags::msg_meta_tag, MPI_COMM_WORLD);
	MPI_Send(&send_points[0], size, MPI_DOUBLE, partner, mpi_tags::msg_data_tag, MPI_COMM_WORLD);

	// answer includes point and distance
	int ans_size = size + size/3;
	std::vector<double> ans(ans_size,0);


	if (ans_size != 0) {

		// get answer
		MPI_Recv(&ans[0], ans_size, MPI_DOUBLE, partner, mpi_tags::msg_ans_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		// parse answer
		int ctr = 0;
		for (int i = 0; i < ans_size; i += 4) {
		
			Min_dist md( Point(ans[i], ans[i+1], ans[i+2]), ans[i+3] );
			int id = pm[partner][ctr].second;

			(*this)[id] = std::min( (*this)[id], md );
			ctr++;
		}
	}
}

// receive message from process (world, source, ind)
void Result_par::recv_msg_from_proc(const World& C, const int& partner) {

	int req_size = 0;
	MPI_Recv(&req_size, 1, MPI_INT, partner, mpi_tags::msg_meta_tag, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	if (req_size != 0) {
		std::vector<double> req_points(req_size,0);
		MPI_Recv(&req_points[0], req_size, MPI_DOUBLE, partner, mpi_tags::msg_data_tag, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

		std::vector<Min_dist> ans_vec;
		for (int i = 0; i < req_size; i += 3) {
			ans_vec.push_back( Min_dist( Point(req_points[i], req_points[i+1], req_points[i+2]), C) );
		}

		// prepare answer
		std::vector<double> ans;
		for (int i = 0; i < ans_vec.size(); i++) {
			ans.push_back( ans_vec[i].get_target().getX() );
			ans.push_back( ans_vec[i].get_target().getY() );
			ans.push_back( ans_vec[i].get_target().getZ() );
			ans.push_back( ans_vec[i].get_distance()      );
		}

		// send answer
		MPI_Send(&ans[0], ans.size(), MPI_DOUBLE, partner, mpi_tags::msg_ans_tag, MPI_COMM_WORLD);
	}
}

