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


#ifndef _NEIGHBOURHOOD_H
#define _NEIGHBOURHOOD_H

#include "world.h"
#include "box.h"
#include <vector>
#include <functional>

class World;
class Box;

class Neighbourhood : public std::vector<std::reference_wrapper<Box>> {

private:
	World* world;

	// initialize neighbourhood
	void init(const Box&);

public:
	Neighbourhood() {}

	// constuctor with id and world pointer
	Neighbourhood(const int&, World&);

	// constructor with box
	Neighbourhood(const Box&);
};

#endif
