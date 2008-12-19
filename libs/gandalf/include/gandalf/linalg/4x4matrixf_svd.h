/**
 * File:          $RCSfile: 4x4matrixf_svd.h,v $
 * Module:        4x4 matrix singular value decomposition (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.5 $
 * Last edited:   $Date: 2002/04/18 14:56:23 $
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

#ifndef _GAN_MATRIX44F_SVD_H
#define _GAN_MATRIX44F_SVD_H

#include <gandalf/linalg/4x4matrixf.h>

#ifdef __cplusplus
extern "C" {
#endif

Gan_Bool gan_mat44f_svd ( Gan_Matrix44_f *A,
                          Gan_Matrix44_f *U, Gan_Vector4_f *W,
                          Gan_Matrix44_f *VT );
Gan_Bool gan_mat44Tf_svd ( Gan_Matrix44_f *A,
                           Gan_Matrix44_f *U, Gan_Vector4_f *W,
                           Gan_Matrix44_f *VT );

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MATRIX44_SVD_H */
