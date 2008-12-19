/**
 * File:          $RCSfile: segment_strings.h,v $
 * Module:        Edge string segmentation algorithm
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.1 $
 * Last edited:   $Date: 2003/10/29 17:27:31 $
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

#ifndef _GAN_SEGMENT_STRINGS_H
#define _GAN_SEGMENT_STRINGS_H

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

Gan_Bool gan_segment_strings_q ( Gan_EdgeFeatureMap *edge_map,
                                 unsigned test_length, float rms_error_thres,
                                 unsigned string_length_thres );


/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_SEGMENT_STRINGS_H */
