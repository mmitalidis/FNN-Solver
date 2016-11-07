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


#include "min_dist.h"
#include <vector>
#include <limits>
#include <algorithm>


// Empty constructor
Min_dist::Min_dist() {
	target = Point();
	distance = std::numeric_limits<double>::infinity();
}

// constructor from data
Min_dist::Min_dist(const Point& p, const double& d) : target(p), distance(d) {}

// Constructor from world data (source, targets)
Min_dist::Min_dist(const Point& src, const World& world) {
	update(src, world.get_neighbourhood(src) );
}

// Constructor from box data (source, targets)
Min_dist::Min_dist(const Point& src, const Neighbourhood& n) {
	update(src,n);
}

// Constructor from box data (source, targets)
Min_dist::Min_dist(const Point& src, const Box& b) {
	update(src,b);
}

// constuctor with Point data (source, target)
Min_dist::Min_dist(const Point& src, const Point& dest) {
	target = dest;
	distance = src.dist(dest);
}

// update the class contents
template <typename T>
void Min_dist::update(const Point& src, const T& x) {
	
	if (x.empty()) {
		target = Point();
		distance = std::numeric_limits<double>::infinity();
	}
	else {
		std::vector<Min_dist> v;
		for (int i = 0; i < x.size(); ++i) 
			v.push_back( Min_dist(src, x[i]) );

		auto it = std::min_element(v.begin(), v.end());

		target   = it->get_target();
		distance = it->get_distance();
	}
}

// overload operator < to compare min_dist
bool Min_dist::operator< (const Min_dist& md) const {
	return (distance < md.get_distance());
}


