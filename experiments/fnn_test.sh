#!/usr/bin/octave-cli

% =======================================================================
%  This file is part of FNN-Solver.
%  Copyright (C) 2016 Marios Mitalidis
%
%  FNN-Solver is free software: you can redistribute it and/or modify
%  it under the terms of the GNU General Public License as published by
%  the Free Software Foundation, either version 3 of the License, or
%  (at your option) any later version.
%
%  FNN-Solver is distributed in the hope that it will be useful,
%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%  GNU General Public License for more details.
%
%  You should have received a copy of the GNU General Public License
%  along with FNN-Solver.  If not, see <http://www.gnu.org/licenses/>.
% =======================================================================

epsilon = 1e-5;

arg_list = argv ();

if nargin ~= 3
	error('Invalid number of input argument.');
end

% file input
C = csvread(arg_list{1});
Q = csvread(arg_list{2});
R = csvread(arg_list{3});

d = R(:,1);
O = R(:,2:4);

if size(O,1) ~= size(d,1)
	error('Output files have different size.');
end

O_calc = zeros(size(O));
d_calc = zeros(size(d));


% fnn calculation
for i = 1:length(Q)

	cv = [C(1,1), C(1,2), C(1,3)];
	cq = [Q(i,1), Q(i,2), Q(i,3)];

	min_dist = norm(cv-cq);
	min_vec  = cv;

	for j = 2:length(C)
		
		cv = [C(j,1), C(j,2), C(j,3)];
		tmp = norm(cv-cq);
		if tmp < min_dist
			min_dist = tmp;
			min_vec  = cv;
		end
	end

	O_calc(i,:) = min_vec;
	d_calc(i)   = min_dist;
end


% output result
if any(any(O - O_calc > epsilon)) || any(d - d_calc > epsilon)
	printf('Wrong.\n');
else
	printf('Correct.\n');
end
	
