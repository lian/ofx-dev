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
#ifndef LS_MINIMIZER_H
#define LS_MINIMIZER_H

#include <limits>
#include <cxcore.h>
#include "ls_step_solver.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef double ls_minimizer_type;

#include "observation_types.h"
#include "prosac_function_types.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*callback_function)(double * state, void ** user_data);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! Non-linear Minimizer
 *  \author Vincent Lepetit
 *  \ingroup starter
 */
class ls_minimizer
{
public:

  ls_minimizer(int state_size, int maximum_scalar_measure_number);
  ~ls_minimizer();

  void set_max_number_of_observations_2data_1measure(int n);
  void set_max_number_of_observations_2data_2measures(int n);

  //! for example a 3D point projected on a 2D plane
  void set_max_number_of_observations_3data_2measures(int n);

  /*! Scale applied to each optimized parameter (each dimension of the
   * optimization space). Not used by default, but an automated method is used.
   */
  void set_scales(double * scales);
  void desactivate_automated_scaling(void) { use_automated_scaling = false; }

  /*! 0 = nothing
   *  1 = messages before and after minimization
   *  2 = message at each iteration.
   *  3 = debug
   */
  void set_verbose_level(int vl);

  /*! user arbitrary pointers. slot_index should be in [0,9]
   * this pointer array is passed to the callback functions
   */
  void set_user_data(int slot_index, void * ptr);

  //! call that before adding observations for a new optimization.
  void reset_observations(void);

  bool add_observation(function_2data_1measure f,
                       const double d0, const double d1,
                       const double b0);
  bool add_observation(function_2data_2measures f,
                       const double d0, const double d1,
                       const double b0, const double b1);
  /*! In the case of a 3d point projected on a 2d plane:
   *  d0 = X, d1 = Y, d2 = Z
   *  (b0,b1) projection goal
   * f : f(d0,d1,d2,state, ..) is the function computing the projection and its gradient.
   */
  bool add_observation(function_3data_2measures f,
                       const double d0, const double d1, const double d2,
                       const double b0, const double b1);

  //! this callback is called each time the state vector changes.
  void set_new_iteration_callback(callback_function callback);

  /*! For robust estimation (default = +inf)
   *  residual = max( ||b-f(d,state)||^2, c^2 )
   *  This value will be applied to next added observations
   */
  void set_default_c(double c);

  /*! For robust estimation (default = +inf):
   *  change the last added observation robust estimator value
   */
  void set_last_observation_c(double c);

  //! For robust estimation using Julien' method (default = +inf for both):
  void set_last_observation_c_max_c_min(double c_max, double c_min);
  //! Set observation weight (default = 1):
  void set_last_observation_weight(double weight);
  //! Set observation confidence (default = 1). Only used for PROSAC and cat tail.
  void set_last_observation_confidence(double confidence);

  //! state vector
  ls_minimizer_type * state;

  // ALGORITHMS:
  // Steepest descent:
  int minimize_using_steepest_descent_from(double * initial_state);

  // Levenberg-Marquardt
  int minimize_using_levenberg_marquardt_from(double * initial_state);
  void lm_set_max_iterations(int it);
  //! if f iterations do not decrease the function, stop.
  void lm_set_max_failures_in_a_row(int f);
  //! stop condition. Very restrictive: 0.999  less restrictive: 0.9 
  void lm_set_tol_cos(double t);

  // Gauss-Newton:
  bool minimize_using_gauss_newton_from(double * initial_state);

  //! Dogleg (not convincing).
  int minimize_using_dogleg_from(double * initial_state);

  /*! Cat Tail (experimental)
   * a mix between gauss-newton and line search.
   */
  int minimize_using_cattail_from(double * initial_state);
  void ct_set_max_iterations(int it) {ct_max_iterations = it; }
  void set_line_search_parameters(double lambda0, double k_rough, double k_fine);

  // Prosac
  double minimize_using_prosac(prosac_function_20scalars f, int observation_type, int min_number_of_inliers, int max_number_of_iterations);

  // Julien' method
  double minimize_using_julien_method_from(double * state, int nb_steps, int nb_iterations_per_step);

  // DEBUGGING:
  /*! Checking derivatives: compares finite difference jacobian and analytical
   *  jacobian computed by the user provided functions.
   */
  void check_jacobians_around(double * state, double state_step);

  // Comparing with ground truth:
  void set_last_observation_as_outlier(void);
  void set_ground_truth(double * state);
  void compare_outliers_with_ground_truth(void);
  void compare_state_with_ground_truth(void);

private:
  void set_default_values(void);

  inline double rho(double x2, double c2) { return (x2 < c2) ? x2 : c2; }
  double build_eps(double * state, double current_best_residual = std::numeric_limits<double>::max());
  int nb_inliers;
  bool build_J(double * state);
  bool build_J_and_eps(double * state);
  bool build_J_and_stuff(double * state);
  double compute_residual(double * state, bool display = false);
  // !!! CALL new_iteration_callback function before calling residual !!!
  ls_minimizer_type residual(ls_minimizer_type * state);

  double build_eps_return_inlier_residual(double * state, double current_best_residual = std::numeric_limits<double>::max());
  double inlier_residual(double * state, double current_best_residual);

  void show_state(int vl, double * state, double r);

  void set_current_c_s(double k = -1.);

  ls_minimizer_type * new_state, * best_state, * scales;
  int state_size;

  double default_squared_c;
  observation_2data_1measure * observations_2data_1measure;
  int number_of_observation_2data_1measure;

  observation_2data_2measures * observations_2data_2measures;
  int number_of_observation_2data_2measures;

  observation_3data_2measures * observations_3data_2measures;
  int number_of_observation_3data_2measures;

  int type_of_last_added_observation;

  CvMat * J, * eps, * eps_previous;
  CvMat * Jt, * JtJ, * Jteps, * ds, * Jds, * aug_JtJ;
  ls_step_solver * step_solver;
  callback_function new_iteration_callback;

  bool use_user_scaling, use_automated_scaling;

  void * user_data[10];

  // Algorithm specific data:
  // Levenberg-Marquardt
  int lm_max_iterations;
  int lm_max_failures_in_a_row;
  double lm_tol_cos;

  // Dog leg:
  double dl_update_Delta(double rho, double Delta, double rho_min, double rho_max);
  double dl_tol_cos;
  CvMat * dl_delta_diff, * dl_delta_dl, * dl_delta_sd, * dl_delta_gn;
  CvMat * JtJdelta, * JJteps;

  // Cat tail:
  bool line_search(CvMat * dir, double lambda_min, double lambda_max, double current_residual, double & new_residual, double & new_lambda);
  CvMat * ct_delta_gn, * ct_delta_sd;
  int ct_max_iterations;
  double ct_k_rough, ct_k_fine, ct_lambda0;

  // Prosac:
  bool pick_random_indices(int & i0, int & i1, int max_index);
  bool pick_random_indices(int & i0, int & i1, int & i2, int max_index);
  bool pick_random_indices(int & i0, int & i1, int & i2, int & i3, int max_index);

  // Julien' method:
  bool inside_julien_method;

  // For debugging:
  int verbose_level;
  double * ground_truth_state;
};

#endif // LS_MINIMIZER_H
