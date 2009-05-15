#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxVectorMath.h"

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
		void mouseReleased();
		
		vector <ofxVec2f> ptsList;
		vector <ofxVec2f> leftNormals;
		vector <ofxVec2f> rightNormals;
		vector <float> speedList; 
		
		ofxVec2f prevPoint;
		
		bool recording; 
		float playPos;
		
};

#endif
