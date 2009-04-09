#ifndef _OF_VIDEO_PLAYER_QT
#define _OF_VIDEO_PLAYER_QT

#include "ofConstants.h"

#ifdef OF_VIDEO_PLAYER_QUICKTIME

#include "ofQtUtils.h"
#include "ofVideoPlayer.h"



class ofVideoPlayerImpl {
public:
	typedef ofVideoPlayer	Generic;
	
	ofVideoPlayerImpl(Generic *generic);
	~ofVideoPlayerImpl();
	
	Generic	*			generic;
	MovieController  	thePlayer;
	GWorldPtr 			offscreenGWorld;
	Movie 			 	moviePtr;
	unsigned char * 	offscreenGWorldPixels;	// 32 bit: argb (qt k32ARGBPixelFormat)
	
	
	void				createImgMemAndGWorld(ofVideoPlayer *ofv);
	void				qtGetFrameCount(Movie & movForcount);

};

#endif	// OF_VIDEO_PLAYER_QUICKTIME

#endif	// _OF_VIDEO_PLAYER_QT