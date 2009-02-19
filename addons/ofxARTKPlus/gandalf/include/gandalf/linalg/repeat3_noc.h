/**
 * File:          $RCSfile: repeat3_noc.h,v $
 * Module:        Macros for 3-fold repetition of vector/matrix operations
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

#ifndef _GAN_REPEAT3_H
#define _GAN_REPEAT3_H

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing three-fold repetitions */
#define GAN_REP3_AS(a,b,p1,p2,p3) (a p1 b, a p2 b, a p3 b)
#define GAN_REP3_AS_C(a,b) GAN_REP3_AS(a,b,x,y,z)
#define GAN_REP3_A(a,p1,p2,p3) (a p1, a p2, a p3)
#define GAN_REP3_A_C(a) GAN_REP3_A(a,x,y,z)

#define GAN_FREP3_A(a,b,p1,p2,p3,q1,q2,q3) (a p1 b q1, a p2 b q2, a p3 b q3)
#define GAN_FREP3_A_C(a,b,p1,p2,p3) GAN_FREP3_A(a,b,x,y,z,p1,p2,p3)


#define GAN_REP3_ABS(a,b,c,p1,p2,p3,q1,q2,q3)\
           (a p1 b q1 c, a p2 b q2 c, a p3 b q3 c)
#define GAN_REP3_AAS(a,b,c,p1,p2,p3) GAN_REP3_ABS(a,b,c,p1,p2,p3,p1,p2,p3)
#define GAN_REP3_AAS_C(a,b,c) GAN_REP3_AAS(a,b,c,x,y,z)

#define GAN_REP3_AB(a,b,p1,p2,p3,q1,q2,q3)\
           (a p1 b q1, a p2 b q2, a p3 b q3)
#define GAN_REP3_AA(a,b,p1,p2,p3) GAN_REP3_AB(a,b,p1,p2,p3,p1,p2,p3)
#define GAN_REP3_AA_C(a,b) GAN_REP3_AA(a,b,x,y,z)

#define GAN_REP3_ABCS(a,b,c,d,p1,p2,p3,q1,q2,q3,r1,r2,r3)\
           (a p1 b q1 c r1 d, a p2 b q2 c r2 d, a p3 b q3 c r3 d)
#define GAN_REP3_ABC(a,b,c,p1,p2,p3,q1,q2,q3,r1,r2,r3)\
           (a p1 b q1 c r1, a p2 b q2 c r2, a p3 b q3 c r3)
#define GAN_REP3_AAA(a,b,c,p1,p2,p3)\
        GAN_REP3_ABC(a,b,c,p1,p2,p3,p1,p2,p3,p1,p2,p3)
#define GAN_REP3_AAA_C(a,b,c) GAN_REP3_AAA(a,b,c,x,y,z)

#define GAN_REP3_OP_AB(a,b,p1,p2,p3,q1,q2,q3,op)\
           (a p1 b q1 op a p2 b q2 op a p3 b q3)
#define GAN_REP3_OP_AA(a,b,p1,p2,p3,op)\
           GAN_REP3_OP_AB(a,b,p1,p2,p3,p1,p2,p3,op)
#define GAN_REP3_OP_AA_C(a,b,op) GAN_REP3_OP_AA(a,b,x,y,z,op)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT3_H */
