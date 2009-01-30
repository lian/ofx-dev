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
#ifndef OBSERVATION_TYPES_H
#define OBSERVATION_TYPES_H

#include <cmath>
#include <limits>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class observation
{
public:
  inline void set_default_values(void) { squared_c = std::numeric_limits<double>::max(); confidence = 1.; weight = 1.; sqrt_weight = 1.; ground_truth_outlier = false; }
  ls_minimizer_type squared_c_current, squared_c, c_min, c_max;
  ls_minimizer_type weight, sqrt_weight;
  double confidence;
  bool outlier, ground_truth_outlier;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*function_2data_1measure)(const ls_minimizer_type d0, const ls_minimizer_type d1, 
                                        const ls_minimizer_type * state, 
                                        ls_minimizer_type & b0, 
                                        ls_minimizer_type * J, 
                                        void ** user_data);

class observation_2data_1measure : public observation
{
public:
  function_2data_1measure f;

  ls_minimizer_type d0, d1;
  ls_minimizer_type b0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*function_2data_2measures)(const ls_minimizer_type d0, const ls_minimizer_type d1, 
                                         const ls_minimizer_type * state,
                                         ls_minimizer_type & b0, ls_minimizer_type & b1, 
                                         ls_minimizer_type * J, 
                                         void ** user_data);

class observation_2data_2measures : public observation
{
public:
  function_2data_2measures f;

  ls_minimizer_type d0, d1;
  ls_minimizer_type b0, b1;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*function_3data_2measures)(const ls_minimizer_type d0, 
		const ls_minimizer_type d1, const ls_minimizer_type d2, 
		const ls_minimizer_type * state, 
		ls_minimizer_type & b0, ls_minimizer_type & b1, 
                                         ls_minimizer_type * J, 
                                         void ** user_data);

class observation_3data_2measures : public observation
{
public:
  function_3data_2measures f;

  ls_minimizer_type d0, d1, d2;
  ls_minimizer_type b0, b1;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // OBSERVATION_TYPES_H
