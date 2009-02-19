/**
 * File:          $RCSfile: image_scale.h,v $
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

#ifndef _GAN_IMAGE_SCALE_H
#define _GAN_IMAGE_SCALE_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageScale
 * \{
 */

GANDALF_API Gan_Image *gan_image_scale_q ( Gan_Image *source, Gan_Image *mask,
                               Gan_Pixel *scale, Gan_Image *dest );

/**
 * \brief Macro: Scales the pixels in an image.
 * \param source The input image
 * \param mask A binary mask or \c NULL
 * \param scale Pixel defining the scale factor
 * \return Pointer to the scaled image, or \c NULL on failure.
 *
 * Scales all the pixels in an image. This is a macro call
 * to gan_image_scale_q(). If \a mask is not \c NULL then only pixels
 * in the mask are scaled.
 *
 * The \a scale pixel must be of \c GAN_FLOAT type.
 *
 * \sa gan_image_scale_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_scale_s ( Gan_Image *source, Gan_Image *mask,
                               Gan_Pixel *scale );
#else
#define gan_image_scale_s(source,mask,scale)\
        gan_image_scale_q(source,mask,scale,NULL)
#endif

/**
 * \brief Macro: Scales the pixels in an image.
 * \param image The input/output image
 * \param mask A binary mask or \c NULL
 * \param scale Pixel defining the scale factor
 * \return Pointer to the scaled \a image, or \c NULL on failure.
 *
 * Scales all the pixels in an image in-place. This is a macro call
 * to gan_image_scale_q(). If \a mask is not \c NULL then only pixels
 * in the mask are scaled.
 *
 * The \a scale pixel must be of \c GAN_FLOAT type.
 *
 * \sa gan_image_scale_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_scale_i ( Gan_Image *image, Gan_Image *mask,
                               Pixel *scale );
#else
#define gan_image_scale_i(image,mask,scale) \
        gan_image_scale_q(image,mask,scale,image)
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

#endif /* #ifndef _GAN_IMAGE_SCALE_H */
