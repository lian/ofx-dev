/**
 * File:          $RCSfile: 2x3matf_noc.h,v $
 * Module:        2x3 matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.20 $
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

#ifndef _GAN_2X3MATF_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Fill 2x3 matrix with values.
 *
 * Fill 2x3 matrix \a A with values:
 * \f[
 *     A = \left(\begin{array}{ccc} XX & XY & XZ \\ YX & YY & YZ
 *         \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
GANDALF_API Gan_Matrix23_f *gan_mat23f_fill_q ( Gan_Matrix23_f *A,
                                    float XX, float XY, float XZ,
                                    float YX, float YY, float YZ );
#else
#define gan_mat23f_fill_q(A,XX,XY,XZ,YX,YY,YZ)\
           (GAN_TEST_OP1(A,Gan_Matrix23_f),\
            GAN_FREP23_A_C((A)->,=,(XX),(XY),(XZ),(YX),(YY),(YZ)),A)
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
 * \brief Macro: Multiply 2x3 matrix by the transpose of 2x3 matrix.
 *
 * Multiply 2x3 matrix \a A by the transpose of 2x3 matrix \a B, producing
 * a 2x2 matrix \a C as the result, so that
 * \f[
 *   C = A B^{\top}
 * \f]
 *
 * \return Pointer to the result matrix \a C.
 */
GANDALF_API Gan_Matrix22_f *gan_mat23f_rmultm23T_q ( const Gan_Matrix23_f *A, const Gan_Matrix23_f *B,
                                         Gan_Matrix22_f *C );
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
 * \brief Macro: Multiply 2x3 matrix by homogeneous 2-vector.
 *
 * Multiply 2x3 matrix \a A by 2-vector \a p expanded to a homogeneous
 * 3-vector by adding third element \a h, in other words compute and
 * return 2-vector \a q where
 * \f[
 *   q = A \left(\begin{array}{c} p \\ h \end{array}\right)
 * \f]
 *
 * \return Pointer to the result vector \a q.
 */
GANDALF_API Gan_Vector2_f *gan_mat23f_multv2h_q ( const Gan_Matrix23_f *A,
                                      const Gan_Vector2_f *p, float h,
                                      Gan_Vector2_f *q );
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Extract rows of 2x3 matrix.
 *
 * Extract rows of 2x3 matrix \a A into 3-vectors \a p and \a q.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \end{array}\right)
 * \f]
 *
 * \return No value.
 */
GANDALF_API void gan_mat23f_get_rows_q ( const Gan_Matrix23_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q );
#else
#define gan_mat23f_get_rows_q(A,p,q)\
           (GAN_TEST_OP3(A,p,q,Gan_Matrix23_f,Gan_Vector3_f,Gan_Vector3_f),\
            (p)->x=(A)->xx,(p)->y=(A)->xy,(p)->z=(A)->xz,\
            (q)->x=(A)->yx,(q)->y=(A)->yy,(q)->z=(A)->yz)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Extract columns of 2x3 matrix
 *
 * Extract columns of 2x3 matrix \a A into 2-vectors \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{ccc} p & q & r \end{array}\right)
 * \f]
 *
 * \return No value.
 */
GANDALF_API void gan_mat23f_get_cols_q ( const Gan_Matrix23_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q,
                             Gan_Vector2_f *r );
#else
#define gan_mat23f_get_cols_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,Gan_Matrix23_f,\
                         Gan_Vector2_f,Gan_Vector2_f,Gan_Vector2_f),\
            (p)->x=(A)->xx,(q)->x=(A)->xy,(r)->x=(A)->xz,\
            (p)->y=(A)->yx,(q)->y=(A)->yy,(r)->y=(A)->yz)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Extract left-hand 2x2 part of 2x3 matrix.
 *
 * Extract left-hand 2x2 part of 2x3 matrix \a A into 2x2 matrix \a B.
 *
 * \return Pointer to result 2x2 matrix \a B.
 */
GANDALF_API Gan_Matrix22_f *gan_mat23f_get_m22l_q ( const Gan_Matrix23_f *A, Gan_Matrix22_f *B );
#else
#define gan_mat23f_get_m22l_q(A,B)\
           (GAN_TEST_OP2(A,B,Gan_Matrix23_f,Gan_Matrix22_f),\
            (B)->xx=(A)->xx,(B)->xy=(A)->xy,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,B)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Extract right-hand column of 2x3 matrix.
 *
 * Extract right-hand column of 2x3 matrix \a A into 2-vector \a p.
 *
 * \return Pointer to result 2-vector \a p.
 */
GANDALF_API Gan_Vector2_f *gan_mat23f_get_v2r_q ( const Gan_Matrix23_f *A, Gan_Vector2_f *p );
#else
#define gan_mat23f_get_v2r_q(A,p)\
           (GAN_TEST_OP2(A,p,Gan_Matrix23_f,Gan_Vector2_f),\
            (p)->x=(A)->xz,(p)->y=(A)->yz,p)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixBuild
 * \{
 */

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Build 2x3 matrix from 2x2 matrix and column 2-vector.
 *
 * Build 2x3 matrix \a A from 2x2 matrix \a B and column 2-vector \a p,
 * which are respectively inserted in the left-hand and right-hand parts
 * of the 2x3 matrix. The arrangement is thus
 * \f[
 *    A = \left(\begin{array}{cc} B & p \end{array}\right)
 * \f]
 *
 * \return Pointer to result 2x3 matrix \a A.
 */
GANDALF_API Gan_Matrix23_f *gan_mat23f_set_parts_q ( Gan_Matrix23_f *A,
                                         const Gan_Matrix22_f *B, const Gan_Vector2_f *p );
#else
#define gan_mat23f_set_parts_q(A,B,p)\
           (GAN_TEST_OP3(A,B,p,\
                         Gan_Matrix23_f,Gan_Matrix22_f,Gan_Vector2_f),\
            (A)->xx=(B)->xx,(A)->xy=(B)->xy,(A)->xz=(p)->x,\
            (A)->yx=(B)->yx,(A)->yy=(B)->yy,(A)->yz=(p)->y,A)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix23_f gan_mat23f_fill_s ( float XX, float XY, float XZ,
                                   float YX, float YY, float YZ );
GANDALF_API Gan_Matrix22_f gan_mat23f_rmultm23T_s ( const Gan_Matrix23_f *A, const Gan_Matrix23_f *B );
GANDALF_API Gan_Vector2_f gan_mat23f_multv2h_s ( const Gan_Matrix23_f *A,
                                     const Gan_Vector2_f *p, float h );
GANDALF_API Gan_Bool gan_mat23hf_invert_q ( const Gan_Matrix23_f *A, float a,
                                Gan_Matrix23_f *B, float *b );
GANDALF_API Gan_Matrix23_f gan_mat23hf_invert_s ( const Gan_Matrix23_f *A, float a, float *b );
GANDALF_API void gan_mat23f_get_rows_s ( const Gan_Matrix23_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q );
GANDALF_API void gan_mat23f_get_cols_s ( const Gan_Matrix23_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q,
                             Gan_Vector2_f *r );
GANDALF_API Gan_Matrix22_f gan_mat23f_get_m22l_s ( const Gan_Matrix23_f *A );
GANDALF_API Gan_Vector2_f  gan_mat23f_get_v2r_s  ( const Gan_Matrix23_f *A );
GANDALF_API Gan_Matrix23_f gan_mat23f_set_parts_s ( const Gan_Matrix22_f *B, const Gan_Vector2_f *p );
GANDALF_API Gan_Matrix23_f *gan_mat23f_from_matf_q ( const Gan_Matrix_f *A, Gan_Matrix23_f *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X3MATF_H */

#define GAN_MATTYPE Gan_Matrix23_f
#define GAN_MATRIX_TYPE Gan_Matrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f32
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f32
#define GAN_VECTYPE1 Gan_Vector2_f
#define GAN_VECTYPE2 Gan_Vector3_f
#define GAN_MATTYPEL Gan_Matrix22_f
#define GAN_MATTYPER Gan_Matrix33_f
#define GAN_SQUMATTYPEL Gan_SquMatrix22_f
#define GAN_SQUMATTYPER Gan_SquMatrix33_f
#define GAN_MAT_FPRINT                     gan_mat23f_fprint
#define GAN_MAT_PRINT                      gan_mat23f_print
#define GAN_MAT_FSCANF                     gan_mat23f_fscanf
#define GAN_MAT_FWRITE                     gan_mat23f_fwrite
#define GAN_MAT_FREAD                      gan_mat23f_fread
#define GAN_MAT_ZERO_Q                     gan_mat23f_zero_q
#define GAN_MAT_ZERO_S                     gan_mat23f_zero_s
#define GAN_MAT_COPY_Q                     gan_mat23f_copy_q
#define GAN_MAT_COPY_S                     gan_mat23f_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat23f_scale_q
#define GAN_MAT_SCALE_I                    gan_mat23f_scale_i
#define GAN_MAT_SCALE_S                    gan_mat23f_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat23f_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat23f_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat23f_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat23f_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat23f_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat23f_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat23f_unit_q
#define GAN_MAT_UNIT_I                     gan_mat23f_unit_i
#define GAN_MAT_UNIT_S                     gan_mat23f_unit_s
#define GAN_MAT_ADD_Q                      gan_mat23f_add_q
#define GAN_MAT_ADD_I1                     gan_mat23f_add_i1
#define GAN_MAT_ADD_I2                     gan_mat23f_add_i2
#define GAN_MAT_INCREMENT                  gan_mat23f_increment
#define GAN_MAT_ADD_S                      gan_mat23f_add_s
#define GAN_MAT_SUB_Q                      gan_mat23f_sub_q
#define GAN_MAT_SUB_I1                     gan_mat23f_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat23f_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat23f_decrement
#define GAN_MAT_SUB_S                      gan_mat23f_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec23f_outer_q
#define GAN_VEC_OUTER_S                    gan_vec23f_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat23f_multv3_q
#define GAN_MAT_MULTV_S                    gan_mat23f_multv3_s
#define GAN_MATT_MULTV_Q                   gan_mat23Tf_multv2_q
#define GAN_MATT_MULTV_S                   gan_mat23Tf_multv2_s
#define GAN_MAT_LMULTM_Q                   gan_mat23f_lmultm22_q
#define GAN_MAT_LMULTM_S                   gan_mat23f_lmultm22_s
#define GAN_MAT_LMULTMT_Q                  gan_mat23f_lmultm22T_q
#define GAN_MAT_LMULTMT_S                  gan_mat23f_lmultm22T_s
#define GAN_MAT_RMULTM_Q                   gan_mat23f_rmultm33_q
#define GAN_MAT_RMULTM_S                   gan_mat23f_rmultm33_s
#define GAN_MAT_RMULTMT_Q                  gan_mat23f_rmultm33T_q
#define GAN_MAT_RMULTMT_S                  gan_mat23f_rmultm33T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat23f_lmultm23T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat23f_lmultm23T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat23f_rmultm23T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat23f_rmultm23T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat23f_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat23f_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat23f_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat23f_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat23f_lmults22_q
#define GAN_MAT_LMULTS_S                   gan_mat23f_lmults22_s
#define GAN_MAT_RMULTS_Q                   gan_mat23f_rmults33_q
#define GAN_MAT_RMULTS_S                   gan_mat23f_rmults33_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat22f_lrmultm23T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat22f_lrmultm23T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat33f_lrmultm23_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat33f_lrmultm23_s
#define GAN_MAT_LMULTL_Q                   gan_mat23f_lmultl22_q
#define GAN_MAT_LMULTL_S                   gan_mat23f_lmultl22_s
#define GAN_MAT_LMULTL_I                   gan_mat23f_lmultl22_i
#define GAN_MAT_LMULTLI_Q                  gan_mat23f_lmultl22I_q
#define GAN_MAT_LMULTLI_S                  gan_mat23f_lmultl22I_s
#define GAN_MAT_LMULTLI_I                  gan_mat23f_lmultl22I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat23f_lmultl22T_q
#define GAN_MAT_LMULTLT_S                  gan_mat23f_lmultl22T_s
#define GAN_MAT_LMULTLT_I                  gan_mat23f_lmultl22T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat23f_lmultl22IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat23f_lmultl22IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat23f_lmultl22IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat23f_rmultl33_q
#define GAN_MAT_RMULTL_S                   gan_mat23f_rmultl33_s
#define GAN_MAT_RMULTL_I                   gan_mat23f_rmultl33_i
#define GAN_MAT_RMULTLI_Q                  gan_mat23f_rmultl33I_q
#define GAN_MAT_RMULTLI_S                  gan_mat23f_rmultl33I_s
#define GAN_MAT_RMULTLI_I                  gan_mat23f_rmultl33I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat23f_rmultl33T_q
#define GAN_MAT_RMULTLT_S                  gan_mat23f_rmultl33T_s
#define GAN_MAT_RMULTLT_I                  gan_mat23f_rmultl33T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat23f_rmultl33IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat23f_rmultl33IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat23f_rmultl33IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat23f_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat23f_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat23f_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat23f_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat23f_from_matf_q
#define GAN_MAT_FROM_MAT_S                 gan_mat23f_from_matf_s

#ifndef _GAN_2X3MATF_H
#define _GAN_2X3MATF_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat23f_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix23_f),\
                             GAN_REP23_AS((A)->,=0.0,x,y,x,y,z),A)
#define gan_mat23f_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix23_f,Gan_Matrix23_f),\
                               GAN_REP23_AA_C((B)->,=(A)->),B)
#define gan_mat23f_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix23_f,Gan_Matrix23_f),\
                                  GAN_REP23_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat23f_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix23_f),\
                                GAN_REP23_AS_C((A)->,*=(a)),A)
#define gan_mat23f_divide_q(A,a,B) (GAN_TEST_OP2(A,B,\
                                                Gan_Matrix23_f,Gan_Matrix23_f),\
                                   (a)==0.0 ? NULL :\
                                   (GAN_REP23_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat23f_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix23_f),\
                                 (a)==0.0 ? NULL :\
                                 (GAN_REP23_AS_C((A)->,/=(a)),A))
#define gan_mat23f_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix23_f,Gan_Matrix23_f),\
                                 GAN_REP23_AA_C((B)->,=-(A)->),B)
#define gan_mat23f_negate_i(A) gan_mat23f_negate_q(A,A)
#define gan_mat23f_unit_i(A) gan_mat23f_unit_q(A,A)
#define gan_mat23f_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix23_f,\
                                                   Gan_Matrix23_f),\
                                GAN_REP23_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat23f_add_i1(A,B) gan_mat23f_add_q(A,B,A)
#define gan_mat23f_add_i2(A,B) gan_mat23f_add_q(A,B,B)
#define gan_mat23f_increment(A,B) gan_mat23f_add_i1(A,B)
#define gan_mat23f_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix23_f,\
                                                   Gan_Matrix23_f),\
                                GAN_REP23_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat23f_sub_i1(A,B) gan_mat23f_sub_q(A,B,A)
#define gan_mat23f_sub_i2(A,B) gan_mat23f_sub_q(A,B,B)
#define gan_mat23f_decrement(A,B) gan_mat23f_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec23f_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector2_f,Gan_Vector3_f,Gan_Matrix23_f),\
  GAN_REP3_ABC((A)->,=(p)->,*(q)->,xx,xy,xz,x,x,x,x,y,z),\
  GAN_REP3_ABC((A)->,=(p)->,*(q)->,yx,yy,yz,y,y,y,x,y,z),A)
 
/* matrix/vector multiply */
#define gan_mat23f_multv3_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix23_f,Gan_Vector3_f,Gan_Vector2_f),\
  GAN_MAT23F_MULT1D((q)->,(A)->,(p)->,x,y,x,y,z),q)
#define gan_mat23f_multv2h_q(A,p,h,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix23_f,Gan_Vector2_f,Gan_Vector2_f),\
  (q)->x = (A)->xx*(p)->x + (A)->xy*(p)->y + (A)->xz*(h),\
  (q)->y = (A)->yx*(p)->x + (A)->yy*(p)->y + (A)->yz*(h),q)
#define gan_mat23Tf_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix23_f,Gan_Vector2_f,Gan_Vector3_f),\
  GAN_MAT23TF_MULT1D((q)->,(A)->,(p)->,x,y,z,x,y),q)

/* matrix/matrix multiply */
#define gan_mat23f_lmultm22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix22_f,Gan_Matrix23_f),\
  assert((A)!=(C)),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_lmultm22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix22_f,Gan_Matrix23_f),\
  assert((A)!=(C)),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_rmultm33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix33_f,Gan_Matrix23_f),\
  assert((A)!=(C)),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx,zx),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy,zy),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xz,yz,xz,yz,zz),C)
#define gan_mat23f_rmultm33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix33_f,Gan_Matrix23_f),\
  assert((A)!=(C)),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,yz),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xz,yz,zx,zy,zz),C)
#define gan_mat23f_lmultm23T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix23_f,Gan_SquMatrix33_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT23TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx),\
  (C)->yy = GAN_REP2_OP_AA((A)->,*(B)->,xy,yy,+),\
  (C)->zy = GAN_REP2_OP_AB((A)->,*(B)->,xz,yz,xy,yy,+),\
  (C)->zz = GAN_REP2_OP_AA((A)->,*(B)->,xz,yz,+),C)
#define gan_mat23f_slmultT_q(A,C) gan_mat23f_lmultm23T_sym_q(A,A,C)
#define gan_mat23f_rmultm23T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix23_f,Gan_SquMatrix22_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz),\
  (C)->yy = GAN_REP3_OP_AA((A)->,*(B)->,yx,yy,yz,+),C)
#define gan_mat23f_srmultT_q(A,C) gan_mat23f_rmultm23T_sym_q(A,A,C)
#define gan_mat23f_lmults22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix22_f,Gan_Matrix23_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_rmults33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix33_f,Gan_Matrix23_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx,zx),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,zy),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xz,yz,zx,zy,zz),C)
#define gan_symmat22f_lrmultm23T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
          Gan_SquMatrix22_f,Gan_Matrix23_f,Gan_Matrix23_f,Gan_SquMatrix33_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xz,yz,xz,yz),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT23TF_MULT1D((D)->,(B)->,(C)->,xx,yx,zx,xx,yx),\
  (D)->yy = GAN_REP2_OP_AA((C)->,*(B)->,xy,yy,+),\
  (D)->zy = GAN_REP2_OP_AB((C)->,*(B)->,xz,yz,xy,yy,+),\
  (D)->zz = GAN_REP2_OP_AA((C)->,*(B)->,xz,yz,+),D)
#define gan_symmat33f_lrmultm23_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
          Gan_SquMatrix33_f,Gan_Matrix23_f,Gan_Matrix23_f,Gan_SquMatrix22_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT23F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx,zx),\
  GAN_MAT23F_MULT1D((C)->,(B)->,(A)->,xy,yy,yx,yy,zy),\
  GAN_MAT23F_MULT1D((C)->,(B)->,(A)->,xz,yz,zx,zy,zz),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT23F_MULT1D((D)->,(C)->,(B)->,xx,yx,xx,xy,xz),\
  (D)->yy = GAN_REP3_OP_AA((C)->,*(B)->,yx,yy,yz,+),D)
#define gan_mat23f_lmultl22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix22_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_lmultl22_i(A,B) gan_mat23f_lmultl22_q(A,B,A)
#define gan_mat23f_lmultl22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix22_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_lmultl22T_i(A,B) gan_mat23f_lmultl22T_q(A,B,A)
#define gan_mat23f_lmultl22I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix22_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_lmultl22I_i(A,B) gan_mat23f_lmultl22I_q(A,B,A)
#define gan_mat23f_lmultl22IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix22_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),C)
#define gan_mat23f_lmultl22IT_i(A,B) gan_mat23f_lmultl22IT_q(A,B,A)
#define gan_mat23f_rmultl33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix33_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),C)
#define gan_mat23f_rmultl33_i(A,B) gan_mat23f_rmultl33_q(A,B,A)
#define gan_mat23f_rmultl33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix33_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),C)
#define gan_mat23f_rmultl33T_i(A,B) gan_mat23f_rmultl33T_q(A,B,A)
#define gan_mat23f_rmultl33I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix33_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),C)
#define gan_mat23f_rmultl33I_i(A,B) gan_mat23f_rmultl33I_q(A,B,A)
#define gan_mat23f_rmultl33IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_SquMatrix33_f,Gan_Matrix23_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),C)
#define gan_mat23f_rmultl33IT_i(A,B) gan_mat23f_rmultl33IT_q(A,B,A)
#define gan_mat23f_rmultm23T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix23_f,Gan_Matrix23_f,Gan_Matrix22_f),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz),\
  GAN_MAT23F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,yz),C)

#define gan_mat23f_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix23_f),\
                        ((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz +\
                         (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz))
#define gan_mat23f_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix23_f), (float)\
                    sqrt((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz +\
                         (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X3MATF_H */
