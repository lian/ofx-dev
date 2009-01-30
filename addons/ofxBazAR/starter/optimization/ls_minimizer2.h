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
#ifndef LS_MINIMIZER2_H
#define LS_MINIMIZER2_H

// windef.h sometimes defines max. We do not want it. NOMINMAX
#ifdef max
#undef max
#endif

#include <limits>
#include <vector>
#include <cxcore.h>
#include "ls_step_solver.h"


/*! Non-linear Minimizer, modified API
*  \author Vincent Lepetit, Julien Pilet
*  \ingroup starter
*/
class ls_minimizer2
{
public:

  typedef double flt_t;
  typedef void (*callback_function)(flt_t * state, void ** user_data);

  ls_minimizer2(int state_size=0);
  ~ls_minimizer2();

  enum {MAX_B_SIZE = 4};

  /*! Base structure containing observation data for minimization.
  *  The user should create a new class inheriting from observation, 
  *  or use the predefined observation_nn with provided function 
  *  pointers.
  */
  struct observation
  {
    virtual ~observation(){}
    observation() { set_default_values(); }
    void set_default_values(void) { 
      c_max = squared_c = std::numeric_limits<flt_t>::max(); 
      c_min = -std::numeric_limits<flt_t>::max();
      confidence = 1.; 
      weight = 1.; 
      sqrt_weight = 1.; 
      ground_truth_outlier = false; 
      delete_me=false;
      array_delete_me=false;
    }
    void set_weight(flt_t w) { weight =w; sqrt_weight = w*w; }
    flt_t squared_c_current, squared_c, c_min, c_max;
    flt_t weight, sqrt_weight;
    flt_t confidence;
    flt_t *b;
    bool outlier, ground_truth_outlier, delete_me, array_delete_me;
    virtual flt_t residual(const flt_t *computed_b) const;
    virtual int get_nb_measures() const=0;
    virtual void eval_func(const flt_t *state, flt_t *b, flt_t *J, void **user_data) const =0;
    bool operator < (const observation &a) const { return confidence > a.confidence; }
  };

  //! Function pointer type used by observation_nn
  typedef void (*func_nn_ptr)(const flt_t *state, const flt_t *data, int data_size, 
    flt_t *b, flt_t *J, void **user_data);

  //! Pre-defined structure for users that prefer function pointers to class heritage.
  template <int nb_data, int nb_obs> 
  struct observation_nn : observation {
    flt_t data[nb_data];
    flt_t y[nb_obs];

    func_nn_ptr f;

    observation_nn(func_nn_ptr eval, const flt_t *d, const flt_t *b) { 
      f = eval; 
      memcpy(data, d, nb_data*sizeof(flt_t));
      memcpy(y, b, nb_obs*sizeof(flt_t));
      this->b = &y[0];
    }
    virtual ~observation_nn(){}
    virtual int get_nb_measures() const {return nb_obs;}
    virtual void eval_func(const flt_t *state, flt_t *b, flt_t *J, void **user_data) const {
      f(state, data, nb_data, b, J, user_data);
    }
    virtual flt_t residual(const flt_t *computed_b) const {
      flt_t r=0;
      for (int i=0; i<nb_obs; i++) {
        flt_t d = computed_b[i] - y[i];
        r += d*d;
      }
      return r;
    }
  };

  //! Defines the optimization space dimentionality, i.e. the number of optimized parameters.
  void set_state_size(int size);

  /*! Scale applied to each optimized parameter (each dimension of the
  * optimization space). Not used by default, but an automated method is used.
  */
  void set_scales(flt_t * scales);
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

  //! Remove some observations. a=0, b=-1 is equivalent to reset_observation.
  void erase_observations(int a, int b=-1);

  void add_observation(observation *obs, bool to_delete, bool to_array_delete);

  void add_observation_2data_1measure(func_nn_ptr f, const flt_t data[2], const flt_t goal);
  void add_observation_3data_1measure(func_nn_ptr f, const flt_t data[3], const flt_t goal);
  void add_observation_2data_2measures(func_nn_ptr f, const flt_t data[2], const flt_t goal[2]);
  void add_observation_3data_2measures(func_nn_ptr f, const flt_t data[3], const flt_t goal[2]);

  //! this callback is called at the end of every iteration
  void set_new_iteration_callback(callback_function callback);

  //! this callback is called each time the state vector changes.
  void set_state_change_callback(callback_function callback);

  /*! For robust estimation (default = +inf)
  *  residual = max( ||b-f(d,state)||^2, c^2 )
  *  This value will be applied to next added observations
  */
  void set_default_c(flt_t c);

  /*! For robust estimation (default = +inf):
  *  change the last added observation robust estimator value
  */
  void set_last_observation_c(flt_t c);

  //! For robust estimation using Julien' method (default = +inf for both):
  void set_last_observation_c_max_c_min(flt_t c_max, flt_t c_min);

  //! Set observation weight (default = 1):
  void set_last_observation_weight(flt_t weight);

  //! Set observation confidence (default = 1). Only used for PROSAC and cat tail.
  void set_last_observation_confidence(flt_t confidence);

  //! state vector
  flt_t * state;

  // ALGORITHMS:
  // Steepest descent:
  int minimize_using_steepest_descent_from(flt_t * initial_state);

  //! Levenberg-Marquardt minimization
  int minimize_using_levenberg_marquardt_from(flt_t * initial_state);
  void lm_set_max_iterations(int it);
  //! if f iterations do not decrease the function, stop.
  void lm_set_max_failures_in_a_row(int f);
  //! stop condition. Very restrictive: 0.999  less restrictive: 0.9 
  void lm_set_tol_cos(flt_t t);

  void lm_set_initial_lambda(flt_t l);

  // Gauss-Newton:
  bool minimize_using_gauss_newton_from(flt_t * initial_state);

  //! Dogleg (not convincing).
  int minimize_using_dogleg_from(flt_t * initial_state);

  /*! Cat Tail (experimental)
  * a mix between gauss-newton and line search.
  */
  int minimize_using_cattail_from(flt_t * initial_state);
  void ct_set_max_iterations(int it) {ct_max_iterations = it; }
  void set_line_search_parameters(flt_t lambda0, flt_t k_rough, flt_t k_fine);

  // Prosac
  typedef bool (*sample_consensus_func)(flt_t *computed_state, observation **obs, int nobs, void **user_data);
  flt_t minimize_using_prosac(sample_consensus_func f, int nb_samples, int min_number_of_inliers, int max_number_of_iterations);

  // Julien' method
  flt_t minimize_using_julien_method_from(const flt_t * state, int nb_steps, int nb_iterations_per_step);

  // DEBUGGING:
  /*! Checking derivatives: compares finite difference jacobian and analytical
  *  jacobian computed by the user provided functions.
  */
  void check_jacobians_around(flt_t * state, flt_t state_step);

  // Comparing with ground truth:
  void set_last_observation_as_outlier(void);
  void set_ground_truth(flt_t * state);
  void compare_outliers_with_ground_truth(void);
  void compare_state_with_ground_truth(void);

  void reserve(int max_obs) {
    alloc_matrices(max_obs);
  }

private:
  void set_default_values(void);
  void free_all();
  int real_J_size;
  void alloc_matrices(int maximum_scalar_measure_number);
  void free_matrices();
public:
  int count_measures();
private:
  inline flt_t rho(flt_t x2, flt_t c2) { return (x2 < c2) ? x2 : c2; }
  flt_t build_eps(flt_t * state, flt_t current_best_residual = std::numeric_limits<flt_t>::max(),
                  bool outliers_in_residual=true);
  int nb_inliers;
  bool build_J(flt_t * state);
  bool build_J_and_eps(flt_t * state);
  bool build_J_and_stuff(flt_t * state);
  flt_t compute_residual(flt_t * state, bool display = false);
  // !!! CALL new_iteration_callback function before calling residual !!!
  flt_t residual(flt_t * state);

  flt_t build_eps_return_inlier_residual(flt_t * state, flt_t current_best_residual = std::numeric_limits<flt_t>::max());
  flt_t inlier_residual(flt_t * state, flt_t current_best_residual);

  void show_state(int vl, flt_t * state, flt_t r);

  void set_current_c_s(flt_t k = -1.);

  flt_t * new_state, * best_state, * scales;
  int state_size;

  flt_t default_squared_c;

  //!\TODO get rid of STL here by using a linked list
  typedef std::vector<observation *> observation_vector;

  //! The vector containing all observations. Should not be modified in callbacks.
  observation_vector observations;

  CvMat * J, *newJ, * eps, * eps_previous;
  CvMat * Jt, * JtJ, * Jteps, * ds, * Jds, * aug_JtJ;
  ls_step_solver * step_solver;
  callback_function new_iteration_callback;
  callback_function state_change_callback;
  void set_new_state(const flt_t *new_state);

public:
  bool use_user_scaling, use_automated_scaling;

private:
  void * user_data[10];

  // Algorithm specific data:
  // Levenberg-Marquardt
public:
  int lm_max_iterations;
  int lm_max_failures_in_a_row;
  flt_t lm_initial_lambda;
  flt_t lm_tol_cos;
private:

  // Dog leg:
  flt_t dl_update_Delta(flt_t rho, flt_t Delta, flt_t rho_min, flt_t rho_max);
  flt_t dl_tol_cos;
  CvMat * dl_delta_diff, * dl_delta_dl, * dl_delta_sd, * dl_delta_gn;
  CvMat * JtJdelta, * JJteps;

  // Cat tail:
  bool line_search(CvMat * dir, flt_t lambda_min, flt_t lambda_max, flt_t current_residual, flt_t & new_residual, flt_t & new_lambda);
  CvMat * ct_delta_gn, * ct_delta_sd;
  int ct_max_iterations;
  flt_t ct_k_rough, ct_k_fine, ct_lambda0;

  // Prosac:
  bool pick_random_indices(int *idx, int nb, int max_index);

  // Julien' method:
  bool inside_julien_method;

  // For debugging:
public:
  int verbose_level;
private:
  flt_t * ground_truth_state;
};

#endif // LS_MINIMIZER_H
