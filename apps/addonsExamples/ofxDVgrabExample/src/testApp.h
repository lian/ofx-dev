#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofDVUtils.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		void exit();

		unsigned char * 	videoPixels;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;
		ofDVUtils			dvUtils;


	private:
		char                buf[255];
		char                buf2[255];
		float 	            mytimeNow, mytimeThen, myframeRate;
		double 	            myfps;
		int                 myframes;

		bool                useTexture;
};

#endif
