/**
 * File:          $RCSfile: 3vectorf.h,v $
 * Module:        Size 3 vectors (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.10 $
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

#ifndef _GAN_3VECTORF_H
#define _GAN_3VECTORF_H

#include <stdlib.h>
#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat3_noc.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/2vectorf.h>
#include <gandalf/linalg/vecf_gen.h>

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

/// Structure definition for single precision floating point 3-vector
typedef struct Gan_Vector3_f
{
   float x, y, z;
} Gan_Vector3_f;

/// Special definition for 32 bit float
#if (SIZEOF_FLOAT == 4)
typedef struct Gan_Vector3_f Gan_Vector3_f32;
#endif

/* declare functions specific to 3-vectors */
#include <gandalf/linalg/3vecf_noc.h>
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

#endif /* #ifndef _GAN_3VECTORF_H */
