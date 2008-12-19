/**
 * File:          $RCSfile: 4vector_norm.h,v $
 * Module:        Projective normalisation of 4-vector array (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.10 $
 * Last edited:   $Date: 2002/04/18 14:56:23 $
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

#ifndef _GAN_4VECTOR_NORM_H
#define _GAN_4VECTOR_NORM_H

#include <gandalf/linalg/4vector.h>
#include <gandalf/linalg/4x4matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GAN_VEC_NORMALISE gan_vec4_normalize
#define GAN_VECTYPE       Gan_Vector4
#define GAN_SQUMATTYPE    Gan_SquMatrix44

#include <gandalf/linalg/vec_norm_noc.h>

#undef GAN_VEC_NORMALISE
#undef GAN_VECTYPE
#undef GAN_SQUMATTYPE

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_4VECTOR_NORM_H */
