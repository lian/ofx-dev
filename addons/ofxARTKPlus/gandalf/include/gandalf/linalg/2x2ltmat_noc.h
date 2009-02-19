/**
 * File:          $RCSfile: 2x2ltmat_noc.h,v $
 * Module:        2x2 lower triangular matrices (double precision)
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

#ifndef _GAN_2X2LTMAT_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 2x2 lower triangular matrix with values.
 *
 * Fill 2x2 lower triangular matrix \a A with values:
 * \f[
 *   A = \left(\begin{array}{cc} XX & 0 \\ YX & YY \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SquMatrix22 *gan_ltmat22_fill_q ( Gan_SquMatrix22 *A, double XX,
                                      double YX, double YY );
#else
#define gan_ltmat22_fill_q(A,XX,YX,YY) (GAN_ST22_FILL(A,GAN_LOWER_TRI_MATRIX22,XX,YX,YY),A)
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_SquMatrix22 gan_ltmat22_fill_s ( double XX,
                                     double YX, double YY );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X2LTMAT_H */

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
#define GAN_SQUMATTYPEL Gan_SquMatrix22
#define GAN_SQUMATTYPER Gan_SquMatrix22
#define GAN_FIXED_MATRIX_TYPE GAN_LOWER_TRI_MATRIX22
#define GAN_MAT_FPRINT     gan_ltmat22_fprint
#define GAN_MAT_PRINT      gan_ltmat22_print
#define GAN_MAT_FSCANF     gan_ltmat22_fscanf
#define GAN_MAT_FWRITE     gan_ltmat22_fwrite
#define GAN_MAT_FREAD      gan_ltmat22_fread
#define GAN_MAT_ZERO_Q     gan_ltmat22_zero_q
#define GAN_MAT_ZERO_S     gan_ltmat22_zero_s
#define GAN_MAT_COPY_Q     gan_ltmat22_copy_q
#define GAN_MAT_COPY_S     gan_ltmat22_copy_s
#define GAN_MAT_SCALE_Q    gan_ltmat22_scale_q
#define GAN_MAT_SCALE_S    gan_ltmat22_scale_s
#define GAN_MAT_SCALE_I    gan_ltmat22_scale_i
#define GAN_MAT_DIVIDE_Q   gan_ltmat22_divide_q
#define GAN_MAT_DIVIDE_S   gan_ltmat22_divide_s
#define GAN_MAT_DIVIDE_I   gan_ltmat22_divide_i
#define GAN_MAT_NEGATE_Q   gan_ltmat22_negate_q
#define GAN_MAT_NEGATE_S   gan_ltmat22_negate_s
#define GAN_MAT_NEGATE_I   gan_ltmat22_negate_i
#define GAN_MAT_UNIT_Q     gan_ltmat22_unit_q
#define GAN_MAT_UNIT_S     gan_ltmat22_unit_s
#define GAN_MAT_UNIT_I     gan_ltmat22_unit_i
#define GAN_MAT_ADD_Q      gan_ltmat22_add_q
#define GAN_MAT_ADD_I1     gan_ltmat22_add_i1
#define GAN_MAT_ADD_I2     gan_ltmat22_add_i2
#define GAN_MAT_INCREMENT  gan_ltmat22_increment
#define GAN_MAT_ADD_S      gan_ltmat22_add_s
#define GAN_MAT_SUB_Q      gan_ltmat22_sub_q
#define GAN_MAT_SUB_I1     gan_ltmat22_sub_i1
#define GAN_MAT_SUB_I2     gan_ltmat22_sub_i2
#define GAN_MAT_DECREMENT  gan_ltmat22_decrement
#define GAN_MAT_SUB_S      gan_ltmat22_sub_s
#define GAN_MAT_MULTV_Q    gan_ltmat22_multv2_q
#define GAN_MAT_MULTV_S    gan_ltmat22_multv2_s
#define GAN_MAT_MULTV_I    gan_ltmat22_multv2_i
#define GAN_MATT_MULTV_Q   gan_ltmat22T_multv2_q
#define GAN_MATT_MULTV_S   gan_ltmat22T_multv2_s
#define GAN_MATT_MULTV_I   gan_ltmat22T_multv2_i
#define GAN_MAT_SRMULTT_Q  gan_ltmat22_srmultT_q
#define GAN_MAT_SRMULTT_S  gan_ltmat22_srmultT_s
#define GAN_MAT_SRMULTT_I  gan_ltmat22_srmultT_i
#define GAN_MAT_SLMULTT_Q  gan_ltmat22_slmultT_q
#define GAN_MAT_SLMULTT_S  gan_ltmat22_slmultT_s
#define GAN_MAT_SLMULTT_I  gan_ltmat22_slmultT_i
#define GAN_MAT_SUMSQR_Q   gan_ltmat22_sumsqr_q
#define GAN_MAT_SUMSQR_S   gan_ltmat22_sumsqr_s
#define GAN_MAT_FNORM_Q    gan_ltmat22_Fnorm_q
#define GAN_MAT_FNORM_S    gan_ltmat22_Fnorm_s

#define GAN_SQUMAT_IDENT_Q    gan_ltmat22_ident_q
#define GAN_SQUMAT_IDENT_S    gan_ltmat22_ident_s
#define GAN_SQUMATI_MULTV_Q   gan_ltmat22I_multv2_q
#define GAN_SQUMATI_MULTV_S   gan_ltmat22I_multv2_s
#define GAN_SQUMATI_MULTV_I   gan_ltmat22I_multv2_i
#define GAN_SQUMATIT_MULTV_Q  gan_ltmat22IT_multv2_q
#define GAN_SQUMATIT_MULTV_S  gan_ltmat22IT_multv2_s
#define GAN_SQUMATIT_MULTV_I  gan_ltmat22IT_multv2_i
#define GAN_SQUMAT_INVERT     gan_ltmat22_invert
#define GAN_SQUMAT_INVERT_Q   gan_ltmat22_invert_q
#define GAN_SQUMAT_INVERT_S   gan_ltmat22_invert_s
#define GAN_SQUMAT_INVERT_I   gan_ltmat22_invert_i
#define GAN_SQUMAT_DET_Q      gan_ltmat22_det_q
#define GAN_SQUMAT_DET_S      gan_ltmat22_det_s
#define GAN_SQUMAT_TRACE_Q    gan_ltmat22_trace_q
#define GAN_SQUMAT_TRACE_S    gan_ltmat22_trace_s

#ifndef _GAN_2X2LTMAT_H
#define _GAN_2X2LTMAT_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_ltmat22_zero_q(A) (GAN_ST22_ZERO(A,GAN_LOWER_TRI_MATRIX22),A)
#define gan_ltmat22_ident_q(A) (GAN_ST22_IDENT(A,GAN_LOWER_TRI_MATRIX22),A)
#define gan_ltmat22_copy_q(A,B) (GAN_ST22_COPY(A,B,GAN_LOWER_TRI_MATRIX22),B)
#define gan_ltmat22_scale_q(A,a,B) (GAN_ST22_SCALE(A,a,B,GAN_LOWER_TRI_MATRIX22),B)
#define gan_ltmat22_scale_i(A,a) gan_ltmat22_scale_q(A,a,A)
#define gan_ltmat22_divide_q(A,a,B) ((a)==0.0 ? NULL : (GAN_ST22_DIVIDE(A,a,B,GAN_LOWER_TRI_MATRIX22),B))
#define gan_ltmat22_divide_i(A,a) gan_ltmat22_divide_q(A,a,A)
#define gan_ltmat22_negate_q(A,B) (GAN_ST22_NEGATE(A,B,GAN_LOWER_TRI_MATRIX22),B)
#define gan_ltmat22_negate_i(A) gan_ltmat22_negate_q(A,A)
#define gan_ltmat22_unit_i(A) gan_ltmat22_unit_q(A,A)
#define gan_ltmat22_invert_q(A,B) gan_ltmat22_invert(A,B,NULL)
#define gan_ltmat22_invert_i(A)   gan_ltmat22_invert(A,A,NULL)
#define gan_ltmat22_add_q(A,B,C) (GAN_ST22_ADD(A,B,C,GAN_LOWER_TRI_MATRIX22),C)
#define gan_ltmat22_add_i1(A,B) gan_ltmat22_add_q(A,B,A)
#define gan_ltmat22_add_i2(A,B) gan_ltmat22_add_q(A,B,B)
#define gan_ltmat22_increment(A,B) gan_ltmat22_add_i1(A,B)
#define gan_ltmat22_sub_q(A,B,C) (GAN_ST22_SUB(A,B,C,GAN_LOWER_TRI_MATRIX22),C)
#define gan_ltmat22_sub_i1(A,B) gan_ltmat22_sub_q(A,B,A)
#define gan_ltmat22_sub_i2(A,B) gan_ltmat22_sub_q(A,B,B)
#define gan_ltmat22_decrement(A,B) gan_ltmat22_sub_i1(A,B)
#define gan_ltmat22_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_SquMatrix22,Gan_Vector2,Gan_Vector2),\
  assert((A)->type == GAN_LOWER_TRI_MATRIX22),\
  GAN_LOW22_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)
#define gan_ltmat22_multv2_i(A,p) gan_ltmat22_multv2_q(A,p,p)
#define gan_ltmat22T_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_SquMatrix22,Gan_Vector2,Gan_Vector2),\
  assert((A)->type == GAN_LOWER_TRI_MATRIX22),\
  GAN_UPP22_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)
#define gan_ltmat22T_multv2_i(A,p) gan_ltmat22T_multv2_q(A,p,p)
#define gan_ltmat22I_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_SquMatrix22,Gan_Vector2,Gan_Vector2),\
  assert((A)->type == GAN_LOWER_TRI_MATRIX22),\
  assert((A)->xx != 0.0 && (A)->yy != 0.0),\
  GAN_LOW22I_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)
#define gan_ltmat22I_multv2_i(A,p) gan_ltmat22I_multv2_q(A,p,p)
#define gan_ltmat22IT_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_SquMatrix22,Gan_Vector2,Gan_Vector2),\
  assert((A)->type == GAN_LOWER_TRI_MATRIX22),\
  assert((A)->xx != 0.0 && (A)->yy != 0.0),\
  GAN_UPP22I_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)
#define gan_ltmat22IT_multv2_i(A,p) gan_ltmat22IT_multv2_q(A,p,p)
#define gan_ltmat22_srmultT_q(A,B)\
 (GAN_TEST_OP2(A,B,Gan_SquMatrix22,Gan_SquMatrix22),\
  assert((A)->type == GAN_LOWER_TRI_MATRIX22),\
  (B)->yy = (A)->yx*(A)->yx + (A)->yy*(A)->yy,\
  (B)->yx = (A)->xx*(A)->yx, (B)->xx = (A)->xx*(A)->xx,\
  gan_eval((B)->type = GAN_SYMMETRIC_MATRIX22),B)
#define gan_ltmat22_srmultT_i(A) gan_ltmat22_srmultT_q(A,A)
#define gan_ltmat22_slmultT_q(A,B)\
 (GAN_TEST_OP2(A,B,Gan_SquMatrix22,Gan_SquMatrix22),\
  assert((A)->type == GAN_LOWER_TRI_MATRIX22),\
  (B)->xx = (A)->xx*(A)->xx + (A)->yx*(A)->yx,\
  (B)->yx = (A)->yx*(A)->yy, (B)->yy = (A)->yy*(A)->yy,\
  gan_eval((B)->type = GAN_SYMMETRIC_MATRIX22),B)
#define gan_ltmat22_slmultT_i(A) gan_ltmat22_slmultT_q(A,A)

#define gan_ltmat22_det_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                              assert((A)->type==GAN_LOWER_TRI_MATRIX22),\
                              ((A)->xx*(A)->yy))
#define gan_ltmat22_trace_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                                assert((A)->type==GAN_LOWER_TRI_MATRIX22),\
                                ((A)->xx + (A)->yy))
#define gan_ltmat22_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                                 assert((A)->type==GAN_LOWER_TRI_MATRIX22),\
                                 ((A)->xx*(A)->xx+\
                                  (A)->yx*(A)->yx+(A)->yy*(A)->yy))
#define gan_ltmat22_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_SquMatrix22),\
                                assert((A)->type==GAN_LOWER_TRI_MATRIX22),\
                                sqrt((A)->xx*(A)->xx+\
                                      (A)->yx*(A)->yx+(A)->yy*(A)->yy))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X2LTMAT_H */
