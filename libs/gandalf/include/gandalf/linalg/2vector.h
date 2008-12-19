/**
 * File:          $RCSfile: 2vector.h,v $
 * Module:        Size 2 vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.18 $
 * Last edited:   $Date: 2005/04/15 02:15:23 $
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

#ifndef _GAN_2VECTOR_H
#define _GAN_2VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat2_noc.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/vec_gen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup LinearAlgebra
 * \{
 */

/**
 * \addtogroup FixedSizeMatVec
 * \{
 */

/**
 * \addtogroup FixedSizeVector
 * \{
 */

/// Structure definition for double precision floating point 2-vector
typedef struct Gan_Vector2
{
   double x, y;
} Gan_Vector2, Gan_Vector2_d;

/// Structure definition for unsigned character 2-vector
typedef struct Gan_Vector2_uc
{
   unsigned char x, y;
} Gan_Vector2_uc;

/// Structure definition for short integer 2-vector
typedef struct Gan_Vector2_s
{
   short x, y;
} Gan_Vector2_s;

/// Structure definition for unsigned short integer 2-vector
typedef struct Gan_Vector2_us
{
   unsigned short x, y;
} Gan_Vector2_us;

/// Structure definition for integer 2-vector
typedef struct Gan_Vector2_i
{
   int x, y;
} Gan_Vector2_i;

/// Structure definition for unsigned integer 2-vector
typedef struct Gan_Vector2_ui
{
   unsigned int x, y;
} Gan_Vector2_ui;

/// Special definitions for 8/16/32/64 bits
#if (SIZEOF_DOUBLE == 8)
typedef struct Gan_Vector2 Gan_Vector2_f64;
#endif

#if (SIZEOF_CHAR == 1)
typedef struct Gan_Vector2_uc Gan_Vector2_ui8;
#endif

#if (SIZEOF_SHORT == 2)
typedef struct Gan_Vector2_s  Gan_Vector2_i16;
typedef struct Gan_Vector2_us Gan_Vector2_ui16;
#endif

#if (SIZEOF_INT == 4)
typedef struct Gan_Vector2_i  Gan_Vector2_i32;
typedef struct Gan_Vector2_ui Gan_Vector2_ui32;
#endif

/* declare functions specific to 2-vectors */
#include <gandalf/linalg/2vec_noc.h>
#include <gandalf/linalg/vectorf_noc.h>

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_2VECTOR_H */
