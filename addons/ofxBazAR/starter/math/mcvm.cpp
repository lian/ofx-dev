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
#include "mcvm.h"

void mcvmPrint(ostream & o, CvMat * A, char * matrix_name)
{
  if (A->cols == 1)
  {
    if (matrix_name != 0)
      o << matrix_name << " = [ ";
    else
      o << " [ ";
    for(int i = 0; i < A->rows; i++)
      o << cvmGet(A, i, 0) << "; ";
    o << "]^t" << endl;
    return;
  }

  if (matrix_name != 0)
    o << matrix_name << ":" << endl;
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
      o << cvmGet(A, i, j) << " ";
    o << endl;
  }
}

