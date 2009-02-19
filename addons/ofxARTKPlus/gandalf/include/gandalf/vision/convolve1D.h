/**
 * File:          $RCSfile: convolve1D.h,v $
 * Module:        Image 1D convolution routines
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.22 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
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

#ifndef _GAN_CONVOLVE1D_H
#define _GAN_CONVOLVE1D_H

#include <gandalf/vision/mask1D.h>
#include <gandalf/image/image_defs.h>
#include <gandalf/image/image_channel.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup Convolution
 * \{
 */

GANDALF_API Gan_Bool gan_convolve1D_f ( float *source, int sstride,
                            Gan_EdgeBehaviour eEdgeBehaviour,
                            Gan_Bool zero_outside,
                            float *dest,   int dstride,
                            Gan_Mask1D *mask, int dsize );
GANDALF_API Gan_Bool gan_convolve1D_d ( double *source, int sstride,
                            Gan_EdgeBehaviour eEdgeBehaviour,
                            Gan_Bool zero_outside,
                            double *dest,   int dstride,
                            Gan_Mask1D *mask, int dsize );
GANDALF_API Gan_Bool gan_convolve1D_i ( int *source, int sstride,
                            Gan_EdgeBehaviour eEdgeBehaviour,
                            Gan_Bool zero_outside,
                            int *dest,   int dstride,
                            Gan_Mask1D *mask, int dsize );
GANDALF_API Gan_Bool gan_convolve1D_uc ( unsigned char *source, int sstride,
                             Gan_EdgeBehaviour behaviour,
                             Gan_Bool zero_outside,
                             unsigned char *dest,   int dstride,
                             Gan_Mask1D *mask, int dsize );
GANDALF_API Gan_Bool gan_convolve1D_us ( unsigned short *source, int sstride,
                             Gan_EdgeBehaviour behaviour,
                             Gan_Bool zero_outside,
                             unsigned short *dest,   int dstride,
                             Gan_Mask1D *mask, int dsize );
GANDALF_API Gan_Bool gan_convolve1D_ui ( unsigned int *source, int sstride,
                             Gan_EdgeBehaviour behaviour,
                             Gan_Bool zero_outside,
                             unsigned int *dest,   int dstride,
                             Gan_Mask1D *mask, int dsize );

GANDALF_API Gan_Image *gan_image_convolve1Dx_q ( const Gan_Image *image,
                                     Gan_ImageChannelType channel,
                                     Gan_EdgeBehaviour eEdgeBehaviour,
                                     Gan_Mask1D *mask, Gan_Image *dest );
GANDALF_API Gan_Image *gan_image_convolve1Dy_q ( const Gan_Image *image,
                                     Gan_ImageChannelType channel,
                                     Gan_EdgeBehaviour eEdgeBehaviour,
                                     Gan_Mask1D *mask, Gan_Image *dest );

/**
 * \brief Macro: Convolves an image in the x-direction.
 * \param image The input image
 * \param channel Colour channel to be convolved where applicable
 * \param eEdgeBehaviour Behaviour of data beyond edge
 * \param mask The image convolution mask
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Applies a one-dimensional convolution operation to the given image in the
 * x-direction. When the image contains colour or vector field data, a
 * particular colour channel/vector field element can be specified by the
 * channel argument, which  should otherwise be passed as #GAN_ALL_CHANNELS.
 *
 * Macro call to gan_image_convolve1Dx_q().
 *
 * \sa gan_image_convolve1Dx_q, gan_gauss_mask_new().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convolve1Dx_s ( const Gan_Image *image,
                                     Gan_ImageChannelType channel,
                                     Gan_EdgeBehaviour eEdgeBehaviour,
                                     Gan_Mask1D *mask );
#else
#define gan_image_convolve1Dx_s(image,channel,behaviour,mask)\
   gan_image_convolve1Dx_q(image,channel,behaviour,mask,NULL)
#endif

/**
 * \brief Macro: Convolves an image in the y-direction.
 * \param image The input image
 * \param channel Colour channel to be convolved where applicable
 * \param eEdgeBehaviour Behaviour of data beyond edge
 * \param mask The image convolution mask
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Applies a one-dimensional convolution operation to the given image in the
 * y-direction. When the image contains colour or vector field data, a
 * particular colour channel/vector field element can be specified by the
 * channel argument, which should otherwise be passed as #GAN_ALL_CHANNELS.
 *
 * Macro call to gan_image_convolve1Dy_q().
 *
 * \sa gan_image_convolve1Dy_q, gan_gauss_mask_new().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_convolve1Dy_s ( const Gan_Image *image,
                                     Gan_ImageChannelType channel,
                                     Gan_EdgeBehaviour eEdgeBehaviour,
                                     Gan_Mask1D *mask );
#else
#define gan_image_convolve1Dy_s(image,channel,behaviour,mask)\
   gan_image_convolve1Dy_q(image,channel,behaviour,mask,NULL)
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

#endif /* #ifndef _GAN_CONVOLVE1D_H */
