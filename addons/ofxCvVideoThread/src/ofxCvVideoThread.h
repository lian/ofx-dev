#ifndef OFVIDEOTHREAD_H_
#define OFVIDEOTHREAD_H_



#include "ofxThread.h"
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"

#include "ofxCvGrayscaleImage.h"
#include "ofxCvColorImage.h"
#include "ofxCvVTColorImage.h"
#include "ofxCvImage.h"


enum ofxVThreadImgType{
	OFX_VTHREAD_PLAIN_RGB24,
	OFX_VTHREAD_CV_COLOR,
	OFX_VTHREAD_CV_GREY
};

class ofxCvVThreadEventManager;
class ofxCvVThreadListener;

class ofxCvVideoThread: public ofxThread, 
				public ofDrawListener, 
				public ofUpdateListener
{
public:
	ofxCvVideoThread();
	virtual ~ofxCvVideoThread();
	
	void 			threadedFunction();
	void 			play();
    void 			stop();

	bool 			isFrameNew();
	void			close();
	void 			init(int w, int h, ofxVThreadImgType imgType);

	
	
	unsigned char 	* 		getPixels();
	ofxCvColorImage *		getCvColorImage();
	ofxCvGrayscaleImage *	getCvGrayImage();
	
	void 			setVerbose(bool bTalkToMe);
	void			setDeviceID(int _deviceID);

	
	void			update();
	void 			draw();	
	void			draw( int x, int y );
	void			draw( int x, int y, int w, int h );
	void			addReadingThread();
	void			removeReadingThread();
	
	

	CvCapture* 		 	vidGrabber;
	unsigned int		width, height;
	int					x, y;
	float  				speed;
	//bool 				bLoaded;	
	long				frame;
	ofxVThreadImgType	imgType;
	

private:
	
	bool					_isPaused;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvVTColorImage		colorImg;
	int						_deviceID;
	bool					_bTalkToMe;
	bool					_isFrameNew;
	int						readingThreads;					
	
	
	
	
	
//--------------------------------------------------------------------------------
//  events:
	
public:
	void			addNewFrameListener(ofxCvVThreadListener * listener);
	void			removeNewFrameListener(ofxCvVThreadListener * listener);
	
private:
	ofxCvVThreadEventManager * eventManager;
};

#endif /*OFVIDEOTHREAD_H_*/
