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
#include "linear_systems.h"
#include "linear_algebra.h"

bool solve_ls(double A11, double A12, double A13, double & x1, double B1, 
              double A21, double A22, double A23, double & x2, double B2, 
              double A31, double A32, double A33, double & x3, double B3)
{
  double det = gfla_det(A11, A12, A13,
                        A21, A22, A23, 
                        A31, A32, A33);

  x1 = x2 = x3 = 0;
  if (det == 0) return false;

  double inv_det = 1. / det;

  x1 = inv_det * (gfla_det(A22, A23, A32, A33) * B1 + gfla_det(A13, A12, A33, A32) * B2 + gfla_det(A12, A13, A22, A23) * B3);
  x2 = inv_det * (gfla_det(A23, A21, A33, A31) * B1 + gfla_det(A11, A13, A31, A33) * B2 + gfla_det(A13, A11, A23, A21) * B3);
  x3 = inv_det * (gfla_det(A21, A22, A31, A32) * B1 + gfla_det(A12, A11, A32, A31) * B2 + gfla_det(A11, A12, A21, A22) * B3);

  return true;
}

