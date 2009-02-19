/**
 * File:          $RCSfile: 2x2ltmatTf_noc.h,v $
 * Module:        2x2 lower triangular matrices (transposed, single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.8 $
 * Last edited:   $Date: 2002/04/18 14:56:22 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * Notes:         Not to be compiled separately
 */

#define GAN_MATTYPE Gan_SquMatrix22_f
#define GAN_MATRIX_TYPE Gan_SquMatrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_MAT_FPRINT   gan_ltmat22Tf_fprint
#define GAN_MAT_PRINT    gan_ltmat22Tf_print
#define GAN_MAT_FSCANF   gan_ltmat22Tf_fscanf
#define GAN_FIXED_MATRIX_TYPE GAN_LOWER_TRI_MATRIX22_F

#define gan_ltmat22Tf_fwrite gan_ltmat22f_fwrite
#define gan_ltmat22Tf_fread  gan_ltmat22f_fread
