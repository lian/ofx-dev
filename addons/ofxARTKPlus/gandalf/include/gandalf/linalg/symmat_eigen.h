/**
 * File:          $RCSfile: symmat_eigen.h,v $
 * Module:        Symmetric matrix eigenvalues & eigenvectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.12 $
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

#ifndef _GAN_SYMMAT_EIGEN_H
#define _GAN_SYMMAT_EIGEN_H

#include <gandalf/linalg/vec_gen.h>
#include <gandalf/linalg/mat_gen.h>
#include <gandalf/linalg/mat_square.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup LinearAlgebra
 * \{
 */

/**
 * \addtogroup GeneralSizeMatVec
 * \{
 */

/**
 * \addtogroup GeneralSizeMatrix
 * \{
 */

/**
 * \addtogroup GeneralSizeMatrixEigen
 * \{
 */

/**
 * \brief Structure for eigendecomposition of an accumulated symmetric matrix.
 *
 * Structure to hold accumulated symmetric matrix and resulting
 * eigendecomposition of a sum of vector outer products.
 */
typedef struct
{
   Gan_SquMatrix SxxT; /**< accumulated sum of vector outer products */
   Gan_SquMatrix W;    /**< diagonal matrix of eigenvalues */
   Gan_Matrix    Z;    /**< matrix of eigenvectors */
   Gan_Vector    work; /**< workspace for computing eigendecomposition */

   Gan_Bool alloc; /**< whether this structure was dynamically allocated */
} Gan_SymMatEigenStruct;

GANDALF_API Gan_SymMatEigenStruct *gan_symeigen_form_data ( Gan_SymMatEigenStruct *sme,
                                                long max_size,
                                                double *work_data,
                                                unsigned long work_data_size );

/**
 * \brief Macro: Forms a symmetric matrix eigendecomposition structure.
 * \param sme A pointer to a structure or \c NULL
 * \param max_size The envisaged largest size of matrix
 * \return Pointer to the formed structure, or \c NULL on failure.
 *
 * Allocates/fills a structure with initial values to compute the
 * eigendecomposition of a sum of vector outer products.
 *
 * Macro call to gan_symeigen_form_data().
 *
 * \sa gan_symeigen_form_data(), gan_symeigen_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SymMatEigenStruct *gan_symeigen_form ( Gan_SymMatEigenStruct *sme,
                                           long max_size );
#else
#define gan_symeigen_form(sme,ms) gan_symeigen_form_data(sme,ms,NULL,0)
#endif

/**
 * \brief Macro: Allocates a symmetric matrix eigendecomposition structure.
 * \param max_size The envisaged largest size of matrix
 * \return Pointer to the allocated structure, or \c NULL on failure.
 *
 * Allocates a structure with initial values to compute the eigendecomposition
 * of a sum of vector outer products.
 *
 * Macro call to gan_symeigen_form_data().
 *
 * \sa gan_symeigen_form_data(), gan_symeigen_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_SymMatEigenStruct *gan_symeigen_alloc ( long max_size );
#else
#define gan_symeigen_alloc(ms) gan_symeigen_form_data(NULL,ms,NULL,0)
#endif

GANDALF_API void     gan_symeigen_free      ( Gan_SymMatEigenStruct *sme );
GANDALF_API Gan_Bool gan_symeigen_reset     ( Gan_SymMatEigenStruct *sme, long size );
GANDALF_API Gan_Bool gan_symeigen_increment ( Gan_SymMatEigenStruct *sme,
                                  double scale, ... );
GANDALF_API Gan_Bool gan_symeigen_solve     ( Gan_SymMatEigenStruct *sme );

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_SYMMAT_EIGEN_H */
