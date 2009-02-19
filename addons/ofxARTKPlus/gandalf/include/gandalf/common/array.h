/**
 * File:          $RCSfile: array.h,v $
 * Module:        Array module
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.15 $
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

#ifndef _GAN_ARRAY_H
#define _GAN_ARRAY_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonArray
 * \{
 */

/* array fill declarations */
#define GAN_FILL_DEC(t,f) \
  GANDALF_API void gan_fill_array_ ## f ( t *arr, unsigned long size, long stride, t val )

GAN_FILL_DEC(unsigned char,uc);
GAN_FILL_DEC(short,s);
GAN_FILL_DEC(unsigned short,us);
GAN_FILL_DEC(int,i);
GAN_FILL_DEC(unsigned int,ui);
GAN_FILL_DEC(long,l);
GAN_FILL_DEC(unsigned long,ul);
GAN_FILL_DEC(double,d);
GAN_FILL_DEC(float,f);
GAN_FILL_DEC(void *,p);

/* array copy declarations */
#define GAN_COPY_DEC(c,t)\
GANDALF_API void\
 gan_copy_array_ ## c ( const t *source, long s_stride, unsigned long size,\
                              t *dest,   long d_stride )

GAN_COPY_DEC(c,char);
GAN_COPY_DEC(uc,unsigned char);
GAN_COPY_DEC(s,short);
GAN_COPY_DEC(us,unsigned short);
GAN_COPY_DEC(i,int);
GAN_COPY_DEC(ui,unsigned int);
GAN_COPY_DEC(l,long);
GAN_COPY_DEC(ul,unsigned long);
GAN_COPY_DEC(f,float);
GAN_COPY_DEC(d,double);
GAN_COPY_DEC(p,void *);

/* macros for arrays of objects with specific bit size */

/* 8-bit integer types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 8-bit unsigned integer objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_uint8 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_uint8,ui8);

/**
 * \brief Copy array of 8-bit unsigned integer objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_uint8 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(ui8,gan_uint8);

#else

#if (SIZEOF_CHAR == 1)
#define gan_fill_array_ui8(arr,size,stride,val) \
        gan_fill_array_uc(arr,size,stride,val)
#define gan_copy_array_ui8(source,s_stride,size,dest,d_stride) \
        gan_copy_array_uc(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_CHAR == 1) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/* 16-bit integer types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 16-bit unsigned integer objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_uint16 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_uint16,ui16);

/**
 * \brief Copy array of 16-bit unsigned integer objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_uint16 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(ui16,gan_uint16);

#else

#if (SIZEOF_SHORT == 2)
#define gan_fill_array_ui16(arr,size,stride,val) \
        gan_fill_array_us(arr,size,stride,val)
#define gan_copy_array_ui16(source,s_stride,size,dest,d_stride) \
        gan_copy_array_us(source,s_stride,size,dest,d_stride)
#elif (SIZEOF_INT == 2)
#define gan_fill_array_ui16(arr,size,stride,val) \
        gan_fill_array_ui(arr,size,stride,val)
#define gan_copy_array_ui16(source,s_stride,size,dest,d_stride) \
        gan_copy_array_ui(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_SHORT == 2) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/* 32-bit integer types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 32-bit unsigned integer objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_uint32 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_uint32,ui32);

/**
 * \brief Copy array of 32-bit unsigned integer objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_uint32 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(ui32,gan_uint32);

#else

#if (SIZEOF_INT == 4)
#define gan_fill_array_ui32(arr,size,stride,val) \
        gan_fill_array_ui(arr,size,stride,val)
#define gan_copy_array_ui32(source,s_stride,size,dest,d_stride) \
        gan_copy_array_ui(source,s_stride,size,dest,d_stride)
#elif (SIZEOF_LONG == 4)
#define gan_fill_array_ui32(arr,size,stride,val) \
        gan_fill_array_ul(arr,size,stride,val)
#define gan_copy_array_ui32(source,s_stride,size,dest,d_stride) \
        gan_copy_array_ul(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_INT == 4) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/* 32-bit signed integer types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 32-bit signed integer objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_int32 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_int32,i32);

/**
 * \brief Copy array of 32-bit unsigned integer objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_int32 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(i32,gan_int32);

#else

#if (SIZEOF_INT == 4)
#define gan_fill_array_i32(arr,size,stride,val) \
        gan_fill_array_i(arr,size,stride,val)
#define gan_copy_array_i32(source,s_stride,size,dest,d_stride) \
        gan_copy_array_i(source,s_stride,size,dest,d_stride)
#elif (SIZEOF_LONG == 4)
#define gan_fill_array_i32(arr,size,stride,val) \
        gan_fill_array_l(arr,size,stride,val)
#define gan_copy_array_i32(source,s_stride,size,dest,d_stride) \
        gan_copy_array_l(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_INT == 4) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/* 64-bit integer types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 64-bit unsigned integer objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_ui64 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_ui64,ui64);

/**
 * \brief Copy array of 64-bit unsigned integer objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_ui64 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(ui64,gan_ui64);

#else

#if (SIZEOF_INT == 8)
#define gan_fill_array_ui64(arr,size,stride,val) \
        gan_fill_array_ui(arr,size,stride,val)
#define gan_copy_array_ui64(source,s_stride,size,dest,d_stride) \
        gan_copy_array_ui(source,s_stride,size,dest,d_stride)
#elif (SIZEOF_LONG == 8)
#define gan_fill_array_ui64(arr,size,stride,val) \
        gan_fill_array_ul(arr,size,stride,val)
#define gan_copy_array_ui64(source,s_stride,size,dest,d_stride) \
        gan_copy_array_ul(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_INT == 8) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/* 32-bit float types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 32-bit floating point objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_float32 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_float32,f32);

/**
 * \brief Copy array of 32-bit floating point objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_float32 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(f32,gan_float32);

#else

#if (SIZEOF_FLOAT == 4)
#define gan_fill_array_f32(arr,size,stride,val) \
        gan_fill_array_f(arr,size,stride,val)
#define gan_copy_array_f32(source,s_stride,size,dest,d_stride) \
        gan_copy_array_f(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_FLOAT == 4) */

#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/* 64-bit float types */
#ifdef GAN_GENERATE_DOCUMENTATION

/**
 * \brief Fill array of 64-bit floating point objects.
 * \return No value.
 *
 * Fill array \a arr of objects of type #gan_float64 with a constant value
 * \a val.
 */
GAN_FILL_DEC(gan_float64,f64);

/**
 * \brief Copy array of 64-bit floating point objects.
 * \return No value.
 *
 * \brief Copy \a source array of objects of type #gan_float64 to \a dest
 * array. The stride arguments indicate the spacing between elements of the
 * arrays.
 */
GAN_COPY_DEC(f64,gan_float64);

#else

#if (SIZEOF_DOUBLE == 8)
#define gan_fill_array_f64(arr,size,stride,val) \
        gan_fill_array_d(arr,size,stride,val)
#define gan_copy_array_f64(source,s_stride,size,dest,d_stride) \
        gan_copy_array_d(source,s_stride,size,dest,d_stride)
#endif /* #if (SIZEOF_DOUBLE == 8) */

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

#endif /* #ifndef _GAN_ARRAY_H */
