/**
 * File:          $RCSfile: image_vfield3D_int.h,v $
 * Module:        3D vector field signed integer images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.19 $
 * Last edited:   $Date: 2005/04/15 02:15:06 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
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

#ifndef _GAN_IMAGE_VFIELD3D_INT_H
#define _GAN_IMAGE_VFIELD3D_INT_H

#define GAN_PIXEL struct Gan_Vector3_i
#define GAN_PIXEL_FORMAT 3D vector field
#define GAN_PIXEL_TYPE int
#define GAN_IMTYPE i
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_vfield3D_i
#define GAN_IMAGE_SET_GEN gan_image_set_gen_vfield3D_i
#define GAN_IMAGE_ALLOC gan_image_alloc_vfield3D_i
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_vfield3D_i
#define GAN_IMAGE_FORM gan_image_form_vfield3D_i
#define GAN_IMAGE_FORM_DATA gan_image_form_data_vfield3D_i
#define GAN_IMAGE_SET gan_image_set_vfield3D_i
#define GAN_IMAGE_SET_PIX gan_image_set_pix_vfield3D_i
#define GAN_IMAGE_GET_PIX gan_image_get_pix_vfield3D_i
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_vfield3D_i
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_vfield3D_i
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_vfield3D_i
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_vfield3D_i
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_vfield3D_i
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_vfield3D_i

#include <gandalf/image/image_colour_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_vfield3D_i(h,w)\
           gan_image_form_gen_vfield3D_i(NULL,h,w,(w)*sizeof(Gan_Vector3_i),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_vfield3D_i(img,h,w)\
           gan_image_form_gen_vfield3D_i(img,h,w,(w)*sizeof(Gan_Vector3_i),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_vfield3D_i(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_vfield3D_i(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_data_vfield3D_i(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_vfield3D_i(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_vfield3D_i(img,h,w)\
           gan_image_set_gen_vfield3D_i(img,h,w,(w)*sizeof(Gan_Vector3_i),GAN_TRUE)
#define gan_assert_image_vfield3D_i(img)\
        (assert((img)->format == GAN_VECTOR_FIELD_3D &&\
                (img)->type == GAN_INT))
#ifdef NDEBUG
#define gan_image_set_pix_vfield3D_i(img,row,col,val)\
       ((img)->row_data.vfield3D.i[row][col]=*(val),GAN_TRUE)
#define gan_image_get_pix_vfield3D_i(img,row,col) \
       ((img)->row_data.vfield3D.i[row][col])
#define gan_image_get_pixptr_vfield3D_i(img,row,col) (&(img)->row_data.vfield3D.i[row][col])
#define gan_image_get_pixarr_vfield3D_i(img) ((img)->row_data.vfield3D.i)
#else
#define gan_image_set_pix_vfield3D_i(img,row,col,val)\
           (gan_assert_image_vfield3D_i(img),\
            (img)->set_pix.vfield3D.i(img,row,col,val))
#define gan_image_get_pix_vfield3D_i(img,row,col)\
           (gan_assert_image_vfield3D_i(img),\
            (img)->get_pix.vfield3D.i(img,row,col))
#endif
#define gan_image_fill_const_vfield3D_i(img,val)\
       (gan_assert_image_vfield3D_i(img),\
        (img)->fill_const.vfield3D.i(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_VFIELD3D_INT_H */
