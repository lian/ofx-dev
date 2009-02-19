/**
 * File:          $RCSfile: image_vfield2D_float.h,v $
 * Module:        2D vector field single precision float images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.12 $
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

#ifndef _GAN_IMAGE_VFIELD2D_FLOAT_H
#define _GAN_IMAGE_VFIELD2D_FLOAT_H

#define GAN_PIXEL struct Gan_Vector2_f
#define GAN_PIXEL_FORMAT 2D vector field
#define GAN_PIXEL_TYPE float
#define GAN_IMTYPE f
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_vfield2D_f
#define GAN_IMAGE_SET_GEN gan_image_set_gen_vfield2D_f
#define GAN_IMAGE_ALLOC gan_image_alloc_vfield2D_f
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_vfield2D_f
#define GAN_IMAGE_FORM gan_image_form_vfield2D_f
#define GAN_IMAGE_FORM_DATA gan_image_form_data_vfield2D_f
#define GAN_IMAGE_SET gan_image_set_vfield2D_f
#define GAN_IMAGE_SET_PIX gan_image_set_pix_vfield2D_f
#define GAN_IMAGE_GET_PIX gan_image_get_pix_vfield2D_f
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_vfield2D_f
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_vfield2D_f
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_vfield2D_f
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_vfield2D_f
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_vfield2D_f
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_vfield2D_f

#include <gandalf/image/image_colour_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_vfield2D_f(h,w)\
           gan_image_form_gen_vfield2D_f(NULL,h,w,(w)*sizeof(Gan_Vector2_f),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_vfield2D_f(img,h,w)\
           gan_image_form_gen_vfield2D_f(img,h,w,(w)*sizeof(Gan_Vector2_f),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_vfield2D_f(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_vfield2D_f(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_data_vfield2D_f(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_vfield2D_f(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_vfield2D_f(img,h,w)\
           gan_image_set_gen_vfield2D_f(img,h,w,(w)*sizeof(Gan_Vector2_f),GAN_TRUE)
#define gan_assert_image_vfield2D_f(img)\
        (assert((img)->format == GAN_VECTOR_FIELD_2D &&\
                (img)->type == GAN_FLOAT))
#ifdef NDEBUG
#define gan_image_set_pix_vfield2D_f(img,row,col,val)\
       ((img)->row_data.vfield2D.f[row][col]=*(val),GAN_TRUE)
#define gan_image_get_pix_vfield2D_f(img,row,col) \
       ((img)->row_data.vfield2D.f[row][col])
#define gan_image_get_pixptr_vfield2D_f(img,row,col) (&(img)->row_data.vfield2D.f[row][col])
#define gan_image_get_pixarr_vfield2D_f(img) ((img)->row_data.vfield2D.f)
#else
#define gan_image_set_pix_vfield2D_f(img,row,col,val)\
           (gan_assert_image_vfield2D_f(img),\
            (img)->set_pix.vfield2D.f(img,row,col,val))
#define gan_image_get_pix_vfield2D_f(img,row,col)\
           (gan_assert_image_vfield2D_f(img),\
            (img)->get_pix.vfield2D.f(img,row,col))
#endif
#define gan_image_fill_const_vfield2D_f(img,val)\
       (gan_assert_image_vfield2D_f(img),\
        (img)->fill_const.vfield2D.f(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_VFIELD2D_FLOAT_H */
