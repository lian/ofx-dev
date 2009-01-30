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
#include <iomanip>
#include <algorithm>

#include "../math/mcvm.h"
#include "../math/polynom_solver.h"
#include "ls_minimizer2.h"

using namespace std;

#define msg(level, M) (level <= verbose_level) ? (cout << M) : (cout << "")

ls_minimizer2::ls_minimizer2(int state_size)
{
  state=0;
  new_state=0;
  best_state=0;
  scales=0;
  step_solver=0;
  ground_truth_state=0;
  J=0;
  use_user_scaling = false;
  use_automated_scaling = true;
  new_iteration_callback = 0;
  state_change_callback = 0;
  set_default_values();
  set_state_size(state_size);
}

void ls_minimizer2::set_state_size(int state_size)
{
  free_all();
  if (state_size<=0) return;

  this->state_size = state_size;
  state = new flt_t[state_size];
  new_state = new flt_t[state_size];
  best_state = new flt_t[state_size];
  scales = new flt_t[state_size];
  for(int i = 0; i < state_size; i++)
    scales[i] = 1.;
}

void ls_minimizer2::alloc_matrices(int maximum_scalar_measure_number)
{
  assert(state_size>0);
  assert(maximum_scalar_measure_number>0);

  if (J && real_J_size>=maximum_scalar_measure_number) {
	  step_solver->resize(state_size, maximum_scalar_measure_number);
	  return;
  }

  free_matrices();
  step_solver = new ls_step_solver(state_size, maximum_scalar_measure_number);
  real_J_size = maximum_scalar_measure_number;
  J = cvCreateMat(maximum_scalar_measure_number, state_size, CV_64F);
  newJ = cvCreateMat(maximum_scalar_measure_number, state_size, CV_64F);
  eps = cvCreateMat(maximum_scalar_measure_number, 1, CV_64F);
  eps_previous = cvCreateMat(maximum_scalar_measure_number, 1, CV_64F);
  //Jt = cvCreateMat(state_size, maximum_scalar_measure_number, CV_64F);
  JtJ = cvCreateMat(state_size, state_size, CV_64F);
  Jteps = cvCreateMat(state_size, 1, CV_64F);
  ds = cvCreateMat(state_size, 1, CV_64F);
  Jds = cvCreateMat(maximum_scalar_measure_number, 1, CV_64F);

  // For Levenberg-Marquardt:
  aug_JtJ = cvCreateMat(state_size, state_size, CV_64F);

  // For Dog Leg:
  dl_delta_sd   = cvCreateMat(state_size, 1, CV_64F);
  dl_delta_gn   = cvCreateMat(state_size, 1, CV_64F);
  dl_delta_dl   = cvCreateMat(state_size, 1, CV_64F);
  dl_delta_diff = cvCreateMat(state_size, 1, CV_64F);
  JtJdelta      = cvCreateMat(state_size, 1, CV_64F);
  JJteps = cvCreateMat(maximum_scalar_measure_number, 1, CV_64F);

  // For Cat Tail:
  ct_delta_gn   = cvCreateMat(state_size, 1, CV_64F);
  ct_delta_sd   = cvCreateMat(state_size, 1, CV_64F);

}

ls_minimizer2::~ls_minimizer2() {
  free_all();
}

void ls_minimizer2::free_all()
{
  if (state) {
    delete[] state;
    delete[] new_state;
    delete[] best_state;
    delete[] scales;
    delete[] ground_truth_state;
  }
  free_matrices();
}

void ls_minimizer2::free_matrices()
{
  if (step_solver) delete step_solver;
  step_solver=0;

  if (J==0) return;

  cvReleaseMat(&J);
  cvReleaseMat(&newJ);
  cvReleaseMat(&eps);
  cvReleaseMat(&eps_previous);
  //cvReleaseMat(&Jt);
  cvReleaseMat(&JtJ);
  cvReleaseMat(&Jteps);
  cvReleaseMat(&ds);
  cvReleaseMat(&Jds);

  cvReleaseMat(&aug_JtJ);
  cvReleaseMat(&dl_delta_sd);
  cvReleaseMat(&dl_delta_gn);
  cvReleaseMat(&dl_delta_dl);
  cvReleaseMat(&dl_delta_diff);
  cvReleaseMat(&JtJdelta);
  cvReleaseMat(&JJteps);

  cvReleaseMat(&ct_delta_gn);
  cvReleaseMat(&ct_delta_sd);
}

void ls_minimizer2::set_user_data(int slot_index, void * ptr)
{
  assert((unsigned)slot_index< 10);
  user_data[slot_index] = ptr;
}


void ls_minimizer2::set_scales(flt_t * scales)
{
  flt_t norm = 0;
  for(int i = 0; i < state_size; i++)
    norm += scales[i] * scales[i];
  norm = sqrt(norm);

  for(int i = 0; i < state_size; i++)
    this->scales[i] = scales[i] / (state_size * norm);

  use_user_scaling = true;
}

void ls_minimizer2::set_default_values(void)
{
  set_verbose_level(0);

  default_squared_c = numeric_limits<flt_t>::max();

  lm_set_initial_lambda(0);
  lm_set_max_iterations(50);
  lm_set_max_failures_in_a_row(10);
  lm_set_tol_cos(1e-5);

  ct_set_max_iterations(50);
  set_line_search_parameters(1e-3, 5, 1.2);

  inside_julien_method = false;
}

void ls_minimizer2::set_verbose_level(int vl)
{
  verbose_level = vl;
}

void ls_minimizer2::lm_set_max_iterations(int it)
{
  lm_max_iterations = it;
}

void ls_minimizer2::lm_set_max_failures_in_a_row(int f)
{
  lm_max_failures_in_a_row = f;
}

void ls_minimizer2::lm_set_tol_cos(flt_t t)
{
  lm_tol_cos = t;
}

void ls_minimizer2::lm_set_initial_lambda(flt_t l)
{
  lm_initial_lambda = l;
}

void ls_minimizer2::set_line_search_parameters(flt_t lambda0, flt_t k_rough, flt_t k_fine)
{
  ct_lambda0 = lambda0;
  ct_k_rough = k_rough;
  ct_k_fine = k_fine;
}


void ls_minimizer2::set_ground_truth(flt_t * state)
{
  // For debugging:
  if(ground_truth_state) delete[] ground_truth_state;
  ground_truth_state = new flt_t[state_size];
  for(int i = 0; i < state_size; i++)
    ground_truth_state[i] = state[i];
}

void ls_minimizer2::set_new_iteration_callback(callback_function callback)
{
  new_iteration_callback = callback;
}

void ls_minimizer2::set_state_change_callback(callback_function callback)
{
  state_change_callback = callback;
}

void ls_minimizer2::reset_observations(void) {
  erase_observations(0);
}

void ls_minimizer2::erase_observations(int a, int b)
{
  assert(b<0 || (a<=b));
  if (a >= (signed)observations.size()) return;
  observation_vector::iterator first = observations.begin()+a;
  observation_vector::iterator last = (b<0 ? observations.end() : observations.begin()+b);
  for (observation_vector::iterator it = first; it != last; ++it)
  {
    if ((*it)->delete_me) delete *it;
    else if ((*it)->array_delete_me) delete[] *it;
  }
  observations.erase(first,last);
  assert(a == (signed)observations.size());
}

void ls_minimizer2::set_default_c(flt_t c)
{
  default_squared_c = c * c;
}

void ls_minimizer2::add_observation(observation *obs, bool to_delete, bool to_array_delete)
{
  assert(!(to_delete && to_array_delete));

  //if (obs->weight <=0) return;

  obs->sqrt_weight = obs->weight*obs->weight;
  obs->delete_me = to_delete;
  obs->array_delete_me = to_array_delete;
  observations.push_back(obs);
}

void ls_minimizer2::set_last_observation_c(flt_t c)
{
  observation *o = observations.back();
  assert(o!=0);

  o->squared_c = c*c;
}

void ls_minimizer2::set_last_observation_c_max_c_min(flt_t c_max, flt_t c_min)
{
  observation *o = observations.back();
  assert(o!=0);
  o->c_min = c_min;
  o->c_max = c_max;
}

void ls_minimizer2::set_last_observation_weight(flt_t weight)
{
  observation *o = observations.back();
  assert(o!=0);
  o->weight = weight;
  o->sqrt_weight = sqrt(weight);
}

void ls_minimizer2::set_last_observation_confidence(flt_t confidence)
{
  observation *o = observations.back();
  assert(o!=0);
  o->confidence = confidence;
}

void ls_minimizer2::set_last_observation_as_outlier(void)
{
  observation *o = observations.back();
  assert(o!=0);
  o->outlier = true;
}

ls_minimizer2::flt_t ls_minimizer2::observation::residual(const flt_t *computed_b) const
{
  int n = get_nb_measures();
  flt_t r=0;
  for (int i=0; i<n; i++) {
    flt_t d = computed_b[i] - b[i];
    r += d*d;
  }
  return r;
}

ls_minimizer2::flt_t ls_minimizer2::residual(flt_t * state)
{
  flt_t result = 0.;

  flt_t b[MAX_B_SIZE];

  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    observation *obs = *it;
    obs->eval_func(state, b, 0, user_data);
    result += obs->weight*rho(obs->residual(b), obs->squared_c);
  }
  return result;
}

void ls_minimizer2::compare_state_with_ground_truth(void)
{
  if (ground_truth_state==0) return;
  cout << endl;
  cout << "FOUND: ";
  compute_residual(state, true);
  cout << "GROUND TRUTH: ";
  compute_residual(ground_truth_state, true);

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);
}

void ls_minimizer2::compare_outliers_with_ground_truth(void)
{
  int correct_inlier_number = 0, correct_outlier_number = 0;

  flt_t b[MAX_B_SIZE];

  int gt_inliers = 0;

  int observation_number = 0;
  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    observation *o = *it;
    o->eval_func(state, b, 0, user_data);
    flt_t diff = o->residual(b);

    if (diff < o->squared_c && !o->ground_truth_outlier)
      correct_inlier_number++;
    else if (diff >= o->squared_c && o->ground_truth_outlier)
      correct_outlier_number++;

    if (!o->ground_truth_outlier) gt_inliers++;
    ++observation_number;
  }


  cout << endl;
  cout << (100.0 * correct_inlier_number)  / gt_inliers << "% inliers and ";
  cout << (100.0 * correct_outlier_number) / (observation_number - gt_inliers) << "% outliers correctly found.";
  cout << endl;
}

ls_minimizer2::flt_t ls_minimizer2::build_eps(flt_t * state, flt_t current_best_residual, bool outliers_in_residual)
{
  int im_n = 0;
  flt_t residual = 0;

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);

  flt_t b[MAX_B_SIZE];
  /*flt_t diff[MAX_B_SIZE];*/
  nb_inliers = 0;
  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    observation *o = *it;
    o->eval_func(state, b, newJ->data.db + im_n*state_size, user_data);

    flt_t res = o->residual(b);
    assert(res >= 0);
    assert(o->squared_c>=0);
    int n = o->get_nb_measures();
    if (res < o->squared_c)
    {
      o->outlier = false;
      nb_inliers++;
      if (o->weight != 1.) {
        for(int j = 0; j < n*state_size; j++) 
          (newJ->data.db + im_n * state_size)[j] *= o->sqrt_weight;
      }
      for (int i=0; i<n; ++i)
        eps->data.db[im_n+i] = o->sqrt_weight * (o->b[i] - b[i]);
      im_n+=n;
      residual += o->weight * res;
      assert(o->weight >=0);
    }
    else
    {
      o->outlier = true;
      if (outliers_in_residual)
        residual += o->weight * o->squared_c;
    }

    if (residual > current_best_residual) {
      eps->rows = 0;
      newJ->rows = 0;
      return numeric_limits<flt_t>::max();
    }
  }

  eps->rows = im_n;
  newJ->rows = im_n;
  return residual;
}

ls_minimizer2::flt_t ls_minimizer2::build_eps_return_inlier_residual(flt_t * state, flt_t current_best_residual)
{
  return build_eps(state, current_best_residual, false);
}

ls_minimizer2::flt_t ls_minimizer2::inlier_residual(flt_t * state, flt_t current_best_residual)
{
  flt_t residual = 0;

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);

  flt_t b[MAX_B_SIZE];

  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    observation *obs = *it;
    if (!obs->outlier) {
      obs->eval_func(state, b, 0, user_data);
      residual += obs->weight * obs->residual(b);
      if (residual > current_best_residual) return numeric_limits<flt_t>::max();
    }
  }

  return residual;
}

bool ls_minimizer2::build_J(flt_t * state)
{
  int im_n = 0;

  flt_t b[MAX_B_SIZE];
  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    observation *obs = *it;
    if (!obs->outlier) {
      int n = obs->get_nb_measures();
      assert(im_n+n <= real_J_size);
      obs->eval_func(state, b, J->data.db + im_n*state_size, user_data);
      if (obs->weight != 1.) for(int j = 0; j < n*state_size; j++) 
        (J->data.db + im_n * state_size)[j] *= obs->sqrt_weight;
      im_n += n;
    }
  }

  J->rows = im_n;

  return true;
}

ls_minimizer2::flt_t ls_minimizer2::compute_residual(flt_t * state, bool display)
{
  if (display)
    for(int i = 0; i < state_size; i++)
      cout << state[i] << " " << flush;

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);

  flt_t result = residual(state);
  if (display)
    cout << " -> " << result << endl;

  return result;
}

void ls_minimizer2::show_state(int vl, flt_t * state, flt_t r)
{
  for(int i = 0; i < state_size; i++) {
    msg(vl, state[i]);
    if (i < state_size - 1)
      msg(vl, ", ");
  }
  msg(vl, " --> " << setprecision(20) << r << setprecision(6) << endl);
}

bool ls_minimizer2::build_J_and_stuff(flt_t * state)
{
  //build_J(state);
  // Julien: build_eps computed newJ
  CvMat *tmp = J;
  J = newJ;
  newJ = tmp;

  if (J->rows == 0)
  {
    msg(0, "**: No inliers found" << endl);
    return false;
  }
  //Jt->cols = J->rows;
  // Jteps = Jt * eps
  cvGEMM(J, eps, 1, 0, 1, Jteps, CV_GEMM_A_T);
  cvMulTransposed(J, JtJ, 1);

  return true;
}

void ls_minimizer2::set_current_c_s(flt_t k)
{
  if (k < 0)
  {
    if (inside_julien_method) return;
    for (observation_vector::iterator it = observations.begin();
      it != observations.end(); ++it)
    {
      observation *o = *it;
      o->squared_c_current = o->squared_c;
    }
  }
  else
  {
    for (observation_vector::iterator it = observations.begin();
      it != observations.end(); ++it)
    {
      observation *o = *it;
      flt_t c = exp(k * log(o->c_max) + (1. - k) * log(o->c_min));
      o->squared_c_current = c * c;
    }
  }
}

int ls_minimizer2::count_measures()
{
  int n=0;
  int nobs=0;
  if (observations.size()==0) return 0;

  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    n += (*it)->get_nb_measures();
    nobs++;
  }
  msg(2,nobs << " obs, " << n << " measures"<<endl);
  return n;
}

/*!
\return an error code <0 if something went wrong. 
2: unable to improve result after N iterations.
3: termination criterion reached.
4: iterations limit exceeded.
*/
int ls_minimizer2::minimize_using_levenberg_marquardt_from(flt_t * initial_state)
{
  msg(1, "LM: Beginning optimization using Levenberg-Marquardt:" << endl);

  alloc_matrices(count_measures());

  assert(step_solver!=0);
  set_new_state(initial_state);
  assert(step_solver!=0);

  double *state = new flt_t[state_size];
  memcpy(state, initial_state, state_size*sizeof(flt_t));

  set_current_c_s();

  flt_t lambda = lm_initial_lambda, rho = 0., cosinus = 0.;
  int iter_nb = 0, failures_in_a_row = 0;
  int reason = 0;
  flt_t r_previous = build_eps(state), r=0.;

  eps_previous->rows = eps->rows; cvCopy(eps, eps_previous);
  build_J_and_stuff(state);
  cvCopy(JtJ, aug_JtJ);

  msg(1, "LM: "); show_state(1, state, r_previous);

  while(iter_nb < lm_max_iterations)
  {
    iter_nb++;
    msg(2, "LM: iteration # " << iter_nb << " --------------------------------------------" << endl);

    do {
      for(int i = 0; i < state_size; i++)
        if (use_user_scaling)
          aug_JtJ->data.db[i * state_size + i] = JtJ->data.db[i * state_size + i] + lambda * scales[i];
        else if (use_automated_scaling)
          aug_JtJ->data.db[i * state_size + i] = JtJ->data.db[i * state_size + i] +
          lambda * (1 + JtJ->data.db[i * state_size + i] * JtJ->data.db[i * state_size + i]);
        else
          aug_JtJ->data.db[i * state_size + i] = JtJ->data.db[i * state_size + i] + lambda;

        assert(aug_JtJ->cols == state_size && state_size == aug_JtJ->rows);

        if (!step_solver->qr_solve(aug_JtJ, Jteps, ds)) {
          reason = -1;
          goto lm_end;
        }

        assert(aug_JtJ->cols == state_size && state_size == aug_JtJ->rows);

        //! Julien new_state actually contains the old state
        for(int i = 0; i < state_size; i++) {
          new_state[i] = state[i];
          state[i] = state[i] + ds->data.db[i];
        }

        set_new_state(state);
        r = build_eps(state);
        rho = r_previous - r;      
        if (rho > 0) {
          rho /= lambda * cvDotProduct(ds, ds) + cvDotProduct(ds, Jteps);

          Jds->rows = J->rows;
          cvMatMul(J, ds, Jds);
          cosinus = cvDotProduct(eps_previous, Jds) / (sqrt(r_previous) * sqrt(cvDotProduct(Jds, Jds)));
          msg(2, "LM: cosinus = " << cosinus << endl);
          if (cosinus < lm_tol_cos) {
            reason = 3;
            goto lm_end;
          }
          eps_previous->rows = eps->rows; cvCopy(eps, eps_previous);

          build_J_and_stuff(state);
          cvCopy(JtJ, aug_JtJ);
          r_previous = r;
          lambda = lambda / 10; 

          failures_in_a_row = 0;
          msg(2, "LM: iteration succeeded: new lambda = " << lambda << endl);
          msg(2, "LM: "); show_state(2, state, r);
          if (verbose_level >= 3) { compare_outliers_with_ground_truth(); compare_state_with_ground_truth(); }
        }
        else {
          memcpy(state, new_state, state_size*sizeof(flt_t));
          failures_in_a_row++;
          if (failures_in_a_row > lm_max_failures_in_a_row) {
            reason = 2;
            goto lm_end;
          }
          if (lambda == 0) lambda = 1e-3; else lambda *= 10;

          msg(2, "LM: iteration failed --> " << r << "   new lambda = " << lambda << endl);
        }
    } while(rho < 0);
  }
lm_end:
  if (iter_nb >= lm_max_iterations)
    reason = 4;

  switch(reason) {
    case 2: msg(1, "LM: " << failures_in_a_row << " failures in a row." << endl); break;
    case 3: msg(1, "LM: Termination criterion satisfied: cosinus = " << cosinus << " < " << lm_tol_cos << endl);
      break;
    case 4: msg(1, "LM: Too many iterations." << endl); break;
    case -1: msg(1, "LM: qr_solve failed\n"); break;
    default:
      msg(1, "LM: unkown termination reason" << endl);
  }

  msg(1, "LM: ");
  for(int i = 0; i < state_size; i++)
  {
    msg(1, state[i]);
    if (i < state_size - 1)
      msg(1, ", ");
  }
  msg(1, " --> " << r << endl);
  msg(1, "LM: End of minimization." << endl);

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);

  delete[] state;
  return reason;
}

void ls_minimizer2::set_new_state(const flt_t *new_state)
{
  if (memcmp(new_state, state, sizeof(flt_t)*state_size)==0) return;
  for(int i = 0; i < state_size; i++) state[i] = new_state[i];
  if (state_change_callback) state_change_callback(state, user_data);
}

ls_minimizer2::flt_t ls_minimizer2::dl_update_Delta(flt_t rho, flt_t Delta, flt_t rho_min, flt_t rho_max)
{
  if (rho < rho_min) return Delta / 2;
  if (rho > rho_max) return Delta * 2;
  return rho;
}

int ls_minimizer2::minimize_using_dogleg_from(flt_t * initial_state)
{
  msg(1, "DL: Beginning optimization using Dog Leg algorithm:" << endl);

  alloc_matrices(count_measures());

  set_new_state(initial_state);

  set_current_c_s();

  flt_t Delta = 10000., rho = 0., cosinus = 0.;
  flt_t dl_delta_gn_computed = false;
  int iter_nb = 0, failures_in_a_row = 0;
  int reason = 0;

  flt_t r_previous = build_eps(state), r = 0.;
  eps_previous->rows = eps->rows; cvCopy(eps, eps_previous);
  build_J_and_stuff(state);

  msg(1, "DL: "); show_state(1, state, r_previous);

  while(iter_nb < lm_max_iterations)
  {
    iter_nb++;
    msg(2, "DL: iteration # " << iter_nb << " --------------------------------------------" << endl);

    JJteps->rows = J->rows;
    cvMatMul(J, Jteps, JJteps);
    cvScale(Jteps, dl_delta_sd, cvDotProduct(Jteps, Jteps) / cvDotProduct(JJteps, JJteps));

    dl_delta_gn_computed = false;

    do {
      msg(2, "DL: Delta = " << Delta << endl);
      if (cvDotProduct(dl_delta_sd, dl_delta_sd) > Delta * Delta)
      {
        cvScale(dl_delta_sd, dl_delta_dl, Delta / cvDotProduct(dl_delta_sd, dl_delta_sd));
        msg(2, "DL: Trying truncated steepest descent step" << endl);
      }
      else {
        if (!dl_delta_gn_computed) {
          step_solver->qr_solve(JtJ, Jteps, dl_delta_gn);
          //          step_solver->qr_solve(J, eps, dl_delta_gn);
          dl_delta_gn_computed = true;
        }
        if (cvDotProduct(dl_delta_gn, dl_delta_gn) <= Delta * Delta)
        {
          cvCopy(dl_delta_gn, dl_delta_dl);

          msg(2, "DL: Trying gauss-newton step" << endl);
        }
        else {
          cvSub(dl_delta_gn, dl_delta_sd, dl_delta_diff);
          flt_t beta1, beta2, beta;
          solve_deg2(cvDotProduct(dl_delta_diff, dl_delta_diff), 
            2 * cvDotProduct(dl_delta_sd, dl_delta_diff), 
            cvDotProduct(dl_delta_sd, dl_delta_sd) - Delta * Delta,
            beta1, beta2);
          beta = (beta1 > 0) ? beta1 : beta2;
          cvScaleAdd(dl_delta_diff, cvScalar(beta), dl_delta_sd, dl_delta_dl);

          msg(2, "DL: Trying truncated gauss-newton step" << endl);
        }
      }
      for(int i = 0; i < state_size; i++) new_state[i] = state[i] + dl_delta_dl->data.db[i];
      //! TODO looks wrong..
      r = build_eps(new_state);
      cvMatMul(JtJ, dl_delta_dl, JtJdelta);
      flt_t L_delta = 2 * ( 0.5 * r_previous - cvDotProduct(Jteps, dl_delta_dl) + 0.5 * cvDotProduct(dl_delta_dl, JtJdelta));
      rho = (r_previous - r) / (r_previous - L_delta);
      if (rho > 0) {
        set_new_state(new_state);
        Jds->rows = J->rows;
        cvMatMul(J, dl_delta_dl, Jds);
        cosinus = cvDotProduct(eps_previous, Jds) / (sqrt(r_previous) * sqrt(cvDotProduct(Jds, Jds)));
        msg(2, "DL: cosinus = " << cosinus << endl);
        if (cosinus < dl_tol_cos) {
          reason = 3;
          goto dl_end;
        }
        eps_previous->rows = eps->rows; cvCopy(eps, eps_previous);
        r_previous = r;
        build_J_and_stuff(state);

        failures_in_a_row = 0;
        msg(2, "DL: "); show_state(2, state, r);
        if (verbose_level >= 3) { compare_outliers_with_ground_truth(); compare_state_with_ground_truth(); }
      }
      else {
        msg(2, "DL:  -> failure." << endl);

        failures_in_a_row++;
        if (failures_in_a_row > lm_max_failures_in_a_row) {
          reason = 2;
          goto dl_end;
        }
      }
      Delta = dl_update_Delta(rho, Delta, 0.25, 0.75);
    } while(rho < 0);
  }
dl_end:
  if (iter_nb >= lm_max_iterations)
    reason = 4;

  if (reason == 2) msg(1, "DL: " << failures_in_a_row << " failures in a row." << endl);
  if (reason == 3) msg(1, "DL: Termination criterion satisfied: cosinus = " << cosinus << " < " << lm_tol_cos << endl);
  if (reason == 4) msg(1, "DL: Too many iterations." << endl);

  msg(1, "DL: ");
  for(int i = 0; i < state_size; i++)
  {
    msg(1, state[i]);
    if (i < state_size - 1)
      msg(1, ", ");
  }
  msg(1, " --> " << r << endl);
  msg(1, "DL: End of minimization." << endl);

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);

  return reason;
}

bool ls_minimizer2::line_search(CvMat * dir, 
                                flt_t lambda_min, flt_t lambda_max, 
                                flt_t residual0, flt_t & new_residual, flt_t & new_lambda)
{
  lambda_min = lambda_max = 0.; // 

  alloc_matrices(count_measures());

  static flt_t lambda = ct_lambda0;
  for(int i = 0; i < state_size; i++) new_state[i] = state[i] + lambda * dir->data.db[i];
  flt_t residual_lambda = inlier_residual(new_state, residual0);
  flt_t old_residual = residual_lambda;

  while(residual_lambda > residual0)
  {
    msg(2, " LS: rough search lambda = " << lambda << endl);
    lambda /= ct_k_rough;
    for(int i = 0; i < state_size; i++) new_state[i] = state[i] + lambda * dir->data.db[i];
    old_residual = residual_lambda;
    residual_lambda = inlier_residual(new_state, residual0);
  }

  while(residual_lambda < residual0)
  {
    msg(2, " LS: rough search lambda = " << lambda << endl);
    residual0 = residual_lambda;
    lambda *= ct_k_rough;
    for(int i = 0; i < state_size; i++) new_state[i] = state[i] + lambda * dir->data.db[i];
    old_residual = residual_lambda;
    residual_lambda = inlier_residual(new_state, old_residual);
  }
  lambda /= ct_k_rough;
  residual_lambda = old_residual;
  for(int i = 0; i < state_size; i++) new_state[i] = state[i] + lambda * dir->data.db[i];

  bool found = false;
  while(residual_lambda < new_residual)
  {
    msg(2, " LS: fine  search lambda = " << lambda << endl);
    new_residual = residual_lambda;
    memcpy(best_state, new_state, state_size * sizeof(flt_t));
    new_lambda = lambda;
    found = true;

    lambda *= ct_k_fine;
    for(int i = 0; i < state_size; i++) new_state[i] = state[i] + lambda * dir->data.db[i];
    residual_lambda = build_eps(new_state, new_residual);
  }

  return found;
}

bool confidence_cmp(const ls_minimizer2::observation *a, const ls_minimizer2::observation *b)
{
  return a->confidence > b->confidence;
}

int ls_minimizer2::minimize_using_cattail_from(flt_t * initial_state)
{
  msg(1, "CT: Beginning optimization using Cat Tail algorithm:" << endl);

  alloc_matrices(count_measures());

  sort(observations.begin(), observations.end(), confidence_cmp);
  //observations.sort();

  memcpy(state, initial_state, state_size * sizeof(flt_t));

  set_current_c_s();

  flt_t r;
  int iter_nb = 0;
  int reason;
  do
  {
    if (verbose_level >= 3) { msg(3, "CT: "); compare_state_with_ground_truth(); }

    r = build_eps_return_inlier_residual(state);
    flt_t best_r = r;
    build_J_and_stuff(state);

    msg(2, "CT " << nb_inliers << " inliers." << endl);

    int method = -1;
    flt_t best_lambda, gain = 0.;

    step_solver->qr_solve(J, eps, ct_delta_gn);
    for(int i = 0; i < state_size; i++) best_state[i] = state[i] + ct_delta_gn->data.db[i];
    flt_t r_gn = inlier_residual(best_state, best_r);
    if (r_gn < best_r)
    {
      gain = r - r_gn;
      best_r = r_gn;
      method = 1;
    }

    for(int i = 0; i < state_size; i++) ct_delta_sd->data.db[i] = Jteps->data.db[i] / JtJ->data.db[i * state_size + i];
    if (line_search(ct_delta_sd, 0.0001, 1, r, best_r, best_lambda))
    {
      gain = r - best_r;
      method = 2;
    }

    if (method == -1)
    {
      reason = 2;
      goto ct_end;
    }
    else if (method == 1)
      msg(2, "CT: Taking the gauss-newton step." << endl);
    else if (method == 2)
      msg(2, "CT: Taking the corrected linear model step (lambda = " << best_lambda << ")." << endl);
    else 
    {
      cerr << "bug in ls_minimizer2::minimize_using_cattail_from" << endl;
      exit(0);
    }

    msg(2, "CT: Gain = " << gain << " --> residual = " << best_r << endl);
    memcpy(state, best_state, state_size * sizeof(flt_t));

    r = best_r;
    iter_nb++;
    //////////////////////////////////////////////////////////////////////////////////////
  } while(iter_nb < ct_max_iterations);
  reason = 4;

ct_end:
  if (reason == 2) msg(2, "CT: no improvement found." << endl);
  if (reason == 4) msg(2, "CT: Too many iterations (" << ct_max_iterations << ")." << endl);

  msg(1, "CT: ");
  for(int i = 0; i < state_size; i++)
  {
    msg(1, state[i]);
    if (i < state_size - 1)
      msg(1, ", ");
  }
  msg(1, " --> " << r << endl);
  msg(1, "CT: End of minimization." << endl);

  if (new_iteration_callback != 0) new_iteration_callback(state, user_data);

  return 4;
}

bool ls_minimizer2::pick_random_indices(int *idx, int n, int max_index)
{

  if ( n > max_index ) return false;

  for (int i=0; i<n; i++) {
    idx[i] = rand()%max_index;

    for (int j=0; j<i; j++)
      if (idx[i]==idx[j]) {
        --i;
        break;
      }
  }
  return true;
}

static inline unsigned mymin(unsigned a, unsigned b) {
  return (a>b? b : a);
}

ls_minimizer2::flt_t ls_minimizer2::minimize_using_prosac(sample_consensus_func f, 
                                                          int nb_samples,
                                                          int min_number_of_inliers, int max_number_of_iterations)
{
  alloc_matrices(count_measures());

  sort(observations.begin(), observations.end(), confidence_cmp);
  //observations.sort();

  /*flt_t b[MAX_B_SIZE];*/
  flt_t best_residual = numeric_limits<flt_t>::max();
  int *idx = new int[nb_samples];
  observation **o = new observation *[nb_samples];
  for(int iter = 0; iter < max_number_of_iterations; iter++)
  {
    if (!pick_random_indices(idx, nb_samples, mymin(iter + nb_samples, observations.size())))
    {
      cerr << "PR: not enough observations." << endl;
      return false;
    }

    for (int i=0; i<nb_samples; i++) {
      //o[i] = observations[idx[i]];
      observation_vector::iterator it=observations.begin();
      for (int j=0; j<idx[i]; ++i) ++it;
      o[i] = *it;
    }

    //! TODO <Julien> I modified this. It may be wrong.
    if (f(new_state, o, nb_samples, user_data))
    {
      set_new_state(new_state);
      flt_t new_residual = build_eps(state, best_residual);
      if (new_residual < best_residual)
      {
        best_residual = new_residual;
        memcpy(best_state, state, state_size * sizeof(flt_t));
        int nb_inliers = 0;
        for (observation_vector::iterator it = observations.begin();
          it != observations.end(); ++it)
        {
          if (!(*it)->outlier)
            nb_inliers++;
        }
        if (nb_inliers > min_number_of_inliers)
          break;
      }
    }
  }

  delete[] o;
  delete[] idx;

  memcpy(state, best_state, state_size * sizeof(flt_t));
  return best_residual;
}

ls_minimizer2::flt_t ls_minimizer2::minimize_using_julien_method_from(const flt_t * initial_state, int nb_steps, int nb_iterations_per_step)
{
  alloc_matrices(count_measures());
  inside_julien_method = true;
  ct_set_max_iterations(nb_iterations_per_step);

  memcpy(state, initial_state, state_size * sizeof(flt_t));

  for(int i = 0; i < nb_steps; i++)
  {
    msg(2, endl);
    msg(2, "-----------------------------------------------------------------" << endl);
    msg(2, " STEP # " << i << " / " << nb_steps << endl);
    msg(2, "-----------------------------------------------------------------" << endl);
    set_current_c_s(1. - flt_t(i) / (nb_steps - 1));
    minimize_using_cattail_from(state);
  }

  ct_set_max_iterations(50);
  minimize_using_cattail_from(state);

  inside_julien_method = false;

  return 0;
}

void ls_minimizer2::check_jacobians_around(flt_t * state0, flt_t state_step)
{
  alloc_matrices(count_measures());
  flt_t b0[MAX_B_SIZE];
  flt_t b[MAX_B_SIZE];

  int obsnb=0;

  for (observation_vector::iterator it = observations.begin();
    it != observations.end(); ++it)
  {
    cout << "OBS #" << obsnb++ << endl;

    observation *o = *it;
    int n = o->get_nb_measures();
    flt_t * J = new flt_t[n * state_size];
    set_new_state(state0);
    o->eval_func(state, b0, J, user_data);

    for(int j = 0; j < state_size; j++)
    {
      for(int k = 0; k < state_size; k++)
        new_state[k] = state0[k];
      new_state[j] += state_step;

      set_new_state(new_state);

      o->eval_func(state, b, 0, user_data);
      for (int i=0; i<n; i++) {
        flt_t analytic = J[i*state_size + j];
        flt_t numeric = (b[i] - b0[i])/state_step;

        cout << " (df" << i << "/ds" << j << ") = " 
          << analytic << " = " << numeric << endl;
      }
    }

    delete [] J;
  }
}

void ls_minimizer2::add_observation_2data_1measure(func_nn_ptr f, const flt_t data[2], const flt_t goal)
{
  observation_nn<2,1> *o = new observation_nn<2,1>(f, data, &goal);
  o->set_default_values();
  add_observation(o, true, false);
}

void ls_minimizer2::add_observation_3data_1measure(func_nn_ptr f, const flt_t data[3], const flt_t goal)
{
  observation_nn<3,1> *o = new observation_nn<3,1>(f, data, &goal);
  o->set_default_values();
  add_observation(o, true, false);
}

void ls_minimizer2::add_observation_2data_2measures(func_nn_ptr f, const flt_t data[2], const flt_t goal[2])
{
  observation_nn<2,2> *o = new observation_nn<2,2>(f, data, goal);
  o->set_default_values();
  add_observation(o, true, false);
}

void ls_minimizer2::add_observation_3data_2measures(func_nn_ptr f, const flt_t data[3], const flt_t goal[2])
{
  observation_nn<3,2> *o = new observation_nn<3,2>(f, data, goal);
  o->set_default_values();
  add_observation(o, true, false);
}
