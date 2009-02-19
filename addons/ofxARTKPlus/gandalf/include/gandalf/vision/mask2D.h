/**
 * File:          $RCSfile: mask2D.h,v $
 * Module:        Constructing 2D Gaussian convolution masks
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.2 $
 * Last edited:   $Date: 2005/02/20 04:12:45 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2004 <a href="http://frav.escet.urjc.es">FRAV (Face Recognition & Artificial Vision Group)</a>
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

#ifndef _GAN_MASK2D_H
#define _GAN_MASK2D_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg.h>
#include <gandalf/image.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Vision
 * \{
 */

/**
 * \addtogroup Convolution
 * \{
 */

/**
 * \brief Format of 2D convolution mask.
 *
 * Format of 2D convolution mask, whose height \c h \c and width \c w \c 
 * have to be odd.
 *
 * For GAN_MASK2D_SYMMETRIC, only \f$ ((h-1)/2+1)((w-1)/2+1) \f$ elements, 
 * belonging to the upper left quadrant, need to be 
 * specified by the user. The other quadrants are symmetric.
 *
 * For GAN_MASK2D_ANTISYMMETRIC, only \f$ (h-1)(w-1)/4 \f$ elements, 
 * belonging to the upper left quadrant and excluding those located in the
 * central axis of the mask, have to be defined. The upper right and the 
 * lower left quadrants are antisymmetric (multiplied by -1) and the lower
 * right quadrant is symmetric. The pixels located in the central axis
 * are equal to zero.
 */
typedef enum
{
   GAN_MASK2D_SYMMETRIC,     /**< Symmetric 2D convolution mask */
   GAN_MASK2D_ANTISYMMETRIC, /**< Antisymmetric 2D convolution mask */
   GAN_MASK2D_GENERIC        /**< General 2D convolution mask */
} Gan_Mask2DFormat;

/**
 * \brief 2D convolution mask.
 */
typedef struct
{
   /// format of convolution mask
   Gan_Mask2DFormat format;

   /// Number of rows (must be odd)
   unsigned int rows;

   /// Number of columns (must be odd)
   unsigned int cols;

   /// allocated size of mask
   unsigned int size_alloc;

   /// mask data
   Gan_Matrix *data;

   /// whether the mask data was dynamically allocated
   Gan_Bool data_alloc;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_Mask2D;

/* create new mask */

/**
 * \brief Form a new 2D convolution mask.
 * \param mask The 2D convolution mask.
 * \param format The format of the convolution mask.
 * \param data A 2D matrix that defines the values of the mask.
 * \param rows The number of rows of the mask (height).
 * \param cols The number of columns of the mask (width).
 *
 * Don't call this function directly. Use the macro gan_mask1D_form_data()
 * instead.
 */
Gan_Mask2D *gan_mask2D_form_gen ( Gan_Mask2D *mask,
                                  Gan_Mask2DFormat format, 
                                  Gan_Matrix *data, 
                                  unsigned int rows,
                                  unsigned int cols);


/**
 * \brief Copies a convolution mask.
 * \param source The input convolution mask
 * \param dest The output convolution mask
 *
 * Copy 2D convolution mask from source mask to dest mask
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
Gan_Bool    gan_mask2D_copy_q ( Gan_Mask2D *source, Gan_Mask2D *dest );


/**
 * \brief Frees a convolution mask.
 * \param mask The convolution mask to be freed
 *
 * Free memory associated with 2D convolution mask.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
Gan_Bool    gan_mask2D_free ( Gan_Mask2D *mask );

/**
 * \brief Generates a 2D convolution mask from a grey-level image.
 * \param img The image.
 *
 * Generates a 2D convolution mask from a grey-level image.
 * \return A 2D convolution mask identical to the image.
 */
Gan_Mask2D* gan_mask2D_gen_from_Gan_Image (Gan_Image *img);

/**
 * \brief Macro: Allocate and return a new 2D convolution mask.
 *
 * Allocates and returns a new 2D convolution mask with the given \a format
 * and \a size.
 *
 * Implemented as a macro call to gan_mask2D_form_gen().
 * \sa gan_mask2D_form() and gan_mask2D_alloc_data().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
Gan_Mask2D *gan_mask2D_alloc ( Gan_Mask2DFormat format, 
                               unsigned int rows,
			       unsigned int cols);
#else
#define gan_mask2D_alloc(f,r,c) gan_mask2D_form_gen(NULL,f,NULL,r,c)
#endif

/**
 * \brief Macro: Allocate and return a new 2D convolution mask.
 *
 * Allocates and returns a new 2D convolution mask with the given \a format,
 * \a type, \a data array and \a size.
 *
 * Implemented as a macro call to gan_mask2D_form_gen().
 * \sa gan_mask2D_form() and gan_mask2D_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
Gan_Mask2D *gan_mask2D_alloc_data ( Gan_Mask2DFormat format, 
                                    Gan_Matrix *data, unsigned int rows,
				    unsigned int cols );
#else
#define gan_mask2D_alloc_data(f,d,r,c) gan_mask2D_form_gen(NULL,f,d,r,c)
#endif

/**
 * \brief Macro: Build a new 2D convolution mask.
 *
 * Builds and returns a new 2D convolution mask with the given \a format,
 * \a type and \a size, writing it into the provided structure \a mask.
 *
 * Implemented as a macro call to gan_mask2D_form_gen().
 * \sa gan_mask2D_alloc() and gan_mask2D_alloc_data().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
Gan_Mask2D *gan_mask2D_form ( Gan_Mask2D *mask,
                              Gan_Mask2DFormat format, 
                              unsigned int rows,
			      unsigned int cols);
#else
#define gan_mask2D_form(m,f,r,c) gan_mask2D_form_gen(m,f,NULL,r,c)
#endif

/**
 * \brief Macro: Build a new 2D convolution mask.
 *
 * Builds and returns a new 2D convolution mask with the given \a format,
 * \a type, \a data and \a size, writing it into the provided structure
 * \a mask.
 *
 * Implemented as a macro call to gan_mask2D_form_gen().
 * \sa gan_mask1D_alloc() and gan_mask2D_alloc_data().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
Gan_Mask2D *gan_mask2D_form_data ( Gan_Mask2D *mask,
                                   Gan_Mask2DFormat format, 
                                   Gan_Matrix *data, unsigned int rows,
				   unsigned int cols);
#else
#define gan_mask2D_form_data(mask,format,data,rows,cols)\
           gan_mask2D_form_gen(mask,format,data,rows,cols)
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

#endif /* #ifndef _GAN_MASK2D_H */
