/**
 * File:          $RCSfile: cineon_io.h,v $
 * Module:        CINEON format image file I/O functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.14 $
 * Last edited:   $Date: 2005/11/08 20:44:43 $
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

#ifndef _GAN_IMAGE_CINEON_IO_H
#define _GAN_IMAGE_CINEON_IO_H

#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/image/image_defs.h>

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
 * \brief Cineon image header structure
 */
typedef struct Gan_CineonHeaderStruct
{
   /// bit size; 0 means default
   unsigned int bit_size;

   /// whether to pack the data
   Gan_Bool packed;
} Gan_CineonHeaderStruct;

/* forward declaration */
struct Gan_ImageReadControlStruct;
struct Gan_ImageHeaderStruct;
struct Gan_ImageWriteControlStruct;

/* Prototypes for public functions in cineon_io.c */
GANDALF_API Gan_Bool gan_image_is_cineon(const unsigned char *magic_string, size_t length);
GANDALF_API Gan_Image *gan_read_cineon_image_stream ( FILE *infile, Gan_Image *image,
                                          const struct Gan_ImageReadControlStruct *ictrlstr, struct Gan_ImageHeaderStruct *header );
GANDALF_API Gan_Image *gan_read_cineon_image ( const char *filename, Gan_Image *image,
                                   const struct Gan_ImageReadControlStruct *ictrlstr, struct Gan_ImageHeaderStruct *header );
GANDALF_API void       gan_initialise_cineon_header_struct(Gan_CineonHeaderStruct *octrlstr, Gan_ImageFormat image_format, Gan_Type type);
GANDALF_API Gan_Bool   gan_write_cineon_image_stream ( FILE *outfile, const Gan_Image *image, Gan_Bool new_file, const struct Gan_ImageWriteControlStruct *octrlstr );
GANDALF_API Gan_Bool   gan_write_cineon_image ( const char *filename, const Gan_Image *image, const struct Gan_ImageWriteControlStruct *octrlstr );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_CINEON_IO_H */
