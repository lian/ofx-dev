/**
 * File:          $RCSfile: 3vec_noc.h,v $
 * Module:        Size 3 vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.10 $
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

/**
 * \addtogroup FixedSizeVectorFill
 * \{
 */

/**
 * \brief Macro: Fill 3-vector with values
 *
 * Fill 3-vector \a p with values:
 * \f[
 *   p = \left(\begin{array}{c} X \\ Y \\ Z \end{array}\right)
 * \f]
 *
 * \return Pointer to filled 3-vector \a p.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector3 *gan_vec3_fill_q ( Gan_Vector3 *p, double X, double Y, double Z );
#else
#define gan_vec3_fill_q(p,X,Y,Z) (GAN_FREP3_A_C((p)->,=,(X),(Y),(Z)),p)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorProduct
 * \{
 */

/**
 * \brief Macro: Compute vector product of 3-vectors.
 *
 * Compute vector product of 3-vectors \a p, \a q, write the result into
 * 3-vector \f$r = p \times q\f$.
 *
 * \return Pointer to result 3-vector \a r.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector3 *gan_vec3_cross_q ( const Gan_Vector3 *p, const Gan_Vector3 *q,
                                Gan_Vector3 *r );
#else
#define gan_vec3_cross_q(p,q,r) \
  (GAN_TEST_OP3(p,q,r,Gan_Vector3,Gan_Vector3,Gan_Vector3),\
   assert((r)!=(p)&&(r)!=(q)),\
   (r)->x=(p)->y*(q)->z-(p)->z*(q)->y,\
   (r)->y=(p)->z*(q)->x-(p)->x*(q)->z,\
   (r)->z=(p)->x*(q)->y-(p)->y*(q)->x,r)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorExtract
 * \{
 */

/**
 * \brief Macro: Extract top 2-vector part of 3-vector.
 *
 * Extract top 2-vector part of 3-vector \a p into 2-vector \a q.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector2 *gan_vec3_get_v2t_q ( const Gan_Vector3 *p, Gan_Vector2 *q );
#else
#define gan_vec3_get_v2t_q(p,q)\
           (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector2),\
            GAN_REP2_AA_C((q)->,=(p)->),q)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeVectorBuild
 * \{
 */

/**
 * \brief Macro: Build 3-vector from 2-vector and scalar.
 *
 * Build 3-vector \a p from 2-vector \a q and scalar \a s,
 * which are respectively inserted in the top and bottom parts of the 3-vector,
 * so that
 * \f[
 *   p = \left(\begin{array}{c} q \\ s \end{array}\right)
 * \f]
 *
 * \return Result 3-vector \a p.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector3 *gan_vec3_set_parts_q ( Gan_Vector3 *p, const Gan_Vector2 *q, double s );
#else
#define gan_vec3_set_parts_q(p,q,s)\
           (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector2),\
            GAN_REP2_AA_C((p)->,=(q)->), (p)->z = (s),p)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Vector3 gan_vec3_fill_s ( double X, double Y, double Z );
GANDALF_API Gan_Vector3 gan_vec3_set_parts_s ( const Gan_Vector2 *q, double s );
GANDALF_API Gan_Vector2 gan_vec3_get_v2t_s ( const Gan_Vector3 *p );
GANDALF_API Gan_Vector3 gan_vec3_cross_s ( const Gan_Vector3 *p, const Gan_Vector3 *q );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#define GAN_VECTYPE Gan_Vector3
#define GAN_VECTOR_TYPE Gan_Vector
#define GAN_VEC_ELEMENT_TYPE GAN_DOUBLE
#define GAN_REALTYPE double
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f64
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f64
#define GAN_VEC_FPRINT        gan_vec3_fprint
#define GAN_VEC_PRINT         gan_vec3_print
#define GAN_VEC_FSCANF        gan_vec3_fscanf
#define GAN_VEC_FWRITE        gan_vec3_fwrite
#define GAN_VEC_FREAD         gan_vec3_fread
#define GAN_VEC_ZERO_Q        gan_vec3_zero_q
#define GAN_VEC_ZERO_S        gan_vec3_zero_s
#define GAN_VEC_COPY_Q        gan_vec3_copy_q
#define GAN_VEC_COPY_S        gan_vec3_copy_s
#define GAN_VEC_SCALE_Q       gan_vec3_scale_q
#define GAN_VEC_SCALE_S       gan_vec3_scale_s
#define GAN_VEC_SCALE_I       gan_vec3_scale_i
#define GAN_VEC_DIVIDE_Q      gan_vec3_divide_q
#define GAN_VEC_DIVIDE_S      gan_vec3_divide_s
#define GAN_VEC_DIVIDE_I      gan_vec3_divide_i
#define GAN_VEC_NEGATE_Q      gan_vec3_negate_q
#define GAN_VEC_NEGATE_S      gan_vec3_negate_s
#define GAN_VEC_NEGATE_I      gan_vec3_negate_i
#define GAN_VEC_UNIT_Q        gan_vec3_unit_q
#define GAN_VEC_UNIT_S        gan_vec3_unit_s
#define GAN_VEC_UNIT_I        gan_vec3_unit_i
#define GAN_VEC_ADD_Q         gan_vec3_add_q
#define GAN_VEC_ADD_I1        gan_vec3_add_i1
#define GAN_VEC_ADD_I2        gan_vec3_add_i2
#define GAN_VEC_INCREMENT     gan_vec3_increment
#define GAN_VEC_ADD_S         gan_vec3_add_s
#define GAN_VEC_SUB_Q         gan_vec3_sub_q
#define GAN_VEC_SUB_I1        gan_vec3_sub_i1
#define GAN_VEC_SUB_I2        gan_vec3_sub_i2
#define GAN_VEC_DECREMENT     gan_vec3_decrement
#define GAN_VEC_SUB_S         gan_vec3_sub_s
#define GAN_VEC_DOT_Q         gan_vec3_dot_q
#define GAN_VEC_DOT_S         gan_vec3_dot_s
#define GAN_VEC_SQRLEN_Q      gan_vec3_sqrlen_q
#define GAN_VEC_SQRLEN_S      gan_vec3_sqrlen_s
#define GAN_VEC_FROM_VEC_Q    gan_vec3_from_vec_q
#define GAN_VEC_FROM_VEC_S    gan_vec3_from_vec_s

#ifndef GAN_GENERATE_DOCUMENTATION
/* macros: documentation in vectorf_noc.h */
#define gan_vec3_zero_q(p) (GAN_TEST_OP1(p,Gan_Vector3),\
                            GAN_REP3_AS_C((p)->,=0.0),p)
#define gan_vec3_copy_q(p,q) (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector3),\
                              GAN_REP3_AA_C((q)->,=(p)->),q)
#define gan_vec3_scale_q(p,a,q) (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector3),\
                                 GAN_REP3_AAS_C((q)->,=(p)->,*(a)),q)
#define gan_vec3_scale_i(p,a) gan_vec3_scale_q(p,a,p)
#define gan_vec3_divide_q(p,a,q) (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector3),\
                                  (a)==0.0 ? NULL :\
                                  (GAN_REP3_AAS_C((q)->,=(p)->,/(a)),q))
#define gan_vec3_divide_i(p,a) gan_vec3_divide_q(p,a,p)
#define gan_vec3_unit_i(p) gan_vec3_unit_q(p,p)
#define gan_vec3_negate_q(p,q) (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector3),\
                                GAN_REP3_AA_C((q)->,= -(p)->),q)
#define gan_vec3_negate_i(p) gan_vec3_negate_q(p,p)
#define gan_vec3_add_q(p,q,r)\
           (GAN_TEST_OP3(p,q,r,Gan_Vector3,Gan_Vector3,Gan_Vector3),\
            GAN_REP3_AAA_C((r)->,=(p)->,+(q)->),r)
#define gan_vec3_add_i1(p,q) gan_vec3_add_q(p,q,p)
#define gan_vec3_add_i2(p,q) gan_vec3_add_q(p,q,q)
#define gan_vec3_increment(p,q) gan_vec3_add_i1(p,q)
#define gan_vec3_sub_q(p,q,r)\
           (GAN_TEST_OP3(p,q,r,Gan_Vector3,Gan_Vector3,Gan_Vector3),\
            GAN_REP3_AAA_C((r)->,=(p)->,-(q)->),r)
#define gan_vec3_sub_i1(p,q) gan_vec3_sub_q(p,q,p)
#define gan_vec3_sub_i2(p,q) gan_vec3_sub_q(p,q,q)
#define gan_vec3_decrement(p,q) gan_vec3_sub_i1(p,q)
#define gan_vec3_dot_q(p,q) (GAN_TEST_OP2(p,q,Gan_Vector3,Gan_Vector3),\
                             GAN_REP3_OP_AA_C((p)->,*(q)->,+))
#define gan_vec3_sqrlen_q(p) gan_vec3_dot_q(p,p)
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */
