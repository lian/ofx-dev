/**
 * File:          $RCSfile: 2x2symmat_noc.h,v $
 * Module:        2x2 symmetric matrices (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.27 $
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

#ifndef _GAN_2X2SYMMAT_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Fill 2x2 symmetric matrix with values.
 *
 * Fill 2x2 symmetric matrix \a A filled with values:
 * \f[
 *  A = \left(\begin{array}{cc} XX & YX \\ YX & YY \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix22 *gan_symmat22_fill_q ( Gan_SquMatrix22 *A, double XX,
                                       double YX, double YY );
#else
#define gan_symmat22_fill_q(A,XX,YX,YY) (GAN_ST22_FILL(A,GAN_SYMMETRIC_MATRIX22,XX,YX,YY),A)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_SquMatrix22 gan_symmat22_fill_s ( double XX,
                                      double YX, double YY );
GANDALF_API Gan_Matrix22 *gan_symmat22_to_mat22_q ( const Gan_SquMatrix22 *A, Gan_Matrix22 *B );
GANDALF_API Gan_Matrix22 gan_symmat22_to_mat22_s ( const Gan_SquMatrix22 *A );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X2SYMMAT_H */

#define GAN_MATTYPE Gan_SquMatrix22
#define GAN_MATRIX_TYPE Gan_SquMatrix
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix
#define GAN_VECTOR_TYPE Gan_Vector
#define GAN_MAT_ELEMENT_TYPE GAN_DOUBLE
#define GAN_REALTYPE double
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f64
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f64
#define GAN_VECTYPE1 Gan_Vector2
#define GAN_VECTYPE2 Gan_Vector2
#define GAN_FIXED_MATRIX_TYPE GAN_SYMMETRIC_MATRIX22
#define GAN_MAT_FPRINT      gan_symmat22_fprint
#define GAN_MAT_PRINT       gan_symmat22_print
#define GAN_MAT_FSCANF      gan_symmat22_fscanf
#define GAN_MAT_FWRITE      gan_symmat22_fwrite
#define GAN_MAT_FREAD       gan_symmat22_fread
#define GAN_MAT_ZERO_Q      gan_symmat22_zero_q
#define GAN_MAT_ZERO_S      gan_symmat22_zero_s
#define GAN_MAT_COPY_Q      gan_symmat22_copy_q
#define GAN_MAT_COPY_S      gan_symmat22_copy_s
#define GAN_MAT_SCALE_Q     gan_symmat22_scale_q
#define GAN_MAT_SCALE_S     gan_symmat22_scale_s
#define GAN_MAT_SCALE_I     gan_symmat22_scale_i
#define GAN_MAT_DIVIDE_Q    gan_symmat22_divide_q
#define GAN_MAT_DIVIDE_S    gan_symmat22_divide_s
#define GAN_MAT_DIVIDE_I    gan_symmat22_divide_i
#define GAN_MAT_NEGATE_Q    gan_symmat22_negate_q
#define GAN_MAT_NEGATE_S    gan_symmat22_negate_s
#define GAN_MAT_NEGATE_I    gan_symmat22_negate_i
#define GAN_MAT_UNIT_Q      gan_symmat22_unit_q
#define GAN_MAT_UNIT_S      gan_symmat22_unit_s
#define GAN_MAT_UNIT_I      gan_symmat22_unit_i
#define GAN_MAT_ADD_Q       gan_symmat22_add_q
#define GAN_MAT_ADD_I1      gan_symmat22_add_i1
#define GAN_MAT_ADD_I2      gan_symmat22_add_i2
#define GAN_MAT_INCREMENT   gan_symmat22_increment
#define GAN_MAT_ADD_S       gan_symmat22_add_s
#define GAN_MAT_SUB_Q       gan_symmat22_sub_q
#define GAN_MAT_SUB_I1      gan_symmat22_sub_i1
#define GAN_MAT_SUB_I2      gan_symmat22_sub_i2
#define GAN_MAT_DECREMENT   gan_symmat22_decrement
#define GAN_MAT_SUB_S       gan_symmat22_sub_s
#define GAN_MAT_MULTV_Q     gan_symmat22_multv2_q
#define GAN_MAT_MULTV_S     gan_symmat22_multv2_s
#define GAN_MAT_SUMSQR_Q    gan_symmat22_sumsqr_q
#define GAN_MAT_SUMSQR_S    gan_symmat22_sumsqr_s
#define GAN_MAT_FNORM_Q     gan_symmat22_Fnorm_q
#define GAN_MAT_FNORM_S     gan_symmat22_Fnorm_s

#define GAN_SQUMAT_IDENT_Q       gan_symmat22_ident_q
#define GAN_SQUMAT_IDENT_S       gan_symmat22_ident_s
#define GAN_SQUMAT_INVERT        gan_symmat22_invert
#define GAN_SQUMAT_INVERT_Q      gan_symmat22_invert_q
#define GAN_SQUMAT_INVERT_S      gan_symmat22_invert_s
#define GAN_SQUMAT_INVERT_I      gan_symmat22_invert_i
#define GAN_SQUMAT_DET_Q         gan_symmat22_det_q
#define GAN_SQUMAT_DET_S         gan_symmat22_det_s
#define GAN_SQUMAT_TRACE_Q       gan_symmat22_trace_q
#define GAN_SQUMAT_TRACE_S       gan_symmat22_trace_s

#define GAN_VEC_OUTER_SYM_Q    gan_vec22_outer_sym_q
#define GAN_VEC_OUTER_SYM_S    gan_vec22_outer_sym_s
#define GAN_SYMMAT_CHOLESKY    gan_symmat22_cholesky
#define GAN_SYMMAT_CHOLESKY_Q  gan_symmat22_cholesky_q
#define GAN_SYMMAT_CHOLESKY_S  gan_symmat22_cholesky_s
#define GAN_SYMMAT_CHOLESKY_I  gan_symmat22_cholesky_i

#ifndef _GAN_2X2SYMMAT_H
#define _GAN_2X2SYMMAT_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_symmat22_zero_q(A) (GAN_ST22_ZERO(A,GAN_SYMMETRIC_MATRIX22),A)
#define gan_symmat22_ident_q(A) (GAN_ST22_IDENT(A,GAN_SYMMETRIC_MATRIX22),A)
#define gan_symmat22_copy_q(A,B) (GAN_ST22_COPY(A,B,GAN_SYMMETRIC_MATRIX22),B)
#define gan_symmat22_scale_q(A,a,B) (GAN_ST22_SCALE(A,a,B,GAN_SYMMETRIC_MATRIX22),B)
#define gan_symmat22_scale_i(A,a) gan_symmat22_scale_q(A,a,A)
#define gan_symmat22_divide_q(A,a,B) ((a)==0.0 ? NULL : (GAN_ST22_DIVIDE(A,a,B,GAN_SYMMETRIC_MATRIX22),B))
#define gan_symmat22_divide_i(A,a) gan_symmat22_divide_q(A,a,A)
#define gan_symmat22_negate_q(A,B) (GAN_ST22_NEGATE(A,B,GAN_SYMMETRIC_MATRIX22),B)
#define gan_symmat22_negate_i(A) gan_symmat22_negate_q(A,A)
#define gan_symmat22_unit_i(A) gan_symmat22_unit_q(A,A)
#define gan_symmat22_cholesky_q(A,B) gan_symmat22_cholesky(A,B,NULL)
#define gan_symmat22_cholesky_i(A) gan_symmat22_cholesky_q(A,A)
#define gan_symmat22_invert_q(A,B) gan_symmat22_invert(A,B,NULL)
#define gan_symmat22_invert_i(A)   gan_symmat22_invert(A,A,NULL)
#define gan_symmat22_add_q(A,B,C) (GAN_ST22_ADD(A,B,C,GAN_SYMMETRIC_MATRIX22),C)
#define gan_symmat22_add_i1(A,B) gan_symmat22_add_q(A,B,A)
#define gan_symmat22_add_i2(A,B) gan_symmat22_add_q(A,B,B)
#define gan_symmat22_increment(A,B) gan_symmat22_add_i1(A,B)
#define gan_symmat22_sub_q(A,B,C) (GAN_ST22_SUB(A,B,C,GAN_SYMMETRIC_MATRIX22),C)
#define gan_symmat22_sub_i1(A,B) gan_symmat22_sub_q(A,B,A)
#define gan_symmat22_sub_i2(A,B) gan_symmat22_sub_q(A,B,B)
#define gan_symmat22_decrement(A,B) gan_symmat22_sub_i1(A,B)
#define gan_vec22_outer_sym_q(p,A)\
 (GAN_TEST_OP2(p,A,Gan_Vector2,Gan_SquMatrix22),\
  gan_eval((A)->type = GAN_SYMMETRIC_MATRIX22),\
  GAN_REP1_ABC((A)->,=(p)->,*(p)->,xx,x,x),\
  GAN_REP2_ABC((A)->,=(p)->,*(p)->,yx,yy,y,y,x,y),A)
#define gan_symmat22_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_SquMatrix22,Gan_Vector2,Gan_Vector2),\
  assert((p)!=(q) && (A)->type == GAN_SYMMETRIC_MATRIX22),\
  GAN_SYM22_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)
#define gan_symmat22_det_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                               assert((A)->type==GAN_SYMMETRIC_MATRIX22),\
                               ((A)->xx*(A)->yy - (A)->yx*(A)->yx))
#define gan_symmat22_trace_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                                 assert((A)->type==GAN_SYMMETRIC_MATRIX22),\
                                 ((A)->xx+(A)->yy))
#define gan_symmat22_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                                  assert((A)->type==GAN_SYMMETRIC_MATRIX22),\
                                  ((A)->xx*(A)->xx+\
                                   2.0*(A)->yx*(A)->yx+(A)->yy*(A)->yy))
#define gan_symmat22_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                                 assert((A)->type==GAN_SYMMETRIC_MATRIX22),\
                                 sqrt((A)->xx*(A)->xx+\
                                       2.0*(A)->yx*(A)->yx+(A)->yy*(A)->yy))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X2SYMMAT_H */
