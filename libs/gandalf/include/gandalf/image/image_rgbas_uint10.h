/**
 * File:          $RCSfile: image_rgbas_uint10.h,v $
 * Module:        RGB colour with 2-bit padding for 10-bit images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.3 $
 * Last edited:   $Date: 2005/06/30 14:38:34 $
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

#ifndef _GAN_IMAGE_RGBAS_UINT10_H
#define _GAN_IMAGE_RGBAS_UINT10_H

#define GAN_PIXEL struct Gan_RGBASPixel_ui10
#define GAN_PIXEL_FORMAT RGBA colour
#define GAN_PIXEL_TYPE gan_uint16
#define GAN_IMTYPE ui10
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_rgbas_ui10
#define GAN_IMAGE_SET_GEN gan_image_set_gen_rgbas_ui10
#define GAN_IMAGE_ALLOC gan_image_alloc_rgbas_ui10
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_rgbas_ui10
#define GAN_IMAGE_FORM gan_image_form_rgbas_ui10
#define GAN_IMAGE_FORM_DATA gan_image_form_data_rgbas_ui10
#define GAN_IMAGE_SET gan_image_set_rgbas_ui10
#define GAN_IMAGE_SET_PIX gan_image_set_pix_rgbas_ui10
#define GAN_IMAGE_GET_PIX gan_image_get_pix_rgbas_ui10
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_rgbas_ui10
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_rgbas_ui10
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_rgbas_ui10
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_rgbas_ui10
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_rgbas_ui10
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_rgbas_ui10
#define GAN_IMAGE_GET_MINIMUM_PIXEL gan_image_get_minimum_pixel_rgbas_ui10
#define GAN_IMAGE_GET_MAXIMUM_PIXEL gan_image_get_maximum_pixel_rgbas_ui10

#include <gandalf/image/image_colour_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_rgbas_ui10(h,w)\
           gan_image_form_gen_rgbas_ui10(NULL,h,w,(w)*sizeof(Gan_RGBASPixel_ui10),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_rgbas_ui10(img,h,w)\
           gan_image_form_gen_rgbas_ui10(img,h,w,(w)*sizeof(Gan_RGBASPixel_ui10),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_rgbas_ui10(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_rgbas_ui10(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_data_rgbas_ui10(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_rgbas_ui10(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_rgbas_ui10(img,h,w)\
           gan_image_set_gen_rgbas_ui10(img,h,w,(w)*sizeof(Gan_RGBASPixel_ui10),GAN_TRUE)
#define gan_assert_image_rgbas_ui10(img)\
        (assert((img)->format == GAN_RGBAS &&\
                (img)->type == GAN_UINT10))
#ifdef NDEBUG
#define gan_image_set_pix_rgbas_ui10(img,row,col,val)\
       ((img)->row_data.rgbas.ui10[row][col]=*(val),GAN_TRUE)
#define gan_image_get_pix_rgbas_ui10(img,row,col) \
       ((img)->row_data.rgbas.ui10[row][col])
#define gan_image_get_pixptr_rgbas_ui10(img,row,col) (&(img)->row_data.rgbas.ui10[row][col])
#define gan_image_get_pixarr_rgbas_ui10(img) ((img)->row_data.rgbas.ui10)
#else
#define gan_image_set_pix_rgbas_ui10(img,row,col,val)\
       (gan_assert_image_rgbas_ui10(img), (img)->set_pix.rgbas.ui10(img,row,col,val))
#define gan_image_get_pix_rgbas_ui10(img,row,col)\
       (gan_assert_image_rgbas_ui10(img), (img)->get_pix.rgbas.ui10(img,row,col))
#endif
#define gan_image_fill_const_rgbas_ui10(img,val)\
       (gan_assert_image_rgbas_ui10(img), (img)->fill_const.rgbas.ui10(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifndef _GAN_IMAGE_RGBAS_UINT10_H */
