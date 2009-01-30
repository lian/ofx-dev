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
#include <iostream>
#include <cmath>
using namespace std;

#include <starter.h>
#include "keypoint_orientation_corrector.h"

const short ACTUAL_MAX_GRADIENT = 1024;
const unsigned short GRADIENT_SHIFT = 2;
const short MAX_GRADIENT = ACTUAL_MAX_GRADIENT >> GRADIENT_SHIFT;

#define ATAN2_TABLE_INDEX(dx, dy) (((dy + MAX_GRADIENT) * (2 * MAX_GRADIENT + 1)) + (dx + MAX_GRADIENT))

const short MINIMAL_NORM = 0; // of the gradient to be taken into account

#define DERIVATIVES_KERNEL_SIZE 1

bool keypoint_orientation_corrector::subpixel_rotate = false;

keypoint_orientation_corrector::keypoint_orientation_corrector(int _width, int _height, int _neighborhood_size, int _nbLev)
{
  width = _width;
  height = _height;
  neighborhood_size = _neighborhood_size;
  nbLev = _nbLev;

  actual_neighborhood_size = neighborhood_size;

  angle_buckets = new int[ANGLE_BUCKET_NUMBER];

  initialize_tables();
}

void keypoint_orientation_corrector::initialize_tables(void)
{
  atan2_table = new short[(2 * MAX_GRADIENT + 1) * (2 * MAX_GRADIENT + 1)];

  for(int dy = -MAX_GRADIENT; dy <= +MAX_GRADIENT; dy++)
    for(int dx = -MAX_GRADIENT; dx <= +MAX_GRADIENT; dx++)
    {
      int index = ATAN2_TABLE_INDEX(dx, dy);
      float norm2 = float(dx * dx + dy * dy);
      if (norm2 > MINIMAL_NORM * MINIMAL_NORM)
      {
        float angle = atan2((float)dy, (float)dx);
        angle = (float) ((angle + 3.14159) * 180 / 3.14159);
        if (angle < 0) angle = 0;
        if (angle > 359) angle = 359;
        int result = int(angle / ANGLE_QUANTUM + 0.5);
        if (result < 0) result = 0;
        if (result >= ANGLE_BUCKET_NUMBER) result = ANGLE_BUCKET_NUMBER - 1;
        atan2_table[index] = (short)result;
      }
      else
        atan2_table[index] = -1; /////////////////////////////////////////////////////////////////////
    }

    orientation_lookup_tables = new int* [ANGLE_BUCKET_NUMBER*nbLev];

    // this image is used only to know widthStep for each level. TODO: cleanme.
    PyrImage im(cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1), nbLev);

    for(int i = 0; i < ANGLE_BUCKET_NUMBER*nbLev; i++)
    {
      int level = i / ANGLE_BUCKET_NUMBER;
      int angle = i % ANGLE_BUCKET_NUMBER;
      int size = neighborhood_size /*>> (level)*/;
      int * table = orientation_lookup_tables[i] = new int[size * size];
      float cs = float(cos(angle * 2 * 3.14159 / ANGLE_BUCKET_NUMBER));
      float sn = float(sin(angle * 2 * 3.14159 / ANGLE_BUCKET_NUMBER));
      float c = size / 2.f;
      for(int y = 0; y < size; y++)
        for(int x = 0; x < size; x++)
        {
          float dx = x - c;
          float dy = y - c;

          int nx = int(cs * dx - sn * dy + 0.5);
          int ny = int(sn * dx + cs * dy + 0.5);
          table[y * size + x] = int(ny * im[level]->widthStep + nx);
        }
    }

    exp_weights = cvCreateImage(cvSize(neighborhood_size, neighborhood_size), IPL_DEPTH_32S, 1);

    // should test ACTUAL_NEIGHBORHOOD_SIZE here (ie where the first non nul weight appears)
    bool actual_neighborhood_size_found = false;
    for(int y = 0; y < neighborhood_size; y++)
    {
      int * W = (int *)(exp_weights->imageData + y * exp_weights->widthStep);

      for(int x = 0; x < neighborhood_size; x++)
      {
        float d2 = float(gf_sqr(x - neighborhood_size / 2) + gf_sqr(y - neighborhood_size / 2));
        float sigma_d2 = 5;

        W[x] = int(100 * exp(-d2 / (2 * sigma_d2 * sigma_d2)));

        if (y == neighborhood_size / 2)
          if (x > neighborhood_size / 2 && !actual_neighborhood_size_found)
            if (W[x] == 0)
            {
              actual_neighborhood_size = 2 * (x - (neighborhood_size / 2));
              actual_neighborhood_size_found = true;
            }
      }
    }
}

keypoint_orientation_corrector::~keypoint_orientation_corrector()
{
  delete[] angle_buckets;

  for(int i = 0; i < ANGLE_BUCKET_NUMBER*nbLev; i++)
    delete[] orientation_lookup_tables[i];
  delete[] orientation_lookup_tables;
  if (atan2_table) delete[] atan2_table;
}

void keypoint_orientation_corrector::compute_gradient_images(IplImage * image, IplImage ** _Ix, IplImage ** _Iy)
{
  *_Ix = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_16S, 1);
  *_Iy = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_16S, 1);

  cvSobel(image, *_Ix, 1, 0, DERIVATIVES_KERNEL_SIZE);
  cvSobel(image, *_Iy, 0, 1, DERIVATIVES_KERNEL_SIZE);
}

int keypoint_orientation_corrector::orientation_bucket_index(const IplImage * _Ix, const IplImage * _Iy,
                                                             const int u, const int v)
{
  const int D = actual_neighborhood_size / 2;

  for(int i = 0; i < ANGLE_BUCKET_NUMBER; i++)
    angle_buckets[i] = 0;

  for(int y = -D; y < D; y++)
  {
    int dIx = (v + y) * _Ix->widthStep + (u << 1);
    short * Ix_row = (short*)(_Ix->imageData + dIx);
    short * Iy_row = (short*)(_Iy->imageData + dIx);
    int * W        = (int*)  (exp_weights->imageData + (D + y) * exp_weights->widthStep) + D;

    for(int x = -D; x < D; x++)
    {
      if (W[x] == 0) continue;

      int dx = Ix_row[x] >> GRADIENT_SHIFT;
      int dy = Iy_row[x] >> GRADIENT_SHIFT;
      int norm2 = dx * dx + dy * dy;

      if (dx <= -MAX_GRADIENT)      dx = -MAX_GRADIENT + 1;
      else if (dx >= MAX_GRADIENT)  dx =  MAX_GRADIENT - 1;
      if (dy <= -MAX_GRADIENT)      dy = -MAX_GRADIENT + 1;
      else if (dy >= MAX_GRADIENT)  dy =  MAX_GRADIENT - 1;

      int index = atan2_table[ATAN2_TABLE_INDEX(dx, dy)];
      assert(index <ANGLE_BUCKET_NUMBER);
      angle_buckets[index] += W[x] * norm2;
    }
  }

  // Here Lowe smoothes the angle_buckets histogram for a more robust estimation of the orientation
  // He also fits a parabola to refine the orientation. Not required in our method thanks to the classifier.

  int orientation_bucket_index = 0, value = angle_buckets[0];
  for(int i = 1; i < ANGLE_BUCKET_NUMBER; i++)
    if (angle_buckets[i] > value)
    {
      value = angle_buckets[i];
      orientation_bucket_index = i;
    }

    return orientation_bucket_index;
}

int keypoint_orientation_corrector::optimized_orientation_bucket_index(const IplImage * _Ix, const IplImage * _Iy,
                                                                       const int u, const int v)
{
  const int D = actual_neighborhood_size / 2;

  for(int i = 0; i < ANGLE_BUCKET_NUMBER; i++)
    angle_buckets[i] = 0;

  for(int y = -D; y < D; y++)
  {
    int dIx = (v + y) * _Ix->widthStep + (u << 1);
    short * Ix_row = (short*)(_Ix->imageData + dIx);
    short * Iy_row = (short*)(_Iy->imageData + dIx);
    int * W        = (int*)  (exp_weights->imageData + (D + y) * exp_weights->widthStep) + D;

    int dx = (y + D) & 1;

    for(int x = dx; x < D; x+=2)
    {
      if (W[x] == 0) break;

      int dx = Ix_row[x] >> GRADIENT_SHIFT;
      int dy = Iy_row[x] >> GRADIENT_SHIFT;
      int norm2 = dx * dx + dy * dy;

      if (dx <= -MAX_GRADIENT)      dx = -MAX_GRADIENT + 1;
      else if (dx >= MAX_GRADIENT)  dx =  MAX_GRADIENT - 1;
      if (dy <= -MAX_GRADIENT)      dy = -MAX_GRADIENT + 1;
      else if (dy >= MAX_GRADIENT)  dy =  MAX_GRADIENT - 1;

      short index = atan2_table[ATAN2_TABLE_INDEX(dx, dy)];
      angle_buckets[index] += W[x] * norm2;
    }

    for(int x = -2 + dx; x >= -D; x-=2)
    {
      if (W[x] == 0) break;

      int dx = Ix_row[x] >> GRADIENT_SHIFT;
      int dy = Iy_row[x] >> GRADIENT_SHIFT;
      int norm2 = dx * dx + dy * dy;

      if (dx <= -MAX_GRADIENT)     dx = -MAX_GRADIENT + 1;
      else if (dx >= MAX_GRADIENT) dx =  MAX_GRADIENT - 1;
      if (dy <= -MAX_GRADIENT)     dy = -MAX_GRADIENT + 1;
      else if (dy >= MAX_GRADIENT) dy =  MAX_GRADIENT - 1;

      short index = atan2_table[ATAN2_TABLE_INDEX(dx, dy)];
      angle_buckets[index] += W[x] * norm2;
    }
  }

  // Here Lowe smoothes the angle_buckets histogram for a more robust estimation of the orientation
  // He also fits a parabola to refine the orientation. Not required in our method thanks to the classifier.

  int orientation_bucket_index = 0, value = angle_buckets[0];
  for(int i = 1; i < ANGLE_BUCKET_NUMBER; i++)
    if (angle_buckets[i] > value)
    {
      value = angle_buckets[i];
      orientation_bucket_index = i;
    }

    return orientation_bucket_index;
}

void keypoint_orientation_corrector::rotate_patchf(IplImage * original_image, float u, float v, 
                                                   IplImage * rotated_patch,
                                                   float angle)
{
  static float m[6];
  static CvMat M = cvMat( 2, 3, CV_32F, m );

  m[0] = (float)(cos(-angle));
  m[1] = (float)(sin(-angle));
  m[2] = u;
  m[3] = -m[1];
  m[4] = m[0];
  m[5] = v;

  cvGetQuadrangleSubPix(original_image, rotated_patch, &M);
}

void keypoint_orientation_corrector::rotate_patch(IplImage * original_image, int u, int v, 
                                                  IplImage * rotated_patch,
                                                  int orientation_bucket_index, int level)
{
  if (original_image->depth == IPL_DEPTH_8U && rotated_patch->depth == IPL_DEPTH_8U)
  {
    int * table = orientation_lookup_tables[level * ANGLE_BUCKET_NUMBER + orientation_bucket_index];
    char * src = original_image->imageData;
    int offset = (int)v * original_image->widthStep + (int)u;
    unsigned max = (unsigned)original_image->widthStep*(original_image->height+1);
    char * dst = rotated_patch->imageData;

    const int length = neighborhood_size * neighborhood_size;
    for(int i = 0; i < length; i++) {
      unsigned idx = offset + table[i];
      if (idx < max)
        dst[i] = src[idx];
    }
  }
  else if (original_image->depth == (int)IPL_DEPTH_16S && rotated_patch->depth == (int)IPL_DEPTH_16S)
  {
    int * table = orientation_lookup_tables[level* ANGLE_BUCKET_NUMBER + orientation_bucket_index];
    short * src = (short*)(original_image->imageData + (int)v * original_image->widthStep) + (int)u;
    short * dst = (short*)(rotated_patch->imageData);

    const int length = neighborhood_size * neighborhood_size;
    for(int i = 0; i < length; i++)
      dst[i] = src[table[i]];
  }
  else
  {
    cerr << "keypoint_orientation_corrector::rotate_patch invalid depths" << endl;
    cerr << "depth 1 = " << original_image->depth << endl;
    cerr << "depth 2 = " << rotated_patch->depth << endl;
  }
}

float keypoint_orientation_corrector::estimate_orientation_in_radians(IplImage * image, int u, int v, 
                                                                      IplImage * _Ix, IplImage * _Iy)
{
  // Avoid a warning:
  image = 0;

  int _orientation_bucket_index = orientation_bucket_index(_Ix, _Iy, u, v);

  return _orientation_bucket_index * 2 * 3.14159f / ANGLE_BUCKET_NUMBER;
}

int keypoint_orientation_corrector::correct_orientation(IplImage * image, int u, int v, 
                                                        IplImage * rotated_neighborhood,
                                                        IplImage * _Ix, IplImage * _Iy, int level)
{
  int _orientation_bucket_index = orientation_bucket_index(_Ix, _Iy, u, v);

  rotate_patch(image, u, v, rotated_neighborhood, _orientation_bucket_index, level);

  return _orientation_bucket_index;
}

int keypoint_orientation_corrector::correct_orientationf(IplImage * image, float u, float v, 
                                                         IplImage * rotated_neighborhood, 
                                                         float orientation_in_radians, int level)
{
  if (subpixel_rotate)
    rotate_patchf(image, u, v, rotated_neighborhood, orientation_in_radians);
  else {
    int _orientation_bucket_index = int(orientation_in_radians * ANGLE_BUCKET_NUMBER / (2 * 3.14159));
    if (_orientation_bucket_index < 0) _orientation_bucket_index = 0;
    if (_orientation_bucket_index >= ANGLE_BUCKET_NUMBER) _orientation_bucket_index = ANGLE_BUCKET_NUMBER - 1;
    rotate_patch(image, (int)(u+.5f), (int)(v+.5f),  rotated_neighborhood, _orientation_bucket_index, level);
  }

  return 0;
}

