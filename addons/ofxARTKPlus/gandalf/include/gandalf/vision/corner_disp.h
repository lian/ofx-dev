/**
 * File:          $RCSfile: corner_disp.h,v $
 * Module:        Corner feature display using Open GL
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.11 $
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

#ifndef _GAN_CORNER_DISP_H
#define _GAN_CORNER_DISP_H

#include <gandalf/vision/corner_feature.h>
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

GANDALF_API Gan_Bool gan_corner_feature_display ( Gan_CornerFeature *corner,
                                      float size, Gan_Matrix23_f *A,
                                      Gan_RGBPixel_f *corner_colour );
GANDALF_API Gan_Bool gan_corner_feature_map_display ( Gan_CornerFeatureMap *cmap,
                                          float size, Gan_Matrix23_f *A,
                                          Gan_RGBPixel_f *corner_colour,
                                          Gan_RGBPixel_f *bbox_colour );

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

#endif /* #ifndef _GAN_CORNER_DISP_H */
