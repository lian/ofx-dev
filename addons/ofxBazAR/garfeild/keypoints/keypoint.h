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
#ifndef KEYPOINT_H
#define KEYPOINT_H

#include <cv.h>

/*! \defgroup keypoints Feature points detection
 * \ingroup garfeild
 */
//! \ingroup keypoints 
//@{

/*! 
  \brief A 2D feature point as detected by a point detector (\ref yape for example).
*/
class keypoint
{
public:
  keypoint(void) {}
  ~keypoint() {}

  //@{
  float u, v;  //!< 2D coordinates of the point
  
  float scale; //!< point scale 
  float score; //!< higher is the score, stronger is the point
  //@}

  //! Use \ref keypoint_orientation_corrector to compute keypoint orientation:
  float orientation_in_radians; //!< Between 0 and 2 Pi

  //@{
  //! Used for point matching, should disappear soon
  float meanI, sigmaI;
  keypoint * potential_correspondent;
  float match_score;
  int i_bucket, j_bucket;

  int index; // used to locate the keypoint in the keypoint array after matching.
  //@}
};

/*! \file */

/*! 
  \fn CvPoint mcvPoint(keypoint & p) 
  \brief Convert a keypoint into a cvPoint from OpenCV
  \param p the point
*/
inline CvPoint mcvPoint(keypoint & p)
{
  int s = int(p.scale);
  int K = 1 << s;
  return cvPoint(int(K * p.u + 0.5), int(K * p.v + 0.5));
}

//@}
#endif // KEYPOINT_H
