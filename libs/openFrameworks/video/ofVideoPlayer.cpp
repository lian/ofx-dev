#include "ofVideoPlayer.h"
#include "ofUtils.h"




//---------------------------------------------------------------------------
ofVideoPlayer::ofVideoPlayer ()
:	
	width(0),
	height(0),
	speed(1),
	bLoaded(false),

	impl(NULL),
	nFrames(0),
	pixels(NULL),
	bHavePixelsChanged(false),
	bUseTexture(true),
	allocated(false),
	
	bStarted(false),
	bPlaying(false),
	bPaused(false),
	bIsFrameNew(false)
{
	implInit(this);
}

//---------------------------------------------------------------------------
unsigned char * ofVideoPlayer::getPixels(){
	return pixels;
}

//------------------------------------
//for getting a reference to the texture
ofTexture & ofVideoPlayer::getTextureReference(){
	if(!tex.bAllocated() ){
		ofLog(OF_LOG_WARNING, "ofVideoPlayer - getTextureReference - texture is not allocated");
	}
	return tex;
}


//---------------------------------------------------------------------------
bool ofVideoPlayer::isFrameNew(){

	return bIsFrameNew;

}

//--------------------------------------------------------------------
void ofVideoPlayer::update(){
	idleMovie();
}

//---------------------------------------------------------------------------
void ofVideoPlayer::idleMovie(){

	implEnterIdleMovie();

		// ---------------------------------------------------
		// 		on all platforms,
		// 		do "new"ness ever time we idle...
		// 		before "isFrameNew" was clearning,
		// 		people had issues with that...
		// 		and it was badly named so now, newness happens
		// 		per-idle not per isNew call
		// ---------------------------------------------------
	if (bLoaded == true){
		bIsFrameNew = bHavePixelsChanged;
		if (bHavePixelsChanged == true) {
			bHavePixelsChanged = false;
		}
	}

}

//---------------------------------------------------------------------------
void ofVideoPlayer::closeMovie(){
	implCloseMovie();
    bLoaded = false;

}

//---------------------------------------------------------------------------
void ofVideoPlayer::close(){
	closeMovie();
}

//---------------------------------------------------------------------------
ofVideoPlayer::~ofVideoPlayer(){
	closeMovie();
	if (pixels != NULL){
		delete[] pixels;
	}

	tex.clear();
	implFree();
}





//---------------------------------------------------------------------------
bool ofVideoPlayer::loadMovie(string name) {
	return implLoadMovie(name);
}



//--------------------------------------------------------
void ofVideoPlayer::start(){
	implStart();
}

//--------------------------------------------------------
void ofVideoPlayer::play(){
	if (!bStarted){
	 	start();
	}
	else {
		implPlay();
	}
}

//--------------------------------------------------------
void ofVideoPlayer::stop(){
	implStop();
}

//--------------------------------------------------------
void ofVideoPlayer::setVolume(int volume){
	implSetVolume(volume);
}


//--------------------------------------------------------
void ofVideoPlayer::setLoopState(int state){
	implSetLoopState(state);
}


//---------------------------------------------------------------------------
void ofVideoPlayer::setPosition(float pct){
	implSetPosition(pct);
}

//---------------------------------------------------------------------------
void ofVideoPlayer::setFrame(int frame){
	implSetFrame(frame);
}


//---------------------------------------------------------------------------
float ofVideoPlayer::getDuration(){
	return implGetDuration();
}

//---------------------------------------------------------------------------
float ofVideoPlayer::getPosition(){
	return implGetPosition();
}

//---------------------------------------------------------------------------
int ofVideoPlayer::getCurrentFrame(){

	int frame = 0;

	// zach I think this may fail on variable length frames...
	float pos = getPosition();


	float  framePosInFloat = ((float)getTotalNumFrames() * pos);
	int    framePosInInt = (int)framePosInFloat;
	float  floatRemainder = (framePosInFloat - framePosInInt);
	if (floatRemainder > 0.5f) framePosInInt = framePosInInt + 1;
	//frame = (int)ceil((getTotalNumFrames() * getPosition()));
	frame = framePosInInt;

	return frame;

}


//---------------------------------------------------------------------------
bool ofVideoPlayer::getIsMovieDone(){
	return implGetIsMovieDone();

}

//---------------------------------------------------------------------------
void ofVideoPlayer::firstFrame(){

	setFrame(0);

}

//---------------------------------------------------------------------------
void ofVideoPlayer::nextFrame(){

	setFrame(getCurrentFrame() + 1);

}

//---------------------------------------------------------------------------
void ofVideoPlayer::previousFrame(){

	setFrame(getCurrentFrame() - 1);

}



//---------------------------------------------------------------------------
void ofVideoPlayer::setSpeed(float _speed){
	speed = _speed;
	implSetSpeed(speed);
}

//---------------------------------------------------------------------------
float ofVideoPlayer::getSpeed(){
	return speed;
}

//---------------------------------------------------------------------------
void ofVideoPlayer::setPaused(bool _bPause){

	bPaused = _bPause;
	implSetPaused(_bPause);
}

//------------------------------------
void ofVideoPlayer::setUseTexture(bool bUse){
	bUseTexture = bUse;
}

//we could cap these values - but it might be more useful
//to be able to set anchor points outside the image

//----------------------------------------------------------
void ofVideoPlayer::setAnchorPercent(float xPct, float yPct){
    if (bUseTexture)tex.setAnchorPercent(xPct, yPct);
}

//----------------------------------------------------------
void ofVideoPlayer::setAnchorPoint(int x, int y){
    if (bUseTexture)tex.setAnchorPoint(x, y);
}

//----------------------------------------------------------
void ofVideoPlayer::resetAnchor(){
   	if (bUseTexture)tex.resetAnchor();
}

//------------------------------------
void ofVideoPlayer::draw(float _x, float _y, float _w, float _h){
	if (bUseTexture){
		tex.draw(_x, _y, _w, _h);
	}
}

//------------------------------------
void ofVideoPlayer::draw(float _x, float _y){
	draw(_x, _y, (float)width, (float)height);
}

//------------------------------------
int ofVideoPlayer::getTotalNumFrames(){
	return implGetTotalNumFrames();

}

//----------------------------------------------------------
float ofVideoPlayer::getHeight(){
	return (float)height;
}

//----------------------------------------------------------
float ofVideoPlayer::getWidth(){
	return (float)width;
}
