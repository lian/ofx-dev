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
/*! \ingroup starter */
#ifndef LINEAR_SYSTEMS_H
#define LINEAR_SYSTEMS_H

bool solve_ls(double A11, double A12, double A13, double & x1, double B1, 
              double A21, double A22, double A23, double & x2, double B2, 
              double A31, double A32, double A33, double & x3, double B3);

#endif // LINEAR_SYSTEMS_H
