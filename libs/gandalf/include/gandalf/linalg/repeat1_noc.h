/**
 * File:          $RCSfile: repeat1_noc.h,v $
 * Module:        Macros for 1-fold repetition of vector/matrix operations
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

#ifndef _GAN_REPEAT1_H
#define _GAN_REPEAT1_H

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing one-fold repetitions (for consistency) */
#define GAN_REP1_AS(a,b,p1) (a p1 b)
#define GAN_REP1_A(a,p1) (a p1)
#define GAN_REP1_A_C(a,b) GAN_REP1_A(a,b,x)

#define GAN_FREP1_A(a,b,p1,q1) (a p1 b q1)
#define GAN_FREP1_A_C(a,b,p1) GAN_FREP1_A(a,b,x,p1)

#define GAN_REP1_ABS(a,b,c,p1,q1) (a p1 b q1 c)
#define GAN_REP1_AAS(a,b,c,p1) GAN_REP1_ABS(a,b,c,p1,p1)
#define GAN_REP1_AAS_C(a,b,c) GAN_REP1_AAS(a,b,c,x)

#define GAN_REP1_AB(a,b,p1,q1) (a p1 b q1)
#define GAN_REP1_AA(a,b,p1) GAN_REP1_AB(a,b,p1,p1)
#define GAN_REP1_AA_C(a,b) GAN_REP1_AA(a,b,x)

#define GAN_REP1_ABCS(a,b,c,d,p1,q1,r1) (a p1 b q1 c r1 d)
#define GAN_REP1_ABC(a,b,c,p1,q1,r1) (a p1 b q1 c r1)
#define GAN_REP1_AAA(a,b,c,p1) GAN_REP1_ABC(a,b,c,p1,p1,p1)
#define GAN_REP1_AAA_C(a,b,c) GAN_REP1_AAA(a,b,c,x)

#define GAN_REP1_OP_AB(a,b,p1,q1,op) (a p1 b q1)
#define GAN_REP1_OP_AA(a,b,p1,op) GAN_REP1_OP_AB(a,b,p1,p1,op)
#define GAN_REP1_OP_AA_C(a,b,op) GAN_REP1_OP_AA(a,b,x,op)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT1_H */
