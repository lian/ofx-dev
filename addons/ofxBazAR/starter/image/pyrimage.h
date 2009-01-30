/*
Copyright 2005, 2006 Computer Vision Lab, 
Ecole Polytechnique Federale de Lausanne (EPFL), Switzerland. 
All rights reserved.

This file is part of BazAR.

BazAR is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

BazAR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
BazAR; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/
#ifndef PYRIMAGE_H
#define PYRIMAGE_H

#include <cv.h>
#include "ofxCvColorImage.h"

#ifdef WIN32                      // disable warning :
#pragma warning( disable : 4127 ) // (/W4) conditional expression is constant
#pragma warning( disable : 4512 ) // (/W4) assignment operator could not be generated
#pragma warning( disable : 4288 ) // (/W1) loop control variable declared in the for-loop is used outside the for-loop scope
#endif

//! Multi-resolution pyramidal image
/*! Represent a multi-precision pyramidal image.
 *  images[0] is the largest image.
 *  images[nbLev-1] is the smallest image.
 *
 *  Each level is 4 times smaller than the previous one: width and height are
 *  divided by 2.
 */
class PyrImage {
public:
  PyrImage(IplImage *im, int nblev);
  ~PyrImage();

  //! build the pyramid from level 0 by calling cvPyrDown()
  void build();

  //! try to load an image with cvLoadImage() and build a PyrImage.
  //! \return 0 on failure or a valid PyrImage that has to be deleted by the caller.
  static PyrImage *load(int level, const char *filename, int color, bool fatal = true);

  //! Convert a coordinate from one level to another.
  /* \param x the coordinate to translate
   * \param from the level in which x is specified
   * \param to the level to translate the coordinate into
   * \param method controls whether to return minimum or maximum possible
   *  coordinate, when translating from high to low levels.
   *  0 : return the minimum possible value
   *  1 : return the maximum possible value
   *  2 : return the average possible value
   * \return the translate coordinate
   */
  static int convCoord(int x, int from, int to=0, unsigned method = 0);

  //! Convert a subpixel coordinate from one level to another.
  static float convCoordf(float x, int from, int to=0);

  //! Set a pixel a every precision level.
  /*! Compute coordinates for each precision level, and call cvSet2d() on it.
   *  This method is slow.
   * \param x x coordinate for level 0
   * \param y y coordinate for level 0
   * \param val pixel value to change.
   */
  void setPixel(unsigned x, unsigned y, CvScalar& val);

  //! Set all pixels of all levels to a constant value.
  void set(CvScalar val = cvScalarAll(0));

  //! make an exact copy of this image, reallocating all memory.
  PyrImage *clone() const;

  IplImage *operator[](unsigned i) {return images[i];}

  //! apply a gaussian blur on level 0.
  void smoothLevel0(int kernelSize=3) 
  { 
    cvSmooth(images[0], images[0], CV_GAUSSIAN, kernelSize, kernelSize);
  }

  //! set a region of interest using OpenCV cvSetImageROI()
  void setImageROI(CvRect rect);

  //! reset a region of interest using OpenCV cvResetImageROI()
  void resetImageROI();

  const int nbLev;
  IplImage **images;
};

#endif // PYRIMAGE_H

