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


#include "box.h"
#include <iostream>
#include <cstdlib>

// constructor
Box::Box(const int& _id, const int& _n, const int& _m, const int& _k, World* _world) {
	id = _id;
	n  = _n;
	m  = _m;
	k  = _k;
	world = _world;
}

// constructor from vectors
Box::Box(const std::vector<int>& meta, const std::vector<double>& vp) {

	if (meta.size() != 5) {
		std::cout << "Invalid Box metadata arguments." << std::endl;
		exit(2);
	}

	int size = meta[0];
	id = meta[1];
	n = meta[2];
	m = meta[3];
	k = meta[4];

	if (vp.size() % 3 != 0) {
		std::cout << "Invalid Box data arguments." << std::endl;
		exit(2);
	}

	for (int i = 0; i < vp.size(); i+=3)
		this->push_back( Point( vp[i], vp[i+1], vp[i+2] ) );

}

// append a box
void Box::append_box(const Box& b) {
	this->insert(this->end(),b.cbegin(),b.cend());
}


// covert box to vector
std::vector<double> Box::serialize() const {

	std::vector<double> vp;
	for (int i = 0; i < this->size(); ++i) {
		vp.push_back( (*this)[i].getX() );
		vp.push_back( (*this)[i].getY() );
		vp.push_back( (*this)[i].getZ() );
	}

	return (vp);
}

// get box metadata
std::vector<int> Box::get_metadata() const {
	
	std::vector<int> meta;
	
	meta.push_back(this->size() *3 );
	meta.push_back(id);
	meta.push_back(n);
	meta.push_back(m);
	meta.push_back(k);

	return (meta);
}
