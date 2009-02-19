/**
 * File:          $RCSfile: vec_gen.h,v $
 * Module:        Generic column vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.27 $
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

#ifndef _GAN_VEC_GEN_H
#define _GAN_VEC_GEN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/common/misc_error.h>

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
 * \addtogroup GeneralSizeVector
 * \{
 */

#ifndef GAN_MATRIX_STRUCT_DEFINED
struct Gan_Matrix;
#endif

/// Structure definition for double precision general size vector
typedef struct Gan_Vector
{
   /* size of column vector */
   unsigned long rows;

   /* data array containing vector elements */
   double *data;

   /* allocated size of vector (number of double's) */
   size_t data_size;

   /* flag indicating whether vector data was dynamically allocated */
   Gan_Bool data_alloc;

   /* flag indicating whether vector structure was dynamically allocated */
   Gan_Bool struct_alloc;
} Gan_Vector;

#define GAN_VECTOR_STRUCT_DEFINED

#include <gandalf/linalg/mat_gen.h>
#include <gandalf/linalg/mat_square.h>

/* function declarations */
GANDALF_API Gan_Vector *gan_vec_form_gen ( Gan_Vector *x, unsigned long rows,
                               double *data, size_t data_size );
GANDALF_API void gan_vec_free ( Gan_Vector *x );
GANDALF_API Gan_Vector *gan_vec_set_size ( Gan_Vector *x, unsigned long rows );
GANDALF_API Gan_Vector *gan_vec_fill_va ( Gan_Vector *x, unsigned long rows, ... );
GANDALF_API Gan_Vector *gan_vec_fill_vap ( Gan_Vector *x, unsigned long rows,
                               va_list *aptr );
GANDALF_API Gan_Vector *gan_vec_fill_const_q ( Gan_Vector *x, unsigned long rows,
                                   double value );
GANDALF_API Gan_Bool gan_vec_read_va ( const Gan_Vector *x, unsigned long rows, ... );
GANDALF_API Gan_Vector *gan_vec_copy_q ( const Gan_Vector *x, Gan_Vector *y );
GANDALF_API Gan_Vector *gan_vec_scale_q ( Gan_Vector *x, double a, Gan_Vector *y );
GANDALF_API Gan_Vector *gan_vec_add_q ( Gan_Vector *x, Gan_Vector *y, Gan_Vector *z );
GANDALF_API Gan_Vector *gan_vec_sub_q ( Gan_Vector *x, Gan_Vector *y, Gan_Vector *z );
GANDALF_API double gan_vec_dot ( const Gan_Vector *x, const Gan_Vector *y );
GANDALF_API struct Gan_Matrix *gan_vec_outer_q ( const Gan_Vector *x, const Gan_Vector *y,
                                     struct Gan_Matrix *A );
GANDALF_API struct Gan_SquMatrix *gan_vec_outer_sym_q ( const Gan_Vector *x,
                                            struct Gan_SquMatrix *A );
GANDALF_API Gan_Vector *gan_vec_insert ( Gan_Vector *x, unsigned long rx,
                             const Gan_Vector *y, unsigned long ry,
                             unsigned long rows );
GANDALF_API void gan_vec_free_va ( Gan_Vector *x, ... );
GANDALF_API Gan_Vector *gan_vec_insert_mat ( Gan_Vector *x, unsigned long rx,
                                 const struct Gan_Matrix *A, unsigned long ra,
                                                             unsigned long ca,
                                 unsigned long rows );
GANDALF_API Gan_Vector *gan_vec_insert_matT ( Gan_Vector *x, unsigned long rx,
                                  const struct Gan_Matrix *A, unsigned long ra,
                                                              unsigned long ca,
                                  unsigned long rows );
GANDALF_API Gan_Bool gan_vec_fprint ( FILE *fp, const Gan_Vector *x, const char *prefix,
                          int indent, const char *fmt );
GANDALF_API Gan_Vector *gan_vec_fscanf_q ( FILE *fp, Gan_Vector *x,
                               char *prefix, int prefix_len );
GANDALF_API Gan_Bool gan_vec_fwrite ( FILE *fp, const Gan_Vector *x, gan_uint32 magic_number );
GANDALF_API Gan_Vector *gan_vec_fread_q ( FILE *fp, Gan_Vector *x,
                              gan_uint32 *magic_number );

#ifdef GAN_GENERATE_DOCUMENTATION
#define Gan_Matrix    struct Gan_Matrix
#define Gan_SquMatrix struct Gan_SquMatrix
#endif

/**
 * \addtogroup GeneralSizeVectorAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a generic vector.
 *
 * Allocates and returns a generic column vector with given size \a rows.
 *
 * Implemented as a macro call to gan_vec_form_gen().
 * \sa gan_vec_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_alloc ( unsigned long rows );
#else
#define gan_vec_alloc(rows) gan_vec_form_gen(NULL,rows,NULL,0)
#endif

/**
 * \brief Macro: Form and return a generic vector.
 *
 * Forms and returns a generic column vector with given number of rows.
 * If the \a x vector pointer is non-\c NULL, the given vector pointer
 * is filled; otherwise \a x is passed as \c NULL and the vector is
 * dynamically allocated.
 *
 * Implemented as a macro call to gan_vec_form_gen().
 * \sa gan_vec_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_form ( Gan_Vector *x, unsigned long rows );
#else
#define gan_vec_form(x,rows) gan_vec_form_gen(x,rows,NULL,0)
#endif

/**
 * \brief Macro: Form and return a generic vector.
 *
 * Forms and returns a generic column vector with given number of rows.
 * If the \a x vector pointer is non-\c NULL, the given vector pointer
 * is filled; otherwise \a x is passed as \c NULL and the vector is
 * dynamically allocated. Likewise if the provided \a data pointer is \c NULL,
 * the vector data is dynamically allocated. Otherwise, \a data_size is
 * the size of the \a data array in terms of \c double values.
 *
 * Implemented as a macro call to gan_vec_form_gen().
 *
 * \sa gan_vec_alloc() and gan_vec_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_form_data ( Gan_Vector *x, unsigned long rows,
                                void *data, size_t data_size );
#else
#define gan_vec_form_data(x,rows,data,data_size)\
           gan_vec_form_gen(x,rows,data,data_size)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorAccessElement
 * \{
 */

/**
 * \brief Macro: Set specific element of vector.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Set element \a i of generic vector to given value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_vec_set_el ( Gan_Vector *x, unsigned i, double value );
#else
#ifdef NDEBUG
#define gan_vec_set_el(x,i,v) ((x)->data[i] = (v),GAN_TRUE)
#else
#define gan_vec_set_el(x,i,v) ((unsigned)(i)>=(x)->rows \
                               ? (gan_err_flush_trace(),\
                                  gan_err_register("gan_vec_set_el",\
                                                   GAN_ERROR_TOO_LARGE,""),\
                                  GAN_FALSE)\
                               : ((x)->data[i] = (v),GAN_TRUE))
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Get specific element of vector.
 *
 * Macro to return element \a i of generic vector, or \c DBL_MAX on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_vec_get_el ( const Gan_Vector *x, unsigned i );
#else
#ifdef NDEBUG
#define gan_vec_get_el(x,i) (x)->data[i]
#else
#define gan_vec_get_el(x,i) ((unsigned)(i)>=(x)->rows \
                             ? (gan_err_flush_trace(),\
                                gan_err_register("gan_vec_get_el",\
                                                 GAN_ERROR_TOO_LARGE,""),\
                                DBL_MAX)\
                             : (x)->data[i])
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Increment specific element of vector by given value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Macro to increment element i of generic vector by given value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_vec_inc_el ( Gan_Vector *x, unsigned i, double value );
#else
#ifdef NDEBUG
#define gan_vec_inc_el(x,i,v) ((x)->data[i] += (v),GAN_TRUE)
#else
#define gan_vec_inc_el(x,i,v) ((unsigned)(i)>=(x)->rows \
                               ? (gan_err_flush_trace(),\
                                  gan_err_register("gan_vec_inc_el",\
                                                   GAN_ERROR_TOO_LARGE,""),\
                                  GAN_FALSE)\
                               : ((x)->data[i] += (v),GAN_TRUE))
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Decrement specific element of vector by given value.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Macro to decrement element i of generic vector by given value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_vec_dec_el ( Gan_Vector *x, unsigned i, double value );
#else
#ifdef NDEBUG
#define gan_vec_dec_el(x,i,v) ((x)->data[i] -= (v),GAN_TRUE)
#else
#define gan_vec_dec_el(x,i,v) ((unsigned)(i)>=(x)->rows \
                               ? (gan_err_flush_trace(),\
                                  gan_err_register("gan_vec_dec_el",\
                                                   GAN_ERROR_TOO_LARGE,""),\
                                  GAN_FALSE)\
                               : ((x)->data[i] -= (v),GAN_TRUE))
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorIO
 * \{
 */

/**
 * \brief Macro: Print vector to standard output.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Print vector \a x to standard output, with prefix string \a prefix,
 * indentation \a indent and floating-point format \a fmt.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_vec_print ( const Gan_Vector *x,
                         const char *prefix, int indent, const char *fmt );
#else
#define gan_vec_print(x,p,i,f) (gan_vec_fprint(stdout,x,p,i,f))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorFill
 * \{
 */

/**
 * \brief Macro: Allocate and fill all elements of a vector with the same value
 * \param rows The new size of the vector
 * \param value The value to set each element of the vector to
 * \return Allocated and filled vector or \c NULL on failure
 *
 * Allocate a vector, set its size to \a rows, and fill each element with the
 * provided \a value.
 * \sa gan_vec_fill_const_q().
 *
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_fill_const_s ( unsigned long rows, double value );
#else
#define gan_vec_fill_const_s(r,v) gan_vec_fill_const_q(NULL,r,v)
#endif

/**
 * \brief Macro: Fill vector with zeros.
 * \param x The vector to be filled
 * \param rows The new size of the vector
 * \return Pointer to filled vector, or \c NULL on failure.
 *
 * Set the size of vector \a x to \a rows, and fill it with zeros.
 * \sa gan_vec_fill_zero_s().
 *
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_fill_zero_q ( Gan_Vector *x, unsigned long rows );
#else
#define gan_vec_fill_zero_q(x,r) gan_vec_fill_const_q(x,r,0.0)
#endif

/**
 * \brief Macro: Allocate and fill vector with zeros.
 * \param rows The new size of the vector
 * \return The allocated and filled vector, or \c NULL on failure.
 *
 * Allocate a vector, set the size of it to \a rows and fill it with zeros.
 * \sa gan_vec_fill_zero_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_fill_zero_s ( unsigned long rows );
#else
#define gan_vec_fill_zero_s(r) gan_vec_fill_const_s(r,0.0)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorCopy
 * \{
 */

/**
 * \brief Macro: Copy vector.
 *
 * Allocate and return a copy of vector \a x.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_copy_s ( const Gan_Vector *x );
#else
#define gan_vec_copy_s(x) (gan_vec_copy_q((x),NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorScale
 * \{
 */

/**
 * \brief Macro: Multiply vector by scalar.
 *
 * Allocate and return a copy of vector \a x multiplied by scalar \a a.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_scale_s ( Gan_Vector *x, double a );
#else
#define gan_vec_scale_s(x,a) (gan_vec_scale_q(x,a,NULL))
#endif

/**
 * \brief Macro: Multiply vector by scalar.
 * \return Scaled vector \a x.
 *
 * Multiply vector \a x by scalar \a a in-place: \f$ x \leftarrow a x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_scale_i ( Gan_Vector *x, double a );
#else
#define gan_vec_scale_i(x,a) (gan_vec_scale_q(x,a,x))
#endif

/**
 * \brief Macro: Divide vector by scalar.
 * \return Result vector \a y.
 *
 * Divide vector \a x by scalar \a a, writing result into vector
 * \f$ y = \frac{1}{a} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_divide_q ( Gan_Vector *x, double a, Gan_Vector *y );
#else
#define gan_vec_divide_q(x,a,y) (gan_vec_scale_q(x,1.0/(a),y))
#endif

/**
 * \brief Macro: Divide vector by scalar.
 *
 * Allocate and return a copy of vector \a x divided by scalar \a a.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_divide_s ( Gan_Vector *x, double a );
#else
#define gan_vec_divide_s(x,a) (gan_vec_scale_q(x,1.0/(a),NULL))
#endif

/**
 * \brief Macro: Divide vector by scalar.
 *
 * Divide vector \a x by scalar \a a in-place:
 * \f$ x \leftarrow \frac{1}{a} x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_divide_i ( Gan_Vector *x, double a );
#else
#define gan_vec_divide_i(x,a) (gan_vec_scale_q(x,1.0/(a),x))
#endif

/**
 * \brief Macro: Negate vector.
 *
 * Negate vector \a x into vector \f$ y = -x \f$, and return \a y.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_negate_q ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_negate_q(x,y) (gan_vec_scale_q(x,-1.0,y))
#endif

/**
 * \brief Macro: Negate vector.
 *
 * Allocate and return a negated copy \f$ -x \f$ of vector \a x.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_negate_s ( Gan_Vector *x );
#else
#define gan_vec_negate_s(x) (gan_vec_scale_q(x,-1.0,NULL))
#endif

/**
 * \brief Macro: Negate vector.
 *
 * Negate vector \a x in-place: \f$ x \leftarrow -x \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_negate_i ( Gan_Vector *x );
#else
#define gan_vec_negate_i(x) (gan_vec_scale_q(x,-1.0,x))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorAdd
 * \{
 */

/**
 * \brief Macro: Add two vectors.
 * \return Result as a new vector.
 *
 * Add two vectors \a x, \a y and return the result as a new vector
 * \f$ x + y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_add_s ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_add_s(x,y) (gan_vec_add_q((x),(y),NULL))
#endif

/**
 * \brief Macro: Add two vectors and overwrite the first with the result.
 * \return Result vector \a x.
 *
 * Add two vectors \a x, \a y and overwrite \a x with the result:
 * \f$ x \leftarrow x + y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_add_i1 ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_add_i1(x,y) (gan_vec_add_q((x),(y),(x)))
#endif

/**
 * \brief Macro: Add two vectors and overwrite the second with the result.
 * \return Result vector \a y.
 *
 * Add two vectors \a x, \a y and overwrite \a y with the result:
 * \f$ y \leftarrow x + y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_add_i2 ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_add_i2(x,y) (gan_vec_add_q((x),(y),(y)))
#endif

/**
 * \brief Macro: Increment a vector with another vector.
 * \return Result vector x.
 *
 * Increment vector \a x with vector \a y: \f$ x \leftarrow x + y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_increment ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_increment(x,y) (gan_vec_add_q((x),(y),(x)))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorSubtract
 * \{
 */

/**
 * \brief Macro: Subtract two vectors.
 * \return The result as a new vector.
 *
 * Subtract two vectors \a x, \a y and return the result as a new vector
 * \f$ x - y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_sub_s ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_sub_s(x,y) (gan_vec_sub_q((x),(y),NULL))
#endif

/**
 * \brief Macro: Subtract two vectors and overwrite the first with the result.
 * \return Result vector \a x.
 *
 * Subtract two vectors \a x, \a y and overwrite \a x with the result:
 * \f$ x \leftarrow x - y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_sub_i1 ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_sub_i1(x,y) (gan_vec_sub_q((x),(y),(x)))
#endif

/**
 * \brief Macro: Subtract two vectors and overwrite the second with the result.
 * \return Result vector \a y.
 *
 * Subtract two vectors \a x, \a y and overwrite \a y with the result:
 * \f$ y \leftarrow x - y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_sub_i2 ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_sub_i2(x,y) (gan_vec_sub_q((x),(y),(y)))
#endif

/**
 * \brief Macro: Decrement a vector with another vector.
 * \return Result vector x.
 *
 * Decrement vector \a x with vector \a y: \f$ x \leftarrow x - y \f$.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_decrement ( Gan_Vector *x, Gan_Vector *y );
#else
#define gan_vec_decrement(x,y) (gan_vec_sub_q((x),(y),(x)))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorOuterProduct
 * \{
 */

/**
 * \brief Macro: vector outer product
 * \return Result as a new matrix.
 *
 * Compute outer product \f$ x y^{\top} \f$ of vectors \a x and \a y.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix *gan_vec_outer_s ( const Gan_Vector *x, const Gan_Vector *y );
#else
#define gan_vec_outer_s(x,y) gan_vec_outer_q(x,y,NULL)
#endif

/**
 * \brief Macro: vector outer product with self
 * \return Result as a new symmetric matrix.
 *
 * Compute symmetric outer product \f$ x x^{\top} \f$ of vector \a x with
 * itself.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix *gan_vec_outer_sym_s ( const Gan_Vector *x );
#else
#define gan_vec_outer_sym_s(x) gan_vec_outer_sym_q(x,NULL)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorNorms
 * \{
 */

/**
 * \brief Macro: Vector squared length.
 *
 * Returns the scalar product \f$ ||x||^2 \f$ of vector \a x with itself,
 * i.e. the squared length of \a x.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_vec_sqrlen ( const Gan_Vector *x );
#else
#define gan_vec_sqrlen(x) (gan_vec_dot(x,x))
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorTest
 * \{
 */

/**
 * \brief Macro: Checks that two vectors have the same number of rows.
 *
 * Checks that two vectors have the same number of rows.
 *
 * \return #GAN_TRUE if \a x and \a y have the same size, #GAN_FALSE
 *         otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_vec_same_size ( const Gan_Vector *x, const Gan_Vector *y );
#else
#define gan_vec_same_size(x,y) ((x)->rows == (y)->rows)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorSize
 * \{
 */

/**
 * \brief Macro: Returns size of data array in bytes needed to hold vector data.
 *
 * Returns the size of data array in bytes needed to hold vector data for
 * a vector with given size.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API size_t gan_vec_data_size ( unsigned long rows );
#else
#define gan_vec_data_size(rs) (rs)
#endif

/**
 * \}
 */

/**
 * \addtogroup GeneralSizeVectorIO
 * \{
 */

/**
 * \brief Macro: Read vector from file.
 *
 * Read vector from file pointer \a fp. The prefix string for
 * the vector is read from the file into the \a prefix string, up to the
 * maximum length \a prefix_len of the \a prefix string. Any remaining
 * characters after \a prefix has been filled are ignored. Pass \c NULL for
 * \a prefix and zero for \a prefix_len to ignore the prefix string.
 *
 * \return The read vector on success, \c NULL on failure.
 * \sa gan_vec_fscanf_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_fscanf_s ( FILE *fp, const char *prefix, int prefix_len );
#else
#define gan_vec_fscanf_s(fp,p,pl) gan_vec_fscanf_q(fp,NULL,p,pl)
#endif

/**
 * \brief Macro: Read vector from file in binary format.
 *
 * Read vector from file pointer \a fp in binary format. The magic number
 * for the vector is read from the file into the provided pointer.
 *
 * \return The read vector on success, \c NULL on failure.
 * \sa gan_vec_fread_q()
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector *gan_vec_fread_s ( FILE *fp, gan_uint32 *magic_number );
#else
#define gan_vec_fread_s(fp,ml) gan_vec_fread_q(fp,NULL,m)
#endif

/**
 * \}
 */

#ifdef GAN_GENERATE_DOCUMENTATION
#undef Gan_Matrix
#undef Gan_SquMatrix
#endif

/* not user functions */
GANDALF_API Gan_Bool gan_vec_realloc ( Gan_Vector *x, unsigned long rows );
#ifndef NDEBUG
GANDALF_API void gan_vec_db ( const Gan_Vector *x ); /* for use in a debugger */
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

#endif /* #ifndef _GAN_VEC_GEN_H */
