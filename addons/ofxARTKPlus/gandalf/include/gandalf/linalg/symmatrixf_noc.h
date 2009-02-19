/**
 * File:          $RCSfile: symmatrixf_noc.h,v $
 * Module:        Symmetric fixed size matrix functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.15 $
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

/* function declarations for functions common to all small symmetric matrix
 * types */

#ifndef GAN_GENERATE_DOCUMENTATION

#ifdef GAN_VEC_OUTER_SYM_S
GANDALF_API GAN_MATTYPE GAN_VEC_OUTER_SYM_S ( const GAN_VECTYPE1 *p );
#endif

#ifdef GAN_SYMMAT_CHOLESKY
GANDALF_API GAN_MATTYPE *GAN_SYMMAT_CHOLESKY ( GAN_MATTYPE *A, GAN_MATTYPE *B,
                                   int *error_code );
#endif

#ifdef GAN_SYMMAT_CHOLESKY_S
GANDALF_API GAN_MATTYPE GAN_SYMMAT_CHOLESKY_S ( const GAN_MATTYPE *A );
#endif

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#ifdef GAN_GENERATE_DOCUMENTATION

/* documentation for macros defined in individual header files */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

#ifdef GAN_VEC_OUTER_SYM_Q
/**
 * \brief Macro: Computes the outer product of vector with itself
 *
 * Computes and returns \f$ A = p p^{\top} \f$.
 */
GANDALF_API GAN_MATTYPE *GAN_VEC_OUTER_SYM_Q ( const GAN_VECTYPE1 *p, GAN_MATTYPE *A );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixCholesky
 * \{
 */

/**
 * \brief Macro: Compute Cholesky factorisation of fixed size symmetric matrix.
 *
 * Compute Cholesky factorisation of fixed size symmetric matrix \a A,
 * writing result into lower triangular matrix \f$ B = \mbox{chol} (A) \f$
 * such that
 * \f[
 *   B B^{\top} = A
 * \f]
 *
 * \return Pointer to result matrix \a B, or \c NULL on failure.
 */
#ifdef GAN_SYMMAT_CHOLESKY_Q
GANDALF_API GAN_MATTYPE *GAN_SYMMAT_CHOLESKY_Q ( GAN_MATTYPE *A, GAN_MATTYPE *B );
#endif

/**
 * \brief Macro: Compute Cholesky factorisation of fixed size symmetric matrix.
 *
 * Compute Cholesky factorisation of fixed size symmetric matrix \a A in-place:
 * \f$ A \leftarrow \mbox{chol}(A) \f$.
 *
 * \return Pointer to result matrix \a A, or \c NULL on failure.
 */
#ifdef GAN_SYMMAT_CHOLESKY_I
GANDALF_API GAN_MATTYPE *GAN_SYMMAT_CHOLESKY_I ( GAN_MATTYPE *A );
#endif

/**
 * \}
 */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#undef GAN_VEC_OUTER_SYM_Q
#undef GAN_VEC_OUTER_SYM_S
#undef GAN_SYMMAT_CHOLESKY
#undef GAN_SYMMAT_CHOLESKY_Q
#undef GAN_SYMMAT_CHOLESKY_S
#undef GAN_SYMMAT_CHOLESKY_I
