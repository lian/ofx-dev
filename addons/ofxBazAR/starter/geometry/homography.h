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
#ifndef HOMOGRAPHY_H
#define HOMOGRAPHY_H

#include <iostream>
using namespace std;

#include <cv.h>


/*!
  \brief Static class for the estimation of homographies.
  \ingroup starter 
  
  Provides functions to estimate the homography 
  - from 4 point correspondences or
  - from n point correspondences.
  
  - From 4 point correspondences:
  Use one of the estimate() functions:
\code
homography::estimate(H, u1, v1, up1, vp1, u2, v2, up2, vp2, ...)
\endcode
or
\code
CvMat * H = homography::estimate(H, u1, v1, up1, vp1, u2, v2, up2, vp2, ...)
\endcode

Estimates H using a linear method.

- From n correspondences
  if \c H0 \c != \c NULL, it is used to initialize H. H0 can be an affinity matrix.
  \c c is the parameter of the Tukey robust estimator.
*/

class homography : public CvMat
{
public:
  homography();

  homography(float u1, float v1, float up1, float vp1,
             float u2, float v2, float up2, float vp2,
             float u3, float v3, float up3, float vp3,
             float u4, float v4, float up4, float vp4);

  ~homography();

  //! Estimates H from 4 point correspondences
  bool estimate(float u1, float v1, float up1, float vp1,
                float u2, float v2, float up2, float vp2,
                float u3, float v3, float up3, float vp3,
                float u4, float v4, float up4, float vp4);

  //! Estimation from n correspondences. See \ref homography description.
  void set_match_number(int n);
  void add_match(float u, float v, float up, float vp);
  void release_matches(void);

  void estimate(void);

  // Display:
  friend ostream& operator<< (ostream& o, const homography& H);

  //! Computes H(u,v)
  void transform_point(float u, float v, float * up, float * vp);
  void transform_point(double u, double v, double * up, double * vp);

  float cvmGet(const int i, const int j);
  void  cvmSet(const int i, const int j, const float val);
  void  cvmSet(const int i, const int j, const double val);

  friend float cvmGet(const homography * H, const int i, const int j);
  friend void  cvmSet(const homography * H, const int i, const int j, const float val);
  friend void  cvmSet(const homography * H, const int i, const int j, const double val);

private:
  void initialize(void);

  void add_match(CvMat * AA, CvMat * B, int point_index, 
                 float u, float v, float up, float vp);

  CvMat * AA, * B, * X;
  CvMat * AA_n, * B_n, * X_n;
  int match_number, actual_match_number;
};

ostream& operator<< (ostream& o, const homography& H);

inline float homography::cvmGet(const int i, const int j)
{
  return data.fl[3 * i + j];
}

inline void  homography::cvmSet(const int i, const int j, const float val)
{
  data.fl[3 * i + j] = val;
}

inline void  homography::cvmSet(const int i, const int j, const double val)
{
  data.fl[3 * i + j] = (float)val;
}

inline float cvmGet(const homography * H, const int i, const int j)
{
  assert (H->rows == 3 && H->cols == 3);

  return H->data.fl[3 * i + j];
}

inline void cvmSet(const homography * H, const int i, const int j, const float val)
{
  assert (H->rows == 3 && H->cols == 3);

  H->data.fl[3 * i + j] = val;
}

inline void cvmSet(const homography * H, const int i, const int j, const double val)
{
  assert (H->rows == 3 && H->cols == 3);

  H->data.fl[3 * i + j] = (float)val;
}

#endif // HOMOGRAPHY_H
