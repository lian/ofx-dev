/**
 * File:          $RCSfile: 2x4mat_noc.h,v $
 * Module:        2x4 matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.24 $
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

#ifndef _GAN_2X4MAT_H

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
GANDALF_API Gan_Matrix24 *gan_mat24_fill_q ( Gan_Matrix24 *A,
                                 double XX, double XY, double XZ, double XW,
                                 double YX, double YY, double YZ, double YW );
#else
#define gan_mat24_fill_q(A,XX,XY,XZ,XW,YX,YY,YZ,YW)\
   (GAN_TEST_OP1(A,Gan_Matrix24),\
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
GANDALF_API Gan_Vector2 *gan_mat24_multv3h_q ( const Gan_Matrix24 *A, const Gan_Vector3 *p, double h,
                                   Gan_Vector2 *q );
#else
#define gan_mat24_multv3h_q(A,p,h,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix24,Gan_Vector3,Gan_Vector2),\
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
GANDALF_API void gan_mat24_get_rows_q ( const Gan_Matrix24 *A, Gan_Vector4 *p, Gan_Vector4 *q );
#else
#define gan_mat24_get_rows_q(A,p,q)\
           (GAN_TEST_OP3(A,p,q,Gan_Matrix24,Gan_Vector4,Gan_Vector4),\
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
GANDALF_API void gan_mat24_get_cols_q ( const Gan_Matrix24 *A, Gan_Vector2 *p, Gan_Vector2 *q,
                                                   Gan_Vector2 *r, Gan_Vector2 *s );
#else
#define gan_mat24_get_cols_q(A,p,q,r,s)\
           (GAN_TEST_OP5(A,p,q,r,s,Gan_Matrix24,\
                         Gan_Vector2,Gan_Vector2,Gan_Vector2,Gan_Vector2),\
            (p)->x=(A)->xx,(q)->x=(A)->xy,(r)->x=(A)->xz,(s)->x=(A)->xw,\
            (p)->y=(A)->yx,(q)->y=(A)->yy,(r)->y=(A)->yz,(s)->y=(A)->yw)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix24 gan_mat24_fill_s (
                          double XX, double XY, double XZ, double XW,
                          double YX, double YY, double YZ, double YW );
GANDALF_API Gan_Vector2 gan_mat24_multv3h_s ( const Gan_Matrix24 *A,
                                  const Gan_Vector3 *p, double h );
GANDALF_API void gan_mat24_get_rows_s ( const Gan_Matrix24 *A, Gan_Vector4 *p, Gan_Vector4 *q );
GANDALF_API void gan_mat24_get_cols_s ( const Gan_Matrix24 *A, Gan_Vector2 *p, Gan_Vector2 *q,
                                                   Gan_Vector2 *r, Gan_Vector2 *s );
GANDALF_API Gan_Matrix24 *gan_mat24_from_mat_q ( const Gan_Matrix *A, Gan_Matrix24 *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X4MAT_H */

#define GAN_MATTYPE Gan_Matrix24
#define GAN_MATRIX_TYPE Gan_Matrix
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix
#define GAN_VECTOR_TYPE Gan_Vector
#define GAN_MAT_ELEMENT_TYPE GAN_DOUBLE
#define GAN_REALTYPE double
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f64
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f64
#define GAN_VECTYPE1 Gan_Vector2
#define GAN_VECTYPE2 Gan_Vector4
#define GAN_MATTYPEL Gan_Matrix22
#define GAN_MATTYPER Gan_Matrix44
#define GAN_SQUMATTYPEL Gan_SquMatrix22
#define GAN_SQUMATTYPER Gan_SquMatrix44
#define GAN_MAT_FPRINT                     gan_mat24_fprint
#define GAN_MAT_PRINT                      gan_mat24_print
#define GAN_MAT_FSCANF                     gan_mat24_fscanf
#define GAN_MAT_FWRITE                     gan_mat24_fwrite
#define GAN_MAT_FREAD                      gan_mat24_fread
#define GAN_MAT_ZERO_Q                     gan_mat24_zero_q
#define GAN_MAT_ZERO_S                     gan_mat24_zero_s
#define GAN_MAT_COPY_Q                     gan_mat24_copy_q
#define GAN_MAT_COPY_S                     gan_mat24_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat24_scale_q
#define GAN_MAT_SCALE_I                    gan_mat24_scale_i
#define GAN_MAT_SCALE_S                    gan_mat24_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat24_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat24_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat24_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat24_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat24_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat24_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat24_unit_q
#define GAN_MAT_UNIT_I                     gan_mat24_unit_i
#define GAN_MAT_UNIT_S                     gan_mat24_unit_s
#define GAN_MAT_ADD_Q                      gan_mat24_add_q
#define GAN_MAT_ADD_I1                     gan_mat24_add_i1
#define GAN_MAT_ADD_I2                     gan_mat24_add_i2
#define GAN_MAT_INCREMENT                  gan_mat24_increment
#define GAN_MAT_ADD_S                      gan_mat24_add_s
#define GAN_MAT_SUB_Q                      gan_mat24_sub_q
#define GAN_MAT_SUB_I1                     gan_mat24_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat24_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat24_decrement
#define GAN_MAT_SUB_S                      gan_mat24_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec24_outer_q
#define GAN_VEC_OUTER_S                    gan_vec24_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat24_multv4_q
#define GAN_MAT_MULTV_S                    gan_mat24_multv4_s
#define GAN_MATT_MULTV_Q                   gan_mat24T_multv2_q
#define GAN_MATT_MULTV_S                   gan_mat24T_multv2_s
#define GAN_MAT_LMULTM_Q                   gan_mat24_lmultm22_q
#define GAN_MAT_LMULTM_S                   gan_mat24_lmultm22_s
#define GAN_MAT_LMULTMT_Q                  gan_mat24_lmultm22T_q
#define GAN_MAT_LMULTMT_S                  gan_mat24_lmultm22T_s
#define GAN_MAT_RMULTM_Q                   gan_mat24_rmultm44_q
#define GAN_MAT_RMULTM_S                   gan_mat24_rmultm44_s
#define GAN_MAT_RMULTMT_Q                  gan_mat24_rmultm44T_q
#define GAN_MAT_RMULTMT_S                  gan_mat24_rmultm44T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat24_lmultm24T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat24_lmultm24T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat24_rmultm24T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat24_rmultm24T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat24_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat24_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat24_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat24_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat24_lmults22_q
#define GAN_MAT_LMULTS_S                   gan_mat24_lmults22_s
#define GAN_MAT_RMULTS_Q                   gan_mat24_rmults44_q
#define GAN_MAT_RMULTS_S                   gan_mat24_rmults44_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat22_lrmultm24T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat22_lrmultm24T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat44_lrmultm24_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat44_lrmultm24_s
#define GAN_MAT_LMULTL_Q                   gan_mat24_lmultl22_q
#define GAN_MAT_LMULTL_S                   gan_mat24_lmultl22_s
#define GAN_MAT_LMULTL_I                   gan_mat24_lmultl22_i
#define GAN_MAT_LMULTLI_Q                  gan_mat24_lmultl22I_q
#define GAN_MAT_LMULTLI_S                  gan_mat24_lmultl22I_s
#define GAN_MAT_LMULTLI_I                  gan_mat24_lmultl22I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat24_lmultl22T_q
#define GAN_MAT_LMULTLT_S                  gan_mat24_lmultl22T_s
#define GAN_MAT_LMULTLT_I                  gan_mat24_lmultl22T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat24_lmultl22IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat24_lmultl22IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat24_lmultl22IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat24_rmultl44_q
#define GAN_MAT_RMULTL_S                   gan_mat24_rmultl44_s
#define GAN_MAT_RMULTL_I                   gan_mat24_rmultl44_i
#define GAN_MAT_RMULTLI_Q                  gan_mat24_rmultl44I_q
#define GAN_MAT_RMULTLI_S                  gan_mat24_rmultl44I_s
#define GAN_MAT_RMULTLI_I                  gan_mat24_rmultl44I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat24_rmultl44T_q
#define GAN_MAT_RMULTLT_S                  gan_mat24_rmultl44T_s
#define GAN_MAT_RMULTLT_I                  gan_mat24_rmultl44T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat24_rmultl44IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat24_rmultl44IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat24_rmultl44IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat24_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat24_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat24_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat24_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat24_from_mat_q
#define GAN_MAT_FROM_MAT_S                 gan_mat24_from_mat_s

#ifndef _GAN_2X4MAT_H
#define _GAN_2X4MAT_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat24_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix24),\
                             GAN_REP24_AS((A)->,=0.0,x,y,x,y,z,w),A)
#define gan_mat24_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix24,Gan_Matrix24),\
                               GAN_REP24_AA_C((B)->,=(A)->),B)
#define gan_mat24_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix24,Gan_Matrix24),\
                                  GAN_REP24_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat24_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix24),\
                                GAN_REP24_AS_C((A)->,*=(a)),A)
#define gan_mat24_divide_q(A,a,B) (GAN_TEST_OP2(A,B,\
                                                Gan_Matrix24,Gan_Matrix24),\
                                   (a)==0.0 ? NULL :\
                                   (GAN_REP24_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat24_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix24),\
                                 (a)==0.0 ? NULL :\
                                 (GAN_REP24_AS_C((A)->,/=(a)),A))
#define gan_mat24_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix24,Gan_Matrix24),\
                                 GAN_REP24_AA_C((B)->,=-(A)->),B)
#define gan_mat24_negate_i(A) gan_mat24_negate_q(A,A)
#define gan_mat24_unit_i(A) gan_mat24_unit_q(A,A)
#define gan_mat24_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix24,\
                                                   Gan_Matrix24),\
                                GAN_REP24_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat24_add_i1(A,B) gan_mat24_add_q(A,B,A)
#define gan_mat24_add_i2(A,B) gan_mat24_add_q(A,B,B)
#define gan_mat24_increment(A,B) gan_mat24_add_i1(A,B)
#define gan_mat24_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix24,\
                                                   Gan_Matrix24),\
                                GAN_REP24_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat24_sub_i1(A,B) gan_mat24_sub_q(A,B,A)
#define gan_mat24_sub_i2(A,B) gan_mat24_sub_q(A,B,B)
#define gan_mat24_decrement(A,B) gan_mat24_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec24_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector2,Gan_Vector4,Gan_Matrix24),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,xx,xy,xz,xw,x,x,x,x,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,yx,yy,yz,yw,y,y,y,y,x,y,z,w),A)
 
/* matrix/vector multiply */
#define gan_mat24_multv4_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix24,Gan_Vector4,Gan_Vector2),\
  GAN_MAT24_MULT1D((q)->,(A)->,(p)->,x,y,x,y,z,w),q)
#define gan_mat24T_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix24,Gan_Vector2,Gan_Vector4),\
  GAN_MAT24T_MULT1D((q)->,(A)->,(p)->,x,y,z,w,x,y),q)

/* matrix/matrix multiply */
#define gan_mat24_lmultm22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix22,Gan_Matrix24),\
  assert((A)!=(C)),\
  GAN_MAT22_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_MAT22_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_MAT22_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_lmultm22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix22,Gan_Matrix24),\
  assert((A)!=(C)),\
  GAN_MAT22T_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22T_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_MAT22T_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_MAT22T_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_rmultm44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix44,Gan_Matrix24),\
  assert((A)!=(C)),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx,zx,wx),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy,zy,wy),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xz,yz,xz,yz,zz,wz),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xw,yw,xw,yw,zw,ww),C)
#define gan_mat24_rmultm44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix44,Gan_Matrix24),\
  assert((A)!=(C)),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz,xw),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,yz,yw),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xz,yz,zx,zy,zz,zw),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xw,yw,wx,wy,wz,ww),C)
#define gan_mat24_lmultm24T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix24,Gan_SquMatrix44),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX44),\
  GAN_MAT24T_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx),\
  (C)->yy = GAN_REP2_OP_AA((A)->,*(B)->,xy,yy,+),\
  (C)->zy = GAN_REP2_OP_AB((A)->,*(B)->,xz,yz,xy,yy,+),\
  (C)->wy = GAN_REP2_OP_AB((A)->,*(B)->,xw,yw,xy,yy,+),\
  (C)->zz = GAN_REP2_OP_AA((A)->,*(B)->,xz,yz,+),\
  (C)->wz = GAN_REP2_OP_AB((A)->,*(B)->,xw,yw,xz,yz,+),\
  (C)->ww = GAN_REP2_OP_AA((A)->,*(B)->,xw,yw,+),C)
#define gan_mat24_slmultT_q(A,C) gan_mat24_lmultm24T_sym_q(A,A,C)
#define gan_mat24_rmultm24T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_Matrix24,Gan_SquMatrix22),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX22),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy,xz,xw),\
  (C)->yy = GAN_REP4_OP_AA((A)->,*(B)->,yx,yy,yz,yw,+),C)
#define gan_mat24_srmultT_q(A,C) gan_mat24_rmultm24T_sym_q(A,A,C)
#define gan_mat24_lmults22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix22,Gan_Matrix24),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX22),\
  GAN_SYM22_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_SYM22_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_SYM22_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_SYM22_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_rmults44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix44,Gan_Matrix24),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX44),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx,zx,wx),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy,zy,wy),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xz,yz,zx,zy,zz,wz),\
  GAN_MAT24_MULT1D((C)->,(A)->,(B)->,xw,yw,wx,wy,wz,ww),C)
#define gan_symmat22_lrmultm24T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix22,Gan_Matrix24,Gan_Matrix24,Gan_SquMatrix44),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX22),\
  GAN_SYM22_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx),\
  GAN_SYM22_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy),\
  GAN_SYM22_MULT1D((C)->,(A)->,(B)->,xz,yz,xz,yz),\
  GAN_SYM22_MULT1D((C)->,(A)->,(B)->,xw,yw,xw,yw),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX44),\
  GAN_MAT24T_MULT1D((D)->,(B)->,(C)->,xx,yx,zx,wx,xx,yx),\
  (D)->yy = GAN_REP2_OP_AA((C)->,*(B)->,xy,yy,+),\
  (D)->zy = GAN_REP2_OP_AB((C)->,*(B)->,xz,yz,xy,yy,+),\
  (D)->wy = GAN_REP2_OP_AB((C)->,*(B)->,xw,yw,xy,yy,+),\
  (D)->zz = GAN_REP2_OP_AA((C)->,*(B)->,xz,yz,+),\
  (D)->wz = GAN_REP2_OP_AB((C)->,*(B)->,xw,yw,xz,yz,+),\
  (D)->ww = GAN_REP2_OP_AA((C)->,*(B)->,xw,yw,+),D)
#define gan_symmat44_lrmultm24_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix44,Gan_Matrix24,Gan_Matrix24,Gan_SquMatrix22),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX44),\
  GAN_MAT24_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx,zx,wx),\
  GAN_MAT24_MULT1D((C)->,(B)->,(A)->,xy,yy,yx,yy,zy,wy),\
  GAN_MAT24_MULT1D((C)->,(B)->,(A)->,xz,yz,zx,zy,zz,wz),\
  GAN_MAT24_MULT1D((C)->,(B)->,(A)->,xw,yw,wx,wy,wz,ww),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX22),\
  GAN_MAT24_MULT1D((D)->,(C)->,(B)->,xx,yx,xx,xy,xz,xw),\
  (D)->yy = GAN_REP4_OP_AA((C)->,*(B)->,yx,yy,yz,yw,+),D)
#define gan_mat24_lmultl22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix22,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22),\
  GAN_LOW22_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_LOW22_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_LOW22_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_lmultl22_i(A,B) gan_mat24_lmultl22_q(A,B,A)
#define gan_mat24_lmultl22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix22,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22),\
  GAN_UPP22_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_UPP22_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_UPP22_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_lmultl22T_i(A,B) gan_mat24_lmultl22T_q(A,B,A)
#define gan_mat24_lmultl22I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix22,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_LOW22I_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22I_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_LOW22I_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_LOW22I_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_lmultl22I_i(A,B) gan_mat24_lmultl22I_q(A,B,A)
#define gan_mat24_lmultl22IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix22,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0),\
  GAN_UPP22I_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22I_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),\
  GAN_UPP22I_MULT1D((C)->,(B)->,(A)->,xz,yz,xz,yz),\
  GAN_UPP22I_MULT1D((C)->,(B)->,(A)->,xw,yw,xw,yw),C)
#define gan_mat24_lmultl22IT_i(A,B) gan_mat24_lmultl22IT_q(A,B,A)
#define gan_mat24_rmultl44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix44,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44),\
  GAN_UPP44_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24_rmultl44_i(A,B) gan_mat24_rmultl44_q(A,B,A)
#define gan_mat24_rmultl44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix44,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44),\
  GAN_LOW44_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24_rmultl44T_i(A,B) gan_mat24_rmultl44T_q(A,B,A)
#define gan_mat24_rmultl44I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix44,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_UPP44I_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44I_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24_rmultl44I_i(A,B) gan_mat24_rmultl44I_q(A,B,A)
#define gan_mat24_rmultl44IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix24,Gan_SquMatrix44,Gan_Matrix24),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44),\
  assert((B)->xx != 0.0 && (B)->yy != 0.0 && (B)->zz != 0.0),\
  GAN_LOW44I_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44I_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),C)
#define gan_mat24_rmultl44IT_i(A,B) gan_mat24_rmultl44IT_q(A,B,A)

#define gan_mat24_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix24),\
      ((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
       (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw))
#define gan_mat24_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix24),\
  sqrt((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
       (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X4MAT_H */
