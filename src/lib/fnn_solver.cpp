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


#include "fnn_solver.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include "world.h"
#include "search_space.h"
#include "result.h"
#include "print_utils.h"

Fnn_solver::Fnn_solver(int argc, char* argv[], bool print) {

	srand(time(nullptr));

	World        C(argc,argv);
	Search_space Q( C.getN() );

	
	// for time measurements
	struct timeval startwtime, endwtime;
	double run_time;
	gettimeofday(&startwtime,nullptr);

	// calculate result
	Result R(C, Q);
	
	gettimeofday(&endwtime,nullptr);

	// calculate run time
	run_time = (double) ( (endwtime.tv_usec - startwtime.tv_usec) / 1.0e6
           		+ endwtime.tv_sec - startwtime.tv_sec );

	std::cout << run_time << std::endl;

	if (print) {
		std::string Cstr = "C.csv";
		std::string Qstr = "Q.csv";
		std::string Rstr = "R.csv";

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
