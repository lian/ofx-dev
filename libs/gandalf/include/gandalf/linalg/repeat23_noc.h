/**
 * File:          $RCSfile: repeat23_noc.h,v $
 * Module:        Macros for 2x3-fold repetition of matrix operations
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

#ifndef _GAN_REPEAT23_H
#define _GAN_REPEAT23_H

#include <gandalf/linalg/repeat3_noc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* macros for constructing dual two-fold repetitions */

#define GAN_FREP23_A(a,b,p1,p2,q1,q2,q3,r11,r12,r13,r21,r22,r23)\
            (GAN_FREP3_A(a,b,p1##q1,p1##q2,p1##q3,r11,r12,r13),\
             GAN_FREP3_A(a,b,p2##q1,p2##q2,p2##q3,r21,r22,r23))
#define GAN_FREP23_A_C(a,b,r11,r12,r13,r21,r22,r23) \
           GAN_FREP23_A(a,b,x,y,x,y,z,r11,r12,r13,r21,r22,r23)

/* most general macros */
#define GAN_REP23_ABCS(a,b,c,d,p1,p2,q1,q2,q3,r1,r2,s1,s2,s3,t1,t2,u1,u2,u3)\
 (GAN_REP3_ABCS(a,b,c,d,p1##q1,p1##q2,p1##q3,r1##s1,r1##s2,r1##s3,t1##u1,t1##u2,t1##u3),\
  GAN_REP3_ABCS(a,b,c,d,p2##q1,p2##q2,p2##q3,r2##s1,r2##s2,r2##s3,t2##u1,t2##u2,t2##u3))
#define GAN_REP23_ABC(a,b,c,p1,p2,q1,q2,q3,r1,r2,s1,s2,s3,t1,t2,u1,u2,u3)\
 (GAN_REP3_ABC(a,b,c,p1##q1,p1##q2,p1##q3,r1##s1,r1##s2,r1##s3,t1##u1,t1##u2,t1##u3),\
  GAN_REP3_ABC(a,b,c,p2##q1,p2##q2,p2##q3,r2##s1,r2##s2,r2##s3,t2##u1,t2##u2,t2##u3))

#define GAN_REP23_AAAS(a,b,c,d,p1,p2,q1,q2,q3)\
   GAN_REP23_ABCS(a,b,c,d,p1,p2,q1,q2,q3,p1,p2,q1,q2,q3,p1,p2,q1,q2,q3)
#define GAN_REP23_AAA(a,b,c,p1,p2,q1,q2,q3)\
   GAN_REP23_ABC(a,b,c,p1,p2,q1,q2,q3,p1,p2,q1,q2,q3,p1,p2,q1,q2,q3)
#define GAN_REP23_ABS(a,b,c,p1,p2,q1,q2,q3,r1,r2,s1,s2,s3)\
 (GAN_REP3_ABS(a,b,c,p1##q1,p1##q2,p1##q3,r1##s1,r1##s2,r1##s3),\
  GAN_REP3_ABS(a,b,c,p2##q1,p2##q2,p2##q3,r2##s1,r2##s2,r2##s3))
#define GAN_REP23_AB(a,b,p1,p2,q1,q2,q3,r1,r2,s1,s2,s3)\
 (GAN_REP3_AB(a,b,p1##q1,p1##q2,p1##q3,r1##s1,r1##s2,r1##s3),\
  GAN_REP3_AB(a,b,p2##q1,p2##q2,p2##q3,r2##s1,r2##s2,r2##s3))
#define GAN_REP23_AAS(a,b,c,p1,p2,q1,q2,q3)\
            GAN_REP23_ABS(a,b,c,p1,p2,q1,q2,q3,p1,p2,q1,q2,q3)
#define GAN_REP23_AA(a,b,p1,p2,q1,q2,q3)\
            GAN_REP23_AB(a,b,p1,p2,q1,q2,q3,p1,p2,q1,q2,q3)
#define GAN_REP23_AS(a,b,p1,p2,q1,q2,q3)\
 (GAN_REP3_AS(a,b,p1##q1,p1##q2,p1##q3),\
  GAN_REP3_AS(a,b,p2##q1,p2##q2,p2##q3))
#define GAN_REP23_A(a,p1,p2,q1,q2,q3)\
 (GAN_REP3_A(a,p1##q1,p1##q2,p1##q3),\
  GAN_REP3_A(a,p2##q1,p2##q2,p2##q3))

/* macros specific to xx, xy etc coordinates */
#define GAN_REP23_AS_C(a,b) GAN_REP23_AS(a,b,x,y,x,y,z)
#define GAN_REP23_AAS_C(a,b,c) GAN_REP23_AAS(a,b,c,x,y,x,y,z)
#define GAN_REP23_AAAS_C(a,b,c,d) GAN_REP23_AAAS(a,b,c,d,x,y,x,y,z)
#define GAN_REP23_A_C(a) GAN_REP23_A(a,x,y,x,y,z)
#define GAN_REP23_AA_C(a,b) GAN_REP23_AA(a,b,x,y,x,y,z)
#define GAN_REP23_AAA_C(a,b,c) GAN_REP23_AAA(a,b,c,x,y,x,y,z)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_REPEAT23_H */
