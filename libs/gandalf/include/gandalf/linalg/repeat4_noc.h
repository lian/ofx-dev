/**
 * File:          $RCSfile: repeat4_noc.h,v $
 * Module:        Macros for 4-fold repetition of vector/matrix operations
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

#ifndef _GAN_REPEAT4_H
#define _GAN_REPEAT4_H

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing four-fold repetitions */
#define GAN_REP4_AS(a,b,p1,p2,p3,p4) (a p1 b, a p2 b, a p3 b, a p4 b)
#define GAN_REP4_AS_C(a,b) GAN_REP4_AS(a,b,x,y,z,w)
#define GAN_REP4_A(a,p1,p2,p3,p4) (a p1, a p2, a p3, a p4)
#define GAN_REP4_A_C(a) GAN_REP4_A(a,x,y,z,w)

#define GAN_FREP4_A(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
    (a p1 b q1, a p2 b q2,\
     a p3 b q3, a p4 b q4)
#define GAN_FREP4_A_C(a,b,p1,p2,p3,p4) GAN_FREP4_A(a,b,x,y,z,w,p1,p2,p3,p4)

#define GAN_REP4_ABS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4)\
           (a p1 b q1 c, a p2 b q2 c, a p3 b q3 c, a p4 b q4 c)
#define GAN_REP4_AAS(a,b,c,p1,p2,p3,p4)\
           GAN_REP4_ABS(a,b,c,p1,p2,p3,p4,p1,p2,p3,p4)
#define GAN_REP4_AAS_C(a,b,c) GAN_REP4_AAS(a,b,c,x,y,z,w)

#define GAN_REP4_AB(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
           (a p1 b q1, a p2 b q2, a p3 b q3, a p4 b q4)
#define GAN_REP4_AA(a,b,p1,p2,p3,p4)\
           GAN_REP4_AB(a,b,p1,p2,p3,p4,p1,p2,p3,p4)
#define GAN_REP4_AA_C(a,b) GAN_REP4_AA(a,b,x,y,z,w)

#define GAN_REP4_ABCS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4)\
     (a p1 b q1 c r1 d, a p2 b q2 c r2 d, a p3 b q3 c r3 d, a p4 b q4 c r4 d)
#define GAN_REP4_ABC(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4)\
     (a p1 b q1 c r1, a p2 b q2 c r2, a p3 b q3 c r3, a p4 b q4 c r4)
#define GAN_REP4_AAA(a,b,c,p1,p2,p3,p4)\
           GAN_REP4_ABC(a,b,c,p1,p2,p3,p4,p1,p2,p3,p4,p1,p2,p3,p4)
#define GAN_REP4_AAA_C(a,b,c) GAN_REP4_AAA(a,b,c,x,y,z,w)

#define GAN_REP4_OP_AB(a,b,p1,p2,p3,p4,q1,q2,q3,q4,op)\
        (a p1 b q1 op a p2 b q2 op a p3 b q3 op a p4 b q4)
#define GAN_REP4_OP_AA(a,b,p1,p2,p3,p4,op)\
           GAN_REP4_OP_AB(a,b,p1,p2,p3,p4,p1,p2,p3,p4,op)
#define GAN_REP4_OP_AA_C(a,b,op) GAN_REP4_OP_AA(a,b,x,y,z,w,op)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT4_H */
