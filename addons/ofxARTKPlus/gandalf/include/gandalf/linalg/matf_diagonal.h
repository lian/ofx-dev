/**
 * File:          $RCSfile: matf_diagonal.h,v $
 * Module:        Diagonal matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.9 $
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

#ifndef _GAN_MATF_DIAGONAL_H
#define _GAN_MATF_DIAGONAL_H

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

#ifndef GAN_MATRIXF_STRUCT_DEFINED
struct Gan_Matrix_f;
#endif

/* function declarations */
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_set_size ( Gan_SquMatrix_f *A,
                                         unsigned long size );
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_fill_va ( Gan_SquMatrix_f *A,
                                        unsigned long size, ... );
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_fill_const_q ( Gan_SquMatrix_f *A,
                                             unsigned long size, float value );
GANDALF_API Gan_Bool gan_diagmatf_read_va ( const Gan_SquMatrix_f *A, unsigned long size,
                                ... );
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_diag_thres ( Gan_SquMatrix_f *A,
                                           unsigned null_space,
                                           float thres, int *indexptr,
                                           float **elptr );
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_inv_diag_thres ( Gan_SquMatrix_f *A,
                                               unsigned null_space,
                                               float thres );
GANDALF_API struct Gan_Matrix_f *gan_diagmatIf_lmult_inf_q ( const Gan_SquMatrix_f *A,
                                                 struct Gan_Matrix_f *B,
                                                 struct Gan_Matrix_f *C );

/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a diagonal matrix.
 *
 * Allocates and returns a diagonal matrix with given \a size.
 *
 * Implemented as a macro call to gan_diagmatf_form_gen().
 * \sa gan_diagmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_alloc ( unsigned long size );
#else
#define gan_diagmatf_alloc(size) gan_diagmatf_form_gen(NULL,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a diagonal matrix.
 *
 * Forms and returns a diagonal matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is filled; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_diagmatf_form_gen().
 * \sa gan_diagmatf_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_form ( Gan_SquMatrix_f *A, unsigned long size );
#else
#define gan_diagmatf_form(A,size) gan_diagmatf_form_gen(A,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a diagonal matrix.
 *
 * Forms and returns a diagonal matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is filled; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated.
 *
 * Implemented as a macro call to gan_diagmatf_form_gen().
 * \sa gan_diagmatf_alloc() and gan_diagmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_form_data ( Gan_SquMatrix_f *A,
                                          unsigned long size,
                                          float *data, size_t data_size );
#else
#define gan_diagmatf_form_data(A,size,data,data_size)\
           gan_diagmatf_form_gen(A,size,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Allocates a diagonal matrix and fills it with a value.
 * \param size Size to set matrix to
 * \param value Value to set each element of the matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a diagonal matrix, sets its \a size, and fills it with zero.
 *
 * \sa gan_diagmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_diagmatf_fill_const_s ( unsigned long size, float value );
#else
#define gan_diagmatf_fill_const_s(size,v) gan_diagmatf_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of diagonal matrix, and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 *
 * Sets the \a size of diagonal matrix \a A, and fills \a A with zero.
 *
 * \sa gan_diagmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_diagmatf_fill_zero_q ( Gan_SquMatrix_f *A, unsigned long size );
#else
#define gan_diagmatf_fill_zero_q(A,size) gan_diagmatf_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates a diagonal matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a diagonal matrix, sets its \a size, and fills it with zero.
 *
 * \sa gan_diagmatf_fill_const_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_diagmatf_fill_zero_s ( unsigned long size );
#else
#define gan_diagmatf_fill_zero_s(size) gan_diagmatf_fill_const_s(size,0.0)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixMatrixProduct
 * \{
 */

/**
 * \brief Macro: Left multiply inverse of diagonal matrix by generic matrix.
 * \return Result as a new matrix.
 *
 * Left-multiply the inverse of a diagonal matrix \a A by a generic matrix
 * \a B, ignoring division by zero. The result is written into a new
 * matrix which is created and returned. The zero elements of \a A are
 * ignored, i.e. effectively assumed to be infinite.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_diagmatIf_lmult_inf_s ( const Gan_SquMatrix_f *A,
                                          Gan_Matrix_f *B );
#else
#define gan_diagmatIf_lmult_inf_s(A,B) (gan_diagmatIf_lmult_inf_q(A,B,NULL))
#endif

/**
 * \brief Macro: Left multiply inverse of diagonal matrix by generic matrix.
 * \return Result matrix \a B.
 *
 * Left-multiply the inverse of a diagonal matrix \a A by a generic matrix
 * \a B, ignoring division by zero. The result is written in-place in \a B,
 * which is also returned. The zero elements of \a A are ignored, i.e.
 * effectively assumed to be infinite.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_diagmatIf_lmult_inf_i ( const Gan_SquMatrix_f *A,
                                          Gan_Matrix_f *B );
#else
#define gan_diagmatIf_lmult_inf_i(A,B) (gan_diagmatIf_lmult_inf_q(A,B,B))
#endif

/**
 * \}
 */

/* not user functions */
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_form_gen ( Gan_SquMatrix_f *A,
                                         unsigned long size,
                                         float *data, size_t data_size );
GANDALF_API Gan_SquMatrix_f *gan_diagmatf_fill_vap ( Gan_SquMatrix_f *A,
                                         unsigned long size, va_list *aptr );

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

#endif /* #ifndef _GAN_MATF_DIAGONAL_H */
