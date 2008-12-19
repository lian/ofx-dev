/**
 * File:          $RCSfile: matvec_clapack.h,v $
 * Module:        CLAPACK wrapper functions (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.15 $
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

#ifndef _GAN_MATVEC_CLAPACK_H
#define _GAN_MATVEC_CLAPACK_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/vec_gen.h>
#include <gandalf/linalg/mat_gen.h>
#include <gandalf/linalg/mat_square.h>

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

GANDALF_API Gan_Bool gan_clapack_pptrf ( Gan_SquMatrix *A, int *error_code );
GANDALF_API Gan_Bool gan_clapack_pptri ( Gan_SquMatrix *A );
GANDALF_API Gan_Bool gan_clapack_getf2 ( Gan_Matrix *A, long *ipiv, int *error_code );
GANDALF_API Gan_Bool gan_clapack_getrf ( Gan_Matrix *A, long *ipiv, int *error_code );
GANDALF_API Gan_Bool gan_clapack_getri ( Gan_Matrix *A, long *ipiv,
                             double *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapack_geqrf ( Gan_Matrix *A, Gan_Vector *tau,
                             double *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapack_gelqf ( Gan_Matrix *A, Gan_Vector *tau,
                             double *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapack_orgqr ( Gan_Matrix *A, Gan_Vector *tau,
                             double *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapack_orglq ( Gan_Matrix *A, Gan_Vector *tau,
                             double *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapack_gesv ( Gan_Matrix *A, Gan_Matrix *B, long *ipiv );
                            
#ifdef HAVE_LAPACK
/* these functions are not locally defined in Gandalf */
GANDALF_API Gan_Bool gan_clapack_geev ( Gan_Matrix *A,
                            Gan_SquMatrix *WR, Gan_SquMatrix *WI,
                            Gan_Matrix *VL, Gan_Matrix *VR,
                            double *work, unsigned long work_size );
GANDALF_API Gan_Bool gan_clapack_gees ( Gan_Matrix *A, Gan_Matrix *Z,
                            double *work, unsigned long work_size );
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

#endif /* #ifndef _GAN_MATVEC_CLAPACK_H */
