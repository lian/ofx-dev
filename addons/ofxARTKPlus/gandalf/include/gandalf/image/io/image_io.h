/**
 * File:          $RCSfile: image_io.h,v $
 * Module:        Image file I/O functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.43 $
 * Last edited:   $Date: 2006/03/15 15:16:09 $
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

#ifndef _GAN_IMAGE_IO_H
#define _GAN_IMAGE_IO_H

#include <gandalf/image/image_defs.h>
#include <gandalf/image/io/png_io.h>
#include <gandalf/image/io/pbm_io.h>
#include <gandalf/image/io/pgm_io.h>
#include <gandalf/image/io/tiff_io.h>
#include <gandalf/image/io/jpeg_io.h>
#include <gandalf/image/io/dpx_io.h>
#include <gandalf/image/io/cineon_io.h>
#include <gandalf/image/io/sgi_io.h>
#include <gandalf/image/io/targa_io.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageIO
 * \{
 */

/**
 * \brief Image file formats supported by Gandalf
 */
typedef enum
{
   GAN_PNG_FORMAT,    /**< PNG image format */
   GAN_PBM_FORMAT,    /**< Portable bitmap image format */
   GAN_PGM_FORMAT,    /**< Portable greymap image format */
   GAN_PPM_FORMAT,    /**< Portable pixmap image format */
   GAN_TIFF_FORMAT,   /**< TIFF image format */
   GAN_JPEG_FORMAT,   /**< JPEG image format */
   GAN_DPX_FORMAT,    /**< DPX image format */
   GAN_CINEON_FORMAT, /**< CINEON image format */
   GAN_SGI_FORMAT,    /**< SGI image format */
   GAN_TARGA_FORMAT,  /**< TrueVision TARGA image format */
   GAN_UNKNOWN_FORMAT /**< Unknown Image Format */
} Gan_ImageFileFormat;

/**
 * \brief Input control structure
 */
typedef struct Gan_ImageReadControlStruct
{
   /// whether to read the image header only
   Gan_Bool header_only;

   /// whether to flip the image data vertically
   Gan_Bool flip;

   /// whether to read a single field of an interlaced image
   Gan_Bool single_field;

   /// if reading a single field, which one
   Gan_Bool upper;

   /// if reading a single field, whether to insert it into a full size image (required for pulldown frames)
   Gan_Bool whole_image;
#if 0
   /// input type for colourspace conversion. #GAN_UNDEFINED_TYPE indicates no conversion. Should be checked against file type.
   Gan_Type itype;

   /// output type for colourspace conversion. #GAN_UNDEFINED_TYPE indicates no conversion. Corresponds to type of \a lookup below.
   Gan_Type otype;

   /// lookup table for conversion, or \c NULL if no conversion
   union
   {
      gan_float32 *f32;
      gan_uint16  *ui16;
   } lookup;
#endif
} Gan_ImageReadControlStruct;

/**
 * \brief Format-specific header information
 */
typedef struct Gan_ImageHeaderInfo
{
   /// SMPTE time code
   gan_uint32 time_code;

   /// SMPTE user bite
   gan_uint32 user_bits;

   /// whether the data is interlaced
   Gan_Bool interlaced;

   /// frame rate of original in frames/sec
   gan_float32 frame_rate;

#ifdef HAVE_PNG
   Gan_PNGHeaderStruct    png;
#endif
#ifdef HAVE_TIFF
   Gan_TIFFHeaderStruct   tiff;
#endif
#ifdef HAVE_JPEG
   Gan_JPEGHeaderStruct   jpeg;
#endif
   Gan_DPXHeaderStruct    dpx;
   Gan_CineonHeaderStruct cineon;
   Gan_SGIHeaderStruct    sgi;
   Gan_TargaHeaderStruct  targa;
} Gan_ImageHeaderInfo;

/**
 * \brief Input image header structure
 */
typedef struct Gan_ImageHeaderStruct
{
   Gan_ImageFileFormat file_format;
   unsigned int width;
   unsigned int height;
   Gan_ImageFormat format;
   Gan_Type type;
   Gan_ImageHeaderInfo info;
} Gan_ImageHeaderStruct;

/**
 * \brief Output image control structure
 */
typedef struct Gan_ImageWriteControlStruct
{
   /// whether to flip the image data vertically
   Gan_Bool flip;

   /// whether to write a single field of an interlaced image
   Gan_Bool single_field;

   /// if writing a single field, which one
   Gan_Bool upper;

   /// if writing a single field, whether to take it from a full size image (required for pulldown frames)
   Gan_Bool whole_image;

   /// whether to reverse the endianness
   Gan_Bool reverse_bytes;

   /// format-specific control information union
   Gan_ImageHeaderInfo info;
} Gan_ImageWriteControlStruct;

GANDALF_API Gan_ImageFileFormat gan_image_determine_file_format_stream ( FILE *infile );
GANDALF_API Gan_ImageFileFormat gan_image_determine_file_format ( const char *filename );
GANDALF_API Gan_ImageFileFormat gan_image_interpret_format_string ( const char *format_string );
GANDALF_API const char *gan_image_file_format_string ( Gan_ImageFileFormat format );
GANDALF_API const char *gan_image_format_string ( Gan_ImageFormat format );
GANDALF_API Gan_Bool gan_image_file_format_compressed ( Gan_ImageFileFormat format );
GANDALF_API Gan_Bool gan_image_format_type_supported ( Gan_ImageFileFormat file_format, Gan_ImageFormat image_format, Gan_Type type,
                                                       const Gan_ImageHeaderInfo* info );
GANDALF_API Gan_Bool gan_image_write_field_supported ( Gan_ImageFileFormat file_format );
GANDALF_API void gan_initialise_image_read_control_struct(Gan_ImageReadControlStruct *ictrlstr);
GANDALF_API Gan_Image *gan_image_read ( const char *filename, Gan_ImageFileFormat file_format, Gan_Image *image,
                                        const Gan_ImageReadControlStruct *ictrlstr, Gan_ImageHeaderStruct *header );
GANDALF_API Gan_Image *gan_image_read_stream ( FILE *infile, Gan_ImageFileFormat file_format, Gan_Image *image,
                                               const Gan_ImageReadControlStruct *ictrlstr, Gan_ImageHeaderStruct *header );
GANDALF_API Gan_Bool gan_initialise_image_header_info(Gan_ImageHeaderInfo *ohdrinfo, Gan_ImageFormat image_format, Gan_Type type);
GANDALF_API Gan_Bool gan_initialise_image_write_control_struct(Gan_ImageWriteControlStruct *octrlstr,
                                                               Gan_ImageFileFormat file_format, Gan_ImageFormat image_format, Gan_Type type);
GANDALF_API Gan_Bool gan_image_write ( const char *filename, Gan_ImageFileFormat file_format, const Gan_Image *image,
                                       const Gan_ImageWriteControlStruct *octrlstr );
GANDALF_API Gan_Bool gan_image_write_stream ( FILE *outfile, Gan_ImageFileFormat file_format, const Gan_Image *image,
                                              Gan_Bool new_file, const Gan_ImageWriteControlStruct *octrlstr );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_IO_H */
