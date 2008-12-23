#ifndef _OFX_TOUCHAPPRELAY
#define _OFX_TOUCHAPPRELAY


#include "ofSimpleApp.h"
#include "ofxTouchApp.h"



class ofxTouchAppRelay : public ofSimpleApp {

  public:

    ofxTouchAppRelay(ofxTouchApp* _TouchAppPtr) : ofSimpleApp() {
        TouchAppPtr = _TouchAppPtr;
    }

    
    void setup(){ TouchAppPtr->_setup(); }
    void update(){ TouchAppPtr->_update(); }
    void draw(){ TouchAppPtr->_draw(); }
    void exit(){ TouchAppPtr->_exit(); }
    
    
    void keyPressed(int key ){ TouchAppPtr->_keyPressed(key); }
    void keyReleased(int key ){ TouchAppPtr->_keyReleased(key); }
    
    void mouseMoved( int x, int y ){ TouchAppPtr->_mouseMoved(x,y); }
    void mouseDragged( int x, int y, int button ){ TouchAppPtr->_mouseDragged(x,y,button); }
    void mousePressed( int x, int y, int button ){ TouchAppPtr->_mousePressed(x,y,button); }
    void mouseReleased(){ TouchAppPtr->_mouseReleased(); }

    //virtual void audioReceived 	(float * input, int bufferSize, int nChannels) {} 
    //virtual void audioRequested (float * output, int bufferSize, int nChannels) {}	

    
    ofxTouchApp* TouchAppPtr;

};

#endif
