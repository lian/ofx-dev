/**
 * File:          $RCSfile: edge_feature.h,v $
 * Module:        Image edge point definition and functions
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

#ifndef _GAN_EDGE_FEATURE_H
#define _GAN_EDGE_FEATURE_H

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

/// 2D edge feature structure
typedef struct Gan_EdgeFeature
{
   /// row/column coordinates in coordinate frame of 2D feature array
   unsigned short r, c;

   /// potentially sub-pixel coordinates of edge feature in coordinate
   /// frame defined by edge map
   Gan_Vector2_f p;

   /// coordinates of feature with any non-linear image distortion removed
   Gan_Vector2_f pu;

   /// edge feature strength/contrast value
   float strength;

   /// orientation of edge in radians, where applicable.
   /**
    * The angle is measured from the positive x axis (zero) towards the
    * positive y axis (pi/2), and should be in the range [-pi,pi].
    * The angle should point in the direction of higher image
    * intensity, or a suitably analagous direction.
    */
   float angle;

   /// covariance of feature edge in direction given by the orientation field
   /// (angle)
   float cov;

   /// status field for user program to define
   int status;

   /// index field for user program to define
   int index;

   /// next feature in list for when edges are stored in a list
   struct Gan_EdgeFeature *next;

   /// previous feature in list for when edges are stored in a list
   struct Gan_EdgeFeature *prev;
} Gan_EdgeFeature;

/// Structure defining a connected string of edge features
typedef struct Gan_EdgeString
{
   /// First edge in string
   Gan_EdgeFeature *first;

   /// Last edge in string
   Gan_EdgeFeature *last;

   /// Length of string
   unsigned length;
} Gan_EdgeString;

/// Definition of 2D edge feature map structure
typedef struct Gan_EdgeFeatureMap
{
   /// number of edge features stored
   unsigned nedges;

   /// array of edge features
   Gan_EdgeFeature *edge;

   /// allocated limit on number of edge features
   unsigned max_nedges;

   /// number of connected edge strings stored
   unsigned nstrings;

   /// array of connected strings of edges
   Gan_EdgeString *string;

   /// allocated limit on number of strings
   unsigned max_nstrings;

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
} Gan_EdgeFeatureMap;

GANDALF_API Gan_EdgeFeatureMap *gan_edge_feature_map_form ( Gan_EdgeFeatureMap *emap,
                                                unsigned max_nedges,
                                                unsigned max_strings );
GANDALF_API void gan_edge_feature_map_free ( Gan_EdgeFeatureMap *emap );
GANDALF_API Gan_Bool gan_edge_feature_map_clear ( Gan_EdgeFeatureMap *emap,
                                      unsigned height, unsigned width,
                                      Gan_Matrix23_f *A, Gan_Camera *camera,
                                      Gan_LocalFeatureMapParams *lpms );
GANDALF_API Gan_EdgeFeature *gan_edge_feature_add ( Gan_EdgeFeatureMap *emap,
                                        unsigned r, unsigned c,
                                        float rf, float cf,
                                        float angle, float cov,
                                        int status, int index,
                                        float strength );
GANDALF_API Gan_EdgeString *gan_edge_feature_string_add ( Gan_EdgeFeatureMap *emap,
                                              Gan_EdgeFeature *edge );
GANDALF_API Gan_Bool gan_edge_feature_string_set_status ( Gan_EdgeString *string,
                                              int status );
GANDALF_API Gan_Bool gan_edge_feature_map_postprocess ( Gan_EdgeFeatureMap *emap );

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
GANDALF_API Gan_EdgeFeatureMap *gan_edge_feature_map_alloc ( unsigned max_nedges,
                                                 unsigned max_nstrings );
#else
#define gan_edge_feature_map_alloc(max_nedges,max_nstrings)\
   gan_edge_feature_map_form(NULL,max_nedges,max_nstrings)
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

#endif /* #ifndef _GAN_EDGE_FEATURE_H */
