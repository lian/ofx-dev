/**
 * File:          $RCSfile: repeat24_noc.h,v $
 * Module:        Macros for 2x4-fold repetition of matrix operations
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

#ifndef _GAN_REPEAT24_H
#define _GAN_REPEAT24_H

#include <gandalf/linalg/repeat4_noc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing dual two-fold repetitions */

#define GAN_FREP24_A(a,b,p1,p2,q1,q2,q3,q4,r11,r12,r13,r14,r21,r22,r23,r24)\
            (GAN_FREP4_A(a,b,p1##q1,p1##q2,p1##q3,p1##q4,r11,r12,r13,r14),\
             GAN_FREP4_A(a,b,p2##q1,p2##q2,p2##q3,p2##q4,r21,r22,r23,r24))
#define GAN_FREP24_A_C(a,b,r11,r12,r13,r14,r21,r22,r23,r24) \
           GAN_FREP24_A(a,b,x,y,x,y,z,w,r11,r12,r13,r14,r21,r22,r23,r24)

/* most general macros */
#define GAN_REP24_ABCS(a,b,c,d,p1,p2,q1,q2,q3,q4,r1,r2,s1,s2,s3,s4,t1,t2,u1,u2,u3,u4)\
 (GAN_REP4_ABCS(a,b,c,d,p1##q1,p1##q2,p1##q3,p1##q4,r1##s1,r1##s2,r1##s3,r1##s4,t1##u1,t1##u2,t1##u3,t1##u4),\
  GAN_REP4_ABCS(a,b,c,d,p2##q1,p2##q2,p2##q3,p2##q4,r2##s1,r2##s2,r2##s3,r2##s4,t2##u1,t2##u2,t2##u3,t2##u4))
#define GAN_REP24_ABC(a,b,c,p1,p2,q1,q2,q3,q4,r1,r2,s1,s2,s3,s4,t1,t2,u1,u2,u3,u4)\
 (GAN_REP4_ABC(a,b,c,p1##q1,p1##q2,p1##q3,p1##q4,r1##s1,r1##s2,r1##s3,r1##s4,t1##u1,t1##u2,t1##u3,t1##u4),\
  GAN_REP4_ABC(a,b,c,p2##q1,p2##q2,p2##q3,p2##q4,r2##s1,r2##s2,r2##s3,r2##s4,t2##u1,t2##u2,t2##u3,t2##u4))

#define GAN_REP24_AAAS(a,b,c,d,p1,p2,q1,q2,q3,q4)\
  GAN_REP24_ABCS(a,b,c,d,p1,p2,q1,q2,q3,q4,p1,p2,q1,q2,q3,q4,p1,p2,q1,q2,q3,q4)
#define GAN_REP24_AAA(a,b,c,p1,p2,q1,q2,q3,q4)\
   GAN_REP24_ABC(a,b,c,p1,p2,q1,q2,q3,q4,p1,p2,q1,q2,q3,q4,p1,p2,q1,q2,q3,q4)
#define GAN_REP24_ABS(a,b,c,p1,p2,q1,q2,q3,q4,r1,r2,s1,s2,s3,s4)\
 (GAN_REP4_ABS(a,b,c,p1##q1,p1##q2,p1##q3,p1##q4,r1##s1,r1##s2,r1##s3,r1##s4),\
  GAN_REP4_ABS(a,b,c,p2##q1,p2##q2,p2##q3,p2##q4,r2##s1,r2##s2,r2##s3,r2##s4))
#define GAN_REP24_AB(a,b,p1,p2,q1,q2,q3,q4,r1,r2,s1,s2,s3,s4)\
 (GAN_REP4_AB(a,b,p1##q1,p1##q2,p1##q3,p1##q4,r1##s1,r1##s2,r1##s3,r1##s4),\
  GAN_REP4_AB(a,b,p2##q1,p2##q2,p2##q3,p2##q4,r2##s1,r2##s2,r2##s3,r2##s4))
#define GAN_REP24_AAS(a,b,c,p1,p2,q1,q2,q3,q4)\
            GAN_REP24_ABS(a,b,c,p1,p2,q1,q2,q3,q4,p1,p2,q1,q2,q3,q4)
#define GAN_REP24_AA(a,b,p1,p2,q1,q2,q3,q4)\
            GAN_REP24_AB(a,b,p1,p2,q1,q2,q3,q4,p1,p2,q1,q2,q3,q4)
#define GAN_REP24_AS(a,b,p1,p2,q1,q2,q3,q4)\
 (GAN_REP4_AS(a,b,p1##q1,p1##q2,p1##q3,p1##q4),\
  GAN_REP4_AS(a,b,p2##q1,p2##q2,p2##q3,p2##q4))
#define GAN_REP24_A(a,p1,p2,q1,q2,q3,q4)\
 (GAN_REP4_A(a,p1##q1,p1##q2,p1##q3,p1##q4),\
  GAN_REP4_A(a,p2##q1,p2##q2,p2##q3,p2##q4))

/* macros specific to xx, xy etc coordinates */
#define GAN_REP24_AS_C(a,b) GAN_REP24_AS(a,b,x,y,x,y,z,w)
#define GAN_REP24_AAS_C(a,b,c) GAN_REP24_AAS(a,b,c,x,y,x,y,z,w)
#define GAN_REP24_AAAS_C(a,b,c,d) GAN_REP24_AAAS(a,b,c,d,x,y,x,y,z,w)
#define GAN_REP24_A_C(a) GAN_REP24_A(a,x,y,x,y,z,w)
#define GAN_REP24_AA_C(a,b) GAN_REP24_AA(a,b,x,y,x,y,z,w)
#define GAN_REP24_AAA_C(a,b,c) GAN_REP24_AAA(a,b,c,x,y,x,y,z,w)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT24_H */
