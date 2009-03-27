#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "SimpleWebScraper.h"
#include "ofMemoryImage.h"

	

/*

x Retrieve text + images with SimpleWebScraper (merge with WebImageLoader)
x threaded
x ofMemoryImage to load images from memory.
- memory leak
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
		
		// callback events ----------------------------------------------------------
		void onTextReceived(const void* pSender, string& response) {
			cout << "text received :" << endl;
			resp = response;
		}
		
		void onUnthreadedStreamReceived(const void* pSender, StreamEventArgs & args_) {
			cout << "unthreaded stream received. " << endl;
			memImg.loadFromData(args_.buff,args_.bytesToRead);
		}
		
		void onThreadedStreamReceived(const void* pSender, StreamEventArgs & args_) {
		
			cout << "threaded stream received. " << endl;
			args = &args_;
			threadedMemImage.loadFromData(args_.buff,args_.bytesToRead);
			received = true;
		}
		
		bool received;

        SimpleWebScraper sws;		

		string			resp;
		ofMemoryImage	memImg;
		ofMemoryImage	threadedMemImage;
		StreamEventArgs * args;
		ofTexture tx[4];
		unsigned char ** pixArr;
		int txCount;
};

#endif
