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
#ifndef PROJECTION_MATRIX_H
#define PROJECTION_MATRIX_H


#include <stdio.h>
#include <cv.h>
#include <iostream>

using namespace std;

/*!\ingroup starter */
//@{

//! 3D to 2D projection matrix
class projection_matrix 
{
public:
  projection_matrix(void);
  ~projection_matrix();

  projection_matrix &operator = (const projection_matrix &P);

  // Output:
  friend ostream& operator<< (ostream& o, const projection_matrix& P);
  void print(FILE * file, char * calibration_filename);

  // Reading from files:
  bool load_tdir(const char * tdir_filename);
  bool load_tdir(const char * tdir_filename, int w, int h);

  void load(FILE * f); // for keyframe format

  static FILE * open_matchmover_output(char * filename);
  static void close_matchmover_output(FILE * f);
  bool read_from_matchmover_output(FILE * f);

  // Projection matrix:
  void set_3x4_matrix(double P[3][4], int width, int height);
  void get_3x4_matrix(double P[3][4]);

  // Internal parameters:
  void set_original_internal_parameters(int image_width, int image_height,
                                        double fx, double fy, double cx, double cy);

  void set_original_internal_parameters(double fx, double fy, double cx, double cy);

  void change_image_size(int new_width, int new_height);

  bool read_internal_parameters_from_tdir_file(const char * tdir_filename);

  double get_cx(void) { return cx; }
  double get_cy(void) { return cy; }
  double get_fx(void) { return fx; }
  double get_fy(void) { return fy; }

  // External parameters:
  void set_camera_centre_and_lookat_point(double Cx, double Cy, double Cz, 
                                          double Lx, double Ly, double Lz, 
                                          double angle_vertical);

  void set_external_parameters(double omega, double phi, double kappa, double Tx, double Ty, double Tz);
  void set_angles(double omega, double phi, double kappa);
  void set_external_parameters(double rot[3][3], double transl[3]);
  void set_external_parameters(double wc2vc[3][4]);
  void set_external_parameters(double ** wc2vc);
  void set_external_parameters(double * state);
  void set_external_parameters_exp_map(double * state, CvMat * JR = 0);
  void set_external_parameters(CvMat * H);
  void set_rotation_to_Id(void);
  void set_translation_to_0(void);

  void get_external_parameters(double * omega, double * phi, double * kappa,
                               double * Tx, double * Ty, double * Tz);
  void get_external_parameters(double * state);
  void get_external_parameters_exp_map(double * state);

  void get_angles(double * omega, double * phi, double * kappa);

  void translate_x(double delta);
  void translate_y(double delta);
  void translate_z(double delta);
  void rotate_x(double delta);
  void rotate_y(double delta);
  void rotate_z(double delta);

  void world_to_cam(double * M, double * Mc);

  // Optical centre:
  void get_optical_centre(double * Cx, double * Cy, double * Cz);
  // Optical centre: DONT DELETE returned pointer !
  double * get_optical_centre(void);

  // Ray casting from pixel:
  // DELETE returned pointer !
  double * get_V(double u, double v);
  void get_V(double u, double v, double * V);
  void get_V(double u, double v, double * Vx, double * Vy, double * Vz);

  // OpenGL:
  void set_GL_zmin_zmax(double zmin, double zmax);

  void set_GL_PROJECTION(int xdim, int ydim, float * gl_vector);
  void set_GL_MODELVIEW(double * gl_matrix);

  bool visible_triangle(double X1, double Y1, double Z1,
                        double X2, double Y2, double Z2,
                        double X3, double Y3, double Z3);

  // Projection:
  void project(const double X, const double Y, const double Z, double * u, double * v);
  void project(const double X, const double Y, const double Z, float * u,  float * v);

private:
  // For reading matchmover output:
  static void read_one_line(FILE * f, char * line);
  void getAAt(const double P[3][4], double AAt[3][3]);

  // Attributes
  double original_fx, original_fy, original_cx, original_cy;
  double fx, fy, cx, cy;

  int original_image_width, original_image_height;
  int image_width, image_height;

  double R[3][3], T[3];
  double P[3][4];
  double optical_centre[3];
  double invAR[3][3]; // =(AR)^(-1)

  void compute_optical_centre(void);
  void compute_invAR(void);
  void compute_P(void);

  bool have_to_recompute_optical_centre;
  bool have_to_recompute_invAR;
  bool have_to_recompute_P;

  double planes[6];
};

ostream& operator<< (ostream& o, const projection_matrix& P);

inline void projection_matrix::project(const double X, const double Y, const double Z, double * u, double * v)
{
  if (have_to_recompute_P)
    compute_P();

  double M[4], PM[3];
  M[0] = X; M[1] = Y; M[2] = Z; M[3] = 1.;
  gfla_mul_mat_vect_3x4(P, M, PM);

  double inv_PM3 = 1 / PM[2];
  *u = inv_PM3 * PM[0];
  *v = inv_PM3 * PM[1];
}

inline void projection_matrix::project(const double X, const double Y, const double Z, float * u, float * v)
{
  if (have_to_recompute_P)
    compute_P();

  double M[4], PM[3];
  M[0] = X; M[1] = Y; M[2] = Z; M[3] = 1.;
  gfla_mul_mat_vect_3x4(P, M, PM);

  double inv_PM3 = 1 / PM[2];
  *u = float(inv_PM3 * PM[0]);
  *v = float(inv_PM3 * PM[1]);
}

//@}
#endif // PROJECTION_MATRIX_H
