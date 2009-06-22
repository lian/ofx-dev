#ifndef _CV_LINE_FITTER
#define _CV_LINE_FITTER



#include "ofxOpenCV.h"
#include "Matrix.h"

//=================================================================================
class cvLineFitter {

	public:

		void fitLine(ofPoint * pts, int nPts, float &slope, float &intercept, float &chiSqr);
		
		
};







#endif 
























