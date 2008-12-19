/**
 * File:          $RCSfile: rotate3D.h,v $
 * Module:        Handling 3D rotations
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.17 $
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

#ifndef _GAN_ROTATE3D_H
#define _GAN_ROTATE3D_H

#include <stdarg.h>
#include <gandalf/linalg/3vector.h>
#include <gandalf/linalg/4vector.h>
#include <gandalf/linalg/3x3matrix.h>
#include <gandalf/linalg/3x4matrix.h>
#include <gandalf/linalg/4x4matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup Rotation
 * \{
 */

/**
 * \brief Types of rotation handled by Gandalf.
 */
typedef enum
{
   /// Quaternion representation of rotation
   GAN_ROT3D_QUATERNION,

   /// Exponential matrix representation of rotation
   GAN_ROT3D_EXPONENTIAL,

   /// Angle/axis representation of rotation
   GAN_ROT3D_ANGLE_AXIS,

   /// Matrix representation of rotation
   GAN_ROT3D_MATRIX
} Gan_Rot3D_Type;

/**
 * \brief Quaternion structure.
 */
typedef struct Gan_Quaternion
{
   double q0; /**< First quaternion parameter representing rotation angle */
   double q1; /**< First quaternion parameter representing axis x-coordinate */
   double q2; /**< First quaternion parameter representing axis y-coordinate */
   double q3; /**< First quaternion parameter representing axis z-coordinate */
} Gan_Quaternion;

/**
 * \brief Structure representing 3D rotation.
 */
typedef struct Gan_Rot3D
{
   /// representation used
   Gan_Rot3D_Type type;

   /// Rotation data
   union
   {
      /// quaternion form
      Gan_Quaternion q;

      /// exponential form
      Gan_Vector3 r;

      /// angle/axis form
      struct { Gan_Vector3 axis; double angle; } aa;

      /// matrix form
      Gan_Matrix33 R;
   } data;
} Gan_Rot3D;

/**
 * \brief Structure representing covariance of 3D rotation.
 */
typedef struct Gan_Rot3D_Cov
{
   /// representation used
   Gan_Rot3D_Type type;

   /// Covariance data
   union
   {
      /// covariance of quaternion
      Gan_SquMatrix44 q;

      /// covariance of exponential rotation vector
      Gan_SquMatrix33 r;
   } data;
} Gan_Rot3D_Cov;

/* quaternion functions */

GANDALF_API void           gan_quat_fill_q ( Gan_Quaternion *q,
                                 double q0, double q1,
                                 double q2, double q3 );
GANDALF_API Gan_Quaternion gan_quat_fill_s ( double q0, double q1,
                                 double q2, double q3 );
GANDALF_API Gan_Quaternion gan_quat_scale_s  ( Gan_Quaternion *q, double s );
GANDALF_API Gan_Quaternion gan_quat_divide_s ( Gan_Quaternion *q, double s );
GANDALF_API Gan_Quaternion gan_quat_unit_s ( Gan_Quaternion *q );

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale a quaternion.
 *
 * Implemented as a macro call to gan_vec4_scale_q().
 */
GANDALF_API Gan_Quaternion *gan_quat_scale_q ( Gan_Quaternion *q1, double s,
                                   Gan_Quaternion *q2 );
#else
#define gan_quat_scale_q(q1,s,q2) gan_vec4_scale_q((Gan_Vector4 *)(q1),(s),(Gan_Vector4 *)q2)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale a quaternion in-place.
 *
 * Implemented as a macro call to gan_vec4_scale_i().
 */
GANDALF_API Gan_Quaternion *gan_quat_scale_i ( Gan_Quaternion *q1, double s );
#else
#define gan_quat_scale_i(q,s) gan_vec4_scale_i((Gan_Vector4 *)(q),(s))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Divide a quaternion by a scalar.
 *
 * Implemented as a macro call to gan_vec4_divide_q().
 */
GANDALF_API Gan_Quaternion *gan_quat_divide_q ( Gan_Quaternion *q1, double s,
                                    Gan_Quaternion *q2 );
#else
#define gan_quat_divide_q(q1,s,q2) gan_vec4_divide_q((Gan_Vector4 *)(q1),(s),(Gan_Vector4 *)q2)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Divide a quaternion by a scalar in-place.
 *
 * Implemented as a macro call to gan_vec4_divide_i().
 */
GANDALF_API Gan_Quaternion *gan_quat_divide_i ( Gan_Quaternion *q1, double s );
#else
#define gan_quat_divide_i(q,s) gan_vec4_divide_i((Gan_Vector4 *)(q),(s))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale a quaternion to unit norm.
 *
 * Implemented as a macro call to gan_quat_unit_q().
 */
GANDALF_API Gan_Quaternion *gan_quat_unit_q ( Gan_Quaternion *q1, Gan_Quaternion *q2 );
#else
#define gan_quat_unit_q(q1,q2) gan_vec4_unit_q((Gan_Vector4 *)(q1),(Gan_Vector4 *)q2)
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Scale a quaternion to unit norm in-place.
 *
 * Implemented as a macro call to gan_vec4_unit_i().
 */
GANDALF_API Gan_Quaternion *gan_quat_unit_i ( Gan_Quaternion *q1 );
#else
#define gan_quat_unit_i(q) gan_vec4_unit_i((Gan_Vector4 *)(q))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Return the squared length of a quaternion.
 *
 * Implemented as a macro call to gan_vec4_sqrlen_q().
 */
GANDALF_API double gan_quat_sqrlen_q ( Gan_Quaternion *q1 );
#else
#define gan_quat_sqrlen_q(q) gan_vec4_sqrlen_q((Gan_Vector4 *)(q))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Return the squared length of a quaternion.
 *
 * Implemented as a macro call to gan_vec4_sqrlen_s().
 */
GANDALF_API double gan_quat_sqrlen_s ( Gan_Quaternion *q1 );
#else
#define gan_quat_sqrlen_s(q) gan_vec4_sqrlen_s((Gan_Vector4 *)(q))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Add two quaternions.
 *
 * Implemented as a macro call to gan_vec4_add_q().
 */
GANDALF_API Gan_Quaternion *gan_quat_add_q ( Gan_Quaternion *q1, Gan_Quaternion *q2,
                                 Gan_Quaternion *q3 );
#else
#define gan_quat_add_q(q1,q2,q3) gan_vec4_add_q((Gan_Vector4 *)(q1),(Gan_Vector4 *)(q2),(Gan_Vector4 *)(q3))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Subtract two quaternions.
 *
 * Implemented as a macro call to gan_vec4_sub_q().
 */
GANDALF_API Gan_Quaternion *gan_quat_sub_q ( Gan_Quaternion *q1, Gan_Quaternion *q2,
                                 Gan_Quaternion *q3 );
#else
#define gan_quat_sub_q(q1,q2,q3) gan_vec4_sub_q((Gan_Vector4 *)(q1),(Gan_Vector4 *)(q2),(Gan_Vector4 *)(q3))
#endif

GANDALF_API Gan_Bool gan_rot3D_build_quaternion ( Gan_Rot3D *rot,
                                      double q0, double q1,
                                      double q2, double q3 );
GANDALF_API Gan_Bool gan_rot3D_build_exponential ( Gan_Rot3D *rot,
                                       double rx, double ry, double rz );
GANDALF_API Gan_Bool gan_rot3D_build_angle_axis ( Gan_Rot3D *rot,
                                      double angle,
                                      double ax, double ay, double az );
GANDALF_API Gan_Bool gan_rot3D_build_matrix ( Gan_Rot3D *rot,
                                  double Rxx, double Rxy, double Rxz,
                                  double Ryx, double Ryy, double Ryz,
                                  double Rzx, double Rzy, double Rzz );
GANDALF_API Gan_Bool  gan_rot3D_ident_q ( Gan_Rot3D *rot, Gan_Rot3D_Type type );
GANDALF_API Gan_Rot3D gan_rot3D_ident_s ( Gan_Rot3D_Type type );
GANDALF_API Gan_Bool  gan_rot3D_apply_v3_q ( Gan_Rot3D *rot,
                                 Gan_Vector3 *X, Gan_Vector3 *X_new );
GANDALF_API Gan_Vector3 gan_rot3D_apply_v3_s ( Gan_Rot3D *rot, Gan_Vector3 *X );
GANDALF_API Gan_Bool  gan_rot3D_mult_q ( Gan_Rot3D *rot1, Gan_Rot3D *rot2,
                             Gan_Rot3D *rot3 );
GANDALF_API Gan_Rot3D gan_rot3D_mult_s ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
GANDALF_API Gan_Bool  gan_rot3D_multI_q ( Gan_Rot3D *rot1, Gan_Rot3D *rot2,
                              Gan_Rot3D *rot3 );
GANDALF_API Gan_Rot3D gan_rot3D_multI_s ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
GANDALF_API Gan_Bool  gan_rot3D_scale_q ( Gan_Rot3D *rot_s, double scale,
                              Gan_Rot3D *rot_d );
GANDALF_API Gan_Rot3D gan_rot3D_scale_s ( Gan_Rot3D *rot_s, double scale );
GANDALF_API Gan_Bool  gan_rot3D_divide_q ( Gan_Rot3D *rot_s, double scale,
                              Gan_Rot3D *rot_d );
GANDALF_API Gan_Rot3D gan_rot3D_divide_s ( Gan_Rot3D *rot_s, double scale );
GANDALF_API Gan_Bool  gan_rot3D_add_q ( Gan_Rot3D *rot1, Gan_Rot3D *rot2, Gan_Rot3D *rot3);
GANDALF_API Gan_Rot3D gan_rot3D_add_s ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
GANDALF_API Gan_Bool  gan_rot3D_sub_q ( Gan_Rot3D *rot1, Gan_Rot3D *rot2, Gan_Rot3D *rot3);
GANDALF_API Gan_Rot3D gan_rot3D_sub_s ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
GANDALF_API Gan_Bool  gan_rot3D_convert_q ( Gan_Rot3D *rot_s, Gan_Rot3D_Type type,
                                Gan_Rot3D *rot_d );
GANDALF_API Gan_Rot3D gan_rot3D_convert_s ( Gan_Rot3D *rot_s, Gan_Rot3D_Type type );
GANDALF_API Gan_Bool  gan_rot3D_from_quaternion_q ( Gan_Rot3D *rot,
                                      Gan_Quaternion *q, Gan_Rot3D_Type type );
GANDALF_API Gan_Bool  gan_rot3D_from_exponential_q ( Gan_Rot3D *rot,
                                         Gan_Vector3 *r, Gan_Rot3D_Type type );
GANDALF_API Gan_Rot3D gan_rot3D_from_quaternion_s ( Gan_Quaternion *q,
                                        Gan_Rot3D_Type type );
GANDALF_API Gan_Rot3D gan_rot3D_from_exponential_s ( Gan_Vector3 *r, Gan_Rot3D_Type type );
GANDALF_API Gan_Bool  gan_rot3D_from_angle_axis_q ( Gan_Rot3D *rot,
                                        double angle, Gan_Vector3 *axis,
                                        Gan_Rot3D_Type type );
GANDALF_API Gan_Rot3D gan_rot3D_from_angle_axis_s ( double angle, Gan_Vector3 *axis,
                                        Gan_Rot3D_Type type );
GANDALF_API Gan_Bool  gan_rot3D_from_matrix_q ( Gan_Rot3D *rot,
                                    Gan_Matrix33 *R, Gan_Rot3D_Type type );
GANDALF_API Gan_Rot3D gan_rot3D_from_matrix_s ( Gan_Matrix33 *R, Gan_Rot3D_Type type );
GANDALF_API Gan_Bool  gan_rot3D_matrix_adjust ( Gan_Matrix33 *R );

/**
 * \brief Macro: Scale rotation parameters in-place.
 *
 * Implemented as a macro call to gan_rot3D_scale_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_rot3D_scale_i ( Gan_Rot3D *rot, double s );
#else
#define gan_rot3D_scale_i(r,s)         gan_rot3D_scale_q(r,s,r)
#endif

/**
 * \brief Macro: Divide rotation parameters by a scalar in-place.
 *
 * Implemented as a macro call to gan_rot3D_scale_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_rot3D_divide_i ( Gan_Rot3D *rot, double s );
#else
#define gan_rot3D_divide_i(r,s)        gan_rot3D_divide_q(r,s,r)
#endif

/**
 * \brief Macro: Add two sets of rotation parameters.
 *
 * Overwrites \a rot1 with the result.
 * Implemented as a macro call to gan_rot3D_add_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_rot3D_increment ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
#else
#define gan_rot3D_increment(r1,r2) gan_rot3D_add_q(r1,r2,r1)
#endif

/**
 * \brief Macro: Add two sets of rotation parameters.
 *
 * Overwrites \a rot2 with the result.
 * Implemented as a macro call to gan_rot3D_add_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_rot3D_add_i2 ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
#else
#define gan_rot3D_add_i2(r1,r2)    gan_rot3D_add_q(r1,r2,r2)
#endif

/**
 * \brief Macro: Subtract two sets of rotation parameters.
 *
 * Overwrites \a rot1 with the result.
 * Implemented as a macro call to gan_rot3D_add_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_rot3D_decrement ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
#else
#define gan_rot3D_decrement(r1,r2) gan_rot3D_sub_q(r1,r2,r1)
#endif

/**
 * \brief Macro: Subtract two sets of rotation parameters.
 *
 * Overwrites \a rot2 with the result.
 * Implemented as a macro call to gan_rot3D_sub_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_rot3D_sub_i2 ( Gan_Rot3D *rot1, Gan_Rot3D *rot2 );
#else
#define gan_rot3D_sub_i2(r1,r2)    gan_rot3D_sub_q(r1,r2,r2)
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

#endif /* #ifndef _GAN_ROTATE3D_H */
