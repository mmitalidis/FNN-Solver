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


#include "world.h"
#include <cstdlib>

// constructor with argc, argv arguments 
World::World(int argc, char*argv[], const int& numtasks) {
	int lg2N, lg2K;
	parse_arguments(argc,argv,lg2N,lg2K);
	set_mesh_size(lg2N, lg2K);

	N = N / numtasks;

	init(lg2N,lg2K);
}
// constructor with argc, argv arguments 
World::World(int argc, char*argv[]) {
	int lg2N, lg2K;
	parse_arguments(argc,argv,lg2N,lg2K);
	set_mesh_size(lg2N, lg2K);

	init(lg2N,lg2K);
}


// constructor with lg2(number of points), lg2(number of boxes) 
World::World(const int& lg2N, const int& lg2K) {
	set_mesh_size(lg2N, lg2K);
	init(lg2N,lg2K);
}

void World::init(const int& lg2N, const int& lg2K) {
	int n, m, k;
	for (int i = 0; i < K; ++i) {
		get_coords_from_box_id(i, n, m, k);
		this->push_back( Box(i,n,m,k,this) );
	}

	for (int i = 0; i < N; ++i)
		add_random_point();
}



// get the first nearest neighbor
Min_dist World::get_fnn(const Point& src) const {
	Min_dist md(src, *this);
	return md;
}

// parse argc, argv arguments
void World::parse_arguments(int argc, char* argv[], int& lg2N, int& lg2K) {
	// check number of arguments
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " n k"             << std::endl << std::endl 
                          << "where, N=2^n is the number of points"     << std::endl 
                     	  << "       K=2^k is the number of grid boxes" << std::endl; 
		exit(1);
	}

	// convert input to integer
	lg2N = atoi(argv[1]);
	lg2K = atoi(argv[2]);

	// check limits
	if (lg2N < world_limits::min_lg2N ||
	    lg2N > world_limits::max_lg2N || 
	    lg2K < world_limits::min_lg2K ||  
	    lg2K > world_limits::max_lg2K) {
		std::cout << "min_n = " << world_limits::min_lg2N << " | max_n = " << world_limits::max_lg2N << std::endl 
                          << "min_k = " << world_limits::min_lg2K << " | max_k = " << world_limits::max_lg2K << std::endl;
		exit(1);
	}
}

// calculate grid size dimensions from user input
void World::set_mesh_size(const int& lg2N, const int& lg2K) {
	// get number of points 
	N = 1 << lg2N;

	// get number of boxes
	K = 1 << lg2K;

	// calculate boxes alignment (must be close to squeare)
	int div = lg2K / 3;

	int lg2n, lg2m, lg2k;
	lg2n = div;
	lg2m = div;
	lg2k = div;

	if (lg2n + lg2m + lg2k == lg2K -1) {
		lg2k++;	
	}
	else if (lg2n + lg2m + lg2k == lg2K -2) {
		lg2k++;
		lg2m++;
	}

	dim.setN(1 << lg2n);
	dim.setM(1 << lg2m);
	dim.setK(1 << lg2k);
}

// calculate the id of the box where the point belongs to
int World::get_box_id_from_point(const Point& p) const {
	int r,c,v;

	r = p.getX() * dim.getN();
	c = p.getY() * dim.getM();
	v = p.getZ() * dim.getK();

	int id = get_box_id_from_coords(r, c, v);
	return (id);
}

// calculate the id of a box from its (n,m,k) coordinates.
int World::get_box_id_from_coords(const int& n, const int& m, const int& k) const {
	int id = n + m*dim.getN() + k*dim.getN()*dim.getM();
	return (id);
}

// calculate the coords of the box from its id
int World::get_coords_from_box_id(const int& id, int& r, int& c, int& v) const {
	v = id / (dim.getN() * dim.getM());
	c = (id - v* dim.getN() * dim.getM()) / dim.getN();
	r =  id - v* dim.getN() * dim.getM() - c * dim.getN();
}

// add a random point to the correct box
void World::add_random_point() {
	Point p = get_random_point();

	int id = get_box_id_from_point(p);
	(*this)[id].push_back(p);
}

// get a random point
Point World::get_random_point() {
	Point p( ((double) rand() / (double) RAND_MAX),
		 ((double) rand() / (double) RAND_MAX),
		 ((double) rand() / (double) RAND_MAX) );
	return p;
}

// clear the contents of a box
void World::clear_box(const int& i) {
	(*this)[i].clear();
}

Neighbourhood World::get_neighbourhood(const Point& p) const {
	
	return get_neighbourhood( get_box(p) );
}

Neighbourhood World::get_neighbourhood(const Box& b) const {
	return Neighbourhood(b);
}

const Box& World::get_box(const Point& p) const {
	return (*this)[ get_box_id_from_point(p) ];
}

//Check that the given grid dimensions are valid.
bool World::is_valid_dim(const int& r, const int& c, const int& v) const {
	if (r < 0 || r >= dim.getN())
		return false;

	if (c < 0 || c >= dim.getM())
		return false;

	if (v < 0 || v >= dim.getK())
		return false;

	return true;
}

// append a box
void World::append_box(Box& b) {
	for (auto& elem : b)
		(*this)[ b.getId() ].push_back( elem );
}

