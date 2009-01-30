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
#ifndef YAPE_H
#define YAPE_H

#include <vector>
#include <cv.h>

#include <starter.h> 
#include "keypoint.h"

const int yape_max_radius = 20;

/*!
\ingroup keypoints 
\brief \em YAPE feature point detector.

Stands for Yet Another Point Extractor.

Usage:

You need OpenCV to use this code.
Two different uses of the Yape class are possible:

1) The simplest way is to call the static function static_detect:
\code
int N = yape::static_detect(image, points, maxNumberOfPoints[, radius]);
\endcode

where:
- \c image is a pointer on a \c IplImage structure from OpenCv. The type of the image should
be \c IPL_DEPTH_8U, with one channel;
The lowest its value is, the finest are the detected points;
- \c points is a array of \ref keypoint s. It should be large enough to store all the detected points;
- \c maxNumberOfPoints is the desired maximum number of detected points.
- \c radius is a parameter for the point detection. Its value should be between 3 and 7, its default value is 7.

The function returns the actual number of detected points.

2) Detection in a large number of images of same size:

If the detection should be performed on a large number of images of same size,
you should first create  an instance of the detector. The yape constructor performs
some pre-computation and pre- memory allocation to save some computation time during
the actual detection.
\code
// Create an instance of Yape for detection in 640x480 images:
yape * pe = new yape(640, 480);

// The default value for the radius is 7. Use set_radius() to change it:
pe->set_radius(3);

// Call the function detect() exactly like the static_detect() function:
N[0] = pe->detect(images[0], points[0], 100);
N[1] = pe->detect(images[1], points[1], 100);
N[2] = pe->detect(images[2], points[2], 100);
N[3] = pe->detect(images[3], points[3], 100);
...

// Call the destructor:
delete pe;
\endcode

The \c saveImageOfDetectedPoints function is useful to save an image of the detected points:
\code
static void saveImageOfDetectedPoints(char * name, IplImage * image, CvPoint * points, int points_nb);
\endcode
*/

class yape
{
public:
  //! Constructor for detection in \c width x \c height images.
  yape(int width, int height);
  virtual ~yape();

  void set_radius(int radius);
  int get_radius(void) { return radius; }

  void set_tau(int tau);
  int get_tau(void) { return tau; }

  void activate_bins(void) { set_use_bins(true); } // Default
  void disactivate_bins(void) { set_use_bins(false); }
  void set_use_bins(bool p_use_bins) { use_bins = p_use_bins; }
  bool get_use_bins(void) { return use_bins; }
  void set_bins_number(int nb_u, int nb_v) { bin_nb_u = nb_u; bin_nb_v = nb_v;}

  //! Subpixel. Can be activated or disactived (default) for monoscale detection. Always activated for multi-scale detection.
  void activate_subpixel(void) { set_use_subpixel(true); } 
  void disactivate_subpixel(void) { set_use_subpixel(false); } // Default
  void set_use_subpixel(bool p_use_subpixel) { use_subpixel = p_use_subpixel; }

  void set_minimal_neighbor_number(int p_minimal_neighbor_number) { minimal_neighbor_number = p_minimal_neighbor_number;} 
  int get_minimal_neighbor_number(void) { return minimal_neighbor_number; } 

  int detect(IplImage * image, keypoint * points, int max_point_number, IplImage * smoothed_image = 0);

  //! detect interest points and add them to tmp_points.
  void raw_detect(IplImage *im);

  //! sort and select the max_point_number best features.
  int pick_best_points(keypoint * points, unsigned int max_point_number);

  //! Static function for point detection. Slower but avoids an instantiation.
  static int static_detect(IplImage * image, keypoint * points, int max_point_number, int radius = 7, int tau = 10);

  //! Save a color image with the detected points on the original image. Useful for visualisation...
  void save_image_of_detected_points(char * name, IplImage * image, keypoint * points, int points_nb);

  //! Return scores and filtered images, for debugging purposes.
  IplImage * get_scores_image(void) { return scores; }
  IplImage * get_filtered_image(void) { return filtered_image; }

  void subpix_refine(IplImage *im, keypoint *p);

protected:
  void reserve_tmp_arrays(void);

  int get_local_maxima(IplImage * image, int R, float scale /*, keypoint * points, int max_point_number */);

  void perform_one_point(const unsigned char * I, const int x, short * Scores,
    const int Im, const int Ip, 
    const short * dirs, const unsigned char opposite, const unsigned char dirs_nb);

  bool double_check(IplImage * image, int x, int y, short * dirs, unsigned char dirs_nb);
  bool third_check(const short * Sb, const int next_line);
  int minimal_neighbor_number;

  void precompute_directions(IplImage * image, short * _Dirs, int * _Dirs_nb, int R);
  void init_for_monoscale(void);

  // Image size:
  int width, height;

  // Radius: scale parameter for point detection
  int radius;

  // Tau: threshold to decide if two intensities are similar.
  int tau;

  // Directions:
  struct dir_table {
    short t[yape_max_radius][1024];
  };
  dir_table *Dirs;
  int *Dirs_nb;

  // For keypoint sorting:
  typedef std::vector<keypoint> keypoint_vector;
  keypoint_vector tmp_points;

  // Bins etc:
  bool use_bins;
  keypoint_vector bins[10][10];
  int bin_nb_u, bin_nb_v;

  // Subpixel (always 'on' for pyramidal version)
  bool use_subpixel;

  // Intermediate images:
  IplImage * scores, * filtered_image;

  // For statistics in the Finite State Machine:
  int stats_state[100], stats_iter[100];

  // For the Finite State Machine:
  int score;
  int a, b;
  // int A, B0, B1, B2;
  int A, B_0, B1, B2;
  int state;

  CvMat * H;
  CvMat * mg;
  CvMat * shift;
};

//! Pyramidal YAPE (Feature point extractor)
/*! Improve Yape to work with multi-scale pyramids (PyrImage).
 * \ingroup keypoints
 */
class pyr_yape : public yape {
public:
  pyr_yape(int w, int h, int nbLev);
  virtual ~pyr_yape();

  //! Blur the given image, build a pyramid and call detect().
  int pyramidBlurDetect(IplImage *im, keypoint *points, int max_point_number, PyrImage *caller_pim = 0);

  //! Call pyramidBlurDetect():
  int detect(IplImage *im, keypoint *points, int max_point_number)
  {
    return pyramidBlurDetect(im, points, max_point_number);
  }

  //! Pyramidal feature point detection.
  int detect(PyrImage * image, keypoint * points, int max_point_number);

  //! Save a color image with the detected points on the original image. Useful for visualisation...
  void save_image_of_detected_points(char * name, IplImage * image, keypoint * points, int points_nb);

  //! compute and print on stdout a keypoint scale histogram.
  void stat_points(keypoint *points, int nb_pts);
  
//protected:
  PyrImage *internal_pim; //< pyramid image, recylcled for each frame
  PyrImage *pscores;
  dir_table *pDirs[12];
  int *pDirs_nb[12];

  //! Limit the maximum number of detected keypoint per level.
  bool equalize;

  void select_level(int l);
};

#endif // YAPE_H
