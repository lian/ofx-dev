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
#include <iostream>
// #include <highgui.h>
#include "pyrimage.h"

using namespace std;

PyrImage::PyrImage(IplImage *im, int nblev) : nbLev(nblev)
{
  images = new IplImage *[nblev];

  images[0] = im;

  for (int i=1; i<nbLev; ++i) {
    images[i] = cvCreateImage(cvSize(images[i-1]->width/2, images[i-1]->height/2),
                              im->depth, im->nChannels);
  }
}

PyrImage::~PyrImage() {
  for (int i=0; i<nbLev; ++i) 
    cvReleaseImage(&images[i]);
  delete [] images;
}

void PyrImage::build()
{
  for (int i=1; i<nbLev; ++i) 
    cvPyrDown(images[i-1], images[i]);
}

PyrImage *PyrImage::load(int level, const char *filename, int color, bool fatal) {

//  IplImage *im = cvLoadImage(filename, color);
	ofImage _img = ofImage();
	_img.loadImage(filename);
	ofxCvColorImage _im = ofxCvColorImage();
	_im = _img.getPixels();
	IplImage *im = _im.getCvImage();
	

  if (im == 0) {
    cerr << filename << ": unable to load image.\n";
    if (fatal)
      exit(-1);
    return 0;
  }

  PyrImage *r= new PyrImage(im, level);
  r->build();
  return r;
}

int PyrImage::convCoord(int x, int from, int to, unsigned max)
{
  if (max == 2) 
    return (convCoord(x, from, to, 0) + convCoord(x, from, to, 1)) >> 1;
  if (to==from) 
    return x;
  if (to<from) {
    if (max == 1) {
      int r=x;
      for (int i=from; i<to; ++i) {
        r = r*2 + 1;
      }
      return r;
    } 
    return x << ( from - to );
  }
  return x >> ( to - from );
}

float PyrImage::convCoordf(float x, int from, int to)
{
  if (to == from) 
    return x;

  if (to<from) 
    return x * float(1 << (from-to));

  return x / float(1 << (to-from)); 
}

void PyrImage::setPixel(unsigned x, unsigned y, CvScalar &val)
{
  if (( x >= (unsigned)images[0]->width ) || ( y >= (unsigned)images[0]->height ))
    return;

  for (int i=0; i<nbLev; ++i) {
    cvSet2D(images[i], 
      convCoord((int)y, 0, i),
      convCoord((int)x, 0, i),
      val);
  }
}

void PyrImage::set(CvScalar val)
{
  for (int i=0; i<nbLev; ++i)
    cvSet(images[i], val);
}

PyrImage *PyrImage::clone() const
{
  PyrImage *p = new PyrImage(cvCloneImage(images[0]), nbLev);
  for (int i=1; i<nbLev; ++i)
    cvCopy(images[i], p->images[i]);
  return p;
}

void PyrImage::setImageROI(CvRect rect) 
{
  CvRect r;
  for (int i=0; i<nbLev; ++i) {
    r.x = convCoord(rect.x, 0, i);
    r.y = convCoord(rect.y, 0, i);
    r.width = convCoord(rect.width, 0, i);
    r.height = convCoord(rect.height, 0, i);
    cvSetImageROI(images[i], r);
  }
}

void PyrImage::resetImageROI()
{
  for (int i=0; i<nbLev; ++i) {
    cvResetImageROI(images[i]);
  }
}

