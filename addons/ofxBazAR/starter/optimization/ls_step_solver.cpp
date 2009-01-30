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
#include <iostream>
#include "ls_step_solver.h"
using namespace std;

#ifdef WIN32
#include <float.h>
static inline int finite(double d) { return _finite(d); }
#endif

ls_step_solver::ls_step_solver(int state_size, int maximum_scalar_measure_number)
{
  this->maximum_scalar_measure_number = maximum_scalar_measure_number;

  M_copy = cvCreateMat(maximum_scalar_measure_number, state_size, CV_64F);
  M1 = new double[maximum_scalar_measure_number];
  M2 = new double[maximum_scalar_measure_number];
  b_copy = new double[maximum_scalar_measure_number];
}

ls_step_solver::~ls_step_solver()
{
	delete[] M1;
	delete[] M2;
	delete[] b_copy;
	if (M_copy) cvReleaseMat(&M_copy);
}

void ls_step_solver::resize(int state_size, int maximum_scalar_measure_number)
{
	if (maximum_scalar_measure_number > M_copy->rows ||
			state_size > M_copy->cols) {
		cvReleaseMat(&M_copy);
		delete[] M1;
		delete[] M2;
		delete[] b_copy;

		this->maximum_scalar_measure_number = maximum_scalar_measure_number;
		M_copy = cvCreateMat(maximum_scalar_measure_number, state_size, CV_64F);
		M1 = new double[maximum_scalar_measure_number];
		M2 = new double[maximum_scalar_measure_number];
		b_copy = new double[maximum_scalar_measure_number];
	}
}

bool ls_step_solver::qr_solve(CvMat * M, CvMat * b, CvMat * X)
{
#ifndef SORRY_VINCENT_Y_A_UN_BUG
	return cvSolve(M, b, X,  CV_LU) != 0;
#else
  int nr = M->rows;
  int nc = M->cols;
  int Mnc = M_copy->cols;

  assert(M_copy->rows == maximum_scalar_measure_number);
  assert(M->cols == M_copy->cols);
  assert(M->rows <= M_copy->rows);
  CvMat subM;
  cvGetSubRect(M_copy, &subM, cvRect(0,0,M->cols, M->rows));
  cvCopy(M, &subM);
  /*
  // copy M -> M_copy
  for(int i = 0; i < nr; i++)
  {
    double * pM = M->data.db + i * nc;
    double * pMc = M_copy->data.db + i * Mnc;

    for(int j = 0; j < nc; j++)
      pMc[j] = pM[j];
  }
  */

  assert(nc <= maximum_scalar_measure_number);
  assert(nr <= maximum_scalar_measure_number);

  // Decomposition QR:
  double * pM = M_copy->data.db;

  bool singular = false;
  double * ppMkk = pM;
  for(int k = 0; k < nc; k++)
  {
    double * ppMik = ppMkk;
    double eta = fabs(*ppMik);
    for(int i = k + 1; i < nr; i++)
    {
      double elt = fabs(*ppMik);
      if (eta < elt) eta = elt;
      ppMik += Mnc;
    }

    if (eta == 0)
    {
      M1[k] = M2[k] = 0;
      singular = true;
    }
    else
    {
      double sum = 0;
      double inv_eta = 1. / eta;
      double * ppMik = ppMkk;
      for(int i = k; i < nr; i++)
      {
        *ppMik *= inv_eta;
        sum += *ppMik * *ppMik;
        ppMik += Mnc;
      }
      double sigma = sqrt(sum);
      if (*ppMkk < 0)
        sigma = -sigma;
      *ppMkk += sigma;
      M1[k] = sigma * *ppMkk;
      M2[k] = -eta * sigma;
      for(int j = k + 1; j < nc; j++)
      {
        double sum = 0;
        double * ppMik = ppMkk;
        int Djk = j - k;
        for(int i = k; i < nr; i++)
        {
          sum += *ppMik * ppMik[Djk];
          ppMik += Mnc;
        }
        double tau = sum / M1[k];
        ppMik = ppMkk;
        for(int i = k; i < nr; i++)
        {
          ppMik[Djk] -= tau * *ppMik;
          ppMik += Mnc;
        }
      }
    }
    ppMkk += Mnc + 1;
  }

  assert(M_copy->rows == maximum_scalar_measure_number);

  // b_copy <- Qt b
  for(int i = 0; i < nr; i++)
    b_copy[i] = b->data.db[i];
  double * ppMjj = pM;
  for(int j = 0; j < nc; j++)
  {
    double tau = 0;
    double * ppMij = ppMjj;
    for(int i = j; i < nr; i++)
    {
      tau += *ppMij * b_copy[i];
      ppMij += Mnc;
    }
    tau /= M1[j];
    ppMij = ppMjj;
    for(int i = j; i < nr; i++)
    {
      b_copy[i] -= tau * *ppMij;
      ppMij += Mnc;
    }
    ppMjj += Mnc + 1;
  }

  assert(M_copy->rows == maximum_scalar_measure_number);

  // X = R-1 b
  double * p_X = X->data.db;
  p_X[nc - 1] = b_copy[nc - 1] / M2[nc - 1];
  if (!finite(p_X[nc-1])) return false;
  for(int i = nc - 2; i >= 0; i--)
  {
    double sum = 0;
    double * ppMij = pM + i * Mnc + (i + 1);

    for(int j = i + 1; j < nc; j++)
    {
      sum += *ppMij * p_X[j];
      ppMij++;
    }
    p_X[i] = (b_copy[i] - sum) / M2[i];
    if (!finite(p_X[i])) return false;
  }
  assert(M_copy->rows == maximum_scalar_measure_number);
  return true;
#endif
}
