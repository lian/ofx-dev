/**
 * File:          $RCSfile: orthog_line.h,v $
 * Module:        Line segment fitting algorithm
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.14 $
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

#ifndef _GAN_ORTHOG_LINE_H
#define _GAN_ORTHOG_LINE_H

#include <gandalf/vision/line_feature.h>
#include <gandalf/vision/edge_feature.h>

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

GANDALF_API Gan_LineFeatureMap *gan_orthog_line_q ( Gan_EdgeFeatureMap *edge_map,
                                        unsigned min_length,
                                        unsigned cut_size,
                                        float rms_error_thres,
                                        Gan_LocalFeatureMapParams *lpms,
                                        Gan_Bool copy_points,
                                        Gan_LineFeatureMap *line_map,
                                        void (*set_progress) ( void *,
                                                               unsigned ),
                                        void *progress_obj );

/**
 * \brief Macro: Computes image lines using an orthogonal regression algorithm.
 * \param edge_map The input edge map
 * \param min_length The minimum line length
 * \param cut_size The length to cut off the ends of each line
 * \param rms_error_thres Threshold on RMS error of line fit
 * \param lpms Pointer to local feature map parameters or NULL
 * \param copy_points Whether to copy the fitted edge points into a line
 * \param set_progress Function to update progress from 0 to 99  or \c NULL
 * \param progress_obj Pointer passed into \a set_progress function or \c NULL
 *
 * Applies a recursive orthogonal regression line finder to
 * edges found in an image. Macro call to gan_orthog_line_q().
 *
 * \return Non-\c NULL a pointer to the computed line map structure, or
 *         \c NULL on failure.
 * \sa gan_orthog_line_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_LineFeatureMap *
 gan_orthog_line_s ( Gan_EdgeFeatureMap *edge_map, unsigned min_length,
                     unsigned cut_size, float rms_error_thres,
                     Gan_LocalFeatureMapParams *lpms, Gan_Bool copy_points,
                     void (*set_progress) ( void *, unsigned ),
                     void *progress_obj );
#else
#define gan_orthog_line_s(edge_map,min_length,cut_size,rms_error_thres,lpms,copy_points,setprog,progobj)\
        gan_orthog_line_q(edge_map,min_length,cut_size,rms_error_thres,lpms,copy_points,NULL,setprog,progobj)
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

#endif /* #ifndef _GAN_ORTHOG_LINE_H */
