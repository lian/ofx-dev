/**
 * File:          $RCSfile: image_pointer.h,v $
 * Module:        Images of pointers
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.21 $
 * Last edited:   $Date: 2004/03/17 16:14:20 $
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

#ifndef _GAN_IMAGE_POINTER_H
#define _GAN_IMAGE_POINTER_H

#define GAN_PIXEL void *
#define GAN_PIXEL_FORMAT grey-level
#define GAN_PIXEL_TYPE void *
#define GAN_IMTYPE p
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_p
#define GAN_IMAGE_SET_GEN gan_image_set_gen_p
#define GAN_IMAGE_ALLOC gan_image_alloc_p
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_p
#define GAN_IMAGE_FORM gan_image_form_p
#define GAN_IMAGE_FORM_DATA gan_image_form_data_p
#define GAN_IMAGE_SET gan_image_set_p
#define GAN_IMAGE_SET_PIX gan_image_set_pix_p
#define GAN_IMAGE_GET_PIX gan_image_get_pix_p
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_p
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_p
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_p
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_p
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_p
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_p

#include <gandalf/image/image_grey_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_p(h,w)\
           gan_image_form_gen_p(NULL,h,w,(w)*sizeof(void *),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_p(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_p(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_p(img,h,w)\
           gan_image_form_gen_p(img,h,w,(w)*sizeof(void *),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_data_p(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_p(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_p(img,h,w) gan_image_set_gen_p(img,h,w,(w)*sizeof(void *),GAN_TRUE)
#define gan_assert_image_p(img)\
        (assert((img)->format == GAN_GREY_LEVEL_IMAGE &&\
                (img)->type == GAN_POINTER))
#ifdef NDEBUG
#define gan_image_set_pix_p(img,row,col,ptr)\
       ((img)->row_data.gl.p[row][col]=(ptr),GAN_TRUE)
#define gan_image_get_pix_p(img,row,col) ((img)->row_data.gl.p[row][col])
#define gan_image_get_pixptr_p(img,row,col) (&(img)->row_data.gl.p[row][col])
#define gan_image_get_pixarr_p(img) ((img)->row_data.gl.p)
#else
#define gan_image_set_pix_p(img,row,col,ptr)\
       (gan_assert_image_p(img), (img)->set_pix.gl.p(img,row,col,ptr))
#define gan_image_get_pix_p(img,row,col)\
       (gan_assert_image_p(img), (img)->get_pix.gl.p(img,row,col))
#endif
#define gan_image_fill_const_p(img,ptr)\
       (gan_assert_image_p(img), (img)->fill_const.gl.p(img,ptr))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_POINTER_H */
