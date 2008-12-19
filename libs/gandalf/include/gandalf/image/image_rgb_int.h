/**
 * File:          $RCSfile: image_rgb_int.h,v $
 * Module:        RGB colour signed integer images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.20 $
 * Last edited:   $Date: 2004/11/20 00:53:11 $
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

#ifndef _GAN_IMAGE_RGB_INT_H
#define _GAN_IMAGE_RGB_INT_H

#define GAN_PIXEL struct Gan_RGBPixel_i
#define GAN_PIXEL_FORMAT RGB colour
#define GAN_PIXEL_TYPE int
#define GAN_IMTYPE i
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_rgb_i
#define GAN_IMAGE_SET_GEN gan_image_set_gen_rgb_i
#define GAN_IMAGE_ALLOC gan_image_alloc_rgb_i
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_rgb_i
#define GAN_IMAGE_FORM gan_image_form_rgb_i
#define GAN_IMAGE_FORM_DATA gan_image_form_data_rgb_i
#define GAN_IMAGE_SET gan_image_set_rgb_i
#define GAN_IMAGE_SET_PIX gan_image_set_pix_rgb_i
#define GAN_IMAGE_GET_PIX gan_image_get_pix_rgb_i
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_rgb_i
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_rgb_i
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_rgb_i
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_rgb_i
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_rgb_i
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_rgb_i
#define GAN_IMAGE_GET_MINIMUM_PIXEL gan_image_get_minimum_pixel_rgb_i
#define GAN_IMAGE_GET_MAXIMUM_PIXEL gan_image_get_maximum_pixel_rgb_i

#include <gandalf/image/image_colour_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_rgb_i(h,w)\
           gan_image_form_gen_rgb_i(NULL,h,w,(w)*sizeof(Gan_RGBPixel_i),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_rgb_i(img,h,w)\
           gan_image_form_gen_rgb_i(img,h,w,(w)*sizeof(Gan_RGBPixel_i),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_rgb_i(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_rgb_i(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_data_rgb_i(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_rgb_i(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_rgb_i(img,h,w)\
           gan_image_set_gen_rgb_i(img,h,w,(w)*sizeof(Gan_RGBPixel_i),GAN_TRUE)
#define gan_assert_image_rgb_i(img)\
        (assert((img)->format == GAN_RGB_COLOUR_IMAGE &&\
                (img)->type == GAN_INT))
#ifdef NDEBUG
#define gan_image_set_pix_rgb_i(img,row,col,val)\
       ((img)->row_data.rgb.i[row][col]=*(val),GAN_TRUE)
#define gan_image_get_pix_rgb_i(img,row,col) \
       ((img)->row_data.rgb.i[row][col])
#define gan_image_get_pixptr_rgb_i(img,row,col) (&(img)->row_data.rgb.i[row][col])
#define gan_image_get_pixarr_rgb_i(img) ((img)->row_data.rgb.i)
#else
#define gan_image_set_pix_rgb_i(img,row,col,val)\
       (gan_assert_image_rgb_i(img), (img)->set_pix.rgb.i(img,row,col,val))
#define gan_image_get_pix_rgb_i(img,row,col)\
       (gan_assert_image_rgb_i(img), (img)->get_pix.rgb.i(img,row,col))
#endif
#define gan_image_fill_const_rgb_i(img,val)\
       (gan_assert_image_rgb_i(img), (img)->fill_const.rgb.i(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_IMAGE_RGB_INT_H */
