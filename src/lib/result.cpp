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


#include "result.h"

// constructor
Result::Result(const World& C, const Search_space& Q) {
	for (auto const& elem : Q)
		this->push_back( Min_dist(elem,C) );	
}
