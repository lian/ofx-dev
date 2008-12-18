/*
 *  ofxFiducialTracker.h
 *  openFrameworks
 *
 *  Created by Alain Ramos a.k.a. ding
 *  Copyright 2008 Alain Ramos.
 *
 *
For Free you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
//	----------------------------------------------------------------------------------------------------

#ifndef OF_X_FIDUCIALTRACKER_H
#define OF_X_FIDUCIALTRACKER_H

#include <list>
#include "ofxFiducial.h"
#include "ofxFinger.h"
#include "ofMain.h"
#include "ofxCvGrayscaleImage.h"
#include "libfidtrack/segment.h"

#define MAX_FIDUCIAL_COUNT 512

//*****************************************************************
//more complex and advanced fiducial tracker using a list
//this is the one I will be focused on for all the cool features
//This Is The Good One

class ofxFiducialTracker {
	
	public:
	
		//constructor & destructor
		ofxFiducialTracker();
		~ofxFiducialTracker();
		
		bool 	detectFinger;
   		float 	fingerSensitivity;
   		float 	minFingerSize;
   		float 	maxFingerSize;
	
		//list to store fiducials
		std::list <ofxFiducial> fiducialsList;
		
		//list to store fingers
		std::list <ofxFinger> fingersList;
	
		//find fiducials in gray image
		void findFiducials( ofxCvGrayscaleImage& input );
	
		//initialize the tree where the fiducial data is from file
		void initTree( const char *file_name );
	
		//initialize the default tree where the fiducial data is
		void initDefaultTree();

	
	private:
	
		//width and height of gray image
		int m_width, m_height;
		//is the segmenter initialized
		bool initialized;
		//is the tree initialized from file
		bool treeFromFile;
		//segmenter
		Segmenter segmenter;
		//tree ID map
		TreeIdMap treeidmap;
	
		//fiducial tracker
		FidtrackerX fidtrackerx;
		//FiducialX array to pass to the fidtracker to find fiducials
		FiducialX fiducials[ MAX_FIDUCIAL_COUNT ];
		//RegionX array to pass to the fidtracker to find fingers
		RegionX regions[ MAX_FIDUCIAL_COUNT*2 ];
		//to keep track of fiducials
		int fidCount;
		
		//check if finger is valid
		int check_finger(RegionX *finger, const unsigned char* img);
		//find fingers
		void findFingers( const unsigned char* pixels );
		//figer ids
		int finger_id;
   
		//deinitialize segmenter
		void deinitSegmenter();
};

#endif

