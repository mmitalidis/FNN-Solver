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


#ifndef _MIN_DIST_H
#define _MIN_DIST_H

#include "world.h"
#include "point.h"

class World;
class Point;
class Neighbourhood;

class Min_dist {

private:
	Point target;
	double distance;

public:
	// Empty constructor
	Min_dist();

	// constructor from data
	Min_dist(const Point&, const double&);

	// Constructor from world data (source, targets)
	Min_dist(const Point&, const World&);

	// Constructor from box data (source, targets)
	Min_dist(const Point&, const Neighbourhood&);

	// Constructor from box data (source, targets)
	Min_dist(const Point&, const Box&);

	// constuctor with Point data (source, target)
	Min_dist(const Point&, const Point&);

	// getters
	inline Point  get_target()   const { return target; }
	inline double get_distance() const { return distance; }

	// update the class contents
	template <typename T>
	void update(const Point&, const T&);

	// overload operator < to compare min_dist
	bool operator< (const Min_dist&) const;

};

#endif
