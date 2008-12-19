/**
 * File:          $RCSfile: camera_defs.h,v $
 * Module:        Camera definitions and building functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.15 $
 * Last edited:   $Date: 2005/07/26 00:41:07 $
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

#ifndef _GAN_CAMERA_DEFS_H
#define _GAN_CAMERA_DEFS_H

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

/**
 * \brief Camera models supported by Gandalf.
 */
typedef enum
{
   /// linear camera model
   GAN_LINEAR_CAMERA,

   /// one parameter K1 of radial distortion
   GAN_RADIAL_DISTORTION_1,

   /// two parameters K1,K2 of radial distortion
   GAN_RADIAL_DISTORTION_2,

   /// three parameters K1,K2,K3 of radial distortion
   GAN_RADIAL_DISTORTION_3,

   /// one parameter K1 of inverse radial distortion
   GAN_RADIAL_DISTORTION_1_INV,

   /// stereographic projection
   GAN_STEREOGRAPHIC_CAMERA,

   /// equidistant projection
   GAN_EQUIDISTANT_CAMERA,

   /// sine-law projection
   GAN_SINE_LAW_CAMERA,

   /// equi-solid angle projection
   GAN_EQUI_SOLID_ANGLE_CAMERA,

   /// distortion model as used by 3D Equalizer V4
   GAN_XY_DISTORTION_4,

   /// warp model with fixed corners
   GAN_FIXED_CORNER_WARP,

   /// inverse warp model with fixed corners
   GAN_FIXED_CORNER_WARP_INV,

   /// camera defined by projective warp and cubic B-spline warp
   GAN_CUBIC_BSPLINE_CAMERA,

   /// camera defined by projective warp and inverse cubic B-spline warp
   GAN_CUBIC_BSPLINE_CAMERA_INV,

   /// affine camera model
   GAN_AFFINE_CAMERA,

   GAN_CAMERA_TYPE_ENUM_COUNT
} Gan_CameraType;

/// Highest supported level of subdivision of cubic B-spline mesh
#define GAN_CUBIC_BSPLINE_CAMERA_LEVEL 4

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_CAMERA_DEFS_H */
