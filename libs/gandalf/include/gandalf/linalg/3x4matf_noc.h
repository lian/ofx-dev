/**
 * File:          $RCSfile: 3x4matf_noc.h,v $
 * Module:        3x4 matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.21 $
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

#ifndef _GAN_3X4MATF_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 3x4 matrix with values.
 *
 * Fill 3x4 matrix \a A with values:
 * \f[ A = \left(\begin{array}{cccc} XX & XY & XZ & XW \\ YX & YY & YZ & YW \\
 *                                   ZX & ZY & ZZ & ZW
 *         \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix34_f *gan_mat34f_fill_q ( Gan_Matrix34_f *A,
                                    float XX, float XY, float XZ, float XW,
                                    float YX, float YY, float YZ, float YW,
                                    float ZX, float ZY, float ZZ, float ZW );
#else
#define gan_mat34f_fill_q(A,XX,XY,XZ,XW,YX,YY,YZ,YW,ZX,ZY,ZZ,ZW)\
   (GAN_TEST_OP1(A,Gan_Matrix34_f),\
    GAN_FREP34_A_C((A)->,=,(XX),(XY),(XZ),(XW),(YX),(YY),(YZ),(YW),(ZX),(ZY),(ZZ),(ZW)),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixMatrixProduct
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Multiply 3x4 matrix by the transpose of 3x4 matrix.
 *
 * Multiply 3x4 matrix \a A by the transpose of 3x4 matrix \a B, producing
 * a 3x3 matrix \a C as the result, so that
 * \f[
 *   C = A B^{\top}
 * \f]
 *
 * \return Pointer to the result matrix \a C.
 */
GANDALF_API Gan_Matrix33_f *gan_mat34f_rmultm34T_q ( const Gan_Matrix34_f *A, const Gan_Matrix34_f *B,
                                         Gan_Matrix33_f *C );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Multiply 3x4 matrix by homogeneous 3-vector.
 *
 * Multiply 3x4 matrix \a A by 3-vector \a p expanded to a homogeneous
 * 4-vector by adding third element \a h, in other words compute and
 * return 3-vector \a q where
 * \f[
 *   q = A \left(\begin{array}{c} p \\ h \end{array}\right)
 * \f]
 *
 * \return Pointer to the result vector \a q.
 */
GANDALF_API Gan_Vector3_f *gan_mat34_multv3h_q ( const Gan_Matrix34_f *A, const Gan_Vector3_f *p,
                                     float h, Gan_Vector3_f *q );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extract rows of 3x4 matrix.
 *
 * Extract rows of 3x4 matrix \a A into 4-vectors \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top}
 *         \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat34f_get_rows_q ( const Gan_Matrix34_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r );
#else
#define gan_mat34f_get_rows_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,Gan_Matrix34_f,\
                         Gan_Vector4_f,Gan_Vector4_f,Gan_Vector4_f),\
            ((p)->x=(A)->xx,(p)->y=(A)->xy,(p)->z=(A)->xz,(p)->w=(A)->xw,\
             (q)->x=(A)->yx,(q)->y=(A)->yy,(q)->z=(A)->yz,(q)->w=(A)->yw,\
             (r)->x=(A)->zx,(r)->y=(A)->zy,(r)->z=(A)->zz,(r)->w=(A)->zw))
#endif

/**
 * \brief Macro: Extract columns of 3x4 matrix
 *
 * Extract columns of 3x4 matrix \a A into 3-vectors \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{cccc} p & q & r & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat34f_get_cols_q ( const Gan_Matrix34_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r, Gan_Vector3_f *s );
#else
#define gan_mat34f_get_cols_q(A,p,q,r,s)\
           (GAN_TEST_OP5(A,p,q,r,s,Gan_Matrix34_f,\
                         Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f),\
            ((p)->x=(A)->xx,(q)->x=(A)->xy,(r)->x=(A)->xz,(s)->x=(A)->xw,\
             (p)->y=(A)->yx,(q)->y=(A)->yy,(r)->y=(A)->yz,(s)->y=(A)->yw,\
             (p)->z=(A)->zx,(q)->z=(A)->zy,(r)->z=(A)->zz,(s)->z=(A)->zw))
#endif

/**
 * \brief Macro: Extract left-hand 3x3 part of 3x4 matrix.
 *
 * Extract left-hand 3x3 part of 3x4 matrix \a A into 3x3 matrix \a B.
 *
 * \return Pointer to result 3x3 matrix \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat34f_get_m33l_q ( const Gan_Matrix34_f *A, Gan_Matrix33_f *B );
#else
#define gan_mat34f_get_m33l_q(A,B)\
           (GAN_TEST_OP2(A,B,Gan_Matrix34_f,Gan_Matrix33_f),\
            (B)->xx=(A)->xx,(B)->xy=(A)->xy,(B)->xz=(A)->xz,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,(B)->yz=(A)->yz,\
            (B)->zx=(A)->zx,(B)->zy=(A)->zy,(B)->zz=(A)->zz,B)
#endif

/**
 * \brief Macro: Extract right-hand column of 3x4 matrix.
 *
 * Extract right-hand column of 3x4 matrix \a A into 3-vector \a p.
 *
 * \return Pointer to result 3-vector \a p.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector3_f *gan_mat34f_get_v3r_q ( const Gan_Matrix34_f *A, Gan_Vector3_f *p );
#else
#define gan_mat34f_get_v3r_q(A,p)\
           (GAN_TEST_OP2(A,p,Gan_Matrix34_f,Gan_Vector3_f),\
            (p)->x=(A)->xw,(p)->y=(A)->yw,(p)->z=(A)->zw,p)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixBuild
 * \{
 */

/**
 * \brief Macro: Build 3x4 matrix from 3x3 matrix and column 3-vector.
 *
 * Build 3x4 matrix \a A from 3x3 matrix \a B and column 3-vector \a p,
 * which are respectively inserted in the left-hand and right-hand parts
 * of the 3x4 matrix. The arrangement is thus
 * \f[
 *    A = \left(\begin{array}{cc} B & p \end{array}\right)
 * \f]
 *
 * \return Pointer to result 3x4 matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix34_f *gan_mat34f_set_parts_q ( Gan_Matrix34_f *A,
                                         const Gan_Matrix33_f *B, const Gan_Vector3_f *p );
#else
#define gan_mat34f_set_parts_q(A,B,p)\
           (GAN_TEST_OP3(A,B,p,\
                         Gan_Matrix34_f,Gan_Matrix33_f,Gan_Vector3_f),\
            (A)->xx=(B)->xx,(A)->xy=(B)->xy,(A)->xz=(B)->xz,(A)->xw=(p)->x,\
            (A)->yx=(B)->yx,(A)->yy=(B)->yy,(A)->yz=(B)->yz,(A)->yw=(p)->y,\
            (A)->zx=(B)->zx,(A)->zy=(B)->zy,(A)->zz=(B)->zz,(A)->zw=(p)->z,A)
#endif

/**
 * \brief Macro: Build 3x4 matrix from 3-vector columns.
 *
 * Build 3x4 matrix \a A from 3-vector columns \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{cccc} p & q & r & s \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix34_f *gan_mat34f_set_cols_q ( Gan_Matrix34_f *A,
                                        const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                        const Gan_Vector3_f *r, const Gan_Vector3_f *s );
#else
#define gan_mat34f_set_cols_q(A,p,q,r,s)\
           (GAN_TEST_OP5(A,p,q,r,s,\
                Gan_Matrix34_f,\
                Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f),\
            (A)->xx=(p)->x,(A)->xy=(q)->x,(A)->xz=(r)->x,(A)->xw=(s)->x,\
            (A)->yx=(p)->y,(A)->yy=(q)->y,(A)->yz=(r)->y,(A)->yw=(s)->y,\
            (A)->zx=(p)->z,(A)->zy=(q)->z,(A)->zz=(r)->z,(A)->zw=(s)->z,A)
#endif

/**
 * \brief Macro: Build 3x4 matrix from 4-vector rows.
 *
 * Build 3x4 matrix \a A from 4-vector rows \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top}
 *     \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix34_f *gan_mat34f_set_rows_q ( Gan_Matrix34_f *A,
                                        const Gan_Vector4_f *p, const Gan_Vector4_f *q,
                                        const Gan_Vector4_f *r );
#else
#define gan_mat34f_set_rows_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,\
                    Gan_Matrix34_f,Gan_Vector4_f,Gan_Vector4_f,Gan_Vector4_f),\
            (A)->xx=(p)->x,(A)->xy=(p)->y,(A)->xz=(p)->z,(A)->xw=(p)->w,\
            (A)->yx=(q)->x,(A)->yy=(q)->y,(A)->yz=(q)->z,(A)->yw=(q)->w,\
            (A)->zx=(r)->x,(A)->zy=(r)->y,(A)->zz=(r)->z,(A)->zw=(r)->w,A)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix34_f gan_mat34f_fill_s (
                          float XX, float XY, float XZ, float XW,
                          float YX, float YY, float YZ, float YW,
                          float ZX, float ZY, float ZZ, float ZW );
GANDALF_API Gan_Vector3_f gan_mat34f_multv3h_s ( const Gan_Matrix34_f *A,
                                     const Gan_Vector3_f *p, float h);
GANDALF_API Gan_Bool gan_mat34hf_invert_q ( const Gan_Matrix34_f *A, float a,
                                Gan_Matrix34_f *B, float *b );
GANDALF_API Gan_Matrix34_f gan_mat34hf_invert_s ( const Gan_Matrix34_f *A, float a, float *b );
GANDALF_API void gan_mat34f_get_rows_s ( const Gan_Matrix34_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r );
GANDALF_API void gan_mat34f_get_cols_s ( const Gan_Matrix34_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r, Gan_Vector3_f *s );
GANDALF_API Gan_Matrix33_f gan_mat34f_get_m33l_s ( const Gan_Matrix34_f *A );
GANDALF_API Gan_Vector3_f  gan_mat34f_get_v3r_s  ( const Gan_Matrix34_f *A );
GANDALF_API Gan_Matrix34_f gan_mat34f_set_parts_s ( const Gan_Matrix33_f *B, const Gan_Vector3_f *p );
GANDALF_API Gan_Matrix34_f gan_mat34f_set_cols_s ( const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                       const Gan_Vector3_f *r, const Gan_Vector3_f *s );
GANDALF_API Gan_Matrix34_f gan_mat34f_set_rows_s ( const Gan_Vector4_f *p, const Gan_Vector4_f *q,
                                       const Gan_Vector4_f *r );
GANDALF_API Gan_Matrix34_f *gan_mat34f_from_matf_q ( const Gan_Matrix_f *A, Gan_Matrix34_f *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_3X4MATF_H */

#define GAN_MATTYPE Gan_Matrix34_f
#define GAN_MATRIX_TYPE Gan_Matrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f32
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f32
#define GAN_VECTYPE1 Gan_Vector3_f
#define GAN_VECTYPE2 Gan_Vector4_f
#define GAN_MATTYPEL Gan_Matrix33_f
#define GAN_MATTYPER Gan_Matrix44_f
#define GAN_SQUMATTYPEL Gan_SquMatrix33_f
#define GAN_SQUMATTYPER Gan_SquMatrix44_f
#define GAN_MAT_FPRINT                     gan_mat34f_fprint
#define GAN_MAT_PRINT                      gan_mat34f_print
#define GAN_MAT_FSCANF                     gan_mat34f_fscanf
#define GAN_MAT_FWRITE                     gan_mat34f_fwrite
#define GAN_MAT_FREAD                      gan_mat34f_fread
#define GAN_MAT_ZERO_Q                     gan_mat34f_zero_q
#define GAN_MAT_ZERO_S                     gan_mat34f_zero_s
#define GAN_MAT_COPY_Q                     gan_mat34f_copy_q
#define GAN_MAT_COPY_S                     gan_mat34f_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat34f_scale_q
#define GAN_MAT_SCALE_I                    gan_mat34f_scale_i
#define GAN_MAT_SCALE_S                    gan_mat34f_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat34f_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat34f_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat34f_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat34f_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat34f_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat34f_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat34f_unit_q
#define GAN_MAT_UNIT_I                     gan_mat34f_unit_i
#define GAN_MAT_UNIT_S                     gan_mat34f_unit_s
#define GAN_MAT_ADD_Q                      gan_mat34f_add_q
#define GAN_MAT_ADD_I1                     gan_mat34f_add_i1
#define GAN_MAT_ADD_I2                     gan_mat34f_add_i2
#define GAN_MAT_INCREMENT                  gan_mat34f_increment
#define GAN_MAT_ADD_S                      gan_mat34f_add_s
#define GAN_MAT_SUB_Q                      gan_mat34f_sub_q
#define GAN_MAT_SUB_I1                     gan_mat34f_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat34f_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat34f_decrement
#define GAN_MAT_SUB_S                      gan_mat34f_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec34f_outer_q
#define GAN_VEC_OUTER_S                    gan_vec34f_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat34f_multv4_q
#define GAN_MAT_MULTV_S                    gan_mat34f_multv4_s
#define GAN_MATT_MULTV_Q                   gan_mat34Tf_multv2_q
#define GAN_MATT_MULTV_S                   gan_mat34Tf_multv2_s
#define GAN_MAT_LMULTM_Q                   gan_mat34f_lmultm33_q
#define GAN_MAT_LMULTM_S                   gan_mat34f_lmultm33_s
#define GAN_MAT_LMULTMT_Q                  gan_mat34f_lmultm33T_q
#define GAN_MAT_LMULTMT_S                  gan_mat34f_lmultm33T_s
#define GAN_MAT_RMULTM_Q                   gan_mat34f_rmultm44_q
#define GAN_MAT_RMULTM_S                   gan_mat34f_rmultm44_s
#define GAN_MAT_RMULTMT_Q                  gan_mat34f_rmultm44T_q
#define GAN_MAT_RMULTMT_S                  gan_mat34f_rmultm44T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat34f_lmultm34T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat34f_lmultm34T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat34f_rmultm34T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat34f_rmultm34T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat34f_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat34f_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat34f_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat34f_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat34f_lmults33_q
#define GAN_MAT_LMULTS_S                   gan_mat34f_lmults33_s
#define GAN_MAT_RMULTS_Q                   gan_mat34f_rmults44_q
#define GAN_MAT_RMULTS_S                   gan_mat34f_rmults44_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat33f_lrmultm34T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat33f_lrmultm34T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat44f_lrmultm34_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat44f_lrmultm34_s
#define GAN_MAT_LMULTL_Q                   gan_mat34f_lmultl33_q
#define GAN_MAT_LMULTL_S                   gan_mat34f_lmultl33_s
#define GAN_MAT_LMULTL_I                   gan_mat34f_lmultl33_i
#define GAN_MAT_LMULTLI_Q                  gan_mat34f_lmultl33I_q
#define GAN_MAT_LMULTLI_S                  gan_mat34f_lmultl33I_s
#define GAN_MAT_LMULTLI_I                  gan_mat34f_lmultl33I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat34f_lmultl33T_q
#define GAN_MAT_LMULTLT_S                  gan_mat34f_lmultl33T_s
#define GAN_MAT_LMULTLT_I                  gan_mat34f_lmultl33T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat34f_lmultl33IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat34f_lmultl33IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat34f_lmultl33IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat34f_rmultl44_q
#define GAN_MAT_RMULTL_S                   gan_mat34f_rmultl44_s
#define GAN_MAT_RMULTL_I                   gan_mat34f_rmultl44_i
#define GAN_MAT_RMULTLI_Q                  gan_mat34f_rmultl44I_q
#define GAN_MAT_RMULTLI_S                  gan_mat34f_rmultl44I_s
#define GAN_MAT_RMULTLI_I                  gan_mat34f_rmultl44I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat34f_rmultl44T_q
#define GAN_MAT_RMULTLT_S                  gan_mat34f_rmultl44T_s
#define GAN_MAT_RMULTLT_I                  gan_mat34f_rmultl44T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat34f_rmultl44IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat34f_rmultl44IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat34f_rmultl44IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat34f_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat34f_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat34f_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat34f_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat34f_from_matf_q
#define GAN_MAT_FROM_MAT_S                 gan_mat34f_from_matf_s

#ifndef _GAN_3X4MATF_H
#define _GAN_3X4MATF_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat34f_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix34_f),\
                             GAN_REP34_AS((A)->,=0.0,x,y,z,x,y,z,w),A)
#define gan_mat34f_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix34_f,Gan_Matrix34_f),\
                               GAN_REP34_AA_C((B)->,=(A)->),B)
#define gan_mat34f_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix34_f,Gan_Matrix34_f),\
                                  GAN_REP34_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat34f_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix34_f),\
                                GAN_REP34_AS_C((A)->,*=(a)),A)
#define gan_mat34f_divide_q(A,a,B) (GAN_TEST_OP2(A,B,\
                                                Gan_Matrix34_f,Gan_Matrix34_f),\
                                   (a)==0.0 ? NULL :\
                                   (GAN_REP34_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat34f_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix34_f),\
                                 (a)==0.0 ? NULL :\
                                 (GAN_REP34_AS_C((A)->,/=(a)),A))
#define gan_mat34f_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix34_f,Gan_Matrix34_f),\
                                 GAN_REP34_AA_C((B)->,=-(A)->),B)
#define gan_mat34f_negate_i(A) gan_mat34f_negate_q(A,A)
#define gan_mat34f_unit_i(A) gan_mat34f_unit_q(A,A)
#define gan_mat34f_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix34_f,\
                                                   Gan_Matrix34_f),\
                                GAN_REP34_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat34f_add_i1(A,B) gan_mat34f_add_q(A,B,A)
#define gan_mat34f_add_i2(A,B) gan_mat34f_add_q(A,B,B)
#define gan_mat34f_increment(A,B) gan_mat34f_add_i1(A,B)
#define gan_mat34f_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix34_f,\
                                                   Gan_Matrix34_f),\
                                GAN_REP34_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat34f_sub_i1(A,B) gan_mat34f_sub_q(A,B,A)
#define gan_mat34f_sub_i2(A,B) gan_mat34f_sub_q(A,B,B)
#define gan_mat34f_decrement(A,B) gan_mat34f_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec34f_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector3_f,Gan_Vector4_f,Gan_Matrix34_f),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,xx,xy,xz,xw,x,x,x,x,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,yx,yy,yz,yw,y,y,y,y,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,zx,zy,zz,zw,z,z,z,z,x,y,z,w),A)
 
/* matrix/vector multiply */
#define gan_mat34f_multv4_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix34_f,Gan_Vector4_f,Gan_Vector3_f),\
  GAN_MAT34F_MULT1D((q)->,(A)->,(p)->,x,y,z,x,y,z,w),q)
#define gan_mat34f_multv3h_q(A,p,h,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix34_f,Gan_Vector3_f,Gan_Vector3_f),\
  (q)->x = (A)->xx*(p)->x + (A)->xy*(p)->y + (A)->xz*(p)->z + (A)->xw*(h),\
  (q)->y = (A)->yx*(p)->x + (A)->yy*(p)->y + (A)->yz*(p)->z + (A)->yw*(h),\
  (q)->z = (A)->zx*(p)->x + (A)->zy*(p)->y + (A)->zz*(p)->z + (A)->zw*(h),q)
#define gan_mat34Tf_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix34_f,Gan_Vector3_f,Gan_Vector4_f),\
  GAN_MAT34TF_MULT1D((q)->,(A)->,(p)->,x,y,z,w,x,y,z),q)

/* matrix/matrix multiply */
#define gan_mat34f_lmultm33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix33_f,Gan_Matrix34_f),\
  assert((A)!=(C)),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_lmultm33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix33_f,Gan_Matrix34_f),\
  assert((A)!=(C)),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_rmultm44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix44_f,Gan_Matrix34_f),\
  assert((A)!=(C)),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,yx,zx,wx),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,xy,yy,zy,wy),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,xz,yz,zz,wz),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,xw,yw,zw,ww),C)
#define gan_mat34f_rmultm44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix44_f,Gan_Matrix34_f),\
  assert((A)!=(C)),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,xy,xz,xw),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,yx,yy,yz,yw),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,zx,zy,zz,zw),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,wx,wy,wz,ww),C)
#define gan_mat34f_lmultm34T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix34_f,Gan_SquMatrix44_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT34TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx),\
  (C)->yy = GAN_REP3_OP_AA((A)->,*(B)->,xy,yy,zy,+),\
  (C)->zy = GAN_REP3_OP_AB((A)->,*(B)->,xz,yz,zz,xy,yy,zy,+),\
  (C)->wy = GAN_REP3_OP_AB((A)->,*(B)->,xw,yw,zw,xy,yy,zy,+),\
  (C)->zz = GAN_REP3_OP_AA((A)->,*(B)->,xz,yz,zz,+),\
  (C)->wz = GAN_REP3_OP_AB((A)->,*(B)->,xw,yw,zw,xz,yz,zz,+),\
  (C)->ww = GAN_REP3_OP_AA((A)->,*(B)->,xw,yw,zw,+),C)
#define gan_mat34f_slmultT_q(A,C) gan_mat34f_lmultm34T_sym_q(A,A,C)
#define gan_mat34f_rmultm34T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix34_f,Gan_SquMatrix33_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,xy,xz,xw),\
  (C)->yy = GAN_REP4_OP_AA((A)->,*(B)->,yx,yy,yz,yw,+),\
  (C)->zy = GAN_REP4_OP_AB((A)->,*(B)->,zx,zy,zz,zw,yx,yy,yz,yw,+),\
  (C)->zz = GAN_REP4_OP_AA((A)->,*(B)->,zx,zy,zz,zw,+),C)
#define gan_mat34f_srmultT_q(A,C) gan_mat34f_rmultm34T_sym_q(A,A,C)
#define gan_mat34f_lmults33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix33_f,Gan_Matrix34_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_rmults44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix44_f,Gan_Matrix34_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,yx,zx,wx),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,yx,yy,zy,wy),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,zx,zy,zz,wz),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,wx,wy,wz,ww),C)
#define gan_symmat33f_lrmultm34T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix33_f,Gan_Matrix34_f,Gan_Matrix34_f,Gan_SquMatrix44_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,yx,zx),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,xy,yy,zy),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,xz,yz,zz),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,xw,yw,zw),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT34TF_MULT1D((D)->,(B)->,(C)->,xx,yx,zx,wx,xx,yx,zx),\
  (D)->yy = GAN_REP3_OP_AA((C)->,*(B)->,xy,yy,zy,+),\
  (D)->zy = GAN_REP3_OP_AB((C)->,*(B)->,xz,yz,zz,xy,yy,zy,+),\
  (D)->wy = GAN_REP3_OP_AB((C)->,*(B)->,xw,yw,zw,xy,yy,zy,+),\
  (D)->zz = GAN_REP3_OP_AA((C)->,*(B)->,xz,yz,zz,+),\
  (D)->wz = GAN_REP3_OP_AB((C)->,*(B)->,xw,yw,zw,xz,yz,zz,+),\
  (D)->ww = GAN_REP3_OP_AA((C)->,*(B)->,xw,yw,zw,+),D)
#define gan_symmat44f_lrmultm34_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
           Gan_SquMatrix44_f,Gan_Matrix34_f,Gan_Matrix34_f,Gan_SquMatrix33_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT34F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx,wx),\
  GAN_MAT34F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,yx,yy,zy,wy),\
  GAN_MAT34F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,zx,zy,zz,wz),\
  GAN_MAT34F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,wx,wy,wz,ww),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT34F_MULT1D((D)->,(C)->,(B)->,xx,yx,zx,xx,xy,xz,xw),\
  (D)->yy = GAN_REP4_OP_AA((C)->,*(B)->,yx,yy,yz,yw,+),\
  (D)->zy = GAN_REP4_OP_AB((C)->,*(B)->,zx,zy,zz,zw,yx,yy,yz,yw,+),\
  (D)->zz = GAN_REP4_OP_AA((C)->,*(B)->,zx,zy,zz,zw,+),D)
#define gan_mat34f_lmultl33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix33_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_lmultl33_i(A,B) gan_mat34f_lmultl33_q(A,B,A)
#define gan_mat34f_lmultl33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix33_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_lmultl33T_i(A,B) gan_mat34f_lmultl33T_q(A,B,A)
#define gan_mat34f_lmultl33I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix33_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_lmultl33I_i(A,B) gan_mat34f_lmultl33I_q(A,B,A)
#define gan_mat34f_lmultl33IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix33_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,xw,yw,zw),C)
#define gan_mat34f_lmultl33IT_i(A,B) gan_mat34f_lmultl33IT_q(A,B,A)
#define gan_mat34f_rmultl44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix44_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),C)
#define gan_mat34f_rmultl44_i(A,B) gan_mat34f_rmultl44_q(A,B,A)
#define gan_mat34f_rmultl44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix44_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),C)
#define gan_mat34f_rmultl44T_i(A,B) gan_mat34f_rmultl44T_q(A,B,A)
#define gan_mat34f_rmultl44I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix44_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),C)
#define gan_mat34f_rmultl44I_i(A,B) gan_mat34f_rmultl44I_q(A,B,A)
#define gan_mat34f_rmultl44IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_SquMatrix44_f,Gan_Matrix34_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),C)
#define gan_mat34f_rmultl44IT_i(A,B) gan_mat34f_rmultl44IT_q(A,B,A)
#define gan_mat34f_rmultm34T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix34_f,Gan_Matrix34_f,Gan_Matrix33_f),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,xy,xz,xw),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,yx,yy,yz,yw),\
  GAN_MAT34F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,zx,zy,zz,zw),C)

#define gan_mat34f_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix34_f),\
      ((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
       (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw +\
       (A)->zx*(A)->zx + (A)->zy*(A)->zy + (A)->zz*(A)->zz + (A)->zw*(A)->zw))
#define gan_mat34f_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix34_f), (float)\
  sqrt((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
       (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw +\
       (A)->zx*(A)->zx + (A)->zy*(A)->zy + (A)->zz*(A)->zz + (A)->zw*(A)->zw))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_3X4MATF_H */
