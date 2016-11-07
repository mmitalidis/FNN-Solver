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


#include "point.h"
#include <cmath>

// constuctor with coordinates
Point::Point(const double& _x,
     	     const double& _y,
             const double& _z) {
	x = _x;
	y = _y;
	z = _z;
}

// empty constructor
Point::Point() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

// distance between two points
double Point::dist(const Point& p) const {

	double dist = sqrt( (p.x - x)*(p.x - x) +
                            (p.y - y)*(p.y - y) +
                            (p.z - z)*(p.z - z));
	return (dist);
}

// compare two points
int Point::compare(const Point& p) const {

	if (p.getX() != x)
		return (0);
	if (p.getY() != y)
		return (0);
	if (p.getZ() != z)
		return (0);

	return (1);

}


