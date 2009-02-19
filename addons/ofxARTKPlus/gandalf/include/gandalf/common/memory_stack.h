/**
 * File:          $RCSfile: memory_stack.h,v $
 * Module:        Stack-style first-in first-out memory allocation module
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.2 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2002 Imagineer Software Limited
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

#ifndef _GAN_MEMORY_STACK_H
#define _GAN_MEMORY_STACK_H

#include <gandalf/common/misc_defs.h>
#include <stddef.h> /* defines size_t */

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
 * \brief Big C type for byte alignment
 */
typedef double Gan_BigType;

/**
 * \brief Structure to hold state of stack memory blocks
 */
typedef struct Gan_MemoryStack
{
   Gan_BigType **block_ptr, *last_free;
   size_t tm_bsize, tm_total;
   int current_tm_block, next_start, alloc_tm_blocks;
   int *block_end, max_tm_blocks;
   Gan_Bool squeeze_OK;

   Gan_Bool alloc; /* whether this structure was dynamically allocated */
} Gan_MemoryStack;

GANDALF_API Gan_MemoryStack *gan_memory_stack_form ( Gan_MemoryStack *ms,
                                         int nblocks, size_t bsize );
GANDALF_API void *gan_ms_malloc ( Gan_MemoryStack *ms, size_t size );
GANDALF_API void  gan_ms_free ( Gan_MemoryStack *ms, void *ptr );
GANDALF_API void  gan_ms_free_va ( Gan_MemoryStack *ms, void *ptr, ... );
GANDALF_API void  gan_memory_stack_free ( Gan_MemoryStack *ms );
GANDALF_API void  gan_memory_stack_clean ( Gan_MemoryStack *ms );
GANDALF_API size_t gan_memory_stack_total ( Gan_MemoryStack *ms );

/**
 * \brief Macro: Allocate and initialise temporary memory allocation structure.
 * \param nblocks Maximum number of blocks of memory to allow
 * \param bsize Size of each block in bytes
 * \return Pointer to new structure, or \c NULL on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_MemoryStack *gan_memory_stack_alloc ( int nblocks, size_t bsize );
#else
#define gan_memory_stack_alloc(nb,bs) gan_memory_stack_form(NULL,nb,bs)
#endif

/**
 * \brief Macro: Dynamically allocate one item of a specific type with "stack" memory.
 * \param ms Memory stack structure
 * \param obj_type The type of objects to be allocated
 * \return The allocated object, or \c NULL on failure.
 *
 * Allocation function for allocating 1 item of the given \a obj_type in
 * temporary stack-style memory. Implemented as a macro call to
 * gan_ms_malloc().
 *
 * \sa gan_ms_malloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void *gan_ms_malloc_object ( Gan_MemoryStack *ms, TYPE obj_type );
#else
#define gan_ms_malloc_object(ms,obj_type) \
        ((obj_type *) gan_ms_malloc(ms,sizeof(obj_type)))
#endif

/**
 * \brief Macro: Dynamically allocate \a n items of a specific type with "stack" memory.
 * \param ms Memory stack structure
 * \param obj_type The type of objects to be allocated
 * \param size The number of objects to allocate for in the array
 * \return The allocated array of objects, or \c NULL on failure.
 *
 * Allocation function for allocating \a size items of the given \a obj_type in
 * temporary stack-style memory.
 * Implemented as a macro call to gan_ms_malloc().
 *
 * \sa gan_ms_malloc_object(), gan_ms_malloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void *gan_ms_malloc_array ( Gan_MemoryStack *ms, TYPE obj_type, size_t size );
#else
#define gan_ms_malloc_array(ms,obj_type,size) \
        ((obj_type *) gan_ms_malloc ( ms, (size)*sizeof(obj_type) ))
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

#endif /* #ifndef _GAN_MEMORY_STACK_H */
