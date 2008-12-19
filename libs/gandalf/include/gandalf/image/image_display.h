/**
 * File:          $RCSfile: image_display.h,v $
 * Module:        Display images using Open GL
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.14 $
 * Last edited:   $Date: 2006/01/30 17:14:41 $
 * Author:        $Author: ndm $
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

#ifndef _GAN_IMAGE_GL_DISPLAY_H
#define _GAN_IMAGE_GL_DISPLAY_H

#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_GLUT

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageDisplay
 * \{
 */

GANDALF_API Gan_Bool gan_image_display ( const Gan_Image *img );
GANDALF_API Gan_Bool gan_display_new_window ( int height, int width, double zoom,
                                  char *name, int offset_r, int offset_c,
                                  int *window_id );
GANDALF_API Gan_Bool gan_display_new_window_array ( int rows, int cols,
                                        int height, int width, double zoom,
                                        char *name, int offset_r, int offset_c,
                                        int *window_id, int **subwindow_id );
GANDALF_API Gan_Bool gan_image_display_new_window ( const Gan_Image *img, double zoom,
                                        char *name, int offset_r, int offset_c,
                                        int *window_id );
GANDALF_API void gan_image_display_free_windows(void);

/**
 * \}
 */

/**
 * \}
 */

#endif /* #ifdef HAVE_GLUT */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_GL_DISPLAY_H */
