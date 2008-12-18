/*
 *  ofxFiducialFinder.cpp
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

#include "ofxFiducialFinder.h"

//constructor
ofxFiducialFinder::ofxFiducialFinder() {
	
	treeFromFile = false;
	initialized  = false;
	m_width		 = 0;
	m_height	 = 0;

	/*terminate_treeidmap() knows that this is kind of uninitialized */
	memset(&fidtrackerx, 0, sizeof(fidtrackerx));
	memset(&treeidmap,   0, sizeof(treeidmap));
	
	//initialize trees data from file ** this is what we want **
	initTree(ofToDataPath("all.trees").c_str());//put trees file in the data folder
	//initTree("all.trees");//uncomment this to put trees file in the executable directory
	//if file is not found init default trees file ** not as up to date **
	if (!treeFromFile) initDefaultTree();		
}


ofxFiducialFinder::~ofxFiducialFinder() {
	
	deinitSegmenter();
}


void ofxFiducialFinder::deinitSegmenter() {
	
	if (initialized){
		terminate_segmenter(&segmenter);
	}
	
	initialized = false;
}


void ofxFiducialFinder::findFiducials( ofxCvGrayscaleImage& input ) {
	
	if(input.width!=m_width || input.height!=m_height) deinitSegmenter();
	
	m_width		= input.width;
	m_height	= input.height;
	
	const unsigned char* pixels = input.getPixels();
	
	//if uninitialized
	if(!initialized){
		//check the center pixel to make sure the image is only black and white
		int centerpix = (int)pixels[(m_width/2)*m_width+(m_height/2)];
		if (centerpix != 0 && 255) {
			printf("Image must be pure black and white with no gray. Threshold first.\n");
			return;
		} else {
			//init segmenter
			initialize_segmenter( &segmenter, m_width, m_height, treeidmap.max_adjacencies );
			initialized = true; // return init true
			printf("Segmenter initialized.\n");
		}
	}
	
	//send pixels to the step segmenter
	step_segmenter( &segmenter, pixels );
	//find fiducials
	int count = find_fiducialsX( fiducials, MAX_FIDUCIAL_COUNT,  
								&fidtrackerx , 
								&segmenter, 
								m_width, m_height);
	//clear fiducial vector
	_fiducials.clear();
	
	//fill fiducial vector
	for(int i = 0; i< count; i++) {
		if(fiducials[i].id!=INVALID_FIDUCIAL_ID){
			_fiducials.push_back( ofxFiducial() );
			_fiducials[i] = fiducials[i];
		}
	}
	
}


void ofxFiducialFinder::initTree( const char *file_name ) {
	
	terminate_fidtrackerX( &fidtrackerx );
	terminate_treeidmap( &treeidmap );
	deinitSegmenter();
	
	initialize_treeidmap_from_file( &treeidmap, file_name );
	initialize_fidtrackerX( &fidtrackerx, &treeidmap, NULL );
	
	if(treeidmap.max_adjacencies<=0) {
		printf("Could not load TreeIdMap from '%s'.\n", file_name);
		treeFromFile = false;
	} else {
		treeFromFile = true;
		printf("TreeIdMap loaded succesfully from '%s'.\n", file_name);
	}
}

void ofxFiducialFinder::initDefaultTree() {
	
	terminate_fidtrackerX( &fidtrackerx );
	terminate_treeidmap( &treeidmap );
	deinitSegmenter();
	
	initialize_treeidmap( &treeidmap );
	initialize_fidtrackerX( &fidtrackerx, &treeidmap, NULL );
	
	if(treeidmap.max_adjacencies<=0) printf("Could not load TreeIdMap.\n");
	else printf("Default TreeIdMap loaded.\n");
	
}