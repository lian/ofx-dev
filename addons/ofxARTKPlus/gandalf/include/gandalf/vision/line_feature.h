/**
 * File:          $RCSfile: line_feature.h,v $
 * Module:        Image line segment definition and functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.22 $
 * Last edited:   $Date: 2005/11/07 23:24:31 $
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

#ifndef _GAN_LINE_FEATURE_H
#define _GAN_LINE_FEATURE_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/vision/camera.h>
#include <gandalf/vision/local_feature.h>
#include <gandalf/image/pixel.h>
#include <gandalf/linalg/2vectorf.h>
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
 * \brief 2D line feature structure.
 */
typedef struct Gan_LineFeature
{
   /// row/column coordinates in coordinate frame of 2D feature array
   unsigned r1, c1, r2, c2;

   /// endpoints of line
   Gan_Vector2_f p1, p2;

   /// line feature strength/contrast value
   float strength;

   /// line parameters a*x + b*y + c = 0 scaled so that a^2 + b^2 = 1
   Gan_Vector3_f l;

   /// Covariance/inverse covariance of line midpoint position
   /**
    * covariance and inverse covariance for canonical line parameters
    * \f$ a/b \f$ in \f$ y=ax+b \f$, with \f$ x/y \f$ system centred on
    * midpoint of line \f$ (p1+p2)/2 \f$ with positive \f$ x \f$ axis along
    * the line towards \f$ p2 \f$ endpoint, and positive \f$ y \f$ axis
    * 90 degrees clockwise/anticlockwise from \f$ x \f$ axis for positive
    * \f$ y \f$ up/down respectively.
    */
   Gan_SquMatrix22_f N, Ni; 

   /// fields for user program to define
   int status;
   int index;

   /// array of points attached to this line
   Gan_Vector2_f *point;

   /// number of points attached to this line
   unsigned npoints;
} Gan_LineFeature;

/**
 * \brief 2D line feature map structure.
 */
typedef struct Gan_LineFeatureMap
{
   /// number of line features stored
   unsigned nlines;

   /// array of line features
   Gan_LineFeature *line;

   /// allocated limit on number of line features
   unsigned max_nlines;

   /// dimensions of image region in which line features have been computed
   unsigned height, width;

   /// whether the following A, Ai fields are set
   Gan_Bool A_set;

   /// transformation between region coordinates (0..width) and (0..height)
   /// and line coordinates, and its inverse
   Gan_Matrix23_f A, Ai;

   /// local blocked feature index map
   Gan_LocalFeatureMap local_fmap;

   /// array of points used to fit the lines to: may be \c NULL
   Gan_Vector2_f *point;

   /// current number of points
   unsigned npoints;

   /// maximum (allocated) number of points
   unsigned max_npoints;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_LineFeatureMap;

GANDALF_API Gan_LineFeatureMap *gan_line_feature_map_form ( Gan_LineFeatureMap *lmap,
                                                            unsigned max_nlines );
GANDALF_API Gan_LineFeatureMap *gan_line_feature_map_copy ( Gan_LineFeatureMap *lmap );
GANDALF_API void gan_line_feature_map_free ( Gan_LineFeatureMap *lmap );
GANDALF_API Gan_Bool gan_line_feature_map_clear ( Gan_LineFeatureMap *lmap,
                                      unsigned height, unsigned width,
                                      Gan_Matrix23_f *A,
                                      Gan_LocalFeatureMapParams *lpms );
GANDALF_API Gan_LineFeature *gan_line_feature_add ( Gan_LineFeatureMap *lmap,
                                        float y1, float x1,
                                        float y2, float x2,
                                        Gan_SquMatrix22_f *N,
                                        int status, int index,
                                        float strength,
                                        Gan_Vector2_f *point,
                                        unsigned npoints );
GANDALF_API Gan_Bool gan_line_feature_map_postprocess ( Gan_LineFeatureMap *lmap );

/**
 * \brief Macro: Allocates a line feature map structure.
 * \param max_nlines The number of lines initially to allocate for
 *
 * Allocates a structure to hold line features, and sets it to be empty.
 * This macro calls gan_line_feature_map_form().
 *
 * \return non-\c NULL the allocated feature map, or \c NULL on failure.
 * \sa gan_line_feature_map_form(), gan_line_feature_map_free().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_LineFeatureMap *gan_line_feature_map_alloc ( unsigned max_nlines );
#else
#define gan_line_feature_map_alloc(max_nlines)\
   gan_line_feature_map_form(NULL,max_nlines)
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

#endif /* #ifndef _GAN_LINE_FEATURE_H */
