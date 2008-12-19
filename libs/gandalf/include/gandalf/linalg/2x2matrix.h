/**
 * File:          $RCSfile: 2x2matrix.h,v $
 * Module:        2x2 matrices (double precision)
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

#ifndef _GAN_2X2MATRIX_H
#define _GAN_2X2MATRIX_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/repeat22_noc.h>
#include <gandalf/linalg/2vector.h>
#include <gandalf/linalg/matvecf_macros_noc.h>
#include <gandalf/linalg/mat_gen.h>
#include <gandalf/linalg/mat_square.h>

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

/// Structure definition for double precision 2x2 matrix
typedef struct Gan_Matrix22
{
   double xx, xy,
          yx, yy;
} Gan_Matrix22;

#ifndef NDEBUG
/// Square matrix type, for setting and checking in debug mode
typedef enum { GAN_SYMMETRIC_MATRIX22, GAN_LOWER_TRI_MATRIX22 }
 Gan_SquMatrix22Type;
#endif /* #ifndef NDEBUG */

/// Structure definition for square double precision 2x2 matrix
typedef struct Gan_SquMatrix22
{
#ifndef NDEBUG
   /* square matrix type, for setting and checking in debug mode */
   Gan_SquMatrix22Type type;
#endif /* #ifndef NDEBUG */

   /* matrix data */
   double xx,
          yx, yy;
} Gan_SquMatrix22;

/* matrix definitions specific to 2x2 matrices */
#define GAN_ST22_FILL(A,t,XX,YX,YY)\
           (GAN_TEST_OP1(A,Gan_SquMatrix22),gan_eval((A)->type=t),\
            GAN_FREP22L_A_C((A)->,=,(XX),(YX),(YY)))
#define GAN_ST22_IDENT(A,t)\
           (GAN_TEST_OP1(A,Gan_SquMatrix22),gan_eval((A)->type=t),\
            GAN_FREP22L_A_C((A)->,=,1.0,0.0,1.0))

/* generic matrix multiply operations */
#define GAN_MAT22_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p1 = GAN_REP2_OP_AB(b,* c,xx,xy,q1,q2,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,yx,yy,q1,q2,+))
#define GAN_MAT22T_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p1 = GAN_REP2_OP_AB(b,* c,xx,yx,q1,q2,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,xy,yy,q1,q2,+))

/* symmetric matrix multiply operation */
#define GAN_SYM22_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p1 = GAN_REP2_OP_AB(b,* c,xx,yx,q1,q2,+),\
  a p2 = GAN_REP2_OP_AB(b,* c,yx,yy,q1,q2,+))

/* lower triangular matrix multiply operations */
#define GAN_LOW22_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p2 = GAN_REP2_OP_AB(b,* c,yx,yy,q1,q2,+),\
  a p1 = GAN_REP1_OP_AB(b,* c,xx,q1,+))
#define GAN_LOW22I_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p1 =  c q1 / b xx,\
  a p2 = (c q2 - b yx * a p1) / b yy)

/* upper triangular matrix multiply operations */
#define GAN_UPP22_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p1 = GAN_REP2_OP_AB(b,* c,xx,yx,q1,q2,+),\
  a p2 = GAN_REP1_OP_AB(b,* c,yy,q2,+))
#define GAN_UPP22I_MULT1D(a,b,c,p1,p2,q1,q2)\
 (a p2 =  c q2 / b yy,\
  a p1 = (c q1 - b yx * a p2) / b xx)

/* symmetric/lower triangular square matrix definitions */
#define GAN_ST22_ZERO(A,t)\
           (GAN_TEST_OP1(A,Gan_SquMatrix22), gan_eval((A)->type=t),\
            GAN_REP22L_AS_C((A)->,=0.0))
#define GAN_ST22_COPY(A,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix22,Gan_SquMatrix22),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP22L_AA_C((B)->,=(A)->))
#define GAN_ST22_SCALE(A,a,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix22,Gan_SquMatrix22),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP22L_AAS_C((B)->,=(A)->,*(a)))
#define GAN_ST22_DIVIDE(A,a,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix22,Gan_SquMatrix22),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP22L_AAS_C((B)->,=(A)->,/(a)))
#define GAN_ST22_NEGATE(A,B,t)\
           (GAN_TEST_OP2(A,B,Gan_SquMatrix22,Gan_SquMatrix22),\
            assert((A)->type==t), gan_eval((B)->type=(A)->type),\
            GAN_REP22L_AA_C((B)->,=-(A)->))
#define GAN_ST22_ADD(A,B,C,t)\
         (GAN_TEST_OP3(A,B,C,Gan_SquMatrix22,Gan_SquMatrix22,Gan_SquMatrix22),\
          assert((A)->type==t && (B)->type==t), gan_eval((C)->type=(A)->type),\
          GAN_REP22L_AAA_C((C)->,=(A)->,+(B)->))
#define GAN_ST22_SUB(A,B,C,t)\
         (GAN_TEST_OP3(A,B,C,Gan_SquMatrix22,Gan_SquMatrix22,Gan_SquMatrix22),\
          assert((A)->type==t && (B)->type==t), gan_eval((C)->type=(A)->type),\
          GAN_REP22L_AAA_C((C)->,=(A)->,-(B)->))

/* declare functions specific to generic 2x2 matrices */
#include <gandalf/linalg/2x2mat_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

/* declare functions specific to symmetric 2x2 matrices */
#include <gandalf/linalg/2x2symmat_noc.h>
#include <gandalf/linalg/symmatrixf_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

/* declare functions specific to lower triangular 2x2 matrices */
#include <gandalf/linalg/2x2ltmat_noc.h>
#include <gandalf/linalg/squmatrixf_noc.h>
#include <gandalf/linalg/matrixf_noc.h>

/* declare functions specific to upper triangular 2x2 matrices */
#include <gandalf/linalg/2x2ltmatT_noc.h>
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

#endif /* #ifndef _GAN_2X2MATRIX_H */
