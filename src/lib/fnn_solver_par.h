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


#ifndef _FNN_SOLVER_PAR_H
#define _FNN_SOLVER_PAR_H

#include "world.h"

namespace mpi_tags {
	const int box_meta_tag = 1;
	const int box_data_tag = 2;

	const int msg_meta_tag = 3;
	const int msg_data_tag = 4;
	const int msg_ans_tag  = 5;

}

namespace mpi_settings {
	const int root = 0;
}

class Fnn_solver_par {

private:

	// share boxes between processes (world, rank, numtasks)
	void share_boxes(World&, const int&, const int&);

	// get partner to send box (rank, incr)
	int get_partner(const int&, const int&, const int&);

	// send boxes to a process (world, rank, partner, numtasks)
	void send_boxes_to_proc(World&, const int&, const int&, const int&);

	// receive boxes from process (world, rank, source, numtasks)
	void recv_boxes_from_proc(World&, const int&, const int&, const int&);

	// send box to process (world, partner, ind)
	void send_box_to_proc(World&, const int&, const int&);

	// receive box from process (world, source, ind)
	void recv_box_from_proc(World&, const int&, const int&);
	

public:

	// constructor
	Fnn_solver_par(int, char**, bool);

	

};


#endif
