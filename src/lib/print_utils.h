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


#ifndef _PRINT_UTILS_H
#define _PRINT_UTILS_H

#include <vector>
#include <iostream>
#include "point.h"
#include "min_dist.h"
#include "box.h"
#include "world.h"
#include "neighbourhood.h"
#include "search_space.h"
#include "result.h"


// output a point class
std::ostream& operator<< (std::ostream&, const Point&);

// output a Min_dist object
std::ostream& operator<< (std::ostream&, const Min_dist&);

// output a Box object
std::ostream& operator<< (std::ostream&, const Box&);

// output a Neighbourhood object
std::ostream& operator<< (std::ostream&, const Neighbourhood&);

// output a World object
std::ostream& operator<< (std::ostream&, const World&);

// output a Search_space object
std::ostream& operator<< (std::ostream&, const Search_space&);

// output a Results object
std::ostream& operator<< (std::ostream&, const Result&);

#endif
