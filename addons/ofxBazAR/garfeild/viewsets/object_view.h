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
#ifndef OBJECT_VIEW_H
#define OBJECT_VIEW_H

#include <cv.h>

#include "../keypoints/keypoint.h"
#include "../keypoints/yape.h"
#include "../viewsets/image_object_point_match.h"
#include "../keypoints/keypoint.h"

/*! an object view contains 3 pyramids for image and gradient 
  \ingroup viewsets
*/
class object_view
{
public:

  // Constructor for training stage:
  object_view(PyrImage * image);

  // Constructor for recognition stage (alloc memory once):
  object_view(int width, int height, int nbLev);

  ~object_view();

  void build_from_image_0(int kernelSize = 3);
  void build(IplImage *im, int kernelSize = -1);
  void comp_gradient();

  PyrImage image;
  PyrImage gradX;
  PyrImage gradY;

  float affine_projection[6];
  int u0, v0;
  float alpha, scale;
};

#endif // OBJECT_VIEW_H
