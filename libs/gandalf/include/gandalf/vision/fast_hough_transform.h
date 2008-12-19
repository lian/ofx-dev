/**
 * File:          $RCSfile: fast_hough_transform.h,v $
 * Module:        Fast Hough Transform implentation
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.3 $
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

#ifndef _GAN_FAST_HOUGH_TRANSFORM_H
#define _GAN_FAST_HOUGH_TRANSFORM_H

#include <gandalf/common/bit_array.h>
#include <gandalf/linalg/mat_gen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup HoughTransform
 * \{
 */

GANDALF_API Gan_Bool gan_fast_hough_transform ( int k, Gan_Matrix *a, int *weight,
                                    int no_points, double *S0, double *X0,
                                    int max_level, int T_thres,
                                    Gan_MemoryStack *memory_stack,
                                    double *X_best, int *level_best,
                                    int *accum_best, Gan_BitArray *list_best,
                                    int *subdivs );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_FAST_HOUGH_TRANSFORM_H */
