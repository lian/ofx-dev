#ifndef OFXCVVTCOLORIMAGE_H_
#define OFXCVVTCOLORIMAGE_H_

#include "ofxCvColorImage.h"

class ofxCvVTColorImage: public ofxCvColorImage
{
public:
	void setFromCVImage(IplImage * image);
};
#endif /*OFXCVVTCOLORIMAGE_H_*/
