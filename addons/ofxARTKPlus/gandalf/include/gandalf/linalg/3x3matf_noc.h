/**
 * File:          $RCSfile: 3x3matf_noc.h,v $
 * Module:        3x3 matrices (single precision)
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

#ifndef _GAN_3X3MATF_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 3x3 matrix with values.
 *
 * Fill 3x3 matrix \a A with values:
 * \f[
 *     A = \left(\begin{array}{ccc} XX & XY & XZ \\ YX & YY & YZ \\
 *                                  ZX & ZY & ZZ \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat33f_fill_q ( Gan_Matrix33_f *A,
                                    float XX, float XY, float XZ,
                                    float YX, float YY, float YZ,
                                    float ZX, float ZY, float ZZ );
#else
#define gan_mat33f_fill_q(A,XX,XY,XZ,YX,YY,YZ,ZX,ZY,ZZ)\
       (GAN_TEST_OP1(A,Gan_Matrix33_f),\
        GAN_FREP33_A_C((A)->,=,(XX),(XY),(XZ),(YX),(YY),(YZ),(ZX),(ZY),(ZZ)),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

/**
 * \brief Macro: Compute vector product matrix.
 *
 * Write matrix form of vector product of 3-vector \a p into 3x3 matrix
 * \a A. This is written as
 * \f[
 *   A = [p]_{\times}
 * \f]
 * such that for any vector \f$ x \f$,
 * \f[
 *   A x = p \times x
 * \f]
 *
 * \return Pointer to result matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat33f_cross_q ( const Gan_Vector3_f *p, Gan_Matrix33_f *A );
#else
#define gan_mat33f_cross_q(p,A)\
           (GAN_TEST_OP2(p,A,Gan_Vector3_f,Gan_Matrix33_f),\
            GAN_FREP33_A_C((A)->,=,0.0F,-(p)->z,(p)->y,(p)->z,0.0F,-(p)->x,-(p)->y,(p)->x,0.0F),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extract rows of 3x3 matrix.
 *
 * Extract rows of 3x3 matrix \a A into 3-vectors \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top}
 *     \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat33f_get_rows_q ( const Gan_Matrix33_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r );
#else
#define gan_mat33f_get_rows_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,\
                         Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f),\
            ((p)->x=(A)->xx,(p)->y=(A)->xy,(p)->z=(A)->xz,\
             (q)->x=(A)->yx,(q)->y=(A)->yy,(q)->z=(A)->yz,\
             (r)->x=(A)->zx,(r)->y=(A)->zy,(r)->z=(A)->zz))
#endif

/**
 * \brief Macro: Extract columns of 3x3 matrix
 *
 * Extract columns of 3x3 matrix \a A into 3-vectors \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{ccc} p & q & r \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat33f_get_cols_q ( const Gan_Matrix33_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r );
#else
#define gan_mat33f_get_cols_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,\
                         Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f),\
            ((p)->x=(A)->xx,(q)->x=(A)->xy,(r)->x=(A)->xz,\
             (p)->y=(A)->yx,(q)->y=(A)->yy,(r)->y=(A)->yz,\
             (p)->z=(A)->zx,(q)->z=(A)->zy,(r)->z=(A)->zz))
#endif

/**
 * \brief Macro: Extract top-left 2x2 part of 3x3 matrix.
 *
 * Extract top-left 2x2 part of 3x3 matrix \a A into 2x2 matrix \a B.
 *
 * \return Pointer to 2x2 matrix \a B.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix22_f *gan_mat33f_get_m22tl_q ( const Gan_Matrix33_f *A,
                                         Gan_Matrix22_f *B );
#else
#define gan_mat33f_get_m22tl_q(A,B)\
           (GAN_TEST_OP2(A,B,Gan_Matrix33_f,Gan_Matrix22_f),\
            (B)->xx=(A)->xx,(B)->xy=(A)->xy,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,B)
#endif

/**
 * \brief Macro: Extract top part of right hand column of 3x3 matrix.
 *
 * Extract top-right column of 3x3 matrix \a A into 2-vector \a p.
 *
 * \return Pointer to result 2-vector \a p.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Vector2_f *gan_mat33f_get_v2tr_q ( const Gan_Matrix33_f *A, Gan_Vector2_f *p );
#else
#define gan_mat33f_get_v2tr_q(A,p)\
           (GAN_TEST_OP2(A,p,Gan_Matrix33_f,Gan_Vector2_f),\
            (p)->x=(A)->xz,(p)->y=(A)->yz,p)
#endif

/**
 * \brief Macro: Extract parts of 3x3 matrix.
 *
 * Extract top-left 2x2 part, top-right 2x1 part, bottom-left 1x2 part and
 * bottom-right element of 3x3 matrix \a A into 2x2 matrix \a B,
 * column 2-vector \a p, row 2-vector \a q and scalar pointer \a s.
 * The arrangement is
 * \f[
 *   A = \left(\begin{array}{cc} B & p \\ q^{\top} & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat33f_get_parts_q ( const Gan_Matrix33_f *A, Gan_Matrix22_f *B,
                              Gan_Vector2_f *p, Gan_Vector2_f *q, float *s );
#else
#define gan_mat33f_get_parts_q(A,B,p,q,s)\
           (GAN_TEST_OP4(A,B,p,q,\
                         Gan_Matrix33_f,Gan_Matrix22_f,Gan_Vector2_f,Gan_Vector2_f),\
            (B)->xx=(A)->xx,(B)->xy=(A)->xy,(p)->x=(A)->xz,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,(p)->y=(A)->yz,\
            (q)->x=(A)->zx,(q)->y=(A)->zy,*(s)=(A)->zz)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixBuild
 * \{
 */

/**
 * \brief Macro: Build a 3x3 matrix from parts.
 *
 * Build 3x3 matrix from 2x2 matrix \a B, column 2-vector \a p,
 * row 2-vector \a q and scalar \a s, which are respectively inserted
 * in the top-left, top-right, bottom-left and bottom-right parts of \a A.
 * The arrangement of the matrix is
 * \f[
 *    \left(\begin{array}{cc} B & p \\ q^{\top} & s \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat33f_set_parts_q ( Gan_Matrix33_f *A, const Gan_Matrix22_f *B,
                                         const Gan_Vector2_f *p, const Gan_Vector2_f *q,
                                         float s );
#else
#define gan_mat33f_set_parts_q(A,B,p,q,s)\
           (GAN_TEST_OP4(A,B,p,q,\
                         Gan_Matrix33_f,Gan_Matrix22_f,Gan_Vector2_f,Gan_Vector2_f),\
            (A)->xx=(B)->xx,(A)->xy=(B)->xy,(A)->xz=(p)->x,\
            (A)->yx=(B)->yx,(A)->yy=(B)->yy,(A)->yz=(p)->y,\
            (A)->zx=(q)->x,(A)->zy=(q)->y,(A)->zz=(s),A)
#endif

/**
 * \brief Macro: Build 3x3 matrix from 3-vector columns.
 *
 * Build 3x3 matrix \a A from 3-vector columns \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{ccc} p & q & r \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat33f_set_cols_q ( Gan_Matrix33_f *A,
                                        const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                        const Gan_Vector3_f *r );
#else
#define gan_mat33f_set_cols_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,\
                         Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f),\
            (A)->xx=(p)->x,(A)->xy=(q)->x,(A)->xz=(r)->x,\
            (A)->yx=(p)->y,(A)->yy=(q)->y,(A)->yz=(r)->y,\
            (A)->zx=(p)->z,(A)->zy=(q)->z,(A)->zz=(r)->z,A)
#endif

/**
 * \brief Macro: Build 3x3 matrix from 3-vector rows.
 *
 * Build 3x3 matrix \a A from 3-vector rows \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top}
 *     \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix33_f *gan_mat33f_set_rows_q ( Gan_Matrix33_f *A,
                                        const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                        const Gan_Vector3_f *r );
#else
#define gan_mat33f_set_rows_q(A,p,q,r)\
           (GAN_TEST_OP4(A,p,q,r,\
                         Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f,Gan_Vector3_f),\
            (A)->xx=(p)->x,(A)->xy=(p)->y,(A)->xz=(p)->z,\
            (A)->yx=(q)->x,(A)->yy=(q)->y,(A)->yz=(q)->z,\
            (A)->zx=(r)->x,(A)->zy=(r)->y,(A)->zz=(r)->z,A)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix33_f gan_mat33f_fill_s ( float XX, float XY, float XZ,
                                   float YX, float YY, float YZ,
                                   float ZX, float ZY, float ZZ );
GANDALF_API Gan_Vector2_f *gan_mat33f_multv2h_q ( const Gan_Matrix33_f *A,
                                      const Gan_Vector2_f *p, float h,
                                      Gan_Vector2_f *q );
GANDALF_API Gan_Vector2_f gan_mat33f_multv2h_s ( const Gan_Matrix33_f *A,
                                     const Gan_Vector2_f *p, float h);
GANDALF_API Gan_Matrix33_f gan_mat33f_cross_s ( const Gan_Vector3_f *p );
GANDALF_API void gan_mat33f_get_rows_s ( const Gan_Matrix33_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r );
GANDALF_API void gan_mat33f_get_cols_s ( const Gan_Matrix33_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r );
GANDALF_API Gan_Matrix33_f gan_mat33f_set_parts_s ( Gan_Matrix22_f *B,
                                        const Gan_Vector2_f *p, const Gan_Vector2_f *q,
                                        float s);
GANDALF_API Gan_Matrix33_f gan_mat33f_set_cols_s ( const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                       const Gan_Vector3_f *r );
GANDALF_API Gan_Matrix33_f gan_mat33f_set_rows_s ( const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                                       const Gan_Vector3_f *r );
GANDALF_API Gan_Matrix33_f *gan_mat33f_from_matf_q ( const Gan_Matrix_f *A,
                                         Gan_Matrix33_f *B );
GANDALF_API Gan_Matrix33_f *gan_mat33f_from_squmatf_q ( const Gan_SquMatrix_f *A,
                                            Gan_Matrix33_f *B );
GANDALF_API Gan_SquMatrix33_f *gan_squmat33f_from_squmatf_q ( const Gan_SquMatrix_f *A,
                                                  Gan_SquMatrix33_f *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_3X3MATF_H */

#define GAN_MATTYPE Gan_Matrix33_f
#define GAN_MATRIX_TYPE Gan_Matrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f32
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f32
#define GAN_VECTYPE1 Gan_Vector3_f
#define GAN_VECTYPE2 Gan_Vector3_f
#define GAN_MATTYPEL Gan_Matrix33_f
#define GAN_MATTYPER Gan_Matrix33_f
#define GAN_SQUMATTYPEL Gan_SquMatrix33_f
#define GAN_SQUMATTYPER Gan_SquMatrix33_f
#define GAN_MAT_FPRINT                     gan_mat33f_fprint
#define GAN_MAT_PRINT                      gan_mat33f_print
#define GAN_MAT_FSCANF                     gan_mat33f_fscanf
#define GAN_MAT_FWRITE                     gan_mat33f_fwrite
#define GAN_MAT_FREAD                      gan_mat33f_fread
#define GAN_MAT_ZERO_Q                     gan_mat33f_zero_q
#define GAN_MAT_ZERO_S                     gan_mat33f_zero_s
#define GAN_MAT_COPY_Q                     gan_mat33f_copy_q
#define GAN_MAT_COPY_S                     gan_mat33f_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat33f_scale_q
#define GAN_MAT_SCALE_I                    gan_mat33f_scale_i
#define GAN_MAT_SCALE_S                    gan_mat33f_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat33f_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat33f_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat33f_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat33f_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat33f_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat33f_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat33f_unit_q
#define GAN_MAT_UNIT_I                     gan_mat33f_unit_i
#define GAN_MAT_UNIT_S                     gan_mat33f_unit_s
#define GAN_MAT_ADD_Q                      gan_mat33f_add_q
#define GAN_MAT_ADD_I1                     gan_mat33f_add_i1
#define GAN_MAT_ADD_I2                     gan_mat33f_add_i2
#define GAN_MAT_INCREMENT                  gan_mat33f_increment
#define GAN_MAT_ADD_S                      gan_mat33f_add_s
#define GAN_MAT_SUB_Q                      gan_mat33f_sub_q
#define GAN_MAT_SUB_I1                     gan_mat33f_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat33f_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat33f_decrement
#define GAN_MAT_SUB_S                      gan_mat33f_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec33f_outer_q
#define GAN_VEC_OUTER_S                    gan_vec33f_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat33f_multv3_q
#define GAN_MAT_MULTV_S                    gan_mat33f_multv3_s
#define GAN_MATT_MULTV_Q                   gan_mat33Tf_multv3_q
#define GAN_MATT_MULTV_S                   gan_mat33Tf_multv3_s
#define GAN_MAT_LMULTMT_Q                  gan_mat33f_lmultm33T_q
#define GAN_MAT_LMULTMT_S                  gan_mat33f_lmultm33T_s
#define GAN_MAT_RMULTM_Q                   gan_mat33f_rmultm33_q
#define GAN_MAT_RMULTM_S                   gan_mat33f_rmultm33_s
#define GAN_MAT_RMULTMT_Q                  gan_mat33f_rmultm33T_q
#define GAN_MAT_RMULTMT_S                  gan_mat33f_rmultm33T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat33f_lmultm33T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat33f_lmultm33T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat33f_rmultm33T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat33f_rmultm33T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat33f_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat33f_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat33f_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat33f_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat33f_lmults33_q
#define GAN_MAT_LMULTS_S                   gan_mat33f_lmults33_s
#define GAN_MAT_RMULTS_Q                   gan_mat33f_rmults33_q
#define GAN_MAT_RMULTS_S                   gan_mat33f_rmults33_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat33f_lrmultm33T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat33f_lrmultm33T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat33f_lrmultm33_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat33f_lrmultm33_s
#define GAN_MAT_LMULTL_Q                   gan_mat33f_lmultl33_q
#define GAN_MAT_LMULTL_S                   gan_mat33f_lmultl33_s
#define GAN_MAT_LMULTL_I                   gan_mat33f_lmultl33_i
#define GAN_MAT_LMULTLI_Q                  gan_mat33f_lmultl33I_q
#define GAN_MAT_LMULTLI_S                  gan_mat33f_lmultl33I_s
#define GAN_MAT_LMULTLI_I                  gan_mat33f_lmultl33I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat33f_lmultl33T_q
#define GAN_MAT_LMULTLT_S                  gan_mat33f_lmultl33T_s
#define GAN_MAT_LMULTLT_I                  gan_mat33f_lmultl33T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat33f_lmultl33IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat33f_lmultl33IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat33f_lmultl33IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat33f_rmultl33_q
#define GAN_MAT_RMULTL_S                   gan_mat33f_rmultl33_s
#define GAN_MAT_RMULTL_I                   gan_mat33f_rmultl33_i
#define GAN_MAT_RMULTLI_Q                  gan_mat33f_rmultl33I_q
#define GAN_MAT_RMULTLI_S                  gan_mat33f_rmultl33I_s
#define GAN_MAT_RMULTLI_I                  gan_mat33f_rmultl33I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat33f_rmultl33T_q
#define GAN_MAT_RMULTLT_S                  gan_mat33f_rmultl33T_s
#define GAN_MAT_RMULTLT_I                  gan_mat33f_rmultl33T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat33f_rmultl33IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat33f_rmultl33IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat33f_rmultl33IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat33f_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat33f_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat33f_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat33f_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat33f_from_matf_q
#define GAN_MAT_FROM_MAT_S                 gan_mat33f_from_matf_s
#define GAN_MAT_FROM_SQUMAT_Q              gan_mat33f_from_squmatf_q
#define GAN_MAT_FROM_SQUMAT_S              gan_mat33f_from_squmatf_s
#define GAN_SQUMAT_FROM_SQUMAT_Q           gan_squmat33f_from_squmatf_q
#define GAN_SQUMAT_FROM_SQUMAT_S           gan_squmat33f_from_squmatf_s

#define GAN_SQUMAT_IDENT_Q    gan_mat33f_ident_q
#define GAN_SQUMAT_IDENT_S    gan_mat33f_ident_s
#define GAN_SQUMAT_TPOSE_Q    gan_mat33f_tpose_q
#define GAN_SQUMAT_TPOSE_S    gan_mat33f_tpose_s
#define GAN_SQUMAT_TPOSE_I    gan_mat33f_tpose_i
#define GAN_MAT_SADDT_Q       gan_mat33f_saddT_q
#define GAN_MAT_SADDT_S       gan_mat33f_saddT_s
#define GAN_SQUMAT_INVERT     gan_mat33f_invert
#define GAN_SQUMAT_INVERT_Q   gan_mat33f_invert_q
#define GAN_SQUMAT_INVERT_S   gan_mat33f_invert_s
#define GAN_SQUMAT_INVERT_I   gan_mat33f_invert_i
#define GAN_SQUMAT_ADJOINT_Q  gan_mat33f_adjoint_q
#define GAN_SQUMAT_ADJOINT_S  gan_mat33f_adjoint_s
#define GAN_SQUMAT_ADJOINTT_Q gan_mat33f_adjointT_q
#define GAN_SQUMAT_ADJOINTT_S gan_mat33f_adjointT_s
#define GAN_SQUMAT_DET_Q      gan_mat33f_det_q
#define GAN_SQUMAT_DET_S      gan_mat33f_det_s
#define GAN_SQUMAT_TRACE_Q    gan_mat33f_trace_q
#define GAN_SQUMAT_TRACE_S    gan_mat33f_trace_s

#ifndef _GAN_3X3MATF_H
#define _GAN_3X3MATF_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat33f_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix33_f),\
                             GAN_REP33_AS((A)->,=0.0F,x,y,z,x,y,z),A)
#define gan_mat33f_ident_q(A) gan_mat33f_fill_q(A,1.0F,0.0F,0.0F,0.0F,1.0F,0.0F,0.0F,0.0F,1.0F)
#define gan_mat33f_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix33_f,Gan_Matrix33_f),\
                               GAN_REP33_AA_C((B)->,=(A)->),B)
#define gan_mat33f_tpose_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix33_f,Gan_Matrix33_f),\
                                (A)==(B)?gan_mat33f_tpose_i(A):\
                                         (GAN_REP33_AAT_C((B)->,=(A)->),B),B)
#define gan_mat33f_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix33_f,Gan_Matrix33_f),\
                                  GAN_REP33_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat33f_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix33_f),\
                                GAN_REP33_AS_C((A)->,*=(a)),A)
#define gan_mat33f_divide_q(A,a,B) (GAN_TEST_OP2(A,B,\
                                                Gan_Matrix33_f,Gan_Matrix33_f),\
                                   (a)==0.0F ? NULL :\
                                   (GAN_REP33_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat33f_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix33_f),\
                                 (a)==0.0F ? NULL :\
                                 (GAN_REP33_AS_C((A)->,/=(a)),A))
#define gan_mat33f_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix33_f,Gan_Matrix33_f),\
                                 GAN_REP33_AA_C((B)->,=-(A)->),B)
#define gan_mat33f_negate_i(A) gan_mat33f_negate_q(A,A)
#define gan_mat33f_unit_i(A) gan_mat33f_unit_q(A,A)
#define gan_mat33f_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_Matrix33_f,\
                                                   Gan_Matrix33_f),\
                                GAN_REP33_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat33f_add_i1(A,B) gan_mat33f_add_q(A,B,A)
#define gan_mat33f_add_i2(A,B) gan_mat33f_add_q(A,B,B)
#define gan_mat33f_increment(A,B) gan_mat33f_add_i1(A,B)
#define gan_mat33f_saddT_q(A,B)\
 (GAN_TEST_OP2(A,B,Gan_Matrix33_f,Gan_SquMatrix33_f),\
  gan_eval((B)->type = GAN_SYMMETRIC_MATRIX33_F),\
  (B)->xx = 2.0F*(A)->xx,\
  (B)->yx = (A)->xy+(A)->yx, (B)->yy = 2.0F*(A)->yy,\
  (B)->zx = (A)->xz+(A)->zx, (B)->zy = (A)->yz+(A)->zy, (B)->zz = 2.0F*(A)->zz,\
  B)
#define gan_mat33f_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,\
                                Gan_Matrix33_f,Gan_Matrix33_f,Gan_Matrix33_f),\
                                GAN_REP33_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat33f_sub_i1(A,B) gan_mat33f_sub_q(A,B,A)
#define gan_mat33f_sub_i2(A,B) gan_mat33f_sub_q(A,B,B)
#define gan_mat33f_decrement(A,B) gan_mat33f_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec33f_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector3_f,Gan_Vector3_f,Gan_Matrix33_f),\
  GAN_REP3_ABC((A)->,=(p)->,*(q)->,xx,xy,xz,x,x,x,x,y,z),\
  GAN_REP3_ABC((A)->,=(p)->,*(q)->,yx,yy,yz,y,y,y,x,y,z),\
  GAN_REP3_ABC((A)->,=(p)->,*(q)->,zx,zy,zz,z,z,z,x,y,z),A)
 
/* matrix/vector multiply */
#define gan_mat33f_multv3_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f),\
  assert((p)!=(q)),\
  GAN_MAT33F_MULT1D((q)->,(A)->,(p)->,x,y,z,x,y,z),q)
#define gan_mat33Tf_multv3_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix33_f,Gan_Vector3_f,Gan_Vector3_f),\
  assert((p)!=(q)),\
  GAN_MAT33TF_MULT1D((q)->,(A)->,(p)->,x,y,z,x,y,z),q)

/* matrix/matrix multiply */
#define gan_mat33f_lmultm33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_Matrix33_f,Gan_Matrix33_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_rmultm33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_Matrix33_f,Gan_Matrix33_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,yx,zx),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,xy,yy,zy),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_rmultm33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_Matrix33_f,Gan_Matrix33_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,xy,xz),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,yx,yy,yz),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,zx,zy,zz),C)
#define gan_mat33f_lmultm33T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_Matrix33_f,Gan_SquMatrix33_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT33TF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  (C)->yy = GAN_REP3_OP_AA((A)->,*(B)->,xy,yy,zy,+),\
  (C)->zy = GAN_REP3_OP_AB((A)->,*(B)->,xz,yz,zz,xy,yy,zy,+),\
  (C)->zz = GAN_REP3_OP_AA((A)->,*(B)->,xz,yz,zz,+),C)
#define gan_mat33f_slmultT_q(A,C) gan_mat33f_lmultm33T_sym_q(A,A,C)
#define gan_mat33f_rmultm33T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_Matrix33_f,Gan_SquMatrix33_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,xy,xz),\
  (C)->yy = GAN_REP3_OP_AA((A)->,*(B)->,yx,yy,yz,+),\
  (C)->zy = GAN_REP3_OP_AB((A)->,*(B)->,zx,zy,zz,yx,yy,yz,+),\
  (C)->zz = GAN_REP3_OP_AA((A)->,*(B)->,zx,zy,zz,+),C)
#define gan_mat33f_srmultT_q(A,C) gan_mat33f_rmultm33T_sym_q(A,A,C)
#define gan_mat33f_lmults33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_SYM33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_rmults33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,yx,zx),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,yx,yy,zy),\
  GAN_MAT33F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,zx,zy,zz),C)
#define gan_symmat33f_lrmultm33T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix33_f,Gan_Matrix33_f,Gan_Matrix33_f,Gan_SquMatrix33_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xx,yx,zx,xx,yx,zx),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xy,yy,zy,xy,yy,zy),\
  GAN_SYM33F_MULT1D((C)->,(A)->,(B)->,xz,yz,zz,xz,yz,zz),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT33TF_MULT1D((D)->,(B)->,(C)->,xx,yx,zx,xx,yx,zx),\
  (D)->yy = GAN_REP3_OP_AA((C)->,*(B)->,xy,yy,zy,+),\
  (D)->zy = GAN_REP3_OP_AB((C)->,*(B)->,xz,yz,zz,xy,yy,zy,+),\
  (D)->zz = GAN_REP3_OP_AA((C)->,*(B)->,xz,yz,zz,+),D)
#define gan_symmat33f_lrmultm33_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
           Gan_SquMatrix33_f,Gan_Matrix33_f,Gan_Matrix33_f,Gan_SquMatrix33_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,yx,yy,zy),\
  GAN_MAT33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,zx,zy,zz),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX33_F),\
  GAN_MAT33F_MULT1D((D)->,(C)->,(B)->,xx,yx,zx,xx,xy,xz),\
  (D)->yy = GAN_REP3_OP_AA((C)->,*(B)->,yx,yy,yz,+),\
  (D)->zy = GAN_REP3_OP_AB((C)->,*(B)->,zx,zy,zz,yx,yy,yz,+),\
  (D)->zz = GAN_REP3_OP_AA((C)->,*(B)->,zx,zy,zz,+),D)
#define gan_mat33f_lmultl33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_lmultl33_i(A,B) gan_mat33f_lmultl33_q(A,B,A)
#define gan_mat33f_lmultl33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_lmultl33T_i(A,B) gan_mat33f_lmultl33T_q(A,B,A)
#define gan_mat33f_lmultl33I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_lmultl33I_i(A,B) gan_mat33f_lmultl33I_q(A,B,A)
#define gan_mat33f_lmultl33IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xx,yx,zx,xx,yx,zx),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xy,yy,zy,xy,yy,zy),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xz,yz,zz,xz,yz,zz),C)
#define gan_mat33f_lmultl33IT_i(A,B) gan_mat33f_lmultl33IT_q(A,B,A)
#define gan_mat33f_rmultl33_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),\
  GAN_UPP33F_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zx,zy,zz),C)
#define gan_mat33f_rmultl33_i(A,B) gan_mat33f_rmultl33_q(A,B,A)
#define gan_mat33f_rmultl33T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),\
  GAN_LOW33F_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zx,zy,zz),C)
#define gan_mat33f_rmultl33T_i(A,B) gan_mat33f_rmultl33T_q(A,B,A)
#define gan_mat33f_rmultl33I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),\
  GAN_UPP33IF_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zx,zy,zz),C)
#define gan_mat33f_rmultl33I_i(A,B) gan_mat33f_rmultl33I_q(A,B,A)
#define gan_mat33f_rmultl33IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix33_f,Gan_SquMatrix33_f,Gan_Matrix33_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX33_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F && (B)->zz != 0.0F),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xz,xx,xy,xz),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yz,yx,yy,yz),\
  GAN_LOW33IF_MULT1D((C)->,(B)->,(A)->,zx,zy,zz,zx,zy,zz),C)
#define gan_mat33f_rmultl33IT_i(A,B) gan_mat33f_rmultl33IT_q(A,B,A)
#define gan_mat33f_invert_q(A,B) gan_mat33f_invert(A,B,NULL)
#define gan_mat33f_invert_i(A)   gan_mat33f_invert(A,A,NULL)

#define gan_mat33f_det_q(A) (GAN_TEST_OP1(A,Gan_Matrix33_f),\
                            ((A)->xx*((A)->yy*(A)->zz - (A)->zy*(A)->yz) +\
                             (A)->xy*((A)->yz*(A)->zx - (A)->zz*(A)->yx) +\
                             (A)->xz*((A)->yx*(A)->zy - (A)->zx*(A)->yy)))
#define gan_mat33f_trace_q(A) (GAN_TEST_OP1(A,Gan_Matrix33_f),\
                              ((A)->xx + (A)->yy + (A)->zz))
#define gan_mat33f_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix33_f),\
                        ((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz +\
                         (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz +\
                         (A)->zx*(A)->zx + (A)->zy*(A)->zy + (A)->zz*(A)->zz))
#define gan_mat33f_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix33_f), (float)\
                    sqrt((A)->xx*(A)->xx + (A)->xy*(A)->xy + (A)->xz*(A)->xz +\
                         (A)->yx*(A)->yx + (A)->yy*(A)->yy + (A)->yz*(A)->yz +\
                         (A)->zx*(A)->zx + (A)->zy*(A)->zy + (A)->zz*(A)->zz))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_3X3MATF_H */
