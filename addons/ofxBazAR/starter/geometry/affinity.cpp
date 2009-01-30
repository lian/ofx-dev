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
#include "affinity.h"


affinity::affinity(void)
{
  initialize();
}

affinity::affinity(float u1, float v1, float up1, float vp1,
                   float u2, float v2, float up2, float vp2,
                   float u3, float v3, float up3, float vp3)
{
  initialize();

  estimate(u1, v1, up1, vp1,
           u2, v2, up2, vp2,
           u3, v3, up3, vp3);
}

void affinity::initialize(void)
{
  AA = cvCreateMat(6, 6, CV_32FC1);
  X  = cvCreateMat(6, 1, CV_32FC1);
  B  = cvCreateMat(6, 1, CV_32FC1);
  type = CV_32FC1;

  type = CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG | CV_MAT_TYPE(type);
  cols = 3;
  rows = 3;
  step = cols * CV_ELEM_SIZE(type);
  data.ptr = (uchar*)new float[cols * rows];
  refcount = NULL;

  cvmSet(2, 0, 0.);
  cvmSet(2, 1, 0.);
  cvmSet(2, 2, 1.);
}

affinity::~affinity()
{
	cvReleaseMat(&AA);
	cvReleaseMat(&X);
	cvReleaseMat(&B);
	delete [] data.ptr;
}

ostream& operator<< (ostream& o, const affinity& A)
{
  o << cvmGet(&A, 0, 0) << "\t" << cvmGet(&A, 0, 1) << "\t" << cvmGet(&A, 0, 2) << endl;
  o << cvmGet(&A, 1, 0) << "\t" << cvmGet(&A, 1, 1) << "\t" << cvmGet(&A, 1, 2) << endl;

  return o;
}

bool affinity::estimate(float u1, float v1, float up1, float vp1,
                        float u2, float v2, float up2, float vp2,
                        float u3, float v3, float up3, float vp3)
{
  ::cvmSet(AA, 0, 0, u1); ::cvmSet(AA, 0, 1, v1); ::cvmSet(AA, 0, 2, 1.); ::cvmSet(AA, 0, 3, 0.); ::cvmSet(AA, 0, 4, 0.); ::cvmSet(AA, 0, 5, 0.);
  ::cvmSet(AA, 1, 0, 0.); ::cvmSet(AA, 1, 1, 0.); ::cvmSet(AA, 1, 2, 0.); ::cvmSet(AA, 1, 3, u1); ::cvmSet(AA, 1, 4, v1); ::cvmSet(AA, 1, 5, 1.);

  ::cvmSet(AA, 2, 0, u2); ::cvmSet(AA, 2, 1, v2); ::cvmSet(AA, 2, 2, 1.); ::cvmSet(AA, 2, 3, 0.); ::cvmSet(AA, 2, 4, 0.); ::cvmSet(AA, 2, 5, 0.);
  ::cvmSet(AA, 3, 0, 0.); ::cvmSet(AA, 3, 1, 0.); ::cvmSet(AA, 3, 2, 0.); ::cvmSet(AA, 3, 3, u2); ::cvmSet(AA, 3, 4, v2); ::cvmSet(AA, 3, 5, 1.);

  ::cvmSet(AA, 4, 0, u3); ::cvmSet(AA, 4, 1, v3); ::cvmSet(AA, 4, 2, 1.); ::cvmSet(AA, 4, 3, 0.); ::cvmSet(AA, 4, 4, 0.); ::cvmSet(AA, 4, 5, 0.);
  ::cvmSet(AA, 5, 0, 0.); ::cvmSet(AA, 5, 1, 0.); ::cvmSet(AA, 5, 2, 0.); ::cvmSet(AA, 5, 3, u3); ::cvmSet(AA, 5, 4, v3); ::cvmSet(AA, 5, 5, 1.);

  ::cvmSet(B, 0, 0, up1);
  ::cvmSet(B, 1, 0, vp1);

  ::cvmSet(B, 2, 0, up2);
  ::cvmSet(B, 3, 0, vp2);

  ::cvmSet(B, 4, 0, up3);
  ::cvmSet(B, 5, 0, vp3);

  int ok = cvSolve(AA, B, X, CV_SVD);

  if (ok != 1)
  {
    cerr << "affinity::estimate: cvSolve failure" << endl;
    return false;
  }

  cvmSet(0, 0, ::cvmGet(X, 0, 0));
  cvmSet(0, 1, ::cvmGet(X, 1, 0));
  cvmSet(0, 2, ::cvmGet(X, 2, 0));

  cvmSet(1, 0, ::cvmGet(X, 3, 0));
  cvmSet(1, 1, ::cvmGet(X, 4, 0));
  cvmSet(1, 2, ::cvmGet(X, 5, 0));

  return true;
}

void affinity::transform_point(float u, float v, float * up, float * vp)
{
  *up = float(cvmGet(0, 0) * u + cvmGet(0, 1) * v + cvmGet(0, 2));
  *vp = float(cvmGet(1, 0) * u + cvmGet(1, 1) * v + cvmGet(1, 2));
}

void affinity::transform_point(double u, double v, double * up, double * vp)
{
  *up = cvmGet(0, 0) * u + cvmGet(0, 1) * v + cvmGet(0, 2);
  *vp = cvmGet(1, 0) * u + cvmGet(1, 1) * v + cvmGet(1, 2);
}

void affinity::compute_cvGetQuandrangleSubPix_transform(CvMat * A_q, int w, int h)
{
  float det = float(cvmGet(0, 0) * cvmGet(1, 1) - cvmGet(1, 0) * cvmGet(0, 1));

  ::cvmSet(A_q, 0, 0,  cvmGet(1, 1) / det);
  ::cvmSet(A_q, 0, 1, -cvmGet(0, 1) / det);
  ::cvmSet(A_q, 1, 0, -cvmGet(1, 0) / det);
  ::cvmSet(A_q, 1, 1,  cvmGet(0, 0) / det);

  ::cvmSet(A_q, 0, 2, ::cvmGet(A_q, 0, 0) * (w / 2 - cvmGet(0, 2)) + ::cvmGet(A_q, 0, 1) * (h / 2 - cvmGet(1, 2)));
  ::cvmSet(A_q, 1, 2, ::cvmGet(A_q, 1, 0) * (w / 2 - cvmGet(0, 2)) + ::cvmGet(A_q, 1, 1) * (h / 2 - cvmGet(1, 2)));
}

void mcvGetQuadrangleSubPix(IplImage * src, IplImage * dest, affinity * A, 
                            int /*fill_outliers*/, CvScalar /*fill_value*/)
{
  A->rows = 2;
  cvGetQuadrangleSubPix(src, dest, A);
  A->rows = 3;
}

