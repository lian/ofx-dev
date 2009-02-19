/**
 * File:          $RCSfile: 4vector.h,v $
 * Module:        Size 4 vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.17 $
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

#ifndef _GAN_4VECTOR_H
#define _GAN_4VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat4_noc.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/3vector.h>
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

/// Structure definition for double precision floating point 4-vector
typedef struct Gan_Vector4
{
   double x, y, z, w;
} Gan_Vector4, Gan_Vector4_d;

/// Structure definition for unsigned character 4-vector
typedef struct Gan_Vector4_uc
{
   unsigned char x, y, z, w;
} Gan_Vector4_uc;

/// Structure definition for integer 4-vector
typedef struct Gan_Vector4_i
{
   int x, y, z, w;
} Gan_Vector4_i;

/// Structure definition for unsigned integer 4-vector
typedef struct Gan_Vector4_ui
{
   unsigned int x, y, z, w;
} Gan_Vector4_ui;

/// Special definitions for 8/16/32/64 bits
#if (SIZEOF_DOUBLE == 8)
typedef struct Gan_Vector4 Gan_Vector4_f64;
#endif

#if (SIZEOF_CHAR == 1)
typedef struct Gan_Vector4_uc Gan_Vector4_ui8;
#endif

#if (SIZEOF_SHORT == 2)
typedef struct Gan_Vector4_s  Gan_Vector4_i16;
typedef struct Gan_Vector4_us Gan_Vector4_ui16;
#endif

#if (SIZEOF_INT == 4)
typedef struct Gan_Vector4_i  Gan_Vector4_i32;
typedef struct Gan_Vector4_ui Gan_Vector4_ui32;
#endif

/* declare functions specific to 4-vectors */
#include <gandalf/linalg/4vec_noc.h>
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

#endif /* #ifndef _GAN_4VECTOR_H */
