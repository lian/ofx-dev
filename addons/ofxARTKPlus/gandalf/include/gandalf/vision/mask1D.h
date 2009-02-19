/**
 * File:          $RCSfile: mask1D.h,v $
 * Module:        Constructing 1D Gaussian convolution masks
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

#ifndef _GAN_MASK1D_H
#define _GAN_MASK1D_H

#include <gandalf/common/misc_defs.h>

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
 * \brief Format of convolution mask.
 */
typedef enum
{
   GAN_MASK1D_SYMMETRIC,     /**< Symmetric 1D convolution mask */
   GAN_MASK1D_ANTISYMMETRIC, /**< Antisymmetric 1D convolution mask */
   GAN_MASK1D_GENERIC        /**< General 1D convolution mask */
} Gan_Mask1DFormat;

/**
 * \brief Edge behaviour
 */
typedef enum
{
   GAN_EDGE_BEHAVIOUR_CLIP,     /**< Don't access data outside edge */
   GAN_EDGE_BEHAVIOUR_REPEAT,   /**< Repeat data outside edge */
   GAN_EDGE_BEHAVIOUR_CIRCULAR, /**< Treat data as circular */
   GAN_EDGE_BEHAVIOUR_EXPAND    /**< Expand data by mask size */
} Gan_EdgeBehaviour;

/**
 * \brief 1D convolution mask.
 */
typedef struct
{
   /// format of convolution mask
   Gan_Mask1DFormat format;

   /// type of mask
   Gan_Type type;

   /// size of mask (must be odd)
   unsigned int size;

   /// allocated size of mask
   unsigned int size_alloc;

   /// mask data
   union
   {
      float  *f;
      double *d;
      int    *i;
      unsigned short *us;
      unsigned char *uc;

   } data;

   /// whether the mask data was dynamically allocated
   Gan_Bool data_alloc;

   /// whether this structure was dynamically allocated
   Gan_Bool alloc;
} Gan_Mask1D;

/* create new mask */
GANDALF_API Gan_Mask1D *gan_mask1D_form_gen ( Gan_Mask1D *mask,
                                  Gan_Mask1DFormat format, Gan_Type type,
                                  void *data, unsigned int size );
GANDALF_API Gan_Bool    gan_mask1D_copy_q ( Gan_Mask1D *source, Gan_Mask1D *dest );
GANDALF_API Gan_Bool    gan_mask1D_free ( Gan_Mask1D *mask );

GANDALF_API Gan_Mask1D *gan_gauss_mask_new ( Gan_Type type, double sigma,
                                 unsigned mask_size, double scale,
                                 void    *mask_data );

/**
 * \brief Macro: Allocate and return a new 1D convolution mask.
 *
 * Allocates and returns a new 1D convolution mask with the given \a format,
 * \a type and \a size.
 *
 * Implemented as a macro call to gan_mask1D_form_gen().
 * \sa gan_mask1D_form() and gan_mask1D_alloc_data().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Mask1D *gan_mask1D_alloc ( Gan_Mask1DFormat format, Gan_Type type,
                               unsigned int size );
#else
#define gan_mask1D_alloc(f,t,s) gan_mask1D_form_gen(NULL,f,t,NULL,s)
#endif

/**
 * \brief Macro: Allocate and return a new 1D convolution mask.
 *
 * Allocates and returns a new 1D convolution mask with the given \a format,
 * \a type, \a data array and \a size.
 *
 * Implemented as a macro call to gan_mask1D_form_gen().
 * \sa gan_mask1D_form() and gan_mask1D_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Mask1D *gan_mask1D_alloc_data ( Gan_Mask1DFormat format, Gan_Type type,
                                    void *data, unsigned int size );
#else
#define gan_mask1D_alloc_data(f,t,d,s) gan_mask1D_form_gen(NULL,f,t,d,s)
#endif

/**
 * \brief Macro: Build a new 1D convolution mask.
 *
 * Builds and returns a new 1D convolution mask with the given \a format,
 * \a type and \a size, writing it into the provided structure \a mask.
 *
 * Implemented as a macro call to gan_mask1D_form_gen().
 * \sa gan_mask1D_alloc() and gan_mask1D_alloc_data().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Mask1D *gan_mask1D_form ( Gan_Mask1D *mask,
                              Gan_Mask1DFormat format, Gan_Type type,
                              unsigned int size );
#else
#define gan_mask1D_form(m,f,t,s) gan_mask1D_form_gen(m,f,t,NULL,s)
#endif

/**
 * \brief Macro: Build a new 1D convolution mask.
 *
 * Builds and returns a new 1D convolution mask with the given \a format,
 * \a type, \a data and \a size, writing it into the provided structure
 * \a mask.
 *
 * Implemented as a macro call to gan_mask1D_form_gen().
 * \sa gan_mask1D_alloc() and gan_mask1D_alloc_data().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Mask1D *gan_mask1D_form_data ( Gan_Mask1D *mask,
                                   Gan_Mask1DFormat format, Gan_Type type,
                                   void *data, unsigned int size );
#else
#define gan_mask1D_form_data(mask,format,type,data,size)\
           gan_mask1D_form_gen(mask,format,type,data,size)
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

#endif /* #ifndef _GAN_MASK1D_H */
