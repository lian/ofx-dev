#ifndef _VIDEO_HAND_CONSTANTS_
#define _VIDEO_HAND_CONSTANTS_



#define MAX_NUM_FINGERS				10			//?
#define MAX_CONTOUR_LENGTH			10000
//------------------------------
typedef struct {
	
	ofxCvBlob 			myBlob;	
	float 				curvatureAtPt[MAX_CONTOUR_LENGTH];
	int 				nFingers;
	ofPoint 			fingerPos[MAX_NUM_FINGERS];
	float 				fingerAngle[MAX_NUM_FINGERS];
	
} handBlob;	



typedef struct {

	ofPoint 			pos;
	float 				energy;
	bool 				bFoundMeThisFrame;
	float 				birthday;
	
} trackedFinger;


#endif	
