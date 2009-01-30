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
#include <assert.h>

#include <starter.h>
#include "image_classification_node.h"

image_classification_node::image_classification_node(void) : children_number(2)
{
  depth = -1;
  class_number = -1;
  parent = 0;
  P = 0;

  leaf = true;

  examples = 0;
}

image_classification_node::image_classification_node(int _depth, int _class_number, image_classification_node * _parent) : children_number(2)
{
  depth = _depth;
  class_number = _class_number;
  parent = _parent;

  leaf = true;

  examples = 0;
  P = 0;
}

image_classification_node::~image_classification_node(void)
{
  if (examples) delete examples;
  if (P) delete[] P;

  if (!is_leaf())
    for(int i = 0; i < children_number; i++)
      delete children[i];
}

void image_classification_node::add_example(image_class_example * pv)
{
  if (examples == 0)
    examples = new vector<image_class_example *>;
  examples->push_back(pv);
}

bool image_classification_node::should_stop_recursion(void)
{
  if (nb_examples() < 2)
    return true;

  // Return true if only one class is present in the examples:
  int represented_class_number = 0;
  int first_represented_class_index = 0;
  for(vector<image_class_example *>::iterator it = examples->begin(); it < examples->end(); it++)
  {
    if (represented_class_number == 0)
    {
      first_represented_class_index = (*it)->class_index;
      represented_class_number = 1;
    }
    else
      if ((*it)->class_index != first_represented_class_index)
        return false;
  }

  return true;
}

void image_classification_node::premature_end_recursion(void)
{
  P = new float[class_number];

  for(int i = 0; i < class_number; i++)
    P[i] = 0.;

  if (nb_examples() > 0)
  {
    for(vector<image_class_example *>::iterator it = examples->begin(); it < examples->end(); it++)
      P[(*it)->class_index]++;

    for(int i = 0; i < class_number; i++)
      P[i] /= examples->size();
  }

  best_class = 0;
  float best_p = P[best_class];
  for(int i = 0; i < class_number; i++)
  {
    if (P[i] > best_p)
    {
      best_p = P[i];
      best_class = i;
    }
  }
}

void image_classification_node::expand(void)
{
  assert(children_number <= 3);

  for(int i = 0; i < children_number; i++)
    children[i] = new image_classification_node(depth + 1, class_number, this);

  if (examples != 0)
  {
    for(vector<image_class_example *>::iterator it = examples->begin(); it < examples->end(); it++)
      for(int i = 0; i < children_number; i++)
        if (fall_in_child(*it, i))
          children[i]->add_example(*it);

    delete examples;

    examples = 0;
  }
}

bool image_classification_node::fall_in_child(image_class_example * pv, int child_index)
{
  int dp = dot_product(pv);

  if (dp <= 0 && child_index == 0) return true;
  if (dp >  0 && child_index == 1) return true;

  return false;
}

int image_classification_node::dot_product(image_class_example * pv) const
{
  unsigned char * I = mcvRow(pv->preprocessed, 0, unsigned char);
  return (int)I[d1] - (int)I[d2];
}

int image_classification_node::child_index(image_class_example * pv) const
{
  int dp = dot_product(pv);
  if (dp <= 0) return 0; 

  return 1;
}

void image_classification_node::end_recursion(void)
{
  for(int i = 0; i < children_number; i++)
  {
    children[i] = new image_classification_node(depth + 1, class_number, this);
    children[i]->P = new float[class_number];
    for(int j = 0; j < class_number; j++)
      children[i]->P[j] = 0.;
  }
}

void image_classification_node::change_class_number_and_reset_probabilities(int new_class_number)
{
  class_number = new_class_number;

  if (is_leaf())
  {
    delete [] P;

    P = new float[class_number];

    for(int i = 0; i < class_number; i++)
      P[i] = 0.;
  }
  else
    for(int i = 0; i < children_number; i++)
      children[i]->change_class_number_and_reset_probabilities(new_class_number);
}

void image_classification_node::reestimate_probabilities_recursive(float * weights)
{
  if (is_leaf())
  {
    if (weights == 0)
    {
      probability_sum = 0;

      for(int i = 0; i < class_number; i++)
        probability_sum += P[i];

      for(int i = 0; i < class_number; i++)
        P[i] = (probability_sum > 0) ? P[i] / probability_sum : 0.f;
    }
    else
    {
      probability_sum = 0;

      for(int i = 0; i < class_number; i++)
        probability_sum += weights[i] * P[i];

      for(int i = 0; i < class_number; i++)
        P[i] = (probability_sum > 0) ? weights[i] * P[i] / probability_sum : 0.f;
    }

    best_class = 0;
    float best_p = P[best_class];
    for(int i = 0; i < class_number; i++)
      if (P[i] > best_p)
      {
        best_p = P[i];
        best_class = i;
      }
  }
  else
    for(int i = 0; i < children_number; i++)
      children[i]->reestimate_probabilities_recursive(weights);
}

void image_classification_node::restore_occurances_recursive(float * weights)
{
  if (is_leaf())
  {    
    if (weights == 0)
    {
      for(int i = 0; i < class_number; i++)
        P[i] = P[i] * probability_sum;
    }
    else
    {
      for(int i = 0; i < class_number; i++)
        P[i] = (weights[i] > 0) ? probability_sum * P[i] / weights[i] : 0.f;
    }
  }
  else
    for(int i = 0; i < children_number; i++)
      children[i]->restore_occurances_recursive(weights);
}

void image_classification_node::reset_class_occurances_recursive(int class_index)
{
  if (is_leaf())
    P[class_index] = 0;
  else
    for(int i = 0; i < children_number; i++)
      children[i]->reset_class_occurances_recursive(class_index);
}

void image_classification_node::save_probability_sums_recursive(std::ofstream& wfs) 
{
  if (is_leaf())
    wfs << probability_sum << " ";
  else
    for(int i = 0; i < children_number; i++)
      children[i]->save_probability_sums_recursive(wfs);
}

void image_classification_node::load_probability_sums_recursive(std::ifstream& wfs) 
{
  if (is_leaf())
    wfs >> probability_sum;
  else
    for(int i = 0; i < children_number; i++)
      children[i]->load_probability_sums_recursive(wfs);
}

int image_classification_node::leaves_number(void)
{
  if (is_leaf())
    return 1;
  else
  {
    int n = 0;

    for(int i = 0; i < children_number; i++)
      n += children[i]->leaves_number();

    return n;
  }
}

int image_classification_node::node_number(void)
{
  if (is_leaf())
    return 0;
  else 
  {
    int n = 1;

    for(int i = 0; i < children_number; i++)
      n += children[i]->node_number();

    return n;
  }
}

void image_classification_node::set_Dot(int image_width, int image_height)
{
  int d;

  d = image_width / 2;

  du1 = int(d * rand_m1p1());
  dv1 = int(d * rand_m1p1());

  du2 = int(d * rand_m1p1());
  dv2 = int(d * rand_m1p1());

  int u0 = image_width / 2, v0 = image_height / 2;
  d1 = (v0 + dv1) * image_width + u0 + du1;
  d2 = (v0 + dv2) * image_width + u0 + du2;

  leaf = false;
}

void image_classification_node::set_Dot(int _du1, int _dv1, int _du2, int _dv2, int image_width, int image_height)
{
  du1 = _du1;
  dv1 = _dv1;
  du2 = _du2;
  dv2 = _dv2;

  int u0 = image_width / 2, v0 = image_height / 2;
  d1 = (v0 + dv1) * image_width + u0 + du1;
  d2 = (v0 + dv2) * image_width + u0 + du2;

  leaf = false;
}

ostream& operator<< (ostream& o, const image_classification_node& node)
{
  int i;

  if (node.is_leaf())
  {
    o << "LEAF " << node.index << " " << node.depth << endl;
    o << node.class_number << " classes" << endl;

    if (node.P != 0)
      for(i = 0; i < node.class_number; i++)
        if (node.P[i] > 0.001)
          o << i << " " << node.P[i] << endl;

    o << "-1 -1" << endl;
  }
  else
  {
    o << "NODE " << node.index << " " << node.depth << endl;
    o << "2dots_tau0" << endl; // Kept for compatibility with older versions
    o << 0 << " " << node.du1 << " " << node.dv1 << " " << node.du2 << " " << node.dv2 << endl;
    for(i = 0; i < node.children_number; i++)
      o << node.children[i]->index << " ";
    o << endl;
    for(i = 0; i < node.children_number; i++)
      o << *node.children[i];
  }

  return o;
}

//! TODO cleanme
int global_patch_size;

istream& operator>> (istream& is, image_classification_node& node)
{
  char dummyString[1000];
  char node_type[1000];

  is >> node_type;

  if (strcmp(node_type, "LEAF") == 0)
  {
    is >> node.index >> node.depth;
    is >> node.class_number >> dummyString ;
    node.P = new float[node.class_number];
    node.best_class = 0;
    float best_p = 0;
    for(int i = 0; i < node.class_number; i++)
      node.P[i] = 0;

    int ci;
    do
    {
      float p;
      is >> ci >> p;
      if (ci >= 0)
      {
        node.P[ci] = p;

        if (p > best_p)
        {
          best_p = p;
          node.best_class = ci;
        }
      }
    } while (ci >= 0);
  }
  else if (strcmp(node_type, "NODE") == 0)
  {
    int _scale, _du1, _dv1, _du2, _dv2;

    is >> node.index >> node.depth;

    is >> dummyString; // Always 2dots_tau0 : Kept for compatibily with older versions of garfield lib

    is >> _scale >> _du1 >> _dv1 >> _du2 >> _dv2;
    node.set_Dot(_du1, _dv1, _du2, _dv2, global_patch_size, global_patch_size);

    node.children_index = new int[node.children_number];

    for(int i = 0; i < node.children_number; i++)
      is >> node.children_index[i];
  }
  else
  {
    cerr << "Error while reading image_classification_node (token = " << node_type << ")." << endl;
    //throw exception("Error while reading image_classification_node"); //TODO A FAIRE
  }

  return is;
}

