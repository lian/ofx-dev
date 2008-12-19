/**
 * File:          $RCSfile: 2x2matf_noc.h,v $
 * Module:        2x2 matrices (single precision)
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

#ifndef _GAN_2X2MATF_H

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Macro: Fill 2x2 matrix with values.
 *
 * Fill 2x2 matrix \a A with values:
 * \f[ A = \left(\begin{array}{cc} XX & XY \\ YX & YY  \end{array}\right)
 * \f]
 *
 * \return Pointer to filled matrix \a A.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Matrix22_f *gan_mat22f_fill_q ( Gan_Matrix22_f *A,
                                    float XX, float XY, float YX, float YY );
#else
#define gan_mat22f_fill_q(A,XX,XY,YX,YY)\
           (GAN_TEST_OP1(A,Gan_Matrix22_f),\
            GAN_FREP22_A_C((A)->,=,(XX),(XY),(YX),(YY)),A)
#endif

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Macro: Extract rows of 2x2 matrix.
 *
 * Extract rows of 2x2 matrix \a A into 2-vectors \a p and \a q.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat22f_get_rows_q ( const Gan_Matrix22_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q );
#else
#define gan_mat22f_get_rows_q(A,p,q)\
           (GAN_TEST_OP3(A,p,q,Gan_Matrix22_f,Gan_Vector2_f,Gan_Vector2_f),\
            ((p)->x=(A)->xx,(p)->y=(A)->xy,\
             (q)->x=(A)->yx,(q)->y=(A)->yy))
#endif

/**
 * \brief Macro: Extract columns of 2x2 matrix
 *
 * Extract columns of 2x2 matrix \a A into 2-vectors \a p and \a q.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{cc} p & q \end{array}\right)
 * \f]
 *
 * \return No value.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_mat22f_get_cols_q ( const Gan_Matrix22_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q );
#else
#define gan_mat22f_get_cols_q(A,p,q)\
           (GAN_TEST_OP3(A,p,q,Gan_Matrix22_f,Gan_Vector2_f,Gan_Vector2_f),\
            ((p)->x=(A)->xx,(q)->x=(A)->xy,\
             (p)->y=(A)->yx,(q)->y=(A)->yy))
#endif

/**
 * \}
 */

#ifndef GAN_GENERATE_DOCUMENTATION

GANDALF_API Gan_Matrix22_f gan_mat22f_fill_s ( float XX, float XY, float YX, float YY );
GANDALF_API void gan_mat22f_get_rows_s ( const Gan_Matrix22_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q );
GANDALF_API void gan_mat22f_get_cols_s ( const Gan_Matrix22_f *A,
                             Gan_Vector2_f *p, Gan_Vector2_f *q );
GANDALF_API Gan_Matrix22_f *gan_mat22f_from_matf_q ( const Gan_Matrix_f *A, Gan_Matrix22_f *B );
GANDALF_API Gan_Matrix22_f *gan_mat22f_from_squmatf_q ( const Gan_SquMatrix_f *A,
                                            Gan_Matrix22_f *B );
GANDALF_API Gan_SquMatrix22_f *gan_squmat22f_from_squmatf_q ( const Gan_SquMatrix_f *A,
                                                  Gan_SquMatrix22_f *B );

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X2MATF_H */

#define GAN_MATTYPE Gan_Matrix22_f
#define GAN_MATRIX_TYPE Gan_Matrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_FWRITE_LENDIAN gan_fwrite_lendian_f32
#define GAN_FREAD_LENDIAN  gan_fread_lendian_f32
#define GAN_VECTYPE1 Gan_Vector2_f
#define GAN_VECTYPE2 Gan_Vector2_f
#define GAN_MATTYPEL Gan_Matrix22_f
#define GAN_MATTYPER Gan_Matrix22_f
#define GAN_SQUMATTYPEL Gan_SquMatrix22_f
#define GAN_SQUMATTYPER Gan_SquMatrix22_f
#define GAN_MAT_FPRINT                     gan_mat22f_fprint
#define GAN_MAT_PRINT                      gan_mat22f_print
#define GAN_MAT_FSCANF                     gan_mat22f_fscanf
#define GAN_MAT_FWRITE                     gan_mat22f_fwrite
#define GAN_MAT_FREAD                      gan_mat22f_fread
#define GAN_MAT_ZERO_Q                     gan_mat22f_zero_q
#define GAN_MAT_ZERO_S                     gan_mat22f_zero_s
#define GAN_MAT_COPY_Q                     gan_mat22f_copy_q
#define GAN_MAT_COPY_S                     gan_mat22f_copy_s
#define GAN_MAT_SCALE_Q                    gan_mat22f_scale_q
#define GAN_MAT_SCALE_I                    gan_mat22f_scale_i
#define GAN_MAT_SCALE_S                    gan_mat22f_scale_s
#define GAN_MAT_DIVIDE_Q                   gan_mat22f_divide_q
#define GAN_MAT_DIVIDE_I                   gan_mat22f_divide_i
#define GAN_MAT_DIVIDE_S                   gan_mat22f_divide_s
#define GAN_MAT_NEGATE_Q                   gan_mat22f_negate_q
#define GAN_MAT_NEGATE_I                   gan_mat22f_negate_i
#define GAN_MAT_NEGATE_S                   gan_mat22f_negate_s
#define GAN_MAT_UNIT_Q                     gan_mat22f_unit_q
#define GAN_MAT_UNIT_I                     gan_mat22f_unit_i
#define GAN_MAT_UNIT_S                     gan_mat22f_unit_s
#define GAN_MAT_ADD_Q                      gan_mat22f_add_q
#define GAN_MAT_ADD_I1                     gan_mat22f_add_i1
#define GAN_MAT_ADD_I2                     gan_mat22f_add_i2
#define GAN_MAT_INCREMENT                  gan_mat22f_increment
#define GAN_MAT_ADD_S                      gan_mat22f_add_s
#define GAN_MAT_SUB_Q                      gan_mat22f_sub_q
#define GAN_MAT_SUB_I1                     gan_mat22f_sub_i1
#define GAN_MAT_SUB_I2                     gan_mat22f_sub_i2
#define GAN_MAT_DECREMENT                  gan_mat22f_decrement
#define GAN_MAT_SUB_S                      gan_mat22f_sub_s
#define GAN_VEC_OUTER_Q                    gan_vec22f_outer_q
#define GAN_VEC_OUTER_S                    gan_vec22f_outer_s
#define GAN_MAT_MULTV_Q                    gan_mat22f_multv2_q
#define GAN_MAT_MULTV_S                    gan_mat22f_multv2_s
#define GAN_MATT_MULTV_Q                   gan_mat22Tf_multv2_q
#define GAN_MATT_MULTV_S                   gan_mat22Tf_multv2_s
#define GAN_MAT_LMULTMT_Q                  gan_mat22f_lmultm22T_q
#define GAN_MAT_LMULTMT_S                  gan_mat22f_lmultm22T_s
#define GAN_MAT_RMULTM_Q                   gan_mat22f_rmultm22_q
#define GAN_MAT_RMULTM_S                   gan_mat22f_rmultm22_s
#define GAN_MAT_RMULTMT_Q                  gan_mat22f_rmultm22T_q
#define GAN_MAT_RMULTMT_S                  gan_mat22f_rmultm22T_s
#define GAN_MAT_LMULTMT_SYM_Q              gan_mat22f_lmultm22T_sym_q
#define GAN_MAT_LMULTMT_SYM_S              gan_mat22f_lmultm22T_sym_s
#define GAN_MAT_RMULTMT_SYM_Q              gan_mat22f_rmultm22T_sym_q
#define GAN_MAT_RMULTMT_SYM_S              gan_mat22f_rmultm22T_sym_s
#define GAN_MAT_SLMULTT_Q                  gan_mat22f_slmultT_q
#define GAN_MAT_SLMULTT_S                  gan_mat22f_slmultT_s
#define GAN_MAT_SRMULTT_Q                  gan_mat22f_srmultT_q
#define GAN_MAT_SRMULTT_S                  gan_mat22f_srmultT_s
#define GAN_MAT_LMULTS_Q                   gan_mat22f_lmults22_q
#define GAN_MAT_LMULTS_S                   gan_mat22f_lmults22_s
#define GAN_MAT_RMULTS_Q                   gan_mat22f_rmults22_q
#define GAN_MAT_RMULTS_S                   gan_mat22f_rmults22_s
#define GAN_SYMMATL_LRMULT_Q               gan_symmat22f_lrmultm22T_q
#define GAN_SYMMATL_LRMULT_S               gan_symmat22f_lrmultm22T_s
#define GAN_SYMMATR_LRMULT_Q               gan_symmat22f_lrmultm22_q
#define GAN_SYMMATR_LRMULT_S               gan_symmat22f_lrmultm22_s
#define GAN_MAT_LMULTL_Q                   gan_mat22f_lmultl22_q
#define GAN_MAT_LMULTL_S                   gan_mat22f_lmultl22_s
#define GAN_MAT_LMULTL_I                   gan_mat22f_lmultl22_i
#define GAN_MAT_LMULTLI_Q                  gan_mat22f_lmultl22I_q
#define GAN_MAT_LMULTLI_S                  gan_mat22f_lmultl22I_s
#define GAN_MAT_LMULTLI_I                  gan_mat22f_lmultl22I_i
#define GAN_MAT_LMULTLT_Q                  gan_mat22f_lmultl22T_q
#define GAN_MAT_LMULTLT_S                  gan_mat22f_lmultl22T_s
#define GAN_MAT_LMULTLT_I                  gan_mat22f_lmultl22T_i
#define GAN_MAT_LMULTLIT_Q                 gan_mat22f_lmultl22IT_q
#define GAN_MAT_LMULTLIT_S                 gan_mat22f_lmultl22IT_s
#define GAN_MAT_LMULTLIT_I                 gan_mat22f_lmultl22IT_i
#define GAN_MAT_RMULTL_Q                   gan_mat22f_rmultl22_q
#define GAN_MAT_RMULTL_S                   gan_mat22f_rmultl22_s
#define GAN_MAT_RMULTL_I                   gan_mat22f_rmultl22_i
#define GAN_MAT_RMULTLI_Q                  gan_mat22f_rmultl22I_q
#define GAN_MAT_RMULTLI_S                  gan_mat22f_rmultl22I_s
#define GAN_MAT_RMULTLI_I                  gan_mat22f_rmultl22I_i
#define GAN_MAT_RMULTLT_Q                  gan_mat22f_rmultl22T_q
#define GAN_MAT_RMULTLT_S                  gan_mat22f_rmultl22T_s
#define GAN_MAT_RMULTLT_I                  gan_mat22f_rmultl22T_i
#define GAN_MAT_RMULTLIT_Q                 gan_mat22f_rmultl22IT_q
#define GAN_MAT_RMULTLIT_S                 gan_mat22f_rmultl22IT_s
#define GAN_MAT_RMULTLIT_I                 gan_mat22f_rmultl22IT_i
#define GAN_MAT_SUMSQR_Q                   gan_mat22f_sumsqr_q
#define GAN_MAT_SUMSQR_S                   gan_mat22f_sumsqr_s
#define GAN_MAT_FNORM_Q                    gan_mat22f_Fnorm_q
#define GAN_MAT_FNORM_S                    gan_mat22f_Fnorm_s
#define GAN_MAT_FROM_MAT_Q                 gan_mat22f_from_matf_q
#define GAN_MAT_FROM_MAT_S                 gan_mat22f_from_matf_s
#define GAN_MAT_FROM_SQUMAT_Q              gan_mat22f_from_squmatf_q
#define GAN_MAT_FROM_SQUMAT_S              gan_mat22f_from_squmatf_s
#define GAN_SQUMAT_FROM_SQUMAT_Q           gan_squmat22f_from_squmatf_q
#define GAN_SQUMAT_FROM_SQUMAT_S           gan_squmat22f_from_squmatf_s

#define GAN_SQUMAT_IDENT_Q    gan_mat22f_ident_q
#define GAN_SQUMAT_IDENT_S    gan_mat22f_ident_s
#define GAN_SQUMAT_TPOSE_Q    gan_mat22f_tpose_q
#define GAN_SQUMAT_TPOSE_S    gan_mat22f_tpose_s
#define GAN_SQUMAT_TPOSE_I    gan_mat22f_tpose_i
#define GAN_MAT_SADDT_Q       gan_mat22f_saddT_q
#define GAN_MAT_SADDT_S       gan_mat22f_saddT_s
#define GAN_SQUMAT_INVERT     gan_mat22f_invert
#define GAN_SQUMAT_INVERT_Q   gan_mat22f_invert_q
#define GAN_SQUMAT_INVERT_S   gan_mat22f_invert_s
#define GAN_SQUMAT_INVERT_I   gan_mat22f_invert_i
#define GAN_SQUMAT_ADJOINT_Q  gan_mat22f_adjoint_q
#define GAN_SQUMAT_ADJOINT_S  gan_mat22f_adjoint_s
#define GAN_SQUMAT_ADJOINTT_Q gan_mat22f_adjointT_q
#define GAN_SQUMAT_ADJOINTT_S gan_mat22f_adjointT_s
#define GAN_SQUMAT_DET_Q      gan_mat22f_det_q
#define GAN_SQUMAT_DET_S      gan_mat22f_det_s
#define GAN_SQUMAT_TRACE_Q    gan_mat22f_trace_q
#define GAN_SQUMAT_TRACE_S    gan_mat22f_trace_s

#ifndef _GAN_2X2MATF_H
#define _GAN_2X2MATF_H

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_mat22f_zero_q(A) (GAN_TEST_OP1(A,Gan_Matrix22_f),\
                             GAN_REP22_AS((A)->,=0.0F,x,y,x,y),A)
#define gan_mat22f_ident_q(A) gan_mat22f_fill_q(A,1.0F,0.0F,0.0F,1.0F)
#define gan_mat22f_copy_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix22_f,Gan_Matrix22_f),\
                               GAN_REP22_AA_C((B)->,=(A)->),B)
#define gan_mat22f_tpose_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix22_f,Gan_Matrix22_f),\
                                (A)==(B)?gan_mat22f_tpose_i(A):\
                                         (GAN_REP22_AAT_C((B)->,=(A)->),B))
#define gan_mat22f_scale_q(A,a,B) (GAN_TEST_OP2(A,B,Gan_Matrix22_f,Gan_Matrix22_f),\
                                  GAN_REP22_AAS_C((B)->,=(A)->,*(a)),B)
#define gan_mat22f_scale_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix22_f),\
                                GAN_REP22_AS_C((A)->,*=(a)),A)
#define gan_mat22f_divide_q(A,a,B) \
        (GAN_TEST_OP2(A,B,Gan_Matrix22_f,Gan_Matrix22_f),\
         (a)==0.0F ? NULL : (GAN_REP22_AAS_C((B)->,=(A)->,/(a)),B))
#define gan_mat22f_divide_i(A,a) (GAN_TEST_OP1(A,Gan_Matrix22_f),\
                                 (a)==0.0F ? NULL :\
                                 (GAN_REP22_AS_C((A)->,/=(a)),A))
#define gan_mat22f_negate_q(A,B) (GAN_TEST_OP2(A,B,Gan_Matrix22_f,Gan_Matrix22_f),\
                                 GAN_REP22_AA_C((B)->,=-(A)->),B)
#define gan_mat22f_negate_i(A) gan_mat22f_negate_q(A,A)
#define gan_mat22f_unit_i(A) gan_mat22f_unit_q(A,A)
#define gan_mat22f_add_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,\
                                                   Gan_Matrix22_f),\
                                GAN_REP22_AAA_C((C)->,=(A)->,+(B)->),C)
#define gan_mat22f_add_i1(A,B) gan_mat22f_add_q(A,B,A)
#define gan_mat22f_add_i2(A,B) gan_mat22f_add_q(A,B,B)
#define gan_mat22f_increment(A,B) gan_mat22f_add_i1(A,B)
#define gan_mat22f_saddT_q(A,B)\
              (GAN_TEST_OP2(A,B,Gan_Matrix22_f,Gan_SquMatrix22_f),\
               gan_eval((B)->type = GAN_SYMMETRIC_MATRIX22_F),\
               (B)->xx = 2.0F*(A)->xx,\
               (B)->yx = (A)->xy+(A)->yx, (B)->yy = 2.0F*(A)->yy,B)
#define gan_mat22f_sub_q(A,B,C) (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,\
                                                   Gan_Matrix22_f),\
                                GAN_REP22_AAA_C((C)->,=(A)->,-(B)->),C)
#define gan_mat22f_sub_i1(A,B) gan_mat22f_sub_q(A,B,A)
#define gan_mat22f_sub_i2(A,B) gan_mat22f_sub_q(A,B,B)
#define gan_mat22f_decrement(A,B) gan_mat22f_sub_i1(A,B)

/* vector/vector outer product */
#define gan_vec22f_outer_q(p,q,A)\
 (GAN_TEST_OP3(p,q,A,Gan_Vector2_f,Gan_Vector2_f,Gan_Matrix22_f),\
  GAN_REP2_ABC((A)->,=(p)->,*(q)->,xx,xy,x,x,x,y),\
  GAN_REP2_ABC((A)->,=(p)->,*(q)->,yx,yy,y,y,x,y),A)
 
/* matrix/vector multiply */
#define gan_mat22f_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix22_f,Gan_Vector2_f,Gan_Vector2_f),\
  assert((p)!=(q)),\
  GAN_MAT22F_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)
#define gan_mat22Tf_multv2_q(A,p,q)\
 (GAN_TEST_OP3(A,p,q,Gan_Matrix22_f,Gan_Vector2_f,Gan_Vector2_f),\
  assert((p)!=(q)),\
  GAN_MAT22TF_MULT1D((q)->,(A)->,(p)->,x,y,x,y),q)

/* matrix/matrix multiply */
#define gan_mat22f_lmultm22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,Gan_Matrix22_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),C)
#define gan_mat22f_rmultm22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,Gan_Matrix22_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy),C)
#define gan_mat22f_rmultm22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,Gan_Matrix22_f),\
  assert((A)!=(C)&&(B)!=(C)),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy),C)
#define gan_mat22f_lmultm22T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,Gan_SquMatrix22_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT22TF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  (C)->yy = GAN_REP2_OP_AA((A)->,*(B)->,xy,yy,+),C)
#define gan_mat22f_slmultT_q(A,C) gan_mat22f_lmultm22T_sym_q(A,A,C)
#define gan_mat22f_rmultm22T_sym_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_Matrix22_f,Gan_SquMatrix22_f),\
  gan_eval((C)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,xy),\
  (C)->yy = GAN_REP2_OP_AA((A)->,*(B)->,yx,yy,+),C)
#define gan_mat22f_srmultT_q(A,C) gan_mat22f_rmultm22T_sym_q(A,A,C)
#define gan_mat22f_lmults22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_SYM22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),C)
#define gan_mat22f_rmults22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((A)!=(C) && (B)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx),\
  GAN_MAT22F_MULT1D((C)->,(A)->,(B)->,xy,yy,yx,yy),C)
#define gan_symmat22f_lrmultm22T_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix22_f,Gan_Matrix22_f,Gan_Matrix22_f,Gan_SquMatrix22_f),\
  assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX22_F),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xx,yx,xx,yx),\
  GAN_SYM22F_MULT1D((C)->,(A)->,(B)->,xy,yy,xy,yy),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT22TF_MULT1D((D)->,(B)->,(C)->,xx,yx,xx,yx),\
  (D)->yy = GAN_REP2_OP_AA((C)->,*(B)->,xy,yy,+),D)
#define gan_symmat22f_lrmultm22_q(A,B,C,D)\
 (GAN_TEST_OP4(A,B,C,D,\
               Gan_SquMatrix22_f,Gan_Matrix22_f,Gan_Matrix22_f,Gan_SquMatrix22_f),\
  (assert((B)!=(C) && (A)->type == GAN_SYMMETRIC_MATRIX22_F)),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_MAT22F_MULT1D((C)->,(B)->,(A)->,xy,yy,yx,yy),\
  gan_eval((D)->type = GAN_SYMMETRIC_MATRIX22_F),\
  GAN_MAT22F_MULT1D((D)->,(C)->,(B)->,xx,yx,xx,xy),\
  (D)->yy = GAN_REP2_OP_AA((C)->,*(B)->,yx,yy,+),D)
#define gan_mat22f_lmultl22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),C)
#define gan_mat22f_lmultl22_i(A,B) gan_mat22f_lmultl22_q(A,B,A)
#define gan_mat22f_lmultl22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),C)
#define gan_mat22f_lmultl22T_i(A,B) gan_mat22f_lmultl22T_q(A,B,A)
#define gan_mat22f_lmultl22I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),C)
#define gan_mat22f_lmultl22I_i(A,B) gan_mat22f_lmultl22I_q(A,B,A)
#define gan_mat22f_lmultl22IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xx,yx,xx,yx),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xy,yy,xy,yy),C)
#define gan_mat22f_lmultl22IT_i(A,B) gan_mat22f_lmultl22IT_q(A,B,A)
#define gan_mat22f_rmultl22_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,xx,xy,xx,xy),\
  GAN_UPP22F_MULT1D((C)->,(B)->,(A)->,yx,yy,yx,yy),C)
#define gan_mat22f_rmultl22_i(A,B) gan_mat22f_rmultl22_q(A,B,A)
#define gan_mat22f_rmultl22T_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,xx,xy,xx,xy),\
  GAN_LOW22F_MULT1D((C)->,(B)->,(A)->,yx,yy,yx,yy),C)
#define gan_mat22f_rmultl22T_i(A,B) gan_mat22f_rmultl22T_q(A,B,A)
#define gan_mat22f_rmultl22I_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xx,xy),\
  GAN_UPP22IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yx,yy),C)
#define gan_mat22f_rmultl22I_i(A,B) gan_mat22f_rmultl22I_q(A,B,A)
#define gan_mat22f_rmultl22IT_q(A,B,C)\
 (GAN_TEST_OP3(A,B,C,Gan_Matrix22_f,Gan_SquMatrix22_f,Gan_Matrix22_f),\
  assert((B)->type == GAN_LOWER_TRI_MATRIX22_F),\
  assert((B)->xx != 0.0F && (B)->yy != 0.0F),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,xx,xy,xx,xy),\
  GAN_LOW22IF_MULT1D((C)->,(B)->,(A)->,yx,yy,yx,yy),C)
#define gan_mat22f_rmultl22IT_i(A,B) gan_mat22f_rmultl22IT_q(A,B,A)
#define gan_mat22f_invert_q(A,B) gan_mat22f_invert(A,B,NULL)
#define gan_mat22f_invert_i(A)   gan_mat22f_invert(A,A,NULL)

#define gan_mat22f_det_q(A) (GAN_TEST_OP1(A,Gan_Matrix22_f),\
                            ((A)->xx*(A)->yy - (A)->xy*(A)->yx))
#define gan_mat22f_trace_q(A) (GAN_TEST_OP1(A,Gan_Matrix22_f),\
                              ((A)->xx+(A)->yy))
#define gan_mat22f_sumsqr_q(A) (GAN_TEST_OP1(A,Gan_Matrix22_f),\
                               ((A)->xx*(A)->xx+(A)->xy*(A)->xy+\
                                (A)->yx*(A)->yx+(A)->yy*(A)->yy))
#define gan_mat22f_Fnorm_q(A) (GAN_TEST_OP1(A,Gan_Matrix22_f), (float)\
                                 sqrt((A)->xx*(A)->xx+(A)->xy*(A)->xy+\
                                      (A)->yx*(A)->yx+(A)->yy*(A)->yy))

#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_2X2MATF_H */
