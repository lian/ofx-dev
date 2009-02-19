/**
 * File:          $RCSfile: 3x4matrixf.h,v $
 * Module:        3x4 matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.7 $
 * Last edited:   $Date: 2002/12/06 17:48:54 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

#ifndef _GAN_3X4MATRIXF_H
#define _GAN_3X4MATRIXF_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat34_noc.h>
#include <gandalf/linalg/3vectorf.h>
#include <gandalf/linalg/4vectorf.h>
#include <gandalf/linalg/3x3matrixf.h>
#include <gandalf/linalg/4x4matrixf.h>
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

/// Structure definition for single precision 3x4 matrix
typedef struct Gan_Matrix34_f
{
   float xx, xy, xz, xw,
         yx, yy, yz, yw,
         zx, zy, zz, zw;
} Gan_Matrix34_f;

/* generic matrix multiply operations */
#define GAN_MAT34F_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3,q4)\
 (a p1 = GAN_REP4_OP_AB(b,* c,xx,xy,xz,xw,q1,q2,q3,q4,+),\
  a p2 = GAN_REP4_OP_AB(b,* c,yx,yy,yz,yw,q1,q2,q3,q4,+),\
  a p3 = GAN_REP4_OP_AB(b,* c,zx,zy,zz,zw,q1,q2,q3,q4,+))
#define GAN_MAT34TF_MULT1D(a,b,c,p1,p2,p3,p4,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,yx,zx,q1,q2,q3,+),\
  a p2 = GAN_REP3_OP_AB(b,* c,xy,yy,zy,q1,q2,q3,+),\
  a p3 = GAN_REP3_OP_AB(b,* c,xz,yz,zz,q1,q2,q3,+),\
  a p4 = GAN_REP3_OP_AB(b,* c,xw,yw,zw,q1,q2,q3,+))

/* declare functions specific to 2x3 matrices */
#include <gandalf/linalg/3x4matf_noc.h>
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

#endif /* #ifndef _GAN_3X4MATRIXF_H */
