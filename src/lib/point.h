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


#ifndef _POINT_H
#define _POINT_H

#include <vector>

class Point {

private:
	double x;
	double y;
	double z;

public:
	// constuctor with coordinates
	Point(const double&,
	      const double&,
	      const double&);

	// empty constructor
	Point();

	// getters and setters
	inline double getX() const { return x; }
	inline double getY() const { return y; }
	inline double getZ() const { return z; }

	inline double setX(const double& _x) { x = _x; }
	inline double setY(const double& _y) { y = _y; }
	inline double setZ(const double& _z) { z = _z; }

	// distance between two points
	double dist(const Point&) const;

	// compare two points
	int compare(const Point&) const;
};


#endif
