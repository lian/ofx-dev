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
#ifndef AFFINITY_H
#define AFFINITY_H

#include <iostream>
#include <assert.h>
#include <cv.h>

using namespace std;

/*! Affine transformation.
  \ingroup starter 
*/
class affinity : public CvMat
{
public:
  affinity(void);
  affinity(float u1, float v1, float up1, float vp1,
           float u2, float v2, float up2, float vp2,
           float u3, float v3, float up3, float vp3);

  ~affinity();

  bool estimate(float u1, float v1, float up1, float vp1,
                float u2, float v2, float up2, float vp2,
                float u3, float v3, float up3, float vp3);

  void transform_point(float u, float v, float * up, float * vp);
  void transform_point(double u, double v, double * up, double * vp);

  void compute_cvGetQuandrangleSubPix_transform(CvMat * A_quadrangle, int width, int height);

  friend ostream& operator<< (ostream& o, const affinity& A);

  float cvmGet(const int i, const int j);
  void  cvmSet(const int i, const int j, const float val);
  void  cvmSet(const int i, const int j, const double val);

  friend float cvmGet(const affinity * A, const int i, const int j);
  friend void  cvmSet(const affinity * A, const int i, const int j, const float val);
  friend void  cvmSet(const affinity * A, const int i, const int j, const double val);
  friend void mcvGetQuadrangleSubPix(IplImage * src, IplImage * dest, affinity * A, 
                                     int fill_outliers = 0, CvScalar fill_value = cvScalarAll(0));

private:
  void initialize(void);
  CvMat * AA, * B, * X;
};

ostream& operator<< (ostream& o, const affinity& A);

inline float affinity::cvmGet(const int i, const int j)
{
  return data.fl[3 * i + j];
}

inline void  affinity::cvmSet(const int i, const int j, const float val)
{
  data.fl[3 * i + j] = val;
}

inline void  affinity::cvmSet(const int i, const int j, const double val)
{
  data.fl[3 * i + j] = (float)val;
}

inline float cvmGet(const affinity * A, const int i, const int j)
{
  assert (A->rows == 3 && A->cols == 3);

  return A->data.fl[3 * i + j];
}

inline void cvmSet(const affinity * A, const int i, const int j, const float val)
{
  assert (A->rows == 3 && A->cols == 3);

  A->data.fl[3 * i + j] = val;
}

inline void cvmSet(const affinity * A, const int i, const int j, const double val)
{
  assert (A->rows == 3 && A->cols == 3);

  A->data.fl[3 * i + j] = (float)val;
}

/*!\ingroup starter*/
void mcvGetQuadrangleSubPix(IplImage * src, IplImage * dest, affinity * A, 
                            int fill_outliers, CvScalar fill_value);

#endif // AFFINITY_H
