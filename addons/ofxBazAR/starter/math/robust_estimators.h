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
#ifndef ROBUST_ESTIMATORS_H
#define ROBUST_ESTIMATORS_H

#include <math.h>

//! \ingroup starter 
//@{

double rho_tukey_without_sqrt(const double x2, const double c);
double rho_tukey_without_sqrt_derivative(const double x2, const double c);

double rho_huber_without_sqrt(const double x2, const double c);
double rho_huber_without_sqrt_derivative(const double x2, const double c);


inline double rho_tukey_without_sqrt(const double x2, const double c)
{
  double c2 = c * c;

  if (x2 > c2)
    return c2 / 6;
  else
  {
    double t = 1. - x2 / c2;

    return c2 / 6 * (1. - t * t * t);
  }
}

inline double rho_tukey_without_sqrt_derivative(const double x2, const double c)
{
  double c2 = c * c;

  if (x2 > c2)
    return 0;
  else
  {
    double t = 1. - x2 / c2;

    return t * t / 2.;
  }
}

inline double rho_huber_without_sqrt(const double x2, const double c)
{
  double c2 = c * c;

  if (x2 < c2)
    return x2;
  else
    return 2 * c * sqrt(x2) - c2;
}

inline double rho_huber_without_sqrt_derivative(const double x2, const double c)
{
  double c2 = c * c;

  if (x2 < c2)
    return 1;
  else
    return c / sqrt(x2);
}

//@}
#endif // ROBUST_ESTIMATORS_H
