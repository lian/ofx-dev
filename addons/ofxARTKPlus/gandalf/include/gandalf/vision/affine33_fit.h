/**
 * File:          $RCSfile: affine33_fit.h,v $
 * Module:        Fit a 2D affine transformation to point/line data
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.13 $
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

#ifndef _GAN_AFFINE33_FIT_H
#define _GAN_AFFINE33_FIT_H

#include <gandalf/linalg/3vector.h>
#include <gandalf/linalg/3x3matrix.h>
#include <gandalf/linalg/2x3matrix.h>
#include <gandalf/linalg/pseudo_inverse.h>
#include <gandalf/vision/homog33_fit.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup GeomFitting
 * \{
 */

/**
 * \brief Macro: Initialises the calculation of a 3x3 affine homography.
 * \param pis A pointer to a pseudo-inverse structure, or \c NULL
 *
 * Initialises the calculation of a 3x3 affine homography between two planes.
 * \return Non-\c NULL on success, \c NULL on failure.
 * \sa gan_affine33_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_PseudoInverseStruct *gan_affine33_init ( Gan_PseudoInverseStruct *pis );
#else
#define gan_affine33_init(pis) gan_pseudoinv_form(pis,6,1)
#endif

/**
 * \brief Macro: Frees structure used to calculate an affine 3x3 homography.
 * \param pis A pointer to a pseudo-inverse structure
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Frees the structure used to calculate a 3x3 affine homography between two
 * planes.
 *
 * \sa gan_affine33_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_affine33_free ( Gan_PseudoInverseStruct *pis );
#else
#define gan_affine33_free(pis) gan_pseudoinv_free(pis)
#endif

GANDALF_API Gan_Bool gan_affine33_increment_p ( Gan_PseudoInverseStruct *pis,
                                    Gan_Vector3 *X, Gan_Vector3 *x,
                                    double scale, int *eq_count );
GANDALF_API Gan_Bool gan_affine33_increment_le ( Gan_PseudoInverseStruct *pis,
                                     Gan_Vector3 *X, Gan_Vector3 *l,
                                     double scale, int *eq_count );
GANDALF_API Gan_Bool gan_affine33_solve ( Gan_PseudoInverseStruct *pis, int eq_count,
                              Gan_Matrix23 *P );
GANDALF_API Gan_Bool gan_affine33_fit ( Gan_Homog33Match *match, unsigned nmatches,
                            Gan_Matrix23 *H );

/**
 * \brief Macro: Resets the structure used to calculate a 3x3 affine
 *               homography.
 * \param pis A pointer to a pseudo-inverse structure
 *
 * Resets the structure used to calculate a 3x3 affine homography between
 * two planes.
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 * \sa gan_affine33_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_affine33_reset ( Gan_PseudoInverseStruct *pis );
#else
#define gan_affine33_reset(pis) gan_pseudoinv_reset((pis),6,1)
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

#endif /* #ifndef _GAN_AFFINE33_FIT_H */
