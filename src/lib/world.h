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


#ifndef _WORLD_H
#define _WORLD_H

#include "neighbourhood.h"
#include "box.h"
#include "grid.h"
#include "min_dist.h"
#include <vector>
#include <cstdlib>
#include <iostream>

class Neighbourhood;
class Box;
class Grid;
class Point;
class Min_dist;

namespace world_limits {

	// minimum value of log2(number of points)
	const int min_lg2N = 1;

	// maximum value of log2(number of points)
	const int max_lg2N = 25;

	// minimum value of log2(number of boxes)
	const int min_lg2K = 1;

	// maximum value of log2(number of boxes)
	const int max_lg2K = 16; 
}


class World : public std::vector<Box> {

private:

	int N; // number of points
	int K; // number of boxes
	Grid dim;

	// parse argc, argv arguments
	void parse_arguments(int, char**, int&, int&);

	// initialize World class
	void init(const int&, const int&);

	// calculate grid size dimensions from user input
	void set_mesh_size(const int&, const int&);

	// calculate the id of the box where the point belongs to
	int get_box_id_from_point(const Point& p) const;

	// add a random point to the correct box
	void add_random_point();

public:
	// constructor with argc, argv arguments and number of processes
	World(int, char**, const int&); 

	// constructor with argc, argv arguments 
	World(int, char**); 

	// constructor with lg2(number of points), lg2(number of boxes) 
	World(const int&, const int&);

	// get the first nearest neighbor
	Min_dist get_fnn(const Point& src) const;

	// number of points getter
	inline int getN() const { return N; }

	// number of boxes getter
	inline int getK() const { return K; }

	// clear the contents of a box
	void clear_box(const int&);

	// get the neighbourhood of a point
	Neighbourhood get_neighbourhood(const Point&) const;

	// get the neighbourhood of a box
	Neighbourhood get_neighbourhood(const Box&) const;

	// get the box of the point
	const Box& get_box(const Point&) const;

	// calculate the id of the box of the point
	int get_box_id_from_coords(const int&, const int&, const int&) const;

	// calculate the coords of the box from its id
	int get_coords_from_box_id(const int&, int&, int&, int&) const;

	//Check that the given grid dimensions are valid.
	bool is_valid_dim(const int&, const int&, const int&) const;

	// get a random point
	static Point get_random_point();

	// append a box
	void append_box(Box&);
};


#endif
