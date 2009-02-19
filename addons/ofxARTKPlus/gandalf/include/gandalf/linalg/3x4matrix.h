/**
 * File:          $RCSfile: 3x4matrix.h,v $
 * Module:        3x4 matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.10 $
 * Last edited:   $Date: 2002/12/06 17:48:53 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

#ifndef _GAN_3X4MATRIX_H
#define _GAN_3X4MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat34_noc.h>
#include <gandalf/linalg/3vector.h>
#include <gandalf/linalg/4vector.h>
#include <gandalf/linalg/3x3matrix.h>
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

/// Structure definition for double precision 3x4 matrix
typedef struct Gan_Matrix34
{
   double xx, xy, xz, xw,
          yx, yy, yz, yw,
          zx, zy, zz, zw;
} Gan_Matrix34;

/* generic matrix multiply operations */
#define GAN_MAT34_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3,q4)\
 (a p1 = GAN_REP4_OP_AB(b,* c,xx,xy,xz,xw,q1,q2,q3,q4,+),\
  a p2 = GAN_REP4_OP_AB(b,* c,yx,yy,yz,yw,q1,q2,q3,q4,+),\
  a p3 = GAN_REP4_OP_AB(b,* c,zx,zy,zz,zw,q1,q2,q3,q4,+))
#define GAN_MAT34T_MULT1D(a,b,c,p1,p2,p3,p4,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,yx,zx,q1,q2,q3,+),\
  a p2 = GAN_REP3_OP_AB(b,* c,xy,yy,zy,q1,q2,q3,+),\
  a p3 = GAN_REP3_OP_AB(b,* c,xz,yz,zz,q1,q2,q3,+),\
  a p4 = GAN_REP3_OP_AB(b,* c,xw,yw,zw,q1,q2,q3,+))

/* declare functions specific to 2x3 matrices */
#include <gandalf/linalg/3x4mat_noc.h>
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

#endif /* #ifndef _GAN_3X4MATRIX_H */
