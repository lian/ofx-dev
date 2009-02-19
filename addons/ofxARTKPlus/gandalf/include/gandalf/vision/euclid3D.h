/**
 * File:          $RCSfile: euclid3D.h,v $
 * Module:        Euclidean 3D geometry
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

#ifndef _GAN_EUCLID3D_H
#define _GAN_EUCLID3D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gandalf/vision/rotate3D.h>
#include <gandalf/linalg/4x4matrix.h>
#include <gandalf/linalg/3x4matrix.h>

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup Euclid
 * \{
 */

/**
 * \brief 3D pose structure.
 */
typedef struct
{
   /// rotation parameters
   Gan_Rot3D   rot;

   /// translation parameters
   Gan_Vector3 trans;
} Gan_Euclid3D;

/**
 * \brief Cross-covariance between rotation and translation
 */
typedef struct Gan_Euclid3D_TRCov
{
   /// Type of rotation
   Gan_Rot3D_Type type;

   /// Covariance matrix
   union
   {
      /// quaternion representation (4 parameters)
      Gan_Matrix34 q;

      /// exponential representation (3 parameters)
      Gan_Matrix33 le;
   } d;
} Gan_Euclid3D_TRCov;

/**
 * \brief Covariance of 3D pose.
 */
typedef struct
{
   /// covariance of rotation parameters
   Gan_Rot3D_Cov      Crr;

   /// cross-covariance between translation \& rotation
   Gan_Euclid3D_TRCov Ctr;

   /// covariance of translation parameters
   Gan_SquMatrix33    Ctt;
} Gan_Euclid3r_Cov;

GANDALF_API Gan_Bool gan_euclid3D_build_quaternion ( Gan_Euclid3D *euc,
                                         double TX, double TY, double TZ,
                                         double q0, double q1,
                                         double q2, double q3 );
GANDALF_API Gan_Bool gan_euclid3D_build_exponential ( Gan_Euclid3D *euc,
                                          double TX, double TY, double TZ,
                                          double rx, double ry, double rz );
GANDALF_API Gan_Bool gan_euclid3D_build_angle_axis ( Gan_Euclid3D *euc,
                                         double TX, double TY, double TZ,
                                         double angle,
                                         double ax, double ay, double az );
GANDALF_API Gan_Bool gan_euclid3D_build_matrix ( Gan_Euclid3D *euc,
                                     double TX, double TY, double TZ,
                                     double Rxx, double Rxy, double Rxz,
                                     double Ryx, double Ryy, double Ryz,
                                     double Rzx, double Rzy, double Rzz );
GANDALF_API void         gan_euclid3D_ident_q ( Gan_Euclid3D *euc,
                                    Gan_Rot3D_Type rot_type );
GANDALF_API Gan_Euclid3D gan_euclid3D_ident_s ( Gan_Rot3D_Type rot_type );
GANDALF_API Gan_Bool     gan_euclid3D_scale_q ( Gan_Euclid3D *euc_src, double scale,
                                    Gan_Euclid3D *euc_dest );
GANDALF_API Gan_Euclid3D gan_euclid3D_scale_s ( Gan_Euclid3D *euc, double scale );

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale pose parameters in-place.
 *
 * Implemented as macro calls to gan_vec3_scale_i() and gan_rot3D_scale_i().
 */
GANDALF_API Gan_Bool gan_euclid3D_scale_i ( Gan_Euclid3D *euc1, double s );
#else
#define gan_euclid3D_scale_i(e,s) (gan_vec3_scale_i(&(e)->trans,s),gan_rot3D_scale_i(&(e)->rot,s),GAN_TRUE)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Divide pose parameters by a scalar.
 *
 * Implemented as macro calls to gan_vec3_divide_q() and gan_rot3D_divide_q().
 */
GANDALF_API Gan_Bool gan_euclid3D_divide_q ( Gan_Euclid3D *euc1, double s,
                                 Gan_Euclid3D *euc2 );
#else
#define gan_euclid3D_divide_q(es,s,ed) (gan_vec3_divide_q(&(es)->trans,s,&(ed)->trans),gan_rot3D_divide_q(&(es)->rot,s,&(ed)->rot))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Divide pose parameters by a scalar in-place.
 *
 * Implemented as macro calls to gan_vec3_divide_i() and gan_rot3D_divide_i().
 */
GANDALF_API Gan_Bool gan_euclid3D_divide_i ( Gan_Euclid3D *euc1, double s );
#else
#define gan_euclid3D_divide_i(e,s) (gan_vec3_divide_i(&(e)->trans,s),gan_rot3D_divide_i(&(e)->rot,s))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Add two sets of pose parameters.
 *
 * Implemented as macro calls to gan_vec3_add_q() and gan_rot3D_add_q().
 */
GANDALF_API Gan_Bool gan_euclid3D_add_q ( Gan_Euclid3D *euc1, Gan_Euclid3D *euc2,
                              Gan_Euclid3D *euc3 );
#else
#define gan_euclid3D_add_q(e1,e2,e3) (gan_vec3_add_q(&(e1)->trans,&(e2)->trans,&(e3)->trans),gan_rot3D_add_q(&(e1)->rot,&(e2)->rot,&(e3)->rot))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Subtract two sets of pose parameters.
 *
 * Implemented as macro calls to gan_vec3_sub_q() and gan_rot3D_sub_q().
 */
GANDALF_API Gan_Bool gan_euclid3D_sub_q ( Gan_Euclid3D *euc1, Gan_Euclid3D *euc2,
                              Gan_Euclid3D *euc3 );
#else
#define gan_euclid3D_sub_q(e1,e2,e3) (gan_vec3_sub_q(&(e1)->trans,&(e2)->trans,&(e3)->trans),gan_rot3D_sub_q(&(e1)->rot,&(e2)->rot,&(e3)->rot))
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

#endif /* #ifndef _GAN_EUCLID3D_H */
