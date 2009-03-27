/*
 *  ofMemoryImage.h
 *  WebImgTextLoaderThreaded
 *
 *  Created by jesús gollonet bailén on 12/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _OF_MEMORY_IMAGE
#define _OF_MEMORY_IMAGE

#include "ofImage.h"

class   ofMemoryImage : public ofImage { 
	
	public:
		
		void loadFromData(const unsigned char * datasource, int len); 
	
	private :
	
		bool loadFromDataIntoPixels(const unsigned char * datasource, int len, ofPixels &pix); 

};

#endif
