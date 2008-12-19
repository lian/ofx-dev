/**
 * File:          $RCSfile: matvecf_clapack.h,v $
 * Module:        CLAPACK wrapper functions (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.7 $
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

#ifndef _GAN_MATVECF_CLAPACK_H
#define _GAN_MATVECF_CLAPACK_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/vecf_gen.h>
#include <gandalf/linalg/matf_gen.h>
#include <gandalf/linalg/matf_square.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup LinearAlgebra
 * \{
 */

/**
 * \addtogroup GeneralSizeMatVec
 * \{
 */

/**
 * \addtogroup GeneralSizeMatVecCLAPACK
 * \{
 */

GANDALF_API Gan_Bool gan_clapackf_pptrf ( Gan_SquMatrix_f *A, int *error_code );
GANDALF_API Gan_Bool gan_clapackf_pptri ( Gan_SquMatrix_f *A );
GANDALF_API Gan_Bool gan_clapackf_getf2 ( Gan_Matrix_f *A, long *ipiv, int *error_code );
GANDALF_API Gan_Bool gan_clapackf_getrf ( Gan_Matrix_f *A, long *ipiv, int *error_code );
GANDALF_API Gan_Bool gan_clapackf_getri ( Gan_Matrix_f *A, long *ipiv,
                              float *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapackf_geqrf ( Gan_Matrix_f *A, Gan_Vector_f *tau,
                              float *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapackf_gelqf ( Gan_Matrix_f *A, Gan_Vector_f *tau,
                              float *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapackf_orgqr ( Gan_Matrix_f *A, Gan_Vector_f *tau,
                              float *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapackf_orglq ( Gan_Matrix_f *A, Gan_Vector_f *tau,
                              float *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapackf_gesv ( Gan_Matrix_f *A, Gan_Matrix_f *B, long *ipiv );

#ifdef HAVE_LAPACK
/* these functions are not locally defined in Gandalf */
GANDALF_API Gan_Bool gan_clapackf_geev ( Gan_Matrix_f *A,
                             Gan_SquMatrix_f *WR,
                             Gan_SquMatrix_f *WI,
                             Gan_Matrix_f *VL, Gan_Matrix_f *VR,
                             float *work, unsigned long work_size );
#endif /* #ifdef HAVE_LAPACK */

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MATVECF_CLAPACK_H */
