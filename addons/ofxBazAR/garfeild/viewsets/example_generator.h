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
#ifndef EXAMPLE_GENERATOR_H
#define EXAMPLE_GENERATOR_H

#include <vector>
using namespace std;

#include "image_class_example.h"

/*!
  \ingroup viewsets 
  \brief Generates random representants of image classes.

  The image classifiers can call the \c generate_random_examples function to generate the learning set.
  Use it when the learning set can be synthesized.
*/
class example_generator
{
public:
  example_generator(void) { }
  virtual ~example_generator() { }

  virtual vector<image_class_example *> * generate_random_examples(void) { return 0; }

  virtual void release_examples(void) { }
};

#endif // EXAMPLE_GENERATOR_H
