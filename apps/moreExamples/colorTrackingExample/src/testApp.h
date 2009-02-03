/*
	Tracking colors: tracking laser
      example found at http://www.berio.alg-a.org/spip.php?article145
	
	This is what this color tracking code does: 
	  It takes an incomming image, either from a live cam or a static picture,
	  and converts it from RGB to HSV, which is a better color system for tracking.
	  Then, changing the HSV values, we try to isolate the color that we want	to
	  track. Once we have located the HSV values that fit the color that we
	  want to track, we compare each pixel and see if it is inside the HSV values
	  that corresponds to the target color. If the pixels are between the desired
	  ranges, we convert them to white, if not, we convert them to black. So, as
	  a result we have a thresolded image that totally separates the target color.
*/

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#define OF_ADDON_USING_OFXOPENCV

#include "ofAddons.h"
#include "laserTracking.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

		// Input Source
		ofVideoGrabber			vidGrabber;
        ofImage                 staticImage;

        ofxCvColorImage		    colorImg;
        ofxCvColorImage		    colorImgHSV;

        ofxCvGrayscaleImage		hueImg;
        ofxCvGrayscaleImage		satImg;
        ofxCvGrayscaleImage		valImg;

        ofImage                 calder;

        unsigned char *         colorTrackedPixels;
        ofTexture               trackedTexture;

        int minHue, maxHue, minSat, maxSat, minVal, maxVal;
		float hue, hueWidth, sat, satWidth, val, valWidth;
		
	protected:

		laserTracking LT;	
	
	private:
		
		bool					videoAsInputSource;
};

#endif
