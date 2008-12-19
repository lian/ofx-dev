/**
 * File:          $RCSfile: image_convert.h,v $
 * Module:        Convert (part of) an image
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.3 $
 * Last edited:   $Date: 2005/12/09 13:18:58 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2000 Imagineer Systems Limited
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

#ifndef _GAN_IMAGE_CONVERT_H
#define _GAN_IMAGE_CONVERT_H

#include <gandalf/image/image_defs.h>
#include <gandalf/image/image_extract.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageConvert
 * \{
 */

/**
 * \brief Macro: Converts an image from one format/type to another.
 * \param source The input image
 * \param format The format of the output image
 * \param type The type of the output image
 * \param dest Destination image
 * \return Pointer to the converted image, or \c NULL on failure.
 *
 * Applies the relevant pixel-by-pixel conversion to convert an image from one
 * format/type to another. This is a macro call to gan_image_extract_q().
 *
 * \sa gan_image_convert_s().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convert_q ( const Gan_Image *source,
                                             Gan_ImageFormat format, Gan_Type type,
                                             Gan_Image *dest );
#else
#define gan_image_convert_q(source,format,type,dest)\
           gan_image_extract_q(source,0,0,(source)->height,(source)->width,format,type,GAN_TRUE,dest)
#endif

/**
 * \brief Macro: Converts an image from one format/type to another.
 * \param source The input image
 * \param format The format of the output image
 * \param type The type of the output image
 * \return Pointer to the converted image, or \c NULL on failure.
 *
 * Applies the relevant pixel-by-pixel conversion to convert an image from one
 * format/type to another. This is a macro call to gan_image_convert_q().
 *
 * \sa gan_image_convert_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convert_s ( const Gan_Image *source,
                                             Gan_ImageFormat format, Gan_Type type );
#else
#define gan_image_convert_s(source,format,type)\
           gan_image_convert_q(source,format,type,NULL)
#endif

/**
 * \brief Macro: Swaps R & B in an RGB image, returning a new image
 * \param source The input image
 * \return Pointer to the converted image, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_swap_RandB_s ( Gan_Image *source );
#else
#define gan_image_swap_RandB_s(source)\
           gan_image_swap_RandB_q(source,NULL)
#endif

/**
 * \brief Macro: Swaps R & B in an RGB image in-place
 * \param img The input/output image
 * \return Pointer to the converted image, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_swap_RandB_i ( Gan_Image *img );
#else
#define gan_image_swap_RandB_i(img)\
           gan_image_swap_RandB_q(img,img)
#endif

/**
 * \brief Macro: Converts an image RGBA to ARGB, returning a new image
 * \param source The input image
 * \return Pointer to the converted ARGB image, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convert_RGBAtoARGB_s ( Gan_Image *source );
#else
#define gan_image_convert_RGBAtoARGB_s(source)\
           gan_image_convert_RGBAtoARGB_q(source,NULL)
#endif

/**
 * \brief Macro: Converts an image RGBA to ARGB in-place
 * \param img The input/output image
 * \return Pointer to the converted ARGB image, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convert_RGBAtoARGB_i ( Gan_Image *img );
#else
#define gan_image_convert_RGBAtoARGB_i(img)\
           gan_image_convert_RGBAtoARGB_q(img,img)
#endif

/**
 * \brief Macro: Converts an image ARGB to RGBA, returning a new image
 * \param source The input image
 * \return Pointer to the converted RGBA image, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convert_ARGBtoRGBA_s ( Gan_Image *source );
#else
#define gan_image_convert_ARGBtoRGBA_s(source)\
           gan_image_convert_ARGBtoRGBA_q(source,NULL)
#endif

/**
 * \brief Macro: Converts an image ARGB to RGBA in-place
 * \param img The input/output image
 * \return Pointer to the converted RGBA image, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convert_ARGBtoRGBA_i ( Gan_Image *img );
#else
#define gan_image_convert_ARGBtoRGBA_i(img)\
           gan_image_convert_ARGBtoRGBA_q(img,img)
#endif

GANDALF_API Gan_Image *gan_image_swap_RandB_q(Gan_Image *source, Gan_Image *dest);
GANDALF_API Gan_Image *gan_image_convert_ARGBtoRGBA_q(Gan_Image *source, Gan_Image *dest);
GANDALF_API Gan_Image *gan_image_convert_RGBAtoARGB_q(Gan_Image *source, Gan_Image *dest);

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_CONVERT_H */
