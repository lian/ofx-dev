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
#ifndef IMAGE_CLASS_EXAMPLE_H
#define IMAGE_CLASS_EXAMPLE_H

#include "../keypoints/keypoint.h"
#include "object_view.h"

/*!
  \ingroup viewsets 
  \brief A representant of an image class.
*/

class image_class_example
{
public:
  image_class_example(void); 
  image_class_example(int class_index, 
                      float u, float v, float scale, 
                      object_view * ov, 
                      int patch_size);

  // For other problems:
  image_class_example(int class_index, IplImage * image);

  ~image_class_example(void);

  int class_index;
  float orig_u, orig_v;

  keypoint *point2d;
  object_view * view;

  IplImage * original_image;
  IplImage * preprocessed;

  void alloc(int sz);

  float dot_product;
};

#endif // IMAGE_CLASS_EXAMPLE_H
