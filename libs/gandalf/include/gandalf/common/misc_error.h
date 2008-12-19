/**
 * File:          $RCSfile: misc_error.h,v $
 * Module:        Miscellaneous error declarations
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.25 $
 * Last edited:   $Date: 2006/01/19 15:00:08 $
 * Author:        $Author: pm $
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

#ifndef _GAN_MISC_ERROR_H
#define _GAN_MISC_ERROR_H

#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <gandalf/common/gan_err.h>
#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonError
 * \{
 */

/* Gandalf error codes. If you change them, remember to change the switch
 * statement in print_error() in misc_error.c.
 */
#define GAN_ERROR_FAILURE                     1
#define GAN_ERROR_NOT_IMPLEMENTED             2
#define GAN_ERROR_REF_OUTSIDE_MATRIX          3
#define GAN_ERROR_CANT_REALLOC                4
#define GAN_ERROR_MALLOC_FAILED               5
#define GAN_ERROR_DIFFERENT_DIMS              6
#define GAN_ERROR_INCOMPATIBLE                7
#define GAN_ERROR_MATRIX_NOT_SQUARE           8
#define GAN_ERROR_INPLACE_TRANSPOSE           9
#define GAN_ERROR_INPLACE_MULTIPLY           10
#define GAN_ERROR_ARRAY_TOO_SMALL            11
#define GAN_ERROR_ILLEGAL_TYPE               12
#define GAN_ERROR_NO_IMPLICIT_INV            13
#define GAN_ERROR_CLAPACK_ILLEGAL_ARG        14
#define GAN_ERROR_CBLAS_ILLEGAL_ARG          15
#define GAN_ERROR_CBLAS_FAILED               16
#define GAN_ERROR_NOT_POSITIVE_DEFINITE      17
#define GAN_ERROR_DIVISION_BY_ZERO           18
#define GAN_ERROR_SQRT_OF_NEG_NUMBER         19
#define GAN_ERROR_NO_CONVERGENCE             20
#define GAN_ERROR_SINGULAR_MATRIX            21
#define GAN_ERROR_IMAGE_TOO_SMALL            22
#define GAN_ERROR_NO_DATA                    23
#define GAN_ERROR_NOT_ENOUGH_DATA            24
#define GAN_ERROR_OPENING_FILE               25
#define GAN_ERROR_CORRUPTED_FILE             26
#define GAN_ERROR_OUTSIDE_RANGE              27
#define GAN_ERROR_TOO_LARGE                  28
#define GAN_ERROR_TOO_SMALL                  29
#define GAN_ERROR_TRUNCATED_FILE             30
#define GAN_ERROR_NOT_INITIALISED            31
#define GAN_ERROR_ILLEGAL_ARGUMENT           32
#define GAN_ERROR_CCMATH_FAILED              33
#define GAN_ERROR_NO_SOLUTION                34
#define GAN_ERROR_READING_FROM_FILE          35
#define GAN_ERROR_WRITING_TO_FILE            36
#define GAN_ERROR_EXTERNAL_LIBRARY_CALL      37
#define GAN_ERROR_ILLEGAL_IMAGE_TYPE         38
#define GAN_ERROR_ILLEGAL_IMAGE_FORMAT       39
#define GAN_ERROR_ILLEGAL_IMAGE_FILE_FORMAT  40
#define GAN_ERROR_ILLEGAL_IMAGE_CHANNEL      41

GANDALF_API const char *gan_err_string_at_lowest_level(void);
GANDALF_API const char *gan_err_string(int error_code);
GANDALF_API void gan_err_default_reporter(void);

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MISC_ERROR_H */
