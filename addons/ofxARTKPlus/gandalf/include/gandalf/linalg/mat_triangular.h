/**
 * File:          $RCSfile: mat_triangular.h,v $
 * Module:        Lower/upper triangular matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.18 $
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

#ifndef _GAN_MAT_TRIANGULAR_H
#define _GAN_MAT_TRIANGULAR_H

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

/* function declarations */
GANDALF_API Gan_SquMatrix *gan_ltmat_set_size ( Gan_SquMatrix *L, unsigned long size );
GANDALF_API Gan_SquMatrix *gan_utmat_set_size ( Gan_SquMatrix *U, unsigned long size );
GANDALF_API Gan_SquMatrix *gan_ltmat_fill_va ( Gan_SquMatrix *L, unsigned long size, ... );
GANDALF_API Gan_SquMatrix *gan_utmat_fill_va ( Gan_SquMatrix *U, unsigned long size, ... );
GANDALF_API Gan_SquMatrix *gan_ltmat_fill_const_q ( Gan_SquMatrix *L,
                                        unsigned long size, double value );
GANDALF_API Gan_SquMatrix *gan_utmat_fill_const_q ( Gan_SquMatrix *U,
                                        unsigned long size, double value );
GANDALF_API Gan_Bool gan_ltmat_read_va ( const Gan_SquMatrix *L, unsigned long size, ... );
GANDALF_API Gan_Bool gan_utmat_read_va ( const Gan_SquMatrix *U, unsigned long size, ... );

/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a lower triangular matrix.
 *
 * Allocates and returns a lower triangular matrix with given \a size.
 *
 * Implemented as a macro call to gan_ltmat_form_gen().
 * See also gan_ltmat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_ltmat_alloc ( unsigned long size );
#else
#define gan_ltmat_alloc(size) gan_ltmat_form_gen(NULL,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a lower triangular matrix.
 *
 * Forms and returns a lower triangular matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_ltmat_form_gen().
 *
 * \sa gan_ltmat_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_ltmat_form ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_ltmat_form(A,size) gan_ltmat_form_gen(A,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a square lower triangular matrix.
 *
 * Forms and returns a square lower triangular matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated.
 *
 * Implemented as a macro call to gan_ltmat_form_gen().
 * \sa gan_ltmat_alloc() and gan_ltmat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_ltmat_form_data ( Gan_SquMatrix *A, unsigned long size,
                                     double *data, size_t data_size );
#else
#define gan_ltmat_form_data(A,size,data,data_size)\
           gan_ltmat_form_gen(A,size,data,data_size)
#endif

/**
 * \brief Macro: Allocate and return a upper triangular matrix.
 *
 * Allocates and returns a upper triangular matrix with given \a size.
 *
 * Implemented as a macro call to gan_utmat_form_gen().
 * \sa gan_utmat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_utmat_alloc ( unsigned long size );
#else
#define gan_utmat_alloc(size) gan_utmat_form_gen(NULL,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a upper triangular matrix.
 *
 * Forms and returns a upper triangular matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_utmat_form_gen().
 * \sa gan_utmat_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_utmat_form ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_utmat_form(A,size) gan_utmat_form_gen(A,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a square upper triangular matrix.
 *
 * Forms and returns a square upper triangular matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated.
 *
 * Implemented as a macro call to gan_utmat_form_gen().
 * \sa gan_utmat_alloc() and gan_utmat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_utmat_form_data ( Gan_SquMatrix *A, unsigned long size,
                                     void *data, size_t data_size );
#else
#define gan_utmat_form_data(A,size,data,data_size)\
           gan_utmat_form_gen(A,size,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Allocates a lower triangular matrix and fills it with a value.
 * \param size Size to set matrix to
 * \param value Value to set each element of the matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a lower triangular matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_ltmat_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_ltmat_fill_const_s ( unsigned long size, double value );
#else
#define gan_ltmat_fill_const_s(size,v) gan_ltmat_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of lower triangular matrix and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 * Sets the \a size of lower triangular matrix \a A, and fills \a A with zero.
 *
 * \sa gan_ltmat_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_ltmat_fill_zero_q ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_ltmat_fill_zero_q(A,size) gan_ltmat_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates a lower triangular matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a lower triangular matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_ltmat_fill_const_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_ltmat_fill_zero_s ( unsigned long size );
#else
#define gan_ltmat_fill_zero_s(size) gan_ltmat_fill_const_s(size,0.0)
#endif

/**
 * \brief Macro: Allocates an upper triangular matrix and fills it with a value.
 * \param size Size to set matrix to
 * \param value Value to set each element of the matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates an upper triangular matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_utmat_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_utmat_fill_const_s ( unsigned long size, double value );
#else
#define gan_utmat_fill_const_s(size,v) gan_utmat_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of upper triangular matrix and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 *
 * Sets the size of upper triangular matrix \a A, and fills \a A with zero.
 *
 * \sa gan_utmat_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_utmat_fill_zero_q ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_utmat_fill_zero_q(A,size) gan_utmat_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates an upper triangular matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates an upper triangular matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_utmat_fill_const_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_utmat_fill_zero_s ( unsigned long size );
#else
#define gan_utmat_fill_zero_s(size) gan_utmat_fill_const_s(size,0.0)
#endif

/**
 * \}
 */

/* not user functions */
GANDALF_API Gan_SquMatrix *gan_ltmat_form_gen ( Gan_SquMatrix *A, unsigned long size,
                                    double *data, size_t data_size );
GANDALF_API Gan_SquMatrix *gan_utmat_form_gen ( Gan_SquMatrix *A, unsigned long size,
                                    double *data, size_t data_size );
GANDALF_API Gan_SquMatrix *gan_ltmat_fill_vap ( Gan_SquMatrix *L,
                                    unsigned long size, va_list *aptr );
GANDALF_API Gan_SquMatrix *gan_utmat_fill_vap ( Gan_SquMatrix *U,
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

#endif /* #ifndef _GAN_MAT_TRIANGULAR_H */
