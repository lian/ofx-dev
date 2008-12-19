/**
 * File:          $RCSfile: matf_gen.h,v $
 * Module:        Generic rectangular matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.16 $
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

#ifndef _GAN_MATF_GEN_H
#define _GAN_MATF_GEN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/common/misc_error.h>
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

#ifndef GAN_SQUMATRIXF_STRUCT_DEFINED
struct Gan_SquMatrix_f;
#endif

/// Structure definition for single precision general size matrix
typedef struct Gan_Matrix_f
{
   /* row and column dimensions of matrix */
   unsigned long rows, cols;

   /* data array containing matrix elements */
   float *data;

   /* allocated size of matrix (number of float's) */
   size_t data_size;

   /* flag indicating whether matrix data was dynamically allocated */
   Gan_Bool data_alloc;

   /* flag indicating whether matrix structure was dynamically allocated */
   Gan_Bool struct_alloc;
} Gan_Matrix_f;

#define GAN_MATRIXF_STRUCT_DEFINED

#include <gandalf/linalg/vecf_gen.h>
#include <gandalf/linalg/matf_square.h>

GANDALF_API void gan_matf_free ( Gan_Matrix_f *A );
GANDALF_API Gan_Matrix_f *gan_matf_set_dims ( Gan_Matrix_f *A,
                                  unsigned long rows, unsigned long cols );
GANDALF_API Gan_Matrix_f *gan_matf_fill_va ( Gan_Matrix_f *A,
                                 unsigned long rows, unsigned long cols, ... );
GANDALF_API Gan_Matrix_f *gan_matf_fill_vap ( Gan_Matrix_f *A,
                                  unsigned long rows, unsigned long cols,
                                  va_list *aptr );
GANDALF_API Gan_Matrix_f *gan_matf_fill_const_q ( Gan_Matrix_f *A,
                                      unsigned long rows, unsigned long cols,
                                      float value );
GANDALF_API Gan_Bool gan_matf_read_va ( const Gan_Matrix_f *A,
                            unsigned long rows, unsigned long cols, ... );
GANDALF_API Gan_Matrix_f *gan_matf_copy_q ( const Gan_Matrix_f *A, Gan_Matrix_f *B );
GANDALF_API Gan_Matrix_f *gan_matf_scale_q ( Gan_Matrix_f *A, float a, Gan_Matrix_f *B );
GANDALF_API Gan_Matrix_f *gan_matf_divide_q ( Gan_Matrix_f *A, float a, Gan_Matrix_f *B );
GANDALF_API Gan_Matrix_f *gan_matf_tpose_q ( Gan_Matrix_f *A, Gan_Matrix_f *B );
GANDALF_API Gan_Bool gan_matf_is_zero ( Gan_Matrix_f *A );
GANDALF_API Gan_Matrix_f *gan_matf_insertsym ( Gan_Matrix_f *A,
                                   unsigned long rA, unsigned long cA,
                                   const struct Gan_SquMatrix_f *B,
                                   unsigned long rB, unsigned long cB,
                                   unsigned long rows , unsigned long cols );
GANDALF_API void gan_matf_free_va ( Gan_Matrix_f *A, ... );
GANDALF_API Gan_Matrix_f *gan_matf_extract_q ( const Gan_Matrix_f *A,
                                   unsigned long r0,   unsigned long c0,
                                   unsigned long rows, unsigned long cols,
                                   Gan_Matrix_f *B );
GANDALF_API float gan_matf_sumsqr ( const Gan_Matrix_f *A );
GANDALF_API float gan_matf_Fnorm ( const Gan_Matrix_f *A );
GANDALF_API Gan_Matrix_f *gan_matf_invert_q ( const Gan_Matrix_f *A, Gan_Matrix_f *B );
GANDALF_API Gan_Bool gan_matf_fprint ( FILE *fp, const Gan_Matrix_f *A, const char *prefix,
                           unsigned indent, const char *fmt );
GANDALF_API Gan_Matrix_f *gan_matf_fscanf_q ( FILE *fp, Gan_Matrix_f *A,
                                  char *prefix, int prefix_len );
GANDALF_API Gan_Bool gan_matf_fwrite ( FILE *fp, const Gan_Matrix_f *A, gan_uint32 magic_number );
GANDALF_API Gan_Matrix_f *gan_matf_fread_q ( FILE *fp, Gan_Matrix_f *A,
                                 gan_uint32 *magic_number );

#ifdef GAN_GENERATE_DOCUMENTATION
#define Gan_SquMatrix_f struct Gan_SquMatrix_f
#endif

/**
 * \addtogroup GeneralSizeMatrixAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a generic matrix.
 *
 * Allocates and returns a generic rectangular matrix with given dimensions.
 *
 * Implemented as a macro call to gan_matf_form_gen().
 * \sa gan_matf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_alloc ( unsigned long rows, unsigned long cols );
#else
#define gan_matf_alloc(rows,cols) gan_matf_form_gen(NULL,rows,cols,NULL,0)
#endif

/**
 * \brief Macro: Form and return a generic matrix.
 *
 * Forms and returns a generic rectangular matrix with given dimensions.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is filled; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_matf_form_gen().
 * \sa gan_matf_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_form ( Gan_Matrix_f *A,
                              unsigned long rows, unsigned long cols );
#else
#define gan_matf_form(A,rows,cols) gan_matf_form_gen(A,rows,cols,NULL,0)
#endif

/**
 * \brief Macro: Form and return a generic matrix.
 *
 * Forms and returns a generic rectangular matrix with given dimensions.
 * If the \a A matrix pointer is non-\c NULL, the given matrix pointer
 * is filled; otherwise \a A is passed as \c NULL and the matrix is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the matrix data is dynamically allocated. Otherwise, \a data_size is
 * the size of the \a data array in terms of \c float values.
 *
 * Implemented as a macro call to gan_matf_form_gen().
 *
 * \sa gan_matf_alloc(), gan_matf_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_form_data ( Gan_Matrix_f *A,
                                   unsigned long rows, unsigned long cols,
                                   float *data, size_t data_size );
#else
#define gan_matf_form_data(A,rows,cols,data,data_size)\
            gan_matf_form_gen(A,rows,cols,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixAccessElement
 * \{
 */

/**
 * \brief Macro: Set specific element of matrix.
 *
 * Macro to set element \a i,\a j of generic matrix.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_matf_set_el ( Gan_Matrix_f *A,
                           unsigned i, unsigned j, float value);
#else
#ifdef NDEBUG
#define gan_matf_set_el(A,i,j,v) ((A)->data[(j)*(A)->rows+(i)] = (v), GAN_TRUE)
#else
#define gan_matf_set_el(A,i,j,v) ((unsigned)(i)>=(A)->rows || \
                                  (unsigned)(j)>=(A)->cols \
                                 ? (gan_err_flush_trace(),\
                                    gan_err_register("gan_matf_set_el",\
                                                     GAN_ERROR_TOO_LARGE,""),\
                                    GAN_FALSE)\
                                 : ((A)->data[(j)*(A)->rows+(i)] = (v),\
                                    GAN_TRUE))
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Get specific element of matrix.
 *
 * Return element \a i,\a j of generic matrix, or \c FLT_MAX on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_matf_get_el ( const Gan_Matrix_f *A, unsigned i, unsigned j );
#else
#ifdef NDEBUG
#define gan_matf_get_el(A,i,j) (A)->data[(j)*(A)->rows+(i)]
#else
#define gan_matf_get_el(A,i,j) ((unsigned)(i)>=(A)->rows || \
                                (unsigned)(j)>=(A)->cols \
                               ? (gan_err_flush_trace(),\
                                  gan_err_register("gan_matf_get_el",\
                                                   GAN_ERROR_TOO_LARGE,""),\
                                  FLT_MAX)\
                               : (A)->data[(j)*(A)->rows+(i)])
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Increment specific element of matrix by given value.
 *
 * Increment element \a i,\a j of generic matrix by given value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_matf_inc_el ( Gan_Matrix_f *A,
                           unsigned i, unsigned j, float value);
#else
#ifdef NDEBUG
#define gan_matf_inc_el(A,i,j,v) ((A)->data[(j)*(A)->rows+(i)] += (v),GAN_TRUE)
#else
#define gan_matf_inc_el(A,i,j,v) ((unsigned)(i)>=(A)->rows || \
                                  (unsigned)(j)>=(A)->cols \
                                 ? (gan_err_flush_trace(),\
                                    gan_err_register("gan_matf_inc_el",\
                                                     GAN_ERROR_TOO_LARGE,""),\
                                    GAN_FALSE)\
                                 : ((A)->data[(j)*(A)->rows+(i)] += (v),\
                                    GAN_TRUE))
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Decrement specific element of matrix by given value.
 *
 * Decrement element \a i,\a j of generic matrix by given value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_matf_dec_el ( Gan_Matrix_f *A,
                           unsigned i, unsigned j, float value);
#else
#ifdef NDEBUG
#define gan_matf_dec_el(A,i,j,v) ((A)->data[(j)*(A)->rows+(i)] -= (v),GAN_TRUE)
#else
#define gan_matf_dec_el(A,i,j,v) ((unsigned)(i)>=(A)->rows || \
                                  (unsigned)(j)>=(A)->cols \
                                 ? (gan_err_flush_trace(),\
                                    gan_err_register("gan_matf_dec_el",\
                                                     GAN_ERROR_TOO_LARGE,""),\
                                    GAN_FALSE)\
                                 : ((A)->data[(j)*(A)->rows+(i)] -= (v),\
                                    GAN_TRUE))
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixIO
 * \{
 */

/**
 * \brief Macro: Print matrix to standard output.
 *
 * Print matrix \a A to standard output, with prefix string \a prefix,
 * indentation \a indent and floating-point format \a fmt.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_matf_print ( const Gan_Matrix_f *A,
                          const char *prefix, int indent, const char *fmt );
#else
#define gan_matf_print(A,p,i,f) (gan_matf_fprint(stdout,A,p,i,f))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Allocate and fill elements of a matrix with the same value.
 * \param rows The new row size of the matrix
 * \param cols The new column size of the matrix
 * \param value The value to set each element of the matrix to
 * \return non-\c NULL on successfully allocating and filling the matrix, or
 *         \c NULL on failure.
 *
 * Allocate a matrix, set the dimensions of it to rows by cols,
 * and fill each element with the provided value.
 * \sa gan_matf_fill_const_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_fill_const_s ( unsigned long rows, unsigned long cols,
                                      float value );
#else
#define gan_matf_fill_const_s(r,c,v) gan_matf_fill_const_q(NULL,r,c,v)
#endif

/**
 * \brief Macro: Fill matrix with zeros.
 * \param A The matrix to be filled
 * \param rows The new row size of the matrix
 * \param cols The new column size of the matrix
 * \return non-\c NULL Successfully filled matrix, or \c NULL on failure.
 *
 * et the dimensions of \a A to \a rows by \a cols, and fill it with zeros.
 * \sa gan_matf_fill_zero_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_fill_zero_q ( Gan_Matrix_f *A,
                                     unsigned long rows, unsigned long cols );
#else
#define gan_matf_fill_zero_q(A,r,c) gan_matf_fill_const_q(A,r,c,0.0)
#endif

/**
 * \brief Macro: Allocate and fill matrix with zeros.
 * \param rows The new row size of the matrix
 * \param cols The new column size of the matrix
 * \return non-\c NULL Successfully allocated and filled matrix, or
 *         \c NULL on failure.
 *
 * Allocate a matrix, set the dimensions of it to \a rows by \a cols,
 * and fill it with zeros.
 * \sa gan_matf_fill_zero_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_fill_zero_s ( unsigned long rows, unsigned cols );
#else
#define gan_matf_fill_zero_s(r,c) gan_matf_fill_const_s(r,c,0.0)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixCopy
 * \{
 */

/**
 * \brief Macro: Copy matrix.
 *
 * Allocate and return a copy of matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_copy_s ( const Gan_Matrix_f *A );
#else
#define gan_matf_copy_s(A) (gan_matf_copy_q(A,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixScale
 * \{
 */

/**
 * \brief Macro: Multiply matrix by scalar.
 *
 * Allocate and return a copy of matrix \a A multiplied by scalar \a a.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_scale_s ( Gan_Matrix_f *A, float a );
#else
#define gan_matf_scale_s(A,a) (gan_matf_scale_q(A,a,NULL))
#endif

/**
 * \brief Macro: Multiply matrix by scalar.
 *
 * Multiply matrix \a A by scalar \a a in-place.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_scale_i ( Gan_Matrix_f *A, float a );
#else
#define gan_matf_scale_i(A,a) (gan_matf_scale_q(A,a,A))
#endif

/**
 * \brief Macro: Divide matrix by scalar.
 *
 * Allocate and return a copy of matrix \a A divided by scalar \a a.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_divide_s ( Gan_Matrix_f *A, float a );
#else
#define gan_matf_divide_s(A,a) (gan_matf_divide_q(A,a,NULL))
#endif

/**
 * \brief Macro: Divide matrix by scalar.
 *
 * Divide matrix \a A by scalar \a a in-place.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_divide_i ( Gan_Matrix_f *A, float a );
#else
#define gan_matf_divide_i(A,a) (gan_matf_divide_q(A,a,A))
#endif

/**
 * \brief Macro: Negate matrix.
 *
 * Negate matrix \a A into matrix \a B, and return \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_negate_q ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_negate_q(A,B) (gan_matf_scale_q(A,-1.0,B))
#endif

/**
 * \brief Macro: Negate matrix.
 *
 * Allocate and return a negated copy of matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_negate_s ( Gan_Matrix_f *A );
#else
#define gan_matf_negate_s(A) (gan_matf_scale_q(A,-1.0,NULL))
#endif

/**
 * \brief Macro: Negate matrix.
 *
 * Negate matrix \a A in-place.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_negate_i ( Gan_Matrix_f *A );
#else
#define gan_matf_negate_i(A) (gan_matf_scale_q(A,-1.0,A))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixTranspose
 * \{
 */

/**
 * \brief Macro: Transpose matrix.
 *
 * Allocate and return the transpose \f$ A^{\top} \f$ of matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_tpose_s ( Gan_Matrix_f *A );
#else
#define gan_matf_tpose_s(A) (gan_matf_tpose_q(A,NULL))
#endif

/**
 * \brief Macro: Transpose matrix.
 *
 * Transpose matrix \a A in-place: \f$ A \leftarrow A^{\top} \f$.
 * \a A must be square.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_tpose_i ( Gan_Matrix_f *A );
#else
#define gan_matf_tpose_i(A) (gan_matf_tpose_q(A,A))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixAdd
 * \{
 */

/**
 * \brief Macro: Add two matrices and write result into a third.
 *
 * Add two matrices \a A, \a B and write result into
 * \f$ C = A + B \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_add_q ( Gan_Matrix_f *A, Gan_Matrix_f *B,
                               Gan_Matrix_f *C );
#else
#define gan_matf_add_q(A,B,C) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two matrices and return the result as a new matrix.
 *
 * Add two matrices \a A, \a B and return the result as a new matrix
 * \f$ A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_add_s ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_add_s(A,B) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add two matrices and overwrite the first with the result.
 *
 * Add two matrices \a A, \a B and overwrite \a A with the result:
 * \f$ A \leftarrow A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_add_i1 ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_add_i1(A,B) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Add two matrices and overwrite the second with the result.
 *
 * Add two matrices \a A, \a B and overwrite \a B with the result:
 * \f$ B \leftarrow A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_add_i2 ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_add_i2(A,B) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(B)))
#endif

/**
 * \brief Macro: Increment a matrix with another matrix.
 *
 * Increment matrix \a A with matrix \a B, and return \a A, i.e.
 * \f$ A \leftarrow A + B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_increment ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_increment(A,B) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Add two matrices, the second transposed, and write result into a third.
 *
 * Add matrix \a A and the transpose of matrix \a B and write result
 * into \f$ C = A + B^{\top} \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_addT_q ( Gan_Matrix_f *A, Gan_Matrix_f *B,
                                Gan_Matrix_f *C );
#else
#define gan_matf_addT_q(A,B,C) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two matrices, the second transposed, and return a new result matrix.
 *
 * Add matrix \a A and the transpose of matrix \a B and return the
 * result as a new matrix \f$ A + B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_addT_s ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_addT_s(A,B) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Increment a matrix with the transpose of another matrix.
 *
 * Increment matrix \a A with the transpose of matrix \a B, and return \a A,
 * i.e. \f$ A \leftarrow A + B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_incrementT ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_incrementT(A,B) (gan_matf_add_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Add two matrices and write result into a symmetric matrix.
 *
 * Add two matrices \a A, \a B and write result into
 * \f$ C = A + B \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_add_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                      Gan_SquMatrix_f *C );
#else
#define gan_matf_add_sym_q(A,B,C) (gan_matf_add_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two matrices and return the result as a new symmetric matrix.
 *
 * Add two matrices \a A, \a B and return the result as a new matrix
 * \f$ A + B \f$. \a C is square and is \em assumed to be symmetric.
 * No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_add_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_add_sym_s(A,B) (gan_matf_add_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add two matrices and write result into a symmetric matrix.
 *
 * Add two matrices \a A, \a B, transposing \a B, and write result into
 * \f$ C = A + B^{\top} \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_addT_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                       Gan_SquMatrix_f *C );
#else
#define gan_matf_addT_sym_q(A,B,C) (gan_matf_add_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two matrices and return the result as a new symmetric matrix.
 *
 * Add two matrices \a A, \a B, transposing \a B, and return the
 * result as a new matrix \f$ A + B^{\top} \f$. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_addT_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_addT_sym_s(A,B) (gan_matf_add_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add two matrices and write result into a symmetric matrix.
 *
 * Add two matrices \a A, \a B, transposing \a A, and write result into
 * \f$ C = A^{\top} + B \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_add_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                       Gan_SquMatrix_f *C );
#else
#define gan_matTf_add_sym_q(A,B,C) (gan_matf_add_sym_gen(A,GAN_TRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two matrices and return the result as a new symmetric matrix.
 *
 * Add two matrices \a A, \a B, transposing \a A, and return the
 * result as a new matrix \f$ A^{\top} + B \f$. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_add_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matTf_add_sym_s(A,B) (gan_matf_add_sym_gen(A,GAN_TRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add two matrices and write result into a symmetric matrix.
 *
 * Add two matrices \a A, \a B, both transposed, and write result into
 * \f$ C = A^{\top} + B^{\top} \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_addT_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                        Gan_SquMatrix_f *C );
#else
#define gan_matTf_addT_sym_q(A,B,C) (gan_matf_add_sym_gen(A,GAN_TRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Add two matrices and return the result as a new symmetric matrix.
 *
 * Add two matrices \a A, \a B, both transposed, and return the result
 * as a new matrix \f$ A^{\top} + B^{\top} \f$. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_addT_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matTf_addT_sym_s(A,B) (gan_matf_add_sym_gen(A,GAN_TRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add matrix to itself and write result into a symmetric matrix.
 *
 * Add matrix \a A to its own transpose, and write result into
 * square symmetric matrix \f$ B = A + A^{\top} \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_saddT_sym_q ( const Gan_Matrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_matf_saddT_sym_q(A,B) (gan_matf_add_sym_gen(A,GAN_NOTRANSPOSE,A,GAN_TRANSPOSE,B))
#endif

/**
 * \brief Macro: Add matrix to itself and return the result as a new symmetric matrix.
 *
 * Add matrix \a A to its own transpose, and return the result as
 * a new square symmetric matrix \f$ A + A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_saddT_sym_s ( const Gan_Matrix_f *A );
#else
#define gan_matf_saddT_sym_s(A) (gan_matf_add_sym_gen(A,GAN_NOTRANSPOSE,A,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Add matrix to itself and write result into a symmetric matrix.
 *
 * Add transpose of matrix \a A to \a A, and write result into
 * square symmetric matrix \f$ B = A^{\top} + A \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_sadd_sym_q ( const Gan_Matrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_matTf_sadd_sym_q(A,B) (gan_matf_add_sym_gen(A,GAN_TRANSPOSE,A,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Add matrix to itself and return the result as a new symmetric matrix.
 *
 * Add transpose of matrix \a A to \a A, and return the result as
 * a new square symmetric matrix \f$ A^{\top} + A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_sadd_sym_s ( const Gan_Matrix_f *A );
#else
#define gan_matTf_sadd_sym_s(A) (gan_matf_add_sym_gen(A,GAN_TRANSPOSE,A,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixSubtract
 * \{
 */

/**
 * \brief Macro: Subtract two matrices and write result into a third.
 *
 * Subtract two matrices \a A, \a B and write result into
 * \f$ C = A - B \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_sub_q ( Gan_Matrix_f *A, Gan_Matrix_f *B, Gan_Matrix_f *C );
#else
#define gan_matf_sub_q(A,B,C) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Subtract two matrices and return the result as a new matrix.
 *
 * Subtract two matrices \a A, \a B and return the result as a new matrix
 * \f$ A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_sub_s ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_sub_s(A,B) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Subtract two matrices and overwrite the first with the result.
 *
 * Subtract two matrices \a A, \a B and overwrite \a A with the result:
 * \f$ A \leftarrow A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_sub_i1 ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_sub_i1(A,B) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Subtract two matrices and overwrite the second with the result.
 *
 * Subtract two matrices \a A, \a B and overwrite \a B with the result:
 * \f$ B \leftarrow A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_sub_i2 ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_sub_i2(A,B) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(B)))
#endif

/**
 * \brief Macro: Decrement a matrix with another matrix.
 *
 * Decrement matrix \a A with matrix \a B, and return \a A, i.e.
 * \f$ A \leftarrow A - B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_decrement ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_decrement(A,B) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,(A)))
#endif

/**
 * \brief Macro: Subtract two matrices, the second transposed, and write result into a third.
 *
 * Subtract matrix \a A and the transpose of matrix \a B and write result
 * into \f$ C = A - B^{\top} \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_subT_q ( Gan_Matrix_f *A, Gan_Matrix_f *B,
                                Gan_Matrix_f *C );
#else
#define gan_matf_subT_q(A,B,C) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Subtract two matrices, the second transposed, and return new result matrix.
 *
 * Subtract matrix \a A and the transpose of matrix \a B and return the
 * result as a new matrix \f$ A - B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_subT_s ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_subT_s(A,B) (gan_matf_subT_q(A,B,NULL))
#endif

/**
 * \brief Macro: Decrement a matrix with the transpose of another matrix.
 *
 * Decrement matrix \a A with the transpose of matrix \a B, and return \a A,
 * i.e. \f$ A \leftarrow A - B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_decrementT ( Gan_Matrix_f *A, Gan_Matrix_f *B );
#else
#define gan_matf_decrementT(A,B) (gan_matf_sub_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,(A)))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixVectorProduct
 * \{
 */

/**
 * \brief Macro: Multiply matrix and a vector, writing the result into another vector.
 *
 * Multiply matrix \a A and vector \a x, writing result into
 * \f$ y = A x \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_matf_multv_q ( const Gan_Matrix_f *A, const Gan_Vector_f *x,
                                 Gan_Vector_f *y );
#else
#define gan_matf_multv_q(A,x,y) (gan_matf_multv_gen(A,GAN_NOTRANSPOSE,x,y))
#endif

/**
 * \brief Macro: Multiply matrix and a vector, returning the result as a new vector.
 *
 * Multiply matrix \a A and vector \a x, creating and returning the
 * result \f$ A x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_matf_multv_s ( const Gan_Matrix_f *A, const Gan_Vector_f *x );
#else
#define gan_matf_multv_s(A,x) (gan_matf_multv_gen(A,GAN_NOTRANSPOSE,x,NULL))
#endif

/**
 * \brief Macro: Multiply the transpose of a matrix by a vector.
 *
 * Multiply transpose of matrix \a A and vector \a x, writing result into
 * \f$ y = A^{\top} x \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_matTf_multv_q ( const Gan_Matrix_f *A, const Gan_Vector_f *x,
                                  Gan_Vector_f *y );
#else
#define gan_matTf_multv_q(A,x,y) (gan_matf_multv_gen(A,GAN_TRANSPOSE,x,y))
#endif

/**
 * \brief Macro: Multiply transpose of matrix by a vector.
 *
 * Multiply transpose of matrix \a A and vector \a x, creating and
 * returning the result \f$ A^{\top} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector_f *gan_matTf_multv_s ( const Gan_Matrix_f *A, const Gan_Vector_f *x );
#else
#define gan_matTf_multv_s(A,x) (gan_matf_multv_gen(A,GAN_TRANSPOSE,x,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixMatrixProduct
 * \{
 */

/**
 * \brief Macro: Multiply two matrices and write result into a third.
 *
 * Multiply two matrices \a A, \a B and write result into
 * \f$ C = A B \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_rmult_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                 Gan_Matrix_f *C );
#else
#define gan_matf_rmult_q(A,B,C) (gan_matf_rmult_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply two matrices and return the result as a new matrix.
 *
 * Multiply two matrices \a A, \a B and return the result as a new matrix
 * \f$ A B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_rmult_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_rmult_s(A,B) (gan_matf_rmult_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply a matrix by the transpose of another and write result into a third.
 *
 * Multiply matrix \a A by the transpose of matrix \a B and write result into
 * \f$ C = A B^{\top} \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_rmultT_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                  Gan_Matrix_f *C );
#else
#define gan_matf_rmultT_q(A,B,C) (gan_matf_rmult_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply a matrix by the transpose of another and return a new matrix.
 *
 * Multiply matrix \a A by the transpose of matrix \a B and return the
 * result as a new matrix \f$ A B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_rmultT_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_rmultT_s(A,B) (gan_matf_rmult_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply the transpose of a matrix by another matrix.
 *
 * Multiply the transpose of matrix \a A by matrix \a B and write result into
 * \f$ C = A^{\top} B \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matTf_rmult_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                  Gan_Matrix_f *C );
#else
#define gan_matTf_rmult_q(A,B,C) (gan_matf_rmult_gen(A,GAN_TRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply the transpose of a matrix by another matrix.
 *
 * Multiply the transpose of matrix \a A by matrix \a B and return the
 * result as a new matrix \f$ A^{\top} B \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matTf_rmult_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matTf_rmult_s(A,B) (gan_matf_rmult_gen(A,GAN_TRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply the transpose of a matrix by the transpose of another matrix.
 *
 * Multiply the transpose of matrix \a A by the transpose of matrix \a B
 * and write result into \f$ C = A^{\top} B^{\top} \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matTf_rmultT_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                   Gan_Matrix_f *C );
#else
#define gan_matTf_rmultT_q(A,B,C) (gan_matf_rmult_gen(A,GAN_TRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply the transpose of a matrix by the transpose of another matrix.
 *
 * Multiply the transpose of matrix \a A by the transpose of matrix \a B
 * and return the result as a new matrix \f$ A^{\top} B^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matTf_rmultT_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matTf_rmultT_s(A,B) (gan_matf_rmult_gen(A,GAN_TRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply two matrices and write result into a symmetric matrix.
 *
 * Multiply two matrices \a A, \a B and write result into
 * \f$ C = A B \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_rmult_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                        Gan_SquMatrix_f *C );
#else
#define gan_matf_rmult_sym_q(A,B,C) (gan_matf_rmult_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply two matrices and return the result as a new symmetric matrix.
 *
 * Multiply two matrices \a A, \a B and return the result as a new matrix
 * \f$ A B \f$. \a C is square and is \em assumed to be symmetric.
 * No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_rmult_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_rmult_sym_s(A,B) (gan_matf_rmult_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply two matrices and write result into a symmetric matrix.
 *
 * Multiply two matrices \a A, \a B, transposing \a B, and write result into
 * \f$ C = A B^{\top} \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_rmultT_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                         Gan_SquMatrix_f *C );
#else
#define gan_matf_rmultT_sym_q(A,B,C) (gan_matf_rmult_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply two matrices and return the result as a new symmetric matrix.
 *
 * Multiply two matrices \a A, \a B, transposing \a B, and return the
 * result as a new matrix \f$ A B^{\top} \f$. \a C is square and is \em assumed
 * to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_rmultT_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_rmultT_sym_s(A,B) (gan_matf_rmult_sym_gen(A,GAN_NOTRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply two matrices and write result into a symmetric matrix.
 *
 * Multiply two matrices \a A, \a B, transposing \a A, and write result into
 * \f$ C = A^{\top} B \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_rmult_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                         Gan_SquMatrix_f *C );
#else
#define gan_matTf_rmult_sym_q(A,B,C) (gan_matf_rmult_sym_gen(A,GAN_TRANSPOSE,B,GAN_NOTRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply two matrices and return the result as a new symmetric matrix.
 *
 * Multiply two matrices \a A, \a B, transposing \a A, and return the
 * result as a new matrix \f$ A^{\top} B \f$. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_rmult_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matTf_rmult_sym_s(A,B) (gan_matf_rmult_sym_gen(A,GAN_TRANSPOSE,B,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply two matrices and write result into a symmetric matrix.
 *
 * Multiply two matrices \a A, \a B, both transposed, and write result into
 * \f$ C = A^{\top} B^{\top} \f$, which is returned. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_rmultT_sym_q ( const Gan_Matrix_f *A, const Gan_Matrix_f *B,
                                          Gan_SquMatrix_f *C );
#else
#define gan_matTf_rmultT_sym_q(A,B,C) (gan_matf_rmult_sym_gen(A,GAN_TRANSPOSE,B,GAN_TRANSPOSE,C))
#endif

/**
 * \brief Macro: Multiply two matrices and return the result as a new symmetric matrix.
 *
 * Multiply two matrices \a A, \a B, both transposed, and return the result
 * as a new matrix \f$ A^{\top} B^{\top} \f$. \a C is square and is
 * \em assumed to be symmetric. No checking of this assumption is done.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matTf_rmultT_sym_s ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matTf_rmultT_sym_s(A,B) (gan_matf_rmult_sym_gen(A,GAN_TRANSPOSE,B,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply matrix by itself and write result into a symmetric matrix.
 *
 * Multiply matrix \a A by its own transpose, and write result into
 * square symmetric matrix \f$ B = A A^{\top} \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_srmultT_q ( const Gan_Matrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_matf_srmultT_q(A,B) (gan_matf_rmult_sym_gen(A,GAN_NOTRANSPOSE,A,GAN_TRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply matrix by itself and return the result as a new symmetric matrix.
 *
 * Multiply matrix \a A by its own transpose, and return the result as
 * a new square symmetric matrix \f$ A A^{\top} \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_srmultT_s ( const Gan_Matrix_f *A );
#else
#define gan_matf_srmultT_s(A) (gan_matf_rmult_sym_gen(A,GAN_NOTRANSPOSE,A,GAN_TRANSPOSE,NULL))
#endif

/**
 * \brief Macro: Multiply matrix by itself and write result into a symmetric matrix.
 *
 * Multiply transpose of matrix \a A by \a A, and write result into
 * square symmetric matrix \f$ B = A^{\top} A \f$, which is returned.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_slmultT_q ( const Gan_Matrix_f *A, Gan_SquMatrix_f *B );
#else
#define gan_matf_slmultT_q(A,B) (gan_matf_rmult_sym_gen(A,GAN_TRANSPOSE,A,GAN_NOTRANSPOSE,B))
#endif

/**
 * \brief Macro: Multiply matrix by itself and return the result as a new symmetric matrix.
 *
 * Multiply transpose of matrix \a A by \a A, and return the result as
 * a new square symmetric matrix \f$ A^{\top} A \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix_f *gan_matf_slmultT_s ( const Gan_Matrix_f *A );
#else
#define gan_matf_slmultT_s(A) (gan_matf_rmult_sym_gen(A,GAN_TRANSPOSE,A,GAN_NOTRANSPOSE,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixInvert
 * \{
 */

/**
 * \brief Macro: Inverts general square matrix
 * \param A Input Matrix
 * \return Non-\c NULL A pointer to the output inverse matrix, or
 *         \c NULL on failure.
 *
 * Inverts general square matrix \a A. This is a nasty operation and should be
 * avoided at all costs.
 *
 * Implemented as a macro call to gan_matf_invert_q().
 *
 * \sa gan_matf_invert_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_invert_s ( const Gan_Matrix_f *A ) /* input matrix */;
#else
#define gan_matf_invert_s(A) gan_matf_invert_q(A,NULL)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixTest
 * \{
 */

/**
 * \brief Macro: Checks that two matrices have the same number of rows and columns.
 *
 * Checks that two matrices have the same number of rows and columns.
 *
 * Returns #GAN_TRUE if \a A and \a B have the same dimensions, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
   GANDALF_API Gan_Bool gan_matf_same_dims ( const Gan_Matrix_f *A, const Gan_Matrix_f *B );
#else
#define gan_matf_same_dims(A,B) ((A)->rows == (B)->rows && (A)->cols == (B)->cols)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixInsert
 * \{
 */

/**
 * \brief Macro: Insert part of generic matrix in another generic matrix.
 *
 * Fills a rectangular part of generic matrix \a A starting at row,column
 * position \a rA,\a cA and \a rows by \a cols in size with the section
 * of generic matrix \a B, starting at position \a rB, \a cB.
 *
 * Macro call to gan_matf_insert_gen().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_insert ( Gan_Matrix_f *A,
                                unsigned long rA, unsigned long cA,
                                const Gan_Matrix_f *B,
                                unsigned long rB,   unsigned long cB,
                                unsigned long rows, unsigned long cols )
;
#else
#define gan_matf_insert(A,rA,cA,B,rB,cB,rows,cols) (gan_matf_insert_gen(A,rA,cA,B,GAN_NOTRANSPOSE,rB,cB,rows,cols))
#endif

/**
 * \brief Macro: Insert transpose of part of generic matrix in another generic matrix.
 *
 * Fills a rectangular part of generic matrix \a A starting at row,column
 * position \a rA,\a cA and \a rows by \a cols in size with the transpose
 * of section of generic matrix \a B, starting at position \a rB, \a cB.
 *
 * Macro call to gan_matf_insert_gen().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_insertT ( Gan_Matrix_f *A,
                                 unsigned long rA, unsigned long cA,
                                 const Gan_Matrix_f *B,
                                 unsigned long rB,   unsigned long cB,
                                 unsigned long rows, unsigned long cols );
#else
#define gan_matf_insertT(A,rA,cA,B,rB,cB,rows,cols) (gan_matf_insert_gen(A,rA,cA,B,GAN_TRANSPOSE,rB,cB,rows,cols))
#endif

/**
 * \brief Macro: Insert part of column vector in a generic matrix.
 *
 * Fills a section of a column of generic matrix \a A starting at
 * row,column position \a rA,\a cA with a section \a rows elements
 * in size, taken from column vector \a x, starting at position \a rx.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_insertv ( Gan_Matrix_f *A,
                                 unsigned long rA, unsigned long cA,
                                 const Gan_Vector_f *x, unsigned long rx,
                                 unsigned long rows );
#else
#define gan_matf_insertv(A,rA,cA,x,rx,rows) (gan_matf_insertv_gen(A,rA,cA,x,GAN_NOTRANSPOSE,rx,rows))
#endif

/**
 * \brief Macro: Insert part of row vector in a generic matrix.
 *
 * Fills a section of a row of generic matrix \a A starting at
 * row,column position \a rA,\a cA with a section \a cols elements
 * in size, taken from transpose of column vector \a x, starting at
 * position \a rx.
 *
 * Macro call to gan_matf_insertv_gen().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_insertvT ( Gan_Matrix_f *A,
                                  unsigned long rA, unsigned long cA,
                                  const Gan_Vector_f *x, unsigned long rx,
                                  unsigned long cols );
#else
#define gan_matf_insertvT(A,rA,cA,x,rx,cols) (gan_matf_insertv_gen(A,rA,cA,x,GAN_TRANSPOSE,rx,cols))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixTest
 * \{
 */

/**
 * \brief Macro: Test dimensions of generic matrix.
 *
 * Returns #GAN_TRUE if generic matrix \a A has dimensions \a rows by
 * \a cols, #GAN_FALSE otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_matf_test_dims ( const Gan_Matrix_f *A, unsigned long rows,
                                               unsigned long cols );
#else
#define gan_matf_test_dims(A,rs,cs) (((A)->rows==(rs))&&((A)->cols==(cs)))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixSize
 * \{
 */

/**
 * \brief Macro: Returns size of data array in bytes needed to hold matrix data.
 *
 * Returns size of data array in bytes needed to hold matrix data for
 * a matrix with given dimensions.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API size_t gan_matf_data_size ( unsigned long rows, unsigned long cols );
#else
#define gan_matf_data_size(rs,cs) ((rs)*(cs))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extracts rectangular part of matrix
 * \param A Input Matrix
 * \param r0 row offset of start of region to be extracted
 * \param c0 column offset of start of region to be extracted
 * \param rows Height of region to be extracted
 * \param cols Width of region to be extracted
 * \return Non-\c NULL Pointer to the output matrix, or \c NULL on failure.
 *
 * Extracts the given rectangular part of matrix \a A, copies it and returns
 * it as a new matrix.
 *
 * Implemented as a macro call to gan_matf_extract_q().
 * \sa gan_matf_extract_q(), gan_matf_insert().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_extract_s ( const Gan_Matrix_f *A,
                                   unsigned long r0,   unsigned long c0,
                                   unsigned long rows, unsigned long cols );
#else
#define gan_matf_extract_s(A,r0,c0,rs,cs) gan_matf_extract_q(A,r0,c0,rs,cs,NULL)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeMatrixIO
 * \{
 */

/**
 * \brief Macro: Read matrix from file
 *
 * Read matrix from file pointer \a fp. The prefix string for
 * the matrix is read from the file into the \a prefix string, up to the
 * maximum length \a prefix_len of the \a prefix string. Any remaining
 * characters after \a prefix has been filled are ignored. Pass \c NULL for
 * \a prefix and zero for \a prefix_len to ignore the prefix string.
 *
 * Returns #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * \sa gan_matf_fscanf_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_fscanf_s ( FILE *fp, const char *prefix,
                                  int prefix_len );
#else
#define gan_matf_fscanf_s(fp,p,pl) gan_matf_fscanf_q(fp,NULL,p,pl)
#endif

/**
 * \brief Macro: Read matrix from file
 *
 * Read matrix from file pointer \a fp in binary format. The magic number
 * for the matrix is read from the file into the provided pointer.
 *
 * Returns the read matrix on success, \c NULL on failure.
 *
 * \sa gan_matf_fread_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix_f *gan_matf_fread_s ( FILE *fp, gan_uint32 *magic_number );
#else
#define gan_matf_fread_s(fp,ml) gan_matf_fread_q(fp,NULL,m)
#endif

/**
 * \}
 */

#ifdef GAN_GENERATE_DOCUMENTATION
#undef Gan_SquMatrix_f
#endif

/* not user functions */
GANDALF_API Gan_Matrix_f *gan_matf_form_gen ( Gan_Matrix_f *A,
                                  unsigned long rows, unsigned long cols,
                                  float *data, size_t data_size );
GANDALF_API Gan_Bool gan_matf_realloc_gen ( Gan_Matrix_f *A,
                                unsigned long rows, unsigned long cols );
GANDALF_API Gan_Matrix_f *gan_matf_add_gen ( Gan_Matrix_f *A, Gan_TposeFlag A_tr,
                                 Gan_Matrix_f *B, Gan_TposeFlag B_tr,
                                 Gan_Matrix_f *C );
GANDALF_API struct Gan_SquMatrix_f *gan_matf_add_sym_gen (
    const Gan_Matrix_f *A, Gan_TposeFlag A_tr,
    const Gan_Matrix_f *B, Gan_TposeFlag B_tr,
    struct Gan_SquMatrix_f *C );
GANDALF_API Gan_Matrix_f *gan_matf_sub_gen ( Gan_Matrix_f *A, Gan_TposeFlag A_tr,
                                 Gan_Matrix_f *B, Gan_TposeFlag B_tr,
                                 Gan_Matrix_f *C );
GANDALF_API Gan_Vector_f *gan_matf_multv_gen ( const Gan_Matrix_f *A, Gan_TposeFlag A_tr,
                                   const Gan_Vector_f *x, Gan_Vector_f *y );
GANDALF_API Gan_Matrix_f *gan_matf_rmult_gen ( const Gan_Matrix_f *A, Gan_TposeFlag A_tr,
                                   const Gan_Matrix_f *B, Gan_TposeFlag B_tr,
                                   Gan_Matrix_f *C );
GANDALF_API struct Gan_SquMatrix_f *gan_matf_rmult_sym_gen (
    const Gan_Matrix_f *A, Gan_TposeFlag A_tr,
    const Gan_Matrix_f *B, Gan_TposeFlag B_tr,
    struct Gan_SquMatrix_f *C );
GANDALF_API Gan_Matrix_f *gan_matf_insert_gen ( Gan_Matrix_f *A,
                                    unsigned long rA, unsigned long cA,
                                    const Gan_Matrix_f *B, Gan_TposeFlag B_tr,
                                    unsigned long rB, unsigned long cB,
                                    unsigned long rows , unsigned long cols );
GANDALF_API Gan_Matrix_f *gan_matf_insertv_gen ( Gan_Matrix_f *A,
                                     unsigned long rA, unsigned long cA,
                                     const struct Gan_Vector_f *x,
                                     Gan_TposeFlag x_tr,
                                     unsigned long rx, unsigned long size );

#ifndef NDEBUG
GANDALF_API void gan_matf_db ( const Gan_Matrix_f *A ); /* for use in a debugger */
#endif

#define gan_matf_realloc(A,rows,cols) gan_matf_realloc_gen(A,rows,cols)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MATF_GEN_H */
