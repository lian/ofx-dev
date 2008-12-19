/**
 * File:          $RCSfile: 2x3matrixf.h,v $
 * Module:        2x3 matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.8 $
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

#ifndef _GAN_2X3MATRIXF_H
#define _GAN_2X3MATRIXF_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat23_noc.h>
#include <gandalf/linalg/2vectorf.h>
#include <gandalf/linalg/3vectorf.h>
#include <gandalf/linalg/2x2matrixf.h>
#include <gandalf/linalg/3x3matrixf.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/matf_gen.h>

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

/// Structure definition for single precision 2x3 matrix
typedef struct Gan_Matrix23_f
{
   float xx, xy, xz,
         yx, yy, yz;
} Gan_Matrix23_f;

/* generic matrix multiply operations */
#define GAN_MAT23F_MULT1D(a,b,c,p1,p2,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,xy,xz,q1,q2,q3,+),\
  a p2 = GAN_REP3_OP_AB(b,* c,yx,yy,yz,q1,q2,q3,+))
#define GAN_MAT23TF_MULT1D(a,b,c,p1,p2,p3,q1,q2)\
 (a p1 = GAN_REP2_OP_AB(b,* c,xx,yx,q1,q2,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,xy,yy,q1,q2,+),\
  a p3 = GAN_REP2_OP_AB(b,* c,xz,yz,q1,q2,+))

/* declare functions specific to 2x3 matrices */
#include <gandalf/linalg/2x3matf_noc.h>
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

#endif /* #ifndef _GAN_2X3MATRIXF_H */
