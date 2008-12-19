/**
 * File:          $RCSfile: image_bit.h,v $
 * Module:        Binary images
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.38 $
 * Last edited:   $Date: 2005/08/22 08:52:19 $
 * Author:        $Author: jps $
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

#ifndef _GAN_IMAGE_BIT_H
#define _GAN_IMAGE_BIT_H

#include <gandalf/common/bit_array.h>

#define GAN_PIXEL Gan_BitWord
#define GAN_PIXEL_FORMAT grey-level
#define GAN_PIXEL_TYPE Gan_Bool
#define GAN_IMTYPE b
#define GAN_IMAGE_FORM_GEN gan_image_form_gen_b
#define GAN_IMAGE_SET_GEN gan_image_set_gen_b
#define GAN_IMAGE_ALLOC gan_image_alloc_b
#define GAN_IMAGE_ALLOC_DATA gan_image_alloc_data_b
#define GAN_IMAGE_FORM gan_image_form_b
#define GAN_IMAGE_FORM_DATA gan_image_form_data_b
#define GAN_IMAGE_SET gan_image_set_b
#define GAN_IMAGE_SET_PIX gan_image_set_pix_b
#define GAN_IMAGE_GET_PIX gan_image_get_pix_b
#define GAN_IMAGE_FILL_CONST gan_image_fill_const_b
#define GAN_IMAGE_GET_ACTIVE_SUBWINDOW gan_image_get_active_subwindow_b
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_b
#define GAN_IMAGE_MASK_WINDOW gan_image_mask_window_b
#define GAN_IMAGE_CLEAR_WINDOW gan_image_clear_window_b

/* to generate bitmap-specific code */
#define GAN_BITMAP

#include <gandalf/image/image_grey_noc.h>

#ifndef GAN_GENERATE_DOCUMENTATION
#define gan_image_alloc_b(h,w)\
           gan_image_form_gen_b(NULL,h,w,(((w)+GAN_BITWORD_SIZE-1)/GAN_BITWORD_SIZE)*sizeof(Gan_BitWord),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_alloc_data_b(h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_b(NULL,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_form_b(img,h,w)\
           gan_image_form_gen_b(img,h,w,(((w)+GAN_BITWORD_SIZE-1)/GAN_BITWORD_SIZE)*sizeof(Gan_BitWord),GAN_TRUE,NULL,0,NULL,0)
#define gan_image_form_data_b(img,h,w,s,pd,pds,rd,rds)\
           gan_image_form_gen_b(img,h,w,s,GAN_FALSE,pd,pds,rd,rds)
#define gan_image_set_b(img,h,w) gan_image_set_gen_b(img,h,w,(((w)+GAN_BITWORD_SIZE-1)/GAN_BITWORD_SIZE)*sizeof(Gan_BitWord),GAN_TRUE)
#define gan_assert_image_b(img)\
        (assert((img)->format == GAN_GREY_LEVEL_IMAGE &&\
                (img)->type == GAN_BOOL))
#ifdef NDEBUG
#define gan_image_set_pix_b(img,row,col,val)\
       (gan_bit_array_twiddle_bit(&(img)->ba[row],(col),(val)),GAN_TRUE)
#define gan_image_get_pix_b(img,row,col)\
       (gan_bit_array_get_bit(&(img)->ba[row],(col)) ? GAN_TRUE : GAN_FALSE)
#else
#define gan_image_set_pix_b(img,row,col,val)\
       (gan_assert_image_b(img), (img)->set_pix.gl.b(img,row,col,val))
#define gan_image_get_pix_b(img,row,col)\
       (gan_assert_image_b(img), (img)->get_pix.gl.b(img,row,col))
#endif
#define gan_image_fill_const_b(img,val)\
       (gan_assert_image_b(img), (img)->fill_const.gl.b(img,val))
#endif /* #ifndef GAN_GENERATE_DOCUMENTATION */

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageBinary
 * \{
 */

#ifdef NDEBUG
#define gan_image_bit_get_pix_4group(img,row,col)\
        (gan_bit_array_get_bit ( &(img)->ba[row],     col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     (col)+1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], (col)+1 ))
#define gan_image_bit_get_pix_5group(img,row,col)\
        (gan_bit_array_get_bit ( &(img)->ba[(row)-1], col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     (col)-1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     (col)+1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], col     ))
#define gan_image_bit_get_pix_9group(img,row,col)\
        (gan_bit_array_get_bit ( &(img)->ba[(row)-1], (col)-1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)-1], col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)-1], (col)+1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     (col)-1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     (col)+1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], (col)-1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], (col)+1))
#define gan_image_bit_get_pix_3group_horiz(img,row,col)\
        (gan_bit_array_get_bit ( &(img)->ba[row], (col)-1 ) && \
         gan_bit_array_get_bit ( &(img)->ba[row], col     ) && \
         gan_bit_array_get_bit ( &(img)->ba[row], (col)+1 ))
#define gan_image_bit_get_pix_3group_vert(img,row,col)\
        (gan_bit_array_get_bit ( &(img)->ba[(row)-1], col ) && \
         gan_bit_array_get_bit ( &(img)->ba[row],     col ) && \
         gan_bit_array_get_bit ( &(img)->ba[(row)+1], col ))
#else
GANDALF_API Gan_Bool gan_image_bit_get_pix_4group ( const Gan_Image *image,
                                        unsigned row, unsigned col );
GANDALF_API Gan_Bool gan_image_bit_get_pix_5group ( const Gan_Image *image,
                                        unsigned row, unsigned col );
GANDALF_API Gan_Bool gan_image_bit_get_pix_9group ( const Gan_Image *image,
                                        unsigned row, unsigned col );
GANDALF_API Gan_Bool gan_image_bit_get_pix_3group_horiz ( const Gan_Image *image,
                                              unsigned row, unsigned col );
GANDALF_API Gan_Bool gan_image_bit_get_pix_3group_vert ( const Gan_Image *image,
                                             unsigned row, unsigned col );
#endif /* #ifdef NDEBUG */

GANDALF_API int gan_image_get_pixel_count_b ( const Gan_Image *image, Gan_Bool val,
                                  const Gan_ImageWindow *psubwin );
GANDALF_API Gan_Image *gan_image_bit_invert_q ( Gan_Image *image,
                                    Gan_Image *result_image );
GANDALF_API Gan_Image *gan_image_bit_and_q ( Gan_Image *image1, Gan_Image *image2,
                                 Gan_Image *result_image );
GANDALF_API Gan_Image *gan_image_bit_nand_q ( Gan_Image *image1, Gan_Image *image2,
                                  Gan_Image *result_image );
GANDALF_API Gan_Image *gan_image_bit_or_q ( Gan_Image *image1, Gan_Image *image2,
                                Gan_Image *result_image );
GANDALF_API Gan_Image *gan_image_bit_eor_q ( Gan_Image *image1, Gan_Image *image2,
                                 Gan_Image *result_image );
GANDALF_API Gan_Image *gan_image_bit_andnot_q ( Gan_Image *image1, Gan_Image *image2,
                                    Gan_Image *result_image );
GANDALF_API Gan_Bool gan_image_bit_fill_row ( Gan_Image *image, unsigned y,
                                  unsigned x, unsigned width, Gan_Bool pix );
GANDALF_API Gan_Bool gan_image_bit_invert_row ( Gan_Image *image, unsigned y,
                                    unsigned x, unsigned width );
GANDALF_API Gan_Bool gan_image_bit_dilate_horiz ( Gan_Image *image, int no_pixels,
                                      Gan_Image *restrict_mask );
GANDALF_API Gan_Bool gan_image_bit_dilate_vert ( Gan_Image *image, int no_pixels,
                                     Gan_Image *restrict_mask );
GANDALF_API Gan_Bool gan_image_bit_shift ( const Gan_Image *image, int vshift, int hshift,
                               Gan_Image *result_image );

/**
 * \brief Macro: Invert binary image.
 * \return The result as a new image.
 *
 * Invert all the bits in the given \a image, creating a new image to hold
 * the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_invert_s ( Gan_Image *image );
#else
#define gan_image_bit_invert_s(i) gan_image_bit_invert_q(i,NULL)
#endif

/**
 * \brief Macro: Invert binary image.
 * \return The result \a image.
 *
 * Invert all the bits in the given \a image, overwriting the result on the
 * input \a image.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_invert_i ( Gan_Image *image );
#else
#define gan_image_bit_invert_i(i) gan_image_bit_invert_q(i,i)
#endif

/**
 * \brief Binary \c AND of all pixels in a binary image.
 * \return The result as a new image.
 *
 * Apply \c AND operation to two input binary images \a image1 and \a image2,
 * creating a new image to hold the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_and_s ( Gan_Image *image1, Gan_Image *image2 );
#else
#define gan_image_bit_and_s(i1,i2) gan_image_bit_and_q(i1,i2,NULL)
#endif

/**
 * \brief Binary \c NAND of all pixels in a binary image.
 * \return The result as a new image.
 *
 * Apply \c NAND operation (not \c AND) to two input binary images \a image1
 * and \a image2, creating a new image to hold the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_nand_s ( Gan_Image *image1, Gan_Image *image2 );
#else
#define gan_image_bit_nand_s(i1,i2) gan_image_bit_nand_q(i1,i2,NULL)
#endif

/**
 * \brief Binary \c OR of all pixels in a binary image.
 * \return The result as a new image.
 *
 * Apply \c OR operation to two input binary images \a image1 and \a image2,
 * creating a new image to hold the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_or_s ( Gan_Image *image1, Gan_Image *image2 );
#else
#define gan_image_bit_or_s(i1,i2) gan_image_bit_or_q(i1,i2,NULL)
#endif

/**
 * \brief Binary \c EOR of all pixels in a binary image.
 * \return The result as a new image.
 *
 * Apply \c EOR operation (exclusive \c OR) to two input binary images
 * \a image1 and \a image2, creating a new image to hold the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_eor_s ( Gan_Image *image1, Gan_Image *image2 );
#else
#define gan_image_bit_eor_s(i1,i2) gan_image_bit_eor_q(i1,i2,NULL)
#endif

/**
 * \brief Binary \c AND-NOT of all pixels in a binary image.
 * \return The result as a new image.
 *
 * Apply \c AND-NOT operation to two input binary images \a image1
 * and \a image2, creating a new image to hold the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_andnot_s ( Gan_Image *image1, Gan_Image *image2 );
#else
#define gan_image_bit_andnot_s(i1,i2) gan_image_bit_andnot_q(i1,i2,NULL)
#endif

/**
 * \brief Binary \c AND of all pixels in a binary image.
 * \return Result binary image \a result.
 *
 * Apply \c AND operation to two input binary images \a image1 and \a image2,
 * overwriting the \a result image with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_and_i ( Gan_Image *result, Gan_Image *image );
#else
#define gan_image_bit_and_i(r,i) gan_image_bit_and_q(r,i,r)
#endif

/**
 * \brief Binary \c NAND of all pixels in a binary image.
 * \return Result binary image \a result.
 *
 * Apply \c NAND operation (not \c AND) to two input binary images \a image1
 * and \a image2, overwriting the \a result image with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_nand_i ( Gan_Image *result, Gan_Image *image );
#else
#define gan_image_bit_nand_i(r,i) gan_image_bit_nand_q(r,i,r)
#endif

/**
 * \brief Binary \c OR of all pixels in a binary image.
 * \return Result binary image \a result.
 *
 * Apply \c OR operation to two input binary images \a image1 and \a image2,
 * overwriting the \a result image with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_or_i ( Gan_Image *result, Gan_Image *image );
#else
#define gan_image_bit_or_i(r,i) gan_image_bit_or_q(r,i,r)
#endif

/**
 * \brief Binary \c EOR of all pixels in a binary image.
 * \return Result binary image \a result.
 *
 * Apply \c EOR operation (exclusive \c OR) to two input binary images
 * \a image1 and \a image2, overwriting the \a result image with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_eor_i ( Gan_Image *result, Gan_Image *image );
#else
#define gan_image_bit_eor_i(r,i) gan_image_bit_eor_q(r,i,r)
#endif

/**
 * \brief Binary \c AND-NOT of all pixels in a binary image.
 * \return Result binary image \a result.
 *
 * Apply \c AND-NOT operation to two input binary images \a image1
 * and \a image2, overwriting the \a result image with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_bit_andnot_i ( Gan_Image *result, Gan_Image *image );
#else
#define gan_image_bit_andnot_i(r,i) gan_image_bit_andnot_q(r,i,r)
#endif

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_BIT_H */
