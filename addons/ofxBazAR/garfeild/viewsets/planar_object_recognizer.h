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
#ifndef PLANAR_OBJECT_RECOGNIZER_H
#define PLANAR_OBJECT_RECOGNIZER_H

#include "ofxCvMain.h"
#include "../keypoints/keypoint.h"
#include "../keypoints/yape.h"
#include <starter.h>
#include "affine_image_generator.h"
#include "object_view.h"
#include "image_classification_forest.h"
#include "image_object_point_match.h"

/*!\defgroup viewsets Viewsets
 * \ingroup garfeild
 * Handle sets of possible appearance for feature points.
 */
//!\ingroup viewsets
//@{

//! Hard coded maximum number of keypoints that planar_object_recognizer can handle
static const int hard_max_detected_pts = 5000;

/*!
\ingroup viewsets
\brief Planar object detector 

This class can learn a planar surface and recognize its feature points on a 
new image.
*/
class planar_object_recognizer
{
public:
  //! empty constructor. call build, load or buildWithCache before use
  planar_object_recognizer();

  //! Create from the data stored in the directory \c directory_name
  planar_object_recognizer(string directory_name);

  ~planar_object_recognizer(void);

  //! Build the model and save it on disk.
  //! \return true on success, false on failure
  bool build_with_cache(string filename, int max_point_number_on_model,
                        int patch_size, int yape_radius, 
                        int tree_number, int nbLev,
                        LEARNPROGRESSION LearnProgress=0);

  bool build(IplImage *model_image,
		  int max_point_number_on_model, int patch_size,
		  int yape_radius, int tree_number, int nbLev, 
		  LEARNPROGRESSION LearnProgress=0, int *roi=0);
  //@{
  /** \name Functions for fine tuning:
  */
  //! Activate bins when detecting model points (Default)
  void use_bins_when_creating_model_points(void) { use_bins_for_model_points = true; } 
  //! Disactivate bins when detecting model points
  void dont_use_bins_when_creating_model_points(void) { use_bins_for_model_points = false; }

  //! Activate bins when detecting input image points (Default)
  void use_bins_when_detecting_input_image_points(void) { use_bins_for_input_image = true; } 
  //! Disactivate bins when detecting model points
  void dont_use_bins_when_detecting_input_image_points(void) { use_bins_for_input_image = false; }

  //! Default = 20
  void set_noise_level(int noise_level);

  //! Default = false;
  void set_use_random_background(bool use_random_background);

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

  //! Default method.
  void use_orientation_correction(void);
  void dont_use_orientation_correction(void);

  //! Default = 10
  void set_max_depth(int p_max_depth) { max_depth = p_max_depth; }

  //! Sample number for the refine step (default = 1000):
  void set_sample_number_for_refining(int sample_number) { sample_number_for_refining = sample_number; }
  int sample_number_for_refining;
  //@}

  //! Create the point recognizer (see \ref forest field)
  void learn(int max_point_number_on_model, 
             int patch_size, int yape_radius, 
             int tree_number, int nbLev=5, 
             LEARNPROGRESSION LearnProgress=0);

  //! Save data in the given directory. The directory must exist.
  void save(string directory_name);

  //! load data from a given directory. 
  //! \return true on success, false on failure.
  bool load(string directory_name);

  /*!
  \brief Detect the object in the given input image.

  Returns true if the object is detected.
  If the object is detected, put the detected corners in the fieds \c detected_u_corner1, \c detected_v_corner1 ...

  Calls successively the functions:
  - \c detect_points 
  - \c preprocess_points
  - \c match_points
  - \c estimate_affine_transformation
  - \c estimate_homographic_transformation_nonlinear_method
  */
  bool detect(IplImage * input_image);

  //! set the maximum number of points we want to detect
  void set_max_detected_pts(int max);

  //@{
  /** \name Functions called by the detect() function 
  */
  void detect_points(IplImage * input_image);
  void preprocess_points(void);
  void match_points(bool fill_match_struct = true);
  bool estimate_affine_transformation(void);
  bool estimate_homographic_transformation_linear_method(void);
  bool estimate_homographic_transformation_nonlinear_method(void);
  //@}

  //! keypoints on the object. (X, Y) = coordinates in the original image, Z = 0.
  //! usage: model_points[target][model], with 0 <= target < detected_point_number and
  //! 0 <= model < model_point_number
  object_keypoint * model_points;
  int model_point_number;

  //! Detected keypoints in the input image
  keypoint *detected_points;
  int detected_point_number;
  image_class_example *detected_point_views;

  //! Match probabilities for each detected keypoint
  float * match_probabilities[hard_max_detected_pts];
  //! Matches between the detected keypoints, and the model keypoints
  image_object_point_match matches[hard_max_detected_pts];
  int match_number;

  bool object_is_detected;
  affinity * affine_motion;
  homography * H;
  ls_minimizer2 * homography_estimator;
  float detected_u_corner1, detected_v_corner1;
  float detected_u_corner2, detected_v_corner2;
  float detected_u_corner3, detected_v_corner3;
  float detected_u_corner4, detected_v_corner4;

  pyr_yape * point_detector;

  //! For visualization
  IplImage * create_result_image(IplImage * input_image, 
    bool p_draw_points, bool p_draw_matches, 
    bool p_draw_object, bool p_draw_model_image,
    int line_width = 2);

  //! For debugging: save generated patches for a particular point in dir patches,
  //! before and after orientation correction.
  void debug_model_point(int p_index_of_model_point_to_debug) 
  { index_of_model_point_to_debug = p_index_of_model_point_to_debug; }

  //! For debugging: save one image per match in dir matches
  void save_one_image_per_match(IplImage * input_image, const char * matches_dir);
  void save_one_image_per_match_model_to_input(IplImage * input_image, const char * matches_dir);
  void save_one_image_per_match_input_to_model(IplImage * input_image, const char * matches_dir);

  ///////////////////////////////////////////////////////////////////////////

  //! Function called by the 2 constructors
  void initialize(void);

  affine_image_generator new_images_generator;

  object_view * object_input_view;

  pair<object_keypoint, int> * search_for_existing_model_point(vector< pair<object_keypoint, int> > * tmp_model_points,
    float cu, float cv, int scale);
  void detect_most_stable_model_points(int max_point_number_on_model, 
                                       int patch_size, int view_number, 
                                       double min_view_rate, 
                                       LEARNPROGRESSION LearnProgress=0);
  void save_image_of_model_points(int patch_size, char * filename = 0);

  //! Image classifier
  image_classification_forest * forest;

  // For position estimation:
  int compute_support_for_affine_transformation(affinity * A);
  bool three_random_correspondences(int * n1, int * n2, int * n3);
  bool valid(affinity * A);

  int max_detected_pts;
  int max_depth;

  //! Some parameters for fine tuning:
  //! Called by the 2 constructors
  void default_settings(void);
  bool use_bins_for_model_points;
  bool use_bins_for_input_image;
  int index_of_model_point_to_debug;

  //! number of generated views for finding stable points
  int views_number; 

  //! minimum visible rate for determining stable keypoints
  double min_view_rate;

  /*! interest points that are closer than this distance are merged by
  * by search_for_existing_model_point().
  */
  double keypoint_distance_threshold;

  /*! The RANSAC estimation will not take into account a match whose score is
   * under that threshold.
   */
  float match_score_threshold;

  /*! The minimum reprojection distance that RANSAC will consider compatible.
   */
  float ransac_dist_threshold;

  //! Distance threshold, in pixels, for non-linear refinement
  float non_linear_refine_threshold;

  //! maximum iteration number for RANSAC
  int max_ransac_iterations;

  /*! RANSAC will stop if it finds a transformation that satisfies at least
   *  ransac_stop_support matches.
   */
  int ransac_stop_support;

  //@{
  //! The following functions are useful for visualization only:
  void save_patch_before_and_after_correction(IplImage * image,
                                              int u, int v, int patch_size,
                                              image_class_example * pv,
                                              int point_index, 
                                              int call_number);
  void concat_model_and_input_images(IplImage * input_image, bool p_draw_model_image = true);
  void draw_points(int line_width = 1);
  void draw_model_points(int line_width = 1);
  void draw_input_image_points(int line_width = 1);
  void draw_matches(int line_width = 2);
  void draw_inlier_matches(int line_width = 1);
  void draw_model(void);
  IplImage * model_and_input_images;
  int x0, y0; // up left corner of modelImage in modelInputImage
  int u_input_image, v_input_image; // up left corner of inputImage in modelInputImage
  //@}

  void check_target_size(IplImage *image);
};

//@}
#endif // PLANAR_OBJECT_RECOGNIZER_H
