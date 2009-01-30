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
#include <fstream>
#include <iomanip>
using namespace std;

#include <starter.h> 
#include "image_classification_forest.h"

image_classification_forest::image_classification_forest(LEARNPROGRESSION _LearnProgress) 
                                                         : image_classifier(_LearnProgress)
{
  weights=0;
}

image_classification_forest::image_classification_forest(int _image_width, int _image_height, int _class_number, 
                                                         int _max_depth, int _tree_number, 
                                                         LEARNPROGRESSION _LearnProgress) 
                                                         : image_classifier(_image_width, _image_height, _class_number,_LearnProgress)
{
  max_depth = _max_depth;
  tree_number = _tree_number;

  thresholds = misclassification_rates = 0;

  weights = new float[class_number];
  for(int i = 0; i < class_number; i++)
    weights[i] = 0;
}


bool image_classification_forest::load(string directory_name)
{
  int i = 0;
  bool ok;
  
  thresholds = misclassification_rates = 0;
  cout << "Reading Forest in " << directory_name << ":" << endl;

  // Read the trees:
  do
  {
    char tree_filename[1000];
    sprintf(tree_filename, "%s/tree%04d.txt", directory_name.data(), i);

    ifstream ifs(tree_filename);
    ok = ifs.is_open();
    if (ok)
    {
      cout << " Reading " << tree_filename << ": " << flush;

      image_classification_tree * tree = new image_classification_tree();
      
      if ( !tree->load(tree_filename) ) 
      {
        delete tree; 
        return false; 
      }

      trees.push_back(tree);
      i++;
    }
  } while(ok);
  if (trees.size() == 0 ) return false;

  image_width = (*trees.begin())->image_width;
  image_height = (*trees.begin())->image_height;
  class_number = (*trees.begin())->class_number;
  max_depth = (*trees.begin())->max_depth;

  // Read weight file:
  weights = new float[class_number];
  char weights_filename[1000];
  sprintf(weights_filename, "%s/weights.txt", directory_name.data());
  ifstream wfs(weights_filename);
  for(i = 0; i < class_number; i++)
    wfs >> weights[i];
  for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
    (*tree_it)->root->load_probability_sums_recursive(wfs);
  wfs.close();

  // Read threshold file:
  if (thresholds != 0)
    delete [] thresholds;
  thresholds = new float [class_number];

  char thresholds_filename[1000];
  sprintf(thresholds_filename, "%s/thresholds.txt", directory_name.data());
  ifstream tfs(thresholds_filename);
  for(i = 0; i < class_number; i++)
    tfs >> thresholds[i];
  tfs.close();

  // Read misclas rates file:
  if (misclassification_rates != 0)
    delete [] misclassification_rates;
  misclassification_rates = new float [class_number];

  char misclassification_rates_filename[1000];
  sprintf(misclassification_rates_filename, "%s/misclassification_rates.txt", directory_name.data());
  ifstream rfs(misclassification_rates_filename);
  if (rfs.good())
  {
    for(i = 0; i < class_number; i++)
      rfs >> misclassification_rates[i];
    rfs.close();
  }
  else
    for(i = 0; i < class_number; i++)
      misclassification_rates[i] = 0.42f;

  cout << "Done." << endl;

  return true;
}

image_classification_forest::~image_classification_forest()
{
  if (weights != 0) {
    delete [] weights;
    weights = 0;
  }

  for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
   delete (*tree_it);

  if (thresholds != 0)
    delete [] thresholds;

  if (misclassification_rates != 0)
    delete [] misclassification_rates;
}

void image_classification_forest::set_saving_directory_name(string _directory_name)
{
  directory_name = _directory_name;
}

void image_classification_forest::create_trees_at_random(void)
{
  for(int i = 0; i < tree_number; i++)
  {
    if (LearnProgression!=0) 
      LearnProgression(BUILDING_TREE, i, tree_number);

    cout << "FOREST: BUILDING TREE # " << i << endl;

    image_classification_tree * tree = new image_classification_tree(image_width, image_height, 
                                                                     class_number, max_depth);

    tree->root = new image_classification_node(0, class_number);
    tree->root->index = 0;

    vector <image_classification_node*> L;
    L.reserve(30);
    L.push_back(tree->root);

    int new_node_index = 1;

    while(!L.empty())
    {
      cout << "BUILDING RANDOM TREE: ~ " << new_node_index << " nodes.\r" << flush;

      image_classification_node * node = (image_classification_node *)L.back();
      L.pop_back();

      node->set_Dot(image_width, image_height);

      if (node->depth < max_depth - 2)
      {
        node->expand();

        for(int i = 0; i < node->children_number; i++)
          L.push_back(node->children[i]);
      }
      else
        node->end_recursion();

      for(int i = 0; i < node->children_number; i++)
      {
        node->children[i]->index = new_node_index;
        new_node_index++;
      }
    }

    cout << "Random tree built (" << tree->node_number() << " nodes)." << endl;

    trees.push_back(tree);
  }
}

// Refine the posterior probabilities stored in the leaves for each tree
void image_classification_forest::refine(example_generator * vg, int call_number)
{
  for(int i = 0; i < call_number; i++)
  {
    if (LearnProgression!=0) 
      LearnProgression(FOREST_REFINEMENT, i, call_number);

    cout << "FOREST REFINEMENT: " << call_number - i << "...    " << (char)13 << flush;

    vector<image_class_example *> * examples = vg->generate_random_examples();

    for(vector<image_class_example *>::iterator example_it = examples->begin(); example_it < examples->end(); example_it++) 
    {
      for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
      {
        image_classification_node * node = (*tree_it)->root;
        unsigned char * I = (unsigned char *)((*example_it)->preprocessed->imageData);

        while(!node->is_leaf()) 
        { 
          int dot_product = (int)I[node->d1] - (int)I[node->d2];

          if (dot_product <= 0) 
            node = node->children[0];
          else 
            node = node->children[1];
        }
        node->P[(*example_it)->class_index]++;
      }
      weights[(*example_it)->class_index]++;
    }

    delete examples;

    vg->release_examples();
  }

  cout << "Reweighted refinement: " << endl;

  for(int i = 0; i < class_number; i++)
    if (weights[i] == 0)
      weights[i] = 0;
    else
      weights[i] = 1 / weights[i];

  for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
    (*tree_it)->root->reestimate_probabilities_recursive(weights);

  cout << "Forest refinement done (" << call_number << " calls to generate_random_examples).            " << endl;
}

void image_classification_forest::restore_occurances()
{
  assert(weights);

  for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
    (*tree_it)->root->restore_occurances_recursive(weights);

  for(int i = 0; i < class_number; ++i)
    weights[i] = weights[i] > 0 ? 1 / weights[i] : 0.0f;
}

void image_classification_forest::reset_class_occurances(int class_index)
{
  for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
    (*tree_it)->root->reset_class_occurances_recursive(class_index);

  weights[class_index] = 0.0f;
}

void image_classification_forest::test(example_generator * vg, int call_number)
{
  int * inlier_total = new int[class_number];
  int * total = new int[class_number];

  int ** correct_samples   = new int*[class_number];
  int ** uncorrect_samples = new int*[class_number];

  const float step = 0.01f;
  int bin_number = int(1. / step);
  for(int i = 0; i < class_number; i++)
  {
    inlier_total[i] = total[i] = 0;
    
    correct_samples[i] = new int[bin_number];
    uncorrect_samples[i] = new int[bin_number];
    for(int j = 0; j < bin_number; j++)
      correct_samples[i][j] = uncorrect_samples[i][j] = 0;
  }

  for(int i = 0; i < call_number; i++)
  {
    if (LearnProgression!=0) 
      LearnProgression(GENERATING_TESTING_SET, i, call_number);
    
    cout << "GENERATING TESTING SET: " << call_number - i << "... " << (char)13 << flush;

    vector<image_class_example *> * examples = vg->generate_random_examples();

    for(vector<image_class_example *>::iterator it = examples->begin(); it < examples->end(); it++)
    {
      float score;
      int found_class_index = recognize(*it, &score);

      int bin_index = int(score / step);
      if (bin_index < 0) bin_index = 0;
      if (bin_index >= bin_number) bin_index = bin_number - 1;

      total[(*it)->class_index]++;
      if ((*it)->class_index == found_class_index)
      {
        inlier_total[found_class_index]++;
        correct_samples[found_class_index][bin_index]++;
      }
      else
        uncorrect_samples[found_class_index][bin_index]++;
    }

    delete examples;

    vg->release_examples();
  }

  // Estimate inlier rates and estimate thresholds:
  cout << "Testing: " << endl;
  cout << "Classification rate = [#p | Y(p) = c = Y^(p)] / [#p | Y(p) = c = Y^(p) or Y(p) != c = Y^(p)]" << endl;
  cout << "Ambiguity measure   = [#p | Y(p) = c != Y^(p)] / [#p | Y(p) = c = Y^(p)]" << endl;

  if (misclassification_rates != 0)
    delete [] misclassification_rates;
  misclassification_rates = new float [class_number];

  int T = 0, IT = 0;
  for(int i = 0; i < class_number; i++)
  {
    if (total[i] == 0)
      misclassification_rates[i] = 0.5;
    else
      misclassification_rates[i] = 1.f - float(inlier_total[i]) / total[i];

    T += total[i];
    IT += inlier_total[i];
  }

  float inlier_percentage = 100.f * float(IT) / T;

  if (thresholds != 0)
    delete [] thresholds;
  thresholds = new float [class_number];

  float desired_inlier_rate = 0.6f;
  float ambiguity_rate_mean = 0;
  for(int i = 0; i < class_number; i++)
  {
    cout << "CLASS " << setw(4) << i << ": ";
    int correct_number = 0, uncorrect_number = 0;
    int j;
    for(j = bin_number - 1; j >= 0; j--)
    {
      correct_number += correct_samples[i][j];
      uncorrect_number += uncorrect_samples[i][j];
      if (float(correct_number) / (correct_number + uncorrect_number) < desired_inlier_rate &&
          (correct_number + uncorrect_number) > 10)
        break;
    }
    thresholds[i] = j * step;
    cout << setw(5) << total[i] << " generated samples, ";
    cout << setw(4) << " T = " << setw(8) << thresholds[i] << ", ";
    cout << setw(6) << setprecision(3) << 100. * float(inlier_total[i]) / total[i] << "% inliers, " << flush;

    correct_number = 0; uncorrect_number = 0;
    for(int j = bin_number - 1; j >= 0; j--)
    {
      correct_number += correct_samples[i][j];
      uncorrect_number += uncorrect_samples[i][j];
    }
    if (correct_number != 0)
    {
      ambiguity_rate_mean += float(uncorrect_number) / correct_number;
      cout << "Ambig: " << setw(4) << setprecision(3) << float(uncorrect_number) / correct_number << endl;
    }
    else
    {
      ambiguity_rate_mean += 2.;
      cout << "Ambig: +oo" << endl;
    }
  }
  cout << "-------------------------------------------" << endl;
  cout << " GLOBAL ESTIMATION: " << setprecision(4) << inlier_percentage << "% inliers." << endl;
  ambiguity_rate_mean /= class_number;
  cout << "         E[Ambig] = " << ambiguity_rate_mean << endl;
  cout << "-------------------------------------------" << endl;

  // Clear allocated arrays:
  for(int i = 0; i < class_number; i++)
  {
    delete [] correct_samples[i];
    delete [] uncorrect_samples[i];
  }

  delete [] correct_samples;
  delete [] uncorrect_samples;

  delete [] total;
  delete [] inlier_total;
}

int image_classification_forest::recognize(image_class_example * pv, float * confidence, int tree_number)
{
  float * p = posterior_probabilities(pv, tree_number);
  int best_class = 0;
  float best_p = p[best_class];

  for(int i = 1; i < class_number; i++)
    if (p[i] > best_p)
    {
      best_p = p[i];
      best_class = i;
    }

  delete [] p;

  if (confidence != 0)
    *confidence = best_p;

  return best_class;
}

float * image_classification_forest::posterior_probabilities(image_class_example * pv, int tree_number)
{
  float * p = new float[class_number];

  posterior_probabilities(pv, p, tree_number);

  return p;
}

void image_classification_forest::posterior_probabilities(image_class_example * pv, float * p, int tree_number)
{
  if (tree_number < 0)
  {
    for(int i = 0; i < class_number; i++)
      p[i] = 0.;

    for(vector<image_classification_tree *>::iterator tree_it = trees.begin();
        tree_it < trees.end(); 
        tree_it++)
    {
      float * tree_p = (*tree_it)->posterior_probabilities(pv);

      for(int i = 0; i < class_number; i++)
        p[i] += tree_p[i];
    }

    float inv_tree_number = 1.f / trees.size();
    for(int i = 0; i < class_number; i++)
      p[i] *= inv_tree_number;
  }
  else 
  {
    for(int i = 0; i < class_number; i++)
      p[i] = 0.;

    int n = 0;
    if (tree_number < 0)
      tree_number = trees.size();

    for(vector<image_classification_tree *>::iterator tree_it = trees.begin();
      tree_it < trees.end(); 
      tree_it++)
    {
      float * tree_p = (*tree_it)->posterior_probabilities(pv);

      for(int i = 0; i < class_number; i++)
        p[i] += tree_p[i];

      n++;
      if (n > tree_number) break;
    }

    float inv_class_number = 1.f / tree_number;
    for(int i = 0; i < class_number; i++)
      p[i] *= inv_class_number;
  }
}

void image_classification_forest::change_class_number_and_reset_probabilities(int new_class_number)
{
  class_number = new_class_number;

  if(weights != 0) {
    delete [] weights;
    weights = 0;
  }
  weights = new float[class_number];
  for(int i = 0; i < class_number; i++)
    weights[i] = 0;

  for(vector<image_classification_tree *>::iterator tree_it = trees.begin();
      tree_it < trees.end(); 
      tree_it++) 
  {
    (*tree_it)->change_class_number_and_reset_probabilities(new_class_number);
  }
}

bool image_classification_forest::save(string directory_name)
{
  int tree_index = 0;

  for(vector<image_classification_tree *>::iterator tree_it = trees.begin();
      tree_it < trees.end(); 
      tree_it++)
  {
    char tree_name[1000];

    sprintf(tree_name, "%s/tree%04d.txt", directory_name.data(), tree_index);

    (*tree_it)->save(tree_name);

    tree_index++;
  }

  // Save thresholds:
  char thresholds_filename[1000];
  sprintf(thresholds_filename, "%s/thresholds.txt", directory_name.data());
  ofstream tfs(thresholds_filename);
  if (!tfs.good()) return false;
  tfs << setw(12) << setprecision(12);
  for(int i = 0; i < class_number; i++)
    tfs << thresholds[i] << endl;
  tfs.close();

  // Save misclassification rates:
  char misclassification_rates_filename[1000];
  sprintf(misclassification_rates_filename, "%s/misclassification_rates.txt", directory_name.data());
  ofstream rfs(misclassification_rates_filename);
  for(int i = 0; i < class_number; i++)
    rfs << misclassification_rates[i] << endl;
  rfs.close();

  // Save weights and probability_sum's.
  char weights_filename[1000];
  sprintf(weights_filename, "%s/weights.txt", directory_name.data());
  ofstream wfs(weights_filename);
  for(int i = 0; i < class_number; i++)
    wfs << weights[i] << endl;
  for(vector<image_classification_tree *>::iterator tree_it = trees.begin(); tree_it < trees.end(); tree_it++)
  {
    (*tree_it)->root->save_probability_sums_recursive(wfs);
    wfs << endl;
  }
  wfs.close();
  

  return true;
}

