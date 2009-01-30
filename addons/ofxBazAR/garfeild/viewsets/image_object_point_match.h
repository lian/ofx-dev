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
#ifndef IMAGE_OBJECT_POINT_MATCH_H
#define IMAGE_OBJECT_POINT_MATCH_H

#include "../keypoints/keypoint.h"
#include "object_keypoint.h"

//!\ingroup viewsets
class image_object_point_match
{
public:
  keypoint * image_point;
  object_keypoint * object_point;
  float score;

  bool inlier;
};

#endif // IMAGE_OBJECT_POINT_MATCH_H
