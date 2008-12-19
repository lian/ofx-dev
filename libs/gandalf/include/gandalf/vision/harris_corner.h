/**
 * File:          $RCSfile: harris_corner.h,v $
 * Module:        Plessey corner detector algorithm
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.14 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2000 Imagineer Software Limited
 * History:       Based on Chris Harris's algorithm at Roke Manor Research
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

#ifndef _GAN_HARRIS_CORNER_H
#define _GAN_HARRIS_CORNER_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/vision/mask1D.h>
#include <gandalf/vision/camera.h>
#include <gandalf/vision/corner_feature.h>
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

GANDALF_API Gan_CornerFeatureMap *
 gan_harris_corner_q ( Gan_Image *image, Gan_Image *mask,
                       Gan_Mask1D *image_filter_y, Gan_Mask1D *image_filter_x,
                       Gan_Mask1D *grad_filter_y,  Gan_Mask1D *grad_filter_x,
                       float kappa, float thres,
                       Gan_Matrix23_f *A, int status, Gan_Camera *camera,
                       Gan_LocalFeatureMapParams *lpms,
                       Gan_CornerFeatureMap *corner_map );

/**
 * \brief Macro: Computes corners in an image using the Harris algorithm.
 * \param image The input image
 * \param mask Binary image indicating region to find corners or \c NULL
 * \param image_filter_y The image convolution mask in the y-direction
 * \param image_filter_x The image convolution mask in the x-direction
 * \param grad_filter_y The gradient convolution mask in the y-direction
 * \param grad_filter_x The gradient convolution mask in the x-direction
 * \param kappa The weighting factor used to compute the corner strength
 * \param thres The threshold on corner strength
 * \param A Affine transformation to apply to corner coordinates or \c NULL
 * \param status The initial status value set for each corner
 * \param camera Pointer to the camera calibration or \c NULL
 * \param lpms Pointer to local feature map parameters or \c NULL
 *
 * Applies the Harris corner detector to find corners in the
 * input image. Macro call to gan_harris_corner_q().
 *
 * \return Non-\c NULL a pointer to the computed corner map structure, or
 *         \c NULL on failure.
 * \sa gan_harris_corner_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_CornerFeatureMap *gan_harris_corner_s ( Gan_Image *image,
                                            Gan_Image *mask,
                                            Gan_Mask1D *image_filter_y,
                                            Gan_Mask1D *image_filter_x,
                                            Gan_Mask1D *grad_filter_y,
                                            Gan_Mask1D *grad_filter_x,
                                            float kappa, float thres,
                                            Gan_Matrix23_f *A, int status,
                                            Gan_Camera *camera,
                                            Gan_LocalFeatureMapParams *lpms );
#else
#define gan_harris_corner_s(image,mask,image_filter_y,image_filter_x,grad_filter_y,grad_filter_x,kappa,thres,A,status,camera,lpms)\
  gan_harris_corner_q(image,mask,image_filter_y,image_filter_x,grad_filter_y,grad_filter_x,kappa,thres,A,status,camera,lpms,NULL)
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

#endif /* #ifndef _GAN_HARRIS_CORNER_H */
