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
#ifndef AFFINE_IMAGE_GENERATOR_H
#define AFFINE_IMAGE_GENERATOR_H

#include <starter.h>
#include "../viewsets/object_view.h"
#include "../keypoints/keypoint_orientation_corrector.h"
#include "example_generator.h"


//! An affine image generator.
//! \ingroup viewsets
class affine_image_generator : public example_generator
{
  static const int max_point_number = 5000;
 public:
  affine_image_generator(void);
  virtual ~affine_image_generator(void);

  void set_original_image(IplImage * original_image,
                          int _u_corner1 = -1, int _v_corner1 = -1, int _u_corner2 = -1, int _v_corner2 = -1, 
                          int _u_corner3 = -1, int _v_corner3 = -1, int _u_corner4 = -1, int _v_corner4 = -1,
                          int affine_image_width = -1, int affine_image_height = -1);

  void set_preprocessed_image(IplImage *preprocessed);

  void set_object_keypoints(object_keypoint * keypoint_array, int point_number);

  void reset_keypoints(void);
  void add_keypoint(float u, float v, int scale, int class_index);
  
  void generate_affine_image(void);
  void generate_object_view(void);

  //! Default = 20
  void set_noise_level(int p_noise_level);
  //! Default = 3
  void set_level_number(int p_level_number);
  //! Default = 32
  void set_patch_size(int p_patch_size);
  //! Default = false;
  void set_use_random_background(bool p_use_random_background) { use_random_background = p_use_random_background; }
  //! Global rotation. Default = [0 : 2Pi]
  void set_range_variation_for_theta(float min_theta, float max_theta);
  //! Skew. Default = [0 : Pi]
  void set_range_variation_for_phi(float min_phi, float max_phi);
  //! Default method. Between 0.5 : 1.5 for both
  void independent_scaling(float min_lambda1, float max_lambda1, float min_lambda2, float max_lambda2);
  //! Constrained scaling. Adds a constraint on the range of the product of l1 and l2.
  void constrained_scaling(float min_lambda1, float max_lambda1, 
                           float min_lambda2, float max_lambda2,
                           float min_l1_l2, float max_l1_l2);
  //! Default true.
  void set_use_orientation_correction(bool p_use_orientation_correction) 
  { use_orientation_correction = p_use_orientation_correction; }
  //! Default false.
  void set_add_gaussian_smoothing(bool p_add_gaussian_smoothing)
  { add_gaussian_smoothing = p_add_gaussian_smoothing; }
  //! Default false.
  void set_change_intensities(bool p_change_intensities)
  { change_intensities = p_change_intensities; }

  void set_gaussian_smoothing_kernel_size(int p_gaussian_smoothing_kernel_size) 
  { gaussian_smoothing_kernel_size = p_gaussian_smoothing_kernel_size; }

  void generate_random_affine_transformation(void);
  void generate_Id_affine_transformation(void);

  void set_roi(int _u_corner1, int _v_corner1, 
               int _u_corner2, int _v_corner2, 
               int _u_corner3, int _v_corner3, 
               int _u_corner4, int _v_corner4);
  bool inside_roi(int u, int v);
  void set_default_values(void);

  vector<image_class_example *> * generate_random_examples(void);
  void release_examples(void);

  void affine_transformation(float u, float v, float & nu, float & nv);
  void inverse_affine_transformation(float u, float v, float & nu, float & nv);

  static void affine_transformation(float a[6], int width, int height, float u, float v, float & nu, float & nv);
  static void inverse_affine_transformation(float a[6], int width, int height, float u, float v, float & nu, float & nv);

  void preprocess_point_view(image_class_example * pv, object_view * ov);

  void add_white_noise(IplImage * image);
  void replace_by_noise(IplImage * image, int value);
  char *white_noise, *limited_white_noise;
  int index_white_noise;

  IplImage * original_image, * processed_original_image;
  IplImage * affine_image;
  float a[6];

  object_view * smoothed_generated_object_view;
  vector<object_view *> generated_object_views_for_learning;
  vector<image_class_example *> point_views;

  object_keypoint * used_keypoint_array;
  object_keypoint * local_keypoint_array;
  int point_number;

  keypoint_orientation_corrector * orientation_corrector;

  bool use_orientation_correction;
  bool use_random_background;
  bool add_gaussian_smoothing;
  bool change_intensities;

  int noise_level;
  int gaussian_smoothing_kernel_size;
  int patch_size, level_number;
  float localization_noise;

  float min_theta, max_theta;
  float min_phi, max_phi;
  int scaling_method;
  float min_lambda1, max_lambda1;
  float min_lambda2, max_lambda2; // for scaling method 0
  float min_l1_l2, max_l1_l2;     // for scaling method 1

  int u_corner1, v_corner1, u_corner2, v_corner2, u_corner3, v_corner3, u_corner4, v_corner4;
};

#endif // AFFINE_IMAGE_GENERATOR_H
