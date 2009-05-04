#ifndef _TEST_APP
#define _TEST_APP

#define WIDTH			800
#define HEIGHT			450
#define BLOBS_WIDTH		160
#define BLOBS_HEIGHT	90
#define BLOBS_TOTAL		3

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void saveOutputImage();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		ofTexture		tex;
		unsigned char	*texPixels;
	
		int numBlobs;
		int *blogPx;
		int *blogPy;
	
		int *blogDx;
		int *blogDy;
	
		int *vy;
		int *vx; 
	
		int					screenGrabCount;
		ofImage 			screenGrab;

};

#endif
