/**
 * File:          $RCSfile: canny_edge.h,v $
 * Module:        Canny edge detection algorithm
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.17 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * History:       Modified from original TINA implementation
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

#ifndef _GAN_CANNY_EDGE_H
#define _GAN_CANNY_EDGE_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/vision/mask1D.h>
#include <gandalf/vision/camera.h>
#include <gandalf/vision/edge_feature.h>
#include <gandalf/image/image_defs.h>
#include <gandalf/linalg/2x3matrix.h>

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

GANDALF_API Gan_EdgeFeatureMap *
 gan_canny_edge_q ( Gan_Image *image, Gan_Image *mask,
                    Gan_Mask1D *filter_y, Gan_Mask1D *filter_x,
                    Gan_RGBPixel_f *colour,
                    Gan_Vector2_f *direction,
                    double lower_thres, double upper_thres,
                    unsigned string_length_thres,
                    Gan_Matrix23_f *A, Gan_Camera *camera,
                    Gan_LocalFeatureMapParams *lpms,
                    Gan_EdgeFeatureMap *edge_map,
                    void (*set_progress) ( void *, unsigned ),
                    void *progress_obj );

/**
 * \brief Macro: Computes edges in an image using the Canny algorithm.
 * \param image The input image
 * \param mask Binary image indicating region to find edges or \c NULL
 * \param filter_y Image convolution filter in the y-direction or \c NULL
 * \param filter_x Image convolution filter in the x-direction or \c NULL
 * \param colour Colour on which to project gradients or \c NULL
 * \param direction Direction on which to project gradients or \c NULL
 * \param lower_thres Lower hysteresis threshold for string building
 * \param upper_thres Upper hysteresis threshold for string building
 * \param string_length_thres The smallest length of string allowed
 * \param A Affine transformation to apply to edgel coordinates or \c NULL
 * \param camera Pointer to the camera calibration or \c NULL
 * \param lpms Pointer to local feature map parameters or \c NULL
 * \param set_progress Function to update progress from 0 to 99  or \c NULL
 * \param progress_obj Pointer passed into \a set_progress function or \c NULL
 *
 * Applies the Canny edge detector to find edges in the input image.
 * Macro call to gan_canny_edge_q().
 *
 * \return Non-\c NULL a pointer to the computed edge map structure, or
 *         \c NULL on failure.
 * \sa gan_canny_edge_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_EdgeFeatureMap *gan_canny_edge_s ( Gan_Image *image,
                                       Gan_Image *mask,
                                       Gan_Mask1D *filter_y,
                                       Gan_Mask1D *filter_x,
                                       Gan_RGBPixel_f *colour,
                                       Gan_Vector2_f *direction,
                                       double lower_thres, double upper_thres,
                                       unsigned string_length_thres,
                                       Gan_Matrix23_f *A, Gan_Camera *camera,
                                       Gan_LocalFeatureMapParams *lpms,
                                       void (*set_progress) ( void *,
                                                              unsigned ),
                                       void *progress_obj );
#else
#define gan_canny_edge_s(image,mask,filter_y,filter_x,colour,direction,lower_thres,upper_thres,string_length_thres,A,camera,lpms,setprog,progobj)\
  gan_canny_edge_q(image,mask,filter_y,filter_x,colour,direction,lower_thres,upper_thres,string_length_thres,A,camera,lpms,NULL,setprog,progobj)
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

#endif /* #ifndef _GAN_CANNY_EDGE_H */
