/**
 * File:          $RCSfile: pixel.h,v $
 * Module:        Image pixel definitions and functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.60 $
 * Last edited:   $Date: 2006/09/15 13:28:06 $
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

#ifndef _GAN_PIXEL_H
#define _GAN_PIXEL_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/common/bit_array.h>
#include <gandalf/linalg/2vector.h>
#include <gandalf/linalg/2vectorf.h>
#include <gandalf/linalg/3vector.h>
#include <gandalf/linalg/3vectorf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageAccessPixel
 * \{
 */

/**
 * \brief Different formats of image pixel.
 */
typedef enum
{
   GAN_GREY_LEVEL_IMAGE,       /**< grey-level images */
   GAN_GREY_LEVEL_ALPHA_IMAGE, /**< grey-level images with alpha channel */
   GAN_RGB_COLOUR_IMAGE,       /**< RGB colour images */
   GAN_RGB_COLOUR_ALPHA_IMAGE, /**< RGB colour images with alpha channel */
   GAN_BGR_COLOUR_IMAGE,       /**< BGR colour images */
   GAN_BGR_COLOUR_ALPHA_IMAGE, /**< BGR colour images with alpha channel */
   GAN_VECTOR_FIELD_2D,        /**< 2D image of 2D vectors */
   GAN_VECTOR_FIELD_3D,        /**< 2D image of 3D vectors */
   GAN_RGBX,                   /**< RGB padded out to a word boundary */
   GAN_RGBAS,                  /**< RGB with a small alpha channel */
   GAN_YUVX444,                /**< YUV 4-4-4 padded out to a word boundary */
   GAN_YUVA444,                /**< YUV with alpha */
   GAN_YUV422,                 /**< YUV 4-2-2 arranged as UYVY */
   GAN_UNDEFINED_IMAGE_FORMAT
} Gan_ImageFormat;

/**
 * \brief Structure defining grey-level unsigned character pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_uc
{
   unsigned char I, /**< Intensity channel */
                 A; /**< Alpha channel */
} Gan_GLAPixel_uc;

/**
 * \brief Structure defining grey-level short integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_s
{
   short I, /**< Intensity channel */
         A; /**< Alpha channel */
} Gan_GLAPixel_s;

/**
 * \brief Structure defining grey-level unsigned short pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_us
{
   unsigned short I, /**< Intensity channel */
                  A; /**< Alpha channel */
} Gan_GLAPixel_us;

/**
 * \brief Structure defining grey-level signed integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_i
{
   int I, /**< Intensity channel */
       A; /**< Alpha channel */
} Gan_GLAPixel_i;

/**
 * \brief Structure defining grey-level unsigned integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_ui
{
   unsigned int I, /**< Intensity channel */
                A; /**< Alpha channel */
} Gan_GLAPixel_ui;

/**
 * \brief Structure defining grey-level unsigned long integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_ul
{
   unsigned long I, /**< Intensity channel */
                 A; /**< Alpha channel */
} Gan_GLAPixel_ul;

/**
 * \brief Structure defining grey-level single precision floating point pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_f
{
   float I, /**< Intensity channel */
         A; /**< Alpha channel */
} Gan_GLAPixel_f;

/**
 * \brief Structure defining grey-level double precision floating point pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_d
{
   double I, /**< Intensity channel */
          A; /**< Alpha channel */
} Gan_GLAPixel_d;

/**
 * \brief Structure defining RGB colour unsigned character pixel.
 */
typedef struct Gan_RGBPixel_uc
{
   unsigned char R, /**< Red channel */
                 G, /**< Green channel */
                 B; /**< Blue channel */
} Gan_RGBPixel_uc;

/**
 * \brief Structure defining RGB colour signed short integer pixel.
 */
typedef struct Gan_RGBPixel_s
{
   short R, /**< Red channel */
         G, /**< Green channel */
         B; /**< Blue channel */
} Gan_RGBPixel_s;

/**
 * \brief Structure defining RGB colour unsigned short integer pixel.
 */
typedef struct Gan_RGBPixel_us
{
   unsigned short R, /**< Red channel */
                  G, /**< Green channel */
                  B; /**< Blue channel */
} Gan_RGBPixel_us;

/**
 * \brief Structure defining RGB colour signed integer pixel.
 */
typedef struct Gan_RGBPixel_i
{
   int R, /**< Red channel */
       G, /**< Green channel */
       B; /**< Blue channel */
} Gan_RGBPixel_i;

/**
 * \brief Structure defining RGB colour signed long integer pixel.
 */
typedef struct Gan_RGBPixel_l
{
   long R, /**< Red channel */
        G, /**< Green channel */
        B; /**< Blue channel */
} Gan_RGBPixel_l;

/**
 * \brief Structure defining RGB colour unsigned integer pixel.
 */
typedef struct Gan_RGBPixel_ui
{
   unsigned int R, /**< Red channel */
                G, /**< Green channel */
                B; /**< Blue channel */
} Gan_RGBPixel_ui;

/**
 * \brief Structure defining RGB colour unsigned long integer pixel.
 */
typedef struct Gan_RGBPixel_ul
{
   unsigned long R, /**< Red channel */
                 G, /**< Green channel */
                 B; /**< Blue channel */
} Gan_RGBPixel_ul;

/**
 * \brief Structure defining RGB colour singe precision floating point pixel.
 */
typedef struct Gan_RGBPixel_f
{
   float R, /**< Red channel */
         G, /**< Green channel */
         B; /**< Blue channel */
} Gan_RGBPixel_f;

/**
 * \brief Structure defining RGB colour double precision floating point pixel.
 */
typedef struct Gan_RGBPixel_d
{
   double R, /**< Red channel */
          G, /**< Green channel */
          B; /**< Blue channel */
} Gan_RGBPixel_d;

/**
 * \brief Structure defining RGB unsigned character pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_uc
{
   unsigned char R, /**< Red channel */
                 G, /**< Green channel */
                 B, /**< Blue channel */
                 A; /**< Alpha channel */
} Gan_RGBAPixel_uc;

/**
 * \brief Structure defining RGB signed short integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_s
{
   short R, /**< Red channel */
         G, /**< Green channel */
         B, /**< Blue channel */
         A; /**< Alpha channel */
} Gan_RGBAPixel_s;

/**
 * \brief Structure defining RGB unsigned short integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_us
{
   unsigned short R, /**< Red channel */
                  G, /**< Green channel */
                  B, /**< Blue channel */
                  A; /**< Alpha channel */
} Gan_RGBAPixel_us;

/**
 * \brief Structure defining RGB signed integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_i
{
   int R, /**< Red channel */
       G, /**< Green channel */
       B, /**< Blue channel */
       A; /**< Alpha channel */
} Gan_RGBAPixel_i;

/**
 * \brief Structure defining RGB signed long integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_l
{
   long R, /**< Red channel */
        G, /**< Green channel */
        B, /**< Blue channel */
        A; /**< Alpha channel */
} Gan_RGBAPixel_l;

/**
 * \brief Structure defining RGB unsigned integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_ui
{
   unsigned int R, /**< Red channel */
                G, /**< Green channel */
                B, /**< Blue channel */
                A; /**< Alpha channel */
} Gan_RGBAPixel_ui;

/**
 * \brief Structure defining RGB unsigned long integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_ul
{
   unsigned long R, /**< Red channel */
                 G, /**< Green channel */
                 B, /**< Blue channel */
                 A; /**< Alpha channel */
} Gan_RGBAPixel_ul;

/**
 * \brief Structure defining RGB single precision floating point pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_f
{
   float R, /**< Red channel */
         G, /**< Green channel */
         B, /**< Blue channel */
         A; /**< Alpha channel */
} Gan_RGBAPixel_f;

/**
 * \brief Structure defining RGB double precision floating point pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_d
{
   double R, /**< Red channel */
          G, /**< Green channel */
          B, /**< Blue channel */
          A; /**< Alpha channel */
} Gan_RGBAPixel_d;

/**
 * \brief Structure defining BGR colour unsigned character pixel.
 */
typedef struct Gan_BGRPixel_uc
{
   unsigned char R, /**< Red channel */
                 G, /**< Green channel */
                 B; /**< Blue channel */
} Gan_BGRPixel_uc;

/**
 * \brief Structure defining BGR colour signed short integer pixel.
 */
typedef struct Gan_BGRPixel_s
{
   short R, /**< Red channel */
         G, /**< Green channel */
         B; /**< Blue channel */
} Gan_BGRPixel_s;

/**
 * \brief Structure defining BGR colour unsigned short integer pixel.
 */
typedef struct Gan_BGRPixel_us
{
   unsigned short R, /**< Red channel */
                  G, /**< Green channel */
                  B; /**< Blue channel */
} Gan_BGRPixel_us;

/**
 * \brief Structure defining BGR colour signed integer pixel.
 */
typedef struct Gan_BGRPixel_i
{
   int R, /**< Red channel */
       G, /**< Green channel */
       B; /**< Blue channel */
} Gan_BGRPixel_i;

/**
 * \brief Structure defining BGR colour unsigned integer pixel.
 */
typedef struct Gan_BGRPixel_ui
{
   unsigned int R, /**< Red channel */
                G, /**< Green channel */
                B; /**< Blue channel */
} Gan_BGRPixel_ui;

/**
 * \brief Structure defining BGR colour singe precision floating point pixel.
 */
typedef struct Gan_BGRPixel_f
{
   float R, /**< Red channel */
         G, /**< Green channel */
         B; /**< Blue channel */
} Gan_BGRPixel_f;

/**
 * \brief Structure defining BGR colour double precision floating point pixel.
 */
typedef struct Gan_BGRPixel_d
{
   double R, /**< Red channel */
          G, /**< Green channel */
          B; /**< Blue channel */
} Gan_BGRPixel_d;

/**
 * \brief Structure defining BGR unsigned character pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_uc
{
   unsigned char R, /**< Red channel */
                 G, /**< Green channel */
                 B, /**< Blue channel */
                 A; /**< Alpha channel */
} Gan_BGRAPixel_uc;

/**
 * \brief Structure defining BGR signed short integer pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_s
{
   short R, /**< Red channel */
         G, /**< Green channel */
         B, /**< Blue channel */
         A; /**< Alpha channel */
} Gan_BGRAPixel_s;

/**
 * \brief Structure defining BGR unsigned short integer pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_us
{
   unsigned short R, /**< Red channel */
                  G, /**< Green channel */
                  B, /**< Blue channel */
                  A; /**< Alpha channel */
} Gan_BGRAPixel_us;

/**
 * \brief Structure defining BGR signed integer pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_i
{
   int R, /**< Red channel */
       G, /**< Green channel */
       B, /**< Blue channel */
       A; /**< Alpha channel */
} Gan_BGRAPixel_i;

/**
 * \brief Structure defining BGR unsigned integer pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_ui
{
   unsigned int R, /**< Red channel */
                G, /**< Green channel */
                B, /**< Blue channel */
                A; /**< Alpha channel */
} Gan_BGRAPixel_ui;

/**
 * \brief Structure defining BGR single precision floating point pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_f
{
   float R, /**< Red channel */
         G, /**< Green channel */
         B, /**< Blue channel */
         A; /**< Alpha channel */
} Gan_BGRAPixel_f;

/**
 * \brief Structure defining BGR double precision floating point pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_d
{
   double R, /**< Red channel */
          G, /**< Green channel */
          B, /**< Blue channel */
          A; /**< Alpha channel */
} Gan_BGRAPixel_d;

/**
 * \brief Structure defining padded 8-bit RGBX pixel
 */
typedef struct Gan_RGBXPixel_ui8
{
   unsigned int X : 8; /**< padding */
   unsigned int B : 8; /**< Blue channel */
   unsigned int G : 8; /**< Green channel */
   unsigned int R : 8; /**< Red channel */
} Gan_RGBXPixel_ui8;

/**
 * \brief Structure defining 10-bit RGBX pixel
 */
typedef struct Gan_RGBXPixel_ui10
{
   unsigned int X : 2;  /**< padding */
   unsigned int B : 10; /**< Blue channel */
   unsigned int G : 10; /**< Green channel */
   unsigned int R : 10; /**< Red channel */
} Gan_RGBXPixel_ui10;

/**
 * \brief Structure defining 10-bit RGB pixel with 2-bit alpha channel
 */
typedef struct Gan_RGBASPixel_ui10
{
   unsigned int A : 2; /**< Alpha channel */
   unsigned int B : 10; /**< Blue channel */
   unsigned int G : 10; /**< Green channel */
   unsigned int R : 10; /**< Red channel */
} Gan_RGBASPixel_ui10;

/**
 * \brief Structure defining 12-bit packed RGBA
 *
 * NB cannot be used to iterate along raster because of the packing
 */
typedef struct Gan_RGBAPixel_ui12
{
   unsigned int A : 12; /**< Alpha channel */
   unsigned int B : 12; /**< Blue channel */
   unsigned int G : 12; /**< Green channel */
   unsigned int R : 12; /**< Red channel */
} Gan_RGBAPixel_ui12;

/**
 * \brief Structure defining YUV 8-bit 4-4-4 pixel padded to a word boundary
 */
typedef struct Gan_YUVX444Pixel_ui8
{
   gan_uint8 Y; /**< Luminance channel */
   gan_uint8 U; /**< Chrominance channel */
   gan_uint8 V; /**< Chrominance channel */
   gan_uint8 X; /**< padding */
} Gan_YUVX444Pixel_ui8;

/**
 * \brief Structure defining YUVA 8-bit 4-4-4 pixel
 */
typedef struct Gan_YUVA444Pixel_ui8
{
   gan_uint8 Y; /**< Luminance channel */
   gan_uint8 U; /**< Chrominance channel */
   gan_uint8 V; /**< Chrominance channel */
   gan_uint8 A; /**< alpha channel */
} Gan_YUVA444Pixel_ui8;

/**
 * \brief Structure defining UYVY 8-bit 4-2-2 pixel
 *
 * NB cannot be used to iterate along raster because of the 4-2-2 sampling
 */
typedef struct Gan_YUV422Pixel_ui8
{
   gan_uint8 UV; /**< One of the two chrominance channels, depending on the column position */
   gan_uint8 Y;  /**< Luminance channel */
} Gan_YUV422Pixel_ui8;

/**
 * \brief Structure defining YX 10-bit luminance with 6-bit padding
 */
typedef struct Gan_YXPixel_ui10
{
   gan_uint16 X :  6; /**< padding */
   gan_uint16 Y : 10; /**< Luminance channel */
} Gan_YXPixel_ui10;

/**
 * \brief Structure defining YX 12-bit luminance with 4-bit padding
 */
typedef struct Gan_YXPixel_ui12
{
   gan_uint16 X :  4; /**< padding */
   gan_uint16 Y : 12; /**< Luminance channel */
} Gan_YXPixel_ui12;

#ifdef GAN_UINT8
#if (SIZEOF_CHAR == 1)
/**
 * \brief Structure defining grey-level 8-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_uc Gan_GLAPixel_ui8;

/**
 * \brief Structure defining RGB colour 8-bit unsigned integer pixel.
 */
typedef struct Gan_RGBPixel_uc Gan_RGBPixel_ui8;

/**
 * \brief Structure defining RGB colour 8-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_uc Gan_RGBAPixel_ui8;

/**
 * \brief Structure defining BGR colour 8-bit unsigned integer pixel.
 */
typedef struct Gan_BGRPixel_uc Gan_BGRPixel_ui8;

/**
 * \brief Structure defining BGR colour 8-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_uc Gan_BGRAPixel_ui8;
#else
#error "8-bit type conflict"
#endif /* #if (SIZEOF_CHAR == 1) */
#endif /* #ifdef GAN_UINT8 */

#ifdef GAN_UINT16
#if (SIZEOF_SHORT == 2)
/**
 * \brief Structure defining grey-level 16-bit unsigned integer pixel with
 *        alpha channel.
 */
typedef struct Gan_GLAPixel_us Gan_GLAPixel_ui16;

/**
 * \brief Structure defining RGB colour 16-bit unsigned integer pixel.
 */
typedef struct Gan_RGBPixel_us Gan_RGBPixel_ui16;

/**
 * \brief Structure defining RGB colour 16-bit unsigned integer pixel with
 *        alpha channel.
 */
typedef struct Gan_RGBAPixel_us Gan_RGBAPixel_ui16;

/**
 * \brief Structure defining BGR colour 16-bit unsigned integer pixel.
 */
typedef struct Gan_BGRPixel_us Gan_BGRPixel_ui16;

/**
 * \brief Structure defining BGR colour 16-bit unsigned integer pixel with
 *        alpha channel.
 */
typedef struct Gan_BGRAPixel_us Gan_BGRAPixel_ui16;
#else
#error "16-bit type conflict"
#endif /* #if (SIZEOF_SHORT == 2) */
#endif /* #ifdef GAN_UINT16 */

#ifdef GAN_UINT32
#if (SIZEOF_INT == 4)
/**
 * \brief Structure defining grey-level 32-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_ui Gan_GLAPixel_ui32;

/**
 * \brief Structure defining RGB colour 32-bit unsigned integer pixel.
 */
typedef struct Gan_RGBPixel_ui Gan_RGBPixel_ui32;

/**
 * \brief Structure defining RGB colour 32-bit signed integer pixel.
 */
typedef struct Gan_RGBPixel_i Gan_RGBPixel_i32;

/**
 * \brief Structure defining RGB colour 32-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_ui Gan_RGBAPixel_ui32;

/**
 * \brief Structure defining RGB colour 32-bit signed integer pixel  with alpha channel.
 */
typedef struct Gan_RGBAPixel_i Gan_RGBAPixel_i32;

/**
 * \brief Structure defining BGR colour 32-bit unsigned integer pixel.
 */
typedef struct Gan_BGRPixel_ui Gan_BGRPixel_ui32;

/**
 * \brief Structure defining BGR colour 32-bit signed integer pixel.
 */
typedef struct Gan_BGRPixel_i Gan_BGRPixel_i32;

/**
 * \brief Structure defining BGR colour 32-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_BGRAPixel_ui Gan_BGRAPixel_ui32;

/**
 * \brief Structure defining BGR colour 32-bit signed integer pixel  with alpha channel.
 */
typedef struct Gan_BGRAPixel_i Gan_BGRAPixel_i32;

#else
#error "32-bit type conflict"
#endif /* #if (SIZEOF_INT == 4) */
#endif /* #ifdef GAN_UINT32 */

#ifdef GAN_UINT64
#if (SIZEOF_INT == 8)
/**
 * \brief Structure defining grey-level 64-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_ui Gan_GLAPixel_ui64;

/**
 * \brief Structure defining RGB colour 64-bit unsigned integer pixel.
 */
typedef struct Gan_RGBPixel_ui Gan_RGBPixel_ui64;

/**
 * \brief Structure defining RGB colour 64-bit signed integer pixel.
 */
typedef struct Gan_RGBPixel_i Gan_RGBPixel_i64;

/**
 * \brief Structure defining RGB colour 64-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_ui Gan_RGBAPixel_ui64;

/**
 * \brief Structure defining RGB colour 64-bit signed integer pixel  with alpha channel.
 */
typedef struct Gan_RGBAPixel_i Gan_RGBAPixel_i64;

#elif (SIZEOF_LONG == 8)
/**
 * \brief Structure defining grey-level 64-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_ul Gan_GLAPixel_ui64;

/**
 * \brief Structure defining RGB colour 64-bit unsigned integer pixel.
 */
typedef struct Gan_RGBPixel_ul Gan_RGBPixel_ui64;

/**
 * \brief Structure defining RGB colour 64-bit signed integer pixel.
 */
typedef struct Gan_RGBPixel_l Gan_RGBPixel_i64;

/**
 * \brief Structure defining RGB colour 64-bit unsigned integer pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_ul Gan_RGBAPixel_ui64;

/**
 * \brief Structure defining RGB colour 64-bit signed integer pixel  with alpha channel.
 */
typedef struct Gan_RGBAPixel_l Gan_RGBAPixel_i64;

#else
#error "64-bit type conflict"
#endif /* #if (SIZEOF_INT == 8) */
#endif /* #ifdef GAN_UINT64 */

#ifdef GAN_FLOAT32
#if (SIZEOF_FLOAT == 4)
/**
 * \brief Structure defining grey-level 32-bit float pixel with alpha channel.
 */
typedef struct Gan_GLAPixel_f Gan_GLAPixel_f32;

/**
 * \brief Structure defining RGB colour 32-bit float pixel.
 */
typedef struct Gan_RGBPixel_f Gan_RGBPixel_f32;

/**
 * \brief Structure defining RGB colour 32-bit float pixel with alpha channel.
 */
typedef struct Gan_RGBAPixel_f Gan_RGBAPixel_f32;

/**
 * \brief Structure defining BGR colour 32-bit float pixel.
 */
typedef struct Gan_BGRPixel_f Gan_BGRPixel_f32;

/**
 * \brief Structure defining BGR colour 32-bit float pixel with
 *        alpha channel.
 */
typedef struct Gan_BGRAPixel_f Gan_BGRAPixel_f32;
#else
#error "32-bit float type conflict"
#endif /* #if (SIZEOF_FLOAT == 4) */
#endif /* #ifdef GAN_FLOAT32 */

#ifdef GAN_FLOAT64
#if (SIZEOF_DOUBLE == 8)
/**
 * \brief Structure defining grey-level 64-bit float pixel with
 *        alpha channel.
 */
typedef struct Gan_GLAPixel_d Gan_GLAPixel_f64;

/**
 * \brief Structure defining RGB colour 64-bit float pixel.
 */
typedef struct Gan_RGBPixel_d Gan_RGBPixel_f64;

/**
 * \brief Structure defining RGB colour 64-bit float pixel with
 *        alpha channel.
 */
typedef struct Gan_RGBAPixel_d Gan_RGBAPixel_f64;

/**
 * \brief Structure defining BGR colour 64-bit float pixel.
 */
typedef struct Gan_BGRPixel_d Gan_BGRPixel_f64;

/**
 * \brief Structure defining BGR colour 64-bit float pixel with
 *        alpha channel.
 */
typedef struct Gan_BGRAPixel_d Gan_BGRAPixel_f64;
#else
#error "64-bit float type conflict"
#endif /* #if (SIZEOF_DOUBLE == 8) */
#endif /* #ifdef GAN_FLOAT64 */

/**
 * \brief Structure definition for image pixel of any format or type.
 */
typedef struct Gan_Pixel
{
   /// format of image: grey-level, RGB colour etc.
   Gan_ImageFormat format;

   /// type of pixel values: unsigned char, float etc.
   Gan_Type type;

   /// nested union defining pixel types
   union
   {
      /// grey level
      union
      {
         unsigned char  uc;
         short          s;
         unsigned short us;
         int            i;
         unsigned int   ui;
         double         d;
         float          f;
         Gan_Bool       b;
         void          *p;

#ifdef GAN_UINT8
         gan_uint8 ui8;
#endif
#ifdef GAN_UINT16
         gan_uint16 ui16;
#endif
#ifdef GAN_UINT32
         gan_uint32 ui32;
#endif
         Gan_YXPixel_ui10 ui10;
         Gan_YXPixel_ui12 ui12;
      } gl;

      /// grey level with alpha channel
      union
      {
         Gan_GLAPixel_uc uc;
         Gan_GLAPixel_s  s;
         Gan_GLAPixel_us us;
         Gan_GLAPixel_i  i;
         Gan_GLAPixel_ui ui;
         Gan_GLAPixel_d  d;
         Gan_GLAPixel_f  f;

#ifdef GAN_UINT8
         Gan_GLAPixel_ui8 ui8;
#endif
#ifdef GAN_UINT16
         Gan_GLAPixel_ui16 ui16;
#endif
#ifdef GAN_UINT32
         Gan_GLAPixel_ui32 ui32;
#endif
      } gla;

      /// RGB colour
      union
      {
         Gan_RGBPixel_uc uc;
         Gan_RGBPixel_s  s;
         Gan_RGBPixel_us us;
         Gan_RGBPixel_i  i;
         Gan_RGBPixel_ui ui;
         Gan_RGBPixel_d  d;
         Gan_RGBPixel_f  f;

#ifdef GAN_UINT8
         Gan_RGBPixel_ui8 ui8;
#endif
#ifdef GAN_UINT16
         Gan_RGBPixel_ui16 ui16;
#endif
#ifdef GAN_UINT32
         Gan_RGBPixel_ui32 ui32;
#endif
      } rgb;

      /// RGB colour with alpha channel
      union
      {
         Gan_RGBAPixel_uc uc;
         Gan_RGBAPixel_s  s;
         Gan_RGBAPixel_us us;
         Gan_RGBAPixel_i  i;
         Gan_RGBAPixel_ui ui;
         Gan_RGBAPixel_d  d;
         Gan_RGBAPixel_f  f;

#ifdef GAN_UINT8
         Gan_RGBAPixel_ui8 ui8;
#endif
#ifdef GAN_UINT16
         Gan_RGBAPixel_ui16 ui16;
#endif
#ifdef GAN_UINT32
         Gan_RGBAPixel_ui32 ui32;
#endif
         Gan_RGBAPixel_ui12 ui12;
      } rgba;

      /// BGR colour
      union
      {
         Gan_BGRPixel_uc uc;
         Gan_BGRPixel_s  s;
         Gan_BGRPixel_us us;
         Gan_BGRPixel_i  i;
         Gan_BGRPixel_ui ui;
         Gan_BGRPixel_d  d;
         Gan_BGRPixel_f  f;

#ifdef GAN_UINT8
         Gan_BGRPixel_ui8 ui8;
#endif
#ifdef GAN_UINT16
         Gan_BGRPixel_ui16 ui16;
#endif
#ifdef GAN_UINT32
         Gan_BGRPixel_ui32 ui32;
#endif
      } bgr;

      /// BGR colour with alpha channel
      union
      {
         Gan_BGRAPixel_uc uc;
         Gan_BGRAPixel_s  s;
         Gan_BGRAPixel_us us;
         Gan_BGRAPixel_i  i;
         Gan_BGRAPixel_ui ui;
         Gan_BGRAPixel_d  d;
         Gan_BGRAPixel_f  f;

#ifdef GAN_UINT8
         Gan_BGRAPixel_ui8 ui8;
#endif
#ifdef GAN_UINT16
         Gan_BGRAPixel_ui16 ui16;
#endif
#ifdef GAN_UINT32
         Gan_BGRAPixel_ui32 ui32;
#endif
      } bgra;

      /// 2D vector field
      union
      {
         Gan_Vector2_f f;
         Gan_Vector2   d;
         Gan_Vector2_s s;
         Gan_Vector2_i i;
      } vfield2D;

      /// 3D vector field
      union
      {
         Gan_Vector3_f f;
         Gan_Vector3   d;
         Gan_Vector3_s s;
         Gan_Vector3_i i;
      } vfield3D;

      /// RGBX data
      union
      {
         Gan_RGBXPixel_ui8   ui8;
         Gan_RGBXPixel_ui10 ui10;
      } rgbx;

      /// RGBA data with small alpha channel
      union
      {
         Gan_RGBASPixel_ui10 ui10;
      } rgbas;

      /// YUV 4-4-4 with padding to a word boundary
      union
      {
         Gan_YUVX444Pixel_ui8 ui8;
      } yuvx444;

      /// YUVA 4-4-4
      union
      {
         Gan_YUVA444Pixel_ui8 ui8;
      } yuva444;

      /// YUV 4-2-2
      union
      {
         Gan_YUV422Pixel_ui8 ui8;
      } yuv422;
   } data;
} Gan_Pixel;

GANDALF_API unsigned char  gan_pixel_rgbuc_to_yuc ( const Gan_RGBPixel_uc *rgb );
GANDALF_API unsigned short gan_pixel_rgbuc_to_yus ( const Gan_RGBPixel_uc *rgb );
GANDALF_API unsigned int   gan_pixel_rgbuc_to_yui ( const Gan_RGBPixel_uc *rgb );
GANDALF_API unsigned char  gan_pixel_rgbus_to_yuc ( const Gan_RGBPixel_us *rgb );
GANDALF_API unsigned short gan_pixel_rgbus_to_yus ( const Gan_RGBPixel_us *rgb );
GANDALF_API float          gan_pixel_rgbui_to_yf  ( const Gan_RGBPixel_ui *rgb );
GANDALF_API float          gan_pixel_rgbf_to_yf   ( const Gan_RGBPixel_f  *rgb );
GANDALF_API double         gan_pixel_rgbd_to_yd   ( const Gan_RGBPixel_d  *rgb );
GANDALF_API unsigned char  gan_pixel_rgbauc_to_yuc ( const Gan_RGBAPixel_uc *rgba );
GANDALF_API unsigned short gan_pixel_rgbauc_to_yus ( const Gan_RGBAPixel_uc *rgba );
GANDALF_API unsigned int   gan_pixel_rgbauc_to_yui ( const Gan_RGBAPixel_uc *rgba );
GANDALF_API unsigned char  gan_pixel_rgbaus_to_yuc ( const Gan_RGBAPixel_us *rgba );
GANDALF_API unsigned short gan_pixel_rgbaus_to_yus ( const Gan_RGBAPixel_us *rgba );
GANDALF_API float          gan_pixel_rgbaui_to_yf  ( const Gan_RGBAPixel_ui *rgba );
GANDALF_API float          gan_pixel_rgbaf_to_yf   ( const Gan_RGBAPixel_f  *rgba );
GANDALF_API double         gan_pixel_rgbad_to_yd   ( const Gan_RGBAPixel_d  *rgba );

GANDALF_API unsigned char  gan_pixel_bgruc_to_yuc ( const Gan_BGRPixel_uc *bgr );
GANDALF_API unsigned short gan_pixel_bgruc_to_yus ( const Gan_BGRPixel_uc *bgr );
GANDALF_API unsigned int   gan_pixel_bgruc_to_yui ( const Gan_BGRPixel_uc *bgr );
GANDALF_API unsigned char  gan_pixel_bgrus_to_yuc ( const Gan_BGRPixel_us *bgr );
GANDALF_API unsigned short gan_pixel_bgrus_to_yus ( const Gan_BGRPixel_us *bgr );
GANDALF_API float          gan_pixel_bgrui_to_yf  ( const Gan_BGRPixel_ui *bgr );
GANDALF_API float          gan_pixel_bgrf_to_yf   ( const Gan_BGRPixel_f  *bgr );
GANDALF_API double         gan_pixel_bgrd_to_yd   ( const Gan_BGRPixel_d  *bgr );
GANDALF_API unsigned char  gan_pixel_bgrauc_to_yuc ( const Gan_BGRAPixel_uc *bgra );
GANDALF_API unsigned short gan_pixel_bgrauc_to_yus ( const Gan_BGRAPixel_uc *bgra );
GANDALF_API unsigned int   gan_pixel_bgrauc_to_yui ( const Gan_BGRAPixel_uc *bgra );
GANDALF_API unsigned char  gan_pixel_bgraus_to_yuc ( const Gan_BGRAPixel_us *bgra );
GANDALF_API unsigned short gan_pixel_bgraus_to_yus ( const Gan_BGRAPixel_us *bgra );
GANDALF_API float          gan_pixel_bgraui_to_yf  ( const Gan_BGRAPixel_ui *bgra );
GANDALF_API float          gan_pixel_bgraf_to_yf   ( const Gan_BGRAPixel_f  *bgra );
GANDALF_API double         gan_pixel_bgrad_to_yd   ( const Gan_BGRAPixel_d  *bgra );

GANDALF_API Gan_Bool gan_image_convert_pixel ( Gan_Pixel *inpix,
                                   Gan_ImageFormat format, Gan_Type type,
                                   Gan_Pixel *outpix, int *error_code );
GANDALF_API double gan_image_convert_scale ( Gan_Type gtFromType, Gan_Type gtToType );
GANDALF_API Gan_Bool gan_image_offset_pixel_q ( Gan_Pixel *pixel, double offset,
                                    Gan_Pixel *offset_pixel );
GANDALF_API Gan_Bool gan_image_scale_pixel_q ( Gan_Pixel *pixel, double scale,
                                   Gan_Pixel *scaled_pixel );
GANDALF_API Gan_Bool gan_image_divide_pixel_q ( Gan_Pixel *pixel, double scale,
                                    Gan_Pixel *scaled_pixel );
GANDALF_API Gan_Bool gan_image_fill_zero_pixel ( Gan_Pixel *pixel );
GANDALF_API const char *gan_image_format_string ( Gan_ImageFormat format );
GANDALF_API Gan_ImageFormat gan_image_format_with_alpha ( Gan_ImageFormat format );
GANDALF_API Gan_ImageFormat gan_image_format_without_alpha ( Gan_ImageFormat format );
GANDALF_API unsigned int gan_image_bits_per_pixel ( Gan_ImageFormat format, Gan_Type type );

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert RGB 8-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8  gan_pixel_rgbui8_to_yui8 ( const Gan_RGBPixel_ui8 *rgb );

/**
 * \brief Macro: Convert RGB 8-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16 gan_pixel_rgbui8_to_yui16 ( const Gan_RGBPixel_ui8 *rgb );

/**
 * \brief Macro: Convert RGB 8-bit pixel to grey-level 32-bit pixel.
 */
GANDALF_API gan_uint32  gan_pixel_rgbui8_to_yui32   ( const Gan_RGBPixel_ui8 *rgb );

/**
 * \brief Macro: Convert RGB 16-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8   gan_pixel_rgbui16_to_yui8   ( const Gan_RGBPixel_ui16 *rgb );

/**
 * \brief Macro: Convert RGB 16-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16  gan_pixel_rgbui16_to_yui16  ( const Gan_RGBPixel_ui16 *rgb );

/**
 * \brief Macro: Convert RGB 32-bit pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_rgbui32_to_yf32   ( const Gan_RGBPixel_ui32 *rgb );

/**
 * \brief Macro: Convert RGB 32-bit float pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_rgbf32_to_yf32    ( const Gan_RGBPixel_f32  *rgb );

/**
 * \brief Macro: Convert RGB 64-bit float pixel to grey-level 64-bit float pixel.
 */
GANDALF_API gan_float64 gan_pixel_rgbf64_to_yf64    ( const Gan_RGBPixel_f64  *rgb );

/**
 * \brief Macro: Convert RGBA 8-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8   gan_pixel_rgbaui8_to_yui8   ( const Gan_RGBAPixel_ui8 *rgba );

/**
 * \brief Macro: Convert RGBA 8-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16  gan_pixel_rgbaui8_to_yui16  ( const Gan_RGBAPixel_ui8 *rgba );

/**
 * \brief Macro: Convert RGBA 8-bit pixel to grey-level 32-bit pixel.
 */
GANDALF_API gan_uint32  gan_pixel_rgbaui8_to_yui32  ( const Gan_RGBAPixel_ui8 *rgba );

/**
 * \brief Macro: Convert RGBA 16-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8   gan_pixel_rgbaui16_to_yui8  ( const Gan_RGBAPixel_ui16 *rgba );

/**
 * \brief Macro: Convert RGBA 16-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16  gan_pixel_rgbaui16_to_yui16 ( const Gan_RGBAPixel_ui16 *rgba );

/**
 * \brief Macro: Convert RGBA 32-bit pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_rgbaui32_to_yf32  ( const Gan_RGBAPixel_ui32 *rgba );

/**
 * \brief Macro: Convert RGBA 32-bit float pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_rgbaf32_to_yf32   ( const Gan_RGBAPixel_f32  *rgba );

/**
 * \brief Macro: Convert RGBA 64-bit float pixel to grey-level 64-bit float pixel.
 */
GANDALF_API gan_float64 gan_pixel_rgbaf64_to_yf64   ( const Gan_RGBAPixel_f64  *rgba );

/**
 * \brief Macro: Convert BGR 8-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8  gan_pixel_bgrui8_to_yui8 ( const Gan_BGRPixel_ui8 *bgr );

/**
 * \brief Macro: Convert BGR 8-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16 gan_pixel_bgrui8_to_yui16 ( const Gan_BGRPixel_ui8 *bgr );

/**
 * \brief Macro: Convert BGR 8-bit pixel to grey-level 32-bit pixel.
 */
GANDALF_API gan_uint32  gan_pixel_bgrui8_to_yui32   ( const Gan_BGRPixel_ui8 *bgr );

/**
 * \brief Macro: Convert BGR 16-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8   gan_pixel_bgrui16_to_yui8   ( const Gan_BGRPixel_ui16 *bgr );

/**
 * \brief Macro: Convert BGR 16-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16  gan_pixel_bgrui16_to_yui16  ( const Gan_BGRPixel_ui16 *bgr );

/**
 * \brief Macro: Convert BGR 32-bit pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_bgrui32_to_yf32   ( const Gan_BGRPixel_ui32 *bgr );

/**
 * \brief Macro: Convert BGR 32-bit float pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_bgrf32_to_yf32    ( const Gan_BGRPixel_f32  *bgr );

/**
 * \brief Macro: Convert BGR 64-bit float pixel to grey-level 64-bit float pixel.
 */
GANDALF_API gan_float64 gan_pixel_bgrf64_to_yf64    ( const Gan_BGRPixel_f64  *bgr );

/**
 * \brief Macro: Convert BGRA 8-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8   gan_pixel_bgraui8_to_yui8   ( const Gan_BGRAPixel_ui8 *bgra );

/**
 * \brief Macro: Convert BGRA 8-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16  gan_pixel_bgraui8_to_yui16  ( const Gan_BGRAPixel_ui8 *bgra );

/**
 * \brief Macro: Convert BGRA 8-bit pixel to grey-level 32-bit pixel.
 */
GANDALF_API gan_uint32  gan_pixel_bgraui8_to_yui32  ( const Gan_BGRAPixel_ui8 *bgra );

/**
 * \brief Macro: Convert BGRA 16-bit pixel to grey-level 8-bit pixel.
 */
GANDALF_API gan_uint8   gan_pixel_bgraui16_to_yui8  ( const Gan_BGRAPixel_ui16 *bgra );

/**
 * \brief Macro: Convert BGRA 16-bit pixel to grey-level 16-bit pixel.
 */
GANDALF_API gan_uint16  gan_pixel_bgraui16_to_yui16 ( const Gan_BGRAPixel_ui16 *bgra );

/**
 * \brief Macro: Convert BGRA 32-bit pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_bgraui32_to_yf32  ( const Gan_BGRAPixel_ui32 *bgra );

/**
 * \brief Macro: Convert BGRA 32-bit float pixel to grey-level 32-bit float pixel.
 */
GANDALF_API gan_float32 gan_pixel_bgraf32_to_yf32   ( const Gan_BGRAPixel_f32  *bgra );

/**
 * \brief Macro: Convert BGRA 64-bit float pixel to grey-level 64-bit float pixel.
 */
GANDALF_API gan_float64 gan_pixel_bgraf64_to_yf64   ( const Gan_BGRAPixel_f64  *bgra );
#else
#if (SIZEOF_CHAR == 1 && SIZEOF_SHORT == 2 && SIZEOF_INT == 4 && SIZEOF_DOUBLE == 8)
#define gan_pixel_rgbui8_to_yui8(rgbpix) gan_pixel_rgbuc_to_yuc(rgbpix)
#define gan_pixel_rgbui8_to_yui16(rgbpix) gan_pixel_rgbuc_to_yus(rgbpix)
#define gan_pixel_rgbui8_to_yui32(rgbpix) gan_pixel_rgbuc_to_yui(rgbpix)
#define gan_pixel_rgbui16_to_yui8(rgbpix) gan_pixel_rgbus_to_yuc(rgbpix)
#define gan_pixel_rgbui16_to_yui16(rgbpix) gan_pixel_rgbus_to_yus(rgbpix)
#define gan_pixel_rgbui32_to_yf32(rgbpix) gan_pixel_rgbui_to_yf(rgbpix)
#define gan_pixel_rgbf32_to_yf32(rgbpix) gan_pixel_rgbf_to_yf(rgbpix)
#define gan_pixel_rgbf64_to_yf64(rgbpix) gan_pixel_rgbd_to_yd(rgbpix)
#define gan_pixel_rgbaui8_to_yui8(rgbpix) gan_pixel_rgbauc_to_yuc(rgbpix)
#define gan_pixel_rgbaui8_to_yui16(rgbpix) gan_pixel_rgbauc_to_yus(rgbpix)
#define gan_pixel_rgbaui8_to_yui32(rgbpix) gan_pixel_rgbauc_to_yui(rgbpix)
#define gan_pixel_rgbaui16_to_yui8(rgbpix) gan_pixel_rgbaus_to_yuc(rgbpix)
#define gan_pixel_rgbaui16_to_yui16(rgbpix) gan_pixel_rgbaus_to_yus(rgbpix)
#define gan_pixel_rgbaui32_to_yf32(rgbpix) gan_pixel_rgbaui_to_yf(rgbpix)
#define gan_pixel_rgbaf32_to_yf32(rgbpix) gan_pixel_rgbaf_to_yf(rgbpix)
#define gan_pixel_rgbaf64_to_yf64(rgbpix) gan_pixel_rgbad_to_yd(rgbpix)
#define gan_pixel_bgrui8_to_yui8(bgrpix) gan_pixel_bgruc_to_yuc(bgrpix)
#define gan_pixel_bgrui8_to_yui16(bgrpix) gan_pixel_bgruc_to_yus(bgrpix)
#define gan_pixel_bgrui8_to_yui32(bgrpix) gan_pixel_bgruc_to_yui(bgrpix)
#define gan_pixel_bgrui16_to_yui8(bgrpix) gan_pixel_bgrus_to_yuc(bgrpix)
#define gan_pixel_bgrui16_to_yui16(bgrpix) gan_pixel_bgrus_to_yus(bgrpix)
#define gan_pixel_bgrui32_to_yf32(bgrpix) gan_pixel_bgrui_to_yf(bgrpix)
#define gan_pixel_bgrf32_to_yf32(bgrpix) gan_pixel_bgrf_to_yf(bgrpix)
#define gan_pixel_bgrf64_to_yf64(bgrpix) gan_pixel_bgrd_to_yd(bgrpix)
#define gan_pixel_bgraui8_to_yui8(bgrpix) gan_pixel_bgrauc_to_yuc(bgrpix)
#define gan_pixel_bgraui8_to_yui16(bgrpix) gan_pixel_bgrauc_to_yus(bgrpix)
#define gan_pixel_bgraui8_to_yui32(bgrpix) gan_pixel_bgrauc_to_yui(bgrpix)
#define gan_pixel_bgraui16_to_yui8(bgrpix) gan_pixel_bgraus_to_yuc(bgrpix)
#define gan_pixel_bgraui16_to_yui16(bgrpix) gan_pixel_bgraus_to_yus(bgrpix)
#define gan_pixel_bgraui32_to_yf32(bgrpix) gan_pixel_bgraui_to_yf(bgrpix)
#define gan_pixel_bgraf32_to_yf32(bgrpix) gan_pixel_bgraf_to_yf(bgrpix)
#define gan_pixel_bgraf64_to_yf64(bgrpix) gan_pixel_bgrad_to_yd(bgrpix)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c short to \c unsigned \c char type.
 */
GANDALF_API unsigned char gan_pixel_us_to_uc ( unsigned short x );

/**
 * \brief Macro: Convert a pixel field from \c unsigned \c 16-bit to \c unsigned \c 8-bit type.
 */
GANDALF_API gan_uint8 gan_pixel_ui16_to_ui8 ( gan_uint16 x );
#else
#if (SIZEOF_SHORT-SIZEOF_CHAR == 1)
#define gan_pixel_us_to_uc(x) ((unsigned char)((x) / 0x101))
#define gan_pixel_ui16_to_ui8(x) gan_pixel_us_to_uc(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_SHORT-SIZEOF_CHAR == 1) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c int to \c unsigned \c char type.
 */
GANDALF_API unsigned char gan_pixel_ui_to_uc ( unsigned x );

/**
 * \brief Macro: Convert a pixel field from 32-bit unsigned integer to 8-bit unsigned integer type.
 */
GANDALF_API gan_uint8 gan_pixel_ui32_to_ui8 ( gan_uint32 x );
#else
#if (SIZEOF_INT-SIZEOF_CHAR == 3)
#define gan_pixel_ui_to_uc(x) ((unsigned char)((x) / 0x1010101))
#define gan_pixel_ui32_to_ui8(x) gan_pixel_ui_to_uc(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_INT-SIZEOF_CHAR == 3) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c float to \c unsigned \c char type.
 *
 * Overflow is handled.
 */
GANDALF_API unsigned char gan_pixel_f_to_uc ( float x );

/**
 * \brief Macro: Convert a pixel field from 32-bit float to 8-bit unsigned integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_uint8 gan_pixel_f32_to_ui8 ( gan_float32 x );
#else
#define gan_pixel_f_to_uc(x) \
   (((x) < 0.0F) ? 0\
                 : (((x) < 1.0F) ? (unsigned char) ((x)*(GAN_UCHAR_MAXF+1.0F))\
                                 : (unsigned char) UCHAR_MAX))
#if (SIZEOF_FLOAT == 4)
#define gan_pixel_f32_to_ui8(x) gan_pixel_f_to_uc(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c double to \c unsigned \c char type.
 *
 * Overflow is handled.
 */
GANDALF_API unsigned char gan_pixel_d_to_uc ( double x );

/**
 * \brief Macro: Convert a pixel field from 64-bit float to 8-bit unsigned integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_uint8 gan_pixel_f64_to_ui8 ( gan_float64 x );
#else
#define gan_pixel_d_to_uc(x) \
   (((x) < 0.0) ? 0\
                : (((x) < 1.0) ? (unsigned char) ((x)*(GAN_UCHAR_MAXD+1.0)) \
                               : (unsigned char) UCHAR_MAX))
#if (SIZEOF_DOUBLE == 8)
#define gan_pixel_f64_to_ui8(x) gan_pixel_d_to_uc(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c char to \c unsigned \c short type.
 */
GANDALF_API unsigned short gan_pixel_uc_to_us ( unsigned char x );

/**
 * \brief Macro: Convert a pixel field from 8-bit unsigned integer to 16-bit unsigned integer type.
 */
GANDALF_API gan_uint16 gan_pixel_ui8_to_ui16 ( gan_uint8 x );
#else
#if (SIZEOF_SHORT-SIZEOF_CHAR == 1)
#define gan_pixel_uc_to_us(x) ((unsigned short) ((x) * 0x101))
#define gan_pixel_ui8_to_ui16(x) gan_pixel_uc_to_us(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_SHORT-SIZEOF_CHAR == 1) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c int to \c unsigned \c short type.
 */
GANDALF_API unsigned short gan_pixel_ui_to_us ( unsigned x );

/**
 * \brief Macro: Convert a pixel field from 32-bit unsigned integer to 16-bit unsigned integer type.
 */
GANDALF_API gan_uint16 gan_pixel_ui32_to_ui16 ( gan_uint32 x );
#else
#if (SIZEOF_INT-SIZEOF_SHORT == 2)
#define gan_pixel_ui_to_us(x) ((unsigned short)((x) / 0x10001))
#define gan_pixel_ui32_to_ui16(x) gan_pixel_ui_to_us(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_INT-SIZEOF_SHORT == 2) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c int to \c short type.
 */
GANDALF_API short gan_pixel_i_to_s ( int x );

/**
 * \brief Macro: Convert a pixel field from 32-bit to 16-bit signed integer type.
 */
GANDALF_API gan_int16 gan_pixel_i32_to_i16 ( gan_int32 x );
#else
#if (SIZEOF_INT-SIZEOF_SHORT == 2)
#define gan_pixel_i_to_s(x) ((short)((x) / 0x10002))
#define gan_pixel_i32_to_i16(x) gan_pixel_i_to_s(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_INT-SIZEOF_SHORT == 2) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c float to \c unsigned \c short type.
 *
 * Overflow is handled.
 */
GANDALF_API unsigned short gan_pixel_f_to_us ( float x );

/**
 * \brief Macro: Convert a pixel field from 32-bit float to 16-bit unsigned integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_int16 gan_pixel_f32_to_ui16 ( gan_float32 x );
#else
#define gan_pixel_f_to_us(x) \
   (((x) < 0.0F) ? 0\
                 : (((x) < 1.0F) ? (unsigned short)((x)*(GAN_USHRT_MAXF+1.0F))\
                                 : (unsigned short)USHRT_MAX))
#if (SIZEOF_FLOAT == 4 && SIZEOF_SHORT == 2)
#define gan_pixel_f32_to_ui16(x) gan_pixel_f_to_us(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c double to \c unsigned \c short type.
 *
 * Overflow is handled.
 */
GANDALF_API unsigned short gan_pixel_d_to_us ( double x );

/**
 * \brief Macro: Convert a pixel field from 64-bit float to 16-bit unsigned integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_int16 gan_pixel_f64_to_ui16 ( gan_float64 x );
#else
#define gan_pixel_d_to_us(x) \
   (((x) < 0.0) ? 0\
                : (((x) < 1.0 ) ? (unsigned short) ((x)*(GAN_USHRT_MAXD+1.0)) \
                                : (unsigned short) USHRT_MAX))
#if (SIZEOF_DOUBLE == 8 && SIZEOF_SHORT == 2)
#define gan_pixel_f64_to_ui16(x) gan_pixel_d_to_us(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c char to \c unsigned \c int type.
 */
GANDALF_API unsigned int gan_pixel_uc_to_ui ( unsigned char x );

/**
 * \brief Macro: Convert a pixel field from 8-bit unsigned integer to 32-bit unsigned integer type.
 */
GANDALF_API gan_uint32 gan_pixel_ui8_to_ui32 ( gan_uint8 x );
#else
#if (SIZEOF_INT-SIZEOF_CHAR == 3)
#define gan_pixel_uc_to_ui(x) ((unsigned) ((x) * 0x1010101))
#define gan_pixel_ui8_to_ui32(x) gan_pixel_uc_to_ui(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_INT-SIZEOF_CHAR == 3) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c short to \c unsigned \c int type.
 */
GANDALF_API unsigned int gan_pixel_us_to_ui ( unsigned short x );

/**
 * \brief Macro: Convert a pixel field from 16-bit unsigned integer to 32-bit unsigned integer type.
 */
GANDALF_API gan_uint32 gan_pixel_ui16_to_ui32 ( gan_uint16 x );
#else
#if (SIZEOF_INT-SIZEOF_SHORT == 2)
#define gan_pixel_us_to_ui(x) ((unsigned) ((x) * 0x10001))
#define gan_pixel_ui16_to_ui32(x) gan_pixel_us_to_ui(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_INT-SIZEOF_SHORT == 2) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c short to \c int type.
 */
GANDALF_API int gan_pixel_s_to_i ( short x );

/**
 * \brief Macro: Convert a pixel field from 16-bit to 32-bit signed integer type.
 */
GANDALF_API gan_int32 gan_pixel_i16_to_i32 ( gan_int16 x );
#else
#if (SIZEOF_INT-SIZEOF_SHORT == 2)
#define gan_pixel_s_to_i(x) ((int) ((x) * 0x10002))
#define gan_pixel_i16_to_i32(x) gan_pixel_s_to_i(x)
#else
#error "Illegal sizes"
#endif /* #if (SIZEOF_INT-SIZEOF_SHORT == 2) */
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c float to \c unsigned \c int type.
 *
 * Overflow is handled.
 */
GANDALF_API unsigned int gan_pixel_f_to_ui ( float x );

/**
 * \brief Macro: Convert a pixel field from 32-bit float to 32-bit unsigned integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_uint32 gan_pixel_f32_to_ui32 ( gan_float32 x );
#else
#define gan_pixel_f_to_ui(x) \
   (((x) < 0.0F) ? 0\
                 : (((x) < 1.0F) ? (unsigned) ((x)*(GAN_UINT_MAXF+1.0F)) \
                                 : (unsigned) UINT_MAX))

#if (SIZEOF_FLOAT == 4 && SIZEOF_INT == 4)
#define gan_pixel_f32_to_ui32(x) gan_pixel_f_to_ui(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c double to \c unsigned \c int type.
 *
 * Overflow is handled.
 */
GANDALF_API unsigned int gan_pixel_d_to_ui ( double x );

/**
 * \brief Macro: Convert a pixel field from 64-bit float to 32-bit unsigned integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_uint32 gan_pixel_f64_to_ui32 ( gan_float64 x );
#else
#define gan_pixel_d_to_ui(x) \
   (((x) < 0.0) ? 0\
                : (((x) < 1.0) ? (unsigned) ((x)*(GAN_UINT_MAXD+1.0)) \
                               : (unsigned) UINT_MAX))
#if (SIZEOF_DOUBLE == 8 && SIZEOF_INT == 4)
#define gan_pixel_f64_to_ui32(x) gan_pixel_d_to_ui(x)
#endif
#endif

extern GANDALF_API float lookup_table_8bit[];

#ifdef GAN_GENERATE_DOCUMENTATION
/*
 * \brief Macro: Convert a pixel field from \c unsigned \c char to \c float type.
 */
GANDALF_API float gan_pixel_uc_to_f ( unsigned char x );

/*
 * \brief Macro: Convert a pixel field from 8-bit unsigned integer to 32-bit float type.
 */
GANDALF_API gan_float32 gan_pixel_ui8_to_f32 ( gan_uint8 x );
#else
#define gan_pixel_uc_to_f(x) (lookup_table_8bit[x])
#if (SIZEOF_FLOAT == 4 && SIZEOF_CHAR == 1)
#define gan_pixel_ui8_to_f32(x) gan_pixel_uc_to_f(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c short to \c float type.
 */
GANDALF_API float gan_pixel_us_to_f ( unsigned short x );

/**
 * \brief Macro: Convert a pixel field from 16-bit unsigned integer to 32-bit float type.
 */
GANDALF_API gan_float32 gan_pixel_ui16_to_f32 ( gan_uint16 x );
#else
#define gan_pixel_us_to_f(x) ((float)(x)/GAN_USHRT_MAXF)
#if (SIZEOF_FLOAT == 4 && SIZEOF_SHORT == 2)
#define gan_pixel_ui16_to_f32(x) gan_pixel_us_to_f(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c int to \c float type.
 */
GANDALF_API float gan_pixel_ui_to_f ( unsigned int x );

/**
 * \brief Macro: Convert a pixel field from 32-bit unsigned integer to 32-bit float type.
 */
GANDALF_API gan_float32 gan_pixel_ui32_to_f32 ( gan_uint32 x );
#else
#define gan_pixel_ui_to_f(x) ((float)(x)/GAN_UINT_MAXF)
#if (SIZEOF_FLOAT == 4 && SIZEOF_INT == 4)
#define gan_pixel_ui32_to_f32(x) gan_pixel_ui_to_f(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c char to \c double type.
 */
GANDALF_API double gan_pixel_uc_to_d ( unsigned char x );

/**
 * \brief Macro: Convert a pixel field from 8-bit unsigned integer to 64-bit float type.
 */
GANDALF_API gan_float64 gan_pixel_ui8_to_f64 ( gan_uint8 x );
#else
#define gan_pixel_uc_to_d(x) ((double)(x)/GAN_UCHAR_MAXD)
#if (SIZEOF_DOUBLE == 8 && SIZEOF_CHAR == 1)
#define gan_pixel_ui8_to_f64(x) gan_pixel_uc_to_d(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c short to \c double type.
 */
GANDALF_API double gan_pixel_us_to_d ( unsigned short x );

/**
 * \brief Macro: Convert a pixel field from 16-bit unsigned integer to 64-bit float type.
 */
GANDALF_API gan_float64 gan_pixel_ui16_to_f64 ( gan_uint16 x );
#else
#define gan_pixel_us_to_d(x) ((double)(x)/GAN_USHRT_MAXD)
#if (SIZEOF_DOUBLE == 8 && SIZEOF_SHORT == 2)
#define gan_pixel_ui16_to_f64(x) gan_pixel_us_to_d(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c unsigned \c int to \c double type.
 */
GANDALF_API double gan_pixel_ui_to_d ( unsigned int x );

/**
 * \brief Macro: Convert a pixel field from 32-bit unsigned integer to 64-bit float type.
 */
GANDALF_API gan_float64 gan_pixel_ui32_to_f64 ( gan_uint32 x );
#else
#define gan_pixel_ui_to_d(x) ((double)(x)/GAN_UINT_MAXD)
#if (SIZEOF_DOUBLE == 8 && SIZEOF_INT == 4)
#define gan_pixel_ui32_to_f64(x) gan_pixel_ui_to_d(x)
#endif
#endif
   
#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c float to \c int type.
 *
 * Overflow is handled.
 */
GANDALF_API int gan_pixel_f_to_i ( float x );

/**
 * \brief Macro: Convert a pixel field from 32-bit float to 32-bit signed integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_int32 gan_pixel_f32_to_i32 ( gan_float32 x );
#else
#define gan_pixel_f_to_i(x) \
   (((x) < -1.0F) ? INT_MIN\
                 : (((x) < 1.0F) ? (int) ((x)*(GAN_INT_MAXF+1.0F)) \
                                 : INT_MAX))
#if (SIZEOF_FLOAT == 4 && SIZEOF_INT == 4)
#define gan_pixel_f32_to_i32(x) gan_pixel_f_to_i(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c double to \c int type.
 *
 * Overflow is handled.
 */
GANDALF_API int gan_pixel_d_to_i ( double x );

/**
 * \brief Macro: Convert a pixel field from 64-bit float to 32-bit signed integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_int32 gan_pixel_f64_to_i32 ( gan_float64 x );
#else
#define gan_pixel_d_to_i(x) \
   (((x) < -1.0) ? INT_MIN\
                : (((x) < 1.0) ? (int) ((x)*(GAN_INT_MAXD+1.0)) \
                               : INT_MAX))
#if (SIZEOF_DOUBLE == 8 && SIZEOF_INT == 4)
#define gan_pixel_f64_to_i32(x) gan_pixel_d_to_i(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c float to \c short type.
 *
 * Overflow is handled.
 */
GANDALF_API short gan_pixel_f_to_s ( float x );

/**
 * \brief Macro: Convert a pixel field from 32-bit float to 16-bit signed integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_int16 gan_pixel_f32_to_i16 ( gan_float32 x );
#else
#define gan_pixel_f_to_s(x) \
   (((x) < -1.0F) ? SHRT_MIN\
                 : (((x) < 1.0F) ? (int) ((x)*(GAN_SHRT_MAXF+1.0F)) \
                                 : SHRT_MAX))
#if (SIZEOF_FLOAT == 4 && SIZEOF_SHORT == 2)
#define gan_pixel_f32_to_i16(x) gan_pixel_f_to_s(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c double to \c short type.
 *
 * Overflow is handled.
 */
GANDALF_API short gan_pixel_d_to_s ( double x );

/**
 * \brief Macro: Convert a pixel field from 64-bit float to 16-bit signed integer type.
 *
 * Overflow is handled.
 */
GANDALF_API gan_int16 gan_pixel_f64_to_i16 ( gan_float64 x );
#else
#define gan_pixel_d_to_s(x) \
   (((x) < -1.0) ? SHRT_MIN\
                : (((x) < 1.0) ? (int) ((x)*(GAN_SHRT_MAXD+1.0)) \
                               : SHRT_MAX))
#if (SIZEOF_DOUBLE == 8 && SIZEOF_SHORT == 2)
#define gan_pixel_f64_to_i16(x) gan_pixel_d_to_s(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c short to \c float type.
 */
GANDALF_API float gan_pixel_s_to_f ( short x );

/**
 * \brief Macro: Convert a pixel field from 16-bit signed integer to 32-bit float type.
 */
GANDALF_API gan_float32 gan_pixel_i16_to_f32 ( gan_int16 x );
#else
#define gan_pixel_s_to_f(x) ((float)(x)/GAN_SHRT_MAXF)
#if (SIZEOF_FLOAT == 4 && SIZEOF_SHORT == 2)
#define gan_pixel_i16_to_f32(x) gan_pixel_s_to_f(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c short to \c double type.
 */
GANDALF_API double gan_pixel_s_to_d ( short x );

/**
 * \brief Macro: Convert a pixel field from 16-bit signed integer to 64-bit float type.
 */
GANDALF_API gan_float64 gan_pixel_i16_to_f64 ( gan_int16 x );
#else
#define gan_pixel_s_to_d(x) ((double)(x)/GAN_SHRT_MAXD)
#if (SIZEOF_DOUBLE == 8 && SIZEOF_SHORT == 2)
#define gan_pixel_i16_to_f64(x) gan_pixel_s_to_d(x)
#endif
#endif
   
#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c int to \c float type.
 */
GANDALF_API float gan_pixel_i_to_f ( int x );

/**
 * \brief Macro: Convert a pixel field from 32-bit signed integer to 32-bit float type.
 */
GANDALF_API gan_float32 gan_pixel_i32_to_f32 ( gan_int32 x );
#else
#define gan_pixel_i_to_f(x) ((float)(x)/GAN_INT_MAXF)
#if (SIZEOF_FLOAT == 4 && SIZEOF_SHORT == 2)
#define gan_pixel_i32_to_f32(x) gan_pixel_i_to_f(x)
#endif
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
/**
 * \brief Macro: Convert a pixel field from \c int to \c double type.
 */
GANDALF_API double gan_pixel_i_to_d ( int x );

/**
 * \brief Macro: Convert a pixel field from 32-bit signed integer to 64-bit float type.
 */
GANDALF_API gan_float64 gan_pixel_i32_to_f64 ( gan_int32 x );
#else
#define gan_pixel_i_to_d(x) ((double)(x)/GAN_INT_MAXD)
#if (SIZEOF_DOUBLE == 8 && SIZEOF_SHORT == 2)
#define gan_pixel_i32_to_f64(x) gan_pixel_i_to_d(x)
#endif
#endif

// other hard-wired 8 bit conversions
#if (SIZEOF_CHAR == 1)

/// Macro: Convert a pixel field from \c float to unsigned 8 bit integer type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API int gan_pixel_f_to_ui8 ( float x );
#else
#define gan_pixel_f_to_ui8(x) gan_pixel_f_to_uc(x)
#endif

/// Macro: Convert a pixel field from \c double to unsigned 8 bit integer type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API int gan_pixel_d_to_ui8 ( double x );
#else
#define gan_pixel_d_to_ui8(x) gan_pixel_d_to_uc(x)
#endif

/// Macro: Convert a pixel field from unsigned 8 bit integer to \c float type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_pixel_ui8_to_f ( gan_uint8 x );
#else
#define gan_pixel_ui8_to_f(x) gan_pixel_uc_to_f(x)
#endif

/// Macro: Convert a pixel field from unsigned 8 bit integer to \c double type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_pixel_ui8_to_d ( gan_uint8 x );
#else
#define gan_pixel_ui8_to_d(x) gan_pixel_uc_to_d(x)
#endif

#endif /* (SIZEOF_CHAR == 1) */

// other hard-wired 16 bit conversions
#if (SIZEOF_SHORT == 2)

/// Macro: Convert a pixel field from \c float to unsigned 16 bit integer type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API int gan_pixel_f_to_ui16 ( float x );
#else
#define gan_pixel_f_to_ui16(x) gan_pixel_f_to_us(x)
#endif

/// Macro: Convert a pixel field from \c double to unsigned 16 bit integer type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API int gan_pixel_d_to_ui16 ( double x );
#else
#define gan_pixel_d_to_ui16(x) gan_pixel_d_to_us(x)
#endif

/// Macro: Convert a pixel field from unsigned 16 bit integer to \c float type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_pixel_ui16_to_f ( gan_uint16 x );
#else
#define gan_pixel_ui16_to_f(x) gan_pixel_us_to_f(x)
#endif

/// Macro: Convert a pixel field from unsigned 16 bit integer to \c double type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_pixel_ui16_to_d ( gan_uint16 x );
#else
#define gan_pixel_ui16_to_d(x) gan_pixel_us_to_d(x)
#endif

#endif /* (SIZEOF_SHORT == 2) */

// hard-wired 32 bit conversions
#if (SIZEOF_INT == 4)

/// Macro: Convert a pixel field from \c float to unsigned 32 bit integer type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API int gan_pixel_f_to_ui32 ( float x );
#else
#define gan_pixel_f_to_ui32(x) gan_pixel_f_to_ui(x)
#endif

/// Macro: Convert a pixel field from \c double to unsigned 32 bit integer type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API int gan_pixel_d_to_ui32 ( double x );
#else
#define gan_pixel_d_to_ui32(x) gan_pixel_d_to_ui(x)
#endif

/// Macro: Convert a pixel field from unsigned 32 bit integer to \c float type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API float gan_pixel_ui32_to_f ( gan_uint32 x );
#else
#define gan_pixel_ui32_to_f(x) gan_pixel_ui_to_f(x)
#endif

/// Macro: Convert a pixel field from unsigned 32 bit integer to \c double type.
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API double gan_pixel_ui32_to_d ( gan_uint32 x );
#else
#define gan_pixel_ui32_to_d(x) gan_pixel_ui_to_d(x)
#endif

#endif /* (SIZEOF_INT == 4) */

/**
 * \brief Macro: Convert pixel.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Converts \a inpix to the given \a format and \a type, producing an ouput
 * pixel in \a outpix.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_convert_pixel_q ( Gan_Pixel *inpix,
                                     Gan_ImageFormat format, Gan_Type type,
                                     Gan_Pixel *outpix );
#else
#define gan_image_convert_pixel_q(inpix,format,type,outpix) \
           gan_image_convert_pixel(inpix,format,type,outpix,NULL)
#endif

/**
 * \brief Macro: Convert pixel in-place.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Converts \a pix to the given \a format and \a type, overwriting \a pix with
 * the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_convert_pixel_i ( Gan_Pixel *pix,
                                     Gan_ImageFormat format, Gan_Type type );
#else
#define gan_image_convert_pixel_i(pix,format,type) \
           gan_image_convert_pixel_q(pix,format,type,pix)
#endif

/**
 * \brief Macro: Offset pixel in-place.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Adds all the channels of the given \a pixel to the given \a offset
 * factor, overwriting \a pixel with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_offset_pixel_i ( Gan_Pixel *pixel, double offset );
#else
#define gan_image_offset_pixel_i(pix,o) gan_image_offset_pixel_q(pix,o,pix)
#endif

/**
 * \brief Macro: Scale pixel in-place.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Multiplies all the channels of the given \a pixel by the given \a scale
 * factor, overwriting \a pixel with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_scale_pixel_i ( Gan_Pixel *pixel, double scale );
#else
#define gan_image_scale_pixel_i(pix,s) gan_image_scale_pixel_q(pix,s,pix)
#endif

/**
 * \brief Macro: Divide pixel by scalar pixel in-place.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Divides all the channels of the given \a pixel by the given \a scale
 * factor, overwriting \a pixel with the result.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_divide_pixel_i ( Gan_Pixel *pixel, double scale );
#else
#define gan_image_divide_pixel_i(pix,s) gan_image_divide_pixel_q(pix,s,pix)
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

#endif /* #ifndef _GAN_PIXEL_H */
