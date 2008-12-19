/**
 * File:          $RCSfile: repeat2_noc.h,v $
 * Module:        Macros for 2-fold repetition of vector/matrix operations
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.5 $
 * Last edited:   $Date: 2002/04/18 14:56:25 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * Notes:         Not to be compiled separately
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

#ifndef _GAN_REPEAT2_H
#define _GAN_REPEAT2_H

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing two-fold repetitions */
#define GAN_REP2_AS(a,b,p1,p2) (a p1 b, a p2 b)
#define GAN_REP2_A(a,p1,p2) (a p1, a p2)
#define GAN_REP2_AS_C(a,b) GAN_REP2_AS(a,b,x,y)
#define GAN_REP2_A_C(a) GAN_REP2_A(a,x,y)

#define GAN_FREP2_A(a,b,p1,p2,q1,q2) (a p1 b q1, a p2 b q2)
#define GAN_FREP2_A_C(a,b,p1,p2) GAN_FREP2_A(a,b,x,y,p1,p2)

#define GAN_REP2_AB(a,b,p1,p2,q1,q2) (a p1 b q1, a p2 b q2)
#define GAN_REP2_AA(a,b,p1,p2) GAN_REP2_AB(a,b,p1,p2,p1,p2)
#define GAN_REP2_AA_C(a,b) GAN_REP2_AA(a,b,x,y)

#define GAN_REP2_ABS(a,b,c,p1,p2,q1,q2) (a p1 b q1 c, a p2 b q2 c)
#define GAN_REP2_AAS(a,b,c,p1,p2) GAN_REP2_ABS(a,b,c,p1,p2,p1,p2)
#define GAN_REP2_AAS_C(a,b,c) GAN_REP2_AAS(a,b,c,x,y)

#define GAN_REP2_AB(a,b,p1,p2,q1,q2) (a p1 b q1, a p2 b q2)
#define GAN_REP2_AA(a,b,p1,p2) GAN_REP2_AB(a,b,p1,p2,p1,p2)
#define GAN_REP2_AA_C(a,b) GAN_REP2_AA(a,b,x,y)

#define GAN_REP2_ABCS(a,b,c,d,p1,p2,q1,q2,r1,r2)\
           (a p1 b q1 c r1 d, a p2 b q2 c r2 d)
#define GAN_REP2_ABC(a,b,c,p1,p2,q1,q2,r1,r2)\
           (a p1 b q1 c r1, a p2 b q2 c r2)
#define GAN_REP2_AAA(a,b,c,p1,p2) GAN_REP2_ABC(a,b,c,p1,p2,p1,p2,p1,p2)
#define GAN_REP2_AAA_C(a,b,c) GAN_REP2_AAA(a,b,c,x,y)

#define GAN_REP2_OP_AB(a,b,p1,p2,q1,q2,op)\
           (a p1 b q1 op a p2 b q2)
#define GAN_REP2_OP_AA(a,b,p1,p2,op) GAN_REP2_OP_AB(a,b,p1,p2,p1,p2,op)
#define GAN_REP2_OP_AA_C(a,b,op) GAN_REP2_OP_AA(a,b,x,y,op)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT2_H */
