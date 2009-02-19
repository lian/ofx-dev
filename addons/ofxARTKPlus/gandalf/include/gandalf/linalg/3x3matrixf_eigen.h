/**
 * File:          $RCSfile: 3x3matrixf_eigen.h,v $
 * Module:        3x3 matrix eigenvalues and eigenvectors (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.7 $
 * Last edited:   $Date: 2003/01/31 18:57:10 $
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

#ifndef _GAN_MATRIX33F_EIGEN_H
#define _GAN_MATRIX33F_EIGEN_H

#include <gandalf/linalg/3x3matrixf.h>
#include <gandalf/common/complex.h>

#ifdef __cplusplus
extern "C" {
#endif

Gan_Bool gan_mat33f_eigen ( Gan_Matrix33_f *A, Gan_Complex_f W[3],
                            Gan_Matrix33_f *VL, Gan_Matrix33_f *VR );

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MATRIX33_EIGEN_H */
