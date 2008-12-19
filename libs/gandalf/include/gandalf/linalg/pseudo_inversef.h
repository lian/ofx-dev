/**
 * File:          $RCSfile: pseudo_inversef.h,v $
 * Module:        Psseudo-inverse solution of linear system (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.8 $
 * Last edited:   $Date: 2002/04/18 14:56:25 $
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

#ifndef _GAN_PSEUDO_INVERSEF_H
#define _GAN_PSEUDO_INVERSEF_H

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
   Gan_SquMatrix_f SaaT; /**< accumulated sum of vector outer products a*a^T */
   Gan_Matrix_f    SabT; /**< accumulated sum of vector outer products a*b^T,
                              as well as holding the solution matrix X */

   Gan_SquMatrix_f L; /**< Cholesky factorisation of SaaT */
   Gan_Matrix_f    X; /**< solution matrix */

   /// boolean variable indicating whether solution has been computed
   Gan_Bool solved;

   /// individual vectors
   Gan_Vector_f a, b;

   /// constraint matrices
   Gan_Matrix_f *C, *D;

   /// null-space dimension
   int null_space;

   /// singular value ratio threshold
   float ratio_thres;

   /// number of low singular values allowed
   int low_values_allowed;

   /// left singular vectors of SaaT
   Gan_Matrix_f *U;

   /// null-vector
   Gan_Vector_f *null_vector;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_PseudoInverseStruct_f;

Gan_PseudoInverseStruct_f *gan_pseudoinvf_form (Gan_PseudoInverseStruct_f *psi,
                                                long max_asize,
                                                long max_bsize);

/**
 * \brief Macro: Allocates a pseudo-inverse equation solving structure.
 * \param max_asize The envisaged largest size of the matrix
 * \param max_bsize The envisaged largest number of solution vectors
 * \return Pointer to the allocated structure, or \c NULL on failure.
 *
 * Allocates/fills a structure with initial values to compute the
 * pseudo-inverse solution of a system of linear equations.
 *
 * Macro call to gan_pseudoinvf_form().
 *
 * \sa gan_pseudoinvf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
Gan_PseudoInverseStruct_f *gan_pseudoinvf_alloc ( long max_asize,
                                                  long max_bsize );
#else
#define gan_pseudoinvf_alloc(mAs,mBs) gan_pseudoinvf_form(NULL,mAs,mBs)
#endif

void     gan_pseudoinvf_free ( Gan_PseudoInverseStruct_f *pis );
Gan_Bool gan_pseudoinvf_reset ( Gan_PseudoInverseStruct_f *pis,
                                long asize, long bsize );
Gan_Bool gan_pseudoinvf_increment ( Gan_PseudoInverseStruct_f *pis,
                                    float scale, ... );
Gan_Bool gan_pseudoinvf_decrement ( Gan_PseudoInverseStruct_f *pis,
                                    float scale, ... );
Gan_Bool gan_pseudoinvf_set_constraint ( Gan_PseudoInverseStruct_f *pis,
                                         Gan_Matrix_f *C, Gan_Matrix_f *D );
Gan_Bool gan_pseudoinvf_set_null_space ( Gan_PseudoInverseStruct_f *pis,
                                         int null_space );
Gan_Bool gan_pseudoinvf_set_ratio_thres ( Gan_PseudoInverseStruct_f *pis,
                                          float ratio_thres );
Gan_Bool gan_pseudoinvf_set_low_values_allowed (Gan_PseudoInverseStruct_f *pis,
                                                int low_values_allowed );
Gan_Bool gan_pseudoinvf_solve ( Gan_PseudoInverseStruct_f *pis,
                                int *error_code );
Gan_Matrix_f *gan_pseudoinvf_get_solution ( Gan_PseudoInverseStruct_f *pis );
Gan_Vector_f *gan_pseudoinvf_get_null_vector ( Gan_PseudoInverseStruct_f *pis);

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

#endif /* #ifndef _GAN_PSEUDO_INVERSEF_H */
