/**
 * File:          $RCSfile: 2x4matf_noc.h,v $
 * Module:        2x4 matrices (single precision)
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

#ifndef _GAN_2X4MATF_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 2x4 matrix with values.
 *
 * Fill 2x4 matrix \a A with values:
 * \f[
 *     A = \left(\begin{array}{cccc} XX & XY & XZ & XW \\ YX & YY & YZ & YW
 *         \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix24_f *gan_mat24f_fill_q ( Gan_Matrix24_f *A,
                                    float XX, float XY, float XZ, float XW,
                                    float YX, float YY, float YZ, float YW );
#else
#define gan_mat24f_fill_q(A,XX,XY,XZ,XW,YX,YY,YZ,YW)\
   (GAN_TEST_OP1(A,Gan_Matrix24_f),\
    GAN_FREP24_A_C((A)->,=,(XX),(XY),(XZ),(XW),(YX),(YY),(YZ),(YW)),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

/**
 * \brief Macro: Multiply 2x4 matrix by homogeneous 3-vector.
 *
 * Multiply 2x4 matrix \a A by 3-vector \a p expanded to a homogeneous
 * 4-vector by adding third element \a h, in other words compute and
 * return 2-vector \a q where
 * \f[
 *    q = A \left(\begin{array}{c} p \\ h \end{array}\right)
 * \f]
 *
 * \return Pointer to the result 2-vector \a q.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector2_f *gan_mat24f_multv3h_q ( const Gan_Matrix24_f *A,
                                      const Gan_Vector3_f *p, float h,
                                      Gan_Vector2_f *q );
#else
#define gan_mat24f_multv3h_q(A,p,h,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix24_f,Gan_Vector3_f,Gan_Vector2_f),\
  (q)->x = (A)->xx*(p)->x + (A)->xy*(p)->y + (A)->xz*(p)->z + (A)->xw*(h),\
  (q)->y = (A)->yx*(p)->x + (A)->yy*(p)->y + (A)->yz*(p)->z + (A)->yw*(h),q)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extract rows of 2x4 matrix.
 *
 * Extract rows of 2x4 matrix \a A into 4-vectors \a p and \a q.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat24f_get_rows_q ( const Gan_Matrix24_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q );
#else
#define gan_mat24f_get_rows_q(A,p,q)\
           (GAN_TEST_OP3(A,p,q,Gan_Matrix24_f,Gan_Vector4_f,Gan_Vector4_f),\
            (p)->x=(A)->xx,(p)->y=(A)->xy,(p)->z=(A)->xz,(p)->w=(A)->xw,\
            (q)->x=(A)->yx,(q)->y=(A)->yy,(q)->z=(A)->yz,(q)->w=(A)->yw)
#endif

/**
 * \brief Macro: Extract columns of 2x4 matrix
 *
 * Extract columns of 2x4 matrix \a A into 2-vectors \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{cccc} p & q & r & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat24f_get_cols_q ( const Gan_Matrix24_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q,
                             Gan_Vector2_f *r, Gan_Vector2_f *s );
#else
#define gan_mat24f_get_cols_q(A,p,q,r,s)\
           (GAN_TEST_OP5(A,p,q,r,s,Gan_Matrix24_f,\
                     Gan_Vector2_f,Gan_Vector2_f,Gan_Vector2_f,Gan_Vector2_f),\
            (p)->x=(A)->xx,(q)->x=(A)->xy,(r)->x=(A)->xz,(s)->x=(A)->xw,\
            (p)->y=(A)->yx,(q)->y=(A)->yy,(r)->y=(A)->yz,(s)->y=(A)->yw)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix24_f gan_mat24f_fill_s ( float XX, float XY, float XZ, float XW,
                                   float YX, float YY, float YZ, float YW );
GANDALF_API Gan_Vector2_f gan_mat24f_multv3h_s ( const Gan_Matrix24_f *A,
                                     const Gan_Vector3_f *p, float h );
GANDALF_API void gan_mat24f_get_rows_s ( const Gan_Matrix24_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q );
GANDALF_API void gan_mat24f_get_cols_s ( const Gan_Matrix24_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q,
                             Gan_Vector2_f *r, Gan_Vector2_f *s );
GANDALF_API Gan_Matrix24_f *gan_mat24f_from_matf_q ( const Gan_Matrix_f *A, Gan_Matrix24_f *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X4MATF_H */

#define GAN_MATTYPE Gan_Matrix24_f
#define GAN_MATRIX_TYPE Gan_Matrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f32
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f32
#define GAN_VECTYPE1 Gan_Vector2_f
#define GAN_VECTYPE2 Gan_Vector4_f
#define GAN_MATTYPEL Gan_Matrix22_f
#define GAN_MATTYPER Gan_Matrix44_f
#define GAN_SQUMATTYPEL Gan_SquMatrix22_f
#define GAN_SQUMATTYPER Gan_SquMatrix44_f
#define GAN_MAT_FPRINT                     gan_mat24f_fprint
#define GAN_MAT_PRINT                      gan_mat24f_print
#define GAN_MAT_FSCANF                     gan_mat24f_fscanf
#define GAN_MAT_FWRITE                     gan_mat24f_fwrite
#define GAN_MAT_FREAD                      gan_mat24f_fread
#define GAN_MAT_ZERO_Q                     gan_mat24f_zero_q
#define GAN_MAT_ZERO_S                     gan_mat24f_zero_s
#define GAN_MAT_COPY_Q                     gan_mat24f_copy_q
#define GAN_MAT_COPY_S                     gan_mat24f_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat24f_scale_q
#define GAN_MAT_SCALE_I                    gan_mat24f_scale_i
#define GAN_MAT_SCALE_S                    gan_mat24f_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat24f_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat24f_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat24f_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat24f_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat24f_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat24f_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat24f_unit_q
#define GAN_MAT_UNIT_I                     gan_mat24f_unit_i
#define GAN_MAT_UNIT_S                     gan_mat24f_unit_s
#define GAN_MAT_ADD_Q                      gan_mat24f_add_q
#define GAN_MAT_ADD_I1                     gan_mat24f_add_i1
#define GAN_MAT_ADD_I2                     gan_mat24f_add_i2
#define GAN_MAT_INCREMENT                  gan_mat24f_increment
#define GAN_MAT_ADD_S                      gan_mat24f_add_s
#define GAN_MAT_SUB_Q                      gan_mat24f_sub_q
#define GAN_MAT_SUB_I1                     gan_mat24f_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat24f_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat24f_decrement
#define GAN_MAT_SUB_S                      gan_mat24f_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec24f_outer_q
#define GAN_VEC_OUTER_S                    gan_vec24f_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat24f_multv4_q
#define GAN_MAT_MULTV_S                    gan_mat24f_multv4_s
#define GAN_MATT_MULTV_Q                   gan_mat24Tf_multv2_q
#define GAN_MATT_MULTV_S                   gan_mat24Tf_multv2_s
#define GAN_MAT_LMULTM_Q                   gan_mat24f_lmultm22_q
#define GAN_MAT_LMULTM_S                   gan_mat24f_lmultm22_s
#define GAN_MAT_LMULTMT_Q                  gan_mat24f_lmultm22T_q
#define GAN_MAT_LMULTMT_S                  gan_mat24f_lmultm22T_s
#define GAN_MAT_RMULTM_Q                   gan_mat24f_rmultm44_q
#define GAN_MAT_RMULTM_S                   gan_mat24f_rmultm44_s
#define GAN_MAT_RMULTMT_Q                  gan_mat24f_rmultm44T_q
#define GAN_MAT_RMULTMT_S                  gan_mat24f_rmultm44T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat24f_lmultm24T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat24f_lmultm24T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat24f_rmultm24T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat24f_rmultm24T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat24f_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat24f_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat24f_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat24f_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat24f_lmults22_q
#define GAN_MAT_LMULTS_S                   gan_mat24f_lmults22_s
#define GAN_MAT_RMULTS_Q                   gan_mat24f_rmults44_q
#define GAN_MAT_RMULTS_S                   gan_mat24f_rmults44_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat22f_lrmultm24T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat22f_lrmultm24T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat44f_lrmultm24_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat44f_lrmultm24_s
#define GAN_MAT_LMULTL_Q                   gan_mat24f_lmultl22_q
#define GAN_MAT_LMULTL_S                   gan_mat24f_lmultl22_s
#define GAN_MAT_LMULTL_I                   gan_mat24f_lmultl22_i
#define GAN_MAT_LMULTLI_Q                  gan_mat24f_lmultl22I_q
#define GAN_MAT_LMULTLI_S                  gan_mat24f_lmultl22I_s
#define GAN_MAT_LMULTLI_I                  gan_mat24f_lmultl22I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat24f_lmultl22T_q
#define GAN_MAT_LMULTLT_S                  gan_mat24f_lmultl22T_s
#define GAN_MAT_LMULTLT_I                  gan_mat24f_lmultl22T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat24f_lmultl22IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat24f_lmultl22IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat24f_lmultl22IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat24f_rmultl44_q
#define GAN_MAT_RMULTL_S                   gan_mat24f_rmultl44_s
#define GAN_MAT_RMULTL_I                   gan_mat24f_rmultl44_i
#define GAN_MAT_RMULTLI_Q                  gan_mat24f_rmultl44I_q
#define GAN_MAT_RMULTLI_S                  gan_mat24f_rmultl44I_s
#define GAN_MAT_RMULTLI_I                  gan_mat24f_rmultl44I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat24f_rmultl44T_q
#define GAN_MAT_RMULTLT_S                  gan_mat24f_rmultl44T_s
#define GAN_MAT_RMULTLT_I                  gan_mat24f_rmultl44T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat24f_rmultl44IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat24f_rmultl44IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat24f_rmultl44IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat24f_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat24f_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat24f_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat24f_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat24f_from_matf_q
#define GAN_MAT_FROM_MAT_S                 gan_mat24f_from_matf_s

#ifndef _GAN_2X4MATF_H
#define _GAN_2X4MATF_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat24f_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix24_f),\
                             GAN_REP24_AS((A)->,=0.0,x,y,x,y,z,w),A)
#define gan_mat24f_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix24_f,Gan_Matrix24_f),\
                               GAN_REP24_AA_C((B)->,=(A)->),B)
#define gan_mat24f_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix24_f,Gan_Matrix24_f),\
                                  GAN_REP24_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat24f_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix24_f),\
                                GAN_REP24_AS_C((A)->,*=(a)),A)
#define gan_mat24f_divide_q(A,a,B) (GAN_TEST_OP2(A,B,\
                                                Gan_Matrix24_f,Gan_Matrix24_f),\
                                   (a)==0.0 ? NULL :\
                                   (GAN_REP24_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat24f_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix24_f),\
                                 (a)==0.0 ? NULL :\
                                 (GAN_REP24_AS_C((A)->,/=(a)),A))
#define gan_mat24f_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix24_f,Gan_Matrix24_f),\
                                 GAN_REP24_AA_C((B)->,=-(A)->),B)
#define gan_mat24f_negate_i(A) gan_mat24f_negate_q(A,A)
#define gan_mat24f_unit_i(A) gan_mat24f_unit_q(A,A)
#define gan_mat24f_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix24_f,\
                                                   Gan_Matrix24_f),\
                                GAN_REP24_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat24f_add_i1(A,B) gan_mat24f_add_q(A,B,A)
#define gan_mat24f_add_i2(A,B) gan_mat24f_add_q(A,B,B)
#define gan_mat24f_increment(A,B) gan_mat24f_add_i1(A,B)
#define gan_mat24f_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix24_f,\
                                                   Gan_Matrix24_f),\
                                GAN_REP24_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat24f_sub_i1(A,B) gan_mat24f_sub_q(A,B,A)
#define gan_mat24f_sub_i2(A,B) gan_mat24f_sub_q(A,B,B)
#define gan_mat24f_decrement(A,B) gan_mat24f_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec24f_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector2_f,Gan_Vector4_f,Gan_Matrix24_f),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,xx,xy,xz,xw,x,x,x,x,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,yx,yy,yz,yw,y,y,y,y,x,y,z,w),A)
 
/* matrix/vector multiply */
#define gan_mat24f_multv4_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix24_f,Gan_Vector4_f,Gan_Vector2_f),\
  GAN_MAT24F_MULT1D((q)->,(A)->,(p)->,x,y,x,y,z,w),q)
#define gan_mat24Tf_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix24_f,Gan_Vector2_f,Gan_Vector4_f),\
  GAN_MAT24TF_MULT1D((q)->,(A)->,(p)->,x,y,z,w,x,y),q)

/* matrix/matrix multiply */
#define gan_mat24f_lmultm22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix22_f,Gan_Matrix24_f),\
  assert((A)!=(C)),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_lmultm22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix22_f,Gan_Matrix24_f),\
  assert((A)!=(C)),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_rmultm44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix44_f,Gan_Matrix24_f),\
  assert((A)!=(C)),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx,zx,wx),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy,zy,wy),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xz,yz,xz,yz,zz,wz),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xw,yw,xw,yw,zw,ww),C)
#define gan_mat24f_rmultm44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix44_f,Gan_Matrix24_f),\
  assert((A)!=(C)),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz,xw),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,yz,yw),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xz,yz,zx,zy,zz,zw),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xw,yw,wx,wy,wz,ww),C)
#define gan_mat24f_lmultm24T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix24_f,Gan_SquMatrix44_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT24TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx),\
  (C)->yy = GAN_REP2_OP_AA((A)->,*(B)->,xy,yy,+),\
  (C)->zy = GAN_REP2_OP_AB((A)->,*(B)->,xz,yz,xy,yy,+),\
  (C)->wy = GAN_REP2_OP_AB((A)->,*(B)->,xw,yw,xy,yy,+),\
  (C)->zz = GAN_REP2_OP_AA((A)->,*(B)->,xz,yz,+),\
  (C)->wz = GAN_REP2_OP_AB((A)->,*(B)->,xw,yw,xz,yz,+),\
  (C)->ww = GAN_REP2_OP_AA((A)->,*(B)->,xw,yw,+),C)
#define gan_mat24f_slmultT_q(A,C) gan_mat24f_lmultm24T_sym_q(A,A,C)
#define gan_mat24f_rmultm24T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_Matrix24_f,Gan_SquMatrix22_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz,xw),\
  (C)->yy = GAN_REP4_OP_AA((A)->,*(B)->,yx,yy,yz,yw,+),C)
#define gan_mat24f_srmultT_q(A,C) gan_mat24f_rmultm24T_sym_q(A,A,C)
#define gan_mat24f_lmults22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix22_f,Gan_Matrix24_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_rmults44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix44_f,Gan_Matrix24_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx,zx,wx),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,zy,wy),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xz,yz,zx,zy,zz,wz),\
  GAN_MAT24F_MULT1D((C)->,(A)->,(B)->,xw,yw,wx,wy,wz,ww),C)
#define gan_symmat22f_lrmultm24T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
           Gan_SquMatrix22_f,Gan_Matrix24_f,Gan_Matrix24_f,Gan_SquMatrix44_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xz,yz,xz,yz),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xw,yw,xw,yw),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT24TF_MULT1D((D)->,(B)->,(C)->,xx,yx,zx,wx,xx,yx),\
  (D)->yy = GAN_REP2_OP_AA((C)->,*(B)->,xy,yy,+),\
  (D)->zy = GAN_REP2_OP_AB((C)->,*(B)->,xz,yz,xy,yy,+),\
  (D)->wy = GAN_REP2_OP_AB((C)->,*(B)->,xw,yw,xy,yy,+),\
  (D)->zz = GAN_REP2_OP_AA((C)->,*(B)->,xz,yz,+),\
  (D)->wz = GAN_REP2_OP_AB((C)->,*(B)->,xw,yw,xz,yz,+),\
  (D)->ww = GAN_REP2_OP_AA((C)->,*(B)->,xw,yw,+),D)
#define gan_symmat44f_lrmultm24_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
           Gan_SquMatrix44_f,Gan_Matrix24_f,Gan_Matrix24_f,Gan_SquMatrix22_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT24F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx,zx,wx),\
  GAN_MAT24F_MULT1D((C)->,(B)->,(A)->,xy,yy,yx,yy,zy,wy),\
  GAN_MAT24F_MULT1D((C)->,(B)->,(A)->,xz,yz,zx,zy,zz,wz),\
  GAN_MAT24F_MULT1D((C)->,(B)->,(A)->,xw,yw,wx,wy,wz,ww),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT24F_MULT1D((D)->,(C)->,(B)->,xx,yx,xx,xy,xz,xw),\
  (D)->yy = GAN_REP4_OP_AA((C)->,*(B)->,yx,yy,yz,yw,+),D)
#define gan_mat24f_lmultl22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix22_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_lmultl22_i(A,B) gan_mat24f_lmultl22_q(A,B,A)
#define gan_mat24f_lmultl22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix22_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_lmultl22T_i(A,B) gan_mat24f_lmultl22T_q(A,B,A)
#define gan_mat24f_lmultl22I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix22_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_lmultl22I_i(A,B) gan_mat24f_lmultl22I_q(A,B,A)
#define gan_mat24f_lmultl22IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix22_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24f_lmultl22IT_i(A,B) gan_mat24f_lmultl22IT_q(A,B,A)
#define gan_mat24f_rmultl44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix44_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24f_rmultl44_i(A,B) gan_mat24f_rmultl44_q(A,B,A)
#define gan_mat24f_rmultl44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix44_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24f_rmultl44T_i(A,B) gan_mat24f_rmultl44T_q(A,B,A)
#define gan_mat24f_rmultl44I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix44_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24f_rmultl44I_i(A,B) gan_mat24f_rmultl44I_q(A,B,A)
#define gan_mat24f_rmultl44IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24_f,Gan_SquMatrix44_f,Gan_Matrix24_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24f_rmultl44IT_i(A,B) gan_mat24f_rmultl44IT_q(A,B,A)

#define gan_mat24f_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix24_f),\
      ((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
       (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw))
#define gan_mat24f_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix24_f), (float)\
  sqrt((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
       (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X4MATF_H */
