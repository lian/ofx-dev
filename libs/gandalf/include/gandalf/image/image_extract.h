/**
 * File:          $RCSfile: image_extract.h,v $
 * Module:        Extract/convert part of an image
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.20 $
 * Last edited:   $Date: 2006/03/14 18:08:17 $
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

#ifndef _GAN_IMAGE_EXTRACT_H
#define _GAN_IMAGE_EXTRACT_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageExtract
 * \{
 */

GANDALF_API Gan_Image *gan_image_extract_q ( const Gan_Image *source,
                                 int      r0,     int      c0,
                                 unsigned height, unsigned width,
                                 Gan_ImageFormat format, Gan_Type type,
                                 Gan_Bool copy_pixels,
                                 Gan_Image *dest );

/**
 * \brief Macro: Extracts part of an image.
 * \param source The input image
 * \param r0 Vertical offset of start of region
 * \param c0 Horizontal offset of start of region
 * \param height Height of region in pixels
 * \param width Width of region in pixels
 * \param format The format of the output image
 * \param type The type of the output image
 * \param copy_pixels Whether to copy the pixels from the source image
 * \return Pointer to the extracted/converted image, or \c NULL on failure.
 *
 * Extracts a sub-part of an image, converting the image to a different format
 * and type if desired. This is a macro call to gan_image_extract_q().
 *
 * \sa gan_image_extract_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_extract_s ( const Gan_Image *source,
                                 int      r0,     int      c0,
                                 unsigned height, unsigned width,
                                 Gan_ImageFormat format, Gan_Type type,
                                 Gan_Bool copy_pixels );
#else
#define gan_image_extract_s(source,r0,c0,height,width,format,type,copy_pixels)\
    gan_image_extract_q(source,r0,c0,height,width,format,type,copy_pixels,NULL)
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

#endif /* #ifndef _GAN_IMAGE_EXTRACT_H */
