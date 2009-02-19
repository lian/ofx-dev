/**
 * File:          $RCSfile: 3x3matrixf.h,v $
 * Module:        3x3 matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.10 $
 * Last edited:   $Date: 2006/03/15 16:18:23 $
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

#ifndef _GAN_3X3MATRIXF_H
#define _GAN_3X3MATRIXF_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat33_noc.h>
#include <gandalf/linalg/3vectorf.h>
#include <gandalf/linalg/2x2matrixf.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/matf_gen.h>
#include <gandalf/linalg/matf_square.h>

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

/// Structure definition for single precision 3x3 matrix
typedef struct Gan_Matrix33_f
{
   float xx, xy, xz,
         yx, yy, yz,
         zx, zy, zz;
} Gan_Matrix33_f;

#ifndef NDEBUG
/// Square matrix type, for setting and checking in debug mode
typedef enum { GAN_SYMMETRIC_MATRIX33_F, GAN_LOWER_TRI_MATRIX33_F }
 Gan_SquMatrix33Type_f;
#endif /* #ifndef NDEBUG */

/// Structure definition for square single precision 3x3 matrix
typedef struct Gan_SquMatrix33_f
{
#ifndef NDEBUG
   /* square matrix type, for setting and checking in debug mode */
   Gan_SquMatrix33Type_f type;
#endif /* #ifndef NDEBUG */

   /* matrix data */
   float xx,
         yx, yy,
         zx, zy, zz;
} Gan_SquMatrix33_f;

/* matrix definitions specific to 3x3 matrices */
#define GAN_ST33F_FILL(A,t,XX,YX,YY,ZX,ZY,ZZ)\
           (GAN_TEST_OP1(A,Gan_SquMatrix33_f),gan_eval((A)->type=t),\
            GAN_FREP33L_A_C((A)->,=,(XX),(YX),(YY),(ZX),(ZY),(ZZ)))
#define GAN_ST33F_IDENT(A,t)\
           (GAN_TEST_OP1(A,Gan_SquMatrix33_f),gan_eval((A)->type=t),\
            GAN_FREP33L_A_C((A)->,=,1.0,0.0,1.0,0.0,0.0,1.0))

/* generic matrix multiply operations */
#define GAN_MAT33F_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,xy,xz,q1,q2,q3,+),\
  a p2 = GAN_REP3_OP_AB(b,* c,yx,yy,yz,q1,q2,q3,+),\
  a p3 = GAN_REP3_OP_AB(b,* c,zx,zy,zz,q1,q2,q3,+))
#define GAN_MAT33TF_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,yx,zx,q1,q2,q3,+),\
  a p2 = GAN_REP3_OP_AB(b,* c,xy,yy,zy,q1,q2,q3,+),\
  a p3 = GAN_REP3_OP_AB(b,* c,xz,yz,zz,q1,q2,q3,+))

/* symmetric matrix multiply operation */
#define GAN_SYM33F_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,yx,zx,q1,q2,q3,+),\
  a p2 = GAN_REP3_OP_AB(b,* c,yx,yy,zy,q1,q2,q3,+),\
  a p3 = GAN_REP3_OP_AB(b,* c,zx,zy,zz,q1,q2,q3,+))

/* lower triangular matrix multiply operations */
#define GAN_LOW33F_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p3 = GAN_REP3_OP_AB(b,* c,zx,zy,zz,q1,q2,q3,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,yx,yy,q1,q2,+),\
  a p1 = GAN_REP1_OP_AB(b,* c,xx,q1,+))
#define GAN_LOW33IF_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p1 =  c q1 / b xx,\
  a p2 = (c q2 - b yx * a p1) / b yy,\
  a p3 = (c q3 - b zx * a p1 - b zy * a p2) / b zz)

/* upper triangular matrix multiply operations */
#define GAN_UPP33F_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p1 = GAN_REP3_OP_AB(b,* c,xx,yx,zx,q1,q2,q3,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,yy,zy,q2,q3,+),\
  a p3 = GAN_REP1_OP_AB(b,* c,zz,q3,+))
#define GAN_UPP33IF_MULT1D(a,b,c,p1,p2,p3,q1,q2,q3)\
 (a p3 =  c q3 / b zz,\
  a p2 = (c q2 - b zy * a p3) / b yy,\
  a p1 = (c q1 - b yx * a p2 - b zx * a p3) / b xx)

/* symmetric/lower triangular square matrix definitions */
#define GAN_ST33F_ZERO(A,t)\
           (GAN_TEST_OP1(A,Gan_SquMatrix33_f), gan_eval((A)->type=t),\
            GAN_REP33L_AS_C((A)->,=0.0))
#define GAN_ST33F_COPY(A,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix33_f,Gan_SquMatrix33_f),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP33L_AA_C((B)->,=(A)->))
#define GAN_ST33F_SCALE(A,a,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix33_f,Gan_SquMatrix33_f),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP33L_AAS_C((B)->,=(A)->,*(a)))
#define GAN_ST33F_DIVIDE(A,a,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix33_f,Gan_SquMatrix33_f),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP33L_AAS_C((B)->,=(A)->,/(a)))
#define GAN_ST33F_NEGATE(A,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix33_f,Gan_SquMatrix33_f),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP33L_AA_C((B)->,=-(A)->))
#define GAN_ST33F_ADD(A,B,C,t)\
         (GAN_TEST_OP3(A,B,C,Gan_SquMatrix33_f,Gan_SquMatrix33_f,Gan_SquMatrix33_f),\
          assert((A)->type==t && (B)->type==t), gan_eval((C)->type=(A)->type),\
          GAN_REP33L_AAA_C((C)->,=(A)->,+(B)->))
#define GAN_ST33F_SUB(A,B,C,t)\
         (GAN_TEST_OP3(A,B,C,Gan_SquMatrix33_f,Gan_SquMatrix33_f,Gan_SquMatrix33_f),\
          assert((A)->type==t && (B)->type==t), gan_eval((C)->type=(A)->type),\
          GAN_REP33L_AAA_C((C)->,=(A)->,-(B)->))

/* declare functions specific to generic 3x3 matrices */
#include <gandalf/linalg/3x3matf_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

/* declare functions specific to symmetric 3x3 matrices */
#include <gandalf/linalg/3x3symmatf_noc.h>
#include <gandalf/linalg/symmatrixf_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

/* declare functions specific to lower triangular 3x3 matrices */
#include <gandalf/linalg/3x3ltmatf_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

/* declare functions specific to upper triangular 3x3 matrices */
#include <gandalf/linalg/3x3ltmatTf_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
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

#endif /* #ifndef _GAN_3X3MATRIXF_H */
