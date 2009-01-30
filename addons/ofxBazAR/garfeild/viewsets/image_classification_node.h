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
#ifndef IMAGE_CLASSIFICATION_NODE_H
#define IMAGE_CLASSIFICATION_NODE_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#include <math.h>
#include "image_class_example.h"

//!\ingroup viewsets
//@{

/*! 
  \ingroup viewsets
  \brief Node for classifier trees (cf \ref image_classification_tree)
*/
class image_classification_node
{
public:
  image_classification_node(void);
  ~image_classification_node(void);
  image_classification_node(int depth, int class_number, image_classification_node * parent = 0);
  
  friend ostream& operator<< (ostream& o, const image_classification_node& node);
  friend istream& operator>> (istream& i, image_classification_node& node);
  
  void add_example(image_class_example * pv);

  bool should_stop_recursion(void);
  void end_recursion(void);
  void expand(void);
  void premature_end_recursion(void);
  
  bool is_leaf(void) const;
  int leaves_number(void);
  int node_number(void);
  int subtree_depth(void);
  void set_Dot(int image_width, int image_height);
  void set_Dot(int _du1, int _dv1, int _du2, int _dv2, int image_width, int image_height);
  bool fall_in_child(image_class_example * pv, int child_index);
  int dot_product(image_class_example * pv) const;
  int child_index(image_class_example * pv) const;
  
  void reestimate_probabilities_recursive(float * weights = 0);
  void restore_occurances_recursive(float * weights = 0);
  void reset_class_occurances_recursive(int class_index);
  void save_probability_sums_recursive(std::ofstream& wfs);
  void load_probability_sums_recursive(std::ifstream& wfs);

  float projection(image_class_example * pv) const;
  
  void change_class_number_and_reset_probabilities(int new_class_number);

  int represented_class_number(void) const;
  
  void print_name(void);
  ostream& name(ostream& o) const;
  
  int nb_examples() { if (examples == 0) return 0; else return int(examples->size()); }

  const int children_number;
  int d1, d2, du1, dv1, du2, dv2;
  bool leaf;
  image_classification_node *children[3];
  image_classification_node * parent;
  int depth, index;

  int * children_index; // for tree loading only
  
  float * P;
  int best_class;
  float P_sum;

  float probability_sum;
  
  vector<image_class_example *> *examples;

  int class_number;
};

inline bool image_classification_node::is_leaf(void) const
{
  return leaf;
}

extern int global_patch_size;

ostream& operator<< (ostream& o, const image_classification_node& node);
istream& operator>> (istream& i, image_classification_node& node);

//@}
#endif // IMAGE_CLASSIFICATION_NODE_H
