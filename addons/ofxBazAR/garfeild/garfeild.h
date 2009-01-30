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
#ifndef GARFEILD_H
#define GARFEILD_H

/*! \defgroup garfeild Garfeild: key points detection and matching

  This module depends on \ref starter and provides tools to detect key points,
  or feature points, and to match them against a set of trained model points.

  Garfeild is designed to quickly detect a planar object on an image. It is a
  two phases process: a training, or off-line phase, and an on-line phase.
  During training, \ref yape detects feature points on a model image. Patches
  are extracted, their orientation corrected, and their appearance learned. The
  \ref planar_object_recognizer::build_with_cache method takes care of the
  learning process.

  During the on-line phase, planar_object_recognizer calls yape to detect
  feature points on the input image. It establish matches with model points. It
  then run RANSAC to sort out bad and good matches, and to find an homography
  sending relating model and input points.

  \example filedetect.cpp
  This example shows how to train and use a planar object detector
*/
//!\ingroup garfeild
//@{
//@}

#include "keypoints/keypoint.h"
#include "keypoints/keypoint_match.h"
#include "keypoints/keypoint_orientation_corrector.h"
#include "keypoints/yape.h"

#include "viewsets/affine_image_generator.h"
#include "viewsets/example_generator.h"
#include "viewsets/image_classification_forest.h"
#include "viewsets/image_classification_node.h"
#include "viewsets/image_classification_tree.h"
#include "viewsets/image_classifier.h"
#include "viewsets/image_object_point_match.h"
#include "viewsets/object_keypoint.h"
#include "viewsets/object_view.h"
#include "viewsets/planar_object_recognizer.h"
#include "calib/CamCalibration.h"
#include "calib/CamAugmentation.h"
#include "lightcalib/lightcalib.h"

#endif // GARFEILD_H
