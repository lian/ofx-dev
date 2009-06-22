#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "fingerDetector.h"

class testApp : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	fingerDetector fingerFinder;

	
	ofVideoGrabber camera;
	
	ofxCvGrayscaleImage cvBackground;
	ofxCvGrayscaleImage cvGray;
	ofxCvGrayscaleImage cvThresh;
	
	ofxCvColorImage cvColor;
	
	ofxCvContourFinder contour;
	
	int i;
	
	int diffMode;
	int vid_w, vid_h;
	int numBlobs;
	
	bool ffound,hfound;
	
	float threshold;
};

#endif
