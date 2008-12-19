/**
 * File:          $RCSfile: lev_marq.h,v $
 * Module:        Levenberg-Marquardt non-linear minimisation algorithm
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

#ifndef _GAN_LEV_MARQ_H
#define _GAN_LEV_MARQ_H

#include <gandalf/linalg/vec_gen.h>
#include <gandalf/linalg/mat_gen.h>
#include <gandalf/linalg/mat_square.h>
#include <gandalf/common/linked_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup LevenbergMarquardt
 * \{
 */

/**
 * \brief Observation type for Levenberg-Marquardt minimisation.
 */
typedef enum
{
   GAN_LEV_MARQ_OBS_H,        /**< h-type observations */
   GAN_LEV_MARQ_OBS_H_ROBUST, /**< robust h-type observations */
   GAN_LEV_MARQ_OBS_F         /**< F-type observations */
} Gan_LevMarqObsType;

/**
 * \brief Observation function for standard h-type observations.
 *
 * Observation function for standard h-type observations
 * \f[
 *     z = h(x) + w
 * \f]
 */
GANDALF_API typedef Gan_Bool (*Gan_LevMarqObsFunc_h) ( Gan_Vector *x,
                                           Gan_Vector *z, void *zdata,
                                           Gan_Vector *h, Gan_Matrix *H );

/**
 * \brief Observation function for F-type observations.
 *
 * Observation function for F-type observations
 * \f[
 *     F(x,z+w) = 0
 * \f]
 */
GANDALF_API typedef Gan_Bool (*Gan_LevMarqObsFunc_F) ( Gan_Vector *x,
                                           Gan_Vector *z, void *zdata,
                                           Gan_Vector *F, Gan_Matrix *Hx,
                                           Gan_Matrix *Hz );

/**
 * \brief Observation structure for Levenberg-Marquardt minimisation.
 */
typedef struct Gan_LevMarqObs
{
   /// type of observation
   Gan_LevMarqObsType type;

   union
   {
      struct
      {
         /// h-type observation function
         Gan_LevMarqObsFunc_h func;

         /// observation vector
         Gan_Vector z;

         /// user pointer to pass along with z
         void *zdata;

         /// inverse covariance matrix N
         Gan_SquMatrix Ni;

         /// scaling of covariance for outlier distribution, if any
         double var_scale;

         /// cut-off point for chi-squared distribution to switch to outlier
         /// distribution, if any
         double chi2;

         /// adjustment to chi-squared residual when using the outlier
         /// distribution
         double chi2_offset;
      } h;

      struct
      {
         /// h-type observation function
         Gan_LevMarqObsFunc_F func;

         /// observation vector
         Gan_Vector z;

         /// user pointer to pass along with z
         void *zdata;

         /// covariance matrix N
         Gan_SquMatrix N;
      } F;
   } details;

   /// whether this observation is an outlier
   Gan_Bool outlier;
} Gan_LevMarqObs;

/**
 * \brief Structure for holding state of Levenberg-Marquardt algorithm.
 */
typedef struct Gan_LevMarqStruct
{
   /// state parameters and old values
   Gan_Vector x, xold;

   /// existing residual
   double residual;

   /// information matrix and vector
   Gan_SquMatrix A;
   Gan_Vector    a;

   /// covariance matrix
   Gan_SquMatrix P;

   /// list of observations
   Gan_List *obs_list;

   /// vector used for observation, and matrices for its Jacobians with
   /// respect to x and z
   Gan_Vector hF;
   Gan_Matrix Hx, Hz;

   /// matrices to hold products N^-1*Hx, Hx^T*N^-1*Hx, Hx^T*N^-1*v and
   /// N^-1*v
   Gan_Matrix    NiHx;
   Gan_SquMatrix HxTNiHx;
   Gan_Vector    HxTNiv;
   Gan_Vector    Niv;

   /// matrix to hold inverse observation covariance for F-type observations
   Gan_SquMatrix Ni;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_LevMarqStruct;

/// Callback function for initialising Levenberg-Marquardt algorithm
typedef Gan_Bool (*Gan_LevMarqInitFunc) ( Gan_Vector *x, Gan_List *obs_list,
                                          void *data );

GANDALF_API Gan_LevMarqStruct *gan_lev_marq_form ( Gan_LevMarqStruct *lm );
GANDALF_API Gan_LevMarqObs *gan_lev_marq_obs_h ( Gan_LevMarqStruct *lm,
                                     Gan_Vector *z, void *zdata,
                                     Gan_SquMatrix *Ni,
                                     Gan_LevMarqObsFunc_h obs_func );
GANDALF_API Gan_LevMarqObs *gan_lev_marq_obs_h_robust ( Gan_LevMarqStruct *lm,
                                            Gan_Vector *z, void *zdata,
                                            Gan_SquMatrix *Ni,
                                            Gan_LevMarqObsFunc_h obs_func,
                                            double var_scale, double chi2 );
GANDALF_API Gan_LevMarqObs *gan_lev_marq_obs_F ( Gan_LevMarqStruct *lm,
                                     Gan_Vector *z, void *zdata,
                                     Gan_SquMatrix *Ni,
                                     Gan_LevMarqObsFunc_F obs_func );
GANDALF_API Gan_Bool gan_lev_marq_init ( Gan_LevMarqStruct *lm,
                             Gan_LevMarqInitFunc init_func,
                             void *data, double *residualp );
GANDALF_API Gan_Bool gan_lev_marq_iteration ( Gan_LevMarqStruct *lm, double lambda,
                                  double *residual );
GANDALF_API Gan_Vector    *gan_lev_marq_get_x ( Gan_LevMarqStruct *lm );
GANDALF_API Gan_SquMatrix *gan_lev_marq_get_P ( Gan_LevMarqStruct *lm );
GANDALF_API void gan_lev_marq_free ( Gan_LevMarqStruct *lm );

/**
 * \brief Macro: Allocates a Levenberg-Marquardt structure.
 *
 * Allocates a structure for computing Levenberg-Marquardt optimisation.
 *
 * \return Pointer to successfully allocated structure or <B>NULL</B>.
 * \sa gan_lev_marq_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_LevMarqStruct *gan_lev_marq_alloc(void);
#else
#define gan_lev_marq_alloc() gan_lev_marq_form(NULL)
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

#endif /* #ifndef _GAN_LEV_MARQ_H */
