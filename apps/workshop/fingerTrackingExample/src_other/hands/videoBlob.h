#ifndef _VIDEO_BLOB
#define _VIDEO_BLOB

#include "ofMain.h"
#include "ofxOpenCV.h"
//#include "videoTexture.h"
#define MAX_CONTOUR_LENGTH		100
class videoBlob {
	
	public:
	
	
		void set(ofxCvBlob myBlob, ofxCvColorImage myImage, ofxCvGrayscaleImage myMask);
		void draw();
		void drawDiagnostically();
		void drawOutline();
		// these are both helpful for interaction:
		void draw(ofxCvGrayscaleImage &mom, int color);
		bool pointInsideMe(float x, float y);
		
		
		void update();
		
		
		
		
		ofxCvBlob 			blob;
//		videoTexture 		myTexture;	
		
		//----------------------------------------- translating points
		ofPoint				pos;
		float 				angle;
		float 				scale;
		int					nPts;						
		ofPoint				pts[MAX_CONTOUR_LENGTH];
		ofPoint 			texPts[4];
		//-----------------------------------------
		
};

#endif	
