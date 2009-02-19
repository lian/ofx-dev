/**
 * File:          $RCSfile: numerics.h,v $
 * Module:        Numerical functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.19 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _GAN_NUMERICS_H
#define _GAN_NUMERICS_H

#include <stdlib.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/common/complex.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonNumerics
 * \{
 */

/* declarations of functions */
GANDALF_API int      gan_sqr_i  ( int       x );
GANDALF_API unsigned gan_sqr_ui ( unsigned  x );
GANDALF_API long     gan_sqr_l  ( long      x );
GANDALF_API float    gan_sqr_f  ( float     x );
GANDALF_API double   gan_sqr_d  ( double    x );
GANDALF_API double gan_cbrt ( double x );
GANDALF_API double gan_normal_sample ( double mu, double sigma );
GANDALF_API int gan_solve_quadratic ( double a, double b, double c,
                          Gan_Complex x[2] );
GANDALF_API int gan_solve_cubic ( double a, double b, double c, double d,
                      Gan_Complex x[3] );

/**
 * \brief Macro: Computes square of a number.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_sqr ( double x );
#else
#define gan_sqr(x) ((x)*(x))
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Integer random number generator function.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API long gan_random(void);
#else
#ifdef HAVE_RANDOM
#define gan_random()              random()
#else /* use the standard rand() function */
#define gan_random()              rand()
#endif /* #ifdef HAVE_RANDOM */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Integer random number seed setter function.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_random_set_seed ( unsigned seed );
#else
#ifdef HAVE_RANDOM
#define gan_random_set_seed(seed) srandom(seed)
#else /* use the standard srand() function */
#define gan_random_set_seed(seed) srand(seed)
#endif /* #ifdef HAVE_RANDOM */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Random floating point number between 0 and 1.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_random_01(void);
#else
#define gan_random_01() ((double)(gan_random()&32767)/32768.0)
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Random floating point number between -1 and 1.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_random_m11(void);
#else
#define gan_random_m11() (2.0*gan_random_01()-1.0)
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

void *gan_kth_highest ( void *base, size_t nmemb, size_t size,
                        unsigned int k,
                        int (*compar)(const void *, const void *) );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_NUMERICS_H */
