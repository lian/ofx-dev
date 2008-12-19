/**
 * File:         $RCSfile: gan_err_trace.h,v $
 * Module:       Error trace
 * Part of:      Gandalf Exception Handling
 *
 * Revision:     $Revision: 1.7 $
 * Last edited:  $Date: 2005/10/18 16:30:47 $
 * Author:       $Author: pm $
 * Copyright:    (c) 2000 Industrial Research Limited
 *
 * Short Desc:   Data structure and management functions for error trace
 * Description:  This module implements the error trace used in gan_err.[ch].
 *
 *               An error trace is a last-in first-out (LIFO) stack for
 *               temporarily holding details of multiple error events
 *               until an application is ready to read the stack.
 *
 *               The stack is usually flushed by the function in a
 *               sequence of nested calls that initially detects an
 *               error. As the call stack unwinds the successive
 *               functions also register errors, but they should not
 *               flush the error trace.
 *
 *               The stack is implemented as a linked list of error
 *               records. If in the process of allocating heap memory
 *               for a new error record a memory error occurs, then
 *               this is refered to as a deep error.
 *
 *               The stack always maintains two preallocated and unused
 *               error records for storing the details of the deep
 *               error and the error that was in the process of being
 *               registered when the deep error occured.
 *
 *               Even if the top of the stack holds a deep error record
 *               and the two preallocated records are used, new errors
 *               can still be registered into the trace. These attempts
 *               may lead to repeated deep errors, in which case the
 *               top deep error serves as an indicator of the deep
 *               continuing error state. However, if the registration
 *               process is successful (because in the intervening
 *               time, some external agent has free'd heap memory) the
 *               old deep error record is left on the stack and the new
 *               errors are registered on top of it.
 *
 *               To ensure that the stack has at least two preallocated
 *               records at process startup time, the bottom and second
 *               to bottom records of the stack use statically
 *               allocated memory. These can never be dynamically
 *               free'd.
 *
 *               To do this, an external module must define two static
 *               error records. In gan_err.c, this is implemented as:
 *
 *               Gan_ErrorTrace record_last =  {NULL, GAN_ET_YES, GAN_ET_NO,
 *                                              GAN_ET_YES, NULL,
 *                                              GAN_EC_DFT_SPARE, NULL, 0,NULL};
 *               Gan_ErrorTrace record_2nd_last =  {&record_last, GAN_ET_YES,
 *                                                  GAN_ET_NO,  GAN_ET_YES,
 *                                                  NULL,GAN_EC_DFT_SPARE,
 *                                                  NULL,0,NULL};
 *
 *               Gan_ErrorTrace * gan_et_trace_top = &record_2nd_last;
 *
 *               The symbol gan_et_trace_top refers to the current top
 *               of stack and is passed into the functions defined in
 *               this module as argument 1.
 *
 *               NB. A statically allocated string containing the deep
 *               error text message must also exist, but this is
 *               defined in gan_err_trace.c.
 *
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

#ifndef _GAN_ERR_TRACE_H
#define _GAN_ERR_TRACE_H

#include <gandalf/common/gan_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonError
 * \{
 */

/**
 * \brief Stores details of single error in an error trace.
 *
 * Error trace is a last in, first out stack of structures containing
 * details of recorded errors. The stack is implemented as a linked
 * list that is traversed by following 'prev' links.
 *
 * The bottom (oldest) and 2nd to bottom record of the error trace are
 * statically allocated, while all others are dynamically allocated
 * (malloc'd). Important that gan_et_flush doesn't try to free() the
 * statically allocated records.
 *
 * \param prev Address of previous (next oldest) record in error trace
 *             Prev for last record is NULL.
 * \param f_static_record Is this record statically or dynamically allocated
 *        If it's static, don't try and free() it. 
 * \param f_static_message Is the text message in this record is contained in a
 *        statically or dynamically allocated char array.
 *        If it's static, don't try and free() it.
 * \param f_spare Whether is record contains details for an error, or is
 *                spare.
 * \param func_name       Name of function in which error occurs
 * \param err_code        Numeric code of error. Default set is defined
 *                        in gan_exception_codes*.h 
 * \param file_name       Name of file in which error occurs 
 * \param line_number     Line in file at which error occurs
 * \param message         Message string describing error
 * \param number          Number attached to error
 *
 * A record has the status "spare" and "not spare". A spare record is
 * always kept in advance so that a deep error can be registered in a
 * memory shortage situation. A record is designated spare when it
 * carries and error code of EC_DFT_SPARE.
 *
 * The text message pointed to by "message" normally resides in a
 * dynamically allocated char array, except for the deep error message
 * which resides in a static char array. Therefore if the error code
 * is EC_DFT_DEEP_ERROR, then the message char array should never be
 * subjected to \c free().
 */
typedef struct Gan_ErrorTrace
{
   struct Gan_ErrorTrace *prev;       /**< Prev => last in, first out */
   int f_static_record;               /**< ( GAN_ET_YES | GAN_ET_NO ) */
   int f_static_message;              /**< ( GAN_ET_YES | GAN_ET_NO ) */
   int f_spare;                       /**< ( GAN_ET_YES | GAN_ET_NO ) */
    
   const char *func_name;
   int         err_code;
   const char *file_name;
   int         line_number;
   char       *message;
   int         number;
} Gan_ErrorTrace;

/**
 * \brief Values for the 'f_spare' and 'f_static_message' in the
 *        #Gan_ErrorTrace structure.
 */
#define GAN_ET_YES  0
#define GAN_ET_NO   1

GANDALF_API Gan_ErrorTrace *gan_et_push ( Gan_ErrorTrace *et_top,
                                          const char *func_name,
                                          int         err_code,
                                          const char *file_name,
                                          int         line_number,
                                          const char *message,
                                          int         number );
GANDALF_API int gan_et_get_record_count ( Gan_ErrorTrace *et_record );
GANDALF_API Gan_ErrorTrace *gan_et_get_record_next ( Gan_ErrorTrace *et_record );
GANDALF_API Gan_ErrorTrace *gan_et_get_record_first ( Gan_ErrorTrace *et_record );
GANDALF_API Gan_ErrorTrace *gan_et_flush_trace( Gan_ErrorTrace *et_record );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_ERR_TRACE_H */
