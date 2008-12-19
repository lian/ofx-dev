/**
 * File:          $RCSfile: allocate.h,v $
 * Module:        Memory allocation module
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.16 $
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

#ifndef _GAN_ALLOCATE_H
#define _GAN_ALLOCATE_H

#include <stdlib.h>
#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonAllocate
 * \{
 */

/**
 * \brief Generic free function type.
 */
typedef void (*Gan_FreeFunc) (void *);

/**
 * \brief Generic copy function type.
 */
typedef void * (*Gan_CopyFunc) (void *);

#ifdef GAN_GENERATE_DOCUMENTATION
#define obj_type int x
#endif

/**
 * \brief Macro: Allocate an object of a specific type using \c malloc().
 * \param obj_type The type of object to be allocated
 * \return Pointer to the allocated object, or \c NULL on failure.
 *
 * Invokes \c malloc() to dynamically allocate an object of a specific type.
 *
 * \sa gan_malloc_array().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void *gan_malloc_object ( TYPE obj_type );
#else
#define gan_malloc_object(obj_type) ((obj_type *) malloc(sizeof(obj_type)))
#endif

/**
 * \brief Macro: Allocate an array of objects of a specific type using \c malloc().
 * \param obj_type The type of objects to be allocated
 * \param size The number of objects to allocate for in the array
 * \return The allocated array of objects, or \c NULL on failure.
 *
 * Invokes \c malloc() to dynamically allocate an array of objects of a
 * specific type.
 *
 * \sa gan_malloc_object(), gan_realloc_array().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void *gan_malloc_array ( TYPE obj_type, unsigned size );
#else
#define gan_malloc_array(obj_type,size) \
           ((obj_type *)malloc((size)*sizeof(obj_type)))
#endif

/**
 * \brief Macro: Reallocate an array of objects using \c realloc().
 * \param obj_type The type of objects to be allocated
 * \param ptr The existing array to be reallocated or NULL
 * \param size The number of objects to allocate for in the array
 * \return The reallocated array of objects, or \c NULL on failure.
 *
 * Invokes \c realloc() to dynamically reallocate an array of objects of a
 * specific type. If \a ptr is passed as \c NULL then it is equivalent to
 * calling gan_malloc_array().
 *
 * \sa gan_malloc_array().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void *gan_realloc_array ( TYPE obj_type, void *ptr, unsigned size );
#else
#define gan_realloc_array(type,ptr,n) \
           ((type *)realloc((void *)ptr,(n)*sizeof(type)))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
#undef obj_type
#endif

GANDALF_API void gan_free_va ( void *ptr, ... );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_ALLOCATE_H */
