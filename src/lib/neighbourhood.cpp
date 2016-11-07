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


#include "neighbourhood.h"

Neighbourhood::Neighbourhood(const int& i, World& world) {
	init( world[i] );
}

Neighbourhood::Neighbourhood(const Box& b) {
	init(b);
}

void Neighbourhood::init(const Box& b) {
	world = b.getWorld();
	int bid = b.getId(); // box id

	int r = b.getN();
	int c = b.getM();
	int v = b.getK();
		
	int s,t,u;
	for (s = -1; s <= 1; s++) {
		for (t = -1; t <= 1; t++) {
			for (u = -1; u <= 1; u++) {
				if (world->is_valid_dim(r+s, c+t, v+u)) {
					this->push_back( (*world)[ world->get_box_id_from_coords(r+s, c+t, v+u) ] );
				}	
			}
		}
	}
}
