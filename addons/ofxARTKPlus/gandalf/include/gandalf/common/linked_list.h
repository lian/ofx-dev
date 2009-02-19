/**
 * File:          $RCSfile: linked_list.h,v $
 * Module:        Linked list
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.30 $
 * Last edited:   $Date: 2006/06/08 16:48:00 $
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

#ifndef _GAN_LINKED_LIST_H
#define _GAN_LINKED_LIST_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/common/allocate.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonList
 * \{
 */

/**
 * \brief Doubly-linked list node.
 */
typedef struct Gan_List_Node
{
   void                 *p_data;
   struct Gan_List_Node *p_next;
   struct Gan_List_Node *p_prev;
} Gan_List_Node;



/**
 * \brief Doubly-linked list type.
 */
typedef struct Gan_List
{
   
   Gan_List_Node *p_first;         /**< First node in list */
   Gan_List_Node *p_current;       /**< Current node in list */
   Gan_List_Node *p_last;          /**< Last node in list */
   Gan_List_Node *p_stack_current; /**< Node stored on the stack */
   
   int node_count;                 /**< Number of nodes in list */
   int current_position;           /**< Current position in list */
   int current_position_stack;     /**< Position stored on stack */
   Gan_Bool is_straight;           /**< Whether list is straight or circular */

   /// indicates whether the structure was dynamically allocated
   Gan_Bool alloc;
} Gan_List;


/* Constructor and Destructor */
GANDALF_API Gan_List*        gan_list_new ( void );
GANDALF_API Gan_List*        gan_list_form(Gan_List *List);
GANDALF_API Gan_List*        gan_list_new_from_array( void **array, unsigned n );
GANDALF_API void             gan_list_free ( Gan_List *List, Gan_FreeFunc free_func);
GANDALF_API Gan_Bool gan_list_insert_first ( Gan_List *List, void *data );
GANDALF_API Gan_Bool gan_list_insert_next  ( Gan_List *List, void *data );
GANDALF_API Gan_Bool gan_list_insert_prev  ( Gan_List *List, void *data );
GANDALF_API Gan_Bool gan_list_insert_last  ( Gan_List *List, void *data );
GANDALF_API Gan_Bool gan_list_insert_at ( Gan_List *List, void *data, int pos );
GANDALF_API Gan_Bool gan_list_delete_first   ( Gan_List *List, Gan_FreeFunc free_func );
GANDALF_API Gan_Bool gan_list_delete_next    ( Gan_List *List, Gan_FreeFunc free_func );
GANDALF_API Gan_Bool gan_list_delete_current ( Gan_List *List, Gan_FreeFunc free_func );
GANDALF_API Gan_Bool gan_list_delete_prev    ( Gan_List *List, Gan_FreeFunc free_func );
GANDALF_API Gan_Bool gan_list_delete_last    ( Gan_List *List, Gan_FreeFunc free_func );
GANDALF_API Gan_Bool gan_list_delete_at( Gan_List *List, Gan_FreeFunc free_func,
                             int pos );
GANDALF_API void gan_list_delete_all ( Gan_List *List, Gan_FreeFunc free_func );
GANDALF_API void gan_list_goto_head ( Gan_List *List);
GANDALF_API void gan_list_goto_tail ( Gan_List *List);
GANDALF_API Gan_Bool gan_list_goto_pos ( Gan_List *List, int pos );
GANDALF_API void *gan_list_set_prev ( Gan_List *List, void *new_data );
GANDALF_API void *gan_list_set_current (Gan_List *List, void *new_data);
GANDALF_API void *gan_list_set_next ( Gan_List *List, void *new_data );
GANDALF_API void gan_list_push_current ( Gan_List *List );
GANDALF_API void gan_list_pop_current ( Gan_List *List );
GANDALF_API int gan_list_get_pos ( Gan_List *List );
GANDALF_API int gan_list_get_size ( Gan_List *List );
GANDALF_API void gan_list_process_data( Gan_List *List,
                            void (*process_func)(void *, void *), void *data );
GANDALF_API Gan_List* gan_list_concat( Gan_List *List1, Gan_List *List2 );
GANDALF_API void gan_list_reverse( Gan_List *List );
GANDALF_API int gan_list_to_array ( Gan_List *List, void ***array_ptr );
GANDALF_API Gan_List* gan_list_copy( Gan_List *List );
GANDALF_API Gan_List* gan_list_copy_with_data( Gan_List *list, Gan_CopyFunc copy_func );
GANDALF_API void gan_list_sort_asc ( Gan_List *List,
                         int (*compare)(const void *, const void *) );
GANDALF_API void gan_list_make_straight ( Gan_List *List );
GANDALF_API void gan_list_make_circular ( Gan_List *List );
GANDALF_API Gan_Bool gan_list_is_circular ( Gan_List *List );

GANDALF_API Gan_Bool gan_list_contains ( Gan_List *List, void *data );
GANDALF_API Gan_Bool gan_list_compare( Gan_List *List1, Gan_List *List2 );

#ifdef GAN_GENERATE_DOCUMENTATION
#define TYPE int
#endif

/**
 * \brief Returns previous data pointer, decrements the current position.
 * \param list List pointer
 * \param node_type Type of object in list
 * \return Data pointer.
 *
 * Returns the data pointed to by the previous node and decrements the current
 * position such that gan_list_get_prev() can be called repeatedly in order to
 * iterate through the list. Call gan_list_goto_head() or another
 * gan_goto_...() function to set the current position in the list first. 
 * \a TYPE is the type the data returned should be cast to, e.g. \c int.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API TYPE *gan_list_get_prev ( Gan_List *list, TYPE node_type );
#else
#define gan_list_get_prev(list,TYPE) ((TYPE*) (gan_list_get_prev_node(list)))
#endif

/**
 * \brief Returns the data pointed to by the current node.
 * \param list The linked list
 * \param node_type The type of object the returned pointer points to
 * \return Data pointer.
 *
 * Returns the data pointed to by the current node. \a TYPE is the type the
 * data returned should be cast to, e.g. \c int.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API TYPE *gan_list_get_current ( Gan_List *list, TYPE node_type );
#else
#define gan_list_get_current(list,TYPE)        ((TYPE*) (gan_list_get_current_node(list)))
#endif

/**
 * \brief Macro: Returns the next data pointer, increments the current position.
 * \param list The linked list.
 * \param node_type The type of object the returned pointer points to
 * \return Data pointer.
 *
 * Returns the data pointed to by the next node and increments the current
 * position such that gan_list_get_next() can be called repeatedly in order
 * to iterate through the list. Call gan_list_goto_head() or another
 * gan_goto_...() function to set the current position in the list first.
 * \a TYPE is the type the data returned should be cast to, e.g. \c int.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API TYPE *gan_list_get_next ( Gan_List *list, TYPE node_type );
#else
#define gan_list_get_next(list,TYPE) ((TYPE*) (gan_list_get_next_node(list)))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
#undef TYPE
#endif

/* not user functions  */
GANDALF_API void *gan_list_get_prev_node ( Gan_List *List );
GANDALF_API void *gan_list_get_next_node ( Gan_List *List );
GANDALF_API void *gan_list_get_current_node ( Gan_List *List );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* _GAN_LINKED_LIST_H */
