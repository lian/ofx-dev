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
#include <cmath>
#include <iostream>
#include <fstream>
#include <float.h>

#include "../math/linear_algebra.h"
#include "projection_matrix.h"

using namespace std;

projection_matrix::projection_matrix(void)
{
  planes[0] = 0;
  planes[1] = 0;
  planes[2] = 100;
  planes[3] = 0;
  planes[4] = -100;
  planes[5] = 10000;
}

projection_matrix::~projection_matrix()
{
}

projection_matrix &projection_matrix::operator=(const projection_matrix &copied)
{
  cx = copied.cx;
  cy = copied.cy;
  fx = copied.fx;
  fy = copied.fy;

  image_width = copied.image_width;
  image_height = copied.image_height;

  original_cx = copied.original_cx;
  original_cy = copied.original_cy;
  original_fx = copied.original_fx;
  original_fy = copied.original_fy;

  original_image_width = copied.original_image_width;
  original_image_height = copied.original_image_height;

  gfla_copy_3x3(copied.R, R);
  gfla_copy_3(copied.T, T);

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;

  return *this;
}

void projection_matrix::getAAt(const double P[3][4], double AAt[3][3])
{
  double t7 = P[0][0]*P[0][0];
  double t8 = P[0][1]*P[0][1];
  double t9 = P[0][2]*P[0][2];
  double t14 = P[0][0]*P[1][0]+P[0][1]*P[1][1]+P[0][2]*P[1][2];
  double t18 = P[0][0]*P[2][0]+P[0][1]*P[2][1]+P[0][2]*P[2][2];
  double t19 = P[1][0]*P[1][0];
  double t20 = P[1][1]*P[1][1];
  double t21 = P[1][2]*P[1][2];
  double t26 = P[1][0]*P[2][0]+P[1][1]*P[2][1]+P[1][2]*P[2][2];
  double t27 = P[2][0]*P[2][0];
  double t28 = P[2][1]*P[2][1];
  double t29 = P[2][2]*P[2][2];
  AAt[0][0] = t7+t8+t9;
  AAt[0][1] = t14;
  AAt[0][2] = t18;
  AAt[1][0] = t14;
  AAt[1][1] = t19+t20+t21;
  AAt[1][2] = t26;
  AAt[2][0] = t18;
  AAt[2][1] = t26;
  AAt[2][2] = t27+t28+t29;
}

void projection_matrix::set_3x4_matrix(double P[3][4], int w, int h)
{
  image_width  = w;
  image_height = h;

  double inv_l = sqrt(P[2][0] * P[2][0] + P[2][1] * P[2][1] + P[2][2] * P[2][2]);
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 4; j++)
      P[i][j] = inv_l * P[i][j];

  R[2][0] = P[2][0];
  R[2][1] = P[2][1];
  R[2][2] = P[2][2];
  T[2]    = P[2][3];

  double AAt[3][3];
  getAAt(P, AAt);
  cx = AAt[2][0];
  cy = AAt[2][1];
  fy = sqrt(AAt[1][1] - cy * cy);
  double s = (AAt[1][0] - cx * cy) / fy;
  fx = sqrt(AAt[0][0] - cx * cx - s * s);

  R[1][0] = (P[1][0] - cy * R[2][0]) / fy;
  R[0][0] = (P[0][0] - s * R[1][0] - cx * R[2][0]) / fx; 

  R[1][1] = (P[1][1] - cy * R[2][1]) / fy;
  R[0][1] = (P[0][1] - s * R[1][1] - cx * R[2][1]) / fx; 

  R[1][2] = (P[1][2] - cy * R[2][2]) / fy;
  R[0][2] = (P[0][2] - s * R[1][2] - cx * R[2][2]) / fx; 

  T[1] = (P[1][3] - cy * T[2]) / fy;
  T[0] = (P[0][3] - s * T[1] - cx * T[2]) / fx;

  if (gfla_det(R) < 0) {
    fy = -fy; // ??
    for(int i = 0; i < 3; i++) 
      R[1][i] = -R[1][i];
    T[1] = -T[1];
  }

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

/*! Load external and internal parameters from a tdir file. The w and h specify
* the size of the projection rectangle.
*
* \return true on success, false on failure.
*/
bool projection_matrix::load_tdir(const char * tdir_filename, int w, int h)
{
  ifstream file;
  file.open(tdir_filename);

  if (!file.good()) return false;
  double P[3][4];

  for (int j=0; j<3; ++j) 
    for (int i=0; i<4; ++i) 
      file >> P[j][i];
  file.close();
  set_3x4_matrix(P, w, h);

  return true;
}

static double diag(double x, double y)
{
  return sqrt(x*x+y*y);
}

static double diagDiff(const int W, const int H, double dx, double dy)
{
  double mdiag = diag(double(W), double(H));
  return fabs(double(mdiag - diag(2 * dx, 2 * dy)));
}

/*! Load external and internal parameters from a tdir file, estimating image
* width and height.
*
* THE WIDTH AND HEIGHT ESTIMATION MIGHT BE WRONG!
*
* \return true on success, false on failure.
*/
bool projection_matrix::load_tdir(const char * tdir_filename)
{
  if (!load_tdir(tdir_filename, 0, 0)) return false;

  static const int modes[] = {
      640, 480,
      320, 240,
      720, 576,
      360, 288,
      800, 600,
      1024, 768,
      512, 384,
      1280, 1024,
      -1, -1
  };

  int best = 0;
  double bestDelta = diagDiff(modes[0], modes[1], cx, cy); 
  for(int i = 1; modes[2 * i] != -1; i++) {
    double delta = diagDiff(modes[2 * i], modes[2 * i + 1], cx, cy);
    if (delta < bestDelta) {
      best = i;
      bestDelta = delta;
    }
  }

  image_width  = modes[2 * best];
  image_height = modes[best + 1];

  return true;
}

void projection_matrix::load(FILE * f)
{
  char calibration_name[500];
  int dummy;

  fscanf(f,"%s", calibration_name);

  fscanf(f, "%d", &dummy);

  if (dummy != -1) // To correct incompatibility with older versions of keyframes
    fscanf(f, "%d", &dummy);

  read_internal_parameters_from_tdir_file(calibration_name);

  fscanf(f, "%lf %lf %lf", &(optical_centre[0]), &(optical_centre[1]), &(optical_centre[2]));
  fscanf(f, "%lf %lf %lf", &(R[0][0]), &(R[0][1]), &(R[0][2]));
  fscanf(f, "%lf %lf %lf", &(R[1][0]), &(R[1][1]), &(R[1][2]));
  fscanf(f, "%lf %lf %lf", &(R[2][0]), &(R[2][1]), &(R[2][2]));
  fscanf(f, "%lf %lf %lf", &(T[0]),     &(T[1]),    &(T[2]));

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::read_one_line(FILE * f, char * line)
{
  int n = 0;
  char c;

  do
  {
    fscanf(f, "%c", &c);
    line[n] = c;
    n++;
  } while (c != '\n');
  n = n - 2; // Skip the (char)13 and the (char)10:
  line[n] = '\0';
}

FILE * projection_matrix::open_matchmover_output(char * filename)
{
  FILE * f = fopen(filename, "r");
  char line[1000];

  if (f == NULL)
    return NULL;

  do {
    read_one_line(f, line);
  } while (strcmp(line, "Camera") != 0);

  read_one_line(f, line);

  return f;
}

void projection_matrix::close_matchmover_output(FILE * f)
{
  fclose(f);
}

bool projection_matrix::read_from_matchmover_output(FILE * f)
{
  int camera_index;
  double focale_length, pixel_ratio, principal_point_u, principal_point_v, K;
  double Oc[3], local_R[3][3], local_t[3];

  if (fscanf(f, "\t%d", &camera_index) != 1)
  {
    cerr << "Error while reading matchmover output (1)." << endl;
    return false;
  }

  if (fscanf(f, "\t F ( %lf ) Pr ( %lf ) Pp ( %lf %lf ) K ( %lf )",
    &focale_length, &pixel_ratio, &principal_point_u, &principal_point_v, &K) != 5)
  {
    cerr << "Error while reading matchmover output (2)." << endl;
    return false;
  }

  if (fscanf(f, "\tOc ( %lf %lf %lf )", &(Oc[0]), &(Oc[1]), &(Oc[2])) != 3)
  {
    cerr << "Error while reading matchmover output (3)." << endl;
    return false;
  }

  if (fscanf(f, "\tRot ( %lf %lf %lf", &(local_R[0][0]), &(local_R[0][1]), &(local_R[0][2])) != 3)
  {
    cerr << "Error while reading matchmover output (4)." << endl;
    return false;
  }

  if (fscanf(f, "%lf %lf %lf", &(local_R[1][0]), &(local_R[1][1]), &(local_R[1][2])) != 3)
  {
    cerr << "Error while reading matchmover output (5)." << endl;
    return false;
  }

  if (fscanf(f, " %lf %lf %lf )", &(local_R[2][0]), &(local_R[2][1]), &(local_R[2][2])) != 3)
  {
    cerr << "Error while reading matchmover output (6)." << endl;
    return false;
  }

  set_original_internal_parameters(int(2 * principal_point_u), int(2 * principal_point_v), // image size
    focale_length, pixel_ratio * focale_length, 
    principal_point_u, principal_point_v);

  gfla_mul_mat_vect_3x3(local_R, Oc, local_t);
  gfla_opp_3(local_t);

  set_external_parameters(local_R, local_t);

  return true;
}

ostream& operator<< (ostream& o, const projection_matrix& P)
{
  o << "[" << P.fx << "\t" << 0    << "\t" << P.cx << "\t][" << P.R[0][0] << "\t"  << P.R[0][1] << "\t" << P.R[0][2] << " | " << P.T[0] << " ]" << endl;
  o << "[" << 0    << "\t" << P.fy << "\t" << P.cy << "\t][" << P.R[1][0] << "\t"  << P.R[1][1] << "\t" << P.R[1][2] << " | " << P.T[1] << " ]" << endl;
  o << "[" << 0    << "\t" << 0    << "\t" << 1    << "\t][" << P.R[2][0] << "\t"  << P.R[2][1] << "\t" << P.R[2][2] << " | " << P.T[2] << " ]" << endl;

  return o;
}

void projection_matrix::print(FILE * file, char * calibration_filename)
{
  fprintf(file, "%s\n", calibration_filename);
  fprintf(file, "0\n");  // Compatibility reasons
  fprintf(file, "-1\n"); // Idem

  if (have_to_recompute_optical_centre)
    compute_optical_centre();

  fprintf(file, "%lf %lf %lf ", optical_centre[0], optical_centre[1], optical_centre[2]);
  fprintf(file, "%lf %lf %lf ", R[0][0], R[0][1], R[0][2]);
  fprintf(file, "%lf %lf %lf ", R[1][0], R[1][1], R[1][2]);
  fprintf(file, "%lf %lf %lf ", R[2][0], R[2][1], R[2][2]);
  fprintf(file, "%lf %lf %lf ", T[0],    T[1],    T[2]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal parameters:

void projection_matrix::set_original_internal_parameters(int _image_width, int _image_height,
                                                         double _fx, double _fy, double _cx, double _cy)
{
  image_width = original_image_width = _image_width;
  image_height = original_image_height = _image_height;

  fx = original_fx = _fx;
  fy = original_fy = _fy;
  cx = original_cx = _cx;
  cy = original_cy = _cy;

  have_to_recompute_invAR = have_to_recompute_P = true;
}

void projection_matrix::set_original_internal_parameters(double _fx, double _fy, double _cx, double _cy)
{
  fx = original_fx = _fx;
  fy = original_fy = _fy;
  cx = original_cx = _cx;
  cy = original_cy = _cy;

  have_to_recompute_invAR = have_to_recompute_P = true;
}

void projection_matrix::change_image_size(int new_width, int new_height)
{
  image_width = new_width;
  image_height = new_height;

  double sx = (double)new_width  / original_image_width;
  double sy = (double)new_height / original_image_height;

  fx = sx * original_fx;
  cx = sx * original_cx;
  fy = sy * original_fy;
  cy = sy * original_cy;

  have_to_recompute_invAR = have_to_recompute_P = true;
}

bool projection_matrix::read_internal_parameters_from_tdir_file(const char * tdir_filename)
{
  double tdir_mat[12];

  FILE * tdir_file = fopen(tdir_filename, "r");
  if (tdir_file == 0) 
  {
    perror(tdir_filename);
    return false;
  }

  for(int i = 0; i < 12 ; i++)
  {
    if (fscanf(tdir_file, "%lf", &tdir_mat[i]) == EOF)
    {
      cout<<"Error loading file (corrupt or wrong format)"<<endl;
      fclose(tdir_file);
      return false;
    }
  }
  fclose(tdir_file);

  original_fx = fx = tdir_mat[0];
  original_fy = fy = tdir_mat[5];
  original_cx = cx = tdir_mat[2];
  original_cy = cy = tdir_mat[6];

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// External parameters:

void projection_matrix::set_camera_centre_and_lookat_point(double Cx, double Cy, double Cz, 
                                                           double Lx, double Ly, double Lz, 
                                                           double angle_vertical)
{
  double rli1[3], rli2[3], rli3[3];
  double k[3];

  rli3[0] = Lx - Cx;
  rli3[1] = Ly - Cy;
  rli3[2] = Lz - Cz;
  gfla_normalize_3(rli3);

  k[0] = sin(angle_vertical) * rli3[1]; 
  k[1] = sin(angle_vertical) * rli3[0]; 
  k[2] = cos(angle_vertical);
  gfla_cross_product(rli3, k, rli1);

  gfla_cross_product(rli3, rli1, rli2);

  for(int i = 0; i < 3; i++)
  {
    R[0][i] = rli1[i];
    R[1][i] = rli2[i];
    R[2][i] = rli3[i];
  }

  for(int i = 0; i < 3; i++)
    T[i] = -(R[i][0] * Cx + R[i][1] * Cy + R[i][2] * Cz);

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_external_parameters(double omega, double phi, double kappa, 
                                                double Tx, double Ty, double Tz)
{
  gfla_get_rotation_from_euler_angles(R, omega, phi, kappa);

  T[0] = Tx;
  T[1] = Ty;
  T[2] = Tz;

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_external_parameters(double * state)
{
  set_external_parameters(state[0], state[1], state[2], state[3], state[4], state[5]);
}

void projection_matrix::set_external_parameters_exp_map(double * state, CvMat * JR)
{
  double * om = state;
  double * t = state + 3;

  double length = sqrt(om[0] * om[0] + om[1] * om[1] + om[2] * om[2]);

  if (length > (2 * 3.14159 - 1)) 
  {
    double new_length = fmod(length, 2 * 3.14159);
    double r = new_length / length;
    om[0] *= r;
    om[1] *= r;
    om[2] *= r;
  }

  // make the rotation matrix
  double rm[9], rv[3];
  CvMat rotMat = cvMat(3, 3, CV_64FC1, rm);
  CvMat rotVec = cvMat(1, 3, CV_64FC1, rv);

  cvSetReal1D(&rotVec, 0, om[0]);
  cvSetReal1D(&rotVec, 1, om[1]);
  cvSetReal1D(&rotVec, 2, om[2]);

  // Compute the rotation matrix
  cvRodrigues(&rotMat, &rotVec, JR, CV_RODRIGUES_V2M);

  // complete the rotation matrix with translation
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
      R[i][j] = cvmGet(&rotMat, i, j); 
    T[i] = t[i];
  }

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::get_external_parameters_exp_map(double * state)
{
  // make the rotation matrix
  double rm[9], rv[3];
  CvMat rotMat = cvMat(3, 3, CV_64FC1, rm);
  CvMat rotVec = cvMat(1, 3, CV_64FC1, rv);

  // Compute the rotation matrix
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      cvmSet(&rotMat, i, j, R[i][j]); 

  cvRodrigues(&rotMat, &rotVec, 0, CV_RODRIGUES_M2V);

  state[0] = rv[0];
  state[1] = rv[1];
  state[2] = rv[2];

  state[3] = T[0];
  state[4] = T[1];
  state[5] = T[2];
}

void projection_matrix::set_external_parameters(double wc2vc[3][4])
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
      R[i][j] = wc2vc[i][j];
    T[i] = wc2vc[i][3];
  }

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_external_parameters(double ** wc2vc)
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
      R[i][j] = wc2vc[i][j];
    T[i] = wc2vc[i][3];
  }

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_external_parameters(double rot[3][3], double transl[3])
{
  gfla_copy_3x3(rot, R);
  gfla_copy_3(transl, T);

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_rotation_to_Id(void)
{
  R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
  R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
  R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_translation_to_0(void)
{
  T[0] = T[1] = T[2] = 0.;

  have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::set_external_parameters(CvMat * H)
{
  double AH1[3], AH2[3];
  double inv_fx = 1. / fx, inv_fy = 1. / fy;

  AH1[0] = inv_fx * cvmGet(H, 0, 0) - cx * inv_fx * cvmGet(H, 2, 0);
  AH1[1] = inv_fy * cvmGet(H, 1, 0) - cy * inv_fy * cvmGet(H, 2, 0);
  AH1[2] =                                          cvmGet(H, 2, 0);

  AH2[0] = inv_fx * cvmGet(H, 0, 1) - cx * inv_fx * cvmGet(H, 2, 1);
  AH2[1] = inv_fy * cvmGet(H, 1, 1) - cy * inv_fy * cvmGet(H, 2, 1);
  AH2[2] =                                          cvmGet(H, 2, 1);

  T[0] = inv_fx * cvmGet(H, 0, 2) - cx * inv_fx * cvmGet(H, 2, 2);
  T[1] = inv_fy * cvmGet(H, 1, 2) - cy * inv_fy * cvmGet(H, 2, 2);
  T[2] =                                          cvmGet(H, 2, 2);

  double norm2_AH1 = AH1[0] * AH1[0] + AH1[1] * AH1[1] + AH1[2] * AH1[2];
  double norm2_AH2 = AH2[0] * AH2[0] + AH2[1] * AH2[1] + AH2[2] * AH2[2];
  double inv_l = 1. / sqrt( sqrt(norm2_AH1 * norm2_AH2) );

  double R1[3], R2[3];
  gfla_scale_3(inv_l, AH1, R1);
  gfla_scale_3(inv_l, AH2, R2);
  gfla_scale_3(inv_l, T);

  double c[3], p[3], d[3];
  gfla_add_3(R1, R2, c);
  gfla_cross_product(R1, R2, p);
  gfla_cross_product(c,  p,  d);

  gfla_normalize_3(c);
  gfla_normalize_3(d);

  double R1p[3], R2p[3], R3p[3];
  gfla_add_3(c, d, R1p);
  gfla_scale_3(1. / sqrt(2.), R1p);

  gfla_sub_3(c, d, R2p);
  gfla_scale_3(1. / sqrt(2.), R2p);

  gfla_cross_product(R1p, R2p, R3p);

  for(int i = 0; i < 3; i++)
  {
    R[i][0] = R1p[i]; 
    R[i][1] = R2p[i]; 
    R[i][2] = R3p[i];
  }

  cout << *this << endl;

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::translate_x(double delta)
{
  T[0] += delta;
  have_to_recompute_optical_centre = have_to_recompute_P = true;
}


void projection_matrix::translate_y(double delta)
{
  T[1] += delta;
  have_to_recompute_optical_centre = have_to_recompute_P = true;
}


void projection_matrix::translate_z(double delta)
{
  T[2] += delta;
  have_to_recompute_optical_centre = have_to_recompute_P = true;
}


void projection_matrix::rotate_x(double delta)
{ 
  double par[6];

  get_external_parameters(&par[0], &par[1], &par[2], &par[3], &par[4], &par[5]);
  par[0] += delta;
  set_external_parameters(par[0], par[1], par[2], par[3], par[4], par[5]);

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::rotate_y(double delta)
{ 
  double par[6];

  get_external_parameters(&par[0], &par[1], &par[2], &par[3], &par[4], &par[5]);
  par[1] += delta;
  set_external_parameters(par[0], par[1], par[2], par[3], par[4], par[5]);

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::rotate_z(double delta)
{ 
  double par[6];

  get_external_parameters(&par[0], &par[1], &par[2], &par[3], &par[4], &par[5]);
  par[2] += delta;
  set_external_parameters(par[0], par[1], par[2], par[3], par[4], par[5]);

  have_to_recompute_invAR = have_to_recompute_optical_centre = have_to_recompute_P = true;
}

void projection_matrix::get_external_parameters(double * state)
{
  get_external_parameters(&state[0], &state[1], &state[2], &state[3], &state[4], &state[5]);
}

void projection_matrix::get_external_parameters(double * omega, double * phi, double * kappa,
                                                double * Tx, double * Ty, double * Tz)
{
  gfla_get_euler_angles_from_rotation(R, omega, phi, kappa);

  *Tx = T[0];
  *Ty = T[1];
  *Tz = T[2];
}

void projection_matrix::world_to_cam(double * M, double * Mc)
{
  if (M != Mc)
  {
    Mc[0] = R[0][0] * M[0] + R[0][1] * M[1] + R[0][2] * M[2] + T[0];
    Mc[1] = R[1][0] * M[0] + R[1][1] * M[1] + R[1][2] * M[2] + T[1];
    Mc[2] = R[2][0] * M[0] + R[2][1] * M[1] + R[2][2] * M[2] + T[2];
  }
  else
  {
    double M2[3];
    M2[0] = R[0][0] * M[0] + R[0][1] * M[1] + R[0][2] * M[2] + T[0];
    M2[1] = R[1][0] * M[0] + R[1][1] * M[1] + R[1][2] * M[2] + T[1];
    M2[2] = R[2][0] * M[0] + R[2][1] * M[1] + R[2][2] * M[2] + T[2];
    Mc[0] = M2[0];
    Mc[1] = M2[1];
    Mc[2] = M2[2];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projection matrix:

void projection_matrix::get_3x4_matrix(double pP[3][4])
{
  if (have_to_recompute_P)
    compute_P();

  gfla_copy_3x4(P, pP);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Optical centre:

void projection_matrix::get_optical_centre(double * Cx, double * Cy, double * Cz)
{
  if (have_to_recompute_optical_centre)
    compute_optical_centre();

  *Cx = optical_centre[0];
  *Cy = optical_centre[1];
  *Cz = optical_centre[2];
}

double * projection_matrix::get_optical_centre(void)
{
  if (have_to_recompute_optical_centre)
    compute_optical_centre();

  return optical_centre;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ray casting:

double * projection_matrix::get_V(double u, double v)
{
  double * V = new double[3];

  get_V(u, v, V);

  return V;
}

void projection_matrix::get_V(double u, double v, double * V)
{
  if (have_to_recompute_invAR)
    compute_invAR();

  V[0] = invAR[0][0] * u + invAR[0][1] * v + invAR[0][2];
  V[1] = invAR[1][0] * u + invAR[1][1] * v + invAR[1][2];
  V[2] = invAR[2][0] * u + invAR[2][1] * v + invAR[2][2];

  gfla_normalize_3(V);
}

void projection_matrix::get_V(double u, double v, double * Vx, double * Vy, double * Vz)
{
  if (have_to_recompute_invAR)
    compute_invAR();

  *Vx = invAR[0][0] * u + invAR[0][1] * v + invAR[0][2];
  *Vy = invAR[1][0] * u + invAR[1][1] * v + invAR[1][2];
  *Vz = invAR[2][0] * u + invAR[2][1] * v + invAR[2][2];

  double inv_norme = 1. / gfla_norme(*Vx, *Vy, *Vz);

  *Vx *= inv_norme;
  *Vy *= inv_norme;
  *Vz *= inv_norme;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL:

void projection_matrix::set_GL_zmin_zmax(double zmin, double zmax)
{
  planes[4] = zmin;
  planes[5] = zmax;
}

void projection_matrix::set_GL_PROJECTION(int xdim, int ydim, float * gl_vector)
{
  double tdir[3][4], S[3][3], Stdir[3][4];
  float gl_mat[4][4];
  double zmin = planes[4], zmax = planes[5], zratio = 2.0 / (zmax - zmin);

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 4; j++)
      tdir[i][j] = 0.;

  tdir[0][0] = fx;
  tdir[1][1] = fy;
  tdir[0][2] = cx;
  tdir[1][2] = cy;
  tdir[2][2] = 1.;

  S[0][0] = 2. / xdim; S[0][1] = 0.;        S[0][2] = -1.;
  S[1][0] = 0.;        S[1][1] = 2. / ydim; S[1][2] = -1.;
  S[2][0] = 0.;        S[2][1] = 0.;        S[2][2] =  1.;

  gfla_mul_mat_3x3x4(S, tdir, Stdir);

  for(int j = 0; j < 4; j++)
  {
    gl_mat[j][0] = float(Stdir[0][j]);
    gl_mat[j][1] = float(Stdir[1][j]); 
    gl_mat[j][3] = float(Stdir[2][j]); 
  }

  // Plane distance computation in 3rd column:
  for(int j = 0; j < 4; j++)
    gl_mat[j][2] = float( planes[j] * zratio );
  gl_mat[3][2]= float( -(1.0 + gl_mat[3][2] + zmin * zratio) );

  for(int i = 0; i < 4; i++) 
    gl_mat[i][1] = -gl_mat[i][1];

  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      gl_vector[j + 4 * i] = gl_mat[i][j];
}

void projection_matrix::set_GL_MODELVIEW(double * gl_vector)
{
  gl_vector[0*4+0] = R[0][0]; gl_vector[0*4+1] = R[1][0]; gl_vector[0*4+2] = R[2][0]; gl_vector[0*4+3] = 0.;
  gl_vector[1*4+0] = R[0][1]; gl_vector[1*4+1] = R[1][1]; gl_vector[1*4+2] = R[2][1]; gl_vector[1*4+3] = 0.;
  gl_vector[2*4+0] = R[0][2]; gl_vector[2*4+1] = R[1][2]; gl_vector[2*4+2] = R[2][2]; gl_vector[2*4+3] = 0.;
  gl_vector[3*4+0] = T[0];    gl_vector[3*4+1] = T[1];    gl_vector[3*4+2] = T[2];    gl_vector[3*4+3] = 1.;
}

bool projection_matrix::visible_triangle(double X1, double Y1, double Z1,
                                         double X2, double Y2, double Z2,
                                         double X3, double Y3, double Z3)
{
  double V[3], n[3];
  get_V(cx, cy, V);
  double M1M2[3], M1M3[3];
  M1M2[0] = X2 - X1; M1M2[1] = Y2 - Y1; M1M2[2] = Z2 - Z1;
  M1M3[0] = X3 - X1; M1M3[1] = Y3 - Y1; M1M3[2] = Z3 - Z1;
  gfla_cross_product(M1M2, M1M3, n);
  return gfla_dot_product(n, V) < 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal functions:

void projection_matrix::compute_invAR(void)
{
  double t4, t6, t8, t10, t12, t14, t16, t19, t24, t27, t28, t30, t32, t34, t35, t37, t39, t43, t52, t55, t57, t59;

  t4 = 1/fx;
  t6 = R[0][0]*R[2][2];
  t8 = R[0][0]*R[2][1];
  t10 = R[1][0]*R[2][2];
  t12 = R[2][1]*R[1][0];
  t14 = R[2][0]*R[0][1];
  t16 = R[2][0]*R[0][2];
  t19 = 1/(t6*R[1][1]-t8*R[1][2]-t10*R[0][1]+t12*R[0][2]+t14*R[1][2]-t16*R[1][1]);
  t24 = 1/fy;
  t27 = fx*R[0][1];
  t28 = R[1][2]*fy;
  t30 = cy*R[2][2];
  t32 = cx*R[2][1];
  t34 = fx*R[0][2];
  t35 = fy*R[1][1];
  t37 = cy*R[2][1];
  t39 = cx*R[2][2];
  t43 = t24*t19;
  t52 = fx*R[0][0];
  t55 = cx*R[2][0];
  t57 = fy*R[1][0];
  t59 = cy*R[2][0];

  invAR[0][0] = (R[1][1]*R[2][2]-R[2][1]*R[1][2])*t4*t19;
  invAR[0][1] = -(R[2][2]*R[0][1]-R[2][1]*R[0][2])*t24*t19;
  invAR[0][2] = (t27*t28+t27*t30+t32*t28-t34*t35-t34*t37-t39*t35)*t4*t43;
  invAR[1][0] = -(t10-R[2][0]*R[1][2])*t4*t19;
  invAR[1][1] = (t6-t16)*t24*t19;
  invAR[1][2] = -(t52*t28+t52*t30+t55*t28-t34*t57-t34*t59-t39*t57)*t4*t43;
  invAR[2][0] = (t12-R[2][0]*R[1][1])*t4*t19;
  invAR[2][1] = -(t8-t14)*t24*t19;
  invAR[2][2] = (t52*t35+t52*t37+t55*t35-t27*t57-t27*t59-t32*t57)*t4*t43;

  have_to_recompute_invAR = false;
}

void projection_matrix::compute_optical_centre(void)
{
  ///              t
  ///calculating -R T
  optical_centre[0] = -(R[0][0] * T[0] + R[1][0] * T[1] + R[2][0] * T[2]);
  optical_centre[1] = -(R[0][1] * T[0] + R[1][1] * T[1] + R[2][1] * T[2]);
  optical_centre[2] = -(R[0][2] * T[0] + R[1][2] * T[1] + R[2][2] * T[2]);

  have_to_recompute_optical_centre = false;
}

void projection_matrix::compute_P(void)
{
  double A[3][3];

  A[0][0] = fx; A[0][1] = 0.; A[0][2] = cx;
  A[1][0] = 0.; A[1][1] = fy; A[1][2] = cy;
  A[2][0] = 0.; A[2][1] = 0.; A[2][2] = 1.;

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 4; j++)
    {
      P[i][j] = 0;
      for(int k = 0; k < 3; k++)
        if (j < 3)
          P[i][j] += A[i][k] * R[k][j];
        else
          P[i][j] += A[i][k] * T[k];
    }

    have_to_recompute_P = false;
}

