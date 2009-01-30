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
#ifndef IMAGE_CLASSIFIER_H
#define IMAGE_CLASSIFIER_H

#include <vector>
#include <string>
using namespace std;

#include "image_class_example.h"
#include "example_generator.h"

//!\ingroup viewsets
//@{

enum{ 
	DETECT_MODEL_POINTS=0,
	BUILDING_TREE=1,
	FOREST_REFINEMENT=2,
	GENERATING_TESTING_SET=3
};

typedef void (*LEARNPROGRESSION)(int,int,int);

/*! 
  \ingroup viewsets
  \brief Image classifier 
*/
class image_classifier
{
public:
  image_classifier(int image_width, int image_height, int class_number, LEARNPROGRESSION LearnProgress=0);
  image_classifier(LEARNPROGRESSION LearnProgress=0);

  virtual ~image_classifier() { }

  virtual bool load(string /*directory_name*/) { return false; }
  virtual bool save(string /*directory_name*/) { return false; }
  virtual void refine(example_generator * vg, int call_number) = 0;
  virtual void test(example_generator * vg, int call_number) = 0;
  virtual int recognize(image_class_example * pv, float * confidence = 0, int dummy = 0) = 0 ;
  virtual float * posterior_probabilities(image_class_example * pv, int dummy = 0) = 0;

  LEARNPROGRESSION LearnProgression;
  
  int image_width, image_height;
  int class_number;

};

//@}
#endif // IMAGE_CLASSIFIER_H
