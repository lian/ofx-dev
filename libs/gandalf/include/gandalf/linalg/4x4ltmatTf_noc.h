/**
 * File:          $RCSfile: 4x4ltmatTf_noc.h,v $
 * Module:        4x4 lower triangular matrices (transposed, single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.8 $
 * Last edited:   $Date: 2002/04/18 14:56:23 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * Notes:         Not to be compiled separately
 */

#define GAN_MATTYPE Gan_SquMatrix44_f
#define GAN_MATRIX_TYPE Gan_SquMatrix_f
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix_f
#define GAN_VECTOR_TYPE Gan_Vector_f
#define GAN_MAT_ELEMENT_TYPE GAN_FLOAT
#define GAN_REALTYPE float
#define GAN_MAT_FPRINT   gan_ltmat44Tf_fprint
#define GAN_MAT_PRINT    gan_ltmat44Tf_print
#define GAN_MAT_FSCANF   gan_ltmat44Tf_fscanf
#define GAN_FIXED_MATRIX_TYPE GAN_LOWER_TRI_MATRIX44_F

#define gan_ltmat44Tf_fwrite gan_ltmat44f_fwrite
#define gan_ltmat44Tf_fread  gan_ltmat44f_fread
