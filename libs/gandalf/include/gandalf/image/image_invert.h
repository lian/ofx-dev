/**
 * File:          $RCSfile: image_invert.h,v $
 * Module:        Extract/fill selected channel(s) of image
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.3 $
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

#ifndef _GAN_IMAGE_INVERT_H
#define _GAN_IMAGE_INVERT_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageInvert
 * \{
 */

GANDALF_API Gan_Image *gan_image_invert_q ( Gan_Image *source, Gan_Image *dest );

/**
 * \brief Macro: Inverts an image.
 * \param source The input image
 * \return Pointer to the inverted image, or \c NULL on failure.
 *
 * Inverts an image. This is a macro call to gan_image_invert_q().
 *
 * \sa gan_image_invert_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_invert_s ( Gan_Image *source );
#else
#define gan_image_invert_s(source) gan_image_invert_q(source,NULL)
#endif

/**
 * \brief Macro: Inverts an image.
 * \param image The input/output image
 * \return Pointer to the inverted \a image, or \c NULL on failure.
 *
 * Inverts an image in-place. This is a macro call to gan_image_invert_q().
 *
 * \sa gan_image_invert_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_invert_i ( Gan_Image *image );
#else
#define gan_image_invert_i(image) gan_image_invert_q(image,image)
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

#endif /* #ifndef _GAN_IMAGE_INVERT_H */
