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

T=1

n_start=21
n_end=25

k_start=16
k_end=16

fout=fnn_experiment.csv
serial_exec='./main_fnn_serial.out'
par_exec='./main_fnn_par.out'

P='2 4 8 16 32 64 128'

> $fout
for n in $(seq $n_start $n_end) ; do
	echo "[*] Running experiments for n=$n"

	for k in $(seq $k_start $k_end) ; do
		for t in $(seq 1 $T) ; do

			echo -n "0,$n,$k,$t,1," >> $fout
			$serial_exec $n $k >> $fout		

			for p in $(echo $P) ; do

				echo -n "1,$n,$k,$t,$p," >> $fout
				mpirun -np $p $par_exec $n $k >> $fout
			done
		done
	done
done

