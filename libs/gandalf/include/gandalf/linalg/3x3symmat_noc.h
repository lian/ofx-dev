/**
 * File:          $RCSfile: 3x3symmat_noc.h,v $
 * Module:        3x3 symmetric matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.25 $
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

#ifndef _GAN_3X3SYMMAT_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 3x3 symmetric matrix with values.
 *
 * Fill 3x3 symmetric matrix \a A with values:
 * \f[ A = \left(\begin{array}{ccc} XX & YX & ZX \\ YX & YY & ZY \\
 *                                  ZX & ZY & ZZ \end{array}\right)
 * \f]
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix33 *gan_symmat33_fill_q ( Gan_SquMatrix33 *A,
                                       double XX,
                                       double YX, double YY,
                                       double ZX, double ZY, double ZZ );
#else
#define gan_symmat33_fill_q(A,XX,YX,YY,ZX,ZY,ZZ) (GAN_ST33_FILL(A,GAN_SYMMETRIC_MATRIX33,XX,YX,YY,ZX,ZY,ZZ),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extract parts of 3x3 symmetric matrix.
 *
 * Extract top-left 2x2 part, bottom-left 1x2 part and bottom-right element
 * of 3x3 symmetric matrix \a A into 2x2 lower triangular matrix \a B,
 * row 2-vector \a p and scalar pointer \a s. The arrangement is
 * \f[
 *     A = \left(\begin{array}{cc} B & p \\ p^{\top} & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_symmat33_get_parts_q ( const Gan_SquMatrix33 *A,
                                Gan_SquMatrix22 *B, Gan_Vector2 *p, double *s);
#else
#define gan_symmat33_get_parts_q(A,B,p,s)\
           (GAN_TEST_OP3(A,B,p,\
                         Gan_SquMatrix33,Gan_SquMatrix22,Gan_Vector2),\
            assert((A)->type == GAN_SYMMETRIC_MATRIX33),\
            gan_eval((B)->type = GAN_SYMMETRIC_MATRIX22),\
            (B)->xx=(A)->xx,\
            (B)->yx=(A)->yx,(B)->yy=(A)->yy,\
            (p)->x=(A)->zx,(p)->y=(A)->zy,*(s)=(A)->zz)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixBuild
 * \{
 */

/**
 * \brief Macro: Build a 3x3 symmetric matrix from parts.
 *
 * Build 3x3 symmetric matrix \a A from 2x2 symmetric matrix
 * \a B, 2-vector \a p, and scalar \a s, which are respectively inserted
 * in the top-left, bottom-left/top-right and bottom-right parts of the 3x3
 * matrix. The arrangement of the matrix is
 * \f[
 *    A = \left(\begin{array}{cc} B & p \\ p^{\top} & s \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix33 *gan_symmat33_set_parts_q ( Gan_SquMatrix33 *A,
                                            const Gan_SquMatrix22 *B,
                                            const Gan_Vector2 *p, double s );
#else
#define gan_symmat33_set_parts_q(A,B,p,s)\
           (GAN_TEST_OP3(A,B,p,Gan_SquMatrix33,Gan_SquMatrix22,Gan_Vector2),\
            assert((B)->type == GAN_SYMMETRIC_MATRIX22),\
            gan_eval((A)->type = GAN_SYMMETRIC_MATRIX33),\
            (A)->xx=(B)->xx,\
            (A)->yx=(B)->yx,(A)->yy=(B)->yy,\
            (A)->zx=(p)->x,(A)->zy=(p)->y,(A)->zz=(s),A)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_SquMatrix33 gan_symmat33_fill_s ( double XX,
                                      double YX, double YY,
                                      double ZX, double ZY, double ZZ );
GANDALF_API void gan_symmat33_get_parts_s ( const Gan_SquMatrix33 *A,
                                Gan_SquMatrix22 *B, Gan_Vector2 *p,
                                double *s );
GANDALF_API Gan_SquMatrix33 gan_symmat33_set_parts_s ( Gan_SquMatrix22 *B,
                                           const Gan_Vector2 *p, double s );
GANDALF_API Gan_Matrix33 *gan_symmat33_to_mat33_q ( const Gan_SquMatrix33 *A, Gan_Matrix33 *B );
GANDALF_API Gan_Matrix33 gan_symmat33_to_mat33_s ( const Gan_SquMatrix33 *A );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_3X3SYMMAT_H */

#define GAN_MATTYPE Gan_SquMatrix33
#define GAN_MATRIX_TYPE Gan_SquMatrix
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix
#define GAN_VECTOR_TYPE Gan_Vector
#define GAN_MAT_ELEMENT_TYPE GAN_DOUBLE
#define GAN_REALTYPE double
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f64
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f64
#define GAN_VECTYPE1 Gan_Vector3
#define GAN_VECTYPE2 Gan_Vector3
#define GAN_FIXED_MATRIX_TYPE GAN_SYMMETRIC_MATRIX33
#define GAN_MAT_FPRINT      gan_symmat33_fprint
#define GAN_MAT_PRINT       gan_symmat33_print
#define GAN_MAT_FSCANF      gan_symmat33_fscanf
#define GAN_MAT_FWRITE      gan_symmat33_fwrite
#define GAN_MAT_FREAD       gan_symmat33_fread
#define GAN_MAT_ZERO_Q      gan_symmat33_zero_q
#define GAN_MAT_ZERO_S      gan_symmat33_zero_s
#define GAN_MAT_COPY_Q      gan_symmat33_copy_q
#define GAN_MAT_COPY_S      gan_symmat33_copy_s
#define GAN_MAT_SCALE_Q     gan_symmat33_scale_q
#define GAN_MAT_SCALE_S     gan_symmat33_scale_s
#define GAN_MAT_SCALE_I     gan_symmat33_scale_i
#define GAN_MAT_DIVIDE_Q    gan_symmat33_divide_q
#define GAN_MAT_DIVIDE_S    gan_symmat33_divide_s
#define GAN_MAT_DIVIDE_I    gan_symmat33_divide_i
#define GAN_MAT_NEGATE_Q    gan_symmat33_negate_q
#define GAN_MAT_NEGATE_S    gan_symmat33_negate_s
#define GAN_MAT_NEGATE_I    gan_symmat33_negate_i
#define GAN_MAT_UNIT_Q      gan_symmat33_unit_q
#define GAN_MAT_UNIT_S      gan_symmat33_unit_s
#define GAN_MAT_UNIT_I      gan_symmat33_unit_i
#define GAN_MAT_ADD_Q       gan_symmat33_add_q
#define GAN_MAT_ADD_I1      gan_symmat33_add_i1
#define GAN_MAT_ADD_I2      gan_symmat33_add_i2
#define GAN_MAT_INCREMENT   gan_symmat33_increment
#define GAN_MAT_ADD_S       gan_symmat33_add_s
#define GAN_MAT_SUB_Q       gan_symmat33_sub_q
#define GAN_MAT_SUB_I1      gan_symmat33_sub_i1
#define GAN_MAT_SUB_I2      gan_symmat33_sub_i2
#define GAN_MAT_DECREMENT   gan_symmat33_decrement
#define GAN_MAT_SUB_S       gan_symmat33_sub_s
#define GAN_MAT_MULTV_Q     gan_symmat33_multv3_q
#define GAN_MAT_MULTV_S     gan_symmat33_multv3_s
#define GAN_MAT_SUMSQR_Q    gan_symmat33_sumsqr_q
#define GAN_MAT_SUMSQR_S    gan_symmat33_sumsqr_s
#define GAN_MAT_FNORM_Q     gan_symmat33_Fnorm_q
#define GAN_MAT_FNORM_S     gan_symmat33_Fnorm_s

#define GAN_SQUMAT_IDENT_Q    gan_symmat33_ident_q
#define GAN_SQUMAT_IDENT_S    gan_symmat33_ident_s
#define GAN_SQUMAT_INVERT     gan_symmat33_invert
#define GAN_SQUMAT_INVERT_Q   gan_symmat33_invert_q
#define GAN_SQUMAT_INVERT_S   gan_symmat33_invert_s
#define GAN_SQUMAT_INVERT_I   gan_symmat33_invert_i
#define GAN_SQUMAT_DET_Q      gan_symmat33_det_q
#define GAN_SQUMAT_DET_S      gan_symmat33_det_s
#define GAN_SQUMAT_TRACE_Q    gan_symmat33_trace_q
#define GAN_SQUMAT_TRACE_S    gan_symmat33_trace_s

#define GAN_VEC_OUTER_SYM_Q gan_vec33_outer_sym_q
#define GAN_VEC_OUTER_SYM_S gan_vec33_outer_sym_s
#define GAN_SYMMAT_CHOLESKY   gan_symmat33_cholesky
#define GAN_SYMMAT_CHOLESKY_Q gan_symmat33_cholesky_q
#define GAN_SYMMAT_CHOLESKY_S gan_symmat33_cholesky_s
#define GAN_SYMMAT_CHOLESKY_I gan_symmat33_cholesky_i

#ifndef _GAN_3X3SYMMAT_H
#define _GAN_3X3SYMMAT_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_symmat33_zero_q(A) (GAN_ST33_ZERO(A,GAN_SYMMETRIC_MATRIX33),A)
#define gan_symmat33_ident_q(A) (GAN_ST33_IDENT(A,GAN_SYMMETRIC_MATRIX33),A)
#define gan_symmat33_copy_q(A,B) (GAN_ST33_COPY(A,B,GAN_SYMMETRIC_MATRIX33),B)
#define gan_symmat33_scale_q(A,a,B) (GAN_ST33_SCALE(A,a,B,GAN_SYMMETRIC_MATRIX33),B)
#define gan_symmat33_scale_i(A,a) gan_symmat33_scale_q(A,a,A)
#define gan_symmat33_divide_q(A,a,B) ((a)==0.0 ? NULL : (GAN_ST33_DIVIDE(A,a,B,GAN_SYMMETRIC_MATRIX33),B))
#define gan_symmat33_divide_i(A,a) gan_symmat33_divide_q(A,a,A)
#define gan_symmat33_negate_q(A,B) (GAN_ST33_NEGATE(A,B,GAN_SYMMETRIC_MATRIX33),B)
#define gan_symmat33_negate_i(A) gan_symmat33_negate_q(A,A)
#define gan_symmat33_unit_i(A) gan_symmat33_unit_q(A,A)
#define gan_symmat33_cholesky_q(A,B) gan_symmat33_cholesky(A,B,NULL)
#define gan_symmat33_cholesky_i(A) gan_symmat33_cholesky_q(A,A)
#define gan_symmat33_invert_q(A,B) gan_symmat33_invert(A,B,NULL)
#define gan_symmat33_invert_i(A)   gan_symmat33_invert(A,A,NULL)
#define gan_symmat33_add_q(A,B,C) (GAN_ST33_ADD(A,B,C,GAN_SYMMETRIC_MATRIX33),C)
#define gan_symmat33_add_i1(A,B) gan_symmat33_add_q(A,B,A)
#define gan_symmat33_add_i2(A,B) gan_symmat33_add_q(A,B,B)
#define gan_symmat33_increment(A,B) gan_symmat33_add_i1(A,B)
#define gan_symmat33_sub_q(A,B,C) (GAN_ST33_SUB(A,B,C,GAN_SYMMETRIC_MATRIX33),C)
#define gan_symmat33_sub_i1(A,B) gan_symmat33_sub_q(A,B,A)
#define gan_symmat33_sub_i2(A,B) gan_symmat33_sub_q(A,B,B)
#define gan_symmat33_decrement(A,B) gan_symmat33_sub_i1(A,B)
#define gan_vec33_outer_sym_q(p,A)\
 (GAN_TEST_OP2(p,A,Gan_Vector3,Gan_SquMatrix33),\
  gan_eval((A)->type = GAN_SYMMETRIC_MATRIX33),\
  GAN_REP1_ABC((A)->,=(p)->,*(p)->,xx,x,x),\
  GAN_REP2_ABC((A)->,=(p)->,*(p)->,yx,yy,y,y,x,y),\
  GAN_REP3_ABC((A)->,=(p)->,*(p)->,zx,zy,zz,z,z,z,x,y,z),A)
#define gan_symmat33_multv3_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_SquMatrix33,Gan_Vector3,Gan_Vector3),\
  assert((p)!=(q) && (A)->type == GAN_SYMMETRIC_MATRIX33),\
  GAN_SYM33_MULT1D((q)->,(A)->,(p)->,x,y,z,x,y,z),q)
#define gan_symmat33_det_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix33),\
                               assert((A)->type==GAN_SYMMETRIC_MATRIX33),\
                               ((A)->xx*((A)->yy*(A)->zz - (A)->zy*(A)->zy) +\
                                (A)->yx*((A)->zy*(A)->zx - (A)->zz*(A)->yx) +\
                                (A)->zx*((A)->yx*(A)->zy - (A)->zx*(A)->yy)))
#define gan_symmat33_trace_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix33),\
                                 assert((A)->type==GAN_SYMMETRIC_MATRIX33),\
                                 ((A)->xx + (A)->yy + (A)->zz))
#define gan_symmat33_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix33),\
                                  assert((A)->type==GAN_SYMMETRIC_MATRIX33),\
                  ((A)->xx*(A)->xx + (A)->yy*(A)->yy + (A)->zz*(A)->zz +\
                   2.0*((A)->yx*(A)->yx + (A)->zx*(A)->zx + (A)->zy*(A)->zy)))
#define gan_symmat33_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix33),\
                                 assert((A)->type==GAN_SYMMETRIC_MATRIX33),\
               sqrt((A)->xx*(A)->xx + (A)->yy*(A)->yy + (A)->zz*(A)->zz +\
                    2.0*((A)->yx*(A)->yx + (A)->zx*(A)->zx + (A)->zy*(A)->zy)))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_3X3SYMMAT_H */
