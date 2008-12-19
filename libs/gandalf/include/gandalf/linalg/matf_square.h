/**
 * File:          $RCSfile: matf_square.h,v $
 * Module:        Square matrices (single precision)
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

#ifndef _GAN_MATF_SQUARE_H
#define _GAN_MATF_SQUARE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/linalg_defs.h>

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

/* forward declaration of square matrix structure */
struct Gan_SquMatrix_f;

/// Structure containing type-specific functions
typedef struct Gan_SquMatrixFFuncs
{
   Gan_Bool (*set_el) ( struct Gan_SquMatrix_f *A, unsigned i, unsigned j,
                        float value );
   float (*get_el) ( const struct Gan_SquMatrix_f *A, unsigned i, unsigned j );
   Gan_Bool (*inc_el) ( struct Gan_SquMatrix_f *A, unsigned i, unsigned j,
                        float value );
   Gan_Bool (*dec_el) ( struct Gan_SquMatrix_f *A, unsigned i, unsigned j,
                        float value );
   Gan_Bool (*fprint) ( FILE *fp, const struct Gan_SquMatrix_f *A,
                        const char *prefix, unsigned indent, const char *fmt );
   struct Gan_SquMatrix_f *(*copy) ( const struct Gan_SquMatrix_f *A,
                                     struct Gan_SquMatrix_f *B );
   struct Gan_SquMatrix_f *(*scale) ( struct Gan_SquMatrix_f *A, float a,
                                      struct Gan_SquMatrix_f *B );
   struct Gan_SquMatrix_f *(*add) (
       struct Gan_SquMatrix_f *A, Gan_TposeFlag A_tr,
       struct Gan_SquMatrix_f *B, Gan_TposeFlag B_tr,
       struct Gan_SquMatrix_f *C );
   struct Gan_SquMatrix_f *(*sub) (
       struct Gan_SquMatrix_f *A, Gan_TposeFlag A_tr,
       struct Gan_SquMatrix_f *B, Gan_TposeFlag B_tr,
       struct Gan_SquMatrix_f *C );
   struct Gan_Vector_f *(*multv) (
       const struct Gan_SquMatrix_f *A, Gan_TposeFlag A_tr, Gan_InvertFlag A_inv,
       struct Gan_Vector_f *x, struct Gan_Vector_f *y );
   struct Gan_Matrix_f *(*rmult) (
       const struct Gan_SquMatrix_f *A, Gan_TposeFlag A_tr, Gan_InvertFlag A_inv,
       struct Gan_Matrix_f *B, Gan_TposeFlag B_tr, struct Gan_Matrix_f *C );
   struct Gan_Matrix_f *(*lmult) (
       const struct Gan_SquMatrix_f *A, Gan_TposeFlag A_tr, Gan_InvertFlag A_inv,
       struct Gan_Matrix_f *B, Gan_TposeFlag B_tr, struct Gan_Matrix_f *C );
   struct Gan_SquMatrix_f *(*rmult_squ) (
       struct Gan_SquMatrix_f *A, Gan_TposeFlag A_tr, Gan_InvertFlag A_inv,
       struct Gan_SquMatrix_f *B, Gan_TposeFlag B_tr, Gan_InvertFlag B_inv,
       struct Gan_SquMatrix_f *C );
   struct Gan_SquMatrix_f *(*lrmult) (
       const struct Gan_SquMatrix_f *A, const struct Gan_Matrix_f *B, Gan_TposeFlag B_tr,
       struct Gan_Matrix_f *C, struct Gan_SquMatrix_f *D );
   struct Gan_SquMatrix_f *(*invert) ( struct Gan_SquMatrix_f *A,
                                       struct Gan_SquMatrix_f *B );
   struct Gan_SquMatrix_f *(*cholesky) ( struct Gan_SquMatrix_f *S,
                                         struct Gan_SquMatrix_f *L,
                                         int *error_code );
   float (*sumsqr) ( const struct Gan_SquMatrix_f *A );
   float (*Fnorm)  ( const struct Gan_SquMatrix_f *A );
   struct Gan_Matrix_f *(*matrix) ( const struct Gan_SquMatrix_f *A,
                                    struct Gan_Matrix_f *B );
} Gan_SquMatrixFFuncs;

/// Structure definition for single precision general size square matrix
typedef struct Gan_SquMatrix_f
{
   /* type of square matrix, i.e. symmetric, triangular etc. */
   Gan_SquMatrixType type;

   /* row and column sizes of matrix */
   unsigned long size;

   /* data array containing matrix elements */
   float *data;

   /* allocated size of matrix (number of float's) */
   size_t data_size;

   /* pointer to structure containing type-specific functions */
   Gan_SquMatrixFFuncs *funcs;

   /* flag indicating whether matrix data was dynamically allocated */
   Gan_Bool data_alloc;

   /* flag indicating whether matrix structure was dynamically allocated */
   Gan_Bool struct_alloc;
} Gan_SquMatrix_f;

#define GAN_SQUMATRIXF_STRUCT_DEFINED

#include <gandalf/linalg/vecf_gen.h>
#include <gandalf/linalg/matf_gen.h>

/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a square matrix.
 *
 * Allocates and returns a square matrix of given \a type and \a size.
 *
 * Implemented as a macro call to gan_squmatf_form_data().
 * \sa gan_squmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_alloc ( Gan_SquMatrixType type,
                                     unsigned long size );
#else
#define gan_squmatf_alloc(type,size) gan_squmatf_form_data(NULL,type,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a square matrix.
 *
 * Forms and returns a square matrix with given \a type and \a size.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is filled; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_squmatf_form_data().
 * \sa gan_squmatf_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_form ( Gan_SquMatrix_f *A, Gan_SquMatrixType type,
                                    unsigned long size );
#else
#define gan_squmatf_form(A,type,size) gan_squmatf_form_data(A,type,size,NULL,0)
#endif

/**
 * \brief Macro: Form and return a square symmetric matrix.
 *
 * Forms and returns a square symmetric matrix with given \a type and
 * \a size. If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is filled; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated. Otherwise, \a data_size is
 * the size of the \a data array in terms of \c double values.
 *
 * \sa gan_squmatf_alloc() and gan_squmatf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_squmatf_form_data ( Gan_SquMatrix_f *A,
                         Gan_SquMatrixType type, unsigned long size,
                         float *data, size_t data_size );
#else
#define gan_squmatf_form_data(A,type,size,data,data_size)\
           gan_squmatf_form_gen(A,type,size,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixAccessElement
 * \{
 */

/**
 * \brief Macro: Set specific element of square matrix.
 *
 * Sets element \a row,\a col of square matrix \a A to given \a value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_set_el ( Gan_SquMatrix_f *A, unsigned row, unsigned col,
                              float value );
#else
#define gan_squmatf_set_el(A,r,c,v) ((A)->funcs->set_el(A,r,c,v))
#endif

/**
 * \brief Macro: Get specific element of square matrix.
 *
 * Returns element \a row,\a col of square matrix \a A, or \c FLT_MAX on
 * failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_squmatf_get_el ( const Gan_SquMatrix_f *A, unsigned row, unsigned col );
#else
#define gan_squmatf_get_el(A,r,c) ((A)->funcs->get_el(A,r,c))
#endif

/**
 * \brief Macro: Increment specific element of square matrix by given value.
 *
 * Increment element \a row,\a col of square matrix \a A by given \a value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_inc_el ( Gan_SquMatrix_f *A, unsigned row, unsigned col,
                              float value );
#else
#define gan_squmatf_inc_el(A,r,c,v) ((A)->funcs->inc_el(A,r,c,v))
#endif

/**
 * \brief Macro: Decrement specific element of square matrix by given value.
 *
 * Decrement element \a row,\a col of square matrix \a A by given \a value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_dec_el ( Gan_SquMatrix_f *A, unsigned row, unsigned col,
                              float value );
#else
#define gan_squmatf_dec_el(A,r,c,v) ((A)->funcs->dec_el(A,r,c,v))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixIO
 * \{
 */

/**
 * \brief Macro: Print square matrix to file pointer.
 *
 * Print square matrix \a A to file pointer \a fp, with prefix string
 * \a prefix, indentation \a indent and floating-point format \a fmt.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_fprint ( FILE *fp, const Gan_SquMatrix_f *A,
                              const char *prefix, int indent,
                              const char *fmt );
#else
#define gan_squmatf_fprint(fp,A,p,i,f) ((A)->funcs->fprint(fp,A,p,i,f))
#endif

/**
 * \brief Macro: Print square matrix to standard output.
 *
 * Print square matrix \a A to standard output, with prefix string \a prefix,
 * indentation \a indent and floating-point format \a fmt.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_print ( const Gan_SquMatrix_f *A,
                             const char *prefix, int indent, const char *fmt );
#else
#define gan_squmatf_print(A,p,i,f) ((A)->funcs->fprint(stdout,A,p,i,f))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Allocates a square matrix and fills it with a value.
 * \param type Type of square matrix
 * \param size Size to set matrix to
 * \param value Value to set each element of the matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a square matrix with given \a type, sets its \a size, and fills
 * it with zero.
 *
 * \sa  gan_squmatf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_squmatf_fill_const_s ( Gan_SquMatrixType type,
                            unsigned long size, float value );
#else
#define gan_squmatf_fill_const_s(t,s,v) gan_squmatf_fill_const_q(NULL,t,s,v)
#endif

/**
 * \brief Macro: Sets the size of square matrix, and fills it with zero
 * \param type Type of square matrix
 * \param A Square matrix to be filled
 * \param size Size to set matrix to
 * \return The filled matrix, or \c NULL on failure.
 *
 * Sets the \a type and \a size of square matrix \a A, and fills \a A with
 * zero.
 *
 * \sa gan_squmatf_fill_const_q()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_squmatf_fill_zero_q ( Gan_SquMatrix_f *A, Gan_SquMatrixType type,
                           unsigned long size );
#else
#define gan_squmatf_fill_zero_q(A,t,s) gan_squmatf_fill_const_q(A,t,s,0.0)
#endif

/**
 * \brief Macro: Allocates a square matrix and fills it with zero.
 * \param type Type of square matrix
 * \param size Size to set matrix to
 * \return The allocated and filled matrix, or \c NULL on failure.
 *
 * Allocates a square matrix, sets its \a type and \a size, and fills it
 * with zero.
 *
 * \sa gan_squmatf_fill_const_s()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *
 gan_squmatf_fill_zero_s ( Gan_SquMatrixType type, unsigned long size );
#else
#define gan_squmatf_fill_zero_s(t,s) gan_squmatf_fill_const_s(t,s,0.0)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixCopy
 * \{
 */

/**
 * \brief Macro: Copy square matrix.
 *
 * Copy square matrix \a A to square matrix \a B, and return \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_copy_q ( const Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_copy_q(A,B) ((A)->funcs->copy(A,B))
#endif

/**
 * \brief Macro: Copy square matrix.
 *
 * Allocate and return a copy of square matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_copy_s ( const Gan_SquMatrix_f *A );
#else
#define gan_squmatf_copy_s(A) ((A)->funcs->copy(A,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixScale
 * \{
 */

/**
 * \brief Macro: Multiply square matrix by scalar.
 * \return Result matrix \a B.
 *
 * Multiply square matrix \a A by scalar \a a, writing result \f$ a A \f$
 * into square matrix \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_scale_q ( Gan_SquMatrix_f *A, float a,
                                       Gan_SquMatrix_f *B );
#else
#define gan_squmatf_scale_q(A,a,B) ((A)->funcs->scale(A,a,B))
#endif

/**
 * \brief Macro: Multiply square matrix by scalar.
 * \return Result as a new matrix.
 *
 * Allocate and return a copy of square matrix \a A multiplied by
 * scalar \a a, i.e. \f$ a A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_scale_s ( Gan_SquMatrix_f *A, float a );
#else
#define gan_squmatf_scale_s(A,a) ((A)->funcs->scale(A,a,NULL))
#endif

/**
 * \brief Macro: Multiply square matrix by scalar.
 * \return Result matrix \a A.
 *
 * Multiply square matrix \a A by scalar \a a in-place:
 * \f$ A \leftarrow a A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_scale_i ( Gan_SquMatrix_f *A, float a );
#else
#define gan_squmatf_scale_i(A,a) ((A)->funcs->scale(A,a,A))
#endif

/**
 * \brief Macro: Divide square matrix by scalar.
 * \return Result matrix \a B.
 *
 * Divide square matrix \a A by scalar \a a, writing result
 * \f$ \frac{1}{a} A \f$into square matrix \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_divide_q ( Gan_SquMatrix_f *A, float a,
                                        Gan_SquMatrix_f *B );
#else
#define gan_squmatf_divide_q(A,a,B) ((A)->funcs->scale(A,1.0/(a),B))
#endif

/**
 * \brief Macro: Divide square matrix by scalar.
 * \return Result as a new matrix.
 *
 * Allocate and return a copy of square matrix \a A divided by
 * scalar \a a, i.e. \f$ \frac{1}{a} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_divide_s ( Gan_SquMatrix_f *A, float a );
#else
#define gan_squmatf_divide_s(A,a) ((A)->funcs->scale(A,1.0/(a),NULL))
#endif

/**
 * \brief Macro: Divide square matrix by scalar.
 *
 * Divide square matrix \a A by scalar \a a in-place:
 * \f$ A \leftarrow \frac{1}{a} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_divide_i ( Gan_SquMatrix_f *A, float a );
#else
#define gan_squmatf_divide_i(A,a) ((A)->funcs->scale(A,1.0/(a),A))
#endif

/**
 * \brief Macro: Negate square matrix.
 * \return Result matrix \a B.
 *
 * Negate square matrix \a A into square matrix \f$ B = -A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_negate_q ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_negate_q(A,B) ((A)->funcs->scale(A,-1.0,B))
#endif

/**
 * \brief Macro: Negate square matrix.
 * \return Result as a new matrix.
 *
 * Allocate and return a negated copy \f$ -A \f$ of square matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_negate_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_negate_s(A) ((A)->funcs->scale(A,-1.0,NULL))
#endif

/**
 * \brief Macro: Negate square matrix.
 *
 * Negate square matrix \a A in-place: \f$ A \leftarrow -A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_negate_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_negate_i(A) ((A)->funcs->scale(A,-1.0,A))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixAdd
 * \{
 */

/**
 * \brief Macro: Add two square matrices.
 * \return Result matrix \a C.
 *
 * Add two square matrices \a A, \a B and write result into
 * \f$ C = A + B \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_add_q ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B,
                                     Gan_SquMatrix_f *C );
#else
#define gan_squmatf_add_q(A,B,C) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two square matrices and return the result as a new matrix.
 * \return Result as a new matrix.
 *
 * Add two square matrices \a A, \a B and return the result as a new square
 * matrix \f$ A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_add_s ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_add_s(A,B) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add two square matrices and overwrite the first with the result.
 * \return Result matrix \a A.
 *
 * Add two square matrices \a A, \a B and overwrite \a A with the
 * result: \f$ A \leftarrow A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_add_i1 ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_add_i1(A,B) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Add two square matrices and overwrite the second with the result.
 * \return Result matrix \a B.
 *
 * Add two square matrices \a A, \a B and overwrite \a B with the result:
 * \f$ B \leftarrow A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_add_i2 ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_add_i2(A,B) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(B)))
#endif

/**
 * \brief Macro: Increment a square matrix with another square matrix.
 * \return Result matrix \a A.
 *
 * Increment square matrix \a A with square matrix \a B:
 * \f$ A \leftarrow A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_increment ( Gan_SquMatrix_f *A,
                                         Gan_SquMatrix_f *B );
#else
#define gan_squmatf_increment(A,B) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Add two square matrices, the second transposed.
 * \return Result matrix \a C.
 *
 * Add square matrix \a A and the transpose of square matrix \a B and write
 * result into \f$ C = A + B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_addT_q ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B,
                                      Gan_SquMatrix_f *C );
#else
#define gan_squmatf_addT_q(A,B,C) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two square matrices, the second transposed.
 * \return Result as a new matrix.
 *
 * Add square matrix \a A and the transpose of square matrix \a B and
 * return the result as a new matrix \f$ A + B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_addT_s ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_addT_s(A,B) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Increment a square matrix with the transpose of another square matrix.
 * \return Result matrix \a A.
 *
 * Increment square matrix \a A with the transpose of square matrix \a B:
 * \f$ A \leftarrow A + B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_incrementT ( Gan_SquMatrix_f *A,
                                          Gan_SquMatrix_f *B );
#else
#define gan_squmatf_incrementT(A,B) ((A)->funcs->add(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,(A)))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixSubtract
 * \{
 */

/**
 * \brief Macro: Subtract two square matrices and write result into a third.
 * \return Result matrix \a C.
 *
 * Subtract two square matrices \a A, \a B and write result into
 * \f$ C = A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_sub_q ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B,
                                     Gan_SquMatrix_f *C );
#else
#define gan_squmatf_sub_q(A,B,C) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Subtract two square matrices and return the result as a new square matrix.
 * \return Result as a new matrix.
 *
 * Subtract two square matrices \a A, \a B and return the result as a new
 * square matrix \f$ A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_sub_s ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_sub_s(A,B) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Subtract two square matrices and overwrite the first with the result.
 * \return Result matrix \a A.
 *
 * Subtract two square matrices \a A, \a B and overwrite \a A with the
 * result: \f$ A \leftarrow A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_sub_i1 ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_sub_i1(A,B) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Subtract two square matrices and overwrite the second with the result.
 * \return Result matrix \a B.
 *
 * Subtract two square matrices \a A, \a B and overwrite \a B with the result:
 * \f$ B \leftarrow A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_sub_i2 ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_sub_i2(A,B) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(B)))
#endif

/**
 * \brief Macro: Decrement a square matrix with another square matrix.
 * \return Result matrix \a A.
 *
 * Decrement square matrix \a A with square matrix \a B, and return \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_decrement ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_decrement(A,B) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Subtract two square matrices, the second transposed.
 * \return Result matrix \a C.
 *
 * Subtract square matrix \a A and the transpose of square matrix \a B and
 * write result into \f$ C = A - B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_subT_q ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B,
                                      Gan_SquMatrix_f *C );
#else
#define gan_squmatf_subT_q(A,B,C) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Subtract two square matrices, the second transposed.
 * \return Result as a new matrix.
 *
 * Subtract square matrix \a A and the transpose of square matrix \a B and
 * return the result as a new square matrix \f$ A - B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_subT_s ( Gan_SquMatrix_f *A,
                                      Gan_SquMatrix_f *B );
#else
#define gan_squmatf_subT_s(A,B) ((A)->funcs->subT(A,B,NULL))
#endif

/**
 * \brief Macro: Decrement a square matrix with the transpose of another square matrix.
 * \return Result matrix \a A.
 *
 * Decrement square matrix \a A with the transpose of square matrix \a B:
 * \f$ A \leftarrow A - B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_decrementT ( Gan_SquMatrix_f *A,
                                          Gan_SquMatrix_f *B );
#else
#define gan_squmatf_decrementT(A,B) ((A)->funcs->sub(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,(A)))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixVectorProduct
 * \{
 */

/**
 * \brief Macro: Multiply square matrix by a vector, writing the result into another vector.
 * \return Result vector \a y.
 *
 * Multiply square matrix \a A by vector \a x, writing result into
 * \f$ y = A * x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatf_multv_q ( const Gan_SquMatrix_f *A, Gan_Vector_f *x,
                                    Gan_Vector_f *y );
#else
#define gan_squmatf_multv_q(A,x,y) ((A)->funcs->multv(A,GAN_NOTRANSPOSE,GAN_NOINVERT,x,y))
#endif

/**
 * \brief Macro: Multiply square matrix by a vector, returning the result as a new vector.
 * \return Result as a new matrix.
 *
 * Multiply square matrix \a A by vector \a x, creating and returning the
 * result \f$ A x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatf_multv_s ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatf_multv_s(A,x) ((A)->funcs->multv(A,GAN_NOTRANSPOSE,GAN_NOINVERT,x,NULL))
#endif

/**
 * \brief Macro: Multiply square matrix by a vector, overwriting the vector with the result.
 * \return Result vector \a x.
 *
 * Multiply square matrix \a A by vector \a x, overwriting \a x with
 * the result \f$ x \leftarrow A x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatf_multv_i ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatf_multv_i(A,x) ((A)->funcs->multv(A,GAN_NOTRANSPOSE,GAN_NOINVERT,x,x))
#endif

/**
 * \brief Macro: Multiply the transpose of a square matrix by a vector.
 * \return Result vector \a y.
 *
 * Multiply transpose of square matrix \a A by vector \a x, writing result
 * into \f$ y = A^{\top} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatTf_multv_q ( const Gan_SquMatrix_f *A, Gan_Vector_f *x,
                                     Gan_Vector_f *y );
#else
#define gan_squmatTf_multv_q(A,x,y) ((A)->funcs->multv(A,GAN_TRANSPOSE,GAN_NOINVERT,x,y))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by a vector.
 *
 * Multiply transpose of square matrix \a A by vector \a x, creating and
 * returning the result \f$ A^{\top} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatTf_multv_s ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatTf_multv_s(A,x) ((A)->funcs->multv(A,GAN_TRANSPOSE,GAN_NOINVERT,x,NULL))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by a vector.
 * \return Result vector \a x.
 *
 * Multiply transpose of square matrix \a A by vector \a x, overwriting
 * \a x with the result \f$ x \leftarrow A^{\top} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatTf_multv_i ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatTf_multv_i(A,x) ((A)->funcs->multv(A,GAN_TRANSPOSE,GAN_NOINVERT,x,x))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by a vector.
 * \return Result vector \a y.
 *
 * Multiply inverse of square matrix \a A by vector \a x, writing result
 * into \f$ y = A^{-1} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatIf_multv_q ( const Gan_SquMatrix_f *A, Gan_Vector_f *x,
                                     Gan_Vector_f *y );
#else
#define gan_squmatIf_multv_q(A,x,y) ((A)->funcs->multv(A,GAN_NOTRANSPOSE,GAN_INVERT,x,y))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by a vector.
 * \return Result as a new vector.
 *
 * Multiply inverse of square matrix \a A by vector \a x, creating and
 * returning the result \f$ A^{-1} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatIf_multv_s ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatIf_multv_s(A,x) ((A)->funcs->multv(A,GAN_NOTRANSPOSE,GAN_INVERT,x,NULL))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by a vector.
 * \return Result vector \a x.
 *
 * Multiply inversee of square matrix \a A by vector \a x, overwriting
 * \a x with the result \f$ x \leftarrow A^{-1} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatIf_multv_i ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatIf_multv_i(A,x) ((A)->funcs->multv(A,GAN_NOTRANSPOSE,GAN_INVERT,x,x))
#endif

/**
 * \brief Macro: Multiply the inverse transpose of a square matrix by a vector.
 * \return Result vector \a y.
 *
 * Multiply inverse transpose of square matrix \a A by vector \a x,
 * writing result into \f$ y = A^{-{\top}} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatITf_multv_q ( const Gan_SquMatrix_f *A, Gan_Vector_f *x,
                                      Gan_Vector_f *y );
#else
#define gan_squmatITf_multv_q(A,x,y) ((A)->funcs->multv(A,GAN_TRANSPOSE,GAN_INVERT,x,y))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by a vector.
 * \return Result as a new vector.
 *
 * Multiply inverse transpose of square matrix \a A by vector \a x,
 * creating and returning the result \f$ A^{-{\top}} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatITf_multv_s ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatITf_multv_s(A,x) ((A)->funcs->multv(A,GAN_TRANSPOSE,GAN_INVERT,x,NULL))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by a vector.
 * \return Result vector \a x.
 *
 * Multiply inversee transpose of square matrix \a A by vector \a x,
 * overwriting \a x with the result \f$ x \leftarrow A^{-{\top}} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_squmatITf_multv_i ( const Gan_SquMatrix_f *A, Gan_Vector_f *x );
#else
#define gan_squmatITf_multv_i(A,x) ((A)->funcs->multv(A,GAN_TRANSPOSE,GAN_INVERT,x,x))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixMatrixProduct
 * \{
 */

/**
 * \brief Macro: Multiply square matrix by generic matrix, and write result into a third.
 * \return Result matrix \a C.
 *
 * Multiply the square matrix \a A by the generic matrix \a B, and write
 * result into generic matrix \f$ C = A B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_rmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                    Gan_Matrix_f *C );
#else
#define gan_squmatf_rmult_q(A,B,C) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply square matrix by generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply square matrix \a A by generic matrix \a B and return the result
 * as a new matrix \f$ A B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_rmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatf_rmult_s(A,B) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply square matrix by generic matrix.
 * \return Result matrix \a B.
 *
 * Multiply square matrix \a A by generic matrix \a B, overwriting \a B
 * with the result: \f$ B \leftarrow A B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_rmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatf_rmult_i(A,B) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply square matrix by transpose of generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply square matrix \a A by the transpose of generic matrix \a B
 * and write result into \f$ C = A B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_rmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                     Gan_Matrix_f *C );
#else
#define gan_squmatf_rmultT_q(A,B,C) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply square matrix by transpose of generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply square matrix \a A by the transpose of generic matrix \a B
 * and return the result as a new matrix \f$ A B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_rmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatf_rmultT_s(A,B) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply the transpose of square matrix \a A by generic matrix \a B and
 * write result into \f$ C = A^{\top} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_rmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                     Gan_Matrix_f *C );
#else
#define gan_squmatTf_rmult_q(A,B,C) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply the transpose of square matrix \a A by generic matrix \a B and
 * return the result as a new matrix \f$ A^{\top} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_rmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatTf_rmult_s(A,B) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by generic matrix.
 * \return Result matrix \a B.
 *
 * Multiply transpose of square matrix \a A by generic matrix \a B,
 * overwriting \a B with the result \f$ B \leftarrow A^{\top} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_rmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatTf_rmult_i(A,B) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by transpose of generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply the transpose of square matrix \a A by the transpose of generic
 * matrix \a B and write result into \f$ C = A^{\top} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_rmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                      Gan_Matrix_f *C );
#else
#define gan_squmatTf_rmultT_q(A,B,C) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by transpose of generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply the transpose of square matrix \a A by the transpose of generic
 * matrix \a B and return the result as a new matrix \f$ A^{\top} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_rmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatTf_rmultT_s(A,B) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply the inverse of square matrix \a A by the generic matrix \a B,
 * and write result into generic matrix \f$ C = A B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_rmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                     Gan_Matrix_f *C );
#else
#define gan_squmatIf_rmult_q(A,B,C) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply inverse of square matrix \a A by generic matrix \a B and return
 * the result as a new matrix \f$ A^{-1} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_rmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatIf_rmult_s(A,B) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by generic matrix.
 * \return Result matrix \a B.
 *
 * Multiply inverse of square matrix \a A by generic matrix \a B,
 * overwriting \a B with the result \f$ B \leftarrow A^{-1} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_rmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatIf_rmult_i(A,B) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by transpose of generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply inverse of square matrix \a A by the transpose of generic matrix
 * \a B and write result into \f$ C = A^{-1} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_rmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                      Gan_Matrix_f *C );
#else
#define gan_squmatIf_rmultT_q(A,B,C) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply inverse of square matrix by transpose of generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply inverse of square matrix \a A by the transpose of generic matrix
 * \a B and return the result as a new matrix \f$ A^{-1} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_rmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatIf_rmultT_s(A,B) ((A)->funcs->rmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply the inverse transpose of square matrix \a A by generic matrix
 * \a B and write result into \f$ C = A^{-{\top}} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_rmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                      Gan_Matrix_f *C );
#else
#define gan_squmatITf_rmult_q(A,B,C) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply the inverse transpose of square matrix \a A by generic matrix
 * \a B and return the result as a new matrix \f$ A^{-{\top}} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_rmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatITf_rmult_s(A,B) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by generic matrix.
 * \return Result matrix \a B.
 *
 * Multiply inverse transpose of square matrix \a A by generic matrix \a B,
 * overwriting \a B with the result \f$ B \leftarrow A^{-{\top}} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_rmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatITf_rmult_i(A,B) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by transpose of generic matrix.
 * \return Result matrix \a C.
 *
 * Multiply the inverse transpose of square matrix \a A by the transpose of
 * generic matrix \a B and write result into \f$ C = A^{-{\top}} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_rmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                       Gan_Matrix_f *C );
#else
#define gan_squmatITf_rmultT_q(A,B,C) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply inverse transpose of square matrix by transpose of generic matrix.
 * \return Result as a new matrix.
 *
 * Multiply the inverse transpose of square matrix \a A by the transpose of
 * generic matrix \a B and return the result as a new matrix
 * \f$ A^{-{\top}} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_rmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatITf_rmultT_s(A,B) ((A)->funcs->rmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by square matrix, and write result into a third.
 * \return Result matrix \a C.
 *
 * Multiply the generic matrix \a B by the square matrix \a A, by write
 * result into generic matrix \f$ C = B A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_lmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                    Gan_Matrix_f *C );
#else
#define gan_squmatf_lmult_q(A,B,C) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply generic matrix by square matrix.
 * \return Result as a new matrix.
 *
 * Multiply generic matrix \a B by square matrix \a A and return the result
 * as a new matrix \f$ B A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_lmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatf_lmult_s(A,B) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by square matrix.
 * \return Result matrix \a B.
 *
 * Multiply generic matrix \a B by square matrix \a A, overwriting \a B
 * with the result \f$ B \leftarrow B A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_lmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatf_lmult_i(A,B) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by square matrix.
 * \return Result matrix \a C.
 *
 * Multiply transpose of generic matrix \a B by square matrix \a A
 * and write result into \f$ C = B^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_lmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                     Gan_Matrix_f *C );
#else
#define gan_squmatf_lmultT_q(A,B,C) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by square matrix.
 * \return Result as a new matrix.
 *
 * Multiply the transpose of generic matrix \a B by square matrix \a A
 * and return the result as a new matrix \f$ B^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatf_lmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatf_lmultT_s(A,B) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by the transpose of square matrix.
 * \return Result matrix \a C.
 *
 * Multiply generic matrix \a B by the transpose of square matrix \a A and
 * write result into \f$ C = B A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_lmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                     Gan_Matrix_f *C );
#else
#define gan_squmatTf_lmult_q(A,B,C) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply generic matrix by transpose of square matrix.
 * \return Result as a new matrix.
 *
 * Multiply generic matrix \a B by the transpose of square matrix \a A and
 * return the result as a new matrix \f$ B A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_lmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatTf_lmult_s(A,B) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply transpose of square matrix by generic matrix.
 * \return Result matrix \a B.
 *
 * Multiply generic matrix \a B by the transpose of square matrix \a A,
 * overwriting \a B with the result \f$ B \leftarrow B A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_lmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatTf_lmult_i(A,B) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by transpose of square matrix.
 * \return Result matrix \a C.
 *
 * Multiply the transpose of generic matrix \a B by the transpose of square
 * matrix \a A, and write result into \f$ C = B^{\top} A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_lmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                      Gan_Matrix_f *C );
#else
#define gan_squmatTf_lmultT_q(A,B,C) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by transpose of square matrix.
 * \return Result as a new matrix.
 *
 * Multiply the transpose of generic matrix \a B by the transpose of square
 * matrix \a A, and return the result as a new matrix
 * \f$ B^{\top} A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatTf_lmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatTf_lmultT_s(A,B) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_NOINVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by inverse of square matrix.
 * \return Result matrix \a C.
 *
 * Multiply generic matrix \a B by the inverse of square matrix \a A
 * and write result into generic matrix \f$ C = B A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_lmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                     Gan_Matrix_f *C );
#else
#define gan_squmatIf_lmult_q(A,B,C) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply generic matrix by inverse of square matrix.
 * \return Result as a new matrix.
 *
 * Multiply generic matrix \a B by the inverse of square matrix \a A and
 * return the result as a new matrix \f$ B A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_lmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatIf_lmult_s(A,B) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by inverse of square matrix.
 * \return Result matrix \a B.
 *
 * Multiply generic matrix \a B by the inverse of square matrix \a A,
 * overwriting \a B with the result \f$ B A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_lmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatIf_lmult_i(A,B) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by inverse of square matrix.
 * \return Result matrix \a C.
 *
 * Multiply transpose of generic matrix \a B by the inverse of square
 * matrix \a A, and write result into \f$ C = B^{\top} A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_lmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                      Gan_Matrix_f *C );
#else
#define gan_squmatIf_lmultT_q(A,B,C) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by inverse of square matrix.
 * \return Result as a new matrix.
 *
 * Multiply transpose of generic matrix \a B by the inverse of square
 * matrix \a A, and return the result as a new matrix \f$ B^{\top} A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatIf_lmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatIf_lmultT_s(A,B) ((A)->funcs->lmult(A,GAN_NOTRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by inverse transpose of square matrix.
 * \return Result matrix \a C.
 *
 * Multiply generic matrix \a B by the inverse transpose of square
 * matrix \a A, and write result into \f$ C = B A^{-{\top}} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_lmult_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                      Gan_Matrix_f *C );
#else
#define gan_squmatITf_lmult_q(A,B,C) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply generic matrix by inverse transpose of square matrix.
 * \return Result as a new matrix.
 *
 * Multiply the inverse transpose of square matrix \a A by generic matrix
 * \a B and return the result as a new matrix \f$ A^{-{\top}} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_lmult_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatITf_lmult_s(A,B) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply generic matrix by inverse transpose of square matrix.
 * \return Result matrix \a B.
 *
 * Multiply inverse transpose of square matrix \a A by generic matrix \a B,
 * overwriting \a B with the result \f$ A^{-{\top}} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_lmult_i ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatITf_lmult_i(A,B) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by inverse transpose of square matrix.
 * \return Result matrix \a C.
 *
 * Multiply the transpose of generic matrix \a B by the inverse transpose
 * of square matrix \a A, and write result into
 * \f$ C = B^{\top} A^{-{\top}} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_lmultT_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B,
                                       Gan_Matrix_f *C );
#else
#define gan_squmatITf_lmultT_q(A,B,C) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply transpose of generic matrix by inverse transpose of square matrix.
 * \return Result as a new matrix.
 *
 * Multiply the transpose of generic matrix \a B by the inverse transpose
 * of square matrix \a A, and return the result as a new matrix
 * \f$ B^{\top} A^{-{\top}} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_squmatITf_lmultT_s ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_squmatITf_lmultT_s(A,B) ((A)->funcs->lmult(A,GAN_TRANSPOSE,GAN_INVERT,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Right-multiply square matrix by its own transpose
 * \return Result matrix \a B.
 *
 * Right-multiply square matrix \a A by its own transpose, writing
 * the result into square matrix \f$ B = A A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_srmultT_squ_q ( Gan_SquMatrix_f *A,
                                             Gan_SquMatrix_f *B );
#else
#define gan_squmatf_srmultT_squ_q(A,B) ((A)->funcs->rmult_squ(A,GAN_NOTRANSPOSE,GAN_NOINVERT,A,GAN_TRANSPOSE,GAN_NOINVERT,B))
#endif

/**
 * \brief Macro: Right-multiply square matrix by its own transpose
 * \return Result as a new matrix.
 *
 * Right-multiply square matrix \a A by its own transpose, returning the
 * result \f$ A A^{\top} \f$ as a new matrix.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_srmultT_squ_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_srmultT_squ_s(A) ((A)->funcs->rmult_squ(A,GAN_NOTRANSPOSE,GAN_NOINVERT,A,GAN_TRANSPOSE,GAN_NOINVERT,NULL))
#endif

/**
 * \brief Macro: Right-multiply square matrix by its own transpose
 * \return Result matrix \a A.
 *
 * Right-multiply square matrix \a A by its own transpose, filling in \a A
 * with the result \f$ A \leftarrow A A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_srmultT_squ_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_srmultT_squ_i(A) ((A)->funcs->rmult_squ(A,GAN_NOTRANSPOSE,GAN_NOINVERT,A,GAN_TRANSPOSE,GAN_NOINVERT,A))
#endif

/**
 * \brief Macro: Right-multiply transpose of square matrix by itself
 * \return Result matrix \a B.
 *
 * Right-multiply transpose of square matrix \a A by itself, writing
 * the result into square matrix \f$ B = A^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatTf_srmult_squ_q ( Gan_SquMatrix_f *A,
                                             Gan_SquMatrix_f *B );
#else
#define gan_squmatTf_srmult_squ_q(A,B) ((A)->funcs->rmult_squ(A,GAN_TRANSPOSE,GAN_NOINVERT,A,GAN_NOTRANSPOSE,GAN_NOINVERT,B))
#endif

/**
 * \brief Macro: Right-multiply transpose of square matrix by itself
 * \return Result as a new matrix.
 *
 * Right-multiply transpose of square matrix \a A by itself, returning the
 * result \f$ A^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatTf_srmult_squ_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatTf_srmult_squ_s(A) ((A)->funcs->rmult_squ(A,GAN_TRANSPOSE,GAN_NOINVERT,A,GAN_NOTRANSPOSE,GAN_NOINVERT,NULL))
#endif

/**
 * \brief Macro: Right-multiply transpose of square matrix by itself
 * \return Result matrix \a A.
 *
 * Right-multiply transpose of square matrix \a A by itself, filling in \a A
 * with the result \f$ A \leftarrow A^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatTf_srmult_squ_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatTf_srmult_squ_i(A) ((A)->funcs->rmult_squ(A,GAN_TRANSPOSE,GAN_NOINVERT,A,GAN_NOTRANSPOSE,GAN_NOINVERT,A))
#endif

/**
 * \brief Macro: Right-multiply inverse of square matrix by its inverse transpose
 * \return Result matrix \a B.
 *
 * Right-multiply inverse of square matrix \a A by its inverse transpose,
 * writing the result into square matrix \f$ B = A^{-1} A^{-{\top}} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatIf_srmultIT_squ_q ( Gan_SquMatrix_f *A,
                                               Gan_SquMatrix_f *B );
#else
#define gan_squmatIf_srmultIT_squ_q(A,B) ((A)->funcs->rmult_squ(A,GAN_NOTRANSPOSE,GAN_INVERT,A,GAN_TRANSPOSE,GAN_INVERT,B))
#endif

/**
 * \brief Macro: Right-multiply inverse of square matrix by its inverse transpose
 * \return Result as a new matrix.
 *
 * Right-multiply inverse of square matrix \a A by its inverse transpose,
 * returning the result \f$ A^{-1} A^{-{\top}} \f$ as a new square matrix.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatIf_srmultIT_squ_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatIf_srmultIT_squ_s(A) ((A)->funcs->rmult_squ(A,GAN_NOTRANSPOSE,GAN_INVERT,A,GAN_TRANSPOSE,GAN_INVERT,NULL))
#endif

/**
 * \brief Macro: Right-multiply inverse of square matrix by its inverse transpose
 * \return Result matrix \a A.
 *
 * Right-multiply inverse of square matrix \a A by its inverse transpose,
 * overwriting \a A with the result \f$ A \leftarrow A^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatIf_srmultIT_squ_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatIf_srmultIT_squ_i(A) ((A)->funcs->rmult_squ(A,GAN_NOTRANSPOSE,GAN_INVERT,A,GAN_TRANSPOSE,GAN_INVERT,A))
#endif

/**
 * \brief Macro: Self-multiply inverse transpose by inverse of square matrix.
 * \return Result matrix \a B.
 *
 * Self-multiply inverse transpose by inverse of square matrix \a A, writing
 * the result into square matrix \f$ B = A^{-{\top}} A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatITf_srmultI_squ_q ( Gan_SquMatrix_f *A,
                                               Gan_SquMatrix_f *B );
#else
#define gan_squmatITf_srmultI_squ_q(A,B) ((A)->funcs->rmult_squ(A,GAN_TRANSPOSE,GAN_INVERT,A,GAN_NOTRANSPOSE,GAN_INVERT,B))
#endif

/**
 * \brief Macro: Self-multiply inverse transpose by inverse of square matrix.
 * \return Result as a new matrix.
 *
 * Self-multiply inverse transpose by inverse of square matrix \a A,
 * returning the result \f$ A^{-{\top}} A^{-1} \f$ as a new square matrix.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatITf_srmultI_squ_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatITf_srmultI_squ_s(A) ((A)->funcs->rmult_squ(A,GAN_TRANSPOSE,GAN_INVERT,A,GAN_NOTRANSPOSE,GAN_INVERT,NULL))
#endif

/**
 * \brief Macro: Self-multiply inverse transpose by inverse of square matrix.
 * \return Result matrix \a A.
 *
 * Self-multiply inverse transpose by inverse of square matrix \a A,
 * filling in \a A with the result \f$ A \leftarrow A^{-{\top}} A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatITf_srmultI_squ_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatITf_srmultI_squ_i(A) ((A)->funcs->rmult_squ(A,GAN_TRANSPOSE,GAN_INVERT,A,GAN_NOTRANSPOSE,GAN_INVERT,A))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeTripleMatrixProduct
 * \{
 */

/**
 * \brief Macro: Multiply symmetric matrix on left and right by generic matrix and transpose.
 * \return Result matrix \a D.
 *
 * Multiply symmetric matrix \a A on the left by generic matrix \a B and on
 * the right by \f$ B^{\top} \f$. The result is written into the result matrix
 * \f$ D = B A B^{\top} \f$. The intermediate result \f$ C = A B^{\top} \f$
 * is written into \a C. \a C may be passed as \c NULL, in which case it
 * is allocated and freed inside the routine.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_symmatf_lrmult_q ( Gan_SquMatrix_f *A, const Gan_Matrix_f *B,
                                        const Gan_Matrix_f *C, Gan_SquMatrix_f *D );
#else
#define gan_symmatf_lrmult_q(A,B,C,D) (assert(gan_squmatf_symmetric(A)),(A)->funcs->lrmult(A,B,GAN_NOTRANSPOSE,C,D))
#endif

/**
 * \brief Macro: Multiply symmetric matrix on left and right by generic matrix and transpose.
 * \return Result as a new matrix.
 *
 * Multiply symmetric matrix \a A on the left by generic matrix \a B and
 * on the right by \f$ B^{\top} \f$, creating and returning the result matrix
 * \f$ B A B^{\top} \f$. The intermediate result \f$ C = A B^{\top} \f$
 * is written into \a C. \a C may be passed as \c NULL, in which case it
 * is allocated and freed inside the routine.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_symmatf_lrmult_s ( Gan_SquMatrix_f *A, const Gan_Matrix_f *B,
                                        const Gan_Matrix_f *C );
#else
#define gan_symmatf_lrmult_s(A,B,C) (assert(gan_squmatf_symmetric(A)),(A)->funcs->lrmult(A,B,GAN_NOTRANSPOSE,C,NULL))
#endif

/**
 * \brief Macro: Multiply symmetric matrix on left and right by generic matrix and transpose.
 * \return Result matrix \a D.
 *
 * Multiply symmetric matrix \a A on the right by generic matrix \a B and on
 * the left by \f$ B^{\top} \f$. The result is written into the result matrix
 * \f$ D = B^{\top} A B \f$. The intermediate result \f$ C = A B \f$
 * is written into \a C. \a C may be passed as \c NULL, in which case it
 * is allocated and freed inside the routine.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_symmatf_lrmultT_q ( Gan_SquMatrix_f *A, const Gan_Matrix_f *B,
                                         const Gan_Matrix_f *C, Gan_SquMatrix_f *D );
#else
#define gan_symmatf_lrmultT_q(A,B,C,D) (assert(gan_squmatf_symmetric(A)),(A)->funcs->lrmult(A,B,GAN_TRANSPOSE,C,D))
#endif

/**
 * \brief Macro: Multiply symmetric matrix on left and right by generic matrix and transpose.
 * \return Result as a new matrix.
 *
 * Multiply symmetric matrix \a A on the right by generic matrix \a B and
 * on the left by \f$ B^{\top} \f$, creating and returning the result matrix
 * \f$ B^{\top} A B \f$. The intermediate result \f$ C = A B \f$
 * is written into \a C. \a C may be passed as \c NULL, in which case it
 * is allocated and freed inside the routine.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_symmatf_lrmultT_s ( Gan_SquMatrix_f *A, const Gan_Matrix_f *B,
                                         const Gan_Matrix_f *C );
#else
#define gan_symmatf_lrmultT_s(A,B,C) (assert(gan_squmatf_symmetric(A)),(A)->funcs->lrmult(A,B,GAN_TRANSPOSE,C,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixInvert
 * \{
 */

/**
 * \brief Macro: Apply matrix inversion.
 * \return Result matrix \a B.
 *
 * Apply matrix inversion to square matrix \a A, writing result into
 * square matrix \f$ B = A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_invert_q ( Gan_SquMatrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_squmatf_invert_q(A,B) ((A)->funcs->invert(A,B))
#endif

/**
 * \brief Macro: Apply matrix inversion.
 * \return Result as a new matrix.
 *
 * Apply matrix inversion to square matrix \a A, creating and returning
 * a new square matrix for the result \f$ A^{-1} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_invert_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_invert_s(A) ((A)->funcs->invert(A,NULL))
#endif

/**
 * \brief Macro: Apply matrix inversion.
 * \return Result matrix \a A.
 *
 * Apply matrix inversion to square matrix \a A, computing the result
 * \f$ A \leftarrow A^{-1} \f$ in-place in \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_invert_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_invert_i(A) ((A)->funcs->invert(A,A))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixCholesky
 * \{
 */

/**
 * \brief Macro: Apply Cholesky factorisation.
 * \return Result matrix \a L.
 *
 * Apply Cholesky factorisation to symmetric or diagonal matrix \a A, writing
 * result into lower triangular matrix \a L so that \f$ A = L L^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_cholesky_q ( Gan_SquMatrix_f *A,
                                          Gan_SquMatrix_f *L );
#else
#define gan_squmatf_cholesky_q(A,L) ((A)->funcs->cholesky(A,L,NULL))
#endif

/**
 * \brief Macro: Apply Cholesky factorisation.
 * \return Result as a new matrix.
 *
 * Apply Cholesky factorisation to symmetric or diagonal matrix \a A, creating
 * and returning a new lower triangular matrix \a L for the result so
 * that \f$ A = L L^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_cholesky_s ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_cholesky_s(A) ((A)->funcs->cholesky(A,NULL,NULL))
#endif

/**
 * \brief Macro: Apply Cholesky factorisation.
 * \return Result matrix \a A.
 *
 * Apply Cholesky factorisation to symmetric or diagonal matrix \a A,
 * computing the result \a L in-place in \a A so that \f$ A = L L^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_cholesky_i ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_cholesky_i(A) ((A)->funcs->cholesky(A,A,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixNorms
 * \{
 */

/**
 * \brief Macro: Squared Frobenius norm of square matrix.
 *
 * Return squared Frobenius norm of square matrix \a A, i.e. the sum of
 * the squared elements of \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_squmatf_sumsqr ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_sumsqr(A) ((A)->funcs->sumsqr(A))
#endif

/**
 * \brief Macro: Frobenius norm of square matrix.
 *
 * Return Frobenius norm of square matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_squmatf_Fnorm ( Gan_SquMatrix_f *A );
#else
#define gan_squmatf_Fnorm(A) ((A)->funcs->Fnorm(A))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixConvert
 * \{
 */

/**
 * \brief Macro: Convert square matrix to generic matrix.
 * \return Result generic rectangular matrix \a B.
 *
 * Convert square matrix \a A to generic matrix \a B.
 *
 * \sa gan_matf_from_squmatf_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_from_squmatf_q ( const Gan_SquMatrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_from_squmatf_q(A,B) ((A)->funcs->matrix(A,B))
#endif

/**
 * \brief Macro: Convert square matrix to generic matrix.
 * \return Result generic rectangular matrix as new matrix.
 *
 * Convert square matrix \a A to generic matrix, which is created.
 *
 * \sa gan_matf_from_squmatf_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_from_squmatf_s ( const Gan_SquMatrix_f *A );
#else
#define gan_matf_from_squmatf_s(A) ((A)->funcs->matrix(A,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixTest
 * \{
 */

/**
 * \brief Macro: Checks that two square matrices have the same type.
 *
 * Returns #GAN_TRUE if \a A and \a B have the same type, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_same_type ( const Gan_SquMatrix_f *A, const Gan_SquMatrix_f *B );
#else
#define gan_squmatf_same_type(A,B) ((A)->type == (B)->type)
#endif

/**
 * \brief Macro: Checks that two square matrices have the same size.
 *
 * Returns #GAN_TRUE if \a A and \a B have the same size, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_same_size ( const Gan_SquMatrix_f *A, const Gan_SquMatrix_f *B );
#else
#define gan_squmatf_same_size(A,B) ((A)->size == (B)->size)
#endif

/**
 * \brief Macro: Checks that two square matrices have the same type and size.
 *
 * Returns #GAN_TRUE if \a A and \a B have the same type and size, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_same_type_size ( const Gan_SquMatrix_f *A, const Gan_SquMatrix_f *B );
#else
#define gan_squmatf_same_type_size(A,B) ((A)->type == (B)->type && (A)->size == (B)->size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixSet
 * \{
 */

/**
 * \brief Macro: Set type of square matrix.
 * \return Matrix \a A.
 *
 * Set type of square matrix \a A to \a type. The size of \a A is unchanged.
 *
 * Implemented as a macro call to gan_squmatf_set_type_size().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_set_type ( Gan_SquMatrix_f *A,
                                        Gan_SquMatrixType type );
#else
#define gan_squmatf_set_type(A,type) gan_squmatf_set_type_size(A,type,(A)->size)
#endif

/**
 * \brief Macro: Set size of square matrix.
 * \return Matrix \a A.
 *
 * Set size of square matrix \a A to \a size. The type of \a A is unchanged.
 *
 * Implemented as a macro call to gan_squmatf_set_type_size().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_set_size ( Gan_SquMatrix_f *A,
                                        unsigned long size );
#else
#define gan_squmatf_set_size(A,size) gan_squmatf_set_type_size(A,(A)->type,size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixTest
 * \{
 */

/**
 * \brief Macro: Test size of square matrix.
 *
 * Returns #GAN_TRUE if square matrix \a A has given \a size, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_test_size ( const Gan_Matrix_f *A, unsigned long size );
#else
#define gan_squmatf_test_size(A,s) ((A)->size==s)
#endif

/**
 * \brief Macro: Test whether square matrix has symmetric type.
 *
 * Returns #GAN_TRUE if square matrix \a A is of symmetric type
 * #GAN_SYMMETRIC_MATRIX, #GAN_FALSE otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_symmetric_type ( const Gan_SquMatrix_f *A );
#else
#define gan_squmatf_symmetric_type(A) ((A)->type==GAN_SYMMETRIC_MATRIX)
#endif

/**
 * \brief Macro: Test whether square matrix has diagonal type.
 *
 * Returns #GAN_TRUE if square matrix \a A is of diagonal type
 * #GAN_DIAGONAL_MATRIX, #GAN_FALSE otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_diagonal_type ( const Gan_SquMatrix_f *A );
#else
#define gan_squmatf_diagonal_type(A) ((A)->type==GAN_DIAGONAL_MATRIX)
#endif

/**
 * \brief Macro: Test whether square matrix is symmetric.
 *
 * Returns #GAN_TRUE if square matrix \a A is of symmetric type,
 * either explicitly #GAN_SYMMETRIC_MATRIX or one of the other symmetric
 * types, such as #GAN_DIAGONAL_MATRIX or #GAN_SCALED_IDENT_MATRIX.
 * #GAN_FALSE is returned if \a A is not one of these faults.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_symmetric ( const Gan_SquMatrix_f *A );
#else
#define gan_squmatf_symmetric(A) ((A)->type==GAN_SYMMETRIC_MATRIX || (A)->type==GAN_DIAGONAL_MATRIX || (A)->type==GAN_SCALED_IDENT_MATRIX)
#endif

/**
 * \brief Macro: Test whether square matrix is diagonal.
 *
 * Returns #GAN_TRUE if square matrix \a A is of diagonal type,
 * either explicitly #GAN_DIAGONAL_MATRIX or one of the other diagonal
 * types such as #GAN_SCALED_IDENT_MATRIX.
 * #GAN_FALSE is returned if \a A is not one of these faults.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_squmatf_diagonal ( const Gan_SquMatrix_f *A );
#else
#define gan_squmatf_diagonal(A) ((A)->type==GAN_DIAGONAL_MATRIX || (A)->type==GAN_SCALED_IDENT_MATRIX)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixIO
 * \{
 */

/**
 * \brief Macro: Read square matrix from ASCII file.
 *
 * Read square matrix from file pointer \a fp. The prefix string for
 * the matrix is read from the file into the \a prefix string, up to the
 * maximum length \a prefix_len of the \a prefix string. Any remaining
 * characters after \a prefix has been filled are ignored. Pass \c NULL for
 * \a prefix and zero for \a prefix_len to ignore the prefix string.
 *
 * \return Read matrix on success, \c NULL on failure.
 * \sa: gan_squmatf_fscanf_q()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_fscanf_s ( FILE *fp,
                                        const char *prefix, int prefix_len );
#else
#define gan_squmatf_fscanf_s(fp,p,pl) gan_squmatf_fscanf_q(fp,NULL,p,pl)
#endif

/**
 * \brief Macro: Read square matrix from binary file.
 * Read square matrix from file pointer \a fp in binary format. The magic
 * number for the matrix is read from the file into the provided pointer.
 *
 * \return Read matrix on success, \c NULL on failure.
 * \sa: gan_squmatf_fread_q()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_squmatf_fread_s ( FILE *fp, gan_uint32 *magic_number );
#else
#define gan_squmatf_fread_s(fp,m) gan_squmatf_fread_q(fp,NULL,m)
#endif

/**
 * \}
 */

GANDALF_API void gan_squmatf_free ( Gan_SquMatrix_f *A );
GANDALF_API void gan_squmatf_free_va ( Gan_SquMatrix_f *A, ... );
GANDALF_API Gan_SquMatrix_f *gan_squmatf_set_type_size ( Gan_SquMatrix_f *A,
                                             Gan_SquMatrixType type,
                                             unsigned long size );
GANDALF_API Gan_SquMatrix_f *gan_squmatf_fill_vap ( Gan_SquMatrix_f *A,
                                        Gan_SquMatrixType type,
                                        unsigned long size, va_list *aptr );
GANDALF_API Gan_SquMatrix_f *gan_squmatf_fill_const_q ( Gan_SquMatrix_f *A,
                                            Gan_SquMatrixType type,
                                            unsigned long size, float value );
GANDALF_API size_t gan_squmatf_data_size ( Gan_SquMatrixType type, unsigned long size );
GANDALF_API Gan_SquMatrix_f *gan_squmatf_fscanf_q ( FILE *fp, Gan_SquMatrix_f *A,
                                        char *prefix, int prefix_len );
GANDALF_API Gan_Bool gan_squmatf_fwrite ( FILE *fp, const Gan_SquMatrix_f *A,
                              gan_uint32 magic_number );
GANDALF_API Gan_SquMatrix_f *gan_squmatf_fread_q ( FILE *fp, Gan_SquMatrix_f *A,
                                       gan_uint32 *magic_number );

/* not user functions */
GANDALF_API Gan_SquMatrix_f *gan_squmatf_form_gen ( Gan_SquMatrix_f *A,
                                        Gan_SquMatrixType type,
                                        unsigned long size,
                                        float *data, size_t data_size );
GANDALF_API void gan_squmatf_free_func ( Gan_SquMatrix_f *A );
#ifndef NDEBUG
GANDALF_API void gan_squmatf_db ( const Gan_SquMatrix_f *A ); /* for use in a debugger */
#endif

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

#endif /* #ifndef _GAN_MATF_SQUARE_H */
