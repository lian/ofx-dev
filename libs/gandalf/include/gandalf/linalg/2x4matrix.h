/**
 * File:          $RCSfile: 2x4matrix.h,v $
 * Module:        2x4 matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.11 $
 * Last edited:   $Date: 2002/12/06 17:48:53 $
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

#ifndef _GAN_2X4MATRIX_H
#define _GAN_2X4MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat24_noc.h>
#include <gandalf/linalg/2vector.h>
#include <gandalf/linalg/4vector.h>
#include <gandalf/linalg/2x2matrix.h>
#include <gandalf/linalg/4x4matrix.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/mat_gen.h>

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
 * \addtogroup FixedSizeMatrix
 * \{
 */

/// Structure definition for double precision 2x4 matrix
typedef struct Gan_Matrix24
{
   double xx, xy, xz, xw,
          yx, yy, yz, yw;
} Gan_Matrix24;

/* generic matrix multiply operations */
#define GAN_MAT24_MULT1D(a,b,c,p1,p2,q1,q2,q3,q4)\
 (a p1 = GAN_REP4_OP_AB(b,* c,xx,xy,xz,xw,q1,q2,q3,q4,+),\
  a p2 = GAN_REP4_OP_AB(b,* c,yx,yy,yz,yw,q1,q2,q3,q4,+))
#define GAN_MAT24T_MULT1D(a,b,c,p1,p2,p3,p4,q1,q2)\
 (a p1 = GAN_REP2_OP_AB(b,* c,xx,yx,q1,q2,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,xy,yy,q1,q2,+),\
  a p3 = GAN_REP2_OP_AB(b,* c,xz,yz,q1,q2,+),\
  a p4 = GAN_REP2_OP_AB(b,* c,xw,yw,q1,q2,+))

/* declare functions specific to 2x3 matrices */
#include <gandalf/linalg/2x4mat_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

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

#endif /* #ifndef _GAN_2X4MATRIX_H */
