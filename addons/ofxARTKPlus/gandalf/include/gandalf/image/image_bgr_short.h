/**
 * File:          $RCSfile: image_bgr_short.h,v $
 * Module:        BGR colour signed short integer images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.2 $
 * Last edited:   $Date: 2006/09/15 20:43:36 $
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

#ifndef _GAN_IMAGE_BGR_SHORT_H
#define _GAN_IMAGE_BGR_SHORT_H

#define GAN_PIXEL struct Gan_BGRPixel_s
#define GAN_PIXEL_FORMAT BGR colour
#define GAN_PIXEL_TYPE short
#define GAN_IMTYPE s
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_bgr_s
#define GAN_IMAGE_SET_GEN gan_image_set_gen_bgr_s
#define GAN_IMAGE_ALLOC gan_image_alloc_bgr_s
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_bgr_s
#define GAN_IMAGE_FORM gan_image_form_bgr_s
#define GAN_IMAGE_FORM_DATA gan_image_form_data_bgr_s
#define GAN_IMAGE_SET gan_image_set_bgr_s
#define GAN_IMAGE_SET_PIX gan_image_set_pix_bgr_s
#define GAN_IMAGE_GET_PIX gan_image_get_pix_bgr_s
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_bgr_s
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_bgr_s
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_bgr_s
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_bgr_s
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_bgr_s
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_bgr_s
#define GAN_IMAGE_GET_MINIMUM_PIXEL gan_image_get_minimum_pixel_bgr_s
#define GAN_IMAGE_GET_MAXIMUM_PIXEL gan_image_get_maximum_pixel_bgr_s

#include <gandalf/image/image_colour_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_bgr_s(h,w)\
           gan_image_form_gen_bgr_s(NULL,h,w,(w)*sizeof(Gan_BGRPixel_s),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_bgr_s(img,h,w)\
           gan_image_form_gen_bgr_s(img,h,w,(w)*sizeof(Gan_BGRPixel_s),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_bgr_s(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_bgr_s(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_data_bgr_s(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_bgr_s(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_bgr_s(img,h,w)\
           gan_image_set_gen_bgr_s(img,h,w,(w)*sizeof(Gan_BGRPixel_s),GAN_TRUE)
#define gan_assert_image_bgr_s(img)\
        (assert((img)->format == GAN_BGR_COLOUR_IMAGE &&\
                (img)->type == GAN_SHORT))
#ifdef NDEBUG
#define gan_image_set_pix_bgr_s(img,row,col,val)\
       ((img)->row_data.bgr.s[row][col]=*(val),GAN_TRUE)
#define gan_image_get_pix_bgr_s(img,row,col) \
       ((img)->row_data.bgr.s[row][col])
#define gan_image_get_pixptr_bgr_s(img,row,col) (&(img)->row_data.bgr.s[row][col])
#define gan_image_get_pixarr_bgr_s(img) ((img)->row_data.bgr.s)
#else
#define gan_image_set_pix_bgr_s(img,row,col,val)\
       (gan_assert_image_bgr_s(img), (img)->set_pix.bgr.s(img,row,col,val))
#define gan_image_get_pix_bgr_s(img,row,col)\
       (gan_assert_image_bgr_s(img), (img)->get_pix.bgr.s(img,row,col))
#endif
#define gan_image_fill_const_bgr_s(img,val)\
       (gan_assert_image_bgr_s(img), (img)->fill_const.bgr.s(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_IMAGE_BGR_SHORT_H */
