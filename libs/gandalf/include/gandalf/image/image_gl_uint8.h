/**
 * File:          $RCSfile: image_gl_uint8.h,v $
 * Module:        Grey level 8-bit images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.3 $
 * Last edited:   $Date: 2005/02/10 20:19:17 $
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

#ifndef _GAN_IMAGE_GL_UINT8_H
#define _GAN_IMAGE_GL_UINT8_H

#include <gandalf/common/misc_defs.h>

#ifdef GAN_UINT8

#ifdef GAN_GENERATE_DOCUMENTATION

#define GAN_PIXEL gan_uint8
#define GAN_PIXEL_FORMAT grey-level
#define GAN_PIXEL_TYPE 8-bit unsigned integer

#define GAN_IMAGE_FORM_GEN gan_image_form_gen_gl_ui8
#define GAN_IMAGE_SET_GEN gan_image_set_gen_gl_ui8
#define GAN_IMAGE_ALLOC gan_image_alloc_gl_ui8
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_gl_ui8
#define GAN_IMAGE_FORM gan_image_form_gl_ui8
#define GAN_IMAGE_FORM_DATA gan_image_form_data_gl_ui8
#define GAN_IMAGE_SET gan_image_set_gl_ui8
#define GAN_IMAGE_SET_PIX gan_image_set_pix_gl_ui8
#define GAN_IMAGE_GET_PIX gan_image_get_pix_gl_ui8
#define GAN_IMAGE_GET_PIXPTR gan_image_get_pixptr_gl_ui8
#define GAN_IMAGE_GET_PIXARR gan_image_get_pixarr_gl_ui8
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_gl_ui8
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_gl_ui8
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_gl_ui8
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_gl_ui8

#include <gandalf/image/image_grey_noc.h>

#else

#if (SIZEOF_CHAR == 1)

#include <gandalf/image/image_gl_uchar.h>

#define gan_image_form_gen_gl_ui8(img,h,w,s,a,pdata,pdsize,rdata,rdsize) \
        gan_image_form_gen_gl_uc(img,h,w,s,a,pdata,pdsize,rdata,rdsize)
#define gan_image_set_gen_gl_ui8(img,h,w,s,a) \
        gan_image_set_gen_gl_uc(img,h,w,s,a)
#define gan_image_get_active_subwindow_gl_ui8(img,align,subwin) \
        gan_image_get_active_subwindow_gl_uc(img,align,subwin)
#define gan_image_mask_window_gl_ui8(img,r0,c0,h,w) \
        gan_image_mask_window_gl_uc(img,r0,c0,h,w)
#define gan_image_clear_window_gl_ui8(img,r0,c0,h,w) \
        gan_image_clear_window_gl_uc(img,r0,c0,h,w)
#define gan_image_set_pix_gl_ui8(img,row,col,val) \
        gan_image_set_pix_gl_uc(img,row,col,val)
#define gan_image_get_pix_gl_ui8(img,row,col) \
        gan_image_get_pix_gl_uc(img,row,col)
#define gan_image_get_pixptr_gl_ui8(img,row,col) \
        gan_image_get_pixptr_gl_uc(img,row,col)
#define gan_image_get_pixarr_gl_ui8(img) \
        gan_image_get_pixarr_gl_uc(img)
#define gan_image_fill_const_gl_ui8(img,val) \
        gan_image_fill_const_gl_uc(img,val)
#define gan_image_alloc_gl_ui8(h,w) gan_image_alloc_gl_uc(h,w)
#define gan_image_form_gl_ui8(img,h,w) gan_image_form_gl_uc(img,h,w)
#define gan_image_alloc_data_gl_ui8(h,w,s,pd,pds,rd,rds) \
        gan_image_alloc_data_gl_uc(h,w,s,pd,pds,rd,rds)
#define gan_image_form_data_gl_ui8(img,h,w,s,pd,pds,rd,rds) \
        gan_image_form_data_gl_uc(img,h,w,s,pd,pds,rd,rds)
#define gan_image_set_gl_ui8(img,h,w) gan_image_set_gl_uc(img,h,w)
#define gan_assert_image_grey_ui8(img) gan_assert_image_grey_uc(img)

#else

#error "8-bit type conflict"

#endif /* #if (SIZEOF_CHAR == 1) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#endif /* #ifdef GAN_UINT8 */

#endif /* #ifndef _GAN_IMAGE_GL_UINT8_H */
