/**
 * File:          $RCSfile: misc_defs.h,v $
 * Module:        Miscellaneous definitions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.60 $
 * Last edited:   $Date: 2006/06/12 13:38:47 $
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

#ifndef _GAN_MISC_DEFS_H
#define _GAN_MISC_DEFS_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <assert.h>
#include <gandalf/config.h>

#ifdef _MSC_VER
#ifdef GANDALF_STATIC
   #define GANDALF_API
#else
   #ifdef GANDALF_EXPORTS
      #define GANDALF_API __declspec(dllexport)
   #else
      #define GANDALF_API __declspec(dllimport)
   #endif
#endif
#else
#define GANDALF_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonMisc
 * \{
 */

/* architecture dependent stuff */

/* on SGIs, SCSL contains LAPACK */
#ifdef HAVE_SCSL
#ifdef HAVE_LAPACK
#error Conflicting versions of LAPACK on SGI
#endif

#define HAVE_LAPACK 1
#endif

/// Boolean data type
typedef enum
{
    /// Boolean false value
    GAN_FALSE=0,

    /// Boolean true value
    GAN_TRUE=1
} Gan_Bool;

/* expresion to be evaluated only if NDEBUG is not defined */
#ifdef NDEBUG
#define gan_eval(x) ((void) 0)
#else
#define gan_eval(x) (x)
#endif

/* define if you want to check for memory leaks */
/* NOT THREAD-SAFE */
#ifndef GAN_THREAD_SAFE
#if 0
#define GAN_MALLOC_DEBUG
#endif
#endif

/// labels for simple types used throughout Gandalf
typedef enum
{
   GAN_CHAR,       /**< signed character */
   GAN_UCHAR,      /**< unsigned character */
   GAN_SHORT,      /**< signed short integer */
   GAN_USHORT,     /**< unsigned short integer */
   GAN_INT,        /**< signed integer */
   GAN_UINT,       /**< unsigned integer */
   GAN_LONG,       /**< signed long integer */
   GAN_ULONG,      /**< unsigned long integer */
   GAN_FLOAT,      /**< single precision floating point */
   GAN_DOUBLE,     /**< double precision floating point */
   GAN_LONGDOUBLE, /**< long double precision floating point */
   GAN_STRING,     /**< string (array of characters) */
   GAN_BOOL,       /**< boolean */
   GAN_POINTER,    /**< generic pointer */
#if (SIZEOF_LONG_LONG != 0)
   GAN_LONGLONG,   /**< signed extra-long integer */
#endif
   GAN_UINT10,     /**< 10-bit unsigned integer */
   GAN_UINT12,     /**< 12-bit unsigned integer */
   GAN_UNDEFINED_TYPE
} Gan_Type;

/// array of sizeof()'s of each Gandalf type, one for each value in a Gan_Type
extern GANDALF_API const size_t gan_type_sizes[];

GANDALF_API const char *gan_type_string ( Gan_Type type );

/* GAN_UINT8/16/32/64_MAX is the maximum value a 8/16/32/64 bit unsigned
 * type can hold. */

/* set floating-point versions of integer type limits */
#if (SIZEOF_CHAR == 1)
#define GAN_CHAR_MAXD 127.0
#define GAN_CHAR_MAXF 127.0F
#define GAN_UCHAR_MAXD 255.0
#define GAN_UCHAR_MAXF 255.0F
#endif

#if (SIZEOF_SHORT == 2)
#define GAN_SHRT_MAXD 32767.0
#define GAN_SHRT_MAXF 32767.0F
#define GAN_USHRT_MAXD 65535.0
#define GAN_USHRT_MAXF 65535.0F
#elif (SIZEOF_SHORT == 4)
#define GAN_SHRT_MAXD 2147483647.0
#define GAN_SHRT_MAXF 2147483647.0F
#define GAN_USHRT_MAXD 4294967295.0
#define GAN_USHRT_MAXF 4294967295.0F
#elif (SIZEOF_SHORT == 8)
#define GAN_SHRT_MAXD 9.2233720368547758e18
#define GAN_SHRT_MAXF 9.2233720368547758e18F
#define GAN_USHRT_MAXD 1.8446744073709552e19
#define GAN_USHRT_MAXF 1.8446744073709552e19F
#endif

#if (SIZEOF_INT == 2)
#define GAN_INT_MAXD 32767.0
#define GAN_INT_MAXF 32767.0F
#define GAN_UINT_MAXD 65535.0
#define GAN_UINT_MAXF 65535.0F
#elif (SIZEOF_INT == 4)
#define GAN_INT_MAXD 2147483647.0
#define GAN_INT_MAXF 2147483647.0F
#define GAN_UINT_MAXD 4294967295.0
#define GAN_UINT_MAXF 4294967295.0F
#elif (SIZEOF_INT == 8)
#define GAN_INT_MAXD 9.2233720368547758e18
#define GAN_INT_MAXF 9.2233720368547758e18F
#define GAN_UINT_MAXD 1.8446744073709552e19
#define GAN_UINT_MAXF 1.8446744073709552e19F
#endif

#if (SIZEOF_LONG == 4)
#define GAN_ULONG_MAXD 4294967295.0
#define GAN_ULONG_MAXF 4294967295.0F
#elif (SIZEOF_LONG == 8)
#define GAN_LONG_MAXD 9.2233720368547758e18
#define GAN_LONG_MAXF 9.2233720368547758e18F
#define GAN_ULONG_MAXD 1.8446744073709552e19
#define GAN_ULONG_MAXF 1.8446744073709552e19F
#endif

/* 8-bit integer types */
#if (SIZEOF_CHAR == 1)
typedef          char gan_int8;
typedef unsigned char gan_uint8;
#define GAN_INT8  GAN_CHAR
#define GAN_UINT8 GAN_UCHAR
#define GAN_INT8_MIN  CHAR_MIN
#define GAN_INT8_MAX  CHAR_MAX
#define GAN_UINT8_MAX UCHAR_MAX
#define GAN_UINT8_MAXD GAN_UCHAR_MAXD
#define GAN_UINT8_MAXF GAN_UCHAR_MAXF
#endif /* #if (SIZEOF_CHAR == 1) */

/* 16-bit integer types */
#if (SIZEOF_SHORT == 2)
typedef          short gan_int16;
typedef unsigned short gan_uint16;
#define GAN_INT16  GAN_SHORT
#define GAN_UINT16 GAN_USHORT
#define GAN_INT16_MIN  SHRT_MIN
#define GAN_INT16_MAX  SHRT_MAX
#define GAN_UINT16_MAX USHRT_MAX
#define GAN_UINT16_MAXD GAN_USHRT_MAXD
#define GAN_UINT16_MAXF GAN_USHRT_MAXF
#elif (SIZEOF_INT == 2)
typedef          int gan_int16;
typedef unsigned int gan_uint16;
#define GAN_INT16  GAN_INT
#define GAN_UINT16 GAN_UINT
#define GAN_INT16_MIN  INT_MIN
#define GAN_INT16_MAX  INT_MAX
#define GAN_UINT16_MAX UINT_MAX
#define GAN_UINT16_MAXD GAN_UINT_MAXD
#define GAN_UINT16_MAXF GAN_UINT_MAXF
#endif /* #if (SIZEOF_SHORT == 2) */

/* 32-bit integer types */
#if (SIZEOF_INT == 4)
typedef          int gan_int32;
typedef unsigned int gan_uint32;
#define GAN_INT32  GAN_INT
#define GAN_UINT32 GAN_UINT
#define GAN_INT32_MIN  INT_MIN
#define GAN_INT32_MAX  INT_MAX
#define GAN_UINT32_MAX UINT_MAX
#define GAN_UINT32_MAXD GAN_UINT_MAXD
#define GAN_UINT32_MAXF GAN_UINT_MAXF
#elif (SIZEOF_LONG == 4)
typedef          long gan_int32;
typedef unsigned long gan_uint32;
#define GAN_INT32  GAN_LONG
#define GAN_UINT32 GAN_ULONG
#define GAN_INT32_MIN  LONG_MIN
#define GAN_INT32_MAX  LONG_MAX
#define GAN_UINT32_MAX ULONG_MAX
#define GAN_UINT32_MAXD GAN_ULONG_MAXD
#define GAN_UINT32_MAXF GAN_ULONG_MAXF
#endif /* #if (SIZEOF_INT == 4) */

/* 64-bit unsigned type */
#if (SIZEOF_INT == 8)
typedef          int gan_int64;
typedef unsigned int gan_uint64;
#define GAN_INT64  GAN_INT
#define GAN_UINT64 GAN_UINT
#define GAN_INT64_MIN  INT_MIN
#define GAN_INT64_MAX  INT_MAX
#define GAN_UINT64_MAX UINT_MAX
#define GAN_UINT64_MAXD GAN_UINT_MAXD
#define GAN_UINT64_MAXF GAN_UINT_MAXF
#elif (SIZEOF_LONG == 8)
typedef          long gan_int64;
typedef unsigned long gan_uint64;
#define GAN_INT64  GAN_LONG
#define GAN_UINT64 GAN_ULONG
#define GAN_INT64_MIN  LONG_MIN
#define GAN_INT64_MAX  LONG_MAX
#define GAN_UINT64_MAX ULONG_MAX
#define GAN_UINT64_MAXD GAN_ULONG_MAXD
#define GAN_UINT64_MAXF GAN_ULONG_MAXF
#endif /* #if (SIZEOF_INT == 8) */

/* 32-bit float type */
#if (SIZEOF_FLOAT == 4)
typedef float gan_float32;
#define GAN_FLOAT32 GAN_FLOAT
#define GAN_FLOAT32_MIN  FLT_MIN
#define GAN_FLOAT32_MAX  FLT_MAX
#endif /* #if (SIZEOF_FLOAT == 4) */

/* 64-bit float type */
#if (SIZEOF_DOUBLE == 8)
typedef double gan_float64;
#define GAN_FLOAT64 GAN_DOUBLE
#define GAN_FLOAT64_MIN  DBL_MIN
#define GAN_FLOAT64_MAX  DBL_MAX
#endif /* #if (SIZEOF_DOUBLE == 8) */

/* check sizes of objects we just defined */
#ifdef GAN_UINT8_MAX
#if (GAN_UINT8_MAX != 0xff)
#error Inconsistent 8-bit integer size
#endif
#endif

#ifdef GAN_UINT16_MAX
#if (GAN_UINT16_MAX != 0xffff)
#error Inconsistent 16-bit integer size
#endif
#endif

#ifdef GAN_UINT32_MAX
#if (GAN_UINT32_MAX != 0xffffffff)
#error Inconsistent 32-bit integer size
#endif
#endif

#ifdef GAN_UINT64_MAX
#if (GAN_UINT64_MAX != 0xffffffffffffffff)
#error Inconsistent 64-bit integer size
#endif
#endif

/**
 * \brief Macro: Applies test and aborts program on false result with a message.
 * \param expr The test expression to be evaluated
 * \param message The message printed when the test fails
 * \return No value.
 *
 * Evaluates a test expression and aborts the program if the expression \a expr
 * evaluates as false, printing the given error \a message.
 * Ignored if \c NDEBUG is defined.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_assert ( Gan_Bool expr, const char*message );
#else
#ifndef NDEBUG
#define gan_assert(expr, message) \
    if (!(expr)) { \
           fprintf(stderr, "Assertion (%s) failed: %s\n File %s(%d).\n", \
                  #expr, message, __FILE__, __LINE__); \
           abort(); }
#else
#define gan_assert(expr, mes) ((void) 0)
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

#ifndef NDEBUG
/**
 *\brief debug flag; can be set interactively in debugger to switch on various messages
 */
GANDALF_API extern Gan_Bool gan_debug;
#endif

/* in case you want to check the status of your malloc()/free() calls... */
#ifdef GAN_MALLOC_DEBUG

#ifndef GAN_DONT_DEFINE_MALLOC
#define malloc(n) gan_malloc(__FILE__,__LINE__,n)
#define free gan_free
#define calloc(n,bs) gan_calloc(__FILE__,__LINE__,n,bs)
#define realloc(ptr,n) gan_realloc(__FILE__,__LINE__,ptr,n)
#endif

GANDALF_API void *gan_calloc  ( const char *file, unsigned line, size_t nmemb, size_t size );
GANDALF_API void *gan_malloc  ( const char *file, unsigned line, size_t size );
GANDALF_API void *gan_realloc ( const char *file, unsigned line, void *ptr, size_t size );
GANDALF_API void  gan_free    ( void *ptr );
GANDALF_API Gan_Bool gan_heap_report(const char *file);
GANDALF_API void  gan_heap_push_fileline ( const char *file, int line );
GANDALF_API void  gan_heap_pop(void);

#define gan_heap_push() gan_heap_push_fileline(__FILE__,__LINE__)

#else
#define gan_heap_report(f)  ((void) 0)
#define gan_heap_push()    ((void) 0)
#define gan_heap_pop()     ((void) 0)
#endif /* #ifdef GAN_MALLOC_DEBUG */

/* check whether memcpy is part of the standard C library */
#ifndef HAVE_MEMCPY
GANDALF_API void *memcpy ( void *dest, const void *src, size_t n );
#endif

/* Necessary for Visual C++ compilation */
#ifndef M_SQRT1_2
#define M_SQRT1_2 0.70710678118654752440
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif

#ifndef M_SQRT3
#define M_SQRT3 1.73205080756887719317
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef M_LN2
# define M_LN2		0.69314718055994530942
#endif

/* extra useful constants */
#define GAN_ONE_THIRD   0.3333333333333333333333
#define GAN_ONE_THIRD_F 0.3333333333333333333333F
#define GAN_ONE_SIXTH   0.1666666666666666666666
#define GAN_ONE_SIXTH_F 0.1666666666666666666666F

/* powf and sqrtf are not available on all platforms: */
#ifndef HAVE_POWF
#define powf(x,y) (float)pow((float)(x), (float)(y))
#endif

#ifndef HAVE_FABSF
#define fabsf(x) (float)fabs((float)(x))
#endif

#ifndef HAVE_SQRTF
#define sqrtf(x) (float)sqrt((float)(x))
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

#endif /* #ifndef _GAN_MISC_DEFS_H */
