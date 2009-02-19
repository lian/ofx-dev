/**
 * File:          $RCSfile: image_gl_int.h,v $
 * Module:        Grey level signed integer images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.14 $
 * Last edited:   $Date: 2004/05/13 15:31:53 $
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

#ifndef _GAN_IMAGE_GL_INT_H
#define _GAN_IMAGE_GL_INT_H

#define GAN_PIXEL int
#define GAN_PIXEL_FORMAT grey-level
#define GAN_PIXEL_TYPE int
#define GAN_IMTYPE i
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_gl_i
#define GAN_IMAGE_SET_GEN gan_image_set_gen_gl_i
#define GAN_IMAGE_ALLOC gan_image_alloc_gl_i
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_gl_i
#define GAN_IMAGE_FORM gan_image_form_gl_i
#define GAN_IMAGE_FORM_DATA gan_image_form_data_gl_i
#define GAN_IMAGE_SET gan_image_set_gl_i
#define GAN_IMAGE_SET_PIX gan_image_set_pix_gl_i
#define GAN_IMAGE_GET_PIX gan_image_get_pix_gl_i
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_gl_i
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_gl_i
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_gl_i
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_gl_i
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_gl_i
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_gl_i
#define GAN_IMAGE_GET_MINIMUM_PIXEL gan_image_get_minimum_pixel_gl_i
#define GAN_IMAGE_GET_MAXIMUM_PIXEL gan_image_get_maximum_pixel_gl_i

#include <gandalf/image/image_grey_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_gl_i(h,w)\
           gan_image_form_gen_gl_i(NULL,h,w,(w)*sizeof(int),GAN_TRUE,NULL,0,NULL,0)

#define gan_image_form_gl_i(img,h,w)\
           gan_image_form_gen_gl_i(img,h,w,(w)*sizeof(int),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_gl_i(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_gl_i(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_data_gl_i(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_gl_i(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_gl_i(img,h,w) gan_image_set_gen_gl_i(img,h,w,(w)*sizeof(int),GAN_TRUE)
#define gan_assert_image_grey_i(img)\
        (assert((img)->format == GAN_GREY_LEVEL_IMAGE &&\
                (img)->type == GAN_INT))
#ifdef NDEBUG
#define gan_image_set_pix_gl_i(img,row,col,val)\
       ((img)->row_data.gl.i[row][col]=(val),GAN_TRUE)
#define gan_image_get_pix_gl_i(img,row,col) ((img)->row_data.gl.i[row][col])
#define gan_image_get_pixptr_gl_i(img,row,col) (&(img)->row_data.gl.i[row][col])
#define gan_image_get_pixarr_gl_i(img) ((img)->row_data.gl.i)
#else
#define gan_image_set_pix_gl_i(img,row,col,val)\
       (gan_assert_image_grey_i(img), (img)->set_pix.gl.i(img,row,col,val))
#define gan_image_get_pix_gl_i(img,row,col)\
       (gan_assert_image_grey_i(img), (img)->get_pix.gl.i(img,row,col))
#endif
#define gan_image_fill_const_gl_i(img,val)\
       (gan_assert_image_grey_i(img), (img)->fill_const.gl.i(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_IMAGE_GL_INT_H */
