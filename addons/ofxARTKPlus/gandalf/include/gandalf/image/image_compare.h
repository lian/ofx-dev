/**
 * File:          $RCSfile: image_compare.h,v $
 * Module:        Extract/fill selected channel(s) of image
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.5 $
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

#ifndef _GAN_IMAGE_COMPARE_H
#define _GAN_IMAGE_COMPARE_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageCompare
 * \{
 */

/**
 * \brief Result of image comparison.
 */
typedef enum
{
   GAN_IMAGES_IDENTICAL,        /**< the images are the same */
   GAN_IMAGE_FORMATS_DIFFERENT, /**< the formats of the images are
                                     different */
   GAN_IMAGE_SIZES_DIFFERENT,   /**< the widths and/or heights of the images
                                     are different */
   GAN_IMAGE_PIXELS_DIFFERENT,  /**< one or more pixels are different */
   GAN_IMAGES_SIMILAR,          /**< ratio of different pixels <=
                                     similarity_thres */
   GAN_IMAGES_NOT_SIMILAR,      /**< ratio of different pixels >
                                     similarity_thres */
} Gan_PixelComparison;

GANDALF_API Gan_Bool gan_image_compare ( Gan_Image *image1, Gan_Image *image2,
                             double pixel_thres, double proportion_thres,
                             Gan_PixelComparison *result );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_COMPARE_H */
