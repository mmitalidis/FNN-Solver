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


#ifndef _GRID_H
#define _GRID_H


class Grid {

private:
	int N, M, K;

public:
	//empty constuctor
	Grid();

	// constuctor
	Grid(const int&, const int&, const int&);

	// getters
	inline int getN() const { return N; }
	inline int getM() const { return M; }
	inline int getK() const { return K; }

	// setters
	inline void setN(const int& _N) { N = _N; }
	inline void setM(const int& _M) { M = _M; }
	inline void setK(const int& _K) { K = _K; }
};

#endif
