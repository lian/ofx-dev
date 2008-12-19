/**
 * File:          $RCSfile: matrixf_noc.h,v $
 * Module:        Fixed size matrix functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.23 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * Notes:         Not to be compiled separately
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

/* function declarations for functions common to all small vector types */

#ifndef GAN_GENERATE_DOCUMENTATION

#ifdef GAN_MAT_FPRINT
GANDALF_API Gan_Bool GAN_MAT_FPRINT ( FILE *fp, const GAN_MATTYPE *A, const char *prefix,
                          int indent, const char *fmt );
#endif

#ifdef GAN_MAT_PRINT
GANDALF_API Gan_Bool GAN_MAT_PRINT ( const GAN_MATTYPE *A, const char *prefix,
                         int indent, const char *fmt );
#endif

#ifdef GAN_MAT_FSCANF
GANDALF_API Gan_Bool GAN_MAT_FSCANF ( FILE *fp, GAN_MATTYPE *A,
                          char *prefix, int prefix_len );
#endif

#ifdef GAN_MAT_FWRITE
GANDALF_API Gan_Bool GAN_MAT_FWRITE ( FILE *fp, const GAN_MATTYPE *A, gan_uint32 magic_number );
#endif

#ifdef GAN_MAT_FREAD
GANDALF_API Gan_Bool GAN_MAT_FREAD ( FILE *fp, GAN_MATTYPE *A, gan_uint32 *magic_number );
#endif

#ifdef GAN_MAT_ZERO_S
GANDALF_API GAN_MATTYPE GAN_MAT_ZERO_S (void);
#endif

#ifdef GAN_MAT_COPY_S
GANDALF_API GAN_MATTYPE GAN_MAT_COPY_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_SCALE_S
GANDALF_API GAN_MATTYPE GAN_MAT_SCALE_S ( const GAN_MATTYPE *A, GAN_REALTYPE a );
#endif

#ifdef GAN_MAT_DIVIDE_S
GANDALF_API GAN_MATTYPE GAN_MAT_DIVIDE_S ( const GAN_MATTYPE *A, GAN_REALTYPE a );
#endif

#ifdef GAN_MAT_NEGATE_S
GANDALF_API GAN_MATTYPE GAN_MAT_NEGATE_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_UNIT_Q
GANDALF_API GAN_MATTYPE *GAN_MAT_UNIT_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_UNIT_S
GANDALF_API GAN_MATTYPE GAN_MAT_UNIT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_ADD_S
GANDALF_API GAN_MATTYPE GAN_MAT_ADD_S ( const GAN_MATTYPE *A, const GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_SUB_S
GANDALF_API GAN_MATTYPE GAN_MAT_SUB_S ( const GAN_MATTYPE *A, const GAN_MATTYPE *B );
#endif

#ifdef GAN_VEC_OUTER_S
GANDALF_API GAN_MATTYPE GAN_VEC_OUTER_S ( const GAN_VECTYPE1 *p, const GAN_VECTYPE2 *q );
#endif

#ifdef GAN_MAT_MULTV_S
GANDALF_API GAN_VECTYPE1 GAN_MAT_MULTV_S ( const GAN_MATTYPE *A, const GAN_VECTYPE2 *p );
#endif

#ifdef GAN_MATT_MULTV_S
GANDALF_API GAN_VECTYPE2 GAN_MATT_MULTV_S ( const GAN_MATTYPE *A, const GAN_VECTYPE1 *p );
#endif

#ifdef GAN_MAT_LMULTM_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTM_S ( const GAN_MATTYPE *A, const GAN_MATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTMT_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTMT_S ( const GAN_MATTYPE *A, const GAN_MATTYPEL *B );
#endif

#ifdef GAN_MAT_RMULTM_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTM_S ( const GAN_MATTYPE *A, const GAN_MATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTMT_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTMT_S ( const GAN_MATTYPE *A, const GAN_MATTYPER *B );
#endif

#ifdef GAN_MAT_LMULTMT_SYM_S
GANDALF_API GAN_SQUMATTYPER GAN_MAT_LMULTMT_SYM_S ( const GAN_MATTYPE *A, const GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_RMULTMT_SYM_S
GANDALF_API GAN_SQUMATTYPEL GAN_MAT_RMULTMT_SYM_S ( const GAN_MATTYPE *A, const GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_SRMULTT_S
GANDALF_API GAN_SQUMATTYPEL GAN_MAT_SRMULTT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_SLMULTT_S
GANDALF_API GAN_SQUMATTYPER GAN_MAT_SLMULTT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_LMULTS_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTS_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_RMULTS_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTS_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_SYMMATL_LRMULT_S
GANDALF_API GAN_SQUMATTYPER GAN_SYMMATL_LRMULT_S ( const GAN_SQUMATTYPEL *A, const GAN_MATTYPE *B,
                                       GAN_MATTYPE *C );
#endif

#ifdef GAN_SYMMATR_LRMULT_S
GANDALF_API GAN_SQUMATTYPEL GAN_SYMMATR_LRMULT_S ( const GAN_SQUMATTYPER *A, const GAN_MATTYPE *B,
                                       GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTL_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTL_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTLI_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTLI_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTLT_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTLT_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTLIT_S
GANDALF_API GAN_MATTYPE GAN_MAT_LMULTLIT_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_RMULTL_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTL_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTLI_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTLI_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTLT_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTLT_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTLIT_S
GANDALF_API GAN_MATTYPE GAN_MAT_RMULTLIT_S ( const GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_SUMSQR_S
GANDALF_API GAN_REALTYPE GAN_MAT_SUMSQR_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_FNORM_S
GANDALF_API GAN_REALTYPE GAN_MAT_FNORM_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_FROM_MAT_S
GANDALF_API GAN_MATTYPE GAN_MAT_FROM_MAT_S ( const GAN_MATRIX_TYPE *A );
#endif

#ifdef GAN_MAT_FROM_SQUMAT_S
GANDALF_API GAN_MATTYPE GAN_MAT_FROM_SQUMAT_S ( const GAN_SQUMATRIX_TYPE *A );
#endif

#ifdef GAN_SQUMAT_FROM_SQUMAT_S
GANDALF_API GAN_SQUMATTYPEL GAN_SQUMAT_FROM_SQUMAT_S ( const GAN_SQUMATRIX_TYPE *A );
#endif

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#ifdef GAN_GENERATE_DOCUMENTATION

/* documentation for macros defined in individual header files */

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

#ifdef GAN_MAT_ZERO_Q
/**
 * \brief Macro: Fill fixed size matrix with zero.
 *
 * Fill fixed size matrix \a A with zero, and return \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_ZERO_Q ( const GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixCopy
 * \{
 */

#ifdef GAN_MAT_COPY_Q
/**
 * \brief Macro: Copy fixed size matrix.
 *
 * Copy fixed size matrix \a A to fixed matrix \a B.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_COPY_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixScale
 * \{
 */

#ifdef GAN_MAT_SCALE_Q
/**
 * \brief Macro: Scale fixed size matrix.
 *
 * Multiply fixed size matrix \a A by scalar \a a, writing result into fixed
 * size matrix \a B.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SCALE_Q ( GAN_MATTYPE *A, GAN_REALTYPE a,
                               GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_SCALE_I
/**
 * \brief Macro: Scale fixed size matrix.
 *
 * Multiply fixed size matrix \a A by scalar \a a in-place.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SCALE_I ( GAN_MATTYPE *A, GAN_REALTYPE a );
#endif

#ifdef GAN_MAT_DIVIDE_Q
/**
 * \brief Macro: Divide fixed size matrix by scalar.
 *
 * Divide fixed size matrix \a A by scalar \a a, writing result into fixed
 * size matrix \a B.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_DIVIDE_Q ( GAN_MATTYPE *A, GAN_REALTYPE a,
                                GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_DIVIDE_I
/**
 * \brief Macro: Divide fixed size matrix by scalar.
 *
 * Divide fixed size matrix \a A by scalar \a a in-place.
 *
 * \return Pointer to result matrix  \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_DIVIDE_I ( GAN_MATTYPE *A, GAN_REALTYPE a );
#endif

#ifdef GAN_MAT_NEGATE_Q
/**
 * \brief Macro: Negate fixed size matrix.
 *
 * Negate fixed size matrix \a A into fixed size matrix \f$ B = -A \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_NEGATE_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_NEGATE_I
/**
 * \brief Macro: Negate fixed size matrix.
 *
 * Negate fixed size matrix \a A in-place: \f$ A \leftarrow -A \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_NEGATE_I ( GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_UNIT_I
/**
 * \brief Macro: Scale matrix to unit norm.
 *
 * Scale fixed-size matrix \a A to unit Frobenius norm in-place.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_UNIT_I ( GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixAdd
 * \{
 */

#ifdef GAN_MAT_ADD_Q
/**
 * \brief Macro: Add two fixed size matrices.
 *
 * Add two fixed matrices \a A, \a B and write result into
 * \f$ C = A + B \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_ADD_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B, GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_ADD_I1
/**
 * \brief Macro: Add two fixed size matrices.
 *
 * Add two fixed matrices \a A, \a B and overwrite \a A with the result:
 * \f$ A \leftarrow A + B \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_ADD_I1 ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_ADD_I2
/**
 * \brief Macro: Add two fixed size matrices.
 *
 * Add two fixed matrices \a A, \a B and overwrite \a B with the result:
 * \f$ B \leftarrow A + B \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_ADD_I2 ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_INCREMENT
/**
 * \brief Macro: Increment a fixed size vector by another.
 *
 * Increment fixed size matrix \a A by fixed size matrix \a B, overwriting
 * \a A with the result: \f$ A \leftarrow A + B \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_INCREMENT ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixSubtract
 * \{
 */

#ifdef GAN_MAT_SUB_Q
/**
 * \brief Macro: Subtract two fixed size matrices.
 *
 * Subtract two fixed matrices \a A, \a B and write result into
 * \f$ C = A - B \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SUB_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B, GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_SUB_I1
/**
 * \brief Macro: Subtract two fixed size matrices.
 *
 * Subtract two fixed size matrices \a A, \a B and overwrite \a A with the
 * result: \f$ A \leftarrow A - B \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SUB_I1 ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_SUB_I2
/**
 * \brief Macro: Subtract two fixed size matrices.
 *
 * Subtract two fixed size matrices \a A, \a B and overwrite \a B with the
 * result: \f$ B \leftarrow A - B \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SUB_I2 ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_DECREMENT
/**
 * \brief Macro: Decrement a fixed size vector by another.
 *
 * Decrement fixed size matrix \a A by fixed size matrix \a B, overwriting
 * \a A with the result: \f$ A \leftarrow A - B \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_DECREMENT ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

#ifdef GAN_VEC_OUTER_Q
/**
 * \brief Macro: Compute the outer product of two fixed size vectors.
 *
 * Computes outer product of vectors \a p & \a q, writing the result into
 * matrix \f$ A = p q^{\top} \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_VEC_OUTER_Q ( const GAN_VECTYPE1 *p, const GAN_VECTYPE2 *q,
                               GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_MULTV_Q
/**
 * \brief Macro: Matrix/vector product.
 *
 * Computes the product of a matrix \a A and a vector \a p, writing the
 * result into vector \f$ q = A p \f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE1 *GAN_MAT_MULTV_Q ( const GAN_MATTYPE *A, GAN_VECTYPE2 *p,
                                GAN_VECTYPE1 *q );
#endif

#ifdef GAN_MAT_MULTV_I
/**
 * \brief Macro: Matrix/vector product.
 *
 * Computes the product of a matrix \a A, and a vector \a p, writing the
 * result in-place into \f$ p \leftarrow A p \f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE1 *GAN_MAT_MULTV_I ( const GAN_MATTYPE *A, GAN_VECTYPE2 *p );
#endif

#ifdef GAN_MATT_MULTV_Q
/**
 * \brief Macro: Matrix/vector product with the matrix transposed.
 *
 * Computes the product of the transpose of a matrix \a A and a vector \a p,
 * writing the result into vector \f$ q = A^{\top} p \f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE2 *GAN_MATT_MULTV_Q ( const GAN_MATTYPE *A, GAN_VECTYPE1 *p,
                                 GAN_VECTYPE2 *q );
#endif

#ifdef GAN_MATT_MULTV_I
/**
 * \brief Macro: Matrix/vector product with the matrix transposed.
 *
 * Computes the product of the transpose of a matrix \a A and a vector \a p,
 * writing the result in-place into \f$ p = A^{\top} p \f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE2 *GAN_MATT_MULTV_I ( const GAN_MATTYPE *A, GAN_VECTYPE1 *p );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixMatrixProduct
 * \{
 */

#ifdef GAN_MAT_LMULTM_Q
/**
 * \brief Macro: Left-multiply a matrix by another matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with another matrix
 * \a B, writing the result into matrix \f$ C = B A \f$.
 * \a B is square but of generic type #GAN_MATTYPEL.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTM_Q ( GAN_MATTYPE *A, const GAN_MATTYPEL *B,
                                GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTMT_Q
/**
 * \brief Macro: Left-multiply a matrix by the transpose of another matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the transpose of
 * a square matrix \a B of generic type #GAN_MATTYPEL, writing the result into
 * another matrix \f$ C = B^{\top} A \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTMT_Q ( GAN_MATTYPE *A, const GAN_MATTYPEL *B,
                                 GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTM_Q
/**
 * \brief Macro: Right-multiply a matrix by another matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with a square matrix
 * \a B of generic type #GAN_MATTYPER, writing the result into another matrix
 * \f$ C = A B \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTM_Q ( GAN_MATTYPE *A, const GAN_MATTYPER *B,
                                GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTMT_Q
/**
 * \brief Macro: Right-multiply a matrix by the transpose of another matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with the transpose of
 * a square matrix \a B of generic type #GAN_MATTYPER, writing the result into
 * another matrix \f$ C = A B^{\top} \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTMT_Q ( GAN_MATTYPE *A, const GAN_MATTYPER *B,
                                 GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTMT_SYM_Q
/**
 * \brief Macro: Matrix product producing a symmetric matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the transpose of
 * a matrix \a B of the same type type, producing a symmetric matrix
 * \f$ C = B^{\top} A \f$.
 * Note that the result is \em assumed to be symmetric, so this
 * routine should be used with care.
 *
 * \return Pointer to result symmetric matrix \a C.
 */
GANDALF_API GAN_SQUMATTYPER *GAN_MAT_LMULTMT_SYM_Q ( const GAN_MATTYPE *A, const GAN_MATTYPE *B,
                                         GAN_SQUMATTYPER *C );
#endif

#ifdef GAN_MAT_RMULTMT_SYM_Q
/**
 * \brief Macro: Matrix product producing a symmetric matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with the transpose of
 * a matrix \a B of the same type type, producing a symmetric matrix
 * \f$ C = A B^{\top} \f$.
 * Note that the result is \em assumed to be symmetric, so this
 * routine should be used with care.
 *
 * \return Pointer to result symmetric matrix \a C.
 */
GANDALF_API GAN_SQUMATTYPEL *GAN_MAT_RMULTMT_SYM_Q ( const GAN_MATTYPE *A, const GAN_MATTYPE *B,
                                         GAN_SQUMATTYPEL *C );
#endif

#ifdef GAN_MAT_LMULTS_Q
/**
 * \brief Macro: Left-multiply a matrix by a symmetric matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with a symmetric
 * matrix \a B, writing the result into another matrix \f$ C = B A \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTS_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B,
                                GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTS_Q
/**
 * \brief Macro: Right-multiply a matrix by a symmetric matrix.
 *
 * Returns the result of right-multiplying a matrix \a A with a symmetric
 * matrix \a B, writing the result into another matrix \f$ C = A B \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTS_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B,
                                GAN_MATTYPE *C );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeTripleMatrixProduct
 * \{
 */

#ifdef GAN_SYMMATL_LRMULT_Q
/**
 * \brief Macro: Matrix triple product involving symmetric matrices.
 *
 * Computes the triple product \f$ B^{\top} A B \f$ as a symmetric matrix,
 * for generic matrix \a B and symmetric matrix \a A, writing the result
 * into symmetric matrix \a D. The intermediate result
 * \f$ A B \f$ is written into matrix \a C.
 *
 * \return Pointer to result symmetric matrix \a D.
 */
GANDALF_API GAN_SQUMATTYPER *GAN_SYMMATL_LRMULT_Q ( const GAN_SQUMATTYPEL *A, const GAN_MATTYPE *B,
                                        const GAN_MATTYPE *C, GAN_SQUMATTYPER *D );
#endif

#ifdef  GAN_SYMMATR_LRMULT_Q
/**
 * \brief Macro: Matrix triple product involving symmetric matrices.
 *
 * Computes the triple product \f$ B A B^{\top} \f$ as symmetric matrix,
 * for generic matrix \a B and symmetric matrix \a A, writing the result
 * into symmetric matrix \a D.
 * The intermediate result \f$ B A \f$ is written into matrix \a C.
 *
 * \return Pointer to result symmetric matrix \a D.
 */
GANDALF_API GAN_SQUMATTYPEL *GAN_SYMMATR_LRMULT_Q ( const GAN_SQUMATTYPER *A, const GAN_MATTYPE *B,
                                        const GAN_MATTYPE *C, GAN_SQUMATTYPEL *D );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixMatrixProduct
 * \{
 */

#ifdef GAN_MAT_LMULTL_Q
/**
 * \brief Macro: Left-multiply a matrix by a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with a
 * lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = B A \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTL_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B,
                                GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTLI_Q
/**
 * \brief Macro: Left-multiply a matrix by the inverse of a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the inverse of
 * a lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = B^{-1} A \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTLI_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B,
                                 GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTLT_Q
/**
 * \brief Macro: Left-multiply a matrix by the transpose of a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the transpose of
 * a lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = B^{\top} A \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTLT_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B,
                                 GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTLIT_Q
/**
 * \brief Macro: Left-multiply a matrix by the inverse transpose of a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the inverse
 * transpose of a lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = B^{-{\top}} A \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTLIT_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B,
                                  GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTL_Q
/**
 * \brief Macro: Right-multiply a matrix by a lower-triangular matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with a
 * lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = A B \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTL_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B,
                                GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTLI_Q
/**
 * \brief Macro: Right-multiply a matrix by the inverse of a lower-triangular matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with the inverse of
 * a lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = A B^{-1} \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTLI_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B,
                                 GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTLT_Q
/**
 * \brief Macro: Right-multiply a matrix by the transpose of a lower-triangular matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with the transpose of
 * a lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = A B^{\top} \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTLT_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B,
                                 GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_RMULTLIT_Q
/**
 * \brief Macro: Right-multiply a matrix by the inverse transpose of a lower-triangular matrix
 *
 * Computes the result of right-multiplying a matrix \a A with the inverse
 * transpose of a lower-triangular matrix \a B, writing the result into matrix
 * \f$ C = A B^{-{\top}} \f$.
 *
 * \return Pointer to result matrix \a C.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTLIT_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B,
                                  GAN_MATTYPE *C );
#endif

#ifdef GAN_MAT_LMULTL_I
/**
 * \brief Macro: Left-multiply a matrix by a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with a
 * lower-triangular matrix \a B, writing the result in-place into
 * \f$ A \leftarrow B A \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTL_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTLI_I
/**
 * \brief Macro: Left-multiply a matrix by the inverse of a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the inverse of
 * a lower-triangular matrix \a B, writing the result in-place into
 * \f$ A \leftarrow B^{-1} A \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTLI_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTLT_I
/**
 * \brief Macro: Left-multiply a matrix by the transpose of a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the transpose of
 * a lower-triangular matrix \a B, writing the result in-place into
 $ \f$ A \leftarrow B^{\top} A \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTLT_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_LMULTLIT_I
/**
 * \brief Macro: Left-multiply a matrix by the inverse transpose of a lower-triangular matrix.
 *
 * Computes the result of left-multiplying a matrix \a A with the inverse
 * transpose of a lower-triangular matrix \a B, writing the result in-place
 * into \f$ A \leftarrow B^{-{\top}} A \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_LMULTLIT_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_RMULTL_I
/**
 * \brief Macro: Right-multiply a matrix by a lower-triangular matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with a
 * lower-triangular matrix in-place \a B, writing the result in-place
 * into \f$ A \leftarrow A B \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTL_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTLI_I
/**
 * \brief Macro: Right-multiply a matrix by the inverse of a lower-triangular matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with the inverse of
 * a lower-triangular matrix \a B, writing the result in-place into
 * \f$ A \leftarrow A B^{-1} \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTLI_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTLT_I
/**
 * \brief Macro: Right-multiply a matrix by the transpose of a lower-triangular matrix.
 *
 * Computes the result of right-multiplying a matrix \a A with the transpose of
 * a lower-triangular matrix \a B, writing the result in-place into
 * \f$ A \leftarrow A B^{\top} \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTLT_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_RMULTLIT_I
/**
 * \brief Macro: Right-multiply a matrix by the inverse transpose of a lower-triangular matrix
 *
 * Computes the result of right-multiplying a matrix \a A with the inverse
 * transpose of a lower-triangular matrix \a B, writing the result in-place
 * into \f$ A \leftarrow A B^{-{\top}} \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_RMULTLIT_I ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_SLMULTT_Q
/**
 * \brief Macro: Left-multiply a matrix by its own transpose, producing a symmetric matrix.
 *
 * Left multiply a fixed-size matrix \a A by its own transpose, producing
 * a symmetric fixed-size matrix \f$ B = A^{\top} A \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_SQUMATTYPER *GAN_MAT_SLMULTT_Q ( GAN_MATTYPE *A, const GAN_SQUMATTYPER *B );
#endif

#ifdef GAN_MAT_SLMULTT_I
/**
 * \brief Macro: Left-multiply a matrix by its own transpose, producing a symmetric matrix.
 *
 * Left multiply a fixed-size matrix \a A by its own transpose, producing
 * a symmetric fixed-size matrix which is overwritten on
 * \f$ A \leftarrow A^{\top} A \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SLMULTT_I ( GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_SRMULTT_Q
/**
 * \brief Macro: Right-multiply a matrix by its own transpose, producing a symmetric matrix.
 *
 * Right multiply a fixed size matrix \a A by its own transpose, producing
 * a symmetric fixed-size matrix \f$ B = A A^{\top} \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_SQUMATTYPEL *GAN_MAT_SRMULTT_Q ( const GAN_MATTYPE *A, GAN_SQUMATTYPEL *B );
#endif

#ifdef GAN_MAT_SRMULTT_I
/**
 * \brief Macro: Right-multiply a matrix by its own transpose, producing a symmetric matrix.
 *
 * Right multiply a fixed size matrix \a A by its own transpose, producing
 * a symmetric fixed-size matrix which is overwritten on
 * \f$ A \leftarrow A A^{\top} \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_MAT_SRMULTT_I ( GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixNorms
 * \{
 */

#ifdef GAN_MAT_SUMSQR_Q
/**
 * \brief Macro: Returns sum of squares of matrix elements.
 *
 * Returns sum of squares of elements of matrix \a A.
 */
GANDALF_API GAN_REALTYPE GAN_MAT_SUMSQR_Q ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_FNORM_Q
/**
 * \brief Macro: Frobenius norm of matrix.
 *
 * Returns Frobenius norm of matrix \a A, defined as the square-root of the
 * sum of squares of the elements of \a A.
 */
GANDALF_API GAN_REALTYPE GAN_MAT_FNORM_Q ( const GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixConvert
 * \{
 */

#ifdef GAN_MAT_FROM_MAT_Q
GANDALF_API GAN_MATTYPE *GAN_MAT_FROM_MAT_Q ( const GAN_MATRIX_TYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_MAT_FROM_SQUMAT_Q
GANDALF_API GAN_MATTYPE *GAN_MAT_FROM_SQUMAT_Q ( const GAN_SQUMATRIX_TYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_SQUMAT_FROM_SQUMAT_Q
GANDALF_API GAN_SQUMATTYPEL *GAN_SQUMAT_FROM_SQUMAT_Q ( const GAN_SQUMATRIX_TYPE *A,
                                            GAN_SQUMATTYPEL *B );
#endif

/**
 * \}
 */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#include <gandalf/linalg/matrixf_undef_noc.h>
