#ifndef _VIDEO_HAND_FINGER_FINDER_
#define _VIDEO_HAND_FINGER_FINDER_

#include "ofMain.h"
#include "ofxOpenCV.h"

#include "videoHandConstants.h"

#include "cvLineFitter.h"

#include "ofVec3f.h"

//  good finger tracking explanation here:
//  www.cs.toronto.edu/~smalik/downloads/2503_project_report.pdf 


#define NPTS_FOR_LINE_FIT 		40


//-----------------------------------------------|
class videoHandFingerDetector{
	
	public:
		
		videoHandFingerDetector();
		
		void findFingers 			(handBlob	&blob);
		void fitLineThroughPts 		(handBlob	&blob, int pt, int fingerId);
		void finger(handBlob &blob);
	
		bool 				* bFingerPointRuns;
		float 				pctOfContourNumForAngleCheck;	// pt j, j-n, j+n, n = pct * contourPtNum
		float 				angleThreshold;
		ofPoint			lineFitPts[NPTS_FOR_LINE_FIT];
		cvLineFitter		CVLF;
		
		
};
//-----------------------------------------------|


#endif	
