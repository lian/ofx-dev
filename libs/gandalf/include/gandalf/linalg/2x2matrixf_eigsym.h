/**
 * File:          $RCSfile: 2x2matrixf_eigsym.h,v $
 * Module:        2x2 symmetric matrix eigenvalues/vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.1 $
 * Last edited:   $Date: 2003/02/24 10:06:35 $
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

#ifndef _GAN_MATRIX22F_EIGSYM_H
#define _GAN_MATRIX22F_EIGSYM_H

#include <gandalf/linalg/2x2matrixf.h>

#ifdef __cplusplus
extern "C" {
#endif

Gan_Bool gan_symmat22f_eigen ( Gan_SquMatrix22_f *A,
                               Gan_Vector2_f *W, Gan_Matrix22_f *Z );

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MATRIX22F_EIGSYM_H */
