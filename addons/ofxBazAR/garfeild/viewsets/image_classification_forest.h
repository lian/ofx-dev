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
#ifndef IMAGE_CLASSIFICATION_FOREST_H
#define IMAGE_CLASSIFICATION_FOREST_H

#include "image_classifier.h"
#include "image_classification_tree.h"

/*!
  \ingroup viewsets 
  \brief Set of classifier trees.
*/

class image_classification_forest : public image_classifier
{
public:
  image_classification_forest(LEARNPROGRESSION LearnProgress=0);

  image_classification_forest(int image_width, int image_height, int class_number, 
                              int max_depth, int trees_number, 
                              LEARNPROGRESSION LearnProgress=0);

  ~image_classification_forest();

  void set_saving_directory_name(string directory_name);
  void create_trees_at_random(void);
  virtual void refine(example_generator * vg, int call_number);
  void restore_occurances();
  void reset_class_occurances(int class_index);
  virtual void test(example_generator * vg, int call_number);
  int recognize(image_class_example * pv, float * confidence = 0, int tree_number = -1);

  virtual float * posterior_probabilities(image_class_example * pv, int tree_number = -1);
  virtual void posterior_probabilities(image_class_example * pv, float * pp, int tree_number = -1);

  void change_class_number_and_reset_probabilities(int new_class_number);

  float * thresholds;
  float * misclassification_rates;

  bool load(string directory_name);
  bool save(string directory_name);

  bool is_ok() { return trees.size() != 0; }

//private:
  vector<image_classification_tree *> trees;
  int tree_number, max_depth;

  float* weights;

  string directory_name;
};

#endif // IMAGE_CLASSIFICATION_FOREST_H
