/*
 *  ofxCvColorTrack.h
 *  openFrameworks
 *
 *  http://www.candersonmiller.com
 *  Created by C. Anderson Miller on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _CV_COLOR_TRACK
#define _CV_COLOR_TRACK

#include "ofMain.h"
#include "ofxOpenCv.h"


//--------------------------------------------------------------------
class ofxCvColorTrack {

	public:
		
		ofxCvColorTrack();
		void  		findColor (	int r, int g, int b);  
		void		update(ofxCvColorImage &input);
		void		setTolerance(int t);
		float		getX();
		float		getY();
		void 		reset();
		void 		draw();

		ofxCvColorImage		    inputCopy;
		CvMemStorage			*contour_storage;
		CvMemStorage			*storage;
		CvMoments				*myMoments;

		//----------------------------------- an array of cvSequences
		int 					nCvSeqsFound;
		CvSeq* 					cvSeqBlobs[500];
		
		int 					nBlobs;
		ofxCvBlob				* blobs; 
		int red;
		int green; 
		int blue;
		float					xAvg;
		float					yAvg;
	private:
		ofxCvColorImage		posterize(ofxCvColorImage input);
		ofxCvColorImage		posterizedCopy;
		int					threshold;
		int					tolerance;
		int					xPosition(int pixelNum, int h, int w);
		int					yPosition(int pixelNum,	int h, int w);
		
		

};

#endif
