/**
 * File:          $RCSfile: image_channel.h,v $
 * Module:        Extract/fill selected channel(s) of image
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.21 $
 * Last edited:   $Date: 2006/01/11 15:33:52 $
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

#ifndef _GAN_IMAGE_CHANNEL_H
#define _GAN_IMAGE_CHANNEL_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageChannel
 * \{
 */

/**
 * \brief Image channel types for extracting individual channels.
 */
typedef enum
{
   /// for grey-level/alpha images
   GAN_INTENSITY_CHANNEL,

   ///for RGB and RGB/alpha images
   GAN_RED_CHANNEL, GAN_GREEN_CHANNEL, GAN_BLUE_CHANNEL,

   /// for grey-level/alpha and RGB/alpha images
   GAN_ALPHA_CHANNEL,

   /// for 2D and 3D vector field images
   GAN_X_CHANNEL,

   /// likewise
   GAN_Y_CHANNEL,

   /// for 3D vector field images
   GAN_Z_CHANNEL,

   /// all colour channels, e.g. R,G,B but not A
   GAN_ALL_COLOUR_CHANNELS,

   /// all channels
   GAN_ALL_CHANNELS
} Gan_ImageChannelType;

GANDALF_API Gan_Image *gan_image_extract_channel_q ( const Gan_Image *source,
                                                     Gan_ImageChannelType channel,
                                                     unsigned r0,     unsigned c0,
                                                     unsigned height, unsigned width,
                                                     Gan_Image *dest );
GANDALF_API Gan_Bool   gan_image_insert_channel ( const Gan_Image *source,
                                                  Gan_ImageChannelType schannel,
                                                  Gan_Image *dest,
                                                  Gan_ImageChannelType dchannel );
GANDALF_API Gan_Bool gan_image_fill_channel_const ( Gan_Image *image,
                                                    Gan_ImageChannelType channel,
                                                    Gan_Pixel *pixel );
GANDALF_API Gan_Bool gan_image_get_minimum_channel_value ( Gan_Image *image,
                                                           Gan_Image *mask,
                                                           Gan_ImageChannelType channel,
                                                           Gan_Pixel *minval );
GANDALF_API Gan_Bool gan_image_get_maximum_channel_value ( Gan_Image *image,
                                                           Gan_Image *mask,
                                                           Gan_ImageChannelType channel,
                                                           Gan_Pixel *maxval );
GANDALF_API Gan_Image* gan_image_threshold_channel_q ( const Gan_Image *source,
                                                       const Gan_Image *mask,
                                                       Gan_ImageChannelType channel,
                                                       float threshold,
                                                       Gan_Image *dest );

/**
 * \brief Macro: Extracts a specific channel from part of an image.
 * \param source The input image
 * \param channel The channel to extract from the image
 * \param r0 Vertical offset of start of region
 * \param c0 Horizontal offset of start of region
 * \param height Height of region in pixels
 * \param width Width of region in pixels
 * \return A pointer to the extracted image, or \c NULL on failure.
 *
 * Extracts a specific channel in a sub-part of an image, This is a macro call
 * to gan_image_extract_channel_q().
 *
 * \sa gan_image_extract_channel_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_extract_channel_s ( const Gan_Image *source,
                                         Gan_ImageChannelType channel,
                                         unsigned r0,     unsigned c0,
                                         unsigned height, unsigned width );
#else
#define gan_image_extract_channel_s(source,channel,r0,c0,height,width)\
           gan_image_extract_channel_q(source,channel,r0,c0,height,width,NULL)
#endif

/**
 * \brief Macro: Sets a single channel of an image to zero.
 * \param image The input image
 * \param channel The channel to set to zero
 * \return #GAN_TRUE on success, or #GAN_FALSE on failure.
 *
 * Sets a single channel of an image to zero. This is a macro call to
 * gan_image_fill_channel_const().
 *
 * \sa gan_image_fill_channel_const().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_fill_channel_zero ( Gan_Image *image,
                                                     Gan_ImageChannelType channel );
#else
#define gan_image_fill_channel_zero(image,channel)\
           gan_image_fill_channel_const(image,channel,NULL)
#endif

/**
 * \brief Macro: Thresholds a channel of an image
 * \param source The input image
 * \param mask Mask of pixels to test
 * \param channel The channel to extract from the image
 * \param threshold The threshold in the range [0..1]
 *
 * Thresholds a specific channel of an image and returns a mask of pixels above the threshold,
 * If a \a mask is specified, all pixels in \a dest outside the mask are set to zero.
 *
 * This is a macro call to gan_image_threshold_channel_q().
 *
 * \sa gan_image_threshold_channel_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image* gan_image_threshold_channel_s ( const Gan_Image *source,
                                                       const Gan_Image *mask,
                                                       Gan_ImageChannelType channel,
                                                       float threshold );
#else
#define gan_image_threshold_channel_s(source,mask,channel,threshold) \
           gan_image_threshold_channel_q(source,mask,channel,threshold,NULL)
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

#endif /* #ifndef _GAN_IMAGE_CHANNEL_H */
