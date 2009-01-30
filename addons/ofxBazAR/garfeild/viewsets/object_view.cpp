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

#include <starter.h>
#include "object_view.h"

// Constructor for training stage:
object_view::object_view(PyrImage * _image) : 
                image(cvCreateImage(cvGetSize(_image->images[0]), IPL_DEPTH_8U, 1), _image->nbLev),
                gradX(cvCreateImage(cvGetSize(_image->images[0]), IPL_DEPTH_16S, 1), _image->nbLev),
                gradY(cvCreateImage(cvGetSize(_image->images[0]), IPL_DEPTH_16S, 1), _image->nbLev)
{
}

// Constructor for recognition stage (alloc memory once):
object_view::object_view(int width, int height, int nbLev) : 
                image(cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1), nbLev),
                gradX(cvCreateImage(cvSize(width, height), IPL_DEPTH_16S, 1), nbLev),
                gradY(cvCreateImage(cvSize(width, height), IPL_DEPTH_16S, 1), nbLev)
{
}

void object_view::build_from_image_0(int kernelSize)
{
  if (kernelSize == 0)
    image.build();
  else
  {
    image.smoothLevel0(kernelSize);
    image.build();
  }
  comp_gradient();
}

void object_view::build(IplImage *im, int kernelSize) 
{
  if (kernelSize == 0)
    cvCopy(im, image[0]);
  else if (kernelSize < 0)
    cvSmooth(im, image[0], CV_GAUSSIAN, 3, 3);
  else
    cvSmooth(im, image[0], CV_GAUSSIAN, kernelSize, kernelSize);
  image.build();
  comp_gradient();
}

void object_view::comp_gradient()
{
  for (int l = 0; l < image.nbLev; ++l) {
    cvSobel(image[l], gradX[l], 1, 0, 1);
    cvSobel(image[l], gradY[l], 0, 1, 1);
  }
}

object_view::~object_view()
{
}

