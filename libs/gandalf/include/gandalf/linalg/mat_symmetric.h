/**
 * File:          $RCSfile: mat_symmetric.h,v $
 * Module:        Symmetric matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.22 $
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

#ifndef _GAN_MAT_SYMMETRIC_H
#define _GAN_MAT_SYMMETRIC_H

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

#ifndef GAN_MATRIX_STRUCT_DEFINED
struct Gan_Matrix;
#endif

/* function declarations */
GANDALF_API Gan_SquMatrix *gan_symmat_set_size ( Gan_SquMatrix *A, unsigned long size );
GANDALF_API Gan_SquMatrix *gan_symmat_fill_va ( Gan_SquMatrix *A,
                                    unsigned long size, ... );
GANDALF_API Gan_SquMatrix *gan_symmat_fill_const_q ( Gan_SquMatrix *A,
                                         unsigned long size, double value );
GANDALF_API Gan_Bool gan_symmat_read_va ( const Gan_SquMatrix *A, unsigned long size, ... );
GANDALF_API Gan_SquMatrix *gan_symmat_insertsym ( Gan_SquMatrix *A, unsigned long rA,
                                      const Gan_SquMatrix *B, unsigned long rB,
                                      unsigned long size );
GANDALF_API Gan_SquMatrix *gan_symmat_insertsym_od ( Gan_SquMatrix *A,
                                         unsigned long rA, unsigned long cA,
                                         const Gan_SquMatrix *B,
                                         unsigned long rB, unsigned long cB,
                                         unsigned long rows,
                                         unsigned long cols );
GANDALF_API Gan_Bool gan_symmat_eigen ( Gan_SquMatrix *A,
                            Gan_SquMatrix *W, struct Gan_Matrix *Z,
                            Gan_Bool sort,
                            double *work, unsigned long work_size );
                            
/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a square symmetric matrix.
 *
 * Allocates and returns a square symmetric matrix with given \a size.
 *
 * Implemented as a macro call to gan_symmat_form_gen().
 * \sa gan_symmat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_alloc ( unsigned long size );
#else
#define gan_symmat_alloc(size) gan_symmat_form_gen(NULL,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a square symmetric matrix.
 *
 * Forms and returns a square symmetric matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_symmat_form_gen().
 * \sa gan_symmat_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_form ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_symmat_form(A,size) gan_symmat_form_gen(A,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a square symmetric matrix.
 *
 * Forms and returns a square symmetric matrix with given \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is used; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated.
 *
 * Implemented as a macro call to gan_symmat_form_gen().
 * \sa gan_symmat_alloc() and gan_symmat_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_form_data ( Gan_SquMatrix *A, unsigned long size,
                                      double *data, size_t data_size );
#else
#define gan_symmat_form_data(A,size,data,data_size)\
           gan_symmat_form_gen(A,size,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Allocates a symmetric matrix and fills it with a value.
 * \param size Size to set matrix to
 * \param value Value to set each element of the matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a symmetric matrix, sets its size, and fills it with the
 * specified value.
 *
 * \sa gan_symmat_fill_const_q()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *
 gan_symmat_fill_const_s ( unsigned long size, double value );
#else
#define gan_symmat_fill_const_s(size,v) gan_symmat_fill_const_q(NULL,size,v)
#endif

/**
 * \brief Macro: Sets the size of symmetric matrix, and fills it with zero.
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 *
 * Sets the size of symmetric matrix \a A, and fills \a A with zero.
 *
 * \sa gan_symmat_fill_const_q()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *
 gan_symmat_fill_zero_q ( Gan_SquMatrix *A, unsigned long size );
#else
#define gan_symmat_fill_zero_q(A,size) gan_symmat_fill_const_q(A,size,0.0)
#endif

/**
 * \brief Macro: Allocates a symmetric matrix and fills it with zero.
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a symmetric matrix, sets its \a size, and fills it with zero.
 *
 * \sa gan_symmat_fill_const_s()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *
 gan_symmat_fill_zero_s ( unsigned long size );
#else
#define gan_symmat_fill_zero_s(size) gan_symmat_fill_const_s(size,0.0)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixInsert
 * \{
 */

/**
 * \brief Macro: Insert part of generic matrix in symmetric matrix.
 * \return Result matrix \a S.
 *
 * Fills a rectangular part of symmetric matrix \a S starting at row,column
 * position \a rS, \a cS and \a rows by \a cols in size with the section
 * in generic matrix \a B, starting at position \a rB, \a cB.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_insert ( Gan_SquMatrix *S,
                                   unsigned long rS, unsigned long cS,
                                   const Gan_Matrix *B,
                                   unsigned long rB, unsigned long cB,
                                   unsigned long rows, unsigned long cols );
#else
#define gan_symmat_insert(S,rS,cS,B,rB,cB,rows,cols) (gan_symmat_insert_gen(S,rS,cS,B,GAN_NOTRANSPOSE,rB,cB,rows,cols))
#endif

/**
 * \brief Macro: Insert transpose of part of generic matrix in symmetric matrix.
 * \return Result matrix \a S.
 *
 * Fills a rectangular part of symmetric matrix \a S starting at row,column
 * position \a rS,\a cS and \a rows by \a cols in size with the transpose
 * of the section in generic matrix \a B, starting at position \a rB, \a cB.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_insertT ( Gan_SquMatrix *S,
                                    unsigned long rS, unsigned long cS,
                                    const Gan_Matrix *B,
                                    unsigned long rB, unsigned long cB,
                                    unsigned long rows, unsigned long cols );
#else
#define gan_symmat_insertT(S,rS,cS,B,rB,cB,rows,cols) (gan_symmat_insert(S,rS,cS,B,GAN_TRANSPOSE,rB,cB,rows,cols))
#endif

/**
 * \brief Macro: Insert part of column vector in a symmetric matrix.
 * \return Result matrix \a A.
 *
 * Fills a section of a column of symmetric matrix \a A starting at
 * row,column position \a rA,\a cA with a section \a rows elements
 * in size, taken from column vector \a x, starting at position \a rx.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_insertv ( Gan_SquMatrix *A,
                                    unsigned long rA, unsigned long cA,
                                    const Gan_Vector *x, unsigned long rx,
                                    unsigned long rows );
#else
#define gan_symmat_insertv(A,rA,cA,x,rx,rows) (gan_symmat_insertv_gen(A,rA,cA,x,GAN_NOTRANSPOSE,rx,rows))
#endif

/**
 * \brief Macro: Insert part of row vector in a symmetric matrix.
 * \return Result matrix \a A.
 *
 * Fills a section of a row of symmetric matrix \a A starting at
 * row,column position \a rA,\a cA with a section \a cols elements
 * in size, taken from transpose of column vector \a x, starting at
 * position \a rx.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_symmat_insertvT ( Gan_SquMatrix *A,
                                     unsigned long rA, unsigned long cA,
                                     const Gan_Vector *x, unsigned long rx,
                                     unsigned long cols );
#else
#define gan_symmat_insertvT(A,rA,cA,x,rx,cols) (gan_symmat_insertv_gen(A,rA,cA,x,GAN_TRANSPOSE,rx,cols))
#endif

/**
 * \}
 */

/* not user functions */
GANDALF_API Gan_SquMatrix *gan_symmat_form_gen ( Gan_SquMatrix *A, unsigned long size,
                                     double *data, size_t data_size );
GANDALF_API Gan_SquMatrix *gan_symmat_fill_vap ( Gan_SquMatrix *A,
                                     unsigned long size, va_list *aptr );
GANDALF_API Gan_SquMatrix *gan_symmat_insert_gen ( Gan_SquMatrix *S,
                                       unsigned long rS,   unsigned long cS,
                                       const struct Gan_Matrix *B,
                                       Gan_TposeFlag B_tr,
                                       unsigned long rB,   unsigned long cB,
                                       unsigned long rows,
                                       unsigned long cols );
GANDALF_API Gan_SquMatrix *gan_symmat_insertv_gen ( Gan_SquMatrix *A,
                                        unsigned long rA, unsigned long cA,
                                        const struct Gan_Vector *x,
                                        Gan_TposeFlag x_tr,
                                        unsigned long rx, unsigned long size );

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

#endif /* #ifndef _GAN_MAT_SYMMETRIC_H */
