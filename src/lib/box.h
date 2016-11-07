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


#ifndef _BOX_H
#define _BOX_H

#include "world.h"
#include "point.h"
#include <vector>

class Point;
class World;

class Box : public std::vector<Point> {

private:
	int id;
	int n, m, k;
	
	World* world;

public:

	// constructor with id, n, m, k, *world
	Box(const int&, const int&, const int&, const int&, World*);

	// constructor from vectors metadata and data
	Box(const std::vector<int>&, const std::vector<double>&);

	// getters
	inline int getId() const { return id; }
	inline int getN() const  { return n;  }
	inline int getM() const  { return m;  }
	inline int getK() const  { return k;  }
	inline World* getWorld() const { return world; }

	// append another box
	void append_box(const Box&);

	// convert box to vector
	std::vector<double> serialize() const;

	// get box metadata
	std::vector<int> get_metadata() const;
};

#endif 
