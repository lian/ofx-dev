/**
 * File:         $RCSfile: fundamental.h,v $
 * Module:       Compute the fundamental matrix from point matches in two frames
 * Part of:      Gandalf Library
 *
 * Revision:     $Revision: 1.10 $
 * Last edited:  $Date: 2005/08/22 08:52:18 $
 * Author:       $Author: jps $
 * Copyright:    (c) 2000 Imagineer Software Limited
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

#ifndef _GAN_FUNDAMENTAL_H
#define _GAN_FUNDAMENTAL_H

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

GANDALF_API Gan_Bool gan_fundamental_matrix_fit ( Gan_Vector3 *p1, Gan_Vector3 *p2, int n,
                                      Gan_SymMatEigenStruct *sme,
                                      Gan_Matrix33 *F );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_FUNDAMENTAL_H */
