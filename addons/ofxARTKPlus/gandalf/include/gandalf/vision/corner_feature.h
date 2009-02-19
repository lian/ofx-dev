/**
 * File:          $RCSfile: corner_feature.h,v $
 * Module:        Image corner point definition and functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.18 $
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

#ifndef _GAN_CORNER_FEATURE_H
#define _GAN_CORNER_FEATURE_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/vision/camera.h>
#include <gandalf/vision/cameraf.h>
#include <gandalf/vision/local_feature.h>
#include <gandalf/image/pixel.h>
#include <gandalf/linalg/2x3matrixf.h>

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

/**
 * \brief 2D corner feature structure.
 */
typedef struct Gan_CornerFeature
{
   /// row/column coordinates in coordinate frame of 2D feature array
   unsigned short r, c;

   /// potentially sub-pixel coordinates of corner feature in
   /// coordinate frame defined by corner map
   Gan_Vector2_f p;

   /// coordinates of feature with any non-linear image distortion removed
   Gan_Vector2_f pu;

   /// corner feature strength/contrast value
   float strength;

   /// covariance for feature point position
   Gan_SquMatrix22_f N;

   /// inverse covariance for feature point position
   Gan_SquMatrix22_f Ni;

   /// status field for user program to define
   int status;

   /// index field for user program to define
   int index;
} Gan_CornerFeature;

/**
 * \brief 2D corner feature map structure.
 */
typedef struct Gan_CornerFeatureMap
{
   /// number of corner features stored
   unsigned ncorners;

   /// array of corner features
   Gan_CornerFeature *corner;

   /// allocated limit on number of corner features
   unsigned max_ncorners;

   /// dimensions of image region in which corner features have been computed
   unsigned height, width;

   /// whether the following A, Ai fields are set
   Gan_Bool A_set;

   /// transformation between region coordinates (0..width) and (0..height)
   /// and corner coordinates, and its inverse
   Gan_Matrix23_f A, Ai;

   /// calibration structure defining camera used for non-linear distortion
   /// correction
   Gan_Camera_f camera;

   /// local blocked feature index map
   Gan_LocalFeatureMap local_fmap;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_CornerFeatureMap;

GANDALF_API Gan_CornerFeatureMap *gan_corner_feature_map_form ( Gan_CornerFeatureMap *cmap,
                                                    unsigned max_ncorners );
GANDALF_API void gan_corner_feature_map_free ( Gan_CornerFeatureMap *cmap );
GANDALF_API Gan_Bool gan_corner_feature_map_clear ( Gan_CornerFeatureMap *cmap,
                                        unsigned height, unsigned width,
                                        Gan_Matrix23_f *A, Gan_Camera *camera,
                                        Gan_LocalFeatureMapParams *lpms );
GANDALF_API Gan_CornerFeature *gan_corner_feature_add ( Gan_CornerFeatureMap *cmap,
                                            unsigned r, unsigned c,
                                            float rf, float cf,
                                            Gan_SquMatrix22_f *N,
                                            int status, int index,
                                            float strength );
GANDALF_API Gan_Bool gan_corner_feature_map_postprocess ( Gan_CornerFeatureMap *cmap );

/**
 * \brief Macro: Allocates a corner feature map structure.
 * \param max_ncorners The number of corners initially to allocate for
 *
 * Allocates a structure to hold corner features, and sets
 * it to be empty. This macro calls gan_corner_feature_map_form().
 *
 * \return non-\c NULL the allocated feature map, \c NULL on failure.
 * \sa gan_corner_feature_map_form(), gan_corner_feature_map_free().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_CornerFeatureMap *gan_corner_feature_map_alloc ( unsigned max_ncorners );
#else
#define gan_corner_feature_map_alloc(max_ncorners)\
   gan_corner_feature_map_form(NULL,max_ncorners)
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

#endif /* #ifndef _GAN_CORNER_FEATURE_H */
