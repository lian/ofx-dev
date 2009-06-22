#ifndef POINT_RECORDER_H
#define POINT_RECORDER_H

#include "ofMain.h"

class pointRecorder {

	public:
	
        pointRecorder();
	
		void addPoint(ofPoint pt);
		void draw();
	
		int	 maxNumPts;
		vector <ofPoint> pts;
		void drawArrow(float oX, float oY,float nX, float nY);
	

};

#endif // POINT_RECORDER_H
