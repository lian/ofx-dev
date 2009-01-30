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
#include <float.h>
#include <math.h>

#include "../math/robust_estimators.h"
#include "../general/general.h"
#include "affinity.h"
#include "homography.h"

using namespace std;


homography::homography(void)
{
  initialize();
}

homography::homography(float u1, float v1, float up1, float vp1,
                       float u2, float v2, float up2, float vp2,
                       float u3, float v3, float up3, float vp3,
                       float u4, float v4, float up4, float vp4)
{
  initialize();

  estimate(u1, v1, up1, vp1,
          u2, v2, up2, vp2,
          u3, v3, up3, vp3,
          u4, v4, up4, vp4);
}

homography::~homography()
{
	if (AA) cvReleaseMat(&AA);
	if (B) cvReleaseMat(&AA);
	if (X) cvReleaseMat(&AA);
	if (AA_n) cvReleaseMat(&AA_n);
	if (B_n) cvReleaseMat(&AA_n);
	if (X_n) cvReleaseMat(&AA_n);
	delete [] data.ptr;
}

void homography::initialize(void)
{
	AA = cvCreateMat(8, 8, CV_32FC1);
	B  = cvCreateMat(8, 1, CV_32FC1);
	X  = cvCreateMat(8, 1, CV_32FC1);

	AA_n = NULL;
	B_n  = NULL;
	X_n  = NULL;
	match_number = 0;
	actual_match_number = 0;


	type = CV_32FC1;

	type = CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG | CV_MAT_TYPE(type);
	cols = 3;
	rows = 3;
	step = cols * CV_ELEM_SIZE(type);
	data.ptr = (uchar*)new float[cols * rows];
	refcount = NULL;
}

ostream& operator<< (ostream& o, const homography& H)
{
  o << cvmGet(&H, 0, 0) << "\t" << cvmGet(&H, 0, 1) << "\t" << cvmGet(&H, 0, 2) << endl;
  o << cvmGet(&H, 1, 0) << "\t" << cvmGet(&H, 1, 1) << "\t" << cvmGet(&H, 1, 2) << endl;
  o << cvmGet(&H, 2, 0) << "\t" << cvmGet(&H, 2, 1) << "\t" << cvmGet(&H, 2, 2) << endl;

  return o;
}

void homography::add_match(CvMat * pAA, CvMat * pB, int point_index, 
                           float u, float v, float up, float vp)
{
  int row = point_index * 2;

  ::cvmSet(pAA, row, 0, 0);
  ::cvmSet(pAA, row, 1, 0);
  ::cvmSet(pAA, row, 2, 0);
  ::cvmSet(pAA, row, 3, -u);
  ::cvmSet(pAA, row, 4, -v);
  ::cvmSet(pAA, row, 5, -1);
  ::cvmSet(pAA, row, 6, u * vp);
  ::cvmSet(pAA, row, 7, v * vp);

  ::cvmSet(pB, row, 0, -vp);

  row++;

  ::cvmSet(pAA, row, 0, u);
  ::cvmSet(pAA, row, 1, v);
  ::cvmSet(pAA, row, 2, 1);
  ::cvmSet(pAA, row, 3, 0);
  ::cvmSet(pAA, row, 4, 0);
  ::cvmSet(pAA, row, 5, 0);
  ::cvmSet(pAA, row, 6, -u * up);
  ::cvmSet(pAA, row, 7, -v * up);

  ::cvmSet(pB, row, 0, up);
}

bool homography::estimate(float u1, float v1, float up1, float vp1,
                          float u2, float v2, float up2, float vp2,
                          float u3, float v3, float up3, float vp3,
                          float u4, float v4, float up4, float vp4)
{
  add_match(AA, B, 0, u1, v1, up1, vp1);
  add_match(AA, B, 1, u2, v2, up2, vp2);
  add_match(AA, B, 2, u3, v3, up3, vp3);
  add_match(AA, B, 3, u4, v4, up4, vp4);

  int ok = cvSolve(AA, B, X, CV_SVD);

  if (ok != 1)
  {
    cerr << "homography::estimate: cvSolve failure" << endl;
    return false;
  }

  cvmSet(0, 0, ::cvmGet(X, 0, 0));
  cvmSet(0, 1, ::cvmGet(X, 1, 0));
  cvmSet(0, 2, ::cvmGet(X, 2, 0));

  cvmSet(1, 0, ::cvmGet(X, 3, 0));
  cvmSet(1, 1, ::cvmGet(X, 4, 0));
  cvmSet(1, 2, ::cvmGet(X, 5, 0));

  cvmSet(2, 0, ::cvmGet(X, 6, 0));
  cvmSet(2, 1, ::cvmGet(X, 7, 0));
  cvmSet(2, 2, 1.);

  return true;
}

void homography::transform_point(float u, float v, float * up, float * vp)
{
  float k = float(1. / (cvmGet(2, 0) * u + cvmGet(2, 1) * v + cvmGet(2, 2)));

  *up = float(k * (cvmGet(0, 0) * u + cvmGet(0, 1) * v + cvmGet(0, 2)));
  *vp = float(k * (cvmGet(1, 0) * u + cvmGet(1, 1) * v + cvmGet(1, 2)));
}

void homography::transform_point(double u, double v, double * up, double * vp)
{
  float k = float(1. / (cvmGet(2, 0) * u + cvmGet(2, 1) * v + cvmGet(2, 2)));

  *up = k * (cvmGet(0, 0) * u + cvmGet(0, 1) * v + cvmGet(0, 2));
  *vp = k * (cvmGet(1, 0) * u + cvmGet(1, 1) * v + cvmGet(1, 2));
}


void homography::set_match_number(int n)
{
  if (n == 0)
    return;

  match_number = n;
  actual_match_number = 0;

  if (AA_n != NULL)
    release_matches();

  AA_n = cvCreateMat(2 * match_number, 8, CV_32FC1);
  X_n  = cvCreateMat(8, 1, CV_32FC1);
  B_n  = cvCreateMat(2 * match_number, 1, CV_32FC1);
}

void homography::release_matches(void)
{
  cvReleaseMat(&AA_n);
  cvReleaseMat(&B_n);
  cvReleaseMat(&X_n);
}

void homography::add_match(float u, float v, float up, float vp)
{
  add_match(AA_n, B_n, actual_match_number, u, v, up, vp);
  actual_match_number++;
}

void homography::estimate(void)
{
  if (match_number != actual_match_number)
  {
    cerr << "error when calling estimate_linear_method: not enough given matches." << endl;
    return;
  }

  int ok = cvSolve(AA_n, B_n, X_n, CV_SVD);

  if (ok != 1)
  {
    cerr << "homography::estimate: cvSolve failure" << endl;
    return;
  }

  cvmSet(0, 0, ::cvmGet(X_n, 0, 0));
  cvmSet(0, 1, ::cvmGet(X_n, 1, 0));
  cvmSet(0, 2, ::cvmGet(X_n, 2, 0));

  cvmSet(1, 0, ::cvmGet(X_n, 3, 0));
  cvmSet(1, 1, ::cvmGet(X_n, 4, 0));
  cvmSet(1, 2, ::cvmGet(X_n, 5, 0));

  cvmSet(2, 0, ::cvmGet(X_n, 6, 0));
  cvmSet(2, 1, ::cvmGet(X_n, 7, 0));
  cvmSet(2, 2, 1.);
}
