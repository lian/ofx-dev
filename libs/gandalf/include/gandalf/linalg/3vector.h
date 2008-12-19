/**
 * File:          $RCSfile: 3vector.h,v $
 * Module:        Size 3 vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.19 $
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

#ifndef _GAN_3VECTOR_H
#define _GAN_3VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat3_noc.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/2vector.h>
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

/// Structure definition for double precision floating point 3-vector
typedef struct Gan_Vector3
{
   double x, y, z;
} Gan_Vector3, Gan_Vector3_d;

/// Structure definition for unsigned character 3-vector
typedef struct Gan_Vector3_uc
{
   unsigned char x, y, z;
} Gan_Vector3_uc;

/// Structure definition for short integer 3-vector
typedef struct Gan_Vector3_s
{
   short x, y, z;
} Gan_Vector3_s;

/// Structure definition for unsigned short integer 3-vector
typedef struct Gan_Vector3_us
{
   unsigned short x, y, z;
} Gan_Vector3_us;

/// Structure definition for integer 3-vector
typedef struct Gan_Vector3_i
{
   int x, y, z;
} Gan_Vector3_i;

/// Structure definition for unsigned integer 3-vector
typedef struct Gan_Vector3_ui
{
   unsigned int x, y, z;
} Gan_Vector3_ui;

/// Special definitions for 8/16/32/64 bits
#if (SIZEOF_DOUBLE == 8)
typedef struct Gan_Vector3 Gan_Vector3_f64;
#endif

#if (SIZEOF_CHAR == 1)
typedef struct Gan_Vector3_uc Gan_Vector3_ui8;
#endif

#if (SIZEOF_SHORT == 2)
typedef struct Gan_Vector3_s  Gan_Vector3_i16;
typedef struct Gan_Vector3_us Gan_Vector3_ui16;
#endif

#if (SIZEOF_INT == 4)
typedef struct Gan_Vector3_i  Gan_Vector3_i32;
typedef struct Gan_Vector3_ui Gan_Vector3_ui32;
#endif

/* declare functions specific to 3-vectors */
#include <gandalf/linalg/3vec_noc.h>
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

#endif /* #ifndef _GAN_3VECTOR_H */
