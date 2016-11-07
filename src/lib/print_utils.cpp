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


#include "print_utils.h"
#include <iomanip>

// output a point class
std::ostream& operator<< (std::ostream& os, const Point& p) {
	os << std::fixed << std::setprecision(7);
	os << p.getX() << ", " << p.getY() << ", " << p.getZ() << std::endl;
	return os;
}

// output a Min_dist object
std::ostream& operator<< (std::ostream& os, const Min_dist& md) {
	os << std::fixed << std::setprecision(7);
	os << md.get_distance() << ", " << md.get_target();
}

// output a Box object
std::ostream& operator<< (std::ostream& os, const Box& v) {
	for (auto const& elem : v) 
		os << elem;
	return os;
}

// output a Neighbourhood object
std::ostream& operator<< (std::ostream& os, const Neighbourhood& v) {
	for (auto const& elem : v) 
		os << elem;
	return os;
}

// output a World object
std::ostream& operator<< (std::ostream& os, const World& v) {
	for (auto const& elem : v) 
		os << elem;
	return os;
}

// output a Search_space object
std::ostream& operator<< (std::ostream& os, const Search_space& v) {
	for (auto const& elem : v) 
		os << elem;
	return os;
}

// output a Results object
std::ostream& operator<< (std::ostream& os, const Result& v) {
	for (auto const& elem : v) 
		os << elem;
	return os;
}
