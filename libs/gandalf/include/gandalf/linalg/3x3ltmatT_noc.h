/**
 * File:          $RCSfile: 3x3ltmatT_noc.h,v $
 * Module:        3x3 lower triangular matrices (transposed, double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.9 $
 * Last edited:   $Date: 2002/04/18 14:56:23 $
 * Author:        $Author: pm $
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

#define GAN_MATTYPE Gan_SquMatrix33
#define GAN_MATRIX_TYPE Gan_SquMatrix
#define GAN_SQUMATRIX_TYPE Gan_SquMatrix
#define GAN_VECTOR_TYPE Gan_Vector
#define GAN_MAT_ELEMENT_TYPE GAN_DOUBLE
#define GAN_REALTYPE double
#define GAN_MAT_FPRINT   gan_ltmat33T_fprint
#define GAN_MAT_PRINT    gan_ltmat33T_print
#define GAN_MAT_FSCANF   gan_ltmat33T_fscanf
#define GAN_FIXED_MATRIX_TYPE GAN_LOWER_TRI_MATRIX33

#define gan_ltmat33T_fwrite gan_ltmat33_fwrite
#define gan_ltmat33T_fread  gan_ltmat33_fread
