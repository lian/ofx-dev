/**
 * File:          $RCSfile: squmatrixf_noc.h,v $
 * Module:        Fixed size square matrix functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.18 $
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

/* function declarations for functions common to all small square matrix
 * types */

#ifndef GAN_GENERATE_DOCUMENTATION

#ifdef GAN_SQUMAT_IDENT_S
GANDALF_API GAN_MATTYPE GAN_SQUMAT_IDENT_S (void);
#endif

#ifdef GAN_SQUMAT_TPOSE_S
GANDALF_API GAN_MATTYPE GAN_SQUMAT_TPOSE_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMAT_TPOSE_I
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_TPOSE_I ( GAN_MATTYPE *A );
#endif

#ifdef GAN_MAT_SADDT_S
GANDALF_API GAN_SQUMATTYPER GAN_MAT_SADDT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMATI_MULTV_S
GANDALF_API GAN_VECTYPE1 GAN_SQUMATI_MULTV_S ( const GAN_MATTYPE *A, const GAN_VECTYPE2 *p );
#endif

#ifdef GAN_SQUMATIT_MULTV_S
GANDALF_API GAN_VECTYPE2 GAN_SQUMATIT_MULTV_S ( const GAN_MATTYPE *A, const GAN_VECTYPE1 *p );
#endif

#ifdef GAN_SQUMAT_INVERT
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_INVERT ( GAN_MATTYPE *A, GAN_MATTYPE *B,
                                 int *error_code );
#endif

#ifdef GAN_SQUMAT_INVERT_S
GANDALF_API GAN_MATTYPE GAN_SQUMAT_INVERT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMAT_ADJOINT_Q
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_ADJOINT_Q ( const GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_SQUMAT_ADJOINT_S
GANDALF_API GAN_MATTYPE GAN_SQUMAT_ADJOINT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMAT_ADJOINTT_Q
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_ADJOINTT_Q ( const GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_SQUMAT_ADJOINTT_S
GANDALF_API GAN_MATTYPE GAN_SQUMAT_ADJOINTT_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMAT_DET_S
GANDALF_API GAN_REALTYPE GAN_SQUMAT_DET_S ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMAT_TRACE_S
GANDALF_API GAN_REALTYPE GAN_SQUMAT_TRACE_S ( const GAN_MATTYPE *A );
#endif

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#ifdef GAN_GENERATE_DOCUMENTATION

/* documentation for macros defined in individual header files */

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

#ifdef GAN_SQUMAT_IDENT_Q
/**
 * \brief Macro: Fill fixed size square matrix with identity.
 *
 * Fill fixed size square matrix \a A with identity.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_IDENT_Q ( GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixTranspose
 * \{
 */

#ifdef GAN_SQUMAT_TPOSE_Q
/**
 * \brief Macro: Transpose fixed size square matrix.
 *
 * Transpose fixed size square matrix \a A to fixed size square matrix
 * \f$ B = A^{\top} \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_TPOSE_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixAdd
 * \{
 */

#ifdef GAN_MAT_SADDT_Q
/**
 * \brief Macro: Add matrix to its own transpose.
 *
 * Compute sum of fixed-size square matrix \a A with its own transpose,
 * producing a symmetric matrix \f$ B = A + A^{\top} \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_SQUMATTYPER *GAN_MAT_SADDT_Q ( const GAN_MATTYPE *A, GAN_SQUMATTYPER *B );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

#ifdef GAN_SQUMATI_MULTV_Q
/**
 * \brief Macro: Computes the product of the inverse of a matrix and a vector
 *
 * Computes the product of the inverse of matrix \a A and a vector \a p,
 * writing the result into vector \f$ q = A p \f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE1 *GAN_SQUMATI_MULTV_Q ( const GAN_MATTYPE *A, GAN_VECTYPE1 *p,
                                    GAN_VECTYPE1 *q );
#endif

#ifdef GAN_SQUMATI_MULTV_I
/**
 * \brief Macro: Computes the product of the inverse of matrix and a vector in-place
 *
 * Computes the product of the inverse of matrix \a A and a vector \a p,
 * writing the result in-place into \f$ p \leftarrow A^{-1} p \f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE1 *GAN_SQUMATI_MULTV_I ( const GAN_MATTYPE *A, GAN_VECTYPE1 *p );
#endif

#ifdef GAN_SQUMATIT_MULTV_Q
/**
 * \brief Macro: Computes the product of an inverted transposed matrix and a vector
 *
 * Computes the product of the inverse transpose of matrix \a A and vector
 * \a p, writing the result into vector \f$ q = A^{-{\top}} p \f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE1 *GAN_SQUMATIT_MULTV_Q ( const GAN_MATTYPE *A, GAN_VECTYPE1 *p,
                                     GAN_VECTYPE1 *q );
#endif

#ifdef GAN_SQUMATIT_MULTV_I
/**
 * \brief Macro: Computes the product of an inverted transposed matrix and a vector in-place
 *
 * Computes the product of the inverse transpose of matrix \a A and vector
 * \a p, writing the result in-place into \f$ p \leftarrow A^{-{\top}} p \f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE1 *GAN_SQUMATIT_MULTV_I ( const GAN_MATTYPE *A, GAN_VECTYPE1 *p );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixInvert
 * \{
 */

#ifdef GAN_SQUMAT_INVERT_Q
/**
 * \brief Macro: Invert fixed size square matrix.
 *
 * Compute inverse of fixed-size square matrix \a A, putting result in
 * \f$ B = A^{-1} \f$.
 *
 * \return Pointer to result matrix \a B.
 */
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_INVERT_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

#ifdef GAN_SQUMAT_INVERT_I
/**
 * \brief Macro: Invert fixed size square matrix in-place.
 *
 * Compute inverse of fixed-size square matrix \a A in-place:
 * \f$ A \leftarrow A^{-1} \f$.
 *
 * \return Pointer to result matrix \a A.
 */
GANDALF_API GAN_MATTYPE *GAN_SQUMAT_INVERT_I ( GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixNorms
 * \{
 */

#ifdef GAN_SQUMAT_DET_Q
/**
 * \brief Macro: Determinant of square matrix.
 *
 * Returns determinant of square matrix \a A.
 */
GANDALF_API GAN_REALTYPE GAN_SQUMAT_DET_Q ( const GAN_MATTYPE *A );
#endif

#ifdef GAN_SQUMAT_TRACE_Q
/**
 * \brief Macro: Trace of square matrix.
 *
 * Returns trace of square matrix \a A.
 */
GANDALF_API GAN_REALTYPE GAN_SQUMAT_TRACE_Q ( const GAN_MATTYPE *A );
#endif

/**
 * \}
 */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#undef GAN_SQUMAT_IDENT_Q
#undef GAN_SQUMAT_IDENT_S
#undef GAN_SQUMAT_TPOSE_Q
#undef GAN_SQUMAT_TPOSE_S
#undef GAN_SQUMAT_TPOSE_I
#undef GAN_MAT_SADDT_Q
#undef GAN_MAT_SADDT_S
#undef GAN_SQUMATI_MULTV_Q
#undef GAN_SQUMATI_MULTV_S
#undef GAN_SQUMATI_MULTV_I
#undef GAN_SQUMATIT_MULTV_Q
#undef GAN_SQUMATIT_MULTV_S
#undef GAN_SQUMATIT_MULTV_I
#undef GAN_SQUMAT_INVERT
#undef GAN_SQUMAT_INVERT_Q
#undef GAN_SQUMAT_INVERT_S
#undef GAN_SQUMAT_INVERT_I
#undef GAN_SQUMAT_ADJOINT_Q
#undef GAN_SQUMAT_ADJOINT_S
#undef GAN_SQUMAT_ADJOINTT_Q
#undef GAN_SQUMAT_ADJOINTT_S
#undef GAN_SQUMAT_DET_Q
#undef GAN_SQUMAT_DET_S
#undef GAN_SQUMAT_TRACE_Q
#undef GAN_SQUMAT_TRACE_S
