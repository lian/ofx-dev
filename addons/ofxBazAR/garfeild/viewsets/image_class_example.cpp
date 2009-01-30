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
using namespace std;

#include "../../starter/image/mcv.h"
#include "image_class_example.h"

image_class_example::image_class_example(int _class_index, 
                                         float u, float v, float scale, 
                                         object_view * ov, 
                                         int patch_size)
{
  point2d = new keypoint; //< TODO: delete this keypoint somewhere.
  point2d->u = u;
  point2d->v = v;
  point2d->scale = scale;
  preprocessed = cvCreateImage(cvSize(patch_size, patch_size), IPL_DEPTH_8U, 1);

  view = ov;

  class_index = _class_index;

  original_image = 0;
}

image_class_example::image_class_example(int p_class_index, IplImage * image)
{
  class_index = p_class_index;
  point2d = 0;

  original_image = cvCloneImage(image);
}

image_class_example::image_class_example()
{
  point2d = 0;
  original_image = 0;
  preprocessed = 0;
  view = 0;
}

image_class_example::~image_class_example(void)
{
  if (preprocessed) cvReleaseImage(&preprocessed);
  if (original_image) cvReleaseImage(&original_image);
}

void image_class_example::alloc(int sz) {
  preprocessed = cvCreateImage(cvSize(sz, sz), IPL_DEPTH_8U, 1);
}

