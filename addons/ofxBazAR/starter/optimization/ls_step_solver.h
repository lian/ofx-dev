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
#ifndef LS_STEP_SOLVER_H
#define LS_STEP_SOLVER_H

#include <cxcore.h>

//!\ingroup starter
//@{

class ls_step_solver
{
public:
  ls_step_solver(int state_size, int maximum_scalar_measure_number);
  ~ls_step_solver();
  void resize(int state_size, int maximum_scalar_measure_number);

  // J data are destroyed
  // return true on success, false on failure
  bool qr_solve(CvMat * J, CvMat * eps, CvMat * ds);

  CvMat * M_copy;
  double * M1, * M2;
  double * b_copy;
  int maximum_scalar_measure_number;
};

//@}

#endif // LS_STEP_SOLVER_H
