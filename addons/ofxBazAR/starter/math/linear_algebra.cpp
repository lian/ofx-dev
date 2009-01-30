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
#include <math.h>

#include "linear_algebra.h"
#include "../general/general.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Vectors:

double gfla_norme(double v1, double v2, double v3)
{
  return sqrt(v1 * v1 + v2 * v2 + v3 * v3);
}

double gfla_normalize_3(double v[3])
{
  double norme = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

  if (norme < 1e-10)
    return 0;

  double inv_norme = 1. / norme;

  v[0] *= inv_norme;
  v[1] *= inv_norme;
  v[2] *= inv_norme;

  return norme;
}

void gfla_scale_3(const double s, double v[3])
{
  v[0] *= s;
  v[1] *= s;
  v[2] *= s;
}

void gfla_scale_3(const double s, const double v[3], double sv[3])
{
  sv[0] = s * v[0];
  sv[1] = s * v[1];
  sv[2] = s * v[2];
}

void gfla_opp_3(double v[3])
{
  v[0] = -v[0];
  v[1] = -v[1];
  v[2] = -v[2];
}

void gfla_add_3(const double u[3], const double v[3], double w[3])
{
  w[0] = u[0] + v[0];
  w[1] = u[1] + v[1];
  w[2] = u[2] + v[2];
}

void gfla_sub_3(const double u[3], const double v[3], double w[3])
{
  w[0] = u[0] - v[0];
  w[1] = u[1] - v[1];
  w[2] = u[2] - v[2];
}

void gfla_cross_product(const double v1[3], const double v2[3], double v1v2[3])
{
  v1v2[0] = v1[1] * v2[2] - v1[2] * v2[1];
  v1v2[1] = v1[2] * v2[0] - v1[0] * v2[2];
  v1v2[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

double gfla_dot_product(const double v1[3], const double v2[3])
{
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


void gfla_copy_3(const double v[3], double copy[3])
{
  for(int i = 0; i < 3; i++)
    copy[i] = v[i];
}

// Matrices:
void gfla_copy_3x3(const double M[3][3], double copy[3][3])
{
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      copy[i][j] = M[i][j];
}

void gfla_copy_3x4(const double M[3][4], double copy[3][4])
{
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 4; j++)
      copy[i][j] = M[i][j];
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Matrices:

double gfla_det(const double M[3][3])
{ 
  return  M[0][0] * M[1][1] * M[2][2] -
          M[0][0] * M[1][2] * M[2][1] -
          M[1][0] * M[0][1] * M[2][2] +
          M[1][0] * M[0][2] * M[2][1] +
          M[2][0] * M[0][1] * M[1][2] -
          M[2][0] * M[0][2] * M[1][1]; 
}

double gfla_det(const double M11, const double M12,
                const double M21, const double M22)
{
  return M11 * M22 - M12 * M21;
}

double gfla_det(const double M11, const double M12, const double M13, 
                const double M21, const double M22, const double M23, 
                const double M31, const double M32, const double M33)
{
  return  M11 * M22 * M33 - M11 * M23 * M32 -
          M21 * M12 * M33 + M21 * M13 * M32 +
          M31 * M12 * M23 - M31 * M13 * M22; 
}

void gfla_get_rotation_from_kappa(double R[3][3], const double kappa)
{
  R[0][0] =  cos(kappa); R[0][1] = sin(kappa); R[0][2] = 0.;
  R[1][0] = -sin(kappa); R[1][1] = cos(kappa); R[1][2] = 0.;
  R[2][0] =          0.; R[2][1] =         0.; R[2][2] = 1.;
}

void gfla_get_rotation_from_phi(double R[3][3], const double phi)
{
  R[0][0] =  cos(phi); R[0][1] = 0.; R[0][2] = -sin(phi);
  R[1][0] =        0.; R[1][1] = 1.; R[1][2] = 0.;
  R[2][0] =  sin(phi); R[2][1] = 0.; R[2][2] = cos(phi);
}

void gfla_get_rotation_from_omega(double R[3][3], const double omega)
{
  R[0][0] =  1.; R[0][1] =          0.; R[0][2] = 0.;
  R[1][0] =  0.; R[1][1] =  cos(omega); R[1][2] = sin(omega);
  R[2][0] =  0.; R[2][1] = -sin(omega); R[2][2] = cos(omega);
}

/*! 
  R = R(kappa) * R(phi) * R(omega)
  */
void gfla_get_rotation_from_euler_angles(double R[3][3], const double omega, const double phi, const double kappa)
{
   double 
     t1 = sin(omega),
     t2 = cos(phi),
     t4 = cos(omega),
     t6 = sin(kappa),
     t8 = cos(kappa),
     t10 = sin(phi),
     t11 = t1*t10,
     t15 = t4*t10;
   
   R[0][0] = t2*t8;
   R[0][1] = t4*t6+t11*t8;
   R[0][2] = t1*t6-t15*t8;
   R[1][0] = -t2*t6;
   R[1][1] = t4*t8-t11*t6;
   R[1][2] = t1*t8+t15*t6;
   R[2][0] = t10;
   R[2][1] = -t1*t2;
   R[2][2] = t4*t2;
}

int gfla_get_euler_angles_from_rotation(const double R[3][3], double * omega, double * phi, double * kappa)
{
  if (fabs(R[2][2]) < 1e-6 && fabs(R[2][1]) < 1e-6)
  {
    /* Degenerate case:  When phi = +/- 90 degrees, then we cannot seperate omega and kappa */
    *omega = atan2(R[1][2], R[1][1]); 
    if (R[2][0] > 0.)
      *phi =  M_PI/2; 
    else 
      *phi = -M_PI/2 ;
    *kappa = 0.;

    return 0;
  }
  else
  {
    *omega = atan2(-R[2][1], R[2][2]);
    *phi   = atan2(R[2][0],  sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]));
    *kappa = atan2(-R[1][0], R[0][0]);

    return 1;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Vectors/Matrices     

void gfla_mul_scale_mat_3x3(double s, double M[3][3], double sM[3][3])
{
  sM[0][0] = s * M[0][0]; sM[0][1] = s * M[0][1]; sM[0][2] = s * M[0][2];
  sM[1][0] = s * M[1][0]; sM[1][1] = s * M[1][1]; sM[1][2] = s * M[1][2];
  sM[2][0] = s * M[2][0]; sM[2][1] = s * M[2][1]; sM[2][2] = s * M[2][2];
}

void gfla_mul_mat_vect_3x3(const double M[3][3], const double v[3], double Mv[3])
{
  if (v != Mv)
    {
      Mv[0] = M[0][0] * v[0] + M[0][1] * v[1] + M[0][2] * v[2];
      Mv[1] = M[1][0] * v[0] + M[1][1] * v[1] + M[1][2] * v[2];
      Mv[2] = M[2][0] * v[0] + M[2][1] * v[1] + M[2][2] * v[2];
    }
  else
    {
      double Mv_temp[3];

      Mv_temp[0] = M[0][0] * v[0] + M[0][1] * v[1] + M[0][2] * v[2];
      Mv_temp[1] = M[1][0] * v[0] + M[1][1] * v[1] + M[1][2] * v[2];
      Mv_temp[2] = M[2][0] * v[0] + M[2][1] * v[1] + M[2][2] * v[2];

      Mv[0] = Mv_temp[0];
      Mv[1] = Mv_temp[1];
      Mv[2] = Mv_temp[2];
    }
}

void gfla_mul_T_mat_vect_3x3(const double M[3][3], const double v[3], double tMv[3])
{
  for(int i = 0; i < 3; i++)
  {
    tMv[i] = M[0][i] * v[0];
    for(int j = 1; j < 3; j++)
      tMv[i] += M[j][i] * v[j];
  }
}

void gfla_mul_mat_vect_3x4(const double M[3][4], const double v[3], double Mv[3])
{
  for(int i = 0; i < 3; i++)
  {
    Mv[i] = M[i][0] * v[0];
    for(int j = 1; j < 4; j++)
      Mv[i] += M[i][j] * v[j];
  }
}

void gfla_mul_mat_3x3x4(const double M[3][3], const double N[3][4], double MN[3][4])
{
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 4; j++)
    {
      MN[i][j] = 0.;
      for(int k = 0; k < 3; k++)
        MN[i][j] += M[i][k] * N[k][j];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Inverse

void gfla_inverse_3(double A[3][3], double invA[3][3])
{
  double t1;
  double t11;
  double t13;
  double t14;
  double t15;
  double t17;
  double t18;
  double t2;
  double t20;
  double t21;
  double t23;
  double t26;
  double t4;
  double t5;
  double t8;
  double t9;
  {
    t1 = A[1][1];
    t2 = A[2][2];
    t4 = A[1][2];
    t5 = A[2][1];
    t8 = A[0][0];

    t9 = t8*t1;
    t11 = t8*t4;
    t13 = A[1][0];
    t14 = A[0][1];
    t15 = t13*t14;
    t17 = A[0][2];
    t18 = t13*t17;
    t20 = A[2][0];
    t21 = t20*t14;
    t23 = t20*t17;
    t26 = 1/(t9*t2-t11*t5-t15*t2+t18*t5+t21*t4-t23*t1);
    invA[0][0] = (t1*t2-t4*t5)*t26;
    invA[0][1] = -(t14*t2-t17*t5)*t26;
    invA[0][2] = -(-t14*t4+t17*t1)*t26;
    invA[1][0] = -(t13*t2-t4*t20)*t26;
    invA[1][1] = (t8*t2-t23)*t26;
    invA[1][2] = -(t11-t18)*t26;
    invA[2][0] = -(-t13*t5+t1*t20)*t26;
    invA[2][1] = -(t8*t5-t21)*t26;
    invA[2][2] = (t9-t15)*t26;
    return;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Print:

void gfla_print_mat_3x3(ostream & o, double M[3][3])
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
      o << M[i][j] << "\t";
    o << endl;
  }
}

void gfla_print_mat_3x4(ostream & o, double M[3][4])
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
      o << M[i][j] << "\t";
    o << endl;
  }
}

void gfla_print_mat_4x4(ostream & o, double * M)
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
      o << M[4 * i + j] << "\t";
    o << endl;
  }
}
