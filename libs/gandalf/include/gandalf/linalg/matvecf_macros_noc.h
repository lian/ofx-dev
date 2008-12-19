/**
 * File:          $RCSfile: matvecf_macros_noc.h,v $
 * Module:        Matrix/vector macros
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.6 $
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

#ifndef _GAN_MATVECF_MACROS_H
#define _GAN_MATVECF_MACROS_H

#ifdef __cplusplus
extern "C" {
#endif

/* macros for testing the types of pointer arguments and then applying an
 * operation to them */
#define GAN_TEST_OP1(A,typeA) assert(sizeof(*(A))==sizeof(typeA))
#define GAN_TEST_OP2(A,B,typeA,typeB)\
  (assert(sizeof(*(A))==sizeof(typeA)&&sizeof(*(B))==sizeof(typeB)))
#define GAN_TEST_OP3(A,B,C,typeA,typeB,typeC)\
  (assert(sizeof(*(A))==sizeof(typeA)&&sizeof(*(B))==sizeof(typeB)&&\
          sizeof(*(C))==sizeof(typeC)))
#define GAN_TEST_OP4(A,B,C,D,typeA,typeB,typeC,typeD)\
  (assert(sizeof(*(A))==sizeof(typeA)&&sizeof(*(B))==sizeof(typeB)&&\
          sizeof(*(C))==sizeof(typeC)&&sizeof(*(D))==sizeof(typeD)))
#define GAN_TEST_OP5(A,B,C,D,E,typeA,typeB,typeC,typeD,typeE)\
  (assert(sizeof(*(A))==sizeof(typeA)&&sizeof(*(B))==sizeof(typeB)&&\
          sizeof(*(C))==sizeof(typeC)&&sizeof(*(D))==sizeof(typeD)&&\
          sizeof(*(E))==sizeof(typeE)))

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MATVECF_MACROS_H */
