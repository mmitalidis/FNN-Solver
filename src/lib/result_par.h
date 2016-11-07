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


#ifndef _RESULT_PAR_H
#define _RESULT_PAR_H

#include "world.h"
#include "search_space.h"
#include "result.h"
#include "neighbourhood.h"
#include "min_dist.h"
#include "box.h"

#include <vector>
#include <map>
#include <utility>
#include "mpi.h"

typedef std::vector<std::pair<Point,int>> Point_msg;

class Result_par : public Result {

private:

	std::map<int,Point_msg> pm;
	int rank, numtasks;

	void prepare_msg(const World&, const Search_space&);
	void comm_and_solve(const World&);
	
	int get_box_owner(const World&, const Box&);
	int get_partner(const int&);

	// send message to process (world, partner, rank, numtasks)
	void send_msg_to_proc(const World&, const int&); 

	// receive message from process (world, partner, rank, numtasks)
	void recv_msg_from_proc(const World&, const int&); 


public:

	// constructor
	Result_par(const World&, const Search_space&, const int&, const int&);

};


#endif
