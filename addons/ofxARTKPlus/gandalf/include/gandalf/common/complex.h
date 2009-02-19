/**
 * File:          $RCSfile: complex.h,v $
 * Module:        Complex numbers
 * Part of:       Gandalf Library 
 *
 * Revision:      
 * Last edited:   
 * Author:        Michael Lincoln
 * Copyright:     (c) 2002 University of Essex
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

#ifndef _GAN_COMPLEX_H
#define _GAN_COMPLEX_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/// Structure definition for double precision complex number
typedef struct Gan_Complex
{
   /// Real part
   double r;

   /// Imaginary part
   double i;
} Gan_Complex, Gan_Complex_d;

/// Structure definition for single precision complex number
typedef struct Gan_Complex_f
{
   /// Real part
   float r;

   /// Imaginary part
   float i;
} Gan_Complex_f;

/**
 * \}
 */

#ifdef __cplusplus
}
#endif



#endif /* #ifndef _GAN_COMPLEX_H */
