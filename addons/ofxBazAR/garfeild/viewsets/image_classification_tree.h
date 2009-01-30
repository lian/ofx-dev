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
#ifndef IMAGE_CLASSIFICATION_TREE_H
#define IMAGE_CLASSIFICATION_TREE_H

#include <vector>
using namespace std;

#include "image_classifier.h"
#include "image_classification_node.h"

/*!
  \ingroup viewsets 
  \brief Image classifier tree.
*/
class image_classification_tree : public image_classifier
{
public:
  image_classification_tree(LEARNPROGRESSION LearnProgress=0);

  image_classification_tree(int image_width, int image_height, 
                            int class_number, int max_depth, 
                            LEARNPROGRESSION LearnProgress=0);

  ~image_classification_tree();

  bool load(string filename);
  bool save(string filename);
  
  virtual void refine(example_generator * vg, int call_number);
  virtual void test(example_generator * vg, int call_number);
  int recognize(image_class_example * pv, float * confidence = 0, int dummy = 0);
  virtual float * posterior_probabilities(image_class_example * pv, int dummy = 0);

  void change_class_number_and_reset_probabilities(int new_class_number);

  int node_number(void);
  int leaves_number(void);
  int actual_max_depth(void);

  double entropy(void);

  image_classification_node * root;
  int max_depth;
  
 private:
  image_classification_node * extract_node(vector <image_classification_node*> * L);
  
  int depth, new_node_index;
};

#endif // IMAGE_CLASSIFICATION_TREE_H
