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
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <starter.h>
#include "affine_image_generator.h"

using namespace std;

// Used for randomizing precomputed white noise
static const int prime = 307189;

affine_image_generator::affine_image_generator(void)
{
  original_image = 0;
  processed_original_image = 0;
  affine_image = 0;
  smoothed_generated_object_view = 0;
  orientation_corrector = 0;

  white_noise = new char[prime];
  limited_white_noise = new char[prime];

  set_default_values();

  local_keypoint_array = new object_keypoint[affine_image_generator::max_point_number];
}

affine_image_generator::~affine_image_generator(void)
{
  if (original_image != 0)
    cvReleaseImage(&original_image);
  if (processed_original_image != 0)
    cvReleaseImage(&processed_original_image);
  if (affine_image != 0)
    cvReleaseImage(&affine_image);
  if (smoothed_generated_object_view != 0)
    delete smoothed_generated_object_view;
  if (orientation_corrector != 0)
    delete orientation_corrector;
  delete[] local_keypoint_array;

  if (white_noise) delete[] white_noise;
  if (limited_white_noise) delete[] limited_white_noise;
}

void affine_image_generator::set_default_values(void)
{
  localization_noise = 0;

  set_noise_level(20);

  set_range_variation_for_theta(0, float(2.*3.1416));
  set_range_variation_for_phi(0, 3.1516f);
  independent_scaling(0.5, 1.5, 0.5, 1.5);
  //  constrained_scaling(0.7, 1.7, 0.9, 1.1);

  set_use_orientation_correction(true);

  set_use_random_background(false);

  set_patch_size(32);
  set_level_number(3);
  set_gaussian_smoothing_kernel_size(3);

  set_add_gaussian_smoothing(false);
  set_change_intensities(false);
}

void affine_image_generator::set_noise_level(int noise_level)
{
  this->noise_level = noise_level;

  index_white_noise = 0;
  for(int i = 0; i < prime; i++)
  {
    limited_white_noise[i] = char(rand() % (2 * noise_level) - noise_level);
    white_noise[i] = char(rand() % 256);
  }
}

void affine_image_generator::set_original_image(IplImage * p_original_image,
                                                int _u_corner1, int _v_corner1, int _u_corner2, int _v_corner2, 
                                                int _u_corner3, int _v_corner3, int _u_corner4, int _v_corner4,
                                                int affine_image_width, int affine_image_height)
{
  if (original_image != 0)
    cvReleaseImage(&original_image);
  original_image = cvCloneImage(p_original_image);

  if (processed_original_image != 0)
    cvReleaseImage(&processed_original_image);
  processed_original_image = cvCloneImage(p_original_image);

  if (affine_image != 0)
    cvReleaseImage(&affine_image);
  if (affine_image_width < 0)
    affine_image = cvCloneImage(p_original_image);
  else
    affine_image = cvCreateImage(cvSize(affine_image_width, affine_image_height), IPL_DEPTH_8U, 1);

  if (smoothed_generated_object_view != 0)
    delete smoothed_generated_object_view;
  smoothed_generated_object_view = new object_view(original_image->width, original_image->height, level_number);

  if (orientation_corrector != 0)
    delete orientation_corrector;
  orientation_corrector = new keypoint_orientation_corrector(original_image->width, original_image->height,
                                                             patch_size, level_number);

  set_roi(_u_corner1, _v_corner1, 
          _u_corner2, _v_corner2, 
          _u_corner3, _v_corner3, 
          _u_corner4, _v_corner4);
}

void affine_image_generator::set_preprocessed_image(IplImage *preprocessed)
{

  if (original_image != 0)
    cvReleaseImage(&original_image);
  original_image = cvCloneImage(preprocessed);

  if (processed_original_image != 0)
    cvReleaseImage(&processed_original_image);
  processed_original_image = cvCloneImage(preprocessed);

  if (affine_image != 0)
    cvReleaseImage(&affine_image);
  affine_image = cvCloneImage(preprocessed);

  if (smoothed_generated_object_view != 0)
    delete smoothed_generated_object_view;
  smoothed_generated_object_view = new object_view(preprocessed->width, preprocessed->height, level_number);

  if (orientation_corrector != 0)
    delete orientation_corrector;
  orientation_corrector = new keypoint_orientation_corrector(preprocessed->width, preprocessed->height,
    patch_size, level_number);

  u_corner1 = 0;                        v_corner1 = 0;
  u_corner2 = preprocessed->width - 1;  v_corner2 = 0;
  u_corner3 = preprocessed->width - 1;  v_corner3 = preprocessed->height - 1;
  u_corner4 = 0;                        v_corner4 = preprocessed->height - 1;
}

void affine_image_generator::set_object_keypoints(object_keypoint * keypoint_array, int p_point_number)
{
  used_keypoint_array = keypoint_array;
  point_number = p_point_number;
}

void affine_image_generator::reset_keypoints(void)
{
  used_keypoint_array = local_keypoint_array;
  point_number = 0;
}

void affine_image_generator::add_keypoint(float u, float v, int scale, int class_index)
{
  assert((unsigned)point_number < 1000);

  local_keypoint_array[point_number].M[0] = u;
  local_keypoint_array[point_number].M[1] = v;
  local_keypoint_array[point_number].scale = float(scale);
  local_keypoint_array[point_number].class_index = class_index;
  point_number++;
}

void affine_image_generator::set_level_number(int p_level_number) 
{
  level_number = p_level_number; 

  if (affine_image != 0)
  {
    if (orientation_corrector != 0)
      delete orientation_corrector;
    orientation_corrector = new keypoint_orientation_corrector(affine_image->width, affine_image->height,
      patch_size, level_number);

    if (smoothed_generated_object_view != 0)
      delete smoothed_generated_object_view;
    smoothed_generated_object_view = new object_view(affine_image->width, affine_image->height, level_number);
  }
}

void affine_image_generator::set_patch_size(int p_patch_size)
{
  patch_size = p_patch_size; 

  if (original_image != 0)
  {
    if (orientation_corrector != 0)
      delete orientation_corrector;

    orientation_corrector = new keypoint_orientation_corrector(affine_image->width, affine_image->height,
                                                               patch_size, level_number);
  }
}

void affine_image_generator::set_roi(int _u_corner1, int _v_corner1, 
                                     int _u_corner2, int _v_corner2, 
                                     int _u_corner3, int _v_corner3, 
                                     int _u_corner4, int _v_corner4)
{
  if (_u_corner1 >= 0)
  {
    u_corner1 = _u_corner1;  v_corner1 = _v_corner1;
    u_corner2 = _u_corner2;  v_corner2 = _v_corner2;
    u_corner3 = _u_corner3;  v_corner3 = _v_corner3;
    u_corner4 = _u_corner4;  v_corner4 = _v_corner4;
  }
  else
  {
    u_corner1 = 0;                          v_corner1 = 0;
    u_corner2 = original_image->width - 1;  v_corner2 = 0;
    u_corner3 = original_image->width - 1;  v_corner3 = original_image->height - 1;
    u_corner4 = 0;                          v_corner4 = original_image->height - 1;
  }

  cvSmooth(original_image, processed_original_image, CV_MEDIAN, 3, 3);
  for(int j = 0; j < processed_original_image->height; j++)
  {
    unsigned char * row = mcvRow(processed_original_image, j, unsigned char);
    for(int i = 0; i < processed_original_image->width; i++)
      if (i <= u_corner1 || i <= u_corner4 || i >= u_corner2 || i >= u_corner3 ||
          j <= v_corner1 || j <= v_corner2 || j >= v_corner3 || j >= v_corner4)
        row[i] = 128;
      else
        if (row[i] == 128) row[i] = 127;
  }
}

static int min4(int a, int b, int c, int d) 
{
  return MIN(a, MIN(b, MIN(c,d)));
}

static int max4(int a, int b, int c, int d) 
{
  return MAX(a, MAX(b, MAX(c,d)));
}

static float min4(float a, float b, float c, float d) 
{
  return MIN(a, MIN(b, MIN(c,d)));
}

static float max4(float a, float b, float c, float d) 
{
  return MAX(a, MAX(b, MAX(c,d)));
}

bool affine_image_generator::inside_roi(int u, int v)
{
  int border_size = 2;

  if (u - border_size < min4(u_corner1, u_corner2, u_corner3, u_corner4)) return false;
  if (v - border_size < min4(v_corner1, v_corner2, v_corner3, v_corner4)) return false;
  if (u + border_size > max4(u_corner1, u_corner2, u_corner3, u_corner4)) return false;
  if (v + border_size > max4(v_corner1, v_corner2, v_corner3, v_corner4)) return false;

  return true;
}


//! Global rotation. Default = [0 : 2Pi]
void affine_image_generator::set_range_variation_for_theta(float p_min_theta, float p_max_theta)
{
  min_theta = p_min_theta;
  max_theta = p_max_theta;
}

//! Skew. Default = [0 : Pi]
void affine_image_generator::set_range_variation_for_phi(float p_min_phi, float p_max_phi)
{
  min_phi = p_min_phi;
  max_phi = p_max_phi;
}

//! Default method. Between 0.5 : 1.5 for both
void affine_image_generator::independent_scaling(float p_min_lambda1, float p_max_lambda1, 
                                                 float p_min_lambda2, float p_max_lambda2)
{
  scaling_method = 0;

  min_lambda1 = p_min_lambda1;
  max_lambda1 = p_max_lambda1;

  min_lambda2 = p_min_lambda2;
  max_lambda2 = p_max_lambda2;
}

//! Constrained scaling. Adds a constraint on the range of the product of l1 and l2.
void affine_image_generator::constrained_scaling(float p_min_lambda1, float p_max_lambda1, 
                                                 float p_min_lambda2, float p_max_lambda2,
                                                 float p_min_l1_l2,   float p_max_l1_l2)
{
  scaling_method = 1;

  min_lambda1 = p_min_lambda1;
  max_lambda1 = p_max_lambda1;

  min_lambda2 = p_min_lambda2;
  max_lambda2 = p_max_lambda2;

  min_l1_l2 = p_min_l1_l2;
  max_l1_l2 = p_max_l1_l2;
}


void affine_image_generator::generate_random_affine_transformation(void)
{
  float theta = min_theta + rand_01() * (max_theta - min_theta);
  float phi   = min_phi   + rand_01() * (max_phi - min_phi);
  float lambda1, lambda2;
  int image_width  = affine_image->width;
  int image_height = affine_image->height;

  if (scaling_method == 0)
  {
    lambda1 = min_lambda1 + rand_01() * (max_lambda1 - min_lambda1);
    lambda2 = min_lambda2 + rand_01() * (max_lambda2 - min_lambda2);
  }
  else
  {
    do
    {
      lambda1 = min_lambda1 + rand_01() * (max_lambda1 - min_lambda1);
      lambda2 = min_lambda2 + rand_01() * (max_lambda2 - min_lambda2);
    } while (lambda1 * lambda2 < min_l1_l2 || lambda1 * lambda2 > max_l1_l2);
  }

  mcvComputeAffineTransfo(a, 
                          image_width / 2, image_height / 2,
                          theta, phi, 
                          lambda1, lambda2, 
                          0, 0);
  int Tx, Ty;
  float nu0, nv0, nu1, nv1, nu2, nv2, nu3, nv3;

  affine_transformation(a, image_width, image_height, float(u_corner1), float(v_corner1), nu0, nv0);
  affine_transformation(a, image_width, image_height, float(u_corner2), float(v_corner2), nu1, nv1);
  affine_transformation(a, image_width, image_height, float(u_corner3), float(v_corner3), nu2, nv2);
  affine_transformation(a, image_width, image_height, float(u_corner4), float(v_corner4), nu3, nv3);

  // Moves two of the four corners on the borders of the image to maximize the visible part of the generated view:
  if (rand() % 2 == 0)
    Tx = - int(min4(nu0, nu1, nu2, nu3)) + patch_size;
  else
    Tx = image_width - int(max4(nu0, nu1, nu2, nu3)) - patch_size;

  if (rand() % 2 == 0)
    Ty = -int(min4(nv0, nv1, nv2, nv3)) + patch_size;
  else
    Ty = image_height - int(max4(nv0, nv1, nv2, nv3)) - patch_size;

  mcvComputeAffineTransfo(a, 
                          image_width / 2, image_height / 2,
                          theta, phi, 
                          lambda1, lambda2, 
                          float(Tx), float(Ty));
}

void affine_image_generator::generate_Id_affine_transformation(void)
{
  int image_width  = affine_image->width;
  int image_height = affine_image->height;

  mcvComputeAffineTransfo(a, 
                          image_width / 2, image_height / 2,
                          0, 0, 
                          1., 1., 
                          0, 0);
}

void affine_image_generator::affine_transformation(float p_a[6], int width, int height, 
                                                   float u, float v, 
                                                   float & nu, float & nv)
{
  float det = p_a[0] * p_a[4] - p_a[3] * p_a[1];

  nu = width  / 2 + 1.f / det * ( p_a[4] * (u - p_a[2]) - p_a[1] * (v - p_a[5]));
  nv = height / 2 + 1.f / det * (-p_a[3] * (u - p_a[2]) + p_a[0] * (v - p_a[5]));  
}

void affine_image_generator::inverse_affine_transformation(float p_a[6], int width, int height, 
                                                           float u, float v, 
                                                           float & nu, float & nv)
{
  nu = p_a[0] * (u - width  / 2) + p_a[1] * (v - height / 2) + p_a[2];
  nv = p_a[3] * (u - width  / 2) + p_a[4] * (v - height / 2) + p_a[5];
}

void affine_image_generator::affine_transformation(float u, float v, float & nu, float & nv)
{
  affine_transformation(a, affine_image->width, affine_image->height, u, v, nu, nv);
}

void affine_image_generator::inverse_affine_transformation(float u, float v, float & nu, float & nv)
{
  inverse_affine_transformation(a, affine_image->width, affine_image->height, u, v, nu, nv);
}

void affine_image_generator::preprocess_point_view(image_class_example * pv, object_view * ov)
{
  if (use_orientation_correction)
  {
    // Lowe orientation:
    int s = (int)pv->point2d->scale;

    pv->point2d->orientation_in_radians = 
      orientation_corrector->estimate_orientation_in_radians(ov->image[s],
      int(pv->point2d->u), int(pv->point2d->v), 
      ov->gradX[s], ov->gradY[s]);

    assert(pv->preprocessed);

    orientation_corrector->correct_orientationf(ov->image[s],
      pv->point2d->u, pv->point2d->v, 
      pv->preprocessed, 
      pv->point2d->orientation_in_radians, s);
  }
  else
  {
    int s = (int)pv->point2d->scale;
    assert(pv->preprocessed);
    mcvGetPatch(ov->image[s], pv->preprocessed, int(pv->point2d->u), int(pv->point2d->v));
  }
}

void affine_image_generator::add_white_noise(IplImage * image)
{
  for(int y = 0; y < image->height; y++)
  {
    unsigned char * line = (unsigned char *)(image->imageData + y * image->widthStep);

    for(int x = 0; x < image->width; x++)
    {
      int p = line[x];

      p += limited_white_noise[index_white_noise];

      if (p > 255) 
        p = 255;
      else if (p < 0)
        p = 0;

      line[x] = (unsigned char)p;

      index_white_noise++;
      if (index_white_noise >= prime) index_white_noise = 1 + rand() % 6;
    }
  }
}

void affine_image_generator::replace_by_noise(IplImage * image, int value)
{
  for(int y = 0; y < image->height; y++)
  {
    unsigned char * row = mcvRow(image, y, unsigned char);

    for(int x = 0; x < image->width; x++)
      if (int(row[x]) == value)
      {
        row[x] = white_noise[index_white_noise];
        index_white_noise++;
        if (index_white_noise >= prime) index_white_noise = 1 + rand() % 6;
      }
  }
}

void affine_image_generator::generate_affine_image(void)
{
  CvMat A = cvMat(2, 3, CV_32F, a);

  cvSet(affine_image, cvScalar(128));

#if 0
  cvGetQuadrangleSubPix(processed_original_image, affine_image, &A);
#else
  float w = -(affine_image->width-1)/2;
  float h = -(affine_image->height-1)/2;
  float sa[9];
  memcpy(sa,a,9*sizeof(float));
  a[2] += w*a[0] +h*a[1]; 
  a[5] += w*a[3] +h*a[4]; 
  cvWarpAffine(processed_original_image, affine_image, &A,CV_INTER_LINEAR+CV_WARP_INVERSE_MAP);
  memcpy(a,sa,9*sizeof(float));
#endif

  if (use_random_background)
    replace_by_noise(affine_image, 128);
  else
    mcvReplace(affine_image, 128, (int)128);

  if (add_gaussian_smoothing)
  {
    if (rand() % 3 == 0)
    {
      int aperture = 3 + 2 * (rand() % 3);
      cvSmooth(affine_image, affine_image, CV_GAUSSIAN, aperture, aperture);
    }

    if (change_intensities)
      cvCvtScale(affine_image, affine_image, rand(0.8f, 1.2f), rand(-10.f, 10.f));

    if (noise_level > 0)
      add_white_noise(affine_image);

    if (0)
    {
      static int n = 0;
      mcvSaveImage("affine%04d.bmp", n, affine_image);
      n++;
    }
  }
}

void affine_image_generator::generate_object_view(void)
{
  generate_affine_image();

  smoothed_generated_object_view->build(affine_image, gaussian_smoothing_kernel_size);
}

vector<image_class_example *> * affine_image_generator::generate_random_examples(void)
{
  generate_random_affine_transformation();
  generate_object_view();

  vector<image_class_example *> * result = new vector<image_class_example *>;

  for(int i = 0; i < point_number; i++)
  {
    object_keypoint * kp = &(used_keypoint_array[i]);
    int scale = int(kp->scale);
    IplImage * im = smoothed_generated_object_view->image[scale];
    float nu, nv;

    affine_transformation(PyrImage::convCoordf(float(kp->M[0]), scale, 0), 
                          PyrImage::convCoordf(float(kp->M[1]), scale, 0),
                          nu, nv);

    nu = PyrImage::convCoordf(nu, 0, scale) + localization_noise * rand_m1p1();
    nv = PyrImage::convCoordf(nv, 0, scale) + localization_noise * rand_m1p1();

    if ((int)nu > patch_size && (int)nu < im->width  - patch_size &&
        (int)nv > patch_size && (int)nv < im->height - patch_size)
    {
      image_class_example * pv = new image_class_example(kp->class_index, 
                                                         nu, nv, (float)scale, 
                                                         smoothed_generated_object_view, 
                                                         patch_size);
      pv->orig_u = float(kp->M[0]);
      pv->orig_v = float(kp->M[1]);

      preprocess_point_view(pv, smoothed_generated_object_view);

      result->push_back(pv);
      point_views.push_back(pv);
    }
  }

  return result;
}

void affine_image_generator::release_examples(void)
{
  for(vector<object_view *>::iterator ov_it = generated_object_views_for_learning.begin();
      ov_it < generated_object_views_for_learning.end();
      ov_it++)
  {
    delete *ov_it;
  }

  generated_object_views_for_learning.clear();

  for(vector<image_class_example *>::iterator pv_it = point_views.begin();
      pv_it < point_views.end();
      pv_it++)
  {
    delete *pv_it;
  }

  point_views.clear();
}
