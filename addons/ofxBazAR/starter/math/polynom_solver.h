/*
Copyright 2005, 2006 Computer Vision Lab, 
Ecole Polytechnique Federale de Lausanne (EPFL), Switzerland. 
All rights reserved.

This file is part of BazAR.

BazAR is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

BazAR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
BazAR; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/
#ifndef POLYNOM_SOLVER_H
#define POLYNOM_SOLVER_H

int solve_deg2(double a, double b, double c, double & x1, double & x2);

int solve_deg3(double a, double b, double c, double d, 
               double & x0, double & x1, double & x2);

int solve_deg4(double a, double b, double c, double d, double e,
               double & x0, double & x1, double & x2, double & x3);

#endif // POLYNOM_SOLVER_H
