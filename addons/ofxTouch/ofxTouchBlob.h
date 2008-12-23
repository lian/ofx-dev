/*
* ofxTouchBlob.h
* openFrameworks
*
* A blob is a homogenous patch represented by a polygonal contour. 
* Typically a blob tracker uses the contour to figure out the blob's
* persistence and "upgrades" it with ids and other temporal 
* information. 
*
*/


#ifndef OFX_TOUCH_BLOB
#define OFX_TOUCH_BLOB

#include <vector>

class ofxTouchBlob {
  public:

    float area;
    float length;
    ofRectangle box;
    ofPoint center;
    
    bool hole;
    vector<ofPoint> contour;
   

    ofxTouchBlob() {
        area = 0.0f;
        length = 0.0f;
        hole = false;        
    }
    
};


#endif


