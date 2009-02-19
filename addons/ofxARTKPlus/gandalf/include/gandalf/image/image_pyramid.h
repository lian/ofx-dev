/**
 * File:          $RCSfile: image_pyramid.h,v $
 * Module:        Construct multi-resolution image pyramid
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.16 $
 * Last edited:   $Date: 2005/10/20 14:24:52 $
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

#ifndef _GAN_IMAGE_GL_PYRAMID_H
#define _GAN_IMAGE_GL_PYRAMID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gandalf/image/image_defs.h>

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImagePyramid
 * \{
 */

/**
 * \brief Structure to hold image and mask at a single pyramid level.
 */
typedef struct Gan_ImagePyramid
{
   Gan_Image *img; /**< image represented at a single resolution level */
   Gan_Image *mask; /**< mask at this level defining which pixels are set */
   Gan_Bool img_alloc, mask_alloc; /**< whether the image/mask was allocated internally */
} Gan_ImagePyramid;

/**
 * \brief Type of averaging used when combining four pixels into one.
 */
typedef enum Gan_ImagePyramidAverage
{
   GAN_AVERAGE_ALL,    /**< take average of all four pixels */
   GAN_AVERAGE_IN_MASK /**< take average only of pixels in the mask */
} Gan_ImagePyramidAverage;

GANDALF_API Gan_Image *gan_image_halve_size ( Gan_Image *image, Gan_Image *himage);
GANDALF_API Gan_Bool gan_image_pyramid_build_preallocated ( Gan_Image *img, Gan_Image *mask,
                                                            unsigned no_levels,
                                                            Gan_ImagePyramidAverage average_type,
                                                            unsigned no_neighbours,
                                                            Gan_Image **imgarray,
                                                            Gan_Image **maskarray,
                                                            Gan_ImagePyramid **pyramid );
GANDALF_API void gan_image_pyramid_free ( Gan_ImagePyramid *pyramid, unsigned no_levels,
                                          Gan_Bool free_top_level );

/**
 * \brief Macro: Builds an image pyramid.
 * \param img The top-level image in the pyramid
 * \param mask The mask corresponding to the top-level image or NULL
 * \param no_levels The number of levels in the pyramid
 * \param average_type The type of averaging of four-pixel neighbourhoods
 * \param no_neighbours Minimum number of neighbours set to transfer resolution
 * \param pyramid Pointer to the pyramid
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Builds an image pyramid. If the \a mask is \c NULL, the pyramid is built
 * without masks, i.e. assuming that all the pixels are valid.
 *
 * \a no_neighbours is the least number of number of pixels in any four-pixel
 * neighbourhood of mask pixels needed to be one in order for the lower
 * resolution mask to be set to one.
 *
 * This is a macro call to \a gan_image_pyramid_build_preallocated().
 *
 * \sa gan_image_pyramid_free().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_pyramid_build ( Gan_Image *img, Gan_Image *mask,
                                               unsigned no_levels,
                                               Gan_ImagePyramidAverage average_type,
                                               unsigned no_neighbours,
                                               Gan_ImagePyramid **pyramid );
#else
#define gan_image_pyramid_build(img,mask,no_levels,average_type, no_neighbours,pyramid) \
    gan_image_pyramid_build_preallocated(img,mask,no_levels,average_type, no_neighbours,NULL,NULL,pyramid)
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

#endif /* #ifndef _GAN_IMAGE_GL_PYRAMID_H */
