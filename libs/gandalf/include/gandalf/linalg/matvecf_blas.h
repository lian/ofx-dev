/**
 * File:          $RCSfile: matvecf_blas.h,v $
 * Module:        C BLAS wrapper functions (single precision)
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

#ifndef _GAN_MATVECF_BLAS_H
#define _GAN_MATVECF_BLAS_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/matf_gen.h>
#include <gandalf/linalg/matf_square.h>
#include <gandalf/linalg/vecf_gen.h>

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
 * \addtogroup GeneralSizeMatVecBLAS
 * \{
 */

GANDALF_API Gan_Vector_f *gan_blasf_axpy ( Gan_Vector_f *y,
                               float a, const Gan_Vector_f *x );
GANDALF_API Gan_Vector_f *gan_blasf_gemv ( Gan_Vector_f *y, float alpha,
                               const Gan_Matrix_f *A, Gan_TposeFlag A_tr,
                               const Gan_Vector_f *x, float beta );
GANDALF_API Gan_Vector_f *gan_blasf_scal ( Gan_Vector_f *x, float a );
GANDALF_API Gan_Matrix_f *gan_blasf_ger ( Gan_Matrix_f *A,
                              const Gan_Vector_f *x,
                              const Gan_Vector_f *y, float a );
GANDALF_API Gan_SquMatrix_f *gan_blasf_spr ( Gan_SquMatrix_f *A,
                                 const Gan_Vector_f *x, float a );
GANDALF_API Gan_Matrix_f *gan_blasf_gemm ( Gan_Matrix_f *C, float alpha,
                               const Gan_Matrix_f *A, Gan_TposeFlag A_tr,
                               const Gan_Matrix_f *B, Gan_TposeFlag B_tr,
                               float beta );

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

#endif /* #ifndef _GAN_MATVECF_BLAS_H */
