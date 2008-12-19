/**
 * File:          $RCSfile: 4x4matf_noc.h,v $
 * Module:        4x4 matrices (single precision)
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

#ifndef _GAN_4X4MATF_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 4x4 matrix with values.
 *
 * Fill 4x4 matrix \a A with values:
 * \f[ A = \left(\begin{array}{cccc} XX & XY & XZ & XW \\ YX & YY & YZ & YW \\
 *                                   ZX & ZY & ZZ & ZW \\ WX & WY & WZ & WW
 *         \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix44_f *gan_mat44f_fill_q ( Gan_Matrix44_f *A,
                                    float XX, float XY, float XZ, float XW,
                                    float YX, float YY, float YZ, float YW,
                                    float ZX, float ZY, float ZZ, float ZW,
                                    float WX, float WY, float WZ, float WW );
#else
#define gan_mat44f_fill_q(A,XX,XY,XZ,XW,YX,YY,YZ,YW,ZX,ZY,ZZ,ZW,WX,WY,WZ,WW)\
           (GAN_TEST_OP1(A,Gan_Matrix44_f),\
            GAN_FREP44_A_C((A)->,=,(XX),(XY),(XZ),(XW),(YX),(YY),(YZ),(YW),(ZX),(ZY),(ZZ),(ZW),(WX),(WY),(WZ),(WW)),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extract rows of 4x4 matrix.
 *
 * Extract rows of 4x4 matrix \a A into 4-vectors \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top} \\ s^{\top}
 *     \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat44f_get_rows_q ( const Gan_Matrix44_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r, Gan_Vector4_f *s );
#else
#define gan_mat44f_get_rows_q(A,p,q,r,s)\
           (GAN_TEST_OP5(A,p,q,r,s,Gan_Matrix44_f,\
                         Gan_Vector4_f,Gan_Vector4_f,Gan_Vector4_f,Gan_Vector4_f),\
            ((p)->x=(A)->xx,(p)->y=(A)->xy,(p)->z=(A)->xz,(p)->w=(A)->xw,\
             (q)->x=(A)->yx,(q)->y=(A)->yy,(q)->z=(A)->yz,(q)->w=(A)->yw,\
             (r)->x=(A)->zx,(r)->y=(A)->zy,(r)->z=(A)->zz,(r)->w=(A)->zw,\
             (s)->x=(A)->wx,(s)->y=(A)->wy,(s)->z=(A)->wz,(s)->w=(A)->ww))
#endif

/**
 * \brief Macro: Extract columns of 4x4 matrix
 *
 * Extract columns of 4x4 matrix \a A into 4-vectors \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{cccc} p & q & r & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat44f_get_cols_q ( const Gan_Matrix44_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r, Gan_Vector4_f *s );
#else
#define gan_mat44f_get_cols_q(A,p,q,r,s)\
           (GAN_TEST_OP5(A,p,q,r,s,Gan_Matrix44_f,\
                         Gan_Vector4_f,Gan_Vector4_f,Gan_Vector4_f,Gan_Vector4_f),\
            ((p)->x=(A)->xx,(q)->x=(A)->xy,(r)->x=(A)->xz,(s)->x=(A)->xw,\
             (p)->y=(A)->yx,(q)->y=(A)->yy,(r)->y=(A)->yz,(s)->y=(A)->yw,\
             (p)->z=(A)->zx,(q)->z=(A)->zy,(r)->z=(A)->zz,(s)->z=(A)->zw,\
             (p)->w=(A)->wx,(q)->w=(A)->wy,(r)->w=(A)->wz,(s)->w=(A)->ww))
#endif

/**
 * \brief Macro: Extract top-left 3x3 part of 4x4 matrix.
 *
 * Extract top-left 3x3 part of 4x4 matrix \a A into 3x3 matrix \a B.
 *
 * \return Pointer to 3x3 matrix \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat44f_get_m33tl_q ( const Gan_Matrix44_f *A, Gan_Matrix33_f *B );
#else
#define gan_mat44f_get_m33tl_q(A,B)\
           (GAN_TEST_OP2(A,B,Gan_Matrix44_f,Gan_Matrix33_f),\
            (B)->xx=(A)->xx,(B)->xy=(A)->xy,(B)->xz=(A)->xz,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,(B)->yz=(A)->yz,\
            (B)->zx=(A)->zx,(B)->zy=(A)->zy,(B)->zz=(A)->zz,B)
#endif

/**
 * \brief Macro: Extract top part of right hand column of 4x4 matrix.
 *
 * Extract top-right column of 4x4 matrix \a A into 3-vector \a p.
 *
 * \return Pointer to result 3-vector \a p.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector3_f *gan_mat44f_get_v3tr_q ( const Gan_Matrix44_f *A, Gan_Vector3_f *p );
#else
#define gan_mat44f_get_v3tr_q(A,p)\
           (GAN_TEST_OP2(A,p,Gan_Matrix44_f,Gan_Vector3_f),\
            (p)->x=(A)->xw,(p)->y=(A)->yw,(p)->z=(A)->zw,p)
#endif

/**
 * \brief Macro: Extract parts of 4x4 matrix.
 *
 * Extract top-left 3x3 part, top-right 3x1 part, bottom-left 1x3 part and
 * bottom-right element of 4x4 matrix \a A into 3x3 matrix \a B,
 * column 3-vector \a p, row 3-vector \a q and scalar pointer \a s.
 * The arrangement is
 * \f[
 *   A = \left(\begin{array}{cc} B & p \\ q^{\top} & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat44f_get_parts_q ( const Gan_Matrix44_f *A, Gan_Matrix33_f *B,
                              Gan_Vector3_f *p, Gan_Vector3_f *q, float *s );
#else
#define gan_mat44f_get_parts_q(A,B,p,q,s)\
           (GAN_TEST_OP4(A,B,p,q,\
                         Gan_Matrix44_f,Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f),\
            (B)->xx=(A)->xx,(B)->xy=(A)->xy,(B)->xz=(A)->xz,(p)->x=(A)->xw,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,(B)->yz=(A)->yz,(p)->y=(A)->yw,\
            (B)->zx=(A)->zx,(B)->zy=(A)->zy,(B)->zz=(A)->zz,(p)->z=(A)->zw,\
            (q)->x=(A)->wx,(q)->y=(A)->wy,(q)->z=(A)->wz,*(s)=(A)->ww)
#endif

/**
 * \brief Macro: Extract 2x2 block parts of 4x4 matrix.
 *
 * Extract top-left, top-right, bottom-left bottom-right blocks of 4x4
 * matrix \a M into 2x2 matrices \a A, \a B, \a C and \a D.
 * The arrangement is
 * \f[
 *   M = \left(\begin{array}{cc} A & B \\ C & D \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat44f_get_blocks_q ( const Gan_Matrix44_f *M,
                               Gan_Matrix22_f *A, Gan_Matrix22_f *B,
                               Gan_Matrix22_f *C, Gan_Matrix22_f *D );
#else
#define gan_mat44f_get_blocks_q(M,A,B,C,D)\
           (GAN_TEST_OP5(M,A,B,C,D,\
                         Gan_Matrix44_f,Gan_Matrix22_f,Gan_Matrix22_f,\
                                      Gan_Matrix22_f,Gan_Matrix22_f),\
            (A)->xx=(M)->xx,(A)->xy=(M)->xy,(B)->xx=(M)->xz,(B)->xy=(M)->xw,\
            (A)->yx=(M)->yx,(A)->yy=(M)->yy,(B)->yx=(M)->yz,(B)->yy=(M)->yw,\
            (C)->xx=(M)->zx,(C)->xy=(M)->zy,(D)->xx=(M)->zz,(D)->xy=(M)->zw,\
            (C)->yx=(M)->wx,(C)->yy=(M)->wy,(D)->yx=(M)->wz,(D)->yy=(M)->ww)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixBuild
 * \{
 */

/**
 * \brief Macro: Build a 4x4 matrix from parts.
 *
 * Build 4x4 matrix from 3x3 matrix \a B, column 3-vector \a p,
 * row 3-vector \a q and scalar \a s, which are respectively inserted
 * in the top-left, top-right, bottom-left and bottom-right parts of \a A.
 * The arrangement of the matrix is
 * \f[
 *    \left(\begin{array}{cc} B & p \\ q^{\top} & s \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix44_f *gan_mat44f_set_parts_q ( Gan_Matrix44_f *A,
                                         const Gan_Matrix33_f *B, const Gan_Vector3_f *p,
                                         const Gan_Vector3_f *q, float s );
#else
#define gan_mat44f_set_parts_q(A,B,p,q,s)\
           (GAN_TEST_OP4(A,B,p,q,\
                         Gan_Matrix44_f,Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f),\
            (A)->xx=(B)->xx,(A)->xy=(B)->xy,(A)->xz=(B)->xz,(A)->xw=(p)->x,\
            (A)->yx=(B)->yx,(A)->yy=(B)->yy,(A)->yz=(B)->yz,(A)->yw=(p)->y,\
            (A)->zx=(B)->zx,(A)->zy=(B)->zy,(A)->zz=(B)->zz,(A)->zw=(p)->z,\
            (A)->wx=(q)->x,(A)->wy=(q)->y,(A)->wz=(q)->z,(A)->ww=(s),A)
#endif

/**
 * \brief Macro: Build a 4x4 matrix from 2x2 blocks.
 *
 * Build 4x4 matrix \a M from 2x2 matrix blocks \a A, \a B, \a C and \a D,
 * which are respectively inserted in the top-left, top-right, bottom-left
 * and bottom-right parts of the 4x4 matrix.
 * The arrangement is
 * \f[
 *   M = \left(\begin{array}{cc} A & B \\ C & D \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a M.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix44_f *gan_mat44f_set_blocks_q ( Gan_Matrix44_f *M,
                                          const Gan_Matrix22_f *A, const Gan_Matrix22_f *B,
                                          const Gan_Matrix22_f *C, const Gan_Matrix22_f *D );
#else
#define gan_mat44f_set_blocks_q(M,A,B,C,D)\
           (GAN_TEST_OP5(M,A,B,C,D,\
                         Gan_Matrix44_f,Gan_Matrix22_f,Gan_Matrix22_f,\
                                      Gan_Matrix22_f,Gan_Matrix22_f),\
            (M)->xx=(A)->xx,(M)->xy=(A)->xy,(M)->xz=(B)->xx,(M)->xw=(B)->xy,\
            (M)->yx=(A)->yx,(M)->yy=(A)->yy,(M)->yz=(B)->yx,(M)->yw=(B)->yy,\
            (M)->zx=(C)->xx,(M)->zy=(C)->xy,(M)->zz=(D)->xx,(M)->zw=(D)->xy,\
            (M)->wx=(C)->yx,(M)->wy=(C)->yy,(M)->wz=(D)->yx,(M)->ww=(D)->yy,M)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix44_f gan_mat44f_fill_s ( float XX, float XY, float XZ, float XW,
                                   float YX, float YY, float YZ, float YW,
                                   float ZX, float ZY, float ZZ, float ZW,
                                   float WX, float WY, float WZ, float WW );
GANDALF_API Gan_Vector3_f *gan_mat44f_multv3h_q ( const Gan_Matrix44_f *A,
                                      const Gan_Vector3_f *p, float h,
                                      Gan_Vector3_f *q );
GANDALF_API Gan_Vector3_f gan_mat44f_multv3h_s ( const Gan_Matrix44_f *A,
                                     const Gan_Vector3_f *p, float h);
GANDALF_API void gan_mat44f_get_rows_s ( const Gan_Matrix44_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r, Gan_Vector4_f *s );
GANDALF_API void gan_mat44f_get_cols_s ( const Gan_Matrix44_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r, Gan_Vector4_f *s );
GANDALF_API Gan_Matrix33_f gan_mat44f_get_m33tl_s ( const Gan_Matrix44_f *A );
GANDALF_API Gan_Vector3_f  gan_mat44f_get_v3tr_s  ( const Gan_Matrix44_f *A );
GANDALF_API void gan_mat44f_get_parts_s ( const Gan_Matrix44_f *A, Gan_Matrix33_f *B,
                              Gan_Vector3_f *p, Gan_Vector3_f *q, float *s );
GANDALF_API void gan_mat44f_get_blocks_s ( const Gan_Matrix44_f *M,
                               Gan_Matrix22_f *A, Gan_Matrix22_f *B,
                               Gan_Matrix22_f *C, Gan_Matrix22_f *D );
GANDALF_API Gan_Matrix44_f gan_mat44f_set_parts_s ( Gan_Matrix33_f *B,
                                        const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                        float s );
GANDALF_API Gan_Matrix44_f gan_mat44f_set_blocks_s ( const Gan_Matrix22_f *A, const Gan_Matrix22_f *B,
                                         const Gan_Matrix22_f *C, const Gan_Matrix22_f *D);
GANDALF_API Gan_Matrix44_f *gan_mat44f_from_matf_q ( const Gan_Matrix_f *A, Gan_Matrix44_f *B );
GANDALF_API Gan_Matrix44_f *gan_mat44f_from_squmatf_q ( const Gan_SquMatrix_f *A,
                                            Gan_Matrix44_f *B );
GANDALF_API Gan_SquMatrix44_f *gan_squmat44f_from_squmatf_q ( const Gan_SquMatrix_f *A,
                                                  Gan_SquMatrix44_f *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_4X4MATF_H */

#define GAN_MATTYPE Gan_Matrix44_f
#define GAN_MATRIX_TYPE Gan_Matrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f32
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f32
#define GAN_VECTYPE1 Gan_Vector4_f
#define GAN_VECTYPE2 Gan_Vector4_f
#define GAN_MATTYPEL Gan_Matrix44_f
#define GAN_MATTYPER Gan_Matrix44_f
#define GAN_SQUMATTYPEL Gan_SquMatrix44_f
#define GAN_SQUMATTYPER Gan_SquMatrix44_f
#define GAN_MAT_FPRINT                     gan_mat44f_fprint
#define GAN_MAT_PRINT                      gan_mat44f_print
#define GAN_MAT_FSCANF                     gan_mat44f_fscanf
#define GAN_MAT_FWRITE                     gan_mat44f_fwrite
#define GAN_MAT_FREAD                      gan_mat44f_fread
#define GAN_MAT_ZERO_Q                     gan_mat44f_zero_q
#define GAN_MAT_ZERO_S                     gan_mat44f_zero_s
#define GAN_MAT_COPY_Q                     gan_mat44f_copy_q
#define GAN_MAT_COPY_S                     gan_mat44f_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat44f_scale_q
#define GAN_MAT_SCALE_I                    gan_mat44f_scale_i
#define GAN_MAT_SCALE_S                    gan_mat44f_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat44f_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat44f_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat44f_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat44f_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat44f_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat44f_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat44f_unit_q
#define GAN_MAT_UNIT_I                     gan_mat44f_unit_i
#define GAN_MAT_UNIT_S                     gan_mat44f_unit_s
#define GAN_MAT_ADD_Q                      gan_mat44f_add_q
#define GAN_MAT_ADD_I1                     gan_mat44f_add_i1
#define GAN_MAT_ADD_I2                     gan_mat44f_add_i2
#define GAN_MAT_INCREMENT                  gan_mat44f_increment
#define GAN_MAT_ADD_S                      gan_mat44f_add_s
#define GAN_MAT_SUB_Q                      gan_mat44f_sub_q
#define GAN_MAT_SUB_I1                     gan_mat44f_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat44f_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat44f_decrement
#define GAN_MAT_SUB_S                      gan_mat44f_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec44f_outer_q
#define GAN_VEC_OUTER_S                    gan_vec44f_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat44f_multv4_q
#define GAN_MAT_MULTV_S                    gan_mat44f_multv4_s
#define GAN_MATT_MULTV_Q                   gan_mat44Tf_multv4_q
#define GAN_MATT_MULTV_S                   gan_mat44Tf_multv4_s
#define GAN_MAT_LMULTMT_Q                  gan_mat44f_lmultm44T_q
#define GAN_MAT_LMULTMT_S                  gan_mat44f_lmultm44T_s
#define GAN_MAT_RMULTM_Q                   gan_mat44f_rmultm44_q
#define GAN_MAT_RMULTM_S                   gan_mat44f_rmultm44_s
#define GAN_MAT_RMULTMT_Q                  gan_mat44f_rmultm44T_q
#define GAN_MAT_RMULTMT_S                  gan_mat44f_rmultm44T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat44f_lmultm44T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat44f_lmultm44T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat44f_rmultm44T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat44f_rmultm44T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat44f_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat44f_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat44f_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat44f_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat44f_lmults44_q
#define GAN_MAT_LMULTS_S                   gan_mat44f_lmults44_s
#define GAN_MAT_RMULTS_Q                   gan_mat44f_rmults44_q
#define GAN_MAT_RMULTS_S                   gan_mat44f_rmults44_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat44f_lrmultm44T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat44f_lrmultm44T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat44f_lrmultm44_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat44f_lrmultm44_s
#define GAN_MAT_LMULTL_Q                   gan_mat44f_lmultl44_q
#define GAN_MAT_LMULTL_S                   gan_mat44f_lmultl44_s
#define GAN_MAT_LMULTL_I                   gan_mat44f_lmultl44_i
#define GAN_MAT_LMULTLI_Q                  gan_mat44f_lmultl44I_q
#define GAN_MAT_LMULTLI_S                  gan_mat44f_lmultl44I_s
#define GAN_MAT_LMULTLI_I                  gan_mat44f_lmultl44I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat44f_lmultl44T_q
#define GAN_MAT_LMULTLT_S                  gan_mat44f_lmultl44T_s
#define GAN_MAT_LMULTLT_I                  gan_mat44f_lmultl44T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat44f_lmultl44IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat44f_lmultl44IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat44f_lmultl44IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat44f_rmultl44_q
#define GAN_MAT_RMULTL_S                   gan_mat44f_rmultl44_s
#define GAN_MAT_RMULTL_I                   gan_mat44f_rmultl44_i
#define GAN_MAT_RMULTLI_Q                  gan_mat44f_rmultl44I_q
#define GAN_MAT_RMULTLI_S                  gan_mat44f_rmultl44I_s
#define GAN_MAT_RMULTLI_I                  gan_mat44f_rmultl44I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat44f_rmultl44T_q
#define GAN_MAT_RMULTLT_S                  gan_mat44f_rmultl44T_s
#define GAN_MAT_RMULTLT_I                  gan_mat44f_rmultl44T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat44f_rmultl44IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat44f_rmultl44IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat44f_rmultl44IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat44f_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat44f_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat44f_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat44f_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat44f_from_matf_q
#define GAN_MAT_FROM_MAT_S                 gan_mat44f_from_matf_s
#define GAN_MAT_FROM_SQUMAT_Q              gan_mat44f_from_squmatf_q
#define GAN_MAT_FROM_SQUMAT_S              gan_mat44f_from_squmatf_s
#define GAN_SQUMAT_FROM_SQUMAT_Q           gan_squmat44f_from_squmatf_q
#define GAN_SQUMAT_FROM_SQUMAT_S           gan_squmat44f_from_squmatf_s

#define GAN_SQUMAT_IDENT_Q    gan_mat44f_ident_q
#define GAN_SQUMAT_IDENT_S    gan_mat44f_ident_s
#define GAN_SQUMAT_TPOSE_Q    gan_mat44f_tpose_q
#define GAN_SQUMAT_TPOSE_S    gan_mat44f_tpose_s
#define GAN_SQUMAT_TPOSE_I    gan_mat44f_tpose_i
#define GAN_MAT_SADDT_Q       gan_mat44f_saddT_q
#define GAN_MAT_SADDT_S       gan_mat44f_saddT_s
#define GAN_SQUMAT_INVERT     gan_mat44f_invert
#define GAN_SQUMAT_INVERT_Q   gan_mat44f_invert_q
#define GAN_SQUMAT_INVERT_S   gan_mat44f_invert_s
#define GAN_SQUMAT_INVERT_I   gan_mat44f_invert_i
#define GAN_SQUMAT_ADJOINT_Q  gan_mat44f_adjoint_q
#define GAN_SQUMAT_ADJOINT_S  gan_mat44f_adjoint_s
#define GAN_SQUMAT_ADJOINTT_Q gan_mat44f_adjointT_q
#define GAN_SQUMAT_ADJOINTT_S gan_mat44f_adjointT_s
#define GAN_SQUMAT_DET_Q      gan_mat44f_det_q
#define GAN_SQUMAT_DET_S      gan_mat44f_det_s
#define GAN_SQUMAT_TRACE_Q    gan_mat44f_trace_q
#define GAN_SQUMAT_TRACE_S    gan_mat44f_trace_s

#ifndef _GAN_4X4MATF_H
#define _GAN_4X4MATF_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat44f_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix44_f),\
                             GAN_REP44_AS((A)->,=0.0F,x,y,z,w,x,y,z,w),A)
#define gan_mat44f_ident_q(A) gan_mat44f_fill_q(A,1.0F,0.0F,0.0F,0.0F,0.0F,1.0F,0.0F,0.0F,0.0F,0.0F,1.0F,0.0F,0.0F,0.0F,0.0F,1.0F)
#define gan_mat44f_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix44_f,Gan_Matrix44_f),\
                               GAN_REP44_AA_C((B)->,=(A)->),B)
#define gan_mat44f_tpose_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix44_f,Gan_Matrix44_f),\
                                (A)==(B)?gan_mat44f_tpose_i(A):\
                                         (GAN_REP44_AAT_C((B)->,=(A)->),B),B)
#define gan_mat44f_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix44_f,Gan_Matrix44_f),\
                                  GAN_REP44_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat44f_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix44_f),\
                                GAN_REP44_AS_C((A)->,*=(a)),A)
#define gan_mat44f_divide_q(A,a,B) (GAN_TEST_OP2(A,B,\
                                                Gan_Matrix44_f,Gan_Matrix44_f),\
                                   (a)==0.0F ? NULL :\
                                   (GAN_REP44_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat44f_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix44_f),\
                                 (a)==0.0F ? NULL :\
                                 (GAN_REP44_AS_C((A)->,/=(a)),A))
#define gan_mat44f_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix44_f,Gan_Matrix44_f),\
                                 GAN_REP44_AA_C((B)->,=-(A)->),B)
#define gan_mat44f_negate_i(A) gan_mat44f_negate_q(A,A)
#define gan_mat44f_unit_i(A) gan_mat44f_unit_q(A,A)
#define gan_mat44f_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,\
                                                   Gan_Matrix44_f),\
                                GAN_REP44_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat44f_add_i1(A,B) gan_mat44f_add_q(A,B,A)
#define gan_mat44f_add_i2(A,B) gan_mat44f_add_q(A,B,B)
#define gan_mat44f_increment(A,B) gan_mat44f_add_i1(A,B)
#define gan_mat44f_saddT_q(A,B)\
 (GAN_TEST_OP2(A,B,Gan_Matrix44_f,Gan_SquMatrix44_f),\
  gan_eval((B)->type = GAN_SYMMETRIC_MATRIX44_F),\
  (B)->xx = 2.0F*(A)->xx,\
  (B)->yx = (A)->xy+(A)->yx, (B)->yy = 2.0F*(A)->yy,\
  (B)->zx = (A)->xz+(A)->zx, (B)->zy = (A)->yz+(A)->zy, (B)->zz = 2.0F*(A)->zz,\
  (B)->wx = (A)->xw+(A)->wx, (B)->wy = (A)->yw+(A)->wy, (B)->wz = (A)->zw+(A)->wz, (B)->ww = 2.0F*(A)->ww,B)
#define gan_mat44f_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,\
                                                   Gan_Matrix44_f),\
                                GAN_REP44_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat44f_sub_i1(A,B) gan_mat44f_sub_q(A,B,A)
#define gan_mat44f_sub_i2(A,B) gan_mat44f_sub_q(A,B,B)
#define gan_mat44f_decrement(A,B) gan_mat44f_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec44f_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector4_f,Gan_Vector4_f,Gan_Matrix44_f),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,xx,xy,xz,xw,x,x,x,x,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,yx,yy,yz,yw,y,y,y,y,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,zx,zy,zz,zw,z,z,z,z,x,y,z,w),\
  GAN_REP4_ABC((A)->,=(p)->,*(q)->,wx,wy,wz,ww,w,w,w,w,x,y,z,w),A)
 
/* matrix/vector multiply */
#define gan_mat44f_multv4_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix44_f,Gan_Vector4_f,Gan_Vector4_f),\
  assert((p)!=(q)),\
  GAN_MAT44F_MULT1D((q)->,(A)->,(p)->,x,y,z,w,x,y,z,w),q)
#define gan_mat44Tf_multv4_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix44_f,Gan_Vector4_f,Gan_Vector4_f),\
  assert((p)!=(q)),\
  GAN_MAT44TF_MULT1D((q)->,(A)->,(p)->,x,y,z,w,x,y,z,w),q)

/* matrix/matrix multiply */
#define gan_mat44f_lmultm44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,Gan_Matrix44_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT44TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_MAT44TF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_MAT44TF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_MAT44TF_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_rmultm44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,Gan_Matrix44_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_rmultm44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,Gan_Matrix44_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,wx,xx,xy,xz,xw),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,wy,yx,yy,yz,yw),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,wz,zx,zy,zz,zw),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,ww,wx,wy,wz,ww),C)
#define gan_mat44f_lmultm44T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,Gan_SquMatrix44_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT44TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  (C)->yy = GAN_REP4_OP_AA((A)->,*(B)->,xy,yy,zy,wy,+),\
  (C)->zy = GAN_REP4_OP_AB((A)->,*(B)->,xz,yz,zz,wz,xy,yy,zy,wy,+),\
  (C)->wy = GAN_REP4_OP_AB((A)->,*(B)->,xw,yw,zw,ww,xy,yy,zy,wy,+),\
  (C)->zz = GAN_REP4_OP_AA((A)->,*(B)->,xz,yz,zz,wz,+),\
  (C)->wz = GAN_REP4_OP_AB((A)->,*(B)->,xw,yw,zw,ww,xz,yz,zz,wz,+),\
  (C)->ww = GAN_REP4_OP_AA((A)->,*(B)->,xw,yw,zw,ww,+),C)
#define gan_mat44f_slmultT_q(A,C) gan_mat44f_lmultm44T_sym_q(A,A,C)
#define gan_mat44f_rmultm44T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_Matrix44_f,Gan_SquMatrix44_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,wx,xx,xy,xz,xw),\
  (C)->yy = GAN_REP4_OP_AA((A)->,*(B)->,yx,yy,yz,yw,+),\
  (C)->zy = GAN_REP4_OP_AB((A)->,*(B)->,zx,zy,zz,zw,yx,yy,yz,yw,+),\
  (C)->wy = GAN_REP4_OP_AB((A)->,*(B)->,wx,wy,wz,ww,yx,yy,yz,yw,+),\
  (C)->zz = GAN_REP4_OP_AA((A)->,*(B)->,zx,zy,zz,zw,+),\
  (C)->wz = GAN_REP4_OP_AB((A)->,*(B)->,wx,wy,wz,ww,zx,zy,zz,zw,+),\
  (C)->ww = GAN_REP4_OP_AA((A)->,*(B)->,wx,wy,wz,ww,+),C)
#define gan_mat44f_srmultT_q(A,C) gan_mat44f_rmultm44T_sym_q(A,A,C)
#define gan_mat44f_lmults44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_SYM44F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_SYM44F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_SYM44F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_SYM44F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_rmults44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,wy,yx,yy,zy,wy),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,wz,zx,zy,zz,wz),\
  GAN_MAT44F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,ww,wx,wy,wz,ww),C)
#define gan_symmat44f_lrmultm44T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix44_f,Gan_Matrix44_f,Gan_Matrix44_f,Gan_SquMatrix44_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_SYM44F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_SYM44F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_SYM44F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_SYM44F_MULT1D((C)->,(A)->,(B)->,xw,yw,zw,ww,xw,yw,zw,ww),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT44TF_MULT1D((D)->,(B)->,(C)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  (D)->yy = GAN_REP4_OP_AA((C)->,*(B)->,xy,yy,zy,wy,+),\
  (D)->zy = GAN_REP4_OP_AB((C)->,*(B)->,xz,yz,zz,wz,xy,yy,zy,wy,+),\
  (D)->wy = GAN_REP4_OP_AB((C)->,*(B)->,xw,yw,zw,ww,xy,yy,zy,wy,+),\
  (D)->zz = GAN_REP4_OP_AA((C)->,*(B)->,xz,yz,zz,wz,+),\
  (D)->wz = GAN_REP4_OP_AB((C)->,*(B)->,xw,yw,zw,ww,xz,yz,zz,wz,+),\
  (D)->ww = GAN_REP4_OP_AA((C)->,*(B)->,xw,yw,zw,ww,+),D)
#define gan_symmat44f_lrmultm44_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix44_f,Gan_Matrix44_f,Gan_Matrix44_f,Gan_SquMatrix44_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT44F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_MAT44F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,yx,yy,zy,wy),\
  GAN_MAT44F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,zx,zy,zz,wz),\
  GAN_MAT44F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,wx,wy,wz,ww),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX44_F),\
  GAN_MAT44F_MULT1D((D)->,(C)->,(B)->,xx,yx,zx,wx,xx,xy,xz,xw),\
  (D)->yy = GAN_REP4_OP_AA((C)->,*(B)->,yx,yy,yz,yw,+),\
  (D)->zy = GAN_REP4_OP_AB((C)->,*(B)->,zx,zy,zz,zw,yx,yy,yz,yw,+),\
  (D)->wy = GAN_REP4_OP_AB((C)->,*(B)->,wx,wy,wz,ww,yx,yy,yz,yw,+),\
  (D)->zz = GAN_REP4_OP_AA((C)->,*(B)->,zx,zy,zz,zw,+),\
  (D)->wz = GAN_REP4_OP_AB((C)->,*(B)->,wx,wy,wz,ww,zx,zy,zz,zw,+),\
  (D)->ww = GAN_REP4_OP_AA((C)->,*(B)->,wx,wy,wz,ww,+),D)
#define gan_mat44f_lmultl44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_lmultl44_i(A,B) gan_mat44f_lmultl44_q(A,B,A)
#define gan_mat44f_lmultl44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_lmultl44T_i(A,B) gan_mat44f_lmultl44T_q(A,B,A)
#define gan_mat44f_lmultl44I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F && (B)->ww !=0.0F),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_lmultl44I_i(A,B) gan_mat44f_lmultl44I_q(A,B,A)
#define gan_mat44f_lmultl44IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F && (B)->ww !=0.0F),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,wx,xx,yx,zx,wx),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,wy,xy,yy,zy,wy),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,wz,xz,yz,zz,wz),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xw,yw,zw,ww,xw,yw,zw,ww),C)
#define gan_mat44f_lmultl44IT_i(A,B) gan_mat44f_lmultl44IT_q(A,B,A)
#define gan_mat44f_rmultl44_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),\
  GAN_UPP44F_MULT1D((C)->,(B)->,(A)->,wx,wy,wz,ww,wx,wy,wz,ww),C)
#define gan_mat44f_rmultl44_i(A,B) gan_mat44f_rmultl44_q(A,B,A)
#define gan_mat44f_rmultl44T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),\
  GAN_LOW44F_MULT1D((C)->,(B)->,(A)->,wx,wy,wz,ww,wx,wy,wz,ww),C)
#define gan_mat44f_rmultl44T_i(A,B) gan_mat44f_rmultl44T_q(A,B,A)
#define gan_mat44f_rmultl44I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F && (B)->ww !=0.0F),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),\
  GAN_UPP44IF_MULT1D((C)->,(B)->,(A)->,wx,wy,wz,ww,wx,wy,wz,ww),C)
#define gan_mat44f_rmultl44I_i(A,B) gan_mat44f_rmultl44I_q(A,B,A)
#define gan_mat44f_rmultl44IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix44_f,Gan_SquMatrix44_f,Gan_Matrix44_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX44_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F && (B)->ww !=0.0F),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xw,xx,xy,xz,xw),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yw,yx,yy,yz,yw),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zw,zx,zy,zz,zw),\
  GAN_LOW44IF_MULT1D((C)->,(B)->,(A)->,wx,wy,wz,ww,wx,wy,wz,ww),C)
#define gan_mat44f_rmultl44IT_i(A,B) gan_mat44f_rmultl44IT_q(A,B,A)
#define gan_mat44f_invert_q(A,B) gan_mat44f_invert(A,B,NULL)
#define gan_mat44f_invert_i(A)   gan_mat44f_invert(A,A,NULL)

#define GAN_DET3(A,X,Y,Z)\
   ((A)->y ## X*((A)->z ## Y*(A)->w ## Z - (A)->w ## Y*(A)->z ## Z) +\
    (A)->y ## Y*((A)->z ## Z*(A)->w ## X - (A)->w ## Z*(A)->z ## X) +\
    (A)->y ## Z*((A)->z ## X*(A)->w ## Y - (A)->w ## X*(A)->z ## Y))
#define gan_mat44f_det_q(A) (GAN_TEST_OP1(A,Gan_Matrix44_f),\
               ((A)->xx*GAN_DET3(A,y,z,w) - (A)->xy*GAN_DET3(A,x,z,w) +\
                (A)->xz*GAN_DET3(A,x,y,w) - (A)->xw*GAN_DET3(A,x,y,z)))
#define gan_mat44f_trace_q(A) (GAN_TEST_OP1(A,Gan_Matrix44_f),\
                              ((A)->xx + (A)->yy + (A)->zz + (A)->ww))
#define gan_mat44f_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix44_f),\
     ((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
      (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw +\
      (A)->zx*(A)->zx + (A)->zy*(A)->zy + (A)->zz*(A)->zz + (A)->zw*(A)->zw +\
      (A)->wx*(A)->wx + (A)->wy*(A)->wy + (A)->wz*(A)->wz + (A)->ww*(A)->ww))
#define gan_mat44f_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix44_f), (float)\
 sqrt((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz + (A)->xw*(A)->xw +\
      (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz + (A)->yw*(A)->yw +\
      (A)->zx*(A)->zx + (A)->zy*(A)->zy + (A)->zz*(A)->zz + (A)->zw*(A)->zw +\
      (A)->wx*(A)->wx + (A)->wy*(A)->wy + (A)->wz*(A)->wz + (A)->ww*(A)->ww))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_4X4MATF_H */
