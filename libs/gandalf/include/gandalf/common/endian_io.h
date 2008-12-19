/**
 * File:          $RCSfile: endian_io.h,v $
 * Module:        Little and big-endian I/O for architecture independent I/O
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.6 $
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

#ifndef _GAN_ENDIAN_IO_H
#define _GAN_ENDIAN_IO_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonEndianIO
 * \{
 */

#ifdef GAN_INT16
GANDALF_API Gan_Bool gan_fread_lendian_i16  ( FILE *fp, gan_int16 *aui16, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_i16 ( FILE *fp, gan_int16 *aui16, size_t nitems );
GANDALF_API Gan_Bool gan_fread_lendian_ui16  ( FILE *fp, gan_uint16 *aui16, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_ui16 ( FILE *fp, gan_uint16 *aui16, size_t nitems );
#endif /* #ifdef GAN_INT16 */

#ifdef GAN_INT32
GANDALF_API Gan_Bool gan_fread_lendian_i32  ( FILE *fp, gan_int32 *aui32, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_i32 ( FILE *fp, gan_int32 *aui32, size_t nitems );
GANDALF_API Gan_Bool gan_fread_lendian_ui32  ( FILE *fp, gan_uint32 *aui32, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_ui32 ( FILE *fp, gan_uint32 *aui32, size_t nitems );
#endif /* #ifdef GAN_INT32 */

#ifdef GAN_INT64
GANDALF_API Gan_Bool gan_fread_lendian_i64  ( FILE *fp, gan_int64 *aui64, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_i64 ( FILE *fp, gan_int64 *aui64, size_t nitems );
GANDALF_API Gan_Bool gan_fread_lendian_ui64  ( FILE *fp, gan_uint64 *aui64, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_ui64 ( FILE *fp, gan_uint64 *aui64, size_t nitems );
#endif /* #ifdef GAN_INT64 */

#ifdef GAN_FLOAT32
GANDALF_API Gan_Bool gan_fread_lendian_f32  ( FILE *fp, gan_float32 *af, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_f32 ( FILE *fp, gan_float32 *af, size_t nitems );
#endif /* #ifdef GAN_FLOAT32 */

#ifdef GAN_FLOAT64
GANDALF_API Gan_Bool gan_fread_lendian_f64  ( FILE *fp, gan_float64 *af64, size_t nitems );
GANDALF_API Gan_Bool gan_fwrite_lendian_f64 ( FILE *fp, gan_float64 *af64, size_t nitems );
#endif /* #ifdef GAN_FLOAT64 */

/* macros for standard types */

/**
 * \brief Macro: Reads an array of signed short integers from a file.
 * \param fp Pointer to a binary file opened for reading
 * \param as Array of integers
 * \param nitems The number of integers to be read into the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Reads an array of signed short integers from a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fread_lendian_s  ( FILE *fp, short *as, size_t nitems );
#else
#if (SIZEOF_SHORT == 2)
#define gan_fread_lendian_s(fp,pl,ni)\
          gan_fread_lendian_i16(fp,(gan_int16 *)(pl),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Writes an array of signed short integers to a file.
 * \param fp Pointer to a binary file opened for reading
 * \param as Array of integers
 * \param nitems The number of integers to be written from the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Writes an array of signed short integers to a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fwrite_lendian_s  ( FILE *fp, short *as, size_t nitems );
#else
#if (SIZEOF_SHORT == 2)
#define gan_fwrite_lendian_s(fp,pl,ni)\
          gan_fwrite_lendian_i16(fp,(gan_int16 *)(pl),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Reads an array of unsigned short integers from a file.
 * \param fp Pointer to a binary file opened for reading
 * \param aus Array of integers
 * \param nitems The number of integers to be read into the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Reads an array of unsigned short integers from a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fread_lendian_us  ( FILE *fp, unsigned short *aus, size_t nitems );
#else
#if (SIZEOF_SHORT == 2)
#define gan_fread_lendian_us(fp,pul,ni)\
          gan_fread_lendian_ui16(fp,(gan_uint16 *)(pul),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Writes an array of unsigned short integers to a file.
 * \param fp Pointer to a binary file opened for reading
 * \param aus Array of integers
 * \param nitems The number of integers to be written from the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Writes an array of unsigned short integers to a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fwrite_lendian_us  ( FILE *fp, unsigned short *aus,
                                  size_t nitems );
#else
#if (SIZEOF_SHORT == 2)
#define gan_fwrite_lendian_us(fp,pul,ni)\
          gan_fwrite_lendian_ui16(fp,(gan_uint16 *)(pul),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Reads an array of signed integers from a file.
 * \param fp Pointer to a binary file opened for reading
 * \param ai Array of integers
 * \param nitems The number of integers to be read into the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Reads an array of signed integers from a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fread_lendian_i  ( FILE *fp, int *ai, size_t nitems );
#else
#if (SIZEOF_INT == 4)
#define gan_fread_lendian_i(fp,ai,ni)\
          gan_fread_lendian_i32(fp,(gan_int32 *)(ai),ni)
#elif (SIZEOF_INT == 8)
#define gan_fread_lendian_i(fp,ai,ni)\
          gan_fread_lendian_i64(fp,(gan_int64 *)(ai),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Writes an array of signed integers to a file.
 * \param fp Pointer to a binary file opened for reading
 * \param ai Array of integers
 * \param nitems The number of integers to be written from the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Writes an array of signed integers to a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fwrite_lendian_i  ( FILE *fp, int *ai, size_t nitems );
#else
#if (SIZEOF_INT == 4)
#define gan_fwrite_lendian_i(fp,ai,ni)\
          gan_fwrite_lendian_i32(fp,(gan_int32 *)(ai),ni)
#elif (SIZEOF_INT == 8)
#define gan_fwrite_lendian_i(fp,ai,ni)\
          gan_fwrite_lendian_i64(fp,(gan_int64 *)(ai),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Reads an array of unsigned integers from a file.
 * \param fp Pointer to a binary file opened for reading
 * \param aui Array of integers
 * \param nitems The number of integers to be read into the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Reads an array of unsigned integers from a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fread_lendian_ui  ( FILE *fp, unsigned *aui, size_t nitems );
#else
#if (SIZEOF_INT == 4)
#define gan_fread_lendian_ui(fp,pui,ni)\
          gan_fread_lendian_ui32(fp,(gan_uint32 *)(pui),ni)
#elif (SIZEOF_INT == 8)
#define gan_fread_lendian_ui(fp,pui,ni)\
          gan_fread_lendian_ui64(fp,(gan_uint64 *)(pui),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Writes an array of unsigned integers to a file.
 * \param fp Pointer to a binary file opened for reading
 * \param aui Array of integers
 * \param nitems The number of integers to be written from the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Writes an array of unsigned integers to a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fwrite_lendian_ui  ( FILE *fp, unsigned *aui, size_t nitems );
#else
#if (SIZEOF_INT == 4)
#define gan_fwrite_lendian_ui(fp,pui,ni)\
          gan_fwrite_lendian_ui32(fp,(gan_uint32 *)(pui),ni)
#elif (SIZEOF_INT == 8)
#define gan_fwrite_lendian_ui(fp,pui,ni)\
          gan_fwrite_lendian_ui64(fp,(gan_uint64 *)(pui),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Reads an array of signed long integers from a file.
 * \param fp Pointer to a binary file opened for reading
 * \param al Array of integers
 * \param nitems The number of integers to be read into the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Reads an array of signed long integers from a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fread_lendian_l  ( FILE *fp, long *al, size_t nitems );
#else
#if (SIZEOF_LONG == 4)
#define gan_fread_lendian_l(fp,pl,ni)\
          gan_fread_lendian_i32(fp,(gan_int32 *)(pl),ni)
#elif (SIZEOF_LONG == 8)
#define gan_fread_lendian_l(fp,pl,ni)\
          gan_fread_lendian_i64(fp,(gan_int64 *)(pl),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Writes an array of signed long integers to a file.
 * \param fp Pointer to a binary file opened for reading
 * \param al Array of integers
 * \param nitems The number of integers to be written from the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Writes an array of signed long integers to a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fwrite_lendian_l  ( FILE *fp, long *al, size_t nitems );
#else
#if (SIZEOF_LONG == 4)
#define gan_fwrite_lendian_l(fp,pl,ni)\
          gan_fwrite_lendian_i32(fp,(gan_int32 *)(pl),ni)
#elif (SIZEOF_LONG == 8)
#define gan_fwrite_lendian_l(fp,pl,ni)\
          gan_fwrite_lendian_i64(fp,(gan_int64 *)(pl),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Reads an array of unsigned long integers from a file.
 * \param fp Pointer to a binary file opened for reading
 * \param aul Array of integers
 * \param nitems The number of integers to be read into the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Reads an array of unsigned long integers from a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fread_lendian_ul  ( FILE *fp, unsigned long *aul, size_t nitems );
#else
#if (SIZEOF_LONG == 4)
#define gan_fread_lendian_ul(fp,pul,ni)\
          gan_fread_lendian_ui32(fp,(gan_uint32 *)(pul),ni)
#elif (SIZEOF_LONG == 8)
#define gan_fread_lendian_ul(fp,pul,ni)\
          gan_fread_lendian_ui64(fp,(gan_uint64 *)(pul),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Writes an array of unsigned long integers to a file.
 * \param fp Pointer to a binary file opened for reading
 * \param aul Array of integers
 * \param nitems The number of integers to be written from the array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Writes an array of unsigned long integers to a file.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_fwrite_lendian_ul  ( FILE *fp, unsigned long *aul,
                                  size_t nitems );
#else
#if (SIZEOF_LONG == 4)
#define gan_fwrite_lendian_ul(fp,pul,ni)\
          gan_fwrite_lendian_ui32(fp,(gan_uint32 *)(pul),ni)
#elif (SIZEOF_LONG == 8)
#define gan_fwrite_lendian_ul(fp,pul,ni)\
          gan_fwrite_lendian_ui64(fp,(gan_uint64 *)(pul),ni)
#else
#error "unsupported size"
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_ENDIAN_IO_H */
