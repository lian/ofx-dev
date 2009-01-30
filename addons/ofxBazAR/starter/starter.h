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
#ifndef STARTER_H
#define STARTER_H

/*!\mainpage
 
  \section intro Introduction

  Bazar is a computer vision library based on feature points detection and
  matching. In particular, it is able to quickly detect and register known
  planar objects in images. It also contains a powerfull geometric and
  photometric camera calibration system.

  It is written and distributed at CVLab, EPFL -- http://cvlab.epfl.ch/

  \section install Installing Bazar

  BazAR depends on OpenCV (http://opencvlibrary.sourceforge.net/). You will
  need to install it before using BazAR. For OpenGL support, GLUT and GLEW are
  required (http://www.opengl.org/resources/libraries/glut/ and http://glew.sourceforge.net/).

  \subsection unix_install UNIX/Linux

  Download bazar-xx.tar.gz. Run:
  tar -xzf bazar-xx.tar.gz
  cd bazar-xx
  ./configure
  make
  
  \subsection windows_install Windows

  Download the windows archive, run setup.exe and follow intructions.

  \section orga Library Organization

  Bazar is made of several modules, implemented in two libraries: 
  - \ref garfeild 
  - \ref starter

  \section Examples

  \example filedetect.cpp
  This example shows how to train and use a planar object detector

  \example singlecalib.cpp
  This interactive example shows how compute the geometric calibration of a
  single camera.

  \example augment3d.cpp
  When calibration is done, this example shows how basic 3D augmentation works.

  \example fullcalib.cpp
  This is a more complete example that computes geometric and photometric
  calibration and augmentation with a single camera.

  \example multicam.cpp
  A multi camera geometric and photmetric calibration example which depends
  only on OpenCV.

  \example multigl.cpp 
  A multi camera geometric and photometric calibration example, with OpenGL
  augmentation.
*/

/*! \defgroup starter Starter: Basic structures and mathematical tools

  Starter contains basic structures and mathematical tools, like a non-linear
  minimizer (ls_minimizer).
 */
#include "general/general.h"

#include "math/linear_algebra.h"
#include "math/linear_systems.h"
#include "math/mcvm.h"
#include "math/robust_estimators.h"

#include "geometry/affinity.h"
#include "geometry/homography.h"
#include "geometry/projection_matrix.h"

#include "image/mcv.h"
#include "image/pyrimage.h"

#include "optimization/ls_minimizer2.h"

#endif // STARTER_H
