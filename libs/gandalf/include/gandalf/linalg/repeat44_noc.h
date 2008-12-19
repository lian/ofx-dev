/**
 * File:          $RCSfile: repeat44_noc.h,v $
 * Module:        Macros for 4x4-fold repetition of matrix operations
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

#ifndef _GAN_REPEAT44_H
#define _GAN_REPEAT44_H

#include <gandalf/linalg/repeat1_noc.h>
#include <gandalf/linalg/repeat2_noc.h>
#include <gandalf/linalg/repeat3_noc.h>
#include <gandalf/linalg/repeat4_noc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing dual two-fold repetitions */

#define GAN_FREP44_A(a,b,p1,p2,p3,p4,q1,q2,q3,q4,r11,r12,r13,r14,r21,r22,r23,r24,r31,r32,r33,r34,r41,r42,r43,r44)\
(GAN_FREP4_A(a,b,p1##q1,p1##q2,p1##q3,p1##q4,r11,r12,r13,r14),\
 GAN_FREP4_A(a,b,p2##q1,p2##q2,p2##q3,p2##q4,r21,r22,r23,r24),\
 GAN_FREP4_A(a,b,p3##q1,p3##q2,p3##q3,p3##q4,r31,r32,r33,r34),\
 GAN_FREP4_A(a,b,p4##q1,p4##q2,p4##q3,p4##q4,r41,r42,r43,r44))
#define GAN_FREP44_A_C(a,b,r11,r12,r13,r14,r21,r22,r23,r24,r31,r32,r33,r34,r41,r42,r43,r44) \
        GAN_FREP44_A(a,b,x,y,z,w,x,y,z,w,r11,r12,r13,r14,r21,r22,r23,r24,r31,r32,r33,r34,r41,r42,r43,r44)

/* most general macros */
#define GAN_REP44_ABCS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4,t1,t2,t3,t4,u1,u2,u3,u4)\
 (GAN_REP4_ABCS(a,b,c,d,p1##q1,p1##q2,p1##q3,p1##q4,\
                        r1##s1,r1##s2,r1##s3,r1##s4,\
                        t1##u1,t1##u2,t1##u3,t1##u4),\
  GAN_REP4_ABCS(a,b,c,d,p2##q1,p2##q2,p2##q3,p2##q4,\
                        r2##s1,r2##s2,r2##s3,r2##s4,\
                        t2##u1,t2##u2,t2##u3,t2##u4),\
  GAN_REP4_ABCS(a,b,c,d,p3##q1,p3##q2,p3##q3,p3##q4,\
                        r3##s1,r3##s2,r3##s3,r3##s4,\
                        t3##u1,t3##u2,t3##u3,t3##u4),\
  GAN_REP4_ABCS(a,b,c,d,p4##q1,p4##q2,p4##q3,p4##q4,\
                        r4##s1,r4##s2,r4##s3,r4##s4,\
                        t4##u1,t4##u2,t4##u3,t4##u4))
#define GAN_REP44_ABC(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4,t1,t2,t3,t4,u1,u2,u3,u4)\
 (GAN_REP4_ABC(a,b,c,p1##q1,p1##q2,p1##q3,p1##q4,\
                     r1##s1,r1##s2,r1##s3,r1##s4,\
                     t1##u1,t1##u2,t1##u3,t1##u4),\
  GAN_REP4_ABC(a,b,c,p2##q1,p2##q2,p2##q3,p2##q4,\
                     r2##s1,r2##s2,r2##s3,r2##s4,\
                     t2##u1,t2##u2,t2##u3,t2##u4),\
  GAN_REP4_ABC(a,b,c,p3##q1,p3##q2,p3##q3,p3##q4,\
                     r3##s1,r3##s2,r3##s3,r3##s4,\
                     t3##u1,t3##u2,t3##u3,t3##u4),\
  GAN_REP4_ABC(a,b,c,p4##q1,p4##q2,p4##q3,p4##q4,\
                     r4##s1,r4##s2,r4##s3,r4##s4,\
                     t4##u1,t4##u2,t4##u3,t4##u4))

#define GAN_REP44_AAAS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4)\
   GAN_REP44_ABCS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)
#define GAN_REP44_AAA(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4)\
   GAN_REP44_ABC(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)

#define GAN_REP44_ABS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4)\
 (GAN_REP4_ABS(a,b,c,p1##q1,p1##q2,p1##q3,p1##q4,\
                     r1##s1,r1##s2,r1##s3,r1##s4),\
  GAN_REP4_ABS(a,b,c,p2##q1,p2##q2,p2##q3,p2##q4,\
                     r2##s1,r2##s2,r2##s3,r2##s4),\
  GAN_REP4_ABS(a,b,c,p3##q1,p3##q2,p3##q3,p3##q4,\
                     r3##s1,r3##s2,r3##s3,r3##s4),\
  GAN_REP4_ABS(a,b,c,p4##q1,p4##q2,p4##q3,p4##q4,\
                     r4##s1,r4##s2,r4##s3,r4##s4))
#define GAN_REP44_AB(a,b,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4)\
 (GAN_REP4_AB(a,b,p1##q1,p1##q2,p1##q3,p1##q4,\
                  r1##s1,r1##s2,r1##s3,r1##s4),\
  GAN_REP4_AB(a,b,p2##q1,p2##q2,p2##q3,p2##q4,\
                  r2##s1,r2##s2,r2##s3,r2##s4),\
  GAN_REP4_AB(a,b,p3##q1,p3##q2,p3##q3,p3##q4,\
                  r3##s1,r3##s2,r3##s3,r3##s4),\
  GAN_REP4_AB(a,b,p4##q1,p4##q2,p4##q3,p4##q4,\
                  r4##s1,r4##s2,r4##s3,r4##s4))

#define GAN_REP44_AAS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4)\
           GAN_REP44_ABS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)
#define GAN_REP44_AA(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
            GAN_REP44_AB(a,b,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)

#define GAN_REP44_AS(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
 (GAN_REP4_AS(a,b,p1##q1,p1##q2,p1##q3,p1##q4),\
  GAN_REP4_AS(a,b,p2##q1,p2##q2,p2##q3,p2##q4),\
  GAN_REP4_AS(a,b,p3##q1,p3##q2,p3##q3,p3##q4),\
  GAN_REP4_AS(a,b,p4##q1,p4##q2,p4##q3,p4##q4))
#define GAN_REP44_A(a,p1,p2,p3,p4,q1,q2,q3,q4)\
 (GAN_REP4_A(a,p1##q1,p1##q2,p1##q3,p1##q4),\
  GAN_REP4_A(a,p2##q1,p2##q2,p2##q3,p2##q4),\
  GAN_REP4_A(a,p3##q1,p3##q2,p3##q3,p3##q4),\
  GAN_REP4_A(a,p4##q1,p4##q2,p4##q3,p4##q4))

/* macros specific to xx, xy etc coordinates */
#define GAN_REP44_AS_C(a,b) GAN_REP44_AS(a,b,x,y,z,w,x,y,z,w)
#define GAN_REP44_AAS_C(a,b,c) GAN_REP44_AAS(a,b,c,x,y,z,w,x,y,z,w)
#define GAN_REP44_AAAS_C(a,b,c,d) GAN_REP44_AAAS(a,b,c,d,x,y,z,w,x,y,z,w)
#define GAN_REP44_A_C(a) GAN_REP44_A(a,x,y,z,w,x,y,z,w)
#define GAN_REP44_AA_C(a,b) GAN_REP44_AA(a,b,x,y,z,w,x,y,z,w)
#define GAN_REP44_AAA_C(a,b,c) GAN_REP44_AAA(a,b,c,x,y,z,w,x,y,z,w)

/* macro for transpose operation */
#define GAN_REP44_AAT(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
 (GAN_REP4_AB(a,b,p1##q1,p1##q2,p1##q3,p1##q4,p1##q1,p2##q1,p3##q1,p4##q1),\
  GAN_REP4_AB(a,b,p2##q1,p2##q2,p2##q3,p2##q4,p1##q2,p2##q2,p3##q2,p4##q2),\
  GAN_REP4_AB(a,b,p3##q1,p3##q2,p3##q3,p3##q4,p1##q3,p2##q3,p3##q3,p4##q3),\
  GAN_REP4_AB(a,b,p4##q1,p4##q2,p4##q3,p4##q4,p1##q4,p2##q4,p3##q4,p4##q4))
#define GAN_REP44_AAT_C(a,b) GAN_REP44_AAT(a,b,x,y,z,w,x,y,z,w)

/* macros for operations on lower triangle of matrices only */
#define GAN_FREP44L_A(a,b,p1,p2,p3,p4,q1,q2,q3,q4,r11,r21,r22,r31,r32,r33,r41,r42,r43,r44)\
 (GAN_FREP1_A(a,b,p1##q1,r11),\
  GAN_FREP2_A(a,b,p2##q1,p2##q2,r21,r22),\
  GAN_FREP3_A(a,b,p3##q1,p3##q2,p3##q3,r31,r32,r33),\
  GAN_FREP4_A(a,b,p4##q1,p4##q2,p4##q3,p4##q4,r41,r42,r43,r44))
#define GAN_FREP44L_A_C(a,b,r11,r21,r22,r31,r32,r33,r41,r42,r43,r44) \
           GAN_FREP44L_A(a,b,x,y,z,w,x,y,z,w,r11,r21,r22,r31,r32,r33,r41,r42,r43,r44)

#define GAN_REP44L_ABCS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4,t1,t2,t3,t4,u1,u2,u3,u4)\
 (GAN_REP1_ABCS(a,b,c,d,p1##q1,r1##s1,t1##u1),\
  GAN_REP2_ABCS(a,b,c,d,p2##q1,p2##q2,r2##s1,r2##s2,t2##u1,t2##u2),\
  GAN_REP3_ABCS(a,b,c,d,p3##q1,p3##q2,p3##q3,r3##s1,r3##s2,r3##s3,t3##u1,t3##u2,t3##u3),\
  GAN_REP4_ABCS(a,b,c,d,p4##q1,p4##q2,p4##q3,p4##q4,r4##s1,r4##s2,r4##s3,r4##s4,t4##u1,t4##u2,t4##u3,t4##u4))
#define GAN_REP44L_ABC(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4,t1,t2,t3,t4,u1,u2,u3,u4)\
 (GAN_REP1_ABC(a,b,c,p1##q1,r1##s1,t1##u1),\
  GAN_REP2_ABC(a,b,c,p2##q1,p2##q2,r2##s1,r2##s2,t2##u1,t2##u2),\
  GAN_REP3_ABC(a,b,c,p3##q1,p3##q2,p3##q3,r3##s1,r3##s2,r3##s3,t3##u1,t3##u2,t3##u3),\
  GAN_REP4_ABC(a,b,c,p4##q1,p4##q2,p4##q3,p4##q4,r4##s1,r4##s2,r4##s3,r4##s4,t4##u1,t4##u2,t4##u3,t4##u4))
#define GAN_REP44L_AAAS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4)\
           GAN_REP44L_ABCS(a,b,c,d,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)
#define GAN_REP44L_AAA(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4)\
           GAN_REP44L_ABC(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)
#define GAN_REP44L_ABS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4)\
 (GAN_REP1_ABS(a,b,c,p1##q1,r1##s1),\
  GAN_REP2_ABS(a,b,c,p2##q1,p2##q2,r2##s1,r2##s2),\
  GAN_REP3_ABS(a,b,c,p3##q1,p3##q2,p3##q3,r3##s1,r3##s2,r3##s3),\
  GAN_REP4_ABS(a,b,c,p4##q1,p4##q2,p4##q3,p4##q4,r4##s1,r4##s2,r4##s3,r4##s4))
#define GAN_REP44L_AB(a,b,p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4,s1,s2,s3,s4)\
 (GAN_REP1_AB(a,b,p1##q1,r1##s1),\
  GAN_REP2_AB(a,b,p2##q1,p2##q2,r2##s1,r2##s2),\
  GAN_REP3_AB(a,b,p3##q1,p3##q2,p3##q3,r3##s1,r3##s2,r3##s3),\
  GAN_REP4_AB(a,b,p4##q1,p4##q2,p4##q3,p4##q4,r4##s1,r4##s2,r4##s3,r4##s4))
#define GAN_REP44L_AAS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4)\
          GAN_REP44L_ABS(a,b,c,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)
#define GAN_REP44L_AA(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
           GAN_REP44L_AB(a,b,p1,p2,p3,p4,q1,q2,q3,q4,p1,p2,p3,p4,q1,q2,q3,q4)
#define GAN_REP44L_AS(a,b,p1,p2,p3,p4,q1,q2,q3,q4)\
 (GAN_REP1_AS(a,b,p1##q1),\
  GAN_REP2_AS(a,b,p2##q1,p2##q2),\
  GAN_REP3_AS(a,b,p3##q1,p3##q2,p3##q3),\
  GAN_REP4_AS(a,b,p4##q1,p4##q2,p4##q3,p4##q4))
#define GAN_REP44L_A(a,p1,p2,p3,p4,q1,q2,q3,q4)\
 (GAN_REP1_A(a,p1##q1),\
  GAN_REP2_A(a,p2##q1,p2##q2),\
  GAN_REP3_A(a,p3##q1,p3##q2,p3##q3),\
  GAN_REP4_A(a,p4##q1,p4##q2,p4##q3,p4##q4))
#define GAN_REP44L_AS_C(a,b) GAN_REP44L_AS(a,b,x,y,z,w,x,y,z,w)
#define GAN_REP44L_AAS_C(a,b,c) GAN_REP44L_AAS(a,b,c,x,y,z,w,x,y,z,w)
#define GAN_REP44L_AAAS_C(a,b,c,d) GAN_REP44L_AAAS(a,b,c,d,x,y,z,w,x,y,z,w)
#define GAN_REP44L_A_C(a) GAN_REP44L_A(a,x,y,z,w,x,y,z,w)
#define GAN_REP44L_AA_C(a,b) GAN_REP44L_AA(a,b,x,y,z,w,x,y,z,w)
#define GAN_REP44L_AAA_C(a,b,c) GAN_REP44L_AAA(a,b,c,x,y,z,w,x,y,z,w)
#define GAN_FREP44L_A_C(a,b,r11,r21,r22,r31,r32,r33,r41,r42,r43,r44)\
           GAN_FREP44L_A(a,b,x,y,z,w,x,y,z,w,r11,r21,r22,r31,r32,r33,r41,r42,r43,r44)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT44_H */
