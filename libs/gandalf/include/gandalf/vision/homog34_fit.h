/**
 * File:          $RCSfile: homog34_fit.h,v $
 * Module:        Fit a 3D --> 2D projective transformation to point/line data
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

#ifndef _HOMOG34_FIT_H
#define _HOMOG34_FIT_H

#include <gandalf/linalg/4vector.h>
#include <gandalf/linalg/3x4matrix.h>
#include <gandalf/linalg/mat_square.h>
#include <gandalf/linalg/symmat_eigen.h>

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
 * \brief Macro: Initialises the calculation of a 3x4 homography.
 * \param sme A pointer to a symmetric eigensystem structure, or \c NULL
 *
 * Initialises the calculation of a 3x4 homography
 *
 * \return non-\c NULL on success, \c NULL on failure.
 * \sa gan_homog34_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SymMatEigenStruct *gan_homog34_init ( Gan_SymMatEigenStruct *sme );
#else
#define gan_homog34_init(sme) gan_symeigen_form(sme,12)
#endif

/**
 * \brief Macro: Frees the structure used to calculate a 3x4 homography.
 * \param sme A pointer to a symmetric eigensystem structure
 * Frees the structure used to calculate a 3x4 homography.
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 * \sa gan_homog34_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_homog34_free ( Gan_SymMatEigenStruct *sme );
#else
#define gan_homog34_free(sme) gan_symeigen_free(sme)
#endif

GANDALF_API Gan_Bool gan_homog34_increment_p ( Gan_SymMatEigenStruct *sme,
                                   Gan_Vector4 *X, Gan_Vector3 *x,
                                   double scale, int *eq_count );
GANDALF_API Gan_Bool gan_homog34_increment_le ( Gan_SymMatEigenStruct *sme,
                                    Gan_Vector4 *X1, Gan_Vector4 *X2,
                                    Gan_Vector3 *l, double scale,
                                    int *eq_count );
GANDALF_API Gan_Bool gan_homog34_solve ( Gan_SymMatEigenStruct *sme, int eq_count,
                             Gan_Matrix34 *P );

/**
 * \brief Macro: Resets the structure used to calculate a 3x4 homography.
 * \param sme A pointer to a symmetric eigensystem structure
 *
 * Resets the structure used to calculate a 3x4 homography between 3D and 2D
 * coordinates.
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 * \sa gan_homog34_increment_le().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_homog34_reset ( Gan_SymMatEigenStruct *sme );
#else
#define gan_homog34_reset(sme) gan_symeigen_reset((sme),12)
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

#endif /* #ifndef _HOMOG34_FIT_H */
