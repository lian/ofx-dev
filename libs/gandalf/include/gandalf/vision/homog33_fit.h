/**
 * File:          $RCSfile: homog33_fit.h,v $
 * Module:        Fit a 2D projective transformation to point/line data
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.19 $
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

#ifndef _GAN_HOMOG33_FIT_H
#define _GAN_HOMOG33_FIT_H

#include <gandalf/linalg/3vector.h>
#include <gandalf/linalg/3x3matrix.h>
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
 * \brief Type of matching feature when computing 2D homography.
 */
typedef enum
{
   GAN_HOMOG33_POINT, /**< Match scene point to image point */
   GAN_HOMOG33_LINE, /**< Match scene line to image line */
   GAN_HOMOG33_LINE_ENDPOINTS, /**< Match scene line endpoints to image line */
   GAN_HOMOG33_IGNORE /**< rejected match */
}
Gan_Homog33MatchType;

/**
 * \brief Structure to hold details of scene and image data to be used in
 *        computing 2D homographies.
 */
typedef struct
{
   Gan_Homog33MatchType type;
   union
   {
      struct { Gan_Vector3 X, x; } p; /**< point --> point match */
      struct { Gan_Vector3 L, l; } l; /**< line --> line match */
      struct { Gan_Vector3 X1, X2, l; } le; /**< line endpoints -->
                                                 line match */
   } d;
} Gan_Homog33Match;

/**
 * \brief Macro: Initialises the calculation of a 3x3 homography.
 * \param sme A pointer to a symmetric eigensystem structure, or \c NULL
 *
 * Initialises the calculation of a 3x3 homography between two planes.
 * \return Non-\c NULL on success, \c NULL on failure.
 * \sa gan_homog33_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SymMatEigenStruct *gan_homog33_init ( Gan_SymMatEigenStruct *sme );
#else
#define gan_homog33_init(sme) gan_symeigen_form(sme,9)
#endif

/**
 * \brief Macro: Frees the structure used to calculate a 3x3 homography.
 * \param sme A pointer to a symmetric eigensystem structure
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Frees the structure used to calculate a 3x3 homography between two planes.
 *
 * \sa gan_homog33_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_homog33_free ( Gan_SymMatEigenStruct *sme );
#else
#define gan_homog33_free(sme) gan_symeigen_free(sme)
#endif

GANDALF_API Gan_Bool gan_homog33_increment_p ( Gan_SymMatEigenStruct *sme,
                                   Gan_Vector3 *X, Gan_Vector3 *x,
                                   double scale, int *eq_count );
GANDALF_API Gan_Bool gan_homog33_increment_l ( Gan_SymMatEigenStruct *sme,
                                   Gan_Vector3 *L, Gan_Vector3 *l,
                                   double scale,
                                   int *eq_count );
GANDALF_API Gan_Bool gan_homog33_increment_le ( Gan_SymMatEigenStruct *sme,
                                    Gan_Vector3 *X, Gan_Vector3 *l,
                                    double scale, int *eq_count );
GANDALF_API Gan_Bool gan_homog33_solve ( Gan_SymMatEigenStruct *sme, int eq_count,
                             Gan_Matrix33 *P );
GANDALF_API Gan_Bool gan_homog33_fit ( Gan_Homog33Match *match, unsigned nmatches,
                           Gan_Matrix33 *H );
GANDALF_API Gan_Bool gan_homog33_fit_points ( const Gan_Vector3 *x, const Gan_Vector3 *X,
                                  unsigned int n, Gan_Matrix33 *H );

/**
 * \brief Macro: Resets the structure used to calculate a 3x3 homography.
 * \param sme A pointer to a symmetric eigensystem structure
 *
 * Resets the structure used to calculate a 3x3 homography between two planes.
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 * \sa gan_homog33_increment_l().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_homog33_reset ( Gan_SymMatEigenStruct *sme );
#else
#define gan_homog33_reset(sme) gan_symeigen_reset((sme),9)
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

#endif /* #ifndef _GAN_HOMOG33_FIT_H */
