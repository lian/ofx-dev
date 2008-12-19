/**
 * File:          $RCSfile: matf_triangular.h,v $
 * Module:        Lower/upper triangular matrices (single precision)
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

#ifndef _GAN_MATF_TRIANGULAR_H
#define _GAN_MATF_TRIANGULAR_H

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

/* function declarations */
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_set_size ( Gan_SquMatrix_f *L,
                                       unsigned long size );
GANDALF_API Gan_SquMatrix_f *gan_utmatf_set_size ( Gan_SquMatrix_f *U,
                                       unsigned long size );
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_fill_va ( Gan_SquMatrix_f *L,
                                      unsigned long size, ... );
GANDALF_API Gan_SquMatrix_f *gan_utmatf_fill_va ( Gan_SquMatrix_f *U,
                                      unsigned long size, ... );
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_fill_const_q ( Gan_SquMatrix_f *L,
                                           unsigned long size, float value );
GANDALF_API Gan_SquMatrix_f *gan_utmatf_fill_const_q ( Gan_SquMatrix_f *U,
                                           unsigned long size, float value );
GANDALF_API Gan_Bool gan_ltmatf_read_va ( const Gan_SquMatrix_f *L, unsigned long size, ... );
GANDALF_API Gan_Bool gan_utmatf_read_va ( const Gan_SquMatrix_f *U, unsigned long size, ... );

/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a lower triangular matrix.
 *
 * Allocates and returns a lower triangular matrix with given \a size.
 *
 * Implemented as a macro call to gan_ltmatf_form_gen().
 * See also gan_ltmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_alloc ( unsigned long size );
#else
#define gan_ltmatf_alloc(size) gan_ltmatf_form_gen(NULL,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a lower triangular matrix.
 *
 * Forms and returns a lower triangular matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_ltmatf_form_gen().
 *
 * \sa gan_ltmatf_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_form ( Gan_SquMatrix_f *A, unsigned long size );
#else
#define gan_ltmatf_form(A,size) gan_ltmatf_form_gen(A,size,NULL,0)
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
 * Implemented as a macro call to gan_ltmatf_form_gen().
 * \sa gan_ltmatf_alloc() and gan_ltmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_form_data ( Gan_SquMatrix_f *A, unsigned long size,
                                        float *data, size_t data_size );
#else
#define gan_ltmatf_form_data(A,size,data,data_size)\
           gan_ltmatf_form_gen(A,size,data,data_size)
#endif

/**
 * \brief Macro: Allocate and return a upper triangular matrix.
 *
 * Allocates and returns a upper triangular matrix with given \a size.
 *
 * Implemented as a macro call to gan_utmatf_form_gen().
 * \sa gan_utmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_utmatf_alloc ( unsigned long size );
#else
#define gan_utmatf_alloc(size) gan_utmatf_form_gen(NULL,size,NULL,0)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_utmatf_form ( Gan_SquMatrix_f *A, unsigned long size );
#else
#define gan_utmatf_form(A,size) gan_utmatf_form_gen(A,size,NULL,0)
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
 * Implemented as a macro call to gan_utmatf_form_gen().
 * \sa gan_utmatf_alloc() and gan_utmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_utmatf_form_data ( Gan_SquMatrix_f *A, unsigned long size,
                                        void *data, size_t data_size );
#else
#define gan_utmatf_form_data(A,size,data,data_size)\
           gan_utmatf_form_gen(A,size,data,data_size)
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
 * \sa gan_ltmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_fill_const_s ( unsigned long size, float value );
#else
#define gan_ltmatf_fill_const_s(size,v) gan_ltmatf_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of lower triangular matrix and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 * Sets the \a size of lower triangular matrix \a A, and fills \a A with zero.
 *
 * \sa gan_ltmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_fill_zero_q ( Gan_SquMatrix_f *A,
                                          unsigned long size );
#else
#define gan_ltmatf_fill_zero_q(A,size) gan_ltmatf_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates a lower triangular matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a lower triangular matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_ltmatf_fill_const_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_fill_zero_s ( unsigned long size );
#else
#define gan_ltmatf_fill_zero_s(size) gan_ltmatf_fill_const_s(size,0.0)
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
 * \sa gan_utmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_utmatf_fill_const_s ( unsigned long size, float value );
#else
#define gan_utmatf_fill_const_s(size,v) gan_utmatf_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of upper triangular matrix and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 *
 * Sets the size of upper triangular matrix \a A, and fills \a A with zero.
 *
 * \sa gan_utmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_utmatf_fill_zero_q ( Gan_SquMatrix_f *A,
                                          unsigned long size );
#else
#define gan_utmatf_fill_zero_q(A,size) gan_utmatf_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates an upper triangular matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates an upper triangular matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_utmatf_fill_const_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_utmatf_fill_zero_s ( unsigned long size );
#else
#define gan_utmatf_fill_zero_s(size) gan_utmatf_fill_const_s(size,0.0)
#endif

/**
 * \}
 */

/* not user functions */
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_form_gen ( Gan_SquMatrix_f *A, unsigned long size,
                                       float *data, size_t data_size );
GANDALF_API Gan_SquMatrix_f *gan_utmatf_form_gen ( Gan_SquMatrix_f *A, unsigned long size,
                                       float *data, size_t data_size );
GANDALF_API Gan_SquMatrix_f *gan_ltmatf_fill_vap ( Gan_SquMatrix_f *L,
                                       unsigned long size, va_list *aptr );
GANDALF_API Gan_SquMatrix_f *gan_utmatf_fill_vap ( Gan_SquMatrix_f *U,
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

#endif /* #ifndef _GAN_MATF_TRIANGULAR_H */
