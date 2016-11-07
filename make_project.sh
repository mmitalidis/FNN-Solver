#!/bin/bash

# =======================================================================
#  This file is part of FNN-Solver.
#  Copyright (C) 2016 Marios Mitalidis
#
#  FNN-Solver is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  FNN-Solver is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with FNN-Solver.  If not, see <http://www.gnu.org/licenses/>.
# =======================================================================

cd ./src/

cd ./lib/
mpic++ -g -std=c++11 -c ./*.cpp
ar rcs ./libfnn.a ./*.o
cd ..

g++ -std=c++11 ./main_fnn_serial.cpp      -L./lib -lfnn -o ./main_fnn_serial.out
g++ -std=c++11 ./main_fnn_serial_test.cpp -L./lib -lfnn -o ./main_fnn_serial_test.out

mpic++ -g -std=c++11 ./main_fnn_par.cpp      -L./lib -lfnn -o ./main_fnn_par.out
mpic++ -std=c++11 ./main_fnn_par_test.cpp -L./lib -lfnn -o ./main_fnn_par_test.out

rm ./lib/*.o
rm ./lib/*.a

mv ./*.out ../
cd ..
