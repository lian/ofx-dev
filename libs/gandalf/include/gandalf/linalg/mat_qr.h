/**
 * File:          $RCSfile: mat_qr.h,v $
 * Module:        Matrix QR decomposition (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.13 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
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

#ifndef _GAN_MAT_QR_H
#define _GAN_MAT_QR_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GAN_MATRIX_STRUCT_DEFINED
struct Gan_Matrix;
#endif

#ifndef GAN_SQUMATRIX_STRUCT_DEFINED
struct Gan_SquMatrix;
#endif

GANDALF_API Gan_Bool gan_mat_qr ( struct Gan_Matrix *A,
                      struct Gan_Matrix *Q, struct Gan_SquMatrix *R,
                      double *work, unsigned long work_size );

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MAT_QR_H */
