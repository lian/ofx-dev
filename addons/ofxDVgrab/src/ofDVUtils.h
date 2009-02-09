#ifndef OFDVUTILS_H_
#define OFDVUTILS_H_

#include "dvgrab.h"
#include "ofTexture.h"

typedef enum VideoType { OF_DV_PAL = 1, OF_DV_NTSC};

typedef enum DeinterlaceType { OF_DV_NO_DEINTERLACE = 0, OF_DV_AVERAGE_DEINTERLACE, OF_DV_LINEAR_BLEND_DEINTERLACE};

class ofDVUtils{

public:

	ofDVUtils();
	~ofDVUtils();

	void                    initGrabber(bool _useTexture, unsigned int _deinterlace, VideoType _videoType);
	void                    grabFrame();
	unsigned char*          getPixels();
	bool                    isFrameNew();
	void                    draw(float _x, float _y, float _w, float _h);
	void                    draw(float _x, float _y);

	protected:
	DVgrab                  *dvgrab;
	int                     width;
	int                     height;
    bool					bUseTexture;
    ofTexture 				tex;
    bool 					bGrabberInited;
    bool 					bIsFrameNew;
    unsigned char * 		pixels;
};

#endif /*OFDVUTILS_H_*/
