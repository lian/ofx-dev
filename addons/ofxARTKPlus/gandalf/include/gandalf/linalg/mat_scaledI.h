/**
 * File:          $RCSfile: mat_scaledI.h,v $
 * Module:        Scaled identity matrices (double precision)
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

#ifndef _GAN_MAT_SCALEDI_H
#define _GAN_MAT_SCALEDI_H

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
GANDALF_API Gan_SquMatrix *gan_scalImat_set_size ( Gan_SquMatrix *A, unsigned long size );
GANDALF_API Gan_SquMatrix *gan_scalImat_fill_va ( Gan_SquMatrix *A,
                                      unsigned long size, ... );
GANDALF_API Gan_SquMatrix *gan_scalImat_fill_const_q ( Gan_SquMatrix *A,
                                           unsigned long size,
                                           double value );
GANDALF_API Gan_Bool gan_scalImat_read_va ( const Gan_SquMatrix *A, unsigned long size, ... );

/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a multiple of the identity matrix.
 *
 * Allocates and returns a multiple of the identity matrix with given \a size.
 *
 * Implemented as a macro call to gan_scalImat_form_gen().
 *
 * \sa gan_scalImat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_scalImat_alloc ( unsigned long size );
#else
#define gan_scalImat_alloc(size) gan_scalImat_form_gen(NULL,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a multiple of the identity matrix.
 *
 * Forms and returns a multiple of the identity matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_scalImat_form_gen().
 *
 * \sa gan_scalImat_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_scalImat_form ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_scalImat_form(A,size) gan_scalImat_form_gen(A,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a multiple of the identity matrix.
 *
 * Forms and returns a multiple of the identity matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated.
 *
 * Implemented as a macro call to gan_scalImat_form_gen().
 *
 * \sa gan_scalImat_alloc() and gan_scalImat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_scalImat_form_data ( Gan_SquMatrix *A, unsigned long size,
                                        double *data, size_t data_size );
#else
#define gan_scalImat_form_data(A,size,data,data_size)\
           gan_scalImat_form_gen(A,size,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Allocates a scaled identity matrix and fills it with a value.
 * \param size Size to set matrix to
 * \param value Value to set each element of the matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a scaled identity matrix, sets its \a size, and fills it with the
 * given \a value.
 *
 * \sa gan_scalImat_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *
 gan_scalImat_fill_const_s ( unsigned long size, double value );
#else
#define gan_scalImat_fill_const_s(size,v) gan_scalImat_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of scaled identity matrix and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 *
 * Sets the \a size of scaled identity matrix \a A, and fills \a A with zero.
 *
 * \sa gan_scalImat_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *
 gan_scalImat_fill_zero_q ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_scalImat_fill_zero_q(A,size) gan_scalImat_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates a scaled identity matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a scaled identity matrix, sets its \a size, and fills it with
 * zero.
 *
 * \sa gan_scalImat_fill_const_s().
 *
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *
 gan_scalImat_fill_zero_s ( unsigned long size );
#else
#define gan_scalImat_fill_zero_s(size) gan_scalImat_fill_const_s(size,0.0)
#endif

/**
 * \}
 */

/* not user functions */
GANDALF_API Gan_SquMatrix *gan_scalImat_form_gen ( Gan_SquMatrix *A, unsigned long size,
                                       double *data, size_t data_size );
GANDALF_API Gan_SquMatrix *gan_scalImat_fill_vap ( Gan_SquMatrix *A,
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

#endif /* #ifndef _GAN_MAT_SCALEDI_H */
