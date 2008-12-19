/**
 * File:          $RCSfile: image_defs.h,v $
 * Module:        Image definitions and general functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.65 $
 * Last edited:   $Date: 2006/09/15 20:43:37 $
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

#ifndef _GAN_IMAGE_DEFS_H
#define _GAN_IMAGE_DEFS_H

#include <stdlib.h>
#include <gandalf/image/pixel.h>
#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/// structure definition for image
typedef struct Gan_Image
{
   /// format of image: grey-level, RGB colour etc.
   Gan_ImageFormat format;

   /// type of pixel values: unsigned char, float etc.
   Gan_Type type;

   /// image dimensions
   unsigned long height, width;

   /// stride of image, i.e. number of bytes in memory between the start of
   /// each row; stride >= width*(size of pixel)
   unsigned long stride;

   /// generic pointer to pixel data, as a byte pointer so that we can do
   /// pointer arithmetic in bytes with it
   unsigned char *pix_data_ptr;

   /// allocated size of image data in bytes
   size_t pix_data_size;

   /// flag indicating whether image data was dynamically allocated
   Gan_Bool pix_data_alloc;

   /// pointers to start of each row
   union
   {
      /// grey level
      union
      {
         unsigned char  **uc;
         short          **s;
         unsigned short **us;
         int            **i;
         unsigned int   **ui;
         float          **f;
         double         **d;
         Gan_BitWord    **b;
         void          ***p;
         Gan_YXPixel_ui10 **ui10;
         Gan_YXPixel_ui12 **ui12;
      } gl;

      /// grey level with alpha channel
      union
      {
         Gan_GLAPixel_uc **uc;
         Gan_GLAPixel_s  **s;
         Gan_GLAPixel_us **us;
         Gan_GLAPixel_i  **i;
         Gan_GLAPixel_ui **ui;
         Gan_GLAPixel_f  **f;
         Gan_GLAPixel_d  **d;
      } gla;

      /// RGB colour
      union
      {
         Gan_RGBPixel_uc **uc;
         Gan_RGBPixel_s  **s;
         Gan_RGBPixel_us **us;
         Gan_RGBPixel_i  **i;
         Gan_RGBPixel_ui **ui;
         Gan_RGBPixel_f  **f;
         Gan_RGBPixel_d  **d;
      } rgb;

      /// RGB colour with alpha channel
      union
      {
         Gan_RGBAPixel_uc **uc;
         Gan_RGBAPixel_s  **s;
         Gan_RGBAPixel_us **us;
         Gan_RGBAPixel_i  **i;
         Gan_RGBAPixel_ui **ui;
         Gan_RGBAPixel_f  **f;
         Gan_RGBAPixel_d  **d;
         Gan_RGBAPixel_ui12 **ui12;
      } rgba;

      /// BGR colour
      union
      {
         Gan_BGRPixel_uc **uc;
         Gan_BGRPixel_s  **s;
         Gan_BGRPixel_us **us;
         Gan_BGRPixel_i  **i;
         Gan_BGRPixel_ui **ui;
         Gan_BGRPixel_f  **f;
         Gan_BGRPixel_d  **d;
      } bgr;

      /// BGR colour with alpha channel
      union
      {
         Gan_BGRAPixel_uc **uc;
         Gan_BGRAPixel_s  **s;
         Gan_BGRAPixel_us **us;
         Gan_BGRAPixel_i  **i;
         Gan_BGRAPixel_ui **ui;
         Gan_BGRAPixel_f  **f;
         Gan_BGRAPixel_d  **d;
      } bgra;

      /// 2D vector field
      union
      {
         Gan_Vector2_f **f;
         Gan_Vector2   **d;
         Gan_Vector2_s **s;
         Gan_Vector2_i **i;
      } vfield2D;

      /// 3D vector field
      union
      {
         Gan_Vector3_f **f;
         Gan_Vector3   **d;
         Gan_Vector3_s **s;
         Gan_Vector3_i **i;
      } vfield3D;

      /// RGBX data
      union
      {
         Gan_RGBXPixel_ui8   **ui8;
         Gan_RGBXPixel_ui10 **ui10;
      } rgbx;

      /// RGBA data with small alpha channel
      union
      {
         Gan_RGBASPixel_ui10 **ui10;
      } rgbas;

      /// YUV 4-4-4 with padding to a word boundary
      union
      {
         Gan_YUVX444Pixel_ui8 **ui8;
      } yuvx444;

      /// YUVA 4-4-4
      union
      {
         Gan_YUVA444Pixel_ui8 **ui8;
      } yuva444;

      /// YUV 4-2-2
      union
      {
         Gan_YUV422Pixel_ui8 **ui8; /* needs special treatment when iterating */
      } yuv422;
   } row_data;

   /// generic pointer to row pointer data
   void *row_data_ptr;

   /// allocated number of row pointers in bytes
   size_t row_data_size;

   /// array of bit arrays for binary images
   Gan_BitArray *ba;

   /// whether bit array was allocated
   Gan_Bool ba_alloc;

   /// user-defined offsets
   int offset_x, offset_y;

   /// flag indicating whether row pointer array was dynamically allocated
   Gan_Bool row_data_alloc;

   /// flag indicating whether image structure was dynamically allocated
   Gan_Bool struct_alloc;

   /// function to free image data, defaulting to free() if this field is NULL
   void (*data_free_func) (void *);

   /// function to free image
   void (*free_func) ( struct Gan_Image *img );

#ifndef NDEBUG   

   /// set image pixel for each format
   union
   {
      /// grey-level formats
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned row, unsigned col, unsigned char pix );
         Gan_Bool (*s)  ( struct Gan_Image *, unsigned row, unsigned col, short pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned row, unsigned col, unsigned short pix );
         Gan_Bool (*i)  ( struct Gan_Image *, unsigned row, unsigned col, int pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned row, unsigned col, unsigned int pix );
         Gan_Bool (*f)  ( struct Gan_Image *, unsigned row, unsigned col, float pix );
         Gan_Bool (*d)  ( struct Gan_Image *, unsigned row, unsigned col, double pix );
         Gan_Bool (*b)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_Bool pix );
         Gan_Bool (*p)  ( struct Gan_Image *, unsigned row, unsigned col, void *pix );
         Gan_Bool (*ui10)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_YXPixel_ui10  *pix );
         Gan_Bool (*ui12)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_YXPixel_ui12  *pix );
      } gl;

      /// grey-level formats with alpha channels
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_s *pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_i *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_ui *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_f *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_GLAPixel_d *pix );
      } gla;

      /// RGB colour formats
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_s *pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_i *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_ui *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_d *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBPixel_f *pix );
      } rgb;

      /// RGB colour formats with alpha channels
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_s *pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_i *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_ui *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_d *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_f *pix );
         Gan_Bool (*ui12) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBAPixel_ui12  *pix );
      } rgba;

      /// BGR colour formats
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_s *pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_i *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_ui *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_d *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRPixel_f *pix );
      } bgr;

      /// BGR colour formats with alpha channels
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_s *pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_i *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_ui *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_d *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_BGRAPixel_f *pix );
      } bgra;

      /// 2D vector field formats
      union
      {
         Gan_Bool (*f) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector2_f *pix );
         Gan_Bool (*d) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector2 *pix );
         Gan_Bool (*s) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector2_s *pix );
         Gan_Bool (*i) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector2_i *pix );
      } vfield2D;

      /// 3D vector field formats
      union
      {
         Gan_Bool (*f) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector3_f *pix );
         Gan_Bool (*d) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector3 *pix );
         Gan_Bool (*s) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector3_s *pix );
         Gan_Bool (*i) ( struct Gan_Image *, unsigned row, unsigned col, Gan_Vector3_i *pix );
      } vfield3D;

      /// RGBX data
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBXPixel_ui8  *pix );
         Gan_Bool (*ui10) ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBXPixel_ui10 *pix );
      } rgbx;

      /// RGBA data with small alpha channel
      union
      {
         Gan_Bool (*ui10)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_RGBASPixel_ui10  *pix );
      } rgbas;

      /// YUV 4-4-4 with padding to a word boundary
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_YUVX444Pixel_ui8  *pix );
      } yuvx444;

      /// YUVA 4-4-4
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_YUVA444Pixel_ui8  *pix );
      } yuva444;

      /// YUV 4-2-2
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, unsigned row, unsigned col, Gan_YUV422Pixel_ui8  *pix );
      } yuv422;
   } set_pix;

   /// get image pixel for each format
   union
   {
      /// grey-level formats
      union
      {
         unsigned char  (*uc) (const struct Gan_Image *, unsigned row, unsigned col);
         short          (*s)  (const struct Gan_Image *, unsigned row, unsigned col);
         unsigned short (*us) (const struct Gan_Image *, unsigned row, unsigned col);
         int            (*i)  (const struct Gan_Image *, unsigned row, unsigned col);
         unsigned int   (*ui) (const struct Gan_Image *, unsigned row, unsigned col);
         float          (*f)  (const struct Gan_Image *, unsigned row, unsigned col);
         double         (*d)  (const struct Gan_Image *, unsigned row, unsigned col);
         Gan_Bool       (*b)  (const struct Gan_Image *, unsigned row, unsigned col);
         void *         (*p)  (const struct Gan_Image *, unsigned row, unsigned col);
         Gan_YXPixel_ui10 (*ui10)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_YXPixel_ui12 (*ui12)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } gl;

      /// grey-level formats with alpha channels
      union
      {
         Gan_GLAPixel_uc (*uc) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_GLAPixel_s  (*s)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_GLAPixel_us (*us) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_GLAPixel_i  (*i)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_GLAPixel_ui (*ui) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_GLAPixel_f  (*f)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_GLAPixel_d  (*d)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } gla;

      /// RGB colour formats
      union
      {
         Gan_RGBPixel_uc (*uc) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBPixel_s  (*s)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBPixel_us (*us) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBPixel_i  (*i)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBPixel_ui (*ui) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBPixel_f  (*f)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBPixel_d  (*d)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } rgb;

      /// RGB colour formats with alpha channels
      union
      {
         Gan_RGBAPixel_uc (*uc) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_s  (*s)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_us (*us) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_i  (*i)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_ui (*ui) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_f  (*f)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_d  (*d)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBAPixel_ui12 (*ui12)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } rgba;

      /// BGR colour formats
      union
      {
         Gan_BGRPixel_uc (*uc) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRPixel_s  (*s)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRPixel_us (*us) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRPixel_i  (*i)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRPixel_ui (*ui) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRPixel_f  (*f)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRPixel_d  (*d)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } bgr;

      /// BGR colour formats with alpha channels
      union
      {
         Gan_BGRAPixel_uc (*uc) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRAPixel_s  (*s)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRAPixel_us (*us) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRAPixel_i  (*i)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRAPixel_ui (*ui) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRAPixel_f  (*f)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_BGRAPixel_d  (*d)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } bgra;

      /// 2D vector field formats
      union
      {
         Gan_Vector2_f (*f) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_Vector2   (*d) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_Vector2_s (*s) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_Vector2_i (*i) ( const struct Gan_Image *, unsigned row, unsigned col );
      } vfield2D;

      /// 3D vector field formats
      union
      {
         Gan_Vector3_f (*f) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_Vector3   (*d) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_Vector3_s (*s) ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_Vector3_i (*i) ( const struct Gan_Image *, unsigned row, unsigned col );
      } vfield3D;

      /// RGBX data
      union
      {
         Gan_RGBXPixel_ui8   (*ui8)  ( const struct Gan_Image *, unsigned row, unsigned col );
         Gan_RGBXPixel_ui10 (*ui10) ( const struct Gan_Image *, unsigned row, unsigned col );
      } rgbx;

      /// RGBA data with small alpha channel
      union
      {
         Gan_RGBASPixel_ui10 (*ui10)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } rgbas;

      /// YUV 4-4-4 with padding to a word boundary
      union
      {
         Gan_YUVX444Pixel_ui8 (*ui8)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } yuvx444;

      /// YUVA 4-4-4
      union
      {
         Gan_YUVA444Pixel_ui8 (*ui8)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } yuva444;

      /// YUV 4-2-2
      union
      {
         Gan_YUV422Pixel_ui8 (*ui8)  ( const struct Gan_Image *, unsigned row, unsigned col );
      } yuv422;
   } get_pix;

#endif /* #ifndef NDEBUG */

   /// fill image with constant value in a mask
   union
   {
      /// grey-level formats
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, unsigned  char pix );
         Gan_Bool (*s)  ( struct Gan_Image *,          short pix );
         Gan_Bool (*us) ( struct Gan_Image *, unsigned short pix );
         Gan_Bool (*i)  ( struct Gan_Image *,            int pix );
         Gan_Bool (*ui) ( struct Gan_Image *, unsigned   int pix );
         Gan_Bool (*f)  ( struct Gan_Image *,          float pix );
         Gan_Bool (*d)  ( struct Gan_Image *,         double pix );
         Gan_Bool (*b)  ( struct Gan_Image *,       Gan_Bool pix );
         Gan_Bool (*p)  ( struct Gan_Image *,         void * pix );
         Gan_Bool (*ui10)  ( struct Gan_Image *, Gan_YXPixel_ui10  *pix );
         Gan_Bool (*ui12)  ( struct Gan_Image *, Gan_YXPixel_ui12  *pix );
      } gl;

      /// grey-level formats with slpha channels
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, Gan_GLAPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, Gan_GLAPixel_s  *pix );
         Gan_Bool (*us) ( struct Gan_Image *, Gan_GLAPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, Gan_GLAPixel_i  *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, Gan_GLAPixel_ui *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, Gan_GLAPixel_f  *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, Gan_GLAPixel_d  *pix );
      } gla;

      /// RGB colour formats
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, Gan_RGBPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, Gan_RGBPixel_s  *pix );
         Gan_Bool (*us) ( struct Gan_Image *, Gan_RGBPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, Gan_RGBPixel_i  *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, Gan_RGBPixel_ui *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, Gan_RGBPixel_f  *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, Gan_RGBPixel_d  *pix );
      } rgb;

      /// RGB colour formats with alpha channels
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, Gan_RGBAPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, Gan_RGBAPixel_s  *pix );
         Gan_Bool (*us) ( struct Gan_Image *, Gan_RGBAPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, Gan_RGBAPixel_i  *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, Gan_RGBAPixel_ui *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, Gan_RGBAPixel_f  *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, Gan_RGBAPixel_d  *pix );
         Gan_Bool (*ui12) ( struct Gan_Image *, Gan_RGBAPixel_ui12 *pix );
      } rgba;

      /// BGR colour formats
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, Gan_BGRPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, Gan_BGRPixel_s  *pix );
         Gan_Bool (*us) ( struct Gan_Image *, Gan_BGRPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, Gan_BGRPixel_i  *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, Gan_BGRPixel_ui *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, Gan_BGRPixel_f  *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, Gan_BGRPixel_d  *pix );
      } bgr;

      /// BGR colour formats with alpha channels
      union
      {
         Gan_Bool (*uc) ( struct Gan_Image *, Gan_BGRAPixel_uc *pix );
         Gan_Bool (*s)  ( struct Gan_Image *, Gan_BGRAPixel_s  *pix );
         Gan_Bool (*us) ( struct Gan_Image *, Gan_BGRAPixel_us *pix );
         Gan_Bool (*i)  ( struct Gan_Image *, Gan_BGRAPixel_i  *pix );
         Gan_Bool (*ui) ( struct Gan_Image *, Gan_BGRAPixel_ui *pix );
         Gan_Bool (*f)  ( struct Gan_Image *, Gan_BGRAPixel_f  *pix );
         Gan_Bool (*d)  ( struct Gan_Image *, Gan_BGRAPixel_d  *pix );
      } bgra;

      /// 2D vector field formats
      union
      {
         Gan_Bool (*f) ( struct Gan_Image *, Gan_Vector2_f *pix );
         Gan_Bool (*d) ( struct Gan_Image *, Gan_Vector2   *pix );
         Gan_Bool (*s) ( struct Gan_Image *, Gan_Vector2_s *pix );
         Gan_Bool (*i) ( struct Gan_Image *, Gan_Vector2_i *pix );
      } vfield2D;

      /// 3D vector field formats
      union
      {
         Gan_Bool (*f) ( struct Gan_Image *, Gan_Vector3_f *pix );
         Gan_Bool (*d) ( struct Gan_Image *, Gan_Vector3   *pix );
         Gan_Bool (*s) ( struct Gan_Image *, Gan_Vector3_s *pix );
         Gan_Bool (*i) ( struct Gan_Image *, Gan_Vector3_i *pix );
      } vfield3D;

      /// RGBX data
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, Gan_RGBXPixel_ui8   *pix );
         Gan_Bool (*ui10) ( struct Gan_Image *, Gan_RGBXPixel_ui10 *pix );
      } rgbx;

      /// RGBA data with small alpha channel
      union
      {
         Gan_Bool (*ui10)  ( struct Gan_Image *, Gan_RGBASPixel_ui10  *pix );
      } rgbas;

      /// YUV 4-4-4 with padding to a word boundary
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, Gan_YUVX444Pixel_ui8  *pix );
      } yuvx444;

      /// YUVA 4-4-4
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, Gan_YUVA444Pixel_ui8  *pix );
      } yuva444;

      /// YUV 4-2-2
      union
      {
         Gan_Bool (*ui8)  ( struct Gan_Image *, Gan_YUV422Pixel_ui8  *pix );
      } yuv422;
   } fill_const;

   /// copy image
   struct Gan_Image * (*copy) ( const struct Gan_Image *, struct Gan_Image * );
} Gan_Image;

#define GAN_IMAGE_STRUCT_DEFINED

/// Definition of a rectangular sub-part of an image
typedef struct Gan_ImageWindow
{
   /// offset of window relative to top-left corner of the image
   int c0, r0;

   /// dimensions of window
   int width, height;
} Gan_ImageWindow;

/**
 * \addtogroup ImageAllocate
 * \{
 */

/**
 * \brief Macro: Allocate and return a new image.
 *
 * Allocates and returns a new image with given \a format
 * (e.g. #GAN_GREY_LEVEL_IMAGE, #GAN_RGB_COLOUR_IMAGE), type (e.g. #GAN_UCHAR
 * for unsigned character images, #GAN_DOUBLE for floating point images),
 * \a height and \a width.
 *
 * Implemented as a macro call to gan_image_form_gen().
 *
 * \sa gan_image_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_alloc ( Gan_ImageFormat format, Gan_Type type,
                                         unsigned long height, unsigned long width );
#else
#define gan_image_alloc(f,t,h,w)\
  gan_image_form_gen(NULL,f,t,h,w,gan_image_min_stride(f,t,w,0),GAN_TRUE,NULL,0,NULL,0)
#endif

/**
 * \brief Macro: Forms and returns a new image.
 *
 * Forms and returns a new image with given \a format
 * (e.g. #GAN_GREY_LEVEL_IMAGE, #GAN_RGB_COLOUR_IMAGE), type (e.g. #GAN_UCHAR
 * for unsigned character images, #GAN_DOUBLE for floating point images),
 * \a height and \a width. If the \a img image pointer is not \c NULL,
 * the given image pointer is filled; otherwise \a img is passed
 * as \c NULL and the image is dynamically allocated.
 *
 * Implemented as a macro call to gan_image_form_gen().
 *
 * \sa gan_image_alloc().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_form ( Gan_Image *img,
                                        Gan_ImageFormat format, Gan_Type type,
                                        unsigned long height, unsigned long width );
#else
#define gan_image_form(img,f,t,h,w)\
  gan_image_form_gen(img,f,t,h,w,gan_image_min_stride(f,t,w,0),GAN_TRUE,NULL,0,NULL,0)
#endif

/**
 * \brief Macro: Allocate image.
 *
 * Allocates and returns an image with given \a format, \a type, dimensions
 * \a height and \a width. If the provided \a pix_data and/or \a row_data
 * pointers are \c NULL (in any combination), the pixel data array and/or the
 * row start pointer array are dynamically allocated. If either are not \c NULL
 * they must be big enough to hold the pixel/row pointer array data.
 * If necessary use gan_image_data_size() to compute the necessary size
 * of the \a pix_data array (the necessary size of \a row_data is
 * \a height pointers).
 *
 * If you want to dynamically allocate the pixel data array and/or the
 * row pointer array with sizes greater than that necessary for the
 * given \a height and \a width, pass \a pix_data and/or \a row_data
 * as \c NULL and set \a pix_data_size and/or \a row_data_size appropriately.
 *
 * Implemented as a macro call to gan_image_form_gen().
 *
 * \sa gan_image_alloc() and gan_image_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_alloc_data ( Gan_ImageFormat format, Gan_Type type,
                                              unsigned long height, unsigned long width,
                                              void *pix_data, size_t pix_data_size,
                                              void *row_data, size_t row_data_size );
#else
#define gan_image_alloc_data(f,t,h,w,pd,pds,rd,rds)\
  gan_image_form_gen(NULL,f,t,h,w,gan_image_min_stride(f,t,w,0),GAN_FALSE,pd,pds,rd,rds)
#endif

/**
 * \brief Macro: Form image.
 *
 * Forms and returns an image \a img with given \a format, \a type, dimensions
 * \a height and \a width. If the provided \a pix_data and/or \a row_data
 * pointers are \c NULL (in any combination), the pixel data array and/or the
 * row start pointer array are dynamically allocated. If either are not \c NULL
 * they must be big enough to hold the pixel/row pointer array data.
 * If necessary use gan_image_data_size() to compute the necessary size of the
 * \a pix_data array (the necessary size of \a row_data is \a height pointers).
 *
 * If you want to dynamically allocate the pixel data array and/or the
 * row pointer array with sizes greater than that necessary for the
 * given \a height and \a width, pass \a pix_data and/or row_data as \c NULL
 * and set \a pix_data_size and/or \a row_data_size appropriately.
 *
 * Implemented as a macro call to gan_image_form_gen().
 *
 * \sa gan_image_alloc() and gan_image_form().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_form_data ( Gan_Image *img,
                                             Gan_ImageFormat format, Gan_Type type,
                                             unsigned long height, unsigned long width,
                                             void *pix_data, size_t pix_data_size,
                                             void *row_data, size_t row_data_size );
#else
#define gan_image_form_data(img,f,t,h,w,pd,pds,rd,rds)\
  gan_image_form_gen(img,f,t,h,w,gan_image_min_stride(f,t,w,0),GAN_FALSE,pd,pds,rd,rds)
#endif

/**
 * \brief Macro: Free an image.
 *
 * Free the memory associated with the image \a img.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API void gan_image_free ( Gan_Image *img );
#else
#define gan_image_free(img) ((img)->free_func(img))
#endif

/**
 * \}
 */

/**
 * \defgroup ImageCopy Copy an Image
 * \{
 */

/**
 * \brief Macro: Copy an image.
 * \return Result image \a img_d.
 *
 * Copy image \a img_s to image \a img_d, and return \a img_d.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_copy_q ( const Gan_Image *img_s, Gan_Image *img_d );
#else
#define gan_image_copy_q(is,id) ((is)->copy(is,id))
#endif

/**
 * \brief Macro: Copy an image.
 * \return Copied image as a new image.
 *
 * Allocate and return a copy of image \a img.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_copy_s ( const Gan_Image *img );
#else
#define gan_image_copy_s(img) ((img)->copy(img,NULL))
#endif

/**
 * \}
 */

/**
 * \addtogroup ImageSet
 * \{
 */

/**
 * \brief Macro: Set format, type and dimensions of image.
 *
 * Set format of image \a img to \a format, its type to \a type, and its
 * dimensions to \a width and \a height. The stride is also set to \a width.
 *
 * Implemented as a macro call to gan_image_set_format_type_dims_gen().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_set_format_type_dims ( Gan_Image *img,
                                                        Gan_ImageFormat format,
                                                        Gan_Type type,
                                                        unsigned long height,
                                                        unsigned long width );
#else
#define gan_image_set_format_type_dims(img,f,t,h,w) gan_image_set_format_type_dims_gen(img,f,t,h,w,gan_image_min_stride(f,t,w,0),GAN_TRUE)
#endif

/**
 * \brief Macro: Set format and type of image.
 *
 * Set format of image \a img to \a format and its type to \a type.
 * The dimensions of \a A remain unchanged.
 *
 * Implemented as a macro call to gan_image_set_format_type_dims().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_set_format_type ( Gan_Image *img,
                                                   Gan_ImageFormat format,
                                                   Gan_Type type );
#else
#define gan_image_set_format_type(img,f,t) gan_image_set_format_type_dims(img,f,t,(img)->height,(img)->width)
#endif

/**
 * \brief Macro: Set type of image.
 *
 * Set type of image to \a type. The format and dimensions of \a A
 * remain unchanged.
 *
 * Implemented as a macro call to gan_image_set_format_type_dims().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_set_type ( Gan_Image *img, Gan_Type type );
#else
#define gan_image_set_type(img,t) gan_image_set_format_type_dims(img,(img)->format,t,(img)->height,(img)->width)
#endif

/**
 * \brief Macro: Set height and width of image.
 *
 * Set dimensions of image \a img to \a height and \a width. The format
 * and type of \a img are unchanged.
 *
 * Implemented as a macro call to gan_image_set_format_type_dims().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Image *gan_image_set_dims ( Gan_Image *img, unsigned long height, unsigned long width );
#else
#define gan_image_set_dims(img,h,w) gan_image_set_format_type_dims(img,(img)->format,(img)->type,h,w)
#endif

/**
 * \}
 */

/**
 * \addtogroup ImageTest
 * \{
 */

/**
 * \brief Macro: Test image format.
 *
 * Returns #GAN_TRUE if the format of the given \a img is \a format, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_test_format ( const Gan_Image *img, Gan_ImageFormat format );
#else
#define gan_image_test_format(img,f) ((img)->format == f)
#endif

/**
 * \brief Macro: Test image type.
 *
 * Returns #GAN_TRUE if the type of the given \a img is \a type, #GAN_FALSE
 * otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_test_type ( const Gan_Image *img, Gan_Type type );
#else
#define gan_image_test_type(img,t) ((img)->type == t)
#endif

/**
 * \brief Macro: Test image dimensions.
 *
 * Returns #GAN_TRUE if the dimensions (width & height) of the given image
 * \a img1 are the same as those of \a img2, #GAN_FALSE otherwise.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_test_dims ( const Gan_Image *img1, const Gan_Image *img2 );
#else
#define gan_image_test_dims(img1,img2) ((img1)->width == (img2)->width && (img1)->height == (img2)->height)
#endif

/**
 * \}
 */

/**
 * \addtogroup ImageFill
 * \{
 */

/**
 * \brief Macro: Fill window of image with zero.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_fill_zero_window ( Gan_Image *img,
                                                  unsigned r0,     unsigned c0,
                                                  unsigned height, unsigned width );
#else
#define gan_image_fill_zero_window(img,r0,c0,h,w) \
           gan_image_fill_const_window(img,r0,c0,h,w,NULL)
#endif

/**
 * \brief Macro: Fill mask in image with zero.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_image_fill_zero_mask ( Gan_Image *img, Gan_Image *mask );
#else
#define gan_image_fill_zero_mask(img,mask) \
           gan_image_fill_const_mask(img,mask,NULL)
#endif

/**
 * \}
 */

/**
 * \addtogroup ImageAllocate
 * \{
 */

GANDALF_API Gan_Image *gan_image_form_gen ( Gan_Image *img,
                                            Gan_ImageFormat format, Gan_Type type,
                                            unsigned long height, unsigned long width,
                                            unsigned long stride, Gan_Bool alloc_pix_data,
                                            void *pix_data, size_t pix_data_size,
                                            void *row_data, size_t row_data_size );
GANDALF_API Gan_Bool gan_image_set_data_free_func ( Gan_Image *img,
                                                    void (*data_free_func)(void *) );

/**
 * \}
 */

/**
 * \addtogroup ImageSize
 * \{
 */

GANDALF_API size_t gan_image_pixel_size ( Gan_ImageFormat format, Gan_Type type );
GANDALF_API size_t gan_image_min_stride ( Gan_ImageFormat format, Gan_Type type,
                                          unsigned long width, size_t alignment );

/**
 * \}
 */

/**
 * \addtogroup ImageFill
 * \{
 */

GANDALF_API Gan_Bool gan_image_fill_const ( Gan_Image *img, Gan_Pixel *pixel );
GANDALF_API Gan_Bool gan_image_fill_zero ( Gan_Image *img );
GANDALF_API Gan_Bool gan_image_fill_const_window ( Gan_Image *img,
                                                   unsigned r0,     unsigned c0,
                                                   unsigned height, unsigned width,
                                                   Gan_Pixel *pixel );
GANDALF_API Gan_Bool gan_image_fill_const_mask ( Gan_Image *img, Gan_Image *mask, Gan_Pixel *pixel );
GANDALF_API Gan_Bool gan_merge_field_into_image(const Gan_Image *field, Gan_Bool flip, Gan_Bool upper, Gan_Bool whole_image, Gan_Image *image);

/**
 * \}
 */

/**
 * \addtogroup ImageAccessPixel
 * \{
 */

GANDALF_API Gan_Pixel gan_image_get_pix ( const Gan_Image *img, unsigned row, unsigned col );
GANDALF_API void     *gan_image_get_pixptr ( const Gan_Image *img, unsigned row, unsigned col );
GANDALF_API Gan_Bool gan_image_get_pix_zero ( const Gan_Image *img, unsigned row, unsigned col );
GANDALF_API Gan_Bool gan_image_set_pix ( Gan_Image *img, unsigned row, unsigned col, Gan_Pixel *pix );
GANDALF_API Gan_Bool gan_image_set_pix_zero ( Gan_Image *img, unsigned row, unsigned col );

/**
 * \}
 */

/**
 * \addtogroup ImageExtract
 * \{
 */

GANDALF_API Gan_Bool gan_image_get_active_subwindow ( const Gan_Image *image, Gan_ImageWindow *subwin );

GANDALF_API void            gan_image_intersect_subwindows_q ( const Gan_ImageWindow *window1, const Gan_ImageWindow *window2,
                                                               Gan_ImageWindow *resultwindow );
GANDALF_API Gan_ImageWindow gan_image_intersect_subwindows_s ( const Gan_ImageWindow *window1, const Gan_ImageWindow *window2 );
GANDALF_API void            gan_image_intersect_subwindows_i ( Gan_ImageWindow *sourcedestwindow, const Gan_ImageWindow *window );
GANDALF_API void            gan_image_fit_subwindow ( Gan_ImageWindow *subwin, const Gan_Image *image );

/**
 * \}
 */

/**
 * \addtogroup ImageFill
 * \{
 */

GANDALF_API Gan_Bool gan_image_mask_window ( Gan_Image *image,
                                             unsigned r0,     unsigned c0,
                                             unsigned height, unsigned width );
GANDALF_API Gan_Bool gan_image_clear_window ( Gan_Image *image,
                                              unsigned r0,     unsigned c0,
                                              unsigned height, unsigned width );

/**
 * \}
 */

/**
 * \addtogroup ImageMinMax
 * \{
 */

GANDALF_API Gan_Bool gan_image_get_minimum_pixel ( Gan_Image *image, Gan_Image *mask, Gan_Pixel *minpix );
GANDALF_API Gan_Bool gan_image_get_maximum_pixel ( Gan_Image *image, Gan_Image *mask, Gan_Pixel *maxpix );

/**
 * \}
 */

/**
 * \addtogroup ImageAllocate
 * \{
 */

GANDALF_API void gan_image_free_va ( Gan_Image *img, ... );

/**
 * \}
 */

/**
 * \addtogroup ImageChannel
 * \{
 */

GANDALF_API Gan_Bool gan_image_has_alpha_channel ( const Gan_Image *img );

/**
 * \}
 */

/**
 * \addtogroup ImageSet
 * \{
 */

/* not user functions: use macros instead */
GANDALF_API Gan_Image *gan_image_set_format_type_dims_gen  ( Gan_Image *img,
                                                 Gan_ImageFormat format,
                                                 Gan_Type type,
                                                 unsigned long height,
                                                 unsigned long width,
                                                 unsigned long stride,
                                                 Gan_Bool alloc_pix_data );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_DEFS_H */
