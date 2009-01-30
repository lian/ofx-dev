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
#ifndef MCV_H
#define MCV_H

#include <cv.h>
#include "ofxCvColorImage.h"

/*! \file */

/////////////////////////////////////////////////////////////////////////////////////////////////

#define mcvRow(image, y, type) ( (type  *)( (image)->imageData + (y) * (image)->widthStep ) )
#define mcvGet2D(image, x, y, type) ( (type  *)( (image)->imageData + (y) * (image)->widthStep ) )[x]
#define mcvGet2D_32f(image, x, y)   ( (float *)( (image)->imageData + (y) * (image)->widthStep ) )[x]

/////////////////////////////////////////////////////////////////////////////////////////////////

CvSize mcvSize(IplImage * image);
IplImage * mcvResize(IplImage * original_image, int new_width, int new_height = -1);

/////////////////////////////////////////////////////////////////////////////////////////////////

void mcvSmooth(IplImage * image, IplImage * smoothed_image, int smooth_type, int aperture);

float mcvGaussianDerivative(IplImage * image, int x, int y, int order_x, int order_y, float sigma);

IplImage * mcvGradientNorm2(IplImage * image, int aperture);

void mcvSetBorder(IplImage * image, int border_size, int value);
void mcvSetBorder(IplImage * image, int border_size);

/////////////////////////////////////////////////////////////////////////////////////////////////

// Color <-> Gray conversions with creation:
IplImage * mcvColorToGray(IplImage * colorImage);
IplImage * mcvGrayToColor(IplImage * grayImage);

// Swap Red in Blue channels:
void mcvSwapRandB(IplImage * image);

IplImage * showLocalMinima(IplImage * image);
IplImage * showLocalMaxima(IplImage * image);

// convert scale between 0 & 255:
void mcvScaleTo0_255(IplImage * original, IplImage * scaled);

void mcvReplace(IplImage * image, int old_value, int new_value);

/////////////////////////////////////////////////////////////////////////////////////////////////

int mcvSaveImage(const char * filename, IplImage * image, bool verbose = true);
int mcvSaveImage(const char * generic_filename, int index, IplImage * image, bool verbose = true);

IplImage * mcvLoadImage(const char * filename, int code, bool verbose = true);
IplImage * mcvLoadImage(const char * generic_filename, int index, int code, bool verbose = true);

/////////////////////////////////////////////////////////////////////////////////////////////////

// Crop & Zoom:
IplImage * mcvCrop(IplImage * image, int x, int y, int width, int height);
void mcvCrop(IplImage * image, int x, int y, IplImage * croppedImage);

IplImage * mcvZoom(IplImage * source, int xc, int yc, float zoom);

void mcvPut(IplImage * destImage, IplImage * imageToCopy, int x, int y);

void mcvDeinterlace(IplImage * image);

/////////////////////////////////////////////////////////////////////////////////////////////////

// Colors
// with 0 <= index <= 5, or index == MCV_RANDOM_COLOR == -1 for a random index:
#define MCV_RANDOM_COLOR (-1)

CvScalar mcvRainbowColor(int index, float coeff = 1);

/////////////////////////////////////////////////////////////////////////////////////////////////

// Drawing functions for visualization:

void mcvCross(IplImage * image, int x, int y, int size, CvScalar color, int thickness=1);
void mcvSquare(IplImage * image, int x, int y, int size, CvScalar color, int thickness=1);
void mcvCircle(IplImage * image, int x, int y, int size, CvScalar color, int thickness=1);

void mcvVisibleLine(IplImage * image, int x1, int y1, int x2, int y2, int thickness=1);

/////////////////////////////////////////////////////////////////////////////////////////////////

// Noise:
void mcvAddWhiteNoise(const IplImage * image, const int minNoise, const int maxNoise);
void mcvAddWhiteNoise(const IplImage * image, const int maxNoise);
IplImage * createTwoLevelsWhiteNoiseImage(int width, int height, float percentageOf0);

IplImage * mcvCreateRandomImage(CvSize size, int depth, int nChannels);

void mcvReplace(IplImage * image, int value, int new_value);
void mcvReplaceByNoise(IplImage * image, int value);

void mcvChangeGamma(IplImage * image, float gamma); // I -> 255 * (I / 255) ^ gamma

/////////////////////////////////////////////////////////////////////////////////////////////////

// Patches:
IplImage * mcvGetPatch(IplImage * image, int u, int v, int width, int height);
void mcvGetPatch(IplImage * image, IplImage * patch, int u, int v);

void mcvComputeAffineTransfo(float * a, 
                             int u, int v, 
                             float theta, float phi, float lambda1, float lambda2, float tx, float ty);

#endif // MCV_H
