#ifndef OFX_TOUCHFILTER
#define OFX_TOUCHFILTER

#include "ofxCvMain.h"


class ofxTouchFilter {
  public:
        
    virtual void allocate( int w, int h ) = 0;    
    virtual void process( ofxCvGrayscaleImage& img ) = 0;
    virtual void draw() = 0;
    virtual void keyPressed( int key ) = 0;
    
};


#endif