/**
 * File:          $RCSfile: image_bgr_float64.h,v $
 * Module:        BGR colour 64-bit float images
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

#ifndef _GAN_IMAGE_BGR_FLOAT64_H
#define _GAN_IMAGE_BGR_FLOAT64_H

#include <gandalf/common/misc_defs.h>

#ifdef GAN_FLOAT64

#ifdef GAN_GENERATE_DOCUMENTATION

#define GAN_PIXEL Gan_BGRPixel_f64
#define GAN_PIXEL_FORMAT BGR colour
#define GAN_PIXEL_TYPE 64-bit float

#define GAN_IMAGE_FORM_GEN gan_image_form_gen_bgr_f64
#define GAN_IMAGE_SET_GEN gan_image_set_gen_bgr_f64
#define GAN_IMAGE_ALLOC gan_image_alloc_bgr_f64
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_bgr_f64
#define GAN_IMAGE_FORM gan_image_form_bgr_f64
#define GAN_IMAGE_FORM_DATA gan_image_form_data_bgr_f64
#define GAN_IMAGE_SET gan_image_set_bgr_f64
#define GAN_IMAGE_SET_PIX gan_image_set_pix_bgr_f64
#define GAN_IMAGE_GET_PIX gan_image_get_pix_bgr_f64
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_bgr_f64
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_bgr_f64
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_bgr_f64
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_bgr_f64
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_bgr_f64
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_bgr_f64

#include <gandalf/image/image_colour_noc.h>

#else

#if (SIZEOF_DOUBLE == 8)

#include <gandalf/image/image_bgr_double.h>

#define gan_image_form_gen_bgr_f64(img,h,w,s,a,pdata,pdsize,rdata,rdsize) \
        gan_image_form_gen_bgr_d(img,h,w,s,a,pdata,pdsize,rdata,rdsize)
#define gan_image_set_gen_bgr_f64(img,h,w,s,a) \
        gan_image_set_gen_bgr_d(img,h,w,s,a)
#define gan_image_set_pix_bgr_f64(img,row,col,val) \
        gan_image_set_pix_bgr_d(img,row,col,val)
#define gan_image_get_pix_bgr_f64(img,row,col) \
        gan_image_get_pix_bgr_d(img,row,col)
#define gan_image_get_pixptr_bgr_f64(img,row,col) \
        gan_image_get_pixptr_bgr_d(img,row,col)
#define gan_image_get_pixarr_bgr_f64(img) \
        gan_image_get_pixarr_bgr_d(img)
#define gan_image_fill_const_bgr_f64(img,val) \
        gan_image_fill_const_bgr_d(img,val)
#define gan_image_alloc_bgr_f64(h,w) gan_image_alloc_bgr_d(h,w)
#define gan_image_form_bgr_f64(img,h,w) gan_image_form_bgr_d(img,h,w)
#define gan_image_alloc_data_bgr_f64(h,w,s,pd,pds,rd,rds) \
        gan_image_alloc_data_bgr_d(h,w,s,pd,pds,rd,rds)
#define gan_image_form_data_bgr_f64(img,h,w,s,pd,pds,rd,rds) \
        gan_image_form_data_bgr_d(img,h,w,s,pd,pds,rd,rds)
#define gan_image_set_bgr_f64(img,h,w) gan_image_set_bgr_d(img,h,w)
#define gan_assert_image_grey_f64(img) gan_assert_image_grey_d(img)

#else

#error "64-bit float type conflict"

#endif /* #if (SIZEOF_DOUBLE == 8) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifdef GAN_FLOAT64 */

#endif /* #ifndef _GAN_IMAGE_BGR_FLOAT64_H */
