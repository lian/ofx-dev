/**
 * File:          $RCSfile: bright_disp.h,v $
 * Module:        Edge feature display using Open GL
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.1 $
 * Last edited:   $Date: 2006/04/21 11:29:53 $
 * Author:        $Author: nicolas $
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

#ifndef _GAN_BRIGHT_DISP_H
#define _GAN_BRIGHT_DISP_H

#include "bright_feature.h"
#include <gandalf/image/pixel.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup FeatureDetection
 * \{
 */

#ifdef HAVE_OPENGL

GANDALF_API Gan_Bool gan_bright_feature_display ( Gan_brightFeature *bright,
                                                  float size, Gan_Matrix23_f *A,
                                                  Gan_RGBPixel_f *bright_colour );
GANDALF_API Gan_Bool gan_bright_feature_map_display ( Gan_brightFeatureMap *bmap,
                                                      float size, Gan_Matrix23_f *A,
                                                      Gan_RGBPixel_f *bright_colour,
                                                      Gan_RGBPixel_f *string_colour,
                                                      Gan_RGBPixel_f *first_colour,
                                                      Gan_RGBPixel_f *last_colour,
                                                      Gan_RGBPixel_f *bbox_colour);

#endif /* #ifdef HAVE_OPENGL */

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_BRIGHT_DISP_H */
