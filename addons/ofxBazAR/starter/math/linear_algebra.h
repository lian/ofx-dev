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
/*! \ingroup starter */
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <iostream>
using namespace std;

// Vectors:
double gfla_norme(double v1, double v2, double v3);

double gfla_normalize_3(double v[3]);

void gfla_scale_3(const double s, double v[3]);
void gfla_scale_3(const double s, const double v[3], double sv[3]);

void gfla_add_3(const double u[3], const double v[3], double w[3]);
void gfla_sub_3(const double u[3], const double v[3], double w[3]);

void   gfla_opp_3(double v[3]);
void   gfla_cross_product(const double v1[3], const double v2[3], double v1v2[3]);
double gfla_dot_product(const double v1[3], const double v2[3]);
void   gfla_copy_3(const double v[3], double copy[3]);

// Copy matrices:
void   gfla_copy_3x3(const double M[3][3], double copy[3][3]);
void   gfla_copy_3x4(const double M[3][4], double copy[3][4]);

// Matrices:
double gfla_det(const double M[3][3]);
double gfla_det(const double M11, const double M12,
                const double M21, const double M22);
double gfla_det(const double M11, const double M12, const double M13, 
                const double M21, const double M22, const double M23, 
                const double M31, const double M32, const double M33);

// Print matrices:
void   gfla_print_mat_3x3(ostream & o, double M[3][3]);
void   gfla_print_mat_3x4(ostream & o, double M[3][4]);
void   gfla_print_mat_4x4(ostream & o, double * M);

// Rotation matrices:
void   gfla_get_rotation_from_euler_angles(double R[3][3], const double omega, const double phi, const double kappa);
int    gfla_get_euler_angles_from_rotation(const double R[3][3], double * omega, double * phi, double * kappa);

// Multiplication Vectors/Matrices
void   gfla_mul_scale_mat_3x3(double s, double M[3][3], double sM[3][3]);

void   gfla_mul_mat_vect_3x3(const double M[3][3], const double v[3], double Mv[3]);
void   gfla_mul_T_mat_vect_3x3(const double M[3][3], const double v[3], double tMv[3]);
void   gfla_mul_mat_vect_3x4(const double M[3][4], const double v[3], double Mv[3]);
void   gfla_mul_mat_3x3x4(const double M[3][3], const double N[3][4], double MN[3][4]);

// Inverse
void gfla_inverse_3(double A[3][3], double invA[3][3]);

#endif // LINEAR_ALGEBRA_H
