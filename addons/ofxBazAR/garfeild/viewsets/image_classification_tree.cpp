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
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "image_classification_tree.h"

#ifdef WIN32
#else
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#endif

//! return memory usage, in kb
int used_memory() {
#ifdef WIN32
  return 42;
#else
  FILE *f;
  int mem;
  char fn[512];
  sprintf(fn, "/proc/%d/statm", getpid());
  f = fopen(fn, "r");
  fscanf(f, "%d", &mem);
  fclose(f);
  return (mem*4)/1024;
#endif
}

image_classification_tree::image_classification_tree(LEARNPROGRESSION _LearnProgress) 
                                                     : image_classifier(_LearnProgress)
{
  root = 0;
}


image_classification_tree::image_classification_tree(int _image_width, int _image_height, 
                                                     int _class_number, int _max_depth, 
                                                     LEARNPROGRESSION _LearnProgress) 
                                                     : image_classifier(_image_width, _image_height, _class_number,_LearnProgress)
{
  max_depth = _max_depth;

  root = 0;
}

bool image_classification_tree::load(string filename)
{
  string dummyString;

  try {
    ifstream ifs(filename.data());

    ifs >> dummyString >> image_width >> image_height;
    global_patch_size = image_width;
    cout << "[Patch size: " << global_patch_size << "]" << flush;

    ifs >> dummyString >> class_number;
    ifs >> dummyString >> max_depth;

    // Read nodes in an iterative way (faster than in a recursive way):
    int nodes_plus_leaves_number;
    ifs >> nodes_plus_leaves_number;

    image_classification_node ** nodes = new image_classification_node* [nodes_plus_leaves_number];

    try
    {
      for(int i = 0; i < nodes_plus_leaves_number; i++)
      {
        image_classification_node * tmp_node = new image_classification_node();
        ifs >> *tmp_node;
        nodes[tmp_node->index] = tmp_node;
      }
    }
    catch (exception)
    {
      delete [] nodes;
      return false;
    }

    // Rebuild the tree:
    root = nodes[0];
    for(int i = 0; i < nodes_plus_leaves_number; i++)
    {
      image_classification_node * node = nodes[i];

      if ( !node->is_leaf() )
      {
        assert(node->children_number <= 3);

        for(int i = 0; i < node->children_number; i++)
        {
          node->children[i] = nodes[node->children_index[i]];
          node->children[i]->parent = node;
        }
        delete [] node->children_index;
      }
    }

    delete [] nodes;

  }
  catch (exception)
  {
    return false;
  }

  cout << ". Ok." << endl;

  return true;
}

image_classification_tree::~image_classification_tree()
{
  if (root != 0)
    delete root;
}

bool image_classification_tree::save(string filename)
{
  cout << "Saving tree (" << filename << ")..." << flush;

  ofstream ofs(filename.data());

  ofs << "image_size: " << image_width << " " << image_height << endl;
  ofs << "class_number: " << class_number << endl;
  ofs << "max_depth:  " << max_depth << endl;

  ofs << node_number() + leaves_number() << endl;

  ofs << *root;

  ofs.close();

  cout << "...ok." << endl;

  return true;
}

void image_classification_tree::refine(example_generator * vg, int call_number)
{
  for(int i = 0; i < call_number; i++)
  {
    cout << "REFINEMENT: " << call_number - i << "...    \r" << flush;

    vector<image_class_example *> * examples = vg->generate_random_examples();

    for(vector<image_class_example *>::iterator it = examples->begin(); it < examples->end(); it++)
    {
      image_classification_node * node = root;

      while(!node->is_leaf()) 
        node = node->children[node->child_index(*it)];
      
      node->P[(*it)->class_index]++;
    }

    delete examples;

    vg->release_examples();
  }

  root->reestimate_probabilities_recursive();

  cout << "Refinement done (" << call_number << " calls to generate_random_examples).            " << endl;
}

void image_classification_tree::test(example_generator * vg, int call_number)
{
  int * inlier_total = new int[class_number];
  int * total = new int[class_number];

  for(int i = 0; i < class_number; i++)
    inlier_total[i] = total[i] = 0;

  for(int i = 0; i < call_number; i++)
  {
    cout << "GENERATING TESTING SET: " << call_number - i << "...    " << (char)13 << flush;

    vector<image_class_example *> * examples = vg->generate_random_examples();

    for(vector<image_class_example *>::iterator it = examples->begin(); it < examples->end(); it++)
    {
      int found_class_index = recognize(*it, 0);

      total[(*it)->class_index]++;
      if ((*it)->class_index == found_class_index)
        inlier_total[found_class_index]++;
    }

    delete examples;

    vg->release_examples();
  }

  cout << "Test: " << flush;
  for(int i = 0; i < class_number; i++)
  {
    cout << "[class " << i << ": ";
    if (total[i] == 0)
      cout << "not represented !!!]." << flush;
    else
      cout << std::setprecision(1) << 100. * float(inlier_total[i]) / total[i] << "% inliers]." << flush;
  }
  
  int T = 0, IT = 0;
  for(int i = 0; i < class_number; i++)
  {
    T += total[i];
    IT += inlier_total[i];
  }

  cout << "ok) -> " << setprecision(1) << 100. * float(IT) / T << "% inliers." << endl;
}


int image_classification_tree::recognize(image_class_example * image, float * confidence, int /*dummy*/)
{
  image_classification_node * node = root;

  while(!node->is_leaf()) 
    node = node->children[node->child_index(image)];

  if (confidence != 0)
    *confidence = node->P[node->best_class];

  return node->best_class;
}

float * image_classification_tree::posterior_probabilities(image_class_example * pv, int /*dummy*/)
{
  image_classification_node * node = root;
  unsigned char * I = (unsigned char *)(pv->preprocessed->imageData);

  while(!node->is_leaf())
  {
    int dot_product = (int)I[node->d1] - (int)I[node->d2];

    if (dot_product <= 0) 
      node = node->children[0];
    else 
      node = node->children[1];
  }
  return node->P;
}

int image_classification_tree::node_number(void)
{
  return root->node_number();
}

int image_classification_tree::leaves_number(void)
{
  return root->leaves_number();
}

int image_classification_tree::actual_max_depth(void)
{
  return 0;
}

double image_classification_tree::entropy(void)
{
  return 0.;
}

image_classification_node * image_classification_tree::extract_node(vector <image_classification_node*> * L)
{
  image_classification_node * result = (image_classification_node *)L->back();
  L->pop_back();

  return result;
}

void image_classification_tree::change_class_number_and_reset_probabilities(int new_class_number)
{
  root->change_class_number_and_reset_probabilities(new_class_number);
}

