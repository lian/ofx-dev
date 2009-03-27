/*
 *  ofMemoryImage.cpp
 *  WebImgTextLoaderThreaded
 *
 *  Created by jesús gollonet bailén on 12/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMemoryImage.h"

void ofMemoryImage::loadFromData(const unsigned char * datasource, int len) {
	bool bLoadedOk = false;
	bLoadedOk = loadFromDataIntoPixels(datasource, len, myPixels);
	
	if (bLoadedOk == true){
			cout << "it's been loaded " << endl;
	
			if (myPixels.bAllocated == true && bUseTexture == true){
			tex.allocate(myPixels.width, myPixels.height, myPixels.glDataType);
		}
	}		
	update();


}

bool ofMemoryImage::loadFromDataIntoPixels(const unsigned char * datasource, int len, ofPixels &pix ) {
	
	int					width, height, bpp;
	bool bLoaded		= false;
	FIBITMAP 			* bmp = NULL;
	
	FIMEMORY *hmem = NULL;
	
	hmem = FreeImage_OpenMemory((BYTE *)datasource, len);
	if (hmem == NULL){ printf("couldn't create memory handle! \n");  }
    cout << "memory open " << endl;
	//get the file type!
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(hmem);
	
	cout << "image format "<<  fif << endl;
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		bmp = FreeImage_LoadFromMemory(fif, hmem, 0);
		if (bmp == NULL) {cout << "we could not load from memory!! " << endl;}
		else {FreeImage_CloseMemory(hmem);}
		
		bLoaded = true;
		if (bmp == NULL){
			bLoaded = false;
			cout << "we are not loadded " << endl;
		}
		
	}

   
	if (bLoaded ){
		
		width 		= FreeImage_GetWidth(bmp);
		height 		= FreeImage_GetHeight(bmp);
		bpp 		= FreeImage_GetBPP(bmp);
		
		bool bPallette = (FreeImage_GetColorType(bmp) == FIC_PALETTE);

		switch (bpp){
			case 8:
				if (bPallette) { 
					FIBITMAP 	* bmpTemp =		FreeImage_ConvertTo24Bits(bmp);
					if (bmp != NULL)			FreeImage_Unload(bmp);
					bmp							= bmpTemp;
					bpp							= FreeImage_GetBPP(bmp);
				} else {
					// do nothing we are grayscale
				}
				break;
			case 24:
				// do nothing we are color
				break;
			case 32:
				// do nothing we are colorAlpha
				break;
			default:
				FIBITMAP 	* bmpTemp =		FreeImage_ConvertTo24Bits(bmp);
				if (bmp != NULL)			FreeImage_Unload(bmp);
				bmp							= bmpTemp;
				bpp							= FreeImage_GetBPP(bmp);
		}
		
		
		int byteCount = bpp / 8;
		
		//------------------------------------------
		// call the allocation routine (which checks if really need to allocate) here:
		allocatePixels(pix, width, height, bpp);
		
		
		
		FreeImage_ConvertToRawBits(pix.pixels, bmp, width*byteCount, bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, false);  // get bits
		
		//------------------------------------------
		// RGB or RGBA swap
		// this can be done with some ill pointer math.
		// anyone game?
		// 
		
		#ifdef TARGET_LITTLE_ENDIAN
			if (byteCount != 1) swapRgb(pix);
		#endif
		//------------------------------------------
		
		
	} else {
		width = height = bpp = 0;
	}
	
	if (bmp != NULL){
		FreeImage_Unload(bmp);
	}
	cout << bLoaded << endl;
	return bLoaded;


}