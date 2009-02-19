/**
 * File:          $RCSfile: pseudo_inverse.h,v $
 * Module:        Psseudo-inverse solution of linear system (double precision)
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

#ifndef _GAN_PSEUDO_INVERSE_H
#define _GAN_PSEUDO_INVERSE_H

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
 * \addtogroup GeneralSizeMatrix
 * \{
 */

/**
 * \addtogroup GeneralSizeMatrixPseudoInverse
 * \{
 */

/// Structure to hold accumulated matrix/vector for computing pseudo-inverse
/// equation solution
typedef struct
{
   Gan_SquMatrix SaaT; /**< accumulated sum of vector outer products a*a^T */
   Gan_Matrix    SabT; /**< accumulated sum of vector outer products a*b^T,
                            as well as holding the solution matrix X */

   Gan_SquMatrix L; /**< Cholesky factorisation of SaaT */
   Gan_Matrix    X; /**< solution matrix */

   /// boolean variable indicating whether solution has been computed
   Gan_Bool solved;

   /// individual vectors
   Gan_Vector a, b;

   /// constraint matrices
   Gan_Matrix *C, *D;

   /// null-space dimension
   int null_space;

   /// singular value ratio threshold
   double ratio_thres;

   /// number of low singular values allowed
   int low_values_allowed;

   /// left singular vectors of SaaT
   Gan_Matrix *U;

   /// null-vector
   Gan_Vector *null_vector;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_PseudoInverseStruct;

GANDALF_API Gan_PseudoInverseStruct *gan_pseudoinv_form ( Gan_PseudoInverseStruct *psi,
                                              long max_asize,
                                              long max_bsize );

/**
 * \brief Macro: Allocates a pseudo-inverse equation solving structure.
 * \param max_asize The envisaged largest size of the matrix
 * \param max_bsize The envisaged largest number of solution vectors
 * \return Pointer to the allocated structure, or \c NULL on failure.
 *
 * Allocates/fills a structure with initial values to compute the
 * pseudo-inverse solution of a system of linear equations.
 *
 * Macro call to gan_pseudoinv_form().
 *
 * \sa gan_pseudoinv_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_PseudoInverseStruct *gan_pseudoinv_alloc ( long max_asize,
                                               long max_bsize );
#else
#define gan_pseudoinv_alloc(mAs,mBs) gan_pseudoinv_form(NULL,mAs,mBs)
#endif

GANDALF_API void     gan_pseudoinv_free ( Gan_PseudoInverseStruct *pis );
GANDALF_API Gan_Bool gan_pseudoinv_reset ( Gan_PseudoInverseStruct *pis,
                               long asize, long bsize );
GANDALF_API Gan_Bool gan_pseudoinv_increment ( Gan_PseudoInverseStruct *pis,
                                   double scale, ... );
GANDALF_API Gan_Bool gan_pseudoinv_decrement ( Gan_PseudoInverseStruct *pis,
                                   double scale, ... );
GANDALF_API Gan_Bool gan_pseudoinv_set_constraint ( Gan_PseudoInverseStruct *pis,
                                        Gan_Matrix *C, Gan_Matrix *D );
GANDALF_API Gan_Bool gan_pseudoinv_set_null_space ( Gan_PseudoInverseStruct *pis,
                                        int null_space );
GANDALF_API Gan_Bool gan_pseudoinv_set_ratio_thres ( Gan_PseudoInverseStruct *pis,
                                         double ratio_thres );
GANDALF_API Gan_Bool gan_pseudoinv_set_low_values_allowed ( Gan_PseudoInverseStruct *pis,
                                                int low_values_allowed );
GANDALF_API Gan_Bool gan_pseudoinv_solve ( Gan_PseudoInverseStruct *pis, int *error_code );
GANDALF_API Gan_Matrix *
         gan_pseudoinv_get_solution ( Gan_PseudoInverseStruct *pis );
GANDALF_API Gan_Vector *
         gan_pseudoinv_get_null_vector ( Gan_PseudoInverseStruct *pis );

/**
 * \}
 */

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

#endif /* #ifndef _GAN_PSEUDO_INVERSE_H */
