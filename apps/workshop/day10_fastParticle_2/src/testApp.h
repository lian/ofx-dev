#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "particle.h"

class testApp : public ofSimpleApp{
	
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
		
		bool useBinning;
	
		// let's make a vector of them
		vector <particle> particles;
	
		static const int binWidth = 8;
		static const int numBins = 128; // this number should correspond to the width of your window / binWidth
	
		vector <particle *> bin[numBins];
	
		
	
		 
	
};

#endif
	
