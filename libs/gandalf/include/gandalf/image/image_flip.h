/**
 * File:          $RCSfile: image_flip.h,v $
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

#ifndef _GAN_IMAGE_FLIP_H
#define _GAN_IMAGE_FLIP_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageFlip
 * \{
 */

GANDALF_API Gan_Image *gan_image_flip_q ( Gan_Image *source, Gan_Bool interlaced,
                              Gan_Image *dest );

/**
 * \brief Macro: Flips an image vertically.
 * \param source The input image
 * \param interlaced Whether the source image is interlaced or not
 * \return Pointer to the flipped image, or \c NULL on failure.
 *
 * Flips an image. If \a interlaced is #GAN_TRUE the upper and lower fields
 * are flipped separately.
 *
 * This is a macro call to gan_image_flip_q().
 *
 * \sa gan_image_flip_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_flip_s ( Gan_Image *source, Gan_Bool interlaced );
#else
#define gan_image_flip_s(source,ilaced) gan_image_flip_q(source,ilaced,NULL)
#endif

/**
 * \brief Macro: Flips an image.vertically
 * \param image The input/output image
 * \param interlaced Whether the source image is interlaced or not
 * \return Pointer to the flipped \a image, or \c NULL on failure.
 *
 * Flips an image in-place. If \a interlaced is #GAN_TRUE the upper and
 * lower fields are flipped separately.
 *
 * This is a macro call to gan_image_flip_q().
 *
 * \sa gan_image_flip_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_flip_i ( Gan_Image *image, Gan_Bool interlaced );
#else
#define gan_image_flip_i(image,ilaced) gan_image_flip_q(image,ilaced,image)
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

#endif /* #ifndef _GAN_IMAGE_FLIP_H */
