/**
 * File:          $RCSfile: movie.h,v $
 * Module:        Image movie definitions and functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.10 $
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

#ifndef _GAN_MOVIE_H
#define _GAN_MOVIE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gandalf/image/io/image_io.h>

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageIO
 * \{
 */

/**
 * \brief Image sequence structure.
 */
typedef struct Gan_MovieStruct
{
   /// directory in which image sequence is stored
   char *directory;

   /// base name of sequence
   char *basename;

   /// number of digits in number field of file name
   int no_digits;

   /// suffix string of each file name
   char *suffix;

   /// number of first image in the sequence
   int first;

   /// change in number between each frame of the sequence
   int step;

   /// number of images in the sequence
   int no_images;

   /// file format, e.g. GAN_PNG_FORMAT
   Gan_ImageFileFormat file_format;

   /// how much of images to crop (ignore) at each side
   int crop_xlow, crop_xhigh, crop_ylow, crop_yhigh;
} Gan_MovieStruct;

GANDALF_API Gan_MovieStruct *gan_movie_new ( const char *directory,
                                 const char *basename, int no_digits,
                                 const char *suffix,
                                 int first, int no_images,
                                 Gan_ImageFileFormat file_format );
GANDALF_API void gan_movie_set_step ( Gan_MovieStruct *movie, int step );
GANDALF_API void gan_movie_set_crop_window ( Gan_MovieStruct *movie,
                                 int crop_left, int crop_right,
                                 int crop_top,  int crop_bottom );
GANDALF_API void gan_movie_free ( Gan_MovieStruct *movie );
GANDALF_API char *gan_movie_image_name ( Gan_MovieStruct *movie, int number,
                             char *string, unsigned slen );
GANDALF_API Gan_Image *gan_movie_image_read ( Gan_MovieStruct *movie, int number,
                                  Gan_Image *image );
GANDALF_API Gan_Bool   gan_movie_image_write ( Gan_MovieStruct *movie, int number,
                                   Gan_Image *image );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_MOVIE_H */

