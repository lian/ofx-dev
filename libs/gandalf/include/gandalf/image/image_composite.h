/**
 * File:          $RCSfile: image_composite.h,v $
 * Module:        Extract/fill selected channel(s) of image
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.8 $
 * Last edited:   $Date: 2006/03/22 18:41:33 $
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

#ifndef _GAN_IMAGE_COMPOSITE_H
#define _GAN_IMAGE_COMPOSITE_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageComposite
 * \{
 */

GANDALF_API Gan_Image *gan_image_composite_q ( Gan_Image *source,
                                               const Gan_Image *source_with_alpha,
                                               const Gan_Image *source_mask,
                                               Gan_Image *dest );
GANDALF_API Gan_Image *gan_image_blend_q ( Gan_Image *source1,
                                           const Gan_Image *source2,
                                           const Gan_Image *alpha,
                                           Gan_Bool invert_alpha,
                                           const Gan_Image *mask,
                                           Gan_Image *dest );
GANDALF_API Gan_Image *gan_image_blend_fixed_alpha_q ( Gan_Image *source1,
                                                       const Gan_Image *source2,
                                                       float alpha,
                                                       const Gan_Image *mask,
                                                       Gan_Image *dest );

/**
 * \brief Macro: Composite with overwriting
 * \param image The input/output image 
 * \param source_with_alpha The input image with the alpha channel
 * \param source_mask Binary mask for source image or \c NULL
 * \return Composited \a image, or \c NULL on failure.
 *
 * Composites the image \a source_with_alpha onto the given \a image,
 * overwriting the result onto \a image. If \a source_mask is not
 * \c NULL, only pixels in the mask are composited.
 *
 * \sa gan_image_composite_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_composite_i ( Gan_Image *image,
                                   const Gan_Image *source_with_alpha,
                                   const Gan_Image *source_mask);
#else
#define gan_image_composite_i(image,source_with_alpha,source_mask)\
           gan_image_composite_q(image,source_with_alpha,source_mask,image)
#endif

/**
 * \brief Macro: Composite into a new image
 * \param image The input image 
 * \param source_with_alpha The input image with the alpha channel
 * \param source_mask Binary mask for source image or \c NULL
 * \return Composited output image, or \c NULL on failure.
 *
 * Composites the image \a source_with_alpha onto the given \a image,
 * overwriting the result onto \a image. If \a source_mask is not
 * \c NULL, only pixels in the mask are composited.
 *
 * \sa gan_image_composite_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_composite_s ( Gan_Image *image,
                                   const Gan_Image *source_with_alpha,
                                   const Gan_Image *source_mask );
#else
#define gan_image_composite_s(image,source_with_alpha,source_mask)\
           gan_image_composite_q(image,source_with_alpha,source_mask,NULL)
#endif

/**
 * \brief Macro: Blend with overwriting
 * \param image The input/output image 
 * \param source2 The second input image
 * \param alpha Alpha image
 * \param invert_alpha Whether to invert the alpha image
 * \param mask Mask for blend
 * \return Composited \a image, or \c NULL on failure.
 *
 * Blends the image \a source2 with the given \a image,
 * overwriting the result onto \a image.
 *
 * \sa gan_image_blend_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_blend_i ( Gan_Image *image,
                                           const Gan_Image *source2,
                                           const Gan_Image *alpha,
                                           Gan_Bool invert_alpha,
                                           const Gan_Image *mask );
#else
#define gan_image_blend_i(image,source2,alpha,invert_alpha,mask)\
           gan_image_blend_q(image,source2,alpha,invert_alpha,mask,image)
#endif

/**
 * \brief Macro: Blend images into a new image
 * \param image The input image 
 * \param source2 The second input image
 * \param alpha Alpha image
 * \param invert_alpha Whether to invert the alpha image
 * \param mask Mask for blend
 * \return Composited output image, or \c NULL on failure.
 *
 * Blends the image \a source2 with the given \a image,
 * overwriting the result onto \a image.
 *
 * \sa gan_image_blend_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_blend_s ( Gan_Image *image,
                                           const Gan_Image *source2,
                                           const Gan_Image *alpha,
                                           Gan_Bool invert_alpha,
                                           const Gan_Image *mask );
#else
#define gan_image_blend_s(image,source2,alpha,invert_alpha,mask)\
           gan_image_blend_q(image,source2,alpha,invert_alpha,mask,NULL)
#endif

/**
 * \brief Macro: Blend with fixed alpha with overwriting
 * \param image The input/output image 
 * \param source2 The second input image
 * \param alpha Alpha value
 * \param mask Mask for blend
 * \return Composited \a image, or \c NULL on failure.
 *
 * Blends the image \a source2 with the given \a image,
 * overwriting the result onto \a image.
 *
 * \sa gan_image_blend_fixed_alpha_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_blend_fixed_alpha_i ( Gan_Image *image,
                                                       const Gan_Image *source2,
                                                       float alpha,
                                                       const Gan_Image *mask );
#else
#define gan_image_blend_fixed_alpha_i(image,source2,alpha,mask)\
           gan_image_blend_fixed_alpha_q(image,source2,alpha,mask,image)
#endif

/**
 * \brief Macro: Blend images with fixed alpha into a new image
 * \param image The input image 
 * \param source2 The second input image
 * \param alpha Alpha value
 * \param mask Mask for blend
 * \return Composited output image, or \c NULL on failure.
 *
 * Blends the image \a source2 with the given \a image,
 * overwriting the result onto \a image.
 *
 * \sa gan_image_blend_fixed_alpha_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_blend_fixed_alpha_s ( Gan_Image *image,
                                                       const Gan_Image *source2,
                                                       float alpha,
                                                       const Gan_Image *mask );
#else
#define gan_image_blend_fixed_alpha_s(image,source2,alpha,mask)\
           gan_image_blend_fixed_alpha_q(image,source2,alpha,mask,NULL)
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

#endif /* #ifndef _GAN_IMAGE_COMPOSITE_H */
