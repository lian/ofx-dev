/**
 * File:          $RCSfile: cameraf.h,v $
 * Module:        Camera definitions and building functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.27 $
 * Last edited:   $Date: 2006/03/15 16:18:23 $
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

#ifndef _GAN_CAMERAF_H
#define _GAN_CAMERAF_H

#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/vision/camera_defs.h>
#include <gandalf/linalg/3x3matrixf.h>
#include <gandalf/linalg/2x3matrixf.h>
#include <gandalf/linalg/3vectorf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup Camera
 * \{
 */

/**
 * \brief Structure containing any previous project/backproject result
 */
typedef struct Gan_PositionState_f
{
   Gan_Bool initialised;
   Gan_Vector3_f pin, pout;
} Gan_PositionState_f;

/**
 * Warped positions and derivatives, to aid backprojection
 */
typedef struct Gan_CubicBSplineSupportF
{
   Gan_Vector2_f warped_pos[1 + (1 << GAN_CUBIC_BSPLINE_CAMERA_LEVEL)][1 + (1 << GAN_CUBIC_BSPLINE_CAMERA_LEVEL)];
   Gan_Matrix22_f warped_deriv[1 + (1 << GAN_CUBIC_BSPLINE_CAMERA_LEVEL)][1 + (1 << GAN_CUBIC_BSPLINE_CAMERA_LEVEL)];
} Gan_CubicBSplineSupportF;

typedef Gan_Vector2_f Gan_CubicBSplineWeightBlockF[1 + (1<<GAN_CUBIC_BSPLINE_CAMERA_LEVEL)];

/**
 * Cubic B-spline weight structure.
 */
typedef struct Gan_CubicBSplineWeightsF
{
   Gan_Vector2_f weight[1 + (1 << GAN_CUBIC_BSPLINE_CAMERA_LEVEL)][1 + (1 << GAN_CUBIC_BSPLINE_CAMERA_LEVEL)];
} Gan_CubicBSplineWeightsF;
         
/**
 * \brief Structure containing camera parameters in single precision.
 */
typedef struct Gan_Camera_f
{
   /// Type of camera
   Gan_CameraType type;

   /// parameters of linear camera

   /// focal distance in x/y pixels
   float fx, fy, fy_over_fx;

   /// image centre x/y coordinates
   float x0, y0;

   /// third homogeneous image coordinate
   float zh;

   /**
    * \brief Supplementary parameters for non-linear camera models.
    *
    * The thresholds are the square \f$ R^2 \f$ of the undistorted radial
    * camera coordinate \f$ R \f$ where the first reversal of distortion occurs
    * (\a thres_R2), and the similar threshold on the distorted radial
    * distance \f$ d\:R \f$, involving both the distortion coefficient
    * \f$ d \f$  and \f$ R \f$ (thres_dR), at the same reversal point.
    * Both thresholds are set to \c FLT_MAX if there is no reversal.
    */
   union
   {
      struct
      {
         /// skew parameters
         float skew, kyx;

         /// inverse camera matrix
         Gan_Matrix23_f Kinv;
      } affine;

      struct
      {
         /// Distortion coefficients
         float K1;

         /// Thresholds on \f$ R^2 \f$ and \f$ d\:R \f$
         float thres_R2, thres_dR;

         /// Outer linear model parameters
         float outer_a, outer_b;
      } radial1;

      struct
      {
         /// Distortion coefficients
         float K1, K2;

         /// Thresholds on \f$ R^2 \f$ and \f$ d\:R \f$
         float thres_R2, thres_dR;

         /// Outer linear model parameters
         float outer_a, outer_b;
      } radial2;

      struct
      {
         /// Distortion coefficients
         float K1, K2, K3;

         /// Thresholds on \f$ R^2 \f$ and \f$ d\:R \f$
         float thres_R2, thres_dR;

         /// Outer linear model parameters
         float outer_a, outer_b;
      } radial3;

      struct { float cxx, cxy, cyx, cyy; } xydist4;

      struct
      {
         float xla, xlp, xha, xhp;
         float yla, ylp, yha, yhp;
         float axx, axy, ayx, ayy;
      } fcwarp;

      struct
      {
         /// skew and lower triangle components store in a scale-independent manner
         float skew, kyx, kzx, kzy;

         /// non-triangular camera matrix and its inverse
         Gan_Matrix33_f K, Kinv;

         /// Cubic B-spline parameters
         Gan_CubicBSplineWeightBlockF *weight;

         /// Support for back-projection
         Gan_CubicBSplineSupportF* support;
      } cbspline;
   } nonlinear;

   /// point functions
   struct
   {
      /// point projection function
      Gan_Bool (*project) ( const struct Gan_Camera_f *camera,
                            Gan_Vector3_f *X, Gan_Vector3_f *p, Gan_PositionState_f *Xpprev,
                            Gan_Matrix22_f *HX, struct Gan_Camera_f *HC,
                            int *error_code );

      /// point back-projection function
      Gan_Bool (*backproject) ( const struct Gan_Camera_f *camera,
                                Gan_Vector3_f *p, Gan_Vector3_f *X, Gan_PositionState_f *pXprev,
                                int *error_code );

      /// function to add distortion to a point
      Gan_Bool (*add_distortion) ( const struct Gan_Camera_f *camera,
                                   Gan_Vector3_f *pu, Gan_Vector3_f *p, Gan_PositionState_f *pupprev,
                                   int *error_code );

      /// function to remove distortion from a point
      Gan_Bool (*remove_distortion) ( const struct Gan_Camera_f *camera,
                                      Gan_Vector3_f *p, Gan_Vector3_f *pu, Gan_PositionState_f *ppuprev,
                                      int *error_code);
   } pointf;

   /// line functions
   struct
   {
      /// line projection function
      Gan_Bool (*project) ( const struct Gan_Camera_f *camera,
                            Gan_Vector3_f *L, Gan_Vector3_f *l );

      /// line back-projection function
      Gan_Bool (*backproject) ( const struct Gan_Camera_f *camera,
                                Gan_Vector3_f *l, Gan_Vector3_f *L );
   } linef;
} Gan_Camera_f;

GANDALF_API Gan_Bool gan_cameraf_build_va ( Gan_Camera_f *camera, Gan_CameraType type,
                                float zh,
                                float fx, float fy, float x0, float y0,
                                ... );
GANDALF_API Gan_Bool gan_cameraf_internalize ( Gan_Camera_f *camera );
GANDALF_API Gan_Bool gan_cameraf_identical ( const Gan_Camera_f *camera1, const Gan_Camera_f *pcamera2 );
GANDALF_API Gan_SquMatrix33_f gan_cameraf_fill_matrix_s ( const Gan_Camera_f *camera );
GANDALF_API Gan_Matrix33_f    gan_cameraf_fill_fullmatrix_s ( const Gan_Camera_f *camera );

GANDALF_API Gan_Bool gan_cameraf_set_common_fields ( Gan_Camera_f *camera,
                                         Gan_CameraType type,
                                         float zh, float fx, float fy,
                                         float x0, float y0 );

/**
 * \brief Macro: Projects a point from the scene onto the image.
 * \param camera Pointer to the camera structure
 * \param X Pointer to the 3D scene point in camera-centred coordinates
 * \param p Pointer to the output homogeneous image coordinate vector
 * \param Xpprev Pointer to previous input/output position or \c NULL
 * \param HX Jacobian of image coordinates w.r.t camera coordinates or \c NULL
 * \param HC Jacobian of image coordinates w.r.t camera parameters or \c NULL
 * \param error_code Pointer to error code or \c NULL
 *
 * Given a 3D point \a X in camera coordinates (X/Y axes parallel to image x/y
 * coordinates but in opposite directions, Z axis out into the world along the
 * optic axis, origin at optical centre), projects \a X onto the image
 * according to the parameters of the given camera.
 *
 * This function also computes the Jacobians of the projection w.r.t. the x & y
 * coordinates of the camera coordinates X and the camera parameters in the
 * matrix \a HX and the array \a HC, which may be passed as \c NULL if the
 * Jacobians are not required.
 *
 * \return #GAN_TRUE on successfully computing image coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_project_point_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_project_point_gen ( const Gan_Camera_f *camera,
                                 Gan_Vector3_f *X, Gan_Vector3_f *p, Gan_PositionState_f *Xpprev,
                                 Gan_Matrix22_f *HX, Gan_Camera_f HC[2],
                                 int *error_code );
#else
#define gan_cameraf_project_point_gen(camera,X,p,Xpprev,HX,HC,ec)\
           ((camera)->pointf.project(camera,X,p,Xpprev,HX,HC,ec))
#endif

/**
 * \brief Macro: Projects a point from the scene onto the image.
 * \param camera Pointer to the camera structure
 * \param X Pointer to the 3D scene point in camera-centred coordinates
 * \param p Pointer to the output homogeneous image coordinate vector
 * \param error_code Pointer to error code or \c NULL
 *
 * Given a 3D point \a X in camera coordinates (X/Y axes parallel to image x/y
 * coordinates but in opposite directions, Z axis out into the world along the
 * optic axis, origin at optical centre), projects \a X onto the image
 * according to the parameters of the given camera.
 *
 * \return #GAN_TRUE on successfully computing image coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_project_point_gen().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_project_point ( const Gan_Camera_f *camera,
                             Gan_Vector3_f *X, Gan_Vector3_f *p,
                             int *error_code );
#else
#define gan_cameraf_project_point(camera,X,p,ec)\
           gan_cameraf_project_point_gen(camera,X,p,NULL,NULL,NULL,ec)
#endif

/**
 * \brief Macro: Projects a point from the scene onto the image.
 * \param camera Pointer to the camera structure
 * \param X Pointer to the 3D scene point in camera-centred coordinates
 * \param p Pointer to the output homogeneous image coordinate vector
 *
 * Given a 3D point \a X in camera coordinates (X/Y axes parallel to image x/y
 * coordinates but in opposite directions, Z axis out into the world along the
 * optic axis, origin at optical centre), projects \a X onto the image
 * according to the parameters of the given camera.
 *
 * Implemented as a macro call to gan_cameraf_project_point_gen().
 *
 * \return #GAN_TRUE on successfully computing image coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_project_line_q(), gan_cameraf_backproject_point_q()
 *     gan_cameraf_project_point_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_project_point_q ( const Gan_Camera_f *camera,
                               Gan_Vector3_f *X, Gan_Vector3_f *p );
#else
#define gan_cameraf_project_point_q(camera,X,p)\
           gan_cameraf_project_point(camera,X,p,NULL)
#endif

/**
 * \brief Macro: Projects a point from the scene onto the image.
 * \param camera Pointer to the camera structure
 * \param X Pointer to the 3D scene/image point (input/output)
 *
 * Given a 3D point \a X in camera coordinates (X/Y axes parallel to image x/y
 * coordinates but in opposite directions, Z axis out into the world along the
 * optic axis, origin at optical centre), projects \a X onto the image
 * according to the parameters of the given camera. The operation is performed
 * in-place in the vector \a X.
 *
 * This is a macro call to gan_cameraf_project_point_q().
 *
 * \return #GAN_TRUE on successfully computing image coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_project_point_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_project_point_i ( const Gan_Camera_f *camera, Gan_Vector3_f *X );
#else
#define gan_cameraf_project_point_i(camera,X)\
           gan_cameraf_project_point_q(camera,X,X)
#endif

/**
 * \brief Macro: Back-projects an image point into the scene.
 * \param camera Pointer to the camera structure
 * \param p Pointer to homogeneous image coordinates of the point
 * \param X Pointer to the output 3D point camera-centred coordinates
 * \param pXprev Pointer to previous input/output position or \c NULL
 * \param error_code Pointer to error code or \c NULL
 *
 * Given the homogeneous coordinates of an image point \a p, back-projects the
 * point into the scene, so that the output point \a X is in camera-centred 3D
 * coordinates, defined such that the scene X/Y axes are parallel to the image
 * x/y coordinates but in opposite directions, the Z axis points out into the
 * world along the optic axis, and the origin is at the optical centre.
 * The backprojected point is chosen to lie on the plane Z=1.
 *
 * \return #GAN_TRUE on successfully computing scene coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_backproject_line_q(), gan_cameraf_project_point_q()
 *     gan_cameraf_backproject_point_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_backproject_point_gen ( const Gan_Camera_f *camera,
                                     Gan_Vector3_f *p, Gan_Vector3_f *X, Gan_PositionState_f *pXprev,
                                     int *error_code );
#else
#define gan_cameraf_backproject_point_gen(camera,p,X,pXprev,ec)\
           ((camera)->pointf.backproject(camera,p,X,pXprev,ec))
#endif

/**
 * \brief Macro: Back-projects an image point into the scene.
 * \param camera Pointer to the camera structure
 * \param p Pointer to homogeneous image coordinates of the point
 * \param X Pointer to the output 3D point camera-centred coordinates
 * \param error_code Pointer to error code or \c NULL
 *
 * Given the homogeneous coordinates of an image point \a p, back-projects the
 * point into the scene, so that the output point \a X is in camera-centred 3D
 * coordinates, defined such that the scene X/Y axes are parallel to the image
 * x/y coordinates but in opposite directions, the Z axis points out into the
 * world along the optic axis, and the origin is at the optical centre.
 * The backprojected point is chosen to lie on the plane Z=1.
 *
 * \return #GAN_TRUE on successfully computing scene coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_backproject_line_q(), gan_cameraf_project_point_q()
 *     gan_cameraf_backproject_point_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_backproject_point ( const Gan_Camera_f *camera,
                                 Gan_Vector3_f *p, Gan_Vector3_f *X,
                                 int *error_code );
#else
#define gan_cameraf_backproject_point(camera,p,X,ec)\
           ((camera)->pointf.backproject(camera,p,X,NULL,ec))
#endif

/**
 * \brief Macro: Back-projects an image point into the scene.
 * \param camera Pointer to the camera structure
 * \param p Pointer to homogeneous image coordinates of the point
 * \param X Pointer to the output 3D point camera-centred coordinates
 *
 * Given the homogeneous coordinates of an image point \a p, back-projects the
 * point into the scene, so that the output point \a X is in camera-centred 3D
 * coordinates, defined such that the scene X/Y axes are parallel to the image
 * x/y coordinates but in opposite directions, the Z axis points out
 * into the world along the optic axis, and the origin is at the optical
 * centre. The backprojected point is chosen to lie on the plane Z=1.
 *
 * Implemented as a macro call to gan_cameraf_backproject_point().
 *
 * \return #GAN_TRUE on successfully computing scene coordinates of point
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_backproject_line_q(), gan_cameraf_project_point_q()
 *     gan_cameraf_backproject_point_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_backproject_point_q ( const Gan_Camera_f *camera,
                                   Gan_Vector3_f *p, Gan_Vector3_f *X );
#else
#define gan_cameraf_backproject_point_q(camera,p,X)\
           gan_cameraf_backproject_point(camera,p,X,NULL)
#endif

/**
 * \brief Macro: Back-projects an image point into the scene.
 * \param camera Pointer to the camera structure
 * \param p Homogeneous image/camera point coordinates (input/output)
 *
 * Given the homogeneous coordinates of an image point \a p, back-projects the
 * point into the scene, so that the output point is in camera-centred 3D
 * coordinates, defined such that the scene X/Y axes are parallel to the image
 * x/y coordinates but in opposite directions, the Z axis points out into the
 * world along the optic axis, and the origin is at the optical centre.
 * The backprojected point is chosen to lie on the plane Z=1. The operation is
 * performed in-place in the vector \a p.
 *
 * This is a macro call to gan_cameraf_backproject_point_q().
 *
 * \return #GAN_TRUE on successfully computing scene coordinates of point,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_backproject_point_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_backproject_point_i ( const Gan_Camera_f *camera,
                                   Gan_Vector3_f *p );
#else
#define gan_cameraf_backproject_point_i(camera,p)\
           gan_cameraf_backproject_point_q(camera,p,p)
#endif

/**
 * \brief Macro: Applies non-linear distortion to an image point.
 * \param camera Pointer to the camera structure
 * \param pu Pointer to the image point coordinates without distortion
 * \param p Pointer to the output distorted image point coordinates
 * \param pupprev Pointer to previous input/output position or \c NULL
 * \param error_code Pointer to error code or \c NULL
 *
 * Given a homogeneous 2D image point \a pu assumed to be the linear projection
 * of a scene point (i.e. having no non-linear distortion), adds distortion to
 * the coordinates, writing the result into the pointer \a p.
 * The camera parameters are read from the given camera.
 *
 * \return #GAN_TRUE on successfully applying the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_remove_distortion_gen().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_add_distortion_gen ( const Gan_Camera_f *camera,
                                 Gan_Vector3_f *pu, Gan_Vector3_f *p, Gan_PositionState_f *pupprev,
                                 int *error_code );
#else
#define gan_cameraf_add_distortion_gen(camera,pu,p,pupprev,ec)\
           ((camera)->pointf.add_distortion(camera,pu,p,pupprev,ec))
#endif

/**
 * \brief Macro: Applies non-linear distortion to an image point.
 * \param camera Pointer to the camera structure
 * \param pu Pointer to the image point coordinates without distortion
 * \param p Pointer to the output distorted image point coordinates
 * \param error_code Pointer to error code or \c NULL
 *
 * Given a homogeneous 2D image point \a pu assumed to be the linear projection
 * of a scene point (i.e. having no non-linear distortion), adds distortion to
 * the coordinates, writing the result into the pointer \a p.
 * The camera parameters are read from the given camera.
 *
 * \return #GAN_TRUE on successfully applying the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_remove_distortion().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_add_distortion ( const Gan_Camera_f *camera,
                              Gan_Vector3_f *pu, Gan_Vector3_f *p,
                              int *error_code );
#else
#define gan_cameraf_add_distortion(camera,pu,p,ec)\
           ((camera)->pointf.add_distortion(camera,pu,p,NULL,ec))
#endif

/**
 * \brief Macro: Applies non-linear distortion to an image point.
 * \param camera Pointer to the camera structure
 * \param pu Pointer to the image point coordinates without distortion
 * \param p Pointer to the output distorted image point coordinates
 *
 * Given a homogeneous 2D image point \a p assumed to be the linear projection
 * of a scene point (i.e. having no non-linear distortion), adds distortion to
 * the coordinates, overwriting the vector \a p with the result.
 * The camera parameters are read from the given camera.
 *
 * This is a macro call to gan_cameraf_add_distortion_q().
 *
 * \return #GAN_TRUE on successfully applying the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_add_distortion_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_add_distortion_q ( const Gan_Camera_f *camera,
                                Gan_Vector3_f *pu, Gan_Vector3_f *p );
#else
#define gan_cameraf_add_distortion_q(camera,pu,p)\
           gan_cameraf_add_distortion(camera,pu,p,NULL) 
#endif

/**
 * \brief Macro: Applies non-linear distortion to an image point.
 * \param camera Pointer to the camera structure
 * \param p Pointer to the image point coordinates (input/output)
 *
 * Given a homogeneous 2D image point \a p assumed to be the linear projection
 * of a scene point (i.e. having no non-linear distortion), adds distortion to
 * the coordinates, overwriting the vector \a p with the result.
 * The camera parameters are read from the given camera.
 *
 * This is a macro call to gan_cameraf_add_distortion_q().
 * \return #GAN_TRUE on successfully applying the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_add_distortion_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_add_distortion_i ( const Gan_Camera_f *camera, Gan_Vector3_f *p );
#else
#define gan_cameraf_add_distortion_i(camera,p)\
           gan_cameraf_add_distortion_q(camera,p,p)
#endif

/**
 * \brief Macro: Removes non-linear distortion from an image point.
 * \param camera Pointer to the camera structure
 * \param p Pointer to the distorted image point coordinates
 * \param pu Pointer to the output image point without distortion
 * \param ppuprev Pointer to previous input/output position or \c NULL
 * \param error_code Pointer to error code or \c NULL
 *
 * Given a homogeneous 2D image point \a p with non-linear distortion, removes
 * the distortion from the coordinates, writing the result into the
 * pointer \a pu. The camera parameters are read from the given camera.
 * \return #GAN_TRUE on successfully removing the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_add_distortion().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_remove_distortion_gen ( const Gan_Camera_f *camera,
                                     Gan_Vector3_f *p, Gan_Vector3_f *pu, Gan_PositionState_f *ppuprev,
                                     int *error_code );
#else
#define gan_cameraf_remove_distortion_gen(camera,p,pu,ppuprev,ec)\
           ((camera)->pointf.remove_distortion(camera,p,pu,ppuprev,ec))
#endif

/**
 * \brief Macro: Removes non-linear distortion from an image point.
 * \param camera Pointer to the camera structure
 * \param p Pointer to the distorted image point coordinates
 * \param pu Pointer to the output image point without distortion
 * \param error_code Pointer to error code or \c NULL
 *
 * Given a homogeneous 2D image point \a p with non-linear distortion, removes
 * the distortion from the coordinates, writing the result into the
 * pointer \a pu. The camera parameters are read from the given camera.
 * \return #GAN_TRUE on successfully removing the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_add_distortion().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_remove_distortion ( const Gan_Camera_f *camera,
                                 Gan_Vector3_f *p, Gan_Vector3_f *pu,
                                 int *error_code );
#else
#define gan_cameraf_remove_distortion(camera,p,pu,ec)\
           ((camera)->pointf.remove_distortion(camera,p,pu,NULL,ec))
#endif

/**
 * \brief Macro: Removes non-linear distortion from an image point.
 * \param camera Pointer to the camera structure
 * \param p Pointer to the distorted image point coordinates
 * \param pu Pointer to the output image point without distortion
 *
 * Given a homogeneous 2D image point \a p with non-linear distortion, removes
 * the distortion from the coordinates, overwriting \a p with the result.
 * The camera parameters are read from the given camera.
 *
 * This is a macro call to gan_cameraf_remove_distortion_q().
 *
 * \return #GAN_TRUE on successfully removing the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_remove_distortion_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_remove_distortion_q ( const Gan_Camera_f *camera,
                                   Gan_Vector3_f *p, Gan_Vector3_f *pu );
#else
#define gan_cameraf_remove_distortion_q(camera,p,pu)\
           gan_cameraf_remove_distortion(camera,p,pu,NULL)
#endif

/**
 * \brief Macro: Removes non-linear distortion from an image point.
 * \param camera Pointer to the camera structure
 * \param p Pointer to the image point coordinates (input/output)
 *
 * Given a homogeneous 2D image point \a p with non-linear distortion, removes
 * the distortion from the coordinates, overwriting \a p with the result.
 * The camera parameters are read from the given camera.
 *
 * This is a macro call to gan_cameraf_remove_distortion_q().
 *
 * \return #GAN_TRUE on successfully removing the distortion,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_remove_distortion_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_remove_distortion_i ( const Gan_Camera_f *camera, Gan_Vector3_f *p );
#else
#define gan_cameraf_remove_distortion_i(camera,p) \
           gan_cameraf_remove_distortion_q(camera,p,p)
#endif

/**
 * \brief Macro: Projects a line from the scene onto the image.
 * \param camera Pointer to the camera structure
 * \param L Pointer to the 3D scene line in camera-centred
 * \param l Pointer to the output homogeneous image coordinate vector
 *
 * Given a 3D line \a L in homogeneous camera coordinates so that the line
 * actually represents a plane \f$L.X=0\f$ through the optical centre,
 * projects \a L onto the image according to the parameters of the given
 * camera.
 *
 * \return #GAN_TRUE on successfully computing the image coordinates of the
 *         line, #GAN_FALSE on failure.
 * \sa gan_cameraf_project_point_q(), gan_cameraf_backproject_line_q()
 *     gan_cameraf_project_line_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_project_line_q ( const Gan_Camera_f *camera,
                              Gan_Vector3_f *L, Gan_Vector3_f *l );
#else
#define gan_cameraf_project_line_q(camera,L,l)\
           ((camera)->linef.project(camera,L,l,NULL))
#endif

/**
 * \brief Macro: Projects a line from the scene onto the image.
 * \param camera Pointer to the camera structure
 * \param L Pointer to the line coordinates (input/output)
 *
 * Given a 3D line \a L in homogeneous camera coordinates so that the line
 * actually represents a plane \f$L.X=0\f$ through the optical centre,
 * projects \a L onto the image according to the parameters of the given
 * camera. The operation is performed in-place in the vector \a L.
 *
 * This is a macro call to gan_cameraf_project_line_q().
 *
 * \return #GAN_TRUE on successfully computing image coordinates of line,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_project_line_q().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_project_line_i ( const Gan_Camera_f *camera, Gan_Vector3_f *L );
#else
#define gan_cameraf_project_line_i(camera,L)\
           gan_cameraf_project_line_q(camera,L,L)
#endif

/**
 * \brief Macro: Back-projects an image line into the scene.
 * \param camera Pointer to the camera structure
 * \param l Pointer to homogeneous image coordinates of the line
 * \param L Pointer to the output 3D line camera-centred coordinates
 *
 * Given the homogeneous coordinates of an image line \a l, back-projects the
 * line into the scene, so that the output line \a L is in camera-centred 3D
 * coordinates, defined such that the scene X/Y axes are parallel to the
 * image x/y coordinates but in opposite directions, the Z axis points out
 * into the world along the optic axis, and the origin is at the optical
 * centre. The backprojected line actually represents a plane \f$L.X=0\f$
 * through the origin (optical centre).
 *
 * \return #GAN_TRUE on successfully computing scene coordinates of line,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_backproject_point_q(), gan_cameraf_project_line_q()
 *     gan_cameraf_backproject_line_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_backproject_line_q ( const Gan_Camera_f *camera,
                                  Gan_Vector3_f *l, Gan_Vector3_f *L );
#else
#define gan_cameraf_backproject_line_q(camera,l,L)\
           ((camera)->linef.backproject(camera,l,L,NULL))
#endif

/**
 * \brief Macro: Back-projects an image line into the scene.
 * \param camera Pointer to the camera structure
 * \param l Pointer to image coordinates of the line (input/output)
 *
 * Given the homogeneous coordinates of an image line \a l, back-projects the
 * line into the scene, so that the output line is in camera-centred 3D
 * coordinates, defined such that the scene X/Y axes are parallel to the
 * image x/y coordinates but in opposite directions, the Z axis points out
 * into the world along the optic axis, and the origin is at the optical
 * centre. The backprojected line actually represents a plane through the
 * origin (optical centre).
 * The operation is performed in-place in the vector \a l.
 *
 * This is a macro call to gan_cameraf_backproject_line_q().
 *
 * \return #GAN_TRUE on successfully computing scene coordinates of line,
 *         #GAN_FALSE on failure.
 * \sa gan_cameraf_backproject_line_q(), gan_cameraf_project_line_q()
 *     gan_cameraf_backproject_line_i().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_cameraf_backproject_line_i ( const Gan_Camera_f *camera, Gan_Vector3_f *l );
#else
#define gan_cameraf_backproject_line_i(camera,l)\
           gan_cameraf_backproject_line_q(camera,l,l)
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

#endif /* #ifndef _GAN_CAMERAF_H */
