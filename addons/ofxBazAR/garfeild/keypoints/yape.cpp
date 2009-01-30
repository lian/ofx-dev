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
/*
* Author:
* Vincent Lepetit <vincent.lepetit@epfl.ch>
* 2004/2005
*/

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

#include <stdlib.h>
#include <math.h>

#include "starter.h"
#include "yape.h"

const unsigned int yape_bin_size = 1000;
const int yape_tmp_points_array_size = 10000;

bool operator <(const keypoint &p1, const keypoint &p2)
{
  return p1.score > p2.score;
}

yape::yape(int _width, int _height)
{
  width = _width;
  height = _height;

  radius = 7;
  tau = 10;
  minimal_neighbor_number = 4;

  activate_bins();
  set_bins_number(4, 4);

  disactivate_subpixel();

  set_minimal_neighbor_number(3);

  init_for_monoscale();
}

yape::~yape()
{
  if (Dirs) delete Dirs;
  if (Dirs_nb) delete[] Dirs_nb;
  if (scores) cvReleaseImage(&scores);
  if (filtered_image) cvReleaseImage(&filtered_image);
}

int yape::static_detect(IplImage * image, keypoint * points, int max_point_number, int _radius, int _tau)
{
  yape * pe = new yape(image->width, image->height);

  pe->set_radius(_radius);
  pe->set_tau(_tau);
  int point_number = pe->detect(image, points, max_point_number);

  delete pe;

  return point_number;
}

void yape::set_radius(int _radius)
{
  radius = _radius;
}

void yape::set_tau(int _tau)
{
  tau = _tau;
}

void yape::init_for_monoscale(void)
{
  scores = cvCreateImage(cvSize(width, height), IPL_DEPTH_16S, 1);
  filtered_image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

  Dirs = new dir_table;
  memset(Dirs,0,sizeof(dir_table));
  Dirs_nb = new int[yape_max_radius];
  memset(Dirs_nb,0,sizeof(int)*yape_max_radius);
  for(int R = 1; R < yape_max_radius; R++)
    precompute_directions(filtered_image, Dirs->t[R], &(Dirs_nb[R]), R);
}

void yape::reserve_tmp_arrays(void)
{
  if (use_bins)
    for(int i = 0; i < bin_nb_u; i++)
      for(int j = 0; j < bin_nb_v; j++)
      {
        bins[i][j].clear();
        bins[i][j].reserve(yape_bin_size); 
      }
  else
  {
    tmp_points.clear();
    tmp_points.reserve(yape_tmp_points_array_size);
  }
}

void yape::precompute_directions(IplImage * image, short * _Dirs, int * _Dirs_nb, int R)
{
  int widthStep = image->widthStep;

  int i = 0;
  int x, y;

  x = R;
  for(y = 0; y < x; y++, i++)
  {
    x = int(sqrt(double(R * R - y * y)) + 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for(x-- ; x < y && x >= 0; x--, i++)
  {
    y = int(sqrt(double(R * R - x * x)) + 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for( ; -x < y; x--, i++)
  {
    y = int(sqrt(double(R * R - x * x)) + 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for(y-- ; y >= 0; y--, i++)
  {
    x = int(-sqrt(double(R * R - y * y)) - 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for(; y > x; y--, i++)
  {
    x = int(-sqrt(double(R * R - y * y)) - 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for(x++ ; x <= 0; x++, i++)
  {
    y = int(-sqrt(double(R * R - x * x)) - 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for( ; x < -y; x++, i++)
  {
    y = int(-sqrt(double(R * R - x * x)) - 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }
  for(y++ ; y < 0; y++, i++)
  {
    x = int(sqrt(double(R * R - y * y)) + 0.5);
    _Dirs[i] = short(x + widthStep * y);
  }

  *_Dirs_nb = i;
  _Dirs[i] = _Dirs[0];
  _Dirs[i + 1] = _Dirs[1];
}

void yape::save_image_of_detected_points(char * name, IplImage * image, keypoint * points, int points_nb)
{
  IplImage * color_image = mcvGrayToColor(image);

  for(int i = 0; i < points_nb; i++) {
    int s = (int)points[i].scale;
    float x = PyrImage::convCoordf(points[i].u, s, 0);
    float y = PyrImage::convCoordf(points[i].v, s, 0);
    float l = PyrImage::convCoordf(32.0f, s, 0);

    mcvCircle(color_image, int(x), int(y), (int)l, mcvRainbowColor(s % 7));
  }

  mcvSaveImage(name, color_image);
}

bool yape::double_check(IplImage * image, int x, int y, short * dirs, unsigned char dirs_nb)
{
  unsigned char * I = (unsigned char *)(image->imageData + y * image->widthStep);
  int Ip = I[x] + tau;
  int Im = I[x] - tau;
  int A;

  for(A = dirs_nb / 2 - 2; A <= dirs_nb / 2 + 2; A++)
    for(int i = 0; i < dirs_nb - A; i++)
    {
      if (I[x+dirs[i]] > Im && I[x+dirs[i]] < Ip && I[x+dirs[i+A]] > Im && I[x+dirs[i+A]] < Ip)
        return false;
    }

    return true;
}

#define A_INF (A < Im)
#define A_SUP (A > Ip)
#define A_NOT_INF (A >= Im)
#define A_NOT_SUP (A <= Ip)

#define B0_INF (B_0 < Im)
#define B0_SUP (B_0 > Ip)
#define B0_NOT_INF (B_0 >= Im)
#define B0_NOT_SUP (B_0 <= Ip)

#define B1_INF (B1 < Im)
#define B1_SUP (B1 > Ip)
#define B1_NOT_INF (B1 >= Im)
#define B1_NOT_SUP (B1 <= Ip)

#define B2_INF (B2 < Im)
#define B2_SUP (B2 > Ip)
#define B2_NOT_INF (B2 >= Im)
#define B2_NOT_SUP (B2 <= Ip)

#define GET_A()   A = I[x+dirs[a]]
#define GET_B0()  B_0 = I[x+dirs[b]]
#define GET_B1()  b++; B1 = I[x+dirs[b]]
#define GET_B2()  b++; B2 = I[x+dirs[b]]

#define GOTO_STATE(s)    { score -= A + B1; state = (s); break; }
#define GOTO_END_NOT_AN_INTEREST_POINT { /*stats_iter[a]++;*/ Scores[x] = 0; return; }
#define PUT_B2_IN_B1_AND_GET_B2()  B1 = B2; GET_B2()

#define B1_NOT_INF_B2_NOT_INF  0
#define B1_NOT_SUP_B2_NOT_SUP  1
#define B1_INF_B2_INF          2
#define B1_SUP_B2_SUP          3
#define B1_INF_B2_NOT_SUP      4
#define B1_SUP_B2_NOT_INF      5
#define B1_SUP_B2_INF          6
#define B1_INF_B2_SUP          7
#define B1_EQUAL_B2_NOT_SUP    8
#define B1_EQUAL_B2_NOT_INF    9

void yape::perform_one_point(const unsigned char * I, const int x, short * Scores,
                             const int Im, const int Ip, 
                             const short * dirs, const unsigned char opposite, const unsigned char dirs_nb)
{
  int score = 0;
  unsigned char a = 0, b = opposite - 1;
  int A, B_0, B1, B2;

  unsigned char state;

  // WE KNOW THAT NOT(A ~ I0 & B1 ~ I0):
  GET_A();
  if (A_NOT_SUP) {
    if (A_NOT_INF) { // A ~ I0
      GET_B0();
      if (B0_NOT_SUP) {
        if (B0_NOT_INF) GOTO_END_NOT_AN_INTEREST_POINT
        else {
          GET_B1();
          if (B1_SUP) {
            GET_B2();
            if (B2_SUP) state = B1_SUP_B2_SUP;
            else if (B2_INF) state = B1_SUP_B2_INF;
            else GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0
          }
          else/* if (B1_INF)*/ {
            GET_B2();
            if (B2_SUP) state = B1_INF_B2_SUP;
            else if (B2_INF) state = B1_INF_B2_INF;
            else GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0
          }
          //else GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B1 ~ I0
        }
      }
      else { // B0 < I0
        GET_B1();
        if (B1_SUP) {
          GET_B2();
          if (B2_SUP) state = B1_SUP_B2_SUP;
          else if (B2_INF) state = B1_SUP_B2_INF;
          else GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0
        }
        else if (B1_INF) {
          GET_B2();
          if (B2_SUP) state = B1_INF_B2_SUP;
          else if (B2_INF) state = B1_INF_B2_INF;
          else GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0
        }
        else GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B1 ~ I0
      }
    }
    else { // A > I0
      GET_B0();
      if (B0_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        GET_B1();
      if (B1_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        GET_B2();
      if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        state = B1_NOT_SUP_B2_NOT_SUP;
    }
  }
  else // A < I0
  {
    GET_B0();
    if (B0_INF) GOTO_END_NOT_AN_INTEREST_POINT
      GET_B1();
    if (B1_INF) GOTO_END_NOT_AN_INTEREST_POINT
      GET_B2();
    if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
      state = B1_NOT_INF_B2_NOT_INF;
  }

  for(a = 1; a <= opposite; a++)
  {
    GET_A();

    switch(state)
    {
    case B1_NOT_INF_B2_NOT_INF:
      if (A_SUP) {
        PUT_B2_IN_B1_AND_GET_B2();
        if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_NOT_INF_B2_NOT_INF);
      }
      if (A_INF) {
        if (B1_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
            PUT_B2_IN_B1_AND_GET_B2();
        if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_EQUAL_B2_NOT_SUP);
      } 
      // A ~ I0
      if (B1_NOT_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        if (B2_NOT_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
      if (B2_SUP) GOTO_STATE(B1_SUP_B2_SUP);
      if (B2_INF) GOTO_STATE(B1_SUP_B2_INF);
      GOTO_END_NOT_AN_INTEREST_POINT

    case B1_NOT_SUP_B2_NOT_SUP:
      if (A_INF) {
        PUT_B2_IN_B1_AND_GET_B2();
        if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_NOT_SUP_B2_NOT_SUP);
      }
      if (A_SUP) {
        if (B1_INF) GOTO_END_NOT_AN_INTEREST_POINT
          if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
            PUT_B2_IN_B1_AND_GET_B2();
        if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_EQUAL_B2_NOT_INF);
      }
      // A ~ I0
      if (B1_NOT_INF) GOTO_END_NOT_AN_INTEREST_POINT
        if (B2_NOT_INF) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
      if (B2_INF) GOTO_STATE(B1_INF_B2_INF);
      if (B2_SUP) GOTO_STATE(B1_INF_B2_SUP);
      GOTO_END_NOT_AN_INTEREST_POINT

    case B1_INF_B2_INF:
      if (A_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        PUT_B2_IN_B1_AND_GET_B2();
      if (A_INF)
      {
        if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_INF_B2_NOT_SUP);
      } 
      // A ~ I0
      if (B2_SUP) GOTO_STATE(B1_INF_B2_SUP);
      if (B2_INF) GOTO_STATE(B1_INF_B2_INF);
      GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0

    case B1_SUP_B2_SUP:
      if (A_INF) GOTO_END_NOT_AN_INTEREST_POINT
        PUT_B2_IN_B1_AND_GET_B2();
      if (A_SUP) {
        if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_SUP_B2_NOT_INF);
      }
      // A ~ I0
      if (B2_SUP) GOTO_STATE(B1_SUP_B2_SUP);
      if (B2_INF) GOTO_STATE(B1_SUP_B2_INF);
      GOTO_END_NOT_AN_INTEREST_POINT

    case B1_INF_B2_NOT_SUP:
      if (A_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        if (A_INF) {
          PUT_B2_IN_B1_AND_GET_B2();
          if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
            GOTO_STATE(B1_NOT_SUP_B2_NOT_SUP);
        }
        if (B2_NOT_INF) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
        if (B2_INF) GOTO_STATE(B1_INF_B2_INF);
        if (B2_SUP) GOTO_STATE(B1_INF_B2_SUP);
        GOTO_END_NOT_AN_INTEREST_POINT

    case B1_SUP_B2_NOT_INF:
      if (A_INF) GOTO_END_NOT_AN_INTEREST_POINT
        if (A_SUP) {
          PUT_B2_IN_B1_AND_GET_B2();
          if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
            GOTO_STATE(B1_NOT_INF_B2_NOT_INF);
        }
        // A ~ I0
        if (B2_NOT_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
        if (B2_SUP) GOTO_STATE(B1_SUP_B2_SUP);
        if (B2_INF) GOTO_STATE(B1_SUP_B2_INF);
        GOTO_END_NOT_AN_INTEREST_POINT

    case B1_INF_B2_SUP:
      if (A_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        if (A_INF) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
      // A ~ I0
      if (B2_SUP) GOTO_STATE(B1_SUP_B2_SUP);
      if (B2_INF) GOTO_STATE(B1_SUP_B2_INF);
      GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0

    case B1_SUP_B2_INF:
      if (A_SUP) GOTO_END_NOT_AN_INTEREST_POINT
        if (A_INF) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
      // A ~ I0
      if (B2_INF) GOTO_STATE(B1_INF_B2_INF);
      if (B2_SUP) GOTO_STATE(B1_INF_B2_SUP);
      GOTO_END_NOT_AN_INTEREST_POINT // A ~ I0, B2 ~ I0

    case B1_EQUAL_B2_NOT_SUP:
      if (A_SUP) {
        if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
        if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_EQUAL_B2_NOT_INF);
      }
      if (A_INF) {
        PUT_B2_IN_B1_AND_GET_B2();
        if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_NOT_SUP_B2_NOT_SUP);
      }
      GOTO_END_NOT_AN_INTEREST_POINT

    case B1_EQUAL_B2_NOT_INF:
      if (A_INF) {
        if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          PUT_B2_IN_B1_AND_GET_B2();
        if (B2_SUP) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_EQUAL_B2_NOT_SUP);
      }
      if (A_SUP) {
        PUT_B2_IN_B1_AND_GET_B2();
        if (B2_INF) GOTO_END_NOT_AN_INTEREST_POINT
          GOTO_STATE(B1_NOT_INF_B2_NOT_INF);
      }
      GOTO_END_NOT_AN_INTEREST_POINT

    default:
      cout << "PB default" << endl;
    } // switch(state)
  } // for(a...)

  Scores[x] = short(score + dirs_nb * I[x]);
}

int yape::detect(IplImage * image, keypoint * points, int max_point_number, IplImage * _filtered_image)
{
  IplImage * used_filtered_image;

  if (_filtered_image == 0)
  {
    int gaussian_filter_size = 3;

    if (radius >= 5) gaussian_filter_size = 5;
    if (radius >= 7) gaussian_filter_size = 7;
    cvSmooth(image, filtered_image, CV_GAUSSIAN, gaussian_filter_size, gaussian_filter_size);

    used_filtered_image = filtered_image;
  }
  else
    used_filtered_image = _filtered_image;

  reserve_tmp_arrays();

  raw_detect(used_filtered_image);

  get_local_maxima(image, radius, 0);

  int points_nb = pick_best_points(points, max_point_number);

  if (use_subpixel)
    for(int i = 0; i < points_nb; i++) 
      subpix_refine(used_filtered_image, points + i);

  return points_nb;
}

static unsigned mymin(unsigned a, unsigned b)
{
	return (a<b ? a:b);
}

/*! This method sorts tmp_points and select the max_point_number best points,
* as long as the score is high enough.
*/
int yape::pick_best_points(keypoint * points, unsigned int max_point_number)
{
  if (use_bins)
  {
    unsigned int N = 0;
    for(int i = 0; i < bin_nb_u; i++)
    {
      for(int j = 0; j < bin_nb_v; j++)
      {
        if (bins[i][j].size() > 0){
          sort(bins[i][j].begin(), bins[i][j].end());
          N += bins[i][j].size();
        }
      }
    }

    N = max_point_number;
    unsigned int N_per_bin = N / (bin_nb_u * bin_nb_v);
    int points_nb = 0;
    for(int i = 0; i < bin_nb_u; i++)
    {
      for(int j = 0; j < bin_nb_v; j++)
      {
        for(unsigned int k = 0; k < mymin(N_per_bin, bins[i][j].size()); k++, points_nb++)
          points[points_nb] = bins[i][j][k];
      }
    }

    return points_nb;
  }
  else
    if (tmp_points.size() > 0) 
    {
      sort(tmp_points.begin(), tmp_points.end());

      int score_threshold = 0;

      int tot_pts = tmp_points.size()<max_point_number ? tmp_points.size() : max_point_number;

      int points_nb = 0;
      for(points_nb = 0; 
        points_nb<tot_pts && tmp_points[points_nb].score>score_threshold; 
        points_nb++)
        points[points_nb] = tmp_points[points_nb];

      return points_nb;
    }

    return 0;
}

/*! Detect interest points, without filtering and without selecting best ones.
* Just find them and add them to tmp_points. tmp_points is not cleared in this
* method.
*/
void yape::raw_detect(IplImage *im) {
  unsigned int R = radius;
  short * dirs = Dirs->t[R];
  unsigned char dirs_nb = (unsigned char)(Dirs_nb[R]);
  unsigned char opposite = dirs_nb / 2;

  CvRect roi = cvGetImageROI(im);

  if (roi.x < int(R+1)) roi.x = R+1;
  if (roi.y < int(R+1)) roi.y = R+1;
  if ((roi.x + roi.width)  > int(im->width-R-2))  roi.width  = im->width  - R - roi.x - 2;
  if ((roi.y + roi.height) > int(im->height-R-2)) roi.height = im->height - R - roi.y - 2;

  unsigned int xend = roi.x + roi.width;
  unsigned int yend = roi.y + roi.height;

  for(unsigned int y = roi.y; y < yend; y++)
  {
    unsigned char * I = (unsigned char *)(im->imageData + y*im->widthStep);
    short * Scores = (short *)(scores->imageData + y*scores->widthStep);

    for(unsigned int x = roi.x; x < xend; x++)
    {
      int Ip = I[x] + tau;
      int Im = I[x] - tau;

      if (Im<I[x+R] && I[x+R]<Ip && Im<I[x-R] && I[x-R]<Ip)
        Scores[x] = 0;
      else 
        perform_one_point(I, x, Scores, Im, Ip, dirs, opposite, dirs_nb);
    }
  }
}

#define Dx 1
#define Dy next_line

#define W (-Dx)
#define E (+Dx)
#define N (-Dy)
#define S (+Dy)

#define MINIMAL_SCORE (0 / radius)

inline bool yape::third_check(const short * Sb, const int next_line)
{
  int n = 0;

  if (Sb[E]   != 0) n++;
  if (Sb[W]   != 0) n++;
  if (Sb[S]   != 0) n++;
  if (Sb[S+E] != 0) n++;
  if (Sb[S+W] != 0) n++;
  if (Sb[N]   != 0) n++;
  if (Sb[N+E] != 0) n++;
  if (Sb[N+W] != 0) n++;

  return n >= minimal_neighbor_number;
}

// Test if a pixel is a local maxima in a given neighborhood.
static inline bool is_local_maxima(const short *p, int neighborhood, const IplImage *scores)
{
#ifdef CONSIDER_ABS_VALUE_ONLY
  unsigned v = abs(p[0]);
  if (v < 5) return false;

  int step = scores->widthStep / 2;

  p -= step*neighborhood;
  for (int y= -neighborhood; y<=neighborhood; ++y) {
    for (int x= -neighborhood; x<=neighborhood; ++x) {
      if (abs(p[x]) > v)
        return false;
    }
    p += step;
  }
  return true;
#else
  int v = p[0];

  int step = scores->widthStep / 2;

  if (v > 0) {
    p -= step*neighborhood;
    for (int y= -neighborhood; y<=neighborhood; ++y) {
      for (int x= -neighborhood; x<=neighborhood; ++x) {
        if (p[x] > v)
          return false;
      }
      p += step;
    }
  } else {
    p -= step*neighborhood;
    for (int y= -neighborhood; y<=neighborhood; ++y) {
      for (int x= -neighborhood; x<=neighborhood; ++x) {
        if (p[x] < v)
          return false;
      }
      p += step;
    }
  }

  return true;

#endif
}

/*! Find local maximas in score image and append them to tmp_points.
* \return the number of local maxima found.
*/
int yape::get_local_maxima(IplImage * image, int R, float scale /*, keypoint * points, int max_number_of_points*/)
{
  int nbpts=0;

  const int next_line = scores->widthStep / sizeof(short);
  int h = scores->height;
  int w = scores->width;

  CvRect roi = cvGetImageROI(image);

  if (roi.x < int(R+1)) roi.x = R+1;
  if (roi.y < int(R+1)) roi.y = R+1;
  if ((roi.x + roi.width)  > int(scores->width-R-2))  roi.width  = scores->width  - R - roi.x - 2;
  if ((roi.y + roi.height) > int(scores->height-R-2)) roi.height = scores->height - R - roi.y - 2;

  unsigned int xend = roi.x + roi.width;
  unsigned int yend = roi.y + roi.height;

  for(unsigned int y = roi.y; y < yend; y++)
  {
    short * Scores = (short *)(scores->imageData + y * scores->widthStep);

    for(unsigned int x = roi.x; x < xend; x++)
    {
      short * Sb = Scores + x;

      // skip 0 score pixels
      if (abs(Sb[0]) < 5)
        ++x; // if this pixel is 0, the next one will not be good enough. Skip it.
      else 
      {
        if (third_check(Sb, next_line) && is_local_maxima(Sb, R, scores))
        {
          keypoint p;
          p.u = float(x);
          p.v = float(y);
          p.scale = scale;
          p.score = float(abs(Sb[0]));

          if (use_bins)
          {
            int bin_u_index = (bin_nb_u * x) / w;
            int bin_v_index = (bin_nb_v * y) / h;

            if (bin_u_index >= bin_nb_u)
              bin_u_index = bin_nb_u - 1;
            if (bin_v_index >= bin_nb_v)
              bin_v_index = bin_nb_v - 1;

            if (bins[bin_u_index][bin_v_index].size() < yape_bin_size)
              bins[bin_u_index][bin_v_index].push_back(p);
          }
          else
            tmp_points.push_back(p);

          nbpts++;
          x += R-1;
        }
      }
    }
  }
  return nbpts;
}

/////////////////////////////////////////////////////////////////
// Sub-pixel / sub-scale accuracy.
/////////////////////////////////////////////////////////////////

static float fit_quadratic_2x2(float x[2], float L[3][3])
{
  float H[2][2];
  float b[2];

  b[0] = -(L[1][2] - L[1][0]) / 2.0f;
  b[1] = -(L[2][1] - L[0][1]) / 2.0f;

  H[0][0] = L[1][0] - 2.0f * L[1][1] + L[1][2];
  H[1][1] = L[0][1] - 2.0f * L[1][1] + L[2][1];
  H[0][1] = H[1][0] = (L[0][0] - L[0][2] - L[2][0] + L[2][2]) / 4.0f;

  float t4 = 1/(H[0][0]*H[1][1]-H[0][1]*H[1][0]);
  x[0] =  H[1][1]*t4*b[0]-H[0][1]*t4*b[1];
  x[1] = -H[1][0]*t4*b[0]+H[0][0]*t4*b[1];

  return 0.5f * (b[0] * x[0] + b[1] * x[1]);
}

void yape::subpix_refine(IplImage *im, keypoint *p)
{
  float L[3][3];

  int px = (int) p->u;
  int py = (int) p->v;
  int dirs_nb = Dirs_nb[radius];
  short * dirs = Dirs->t[radius];

  if ((px<= radius) || (px >= (scores->width-radius)) || (py <= radius) || (py >= (scores->height-radius)))
    return;

  unsigned char * I = (unsigned char *) (im->imageData + py*im->widthStep) +  px;
  short * s = (short *) (scores->imageData + py*scores->widthStep) +  px;
  int line = scores->widthStep/sizeof(short);

  for (int y=0; y<3; ++y) {
    int offset = (y-1)*line - 1;
    for (int x=0; x<3; ++x) {
      if (s[ offset + x]==0) {
        // Compute Laplacian
        int score = 0;
        for (int d=0; d<dirs_nb; ++d)
          score += I[offset + x + dirs[d]];
        L[y][x] = -float(score - dirs_nb*(int)I[offset + x]);
      } else {
        L[y][x] = (float)s[ offset + x];
      }
    }
  }

  float delta[2];
  p->score += fit_quadratic_2x2(delta, L);

  if ((delta[0] >= -1) && (delta[0] <= 1))
    p->u += delta[0];
  else 
    p->u+=0.5f;
  if ((delta[1] >= -1) && (delta[1] <= 1))
    p->v += delta[1];
  else 
    p->v+=0.5f;
}

//////////////////////////////////////////////////////////////////////
// PyrYape implementation
//////////////////////////////////////////////////////////////////////

/*! \param w width passed to Yape constructor
\param h height passed to Yape constructor
\param nbLev pyramid depth
*/
pyr_yape::pyr_yape(int w, int h, int nbLev) 
: yape (w,h)
{
  internal_pim = 0;
  pscores = new PyrImage(scores, nbLev);
  pDirs[0] = Dirs;
  pDirs_nb[0] = Dirs_nb;
  equalize = false;

  PyrImage pim(cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1),nbLev);

  for (int i=1; i<nbLev; i++) {
    pDirs[i] = new dir_table;
    pDirs_nb[i] = new int[yape_max_radius];
    for(int R = 1; R < yape_max_radius; R++)
      precompute_directions(pim[i], pDirs[i]->t[R], &(pDirs_nb[i][R]), R);
  }
}

pyr_yape::~pyr_yape() 
{
  if (internal_pim) delete internal_pim;

  for (int i=0; i<pscores->nbLev; i++) {
    delete pDirs[i];
    delete[] pDirs_nb[i];
  }
  Dirs=0;
  Dirs_nb=0;
  delete pscores;
  pscores = 0;
  scores = 0;
}

void pyr_yape::select_level(int l)
{
  scores = pscores->images[l];
  Dirs = pDirs[l];
  Dirs_nb = pDirs_nb[l];
}

/*! Detect features on the pyramid, filling the scale field of keypoints with
* the pyramid level. \return the detected keypoint number.
*/
int pyr_yape::detect(PyrImage *image, keypoint *points, int max_point_number) 
{
  reserve_tmp_arrays();

  for (int i=image->nbLev-1; i>=0; --i) 
  {
    select_level(i);
    raw_detect(image->images[i]);
    get_local_maxima(image->images[i], radius, float(i));
  }

  int n = pick_best_points(points, max_point_number);
  for (int i = 0; i < n; i++) {
    int l =(int)points[i].scale;
    select_level(l);
    subpix_refine(image->images[l], points + i);
  }

  return n;
}

/*!
* This method does the following:
* 1) Apply a Gaussian blur filter on the provided image, putting the result in
*    the pyramid lowest level.
* 2) Build the pyramid
* 3) call detect() on it.
*
* If no pyramid is given by the caller, a temporary pyramid image is created
* and recycled for future calls.
*
* \param im the input image. Must be 1 channel (gray levels).
* \param points an array to store keypoints.
* \param max_point_number the size of this array.
* \param caller_pim the pyramid to work on, or 0 for an internal pyramid.
*/
int pyr_yape::pyramidBlurDetect(IplImage *im, keypoint *points, int max_point_number, PyrImage *caller_pim)
{
  assert(im->nChannels == 1);

  PyrImage *pim;

  if (caller_pim == 0) 
  {
    if (internal_pim && ((internal_pim->images[0]->width != im->width) 
        || (internal_pim->images[0]->height != im->height))) 
    {
      delete internal_pim;
      internal_pim = 0;
    }

    if (internal_pim == 0)
      internal_pim = new PyrImage(cvCreateImage(cvGetSize(im), IPL_DEPTH_8U, 1), pscores->nbLev);

    pim = internal_pim;
  } 
  else 
  {
    pim = caller_pim;
    assert (im->width == caller_pim->images[0]->width);
  }

  int gaussian_filter_size = 3;
  if (radius >= 5) gaussian_filter_size = 5;
  if (radius >= 7) gaussian_filter_size = 7;
  cvSmooth(im, pim->images[0], CV_GAUSSIAN, gaussian_filter_size, gaussian_filter_size);

  pim->build();

  return detect(pim, points, max_point_number);
}

void pyr_yape::save_image_of_detected_points(char * name, IplImage * image, keypoint * points, int points_nb)
{
  IplImage * point_image = mcvGrayToColor(image);
  for(int i = 0; i < points_nb; i++)
    mcvCircle(point_image,
              (int)PyrImage::convCoordf(points[i].u, (int)points[i].scale, 0), 
              (int)PyrImage::convCoordf(points[i].v, (int)points[i].scale, 0), 
              PyrImage::convCoord(2 * radius, (int)points[i].scale, 0), mcvRainbowColor((int)points[i].scale), 1);
  mcvSaveImage(name, point_image);
  cvReleaseImage(&point_image);
}

void pyr_yape::stat_points(keypoint *points, int nb_pts)
{
  int *histogram = new int[pscores->nbLev];

  for (int l=0; l< pscores->nbLev; ++l) histogram[l]=0;

  for (int i=0; i<nb_pts; ++i)
    histogram[(int)(points[i].scale)]++;

  for (int l=0; l< pscores->nbLev; ++l)
    cout << "Level " << l << ": " << histogram[l] << " keypoints (" 
         << 100.0f * (float)histogram[l]/(float)nb_pts << "%)\n";

  delete[] histogram;
}

