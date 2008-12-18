#include "ofxCvVTColorImage.h"

void ofxCvVTColorImage::setFromCVImage(IplImage * image){
	cvImage = image;
}
