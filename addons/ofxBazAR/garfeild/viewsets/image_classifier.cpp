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
#include "image_classifier.h"

image_classifier::image_classifier(LEARNPROGRESSION _LearnProgress)
{
  LearnProgression=_LearnProgress;
}


image_classifier::image_classifier(int _image_width, int _image_height, int _class_number,
                                   LEARNPROGRESSION _LearnProgress)
{
  LearnProgression=_LearnProgress;

  image_width  = _image_width;
  image_height = _image_height;
  class_number = _class_number;
}

