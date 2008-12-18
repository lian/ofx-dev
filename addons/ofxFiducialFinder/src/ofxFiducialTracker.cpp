/*
 *  ofxFiducialTracker.cpp
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

#include "ofxFiducialTracker.h"

//constructor
ofxFiducialTracker::ofxFiducialTracker() {
	
	treeFromFile	= false;
	initialized		= false;
	m_width			= 0;
	m_height		= 0;
	fidCount		= 0;
	
	detectFinger			= false;
	fingerSensitivity		= 0.05f; //from 0 to 2.0f
   	minFingerSize			= 2.0f;
   	maxFingerSize			= 4.0f;
	finger_id				= 0;

	/*terminate_treeidmap() knows that this is kind of uninitialized */
	memset(&fidtrackerx, 0, sizeof(fidtrackerx));
	memset(&treeidmap,   0, sizeof(treeidmap));
	
	//initialize trees data from file ** this is what we want **
	initTree(ofToDataPath("all.trees").c_str());//put trees file in the data folder
	//initTree("all.trees");//uncomment this to put trees file in the executable directory
	//if file is not found init default trees file ** not as up to date **
	if (!treeFromFile) initDefaultTree();	
}


//destructor
ofxFiducialTracker::~ofxFiducialTracker() {
	
	deinitSegmenter();
	terminate_treeidmap(&treeidmap);
   	terminate_fidtrackerX(&fidtrackerx);
}


//sinds fiducials in image
void ofxFiducialTracker::findFiducials( ofxCvGrayscaleImage& input ) {
	
	//if video height and width dont match previous then reinit segmenter
	if(input.width!=m_width || input.height!=m_height) deinitSegmenter();
	
	//get the video width and height
	m_width		= input.width;
	m_height	= input.height;
	
	//get the pixels
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
	fidCount = find_fiducialsX( fiducials, MAX_FIDUCIAL_COUNT,  
								&fidtrackerx , 
								&segmenter, 
								m_width, m_height);
	
	//fill fiducial list
	for(int i = 0; i< fidCount; i++) {
		if(fiducials[i].id!=INVALID_FIDUCIAL_ID){
			//make empty fiducial
			ofxFiducial * existing_fiducial = NULL;
			//iterate through list to find the current fiducial
			for (std::list<ofxFiducial>::iterator fiducial = fiducialsList.begin(); fiducial != fiducialsList.end(); fiducial++) {
				if (fiducials[i].id == fiducial->fidId)  { //if fiducial id found 
					existing_fiducial = &(*fiducial); //make existing_fiducial pointer point to found fiducial in list
					break;//finish loop
				}
			}
			if (existing_fiducial!=NULL) {//if found
				//update fiducial
				existing_fiducial->update(fiducials[i].x,fiducials[i].y,fiducials[i].angle,fiducials[i].root_size,fiducials[i].leaf_size);
			} else {
				//else add fiducial not found to list
				ofxFiducial addFiducial;
				addFiducial = fiducials[i];
				fiducialsList.push_back(addFiducial);
			}
		}
	}
	//iterate through list to erase dead fiducials 
	for (std::list<ofxFiducial>::iterator fiducial = fiducialsList.begin(); fiducial != fiducialsList.end(); ) {
		bool alive = fiducial->isAlive(); 
		if (!alive) { 
			fiducial =  fiducialsList.erase(fiducial);
		} 
		else ++fiducial; 
	}
	
	if (detectFinger) findFingers(pixels);
}


//finds fingers in a pixel data array
void ofxFiducialTracker::findFingers( const unsigned char* pixels ) {
   		
   		//find regions
   		int fingerCount = find_regionsX( regions, MAX_FIDUCIAL_COUNT,
   										 &fidtrackerx , 
									   	 &segmenter, 
									  	 m_width, m_height);
							
		for(int j = 0; j < fingerCount; j++) {
		
			bool insideFid = false;
			//check to see if a region is inside any fiducial in the list
			for (std::list<ofxFiducial>::iterator fiducial = fiducialsList.begin(); fiducial != fiducialsList.end(); fiducial++) {
			   		if (fiducial->isPointInside(regions[j].x, regions[j].y)) {
			   			insideFid = true;
			   			break;
			   		}
			}
			//if inside any fiducial then it no good
			if (insideFid) continue;//go to next region
		
			int diff = abs(regions[j].width - regions[j].height);
			int max_diff = regions[j].width/2;
			if (regions[j].height > regions[j].width) max_diff = regions[j].height/2;
			
			if (/*regions[j].colour==255 && */(regions[j].width>minFingerSize) && (regions[j].width<maxFingerSize)  &&
			   (regions[j].height>minFingerSize) && (regions[j].height<maxFingerSize) && diff < max_diff) {
			   	
			   	int finger_match = check_finger(&regions[j], pixels);
			   	if(finger_match<0) continue;//go to next region
			   	
			   	ofxFinger * existing_finger = NULL;
			   	float closest = m_width;
			   	
			   	for (std::list<ofxFinger>::iterator finger = fingersList.begin(); finger != fingersList.end(); finger++) {
			   		float distance = finger->getDistance(regions[j].x,regions[j].y);
			   		if ((distance<maxFingerSize*2) && (distance<closest)){
			   		existing_finger = &(*finger);
			   		closest = distance;
			   		
			   		//is there another finger closer than that?
			   		if (distance>maxFingerSize/2) {
			   			
			   			for(int k = 0; k < fingerCount; k++) {
			   				if(j==k) continue;
			   				if ((regions[k].width>minFingerSize) && (regions[k].width<maxFingerSize) &&
			   					(regions[k].height>minFingerSize) && (regions[k].height<maxFingerSize) && diff < max_diff) {
								
								int dx 		= abs(regions[k].x - regions[j].x);
								int dy 		= abs(regions[k].y - regions[j].y);
								float dist 	= sqrt((float)(dx*dx+dy*dy));
								
								if (dist<=distance) { 
									existing_finger=NULL;
									closest=dist;
									break;
									}
								}
							}
						}
					}
				}
				
				if  (existing_finger!=NULL) {
						existing_finger->update(regions[j].x,regions[j].y,regions[j].width, regions[j].height, regions[j].area);
					} else {
						//else add fiducial not found to list
						ofxFinger addFinger;
						addFinger.fingerID = finger_id;
						addFinger = regions[j];
						fingersList.push_back(addFinger);
						finger_id++;
					}
				}
			}
		//iterate through list to erase dead fingers
	for (std::list<ofxFinger>::iterator finger = fingersList.begin(); finger != fingersList.end(); ) {
			bool alive = finger->isAlive(); 
			if (!alive) { 
				finger = fingersList.erase(finger); 
			}
			else ++finger; 
		}
	}


//check region to see if it is a finger
int ofxFiducialTracker::check_finger(RegionX *finger, const unsigned char* img) {

  		int mask_size = finger->width;
  		if (finger->height > finger->width) mask_size = finger->height;
   
  		float outer_radius = mask_size/2.0f;
   		float inner_radius = mask_size/3.0f;
    
  		int rounded_outer_radius = floor(outer_radius+0.5f);
    	int rounded_inner_radius = ceil(inner_radius+0.5f);
     
     	float xratio = (float)mask_size/(float)finger->width;
     	float yratio = (float)mask_size/(float)finger->height;
     	short outer_error = 0;
     	short inner_error = 0;
     
     	for (int x = 0; x < mask_size; x++) {
     		for (int y = 0; y < mask_size; y++) {
     
     			int px = finger->left+(int)floor(x/xratio+0.5f);
     			int py = finger->top +(int)floor(y/yratio+0.5f);
     
    			int finger_pixel = py*m_width+px;
     			if ((finger_pixel >= m_width*m_height) || (finger_pixel<0)) return -1;
     
     			float dx = x-outer_radius+0.5f;
     			float dy = y-outer_radius+0.5f;
     			int dist = floor(sqrtf(dx*dx+dy*dy)+0.5f);
     
  
     
     		if ((dist>rounded_outer_radius) && (img[finger_pixel]==255)) { outer_error++; } 
     		else if ((dist<rounded_inner_radius) && (img[finger_pixel]==0)) { inner_error++; } 
     		}
     	}
     
     	short outer_max_error = (short)floor((mask_size*mask_size)-(outer_radius*outer_radius*PI)+0.5f);
     	short inner_max_error = (short)floor(inner_radius*inner_radius*PI+0.5f);
     
    	//std::cout << "finger: " << finger->left << " " << finger->top << " " << finger->width << " " << finger->height << std::endl;
    	//std::cout << "error: " << outer_error << " " << inner_error << std::endl;
     	//std::cout << "max: " << outer_max_error << " " << inner_max_error << std::endl;
   
    	if ((outer_error>outer_max_error/4*fingerSensitivity) || (inner_error>inner_max_error/6*fingerSensitivity)) return -1;
    	if ((outer_error>outer_max_error/6*fingerSensitivity) || (inner_error>inner_max_error/9*fingerSensitivity)) return 0;
    	return 1;
   }
   
	
	//terminates segmenter
	void ofxFiducialTracker::deinitSegmenter() {
	
	if (initialized){
		terminate_segmenter(&segmenter);
	}
	
	initialized = false;
}
  
  
//initialize the fiducial tree from all.trees file
void ofxFiducialTracker::initTree( const char *file_name ) {
	
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


//initialize the fiducial tree from default_trees.h
void ofxFiducialTracker::initDefaultTree() {
	
	terminate_fidtrackerX( &fidtrackerx );
	terminate_treeidmap( &treeidmap );
	deinitSegmenter();
	
	initialize_treeidmap( &treeidmap );
	initialize_fidtrackerX( &fidtrackerx, &treeidmap, NULL );
	
	if(treeidmap.max_adjacencies<=0) printf("Could not load TreeIdMap.\n");
	else printf("Default TreeIdMap loaded.\n");
	
}
			
			

