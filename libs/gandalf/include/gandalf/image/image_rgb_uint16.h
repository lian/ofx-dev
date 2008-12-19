/**
 * File:          $RCSfile: image_rgb_uint16.h,v $
 * Module:        RGB colour 16-bit images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.2 $
 * Last edited:   $Date: 2004/05/18 17:31:55 $
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

#ifndef _GAN_IMAGE_RGB_UINT16_H
#define _GAN_IMAGE_RGB_UINT16_H

#include <gandalf/common/misc_defs.h>

#ifdef GAN_UINT16

#ifdef GAN_GENERATE_DOCUMENTATION

#define GAN_PIXEL Gan_RGBPixel_ui16
#define GAN_PIXEL_FORMAT RGB colour
#define GAN_PIXEL_TYPE 16-bit unsigned integer

#define GAN_IMAGE_FORM_GEN gan_image_form_gen_rgb_ui16
#define GAN_IMAGE_SET_GEN gan_image_set_gen_rgb_ui16
#define GAN_IMAGE_ALLOC gan_image_alloc_rgb_ui16
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_rgb_ui16
#define GAN_IMAGE_FORM gan_image_form_rgb_ui16
#define GAN_IMAGE_FORM_DATA gan_image_form_data_rgb_ui16
#define GAN_IMAGE_SET gan_image_set_rgb_ui16
#define GAN_IMAGE_SET_PIX gan_image_set_pix_rgb_ui16
#define GAN_IMAGE_GET_PIX gan_image_get_pix_rgb_ui16
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_rgb_ui16
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_rgb_ui16
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_rgb_ui16
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_rgb_ui16
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_rgb_ui16
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_rgb_ui16

#include <gandalf/image/image_colour_noc.h>

#else

#if (SIZEOF_SHORT == 2)

#include <gandalf/image/image_rgb_ushort.h>

#define gan_image_form_gen_rgb_ui16(img,h,w,s,a,pdata,pdsize,rdata,rdsize) \
        gan_image_form_gen_rgb_us(img,h,w,s,a,pdata,pdsize,rdata,rdsize)
#define gan_image_set_gen_rgb_ui16(img,h,w,s,a) \
        gan_image_set_gen_rgb_us(img,h,w,s,a)
#define gan_image_set_pix_rgb_ui16(img,row,col,val) \
        gan_image_set_pix_rgb_us(img,row,col,val)
#define gan_image_get_pix_rgb_ui16(img,row,col) \
        gan_image_get_pix_rgb_us(img,row,col)
#define gan_image_get_pixptr_rgb_ui16(img,row,col) \
        gan_image_get_pixptr_rgb_us(img,row,col)
#define gan_image_get_pixarr_rgb_ui16(img) \
        gan_image_get_pixarr_rgb_us(img)
#define gan_image_fill_const_rgb_ui16(img,val) \
        gan_image_fill_const_rgb_us(img,val)
#define gan_image_alloc_rgb_ui16(h,w) gan_image_alloc_rgb_us(h,w)
#define gan_image_form_rgb_ui16(img,h,w) gan_image_form_rgb_us(img,h,w)
#define gan_image_alloc_data_rgb_ui16(h,w,s,pd,pds,rd,rds) \
        gan_image_alloc_data_rgb_us(h,w,s,pd,pds,rd,rds)
#define gan_image_form_data_rgb_ui16(img,h,w,s,pd,pds,rd,rds) \
        gan_image_form_data_rgb_us(img,h,w,s,pd,pds,rd,rds)
#define gan_image_set_rgb_ui16(img,h,w) gan_image_set_rgb_us(img,h,w)
#define gan_assert_image_grey_ui16(img) gan_assert_image_grey_us(img)

#else

#error "16-bit type conflict"

#endif /* #if (SIZEOF_SHORT == 2) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifdef GAN_UINT16 */

#endif /* #ifndef _GAN_IMAGE_RGB_UINT16_H */
