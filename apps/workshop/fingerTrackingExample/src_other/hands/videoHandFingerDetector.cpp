#include "videoHandFingerDetector.h"

//------------------------------------------------------------
videoHandFingerDetector::videoHandFingerDetector(){
	bFingerPointRuns = new bool[MAX_CONTOUR_LENGTH];
	angleThreshold = - 1.03;
	//angleThreshold = 5;
}

//------------------------------------------------------------
void videoHandFingerDetector::findFingers 	(handBlob &blob){

	memset (bFingerPointRuns, 0, sizeof(bool) * MAX_CONTOUR_LENGTH);

	//--------------------------- blur the contour pts alot ----------
	for (int k=0; k < 3; k++){
		for (int j=1; j< blob.myBlob.nPts-1; j++){
			
			blob.myBlob.pts[j].x =  0.6f * blob.myBlob.pts[j].x +
								  0.2f * blob.myBlob.pts[j-1].x +
								  0.2f * blob.myBlob.pts[j+1].x;
			blob.myBlob.pts[j].y =  0.6f * blob.myBlob.pts[j].y +
								  0.2f * blob.myBlob.pts[j-1].y +
								  0.2f * blob.myBlob.pts[j+1].y;
			
		}
	}

	//--------------------------- calc angles ----------
	// this can be optimized, please
	
	// int kConstant = (int)(blob.myBlob.nPts/20.0f); 
	// usually, this made sense (adjust angle calc based on n points), but with CV_CHAIN_APPROX...  
	// with all the points, and hands pretty big, I found this is pretty good:
	
	int kConstant = 30;
	
	// 	you can try adjusting and see what works well:
	//	int kConstant = 33 + 30 * sin(ofGetElapsedTimef());
	//	printf("%i \n", (int)kConstant);
	
	for (int j=0; j<blob.myBlob.nPts; j++){
		int pt0 = (j - kConstant + blob.myBlob.nPts) % blob.myBlob.nPts;
		int pt1 = j;
		int pt2 = (j + kConstant) % blob.myBlob.nPts;
		
		ofVec3f lineab;
		lineab.x = blob.myBlob.pts[pt1].x - blob.myBlob.pts[pt0].x;
		lineab.y = blob.myBlob.pts[pt1].y - blob.myBlob.pts[pt0].y;
		
		ofVec3f linecb;
		linecb.x = blob.myBlob.pts[pt2].x - blob.myBlob.pts[pt1].x;
		linecb.y = blob.myBlob.pts[pt2].y - blob.myBlob.pts[pt1].y;
		
		lineab.normalize();
		linecb.normalize();
		float dot = lineab.x * linecb.x + lineab.y * linecb.y;
		float cross = lineab.x * linecb.y - lineab.y * linecb.x;
		float theta = acos(dot);
		if (cross < 0) { theta = 0-theta; }
		blob.curvatureAtPt[j] = theta;
		
		
		if (blob.curvatureAtPt[j] < angleThreshold){
			
			bFingerPointRuns[j] = true;
			
			// hack to turn off curve on walls
			// this is a big hack, but seems to work...
			if ((blob.myBlob.pts[pt1].x < 20 || blob.myBlob.pts[pt1].x > 300) ||
				(blob.myBlob.pts[pt1].y < 20 || blob.myBlob.pts[pt1].y > 220)){
					blob.curvatureAtPt[j] = 0;
					bFingerPointRuns[j] = false;
				}
			
		} else {
			bFingerPointRuns[j] = false;
		}
	}

	//if (bFingerPointRuns[0] == true) do something else, smart!
	// ie search for first non, start there and do to there+nPts % nPts...!
	// that's smart :)

	bool bInRun = false;
	int startRun = 0;
	int fingersFound = 0;
	blob.nFingers = 0;
	for (int j=0; j<blob.myBlob.nPts; j++){
		
		if (!bInRun){
			if (bFingerPointRuns[j] == true){
				bInRun = true;
				startRun = j;
			}
		} else {
			if (bFingerPointRuns[j] == false){
				bInRun = false;
				//printf("run from %i to %i \n", startRun, j);
				float maximumMin = 0;
				int indexOfMaxMin = -1;
				
				if (j - startRun > 10){
				for (int k = startRun; k < j; k++){
					float c = blob.curvatureAtPt[k];
					if (c < maximumMin){
						maximumMin = c;
						indexOfMaxMin = k;
					}
				}
				}
				if (indexOfMaxMin != -1){
					
					
					blob.fingerPos[blob.nFingers] = blob.myBlob.pts[indexOfMaxMin];
					
					// try to fit a line here:
					fitLineThroughPts(blob, indexOfMaxMin, blob.nFingers);
					
					if (blob.nFingers < MAX_NUM_FINGERS-1){
						blob.nFingers++;
					}
					
					
				}
			}
		
		}
	}
	
}


//------------------------------------------------------------
void videoHandFingerDetector::finger(handBlob	&blob) {
	ofPoint point1, point2, point3;
	
	for (int i = 0; i < (blob.myBlob.nPts - 2); i++) {
		point1 = blob.myBlob.pts[i];
		point2 = blob.myBlob.pts[i+1];		
		point3 = blob.myBlob.pts[i+2];
		
		if(point2.y < point1.y && point2.y < point3.y) {
			int lineAC1 = pow(((pow((point1.y - point2.y),2)) + (pow((point2.x - point1.x),2))),(1/2));
			float angleA1 = acos(sin(lineAC1));
			int lineAC2 = pow(((pow((point3.y - point2.y),2))+(pow((point3.x - point2.x),2))),(1/2));
			float angleA2 = acos(sin(lineAC2));
			float angle = angleA1 + angleA2;
			//printf("Hoek %f \n", hoek);
			if(angle > 3){
				blob.nFingers++;
				//if(blob.fingerPos[i].x[(blob.nFingers[i]-1)] > 20 && (20+point2.x) == 0){
				if(blob.fingerPos[(blob.nFingers-1)].x > 20 && (20+point2.x) == 0){
					
				} else {
				//	blob.fingerPos[i].x[(blob.nFingers[i]-1)] = 20 + point2.x;
				//	blob.fingerPos[i].y[(blob.nFingers[i]-1)] = 20 + point2.y;
				//	blob.fingerPos[(blob.nFingers-1)].x = 20 + point2.x;
				//	blob.fingerPos[(blob.nFingers-1)].y = 20 + point2.y;
					blob.fingerPos[i].x = 20 + point2.x;
					blob.fingerPos[i].y = 20 + point2.y;
				
				}
				
			}
		}
	}
	printf("Array length %i \n",blob.nFingers);
}

//------------------------------------------------------------
void videoHandFingerDetector::fitLineThroughPts (handBlob	&blob, int pt, int fingerId){

	int count = 0;
	for (int j=0; j< NPTS_FOR_LINE_FIT; j++){
		int myLpt = ((pt - j) + blob.myBlob.nPts) % blob.myBlob.nPts;
		int myRpt = ((pt + j) + blob.myBlob.nPts) % blob.myBlob.nPts;
		lineFitPts[j].x = (blob.myBlob.pts[myLpt].x + blob.myBlob.pts[myRpt].x)/2;
		lineFitPts[j].y = (blob.myBlob.pts[myLpt].y + blob.myBlob.pts[myRpt].y)/2;
	
	}
	
	float slope, intercept, chisqr;
	CVLF.fitLine(lineFitPts, NPTS_FOR_LINE_FIT, slope, intercept, chisqr);
	
	//blob.s->slopeFinger[fingerId] = slope;
	//blob.s->interceptFinger[fingerId] = intercept;
	
	if (fabs(slope) < 0.000001) slope = 0.000001; // / by zero?
	
	ofVec3f pta;
	pta.x = 0;
	pta.y = intercept;

	ofVec3f ptb;
	ptb.y = 0;
	ptb.x = -intercept / slope;
	
	ofVec3f diff = pta - ptb;
	float angle = atan2(diff.y, diff.x);
	
	blob.fingerAngle[fingerId] = angle;
	//printf("%f %f %f \n", slope, intercept, chisqr);

}
		