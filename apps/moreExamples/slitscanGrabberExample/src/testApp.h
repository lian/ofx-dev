#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"


/*
in this case we're storing the slitted image in a second buffer and then slicing
it horizontally
*/


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
	
	private:
	
		ofVideoGrabber 	vid;
		unsigned char **    videoData;
		unsigned char **    slitData;
		
		int                 nFramesToRecord;
        int                 maxFramesToRecord;
        int                 nRecorded;
		
		int horizPw, horizPh;
		unsigned char * horizP;
		ofTexture		horizPtex;
		
		ofTexture delayed;
		ofTexture * videoTextures;
		
		
		unsigned char * slitPx;
		ofTexture		slitTex;
		
		
		bool			reverse;
		
        // array of portions;
        struct Portion **   strPortions;
        int                 maxPortions;
		
        
    
        int imgW, imgH, imgColors;
        int pW, pH, pMod;
        int zoom;

        int nPortions;

        ofTrueTypeFont      verdana;
};

#endif	
