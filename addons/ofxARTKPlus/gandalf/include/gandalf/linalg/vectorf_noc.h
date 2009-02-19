/**
 * File:          $RCSfile: vectorf_noc.h,v $
 * Module:        Fixed size vector functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.19 $
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

GANDALF_API Gan_Bool GAN_VEC_FPRINT ( FILE *fp, const GAN_VECTYPE *p,
                          const char *prefix, int indent,  const char *fmt );
GANDALF_API Gan_Bool GAN_VEC_PRINT ( const GAN_VECTYPE *p, const char *prefix,
                         int indent, const char *fmt );
GANDALF_API Gan_Bool GAN_VEC_FSCANF ( FILE *fp, GAN_VECTYPE *p,
                          char *prefix, int prefix_len );
GANDALF_API Gan_Bool GAN_VEC_FWRITE ( FILE *fp, const GAN_VECTYPE *p, gan_uint32 magic_number );
GANDALF_API Gan_Bool GAN_VEC_FREAD ( FILE *fp, GAN_VECTYPE *p, gan_uint32 *magic_number );
GANDALF_API GAN_VECTYPE  GAN_VEC_ZERO_S (void);
GANDALF_API GAN_VECTYPE  GAN_VEC_COPY_S ( const GAN_VECTYPE *x );
GANDALF_API GAN_VECTYPE  GAN_VEC_SCALE_S ( const GAN_VECTYPE *x, const GAN_REALTYPE a );
GANDALF_API GAN_VECTYPE  GAN_VEC_DIVIDE_S ( const GAN_VECTYPE *x, const GAN_REALTYPE a );
GANDALF_API GAN_VECTYPE  GAN_VEC_NEGATE_S ( const GAN_VECTYPE *x );
GANDALF_API GAN_VECTYPE *GAN_VEC_UNIT_Q ( GAN_VECTYPE *x, GAN_VECTYPE *y );
GANDALF_API GAN_VECTYPE  GAN_VEC_UNIT_S ( const GAN_VECTYPE *x );
GANDALF_API GAN_VECTYPE  GAN_VEC_ADD_S ( const GAN_VECTYPE *x, const GAN_VECTYPE *y );
GANDALF_API GAN_VECTYPE  GAN_VEC_SUB_S ( const GAN_VECTYPE *x, const GAN_VECTYPE *y );
GANDALF_API GAN_REALTYPE GAN_VEC_DOT_S ( const GAN_VECTYPE *p, const GAN_VECTYPE *q );
GANDALF_API GAN_REALTYPE GAN_VEC_SQRLEN_S ( const GAN_VECTYPE *p );
GANDALF_API GAN_VECTYPE *GAN_VEC_FROM_VEC_Q ( const GAN_VECTOR_TYPE *x, GAN_VECTYPE *a );
GANDALF_API GAN_VECTYPE  GAN_VEC_FROM_VEC_S ( const GAN_VECTOR_TYPE *x );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

/* documentation for macros defined in individual header files */

/**
 * \addtogroup FixedSizeVectorFill
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Fill fixed size vector with zero.
 *
 * Fill fixed size vector \a p with zero, and return \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_ZERO_Q ( GAN_VECTYPE *p );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorCopy
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Copy fixed size vector.
 *
 * Copy fixed size vector \a p to fixed vector \a q, and return \a q.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_COPY_Q ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorScale
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale fixed size vector.
 *
 * Multiply fixed size vector \a p by scalar \a a, writing result into fixed
 * size vector \a q, and returning \a q.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_SCALE_Q ( GAN_VECTYPE *p, GAN_REALTYPE a,
                               GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale fixed size vector.
 *
 * Multiply fixed size vector \a p by scalar \a a in-place, returning \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_SCALE_I ( GAN_VECTYPE *p, GAN_REALTYPE a );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Divide fixed size vector by scalar.
 *
 * Divide fixed size vector \a p by scalar \a a, writing result into fixed
 * size vector \a q, and returning \a q.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_DIVIDE_Q ( GAN_VECTYPE *p, GAN_REALTYPE a,
                                GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Divide fixed size vector by scalar.
 *
 * Divide fixed size vector \a p by scalar \a a in-place, returning \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_DIVIDE_I ( GAN_VECTYPE *p, GAN_REALTYPE a );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Negate fixed size vector.
 *
 * Negate fixed size vector \a p into fixed size vector \f$ q = -p \f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_NEGATE_Q ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Negate fixed size vector.
 *
 * Negate fixed size vector \a p in-place: \f$ p \leftarrow -p \f$.
 *
 * \return Pointer to negated vector \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_NEGATE_I ( GAN_VECTYPE *p );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale vector to unit norm.
 *
 * Scale fixed-size vector \a p to unit length in-place, returning \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_UNIT_I ( GAN_VECTYPE *p );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorAdd
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Add two fixed size vectors.
 *
 * Add two fixed vectors \a p, \a q and write result into
 * \f$r = p + q\f$.
 *
 * \return Pointer to result vector \a r.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_ADD_Q ( GAN_VECTYPE *p, GAN_VECTYPE *q, GAN_VECTYPE *r );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Add two fixed size vectors.
 *
 * Add two fixed vectors \a p, \a q and overwrite \a p with the result:
 * \f$p \leftarrow p + q\f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_ADD_I1 ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Add two fixed size vectors.
 *
 * Add two fixed vectors \a p, \a q and overwrite \a q with the result:
 * \f$q \leftarrow p + q\f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_ADD_I2 ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Increment a fixed size vector by another.
 *
 * Increment fixed size vector \a p by fixed size vector \a q, overwriting
 * \a p with the result: \f$p \leftarrow p + q\f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_INCREMENT ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorSubtract
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Subtract two fixed size vectors.
 *
 * Subtract two fixed vectors \a p, \a q and write result into
 * \f$r = p - q\f$.
 *
 * \return Pointer to result vector \a r.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_SUB_Q ( GAN_VECTYPE *p, GAN_VECTYPE *q, GAN_VECTYPE *r );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Subtract two fixed size vectors.
 *
 * Subtract two fixed size vectors \a p, \a q and overwrite \a p with the
 * result: \f$ p \leftarrow p - q\f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_SUB_I1 ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Subtract two fixed size vectors.
 *
 * Subtract two fixed size vectors \a p, \a q and overwrite \a q with the
 * result: \f$ q \leftarrow p - q\f$.
 *
 * \return Pointer to result vector \a q.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_SUB_I2 ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Decrement a fixed size vector by another.
 *
 * Decrement fixed size vector \a p by fixed size vector \a q, overwriting
 * \a p with the result: \f$ p \leftarrow p - q \f$.
 *
 * \return Pointer to result vector \a p.
 */
GANDALF_API GAN_VECTYPE *GAN_VEC_DECREMENT ( GAN_VECTYPE *p, GAN_VECTYPE *q );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorScalarProduct
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Dot product of fixed size vectors.
 *
 * Returns the scalar product \f$ p.q \f$ of the two fixed size vectors
 * \a p and \a q.
 */
GANDALF_API GAN_REALTYPE GAN_VEC_DOT_Q ( const GAN_VECTYPE *p, const GAN_VECTYPE *q );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorNorms
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Returns sum of squares of vector elements.
 *
 * Returns the scalar product \f$ p.p \f$ of fixed size vector \a p with
 * itself.
 *
 * \return The squared length of \a p.
 */
GANDALF_API GAN_REALTYPE GAN_VEC_SQRLEN_Q ( const GAN_VECTYPE *p );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorConvert
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_VECTYPE GAN_VEC_FROM_VEC_S ( const GAN_VECTOR_TYPE *x );
#endif

/**
 * \}
 */

#include <gandalf/linalg/vectorf_undef_noc.h>
