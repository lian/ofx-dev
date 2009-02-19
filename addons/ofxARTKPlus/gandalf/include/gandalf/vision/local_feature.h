/**
 * File:          $RCSfile: local_feature.h,v $
 * Module:        Local blocked feature map definition & functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.15 $
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

#ifndef _GAN_LOCAL_FEATURE_H
#define _GAN_LOCAL_FEATURE_H

#include <gandalf/common/misc_defs.h>
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

/**
 * \brief Structure to hold blocked local feature information.
 */
typedef struct Gan_LocalFeatureMap
{
   /// number of blocks vertically and horizontally
   unsigned yblocks, xblocks;

   /// distance in pixels between adjacent blocks in the vertical and
   /// horizontal directions
   unsigned ystep, xstep;

   /// half "catchment area" of each block as multiple of ystep/xstep
   unsigned bsize2;

   /// integer image holding the number of features in each block
   Gan_Image nfeatures;

   /// pointer image holding arrays of feature indices into an associated
   /// feature map
   Gan_Image index;

   /// whether this structure is dynamically allocated
   Gan_Bool alloc;
} Gan_LocalFeatureMap;

/**
 * \brief Structure to hold parameters for blocked local features.
 */
typedef struct Gan_LocalFeatureMapParams
{
   /// distance in pixels between adjacent blocks in the vertical and
   /// horizontal directions
   unsigned ystep, xstep;

   /// "catchment area" of each block as odd multiple of ystep/xstep
   unsigned bsize;
} Gan_LocalFeatureMapParams;

GANDALF_API Gan_LocalFeatureMap *
      gan_local_feature_map_form ( Gan_LocalFeatureMap *pmap,
                                   unsigned height, unsigned width,
                                   Gan_LocalFeatureMapParams *pms );
GANDALF_API void gan_local_feature_map_free ( Gan_LocalFeatureMap *pmap );
GANDALF_API Gan_Bool gan_local_feature_map_clear ( Gan_LocalFeatureMap *pmap,
                                       unsigned height, unsigned width,
                                       Gan_LocalFeatureMapParams *pms );
GANDALF_API Gan_Bool gan_local_feature_point_add ( Gan_LocalFeatureMap *pmap,
                                       unsigned r, unsigned c,
                                       unsigned index );
GANDALF_API Gan_Bool gan_local_feature_line_add ( Gan_LocalFeatureMap *pmap,
                                      unsigned r1, unsigned c1,
                                      unsigned r2, unsigned c2,
                                      unsigned index );
GANDALF_API Gan_Bool gan_local_feature_map_set_indices ( Gan_LocalFeatureMap *pmap );
GANDALF_API Gan_Bool gan_local_feature_map_find_block ( Gan_LocalFeatureMap *pmap,
                                            double y, double x,
                                            Gan_Matrix23 *Ai,
                                            unsigned *cr, unsigned *cc );

/**
 * \brief Macro: Allocates a local feature map structure.
 * \param height The vertical size of the local feature map
 * \param width The vertical size of the local feature map
 * \param pms Pointer to a structure holding other parameters
 *
 * Allocates a structure to hold a local blocked representation of indices of
 * features stored in a separate feature map (e.g. a point/edge/line feature
 * map), and sets it to be empty. The \a pms structure contains the
 * vertical/horizontal offsets between blocks, and the "catchment area" or
 * size of each block.
 *
 * This macro calls gan_local_feature_map_form().
 *
 * \return non-\c NULL the allocated local feature map, \c NULL on failure.
 * \sa gan_local_feature_map_form(), gan_local_feature_map_free().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_LocalFeatureMap *
 gan_local_feature_map_alloc ( unsigned height, unsigned width,
                               Gan_LocalFeatureMapParams *pms );
#else
#define gan_local_feature_map_alloc(height,width,pms)\
    gan_local_feature_map_form(NULL,height,width,pms)
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

#endif /* #ifndef _GAN_LOCAL_FEATURE_H */
