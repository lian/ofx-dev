/**
 * File:          $RCSfile: convolve2D.h,v $
 * Module:        Image 2D convolution routines
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.1 $
 * Last edited:   $Date: 2004/03/25 09:22:34 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2004 <a href="http://frav.escet.urjc.es">FRAV (Face Recognition & Artificial Vision Group)</a>
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

#ifndef _GAN_CONVOLVE2D_H
#define _GAN_CONVOLVE2D_H

#include <gandalf/vision/mask2D.h>
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

Gan_Bool gan_convolve2D_f ( float *source, 
                            int sstride,
                            float *dest,   
                            int dstride,
                            Gan_Mask2D *mask, 
                            unsigned long width );
Gan_Bool gan_convolve2D_d ( double *source, 
                            int sstride,
                            double *dest,
                            int dstride,  
                            Gan_Mask2D *mask, 
                            unsigned long width);
Gan_Bool gan_convolve2D_i ( int *source, 
                            int sstride,
                            int *dest,  
                            int dstride,
                            Gan_Mask2D *mask, 
                            unsigned long width);
Gan_Bool  gan_convolve2D_uc ( unsigned char *source, 
                              int sstride,
                              unsigned char *dest, 
                              int dstride,
                              Gan_Mask2D *mask,
                              unsigned long width );
Gan_Bool gan_convolve2D_us ( unsigned short *source, 
                             int sstride,
                             unsigned short *dest,   
                             int dstride,
                             Gan_Mask2D *mask, 
                             unsigned long width);
Gan_Bool  gan_convolve2D_ui ( unsigned int *source,
                              int sstride,
                              unsigned int *dest,  
                              int dstride,
                              Gan_Mask2D *mask,
                              unsigned long width );


Gan_Image *gan_image_convolve2D_q ( Gan_Image *image,
                                    Gan_ImageChannelType channel,
                                    Gan_Mask2D *mask, Gan_Image *dest );

/**
 * \brief Macro: Convolves an image in both directions.
 * \param image The input image
 * \param channel Colour channel to be convolved where applicable
 * \param mask The image convolution mask
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Applies a two-dimensional convolution operation to the given image.
 * When the image contains colour or vector field data, a
 * particular colour channel/vector field element can be specified by the
 * channel argument, which  should otherwise be passed as #GAN_ALL_CHANNELS.
 *
 * Macro call to gan_image_convolve2D_q().
 *
 * \sa gan_image_convolve2Dx_q, gan_gauss_mask_new().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
Gan_Image *gan_image_convolve2D_s ( Gan_Image *image,
                                    Gan_ImageChannelType channel,
                                    Gan_Mask2D *mask );
#else
#define gan_image_convolve2D_s(image,channel,mask)\
   gan_image_convolve2D_q(image,channel,mask,NULL)
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

#endif /* #ifndef _GAN_CONVOLVE2D_H */
