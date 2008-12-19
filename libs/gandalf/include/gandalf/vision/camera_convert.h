/**
 * File:          $RCSfile: camera_convert.h,v $
 * Module:        Camera conversion functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.5 $
 * Last edited:   $Date: 2005/10/03 14:41:27 $
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

#ifndef _GAN_CAMERA_CONVERT_H
#define _GAN_CAMERA_CONVERT_H

#include <stdio.h>
#include <gandalf/vision/camera.h>
#include <gandalf/vision/cameraf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup Camera
 * \{
 */

GANDALF_API Gan_Bool gan_cameraf_from_camera_q ( const Gan_Camera *camera,
                                                 Gan_Camera_f     *cameraf,
                                                 Gan_CubicBSplineWeightsF **ppweight,
                                                 Gan_CubicBSplineSupportF **ppsupport );
GANDALF_API Gan_Bool gan_camera_from_cameraf_q ( const Gan_Camera_f *cameraf,
                                                 Gan_Camera         *camera,
                                                 Gan_CubicBSplineWeights **ppweight,
                                                 Gan_CubicBSplineSupport **ppsupport );
GANDALF_API Gan_Camera_f gan_cameraf_from_camera_s ( const Gan_Camera   *camera,
                                                     Gan_CubicBSplineWeightsF **ppweight,
                                                     Gan_CubicBSplineSupportF **ppsupport );
GANDALF_API Gan_Camera   gan_camera_from_cameraf_s ( const Gan_Camera_f *cameraf,
                                                     Gan_CubicBSplineWeights **ppweight,
                                                     Gan_CubicBSplineSupport **ppsupport );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_CAMERA_CONVERT_H */
