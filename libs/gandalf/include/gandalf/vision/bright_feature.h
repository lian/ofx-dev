/**
 * File:          $RCSfile: bright_feature.h,v $
 * Module:        Image edge point definition and functions
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

#ifndef _GAN_BRIGHT_FEATURE_H
#define _GAN_BRIGHT_FEATURE_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/vision/camera.h>
#include <gandalf/vision/cameraf.h>
#include <gandalf/vision/local_feature.h>
#include <gandalf/linalg/2x3matrixf.h>
#include <gandalf/linalg/2vectorf.h>


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

/// 2D bright feature structure
typedef struct Gan_brightFeature
{
   /// row/column coordinates in coordinate frame of 2D feature array
   unsigned short r, c;

   /// potentially sub-pixel coordinates of edge feature in coordinate
   /// frame defined by edge map
   Gan_Vector2_f p;

   /// coordinates of feature with any non-linear image distortion removed
   Gan_Vector2_f pu;



   /**
    * The angle is measured from the positive x axis (zero) towards the
    * positive y axis (pi/2), and should be in the range [-pi,pi].
    * The angle should point in the direction of higher image
    * intensity, or a suitably analagous direction.
    */


   /// next feature in list for when edges are stored in a list
   struct Gan_brightFeature *next;

   /// previous feature in list for when edges are stored in a list
   struct Gan_brightFeature *prev;
} Gan_brightFeature;



/// Definition of 2D bright feature map structure
typedef struct Gan_brightFeatureMap
{
   /// number of edge features stored
   unsigned nbright;

   /// array of edge features
   Gan_brightFeature *bright;

   /// allocated limit on number of edge features
   unsigned max_nbright;

   /// dimensions of image region in which edge features have been computed
   unsigned height, width;

   /// whether the following A, Ai fields are set
   Gan_Bool A_set;

   /// transformation between region coordinates (0..width) and (0..height)
   /// and edge coordinates, and its inverse
   Gan_Matrix23_f A, Ai;

   /// calibration structure defining camera used for non-linear distortion
   /// correction
   Gan_Camera_f camera;

   /// local blocked feature index map
   Gan_LocalFeatureMap local_fmap;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_brightFeatureMap;

GANDALF_API Gan_brightFeatureMap *gan_bright_feature_map_form ( Gan_brightFeatureMap *bmap,
                                                unsigned max_nbright);
GANDALF_API void gan_bright_feature_map_free ( Gan_brightFeatureMap *bmap );
GANDALF_API Gan_Bool gan_bright_feature_map_clear ( Gan_brightFeatureMap *bmap,
                              unsigned height, unsigned width,
                              Gan_Matrix23_f *A, Gan_Camera *camera,
                                                    Gan_LocalFeatureMapParams *lpms );
GANDALF_API Gan_brightFeature *gan_bright_feature_add ( Gan_brightFeatureMap *bmap,
                        unsigned r,  unsigned c,
                          float rf, float cf,int status);


GANDALF_API Gan_Bool gan_bright_feature_map_postprocess ( Gan_brightFeatureMap *bmap );

/// Macro: Allocates a edge feature map structure.
/**
 * \param max_nedges The number of edges initially to allocate for
 * \param max_nstrings The number of strings initially to allocate for
 *
 * Allocates a structure to hold edge features, and sets
 * it to be empty. This macro calls gan_edge_feature_map_form().
 *
 * \return non-\c NULL the allocated feature map, or \c NULL on failure.
 * \sa gan_edge_feature_map_form(), gan_edge_feature_map_free().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_brightFeatureMap *gan_bright_feature_map_alloc ( unsigned max_nbright );
#else
#define gan_bright_feature_map_alloc(max_nbright)\
   gan_bright_feature_map_form(NULL,max_nbright)
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

#endif /* #ifndef _GAN_BRIGTH_FEATURE_H */
