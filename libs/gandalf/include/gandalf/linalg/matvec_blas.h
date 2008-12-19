/**
 * File:          $RCSfile: matvec_blas.h,v $
 * Module:        C BLAS wrapper functions (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.12 $
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

#ifndef _GAN_MATVEC_BLAS_H
#define _GAN_MATVEC_BLAS_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/mat_gen.h>
#include <gandalf/linalg/mat_square.h>
#include <gandalf/linalg/vec_gen.h>

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

GANDALF_API Gan_Vector *gan_blas_axpy ( Gan_Vector *y,
                            double a, const Gan_Vector *x );
GANDALF_API Gan_Vector *gan_blas_gemv ( Gan_Vector *y, double alpha,
                            const Gan_Matrix *A, Gan_TposeFlag A_tr,
                            const Gan_Vector *x, double beta );
GANDALF_API Gan_Vector *gan_blas_scal ( Gan_Vector *x, double a );
GANDALF_API Gan_Matrix *gan_blas_ger ( Gan_Matrix *A, const Gan_Vector *x,
                           const Gan_Vector *y, double a );
GANDALF_API Gan_SquMatrix *gan_blas_spr ( Gan_SquMatrix *A,
                              const Gan_Vector *x, double a );
GANDALF_API Gan_Matrix *gan_blas_gemm ( Gan_Matrix *C, double alpha,
                            const Gan_Matrix *A, Gan_TposeFlag A_tr,
                            const Gan_Matrix *B, Gan_TposeFlag B_tr,
                            double beta );

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

#endif /* #ifndef _GAN_MATVEC_BLAS_H */
