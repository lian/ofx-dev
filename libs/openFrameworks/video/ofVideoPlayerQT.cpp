#include "ofVideoPlayerQT.h"

#ifdef OF_VIDEO_PLAYER_QUICKTIME

bool  	createMovieFromPath(char * path, Movie &movie);
bool 	createMovieFromPath(char * path, Movie &movie){



	Boolean 	isdir			= false;
	OSErr 		result 			= 0;
	FSSpec 		theFSSpec;

	short 		actualResId 	= DoTheRightThing;

	#ifdef TARGET_WIN32
		result = NativePathNameToFSSpec (path, &theFSSpec, 0);
		if (result != noErr) {
			ofLog(OF_LOG_ERROR,"NativePathNameToFSSpec failed %d", result);
			ofLog(OF_LOG_ERROR,"Error loading movie");
			return false;
		}

	#endif



	#ifdef TARGET_OSX
		FSRef 		fsref;
		result = FSPathMakeRef((const UInt8*)path, &fsref, &isdir);
		if (result) {
			ofLog(OF_LOG_ERROR,"FSPathMakeRef failed %d", result);
			ofLog(OF_LOG_ERROR,"Error loading movie");
			return false;
		}
		result = FSGetCatalogInfo(&fsref, kFSCatInfoNone, NULL, NULL, &theFSSpec, NULL);
		if (result) {
			ofLog(OF_LOG_ERROR,"FSGetCatalogInfo failed %d", result);
			ofLog(OF_LOG_ERROR,"Error loading movie");
			return false;
		}
	#endif


	short movieResFile;
	result = OpenMovieFile (&theFSSpec, &movieResFile, fsRdPerm);
	if (result == noErr) {

		short   movieResID = 0;
		result = NewMovieFromFile(&movie, movieResFile, &movieResID, (unsigned char *) 0, newMovieActive, (Boolean *) 0);
		if (result == noErr){
			CloseMovieFile (movieResFile);
		} else {
			ofLog(OF_LOG_ERROR,"NewMovieFromFile failed %d", result);
			return false;
		}
	} else {
		ofLog(OF_LOG_ERROR,"OpenMovieFile failed %d", result);
		return false;
	}

	return true;
}

//--------------------------------------------------------------
bool createMovieFromURL(string urlIn,  Movie &movie){
	char * url = (char *)urlIn.c_str();
	Handle urlDataRef;

	OSErr err;

	urlDataRef = NewHandle(strlen(url) + 1);
	if ( ( err = MemError()) != noErr){ ofLog(OF_LOG_ERROR,"createMovieFromURL: error creating url handle"); return false;}

	BlockMoveData(url, *urlDataRef, strlen(url) + 1);

	err = NewMovieFromDataRef(&movie, newMovieActive,nil, urlDataRef, URLDataHandlerSubType);
	DisposeHandle(urlDataRef);

	if(err != noErr){
		ofLog(OF_LOG_ERROR,"createMovieFromURL: error loading url");
		return false;
	}else{
		return true;
	}

	return false;
}



//--------------------------------------------------------------
OSErr 	DrawCompleteProc(Movie theMovie, long refCon);
OSErr 	DrawCompleteProc(Movie theMovie, long refCon){

	ofVideoPlayer * ofvp = (ofVideoPlayer *)refCon;

	#if defined(TARGET_OSX) && defined(BIG_ENDIAN)
		convertPixels(ofvp->impl->offscreenGWorldPixels, ofvp->pixels, ofvp->width, ofvp->height);
	#endif

	ofvp->bHavePixelsChanged = true;
	if (ofvp->bUseTexture == true){
		ofvp->tex.loadData(ofvp->pixels, ofvp->width, ofvp->height, GL_RGB);
	}

	return noErr;
}



ofVideoPlayerImpl :: ofVideoPlayerImpl(Generic *generic)
:	generic(generic),
	offscreenGWorld(NULL),
	moviePtr(NULL),
	offscreenGWorldPixels(NULL)
{}

ofVideoPlayerImpl :: ~ofVideoPlayerImpl() {
	if(offscreenGWorldPixels)	delete[] offscreenGWorldPixels;
	if(offscreenGWorld)			DisposeGWorld(offscreenGWorld);
}

void ofVideoPlayerImpl :: createImgMemAndGWorld(ofVideoPlayer *ofv){
	Rect movieRect;
	movieRect.top 			= 0;
	movieRect.left 			= 0;
	movieRect.bottom 		= ofv->height;
	movieRect.right 		= ofv->width;
	offscreenGWorldPixels 	= new unsigned char[4 * ofv->width * ofv->height + 32];
	ofv->pixels					= new unsigned char[ofv->width*ofv->height*3];

	#if defined(TARGET_OSX) && defined(BIG_ENDIAN)
		QTNewGWorldFromPtr (&(offscreenGWorld), k32ARGBPixelFormat, &(movieRect), NULL, NULL, 0, (offscreenGWorldPixels), 4 * ofv->width);
	#else
		QTNewGWorldFromPtr (&(offscreenGWorld), k24RGBPixelFormat, &(movieRect), NULL, NULL, 0, (pixels), 3 * ofv->width);
	#endif

	LockPixels(GetGWorldPixMap(offscreenGWorld));
	SetGWorld (offscreenGWorld, NULL);
	SetMovieGWorld (moviePtr, offscreenGWorld, nil);
	//------------------------------------ texture stuff:
	if (ofv->bUseTexture){
		// create the texture, set the pixels to black and
		// upload them to the texture (so at least we see nothing black the callback)
		ofv->tex.allocate(ofv->width,ofv->height,GL_RGB);
		memset(ofv->pixels, 0, ofv->width*ofv->height*3);
		ofv->tex.loadData(ofv->pixels, ofv->width, ofv->height, GL_RGB);
		ofv->allocated = true;
	}
}



//////////////////////////////////
void ofVideoPlayer :: implInit(ofVideoPlayer *generic) {
	impl = new ofVideoPlayerImpl(generic);
}

void ofVideoPlayer :: implFree() {
	delete impl;
	impl = NULL;
}

void ofVideoPlayer :: implEnterIdleMovie() {
	if (bLoaded == true) {
		#if defined(TARGET_WIN32) || defined(QT_USE_MOVIETASK)
			MoviesTask(mImpl->moviePtr, 0);
		#endif
	}
}

void ofVideoPlayer :: implCloseMovie() {
	DisposeMovie (impl->moviePtr);
	#ifdef TARGET_WIN32
		DisposeMovieDrawingCompleteUPP (myDrawCompleteProc);
	#endif
	impl->moviePtr = NULL;
}

bool ofVideoPlayer :: implLoadMovie(string name) {
	initializeQuicktime();			// init quicktime
	closeMovie();					// if we have a movie open, close it
	bLoaded 				= false;	// try to load now

	if( name.substr(0, 7) == "http://" || name.substr(0,7) == "rtsp://" ){
		if(! createMovieFromURL(name, impl->moviePtr) ) return false;
	}else{
		name 					= ofToDataPath(name);
		if( !createMovieFromPath((char *)name.c_str(), impl->moviePtr) ) return false;
	}

	bool bDoWeAlreadyHaveAGworld = false;
	if (width != 0 && height != 0){
		bDoWeAlreadyHaveAGworld = true;
	}
	Rect movieRect;
	GetMovieBox(impl->moviePtr, &(movieRect));
	if (bDoWeAlreadyHaveAGworld){
		// is the gworld the same size, then lets *not* de-allocate and reallocate:
		if (width == movieRect.right &&
			height == movieRect.bottom){
			SetMovieGWorld (impl->moviePtr, impl->offscreenGWorld, nil);
		} else {
			width 	= movieRect.right;
			height 	= movieRect.bottom;
			delete(pixels);
			delete(impl->offscreenGWorldPixels);
			if ((impl->offscreenGWorld)) DisposeGWorld((impl->offscreenGWorld));
			impl->createImgMemAndGWorld(this);
		}
	} else {
		width	= movieRect.right;
		height 	= movieRect.bottom;
		impl->createImgMemAndGWorld(this);
	}

	if (impl->moviePtr == NULL){
		return false;
	}

	//----------------- callback method
	MovieDrawingCompleteUPP myDrawCompleteProc;
	myDrawCompleteProc = NewMovieDrawingCompleteUPP (DrawCompleteProc);
	SetMovieDrawingCompleteProc (impl->moviePtr, movieDrawingCallWhenChanged,  myDrawCompleteProc, (long)this);

	// ------------- get the total # of frames:
	nFrames				= 0;
	TimeValue			curMovieTime;
	curMovieTime		= 0;
	TimeValue			duration;

	//OSType whichMediaType	= VIDEO_TYPE; // mingw chokes on this
	OSType whichMediaType	= FOUR_CHAR_CODE('vide');

	short flags				= nextTimeMediaSample + nextTimeEdgeOK;

	while( curMovieTime >= 0 ) {
		nFrames++;
		GetMovieNextInterestingTime(impl->moviePtr,flags,1,&whichMediaType,curMovieTime,0,&curMovieTime,&duration);
		flags = nextTimeMediaSample;
	}
	nFrames--; // there's an extra time step at the end of themovie




	// ------------- get some pixels in there ------
	GoToBeginningOfMovie(impl->moviePtr);
	SetMovieActiveSegment(impl->moviePtr, -1,-1);
	MoviesTask(impl->moviePtr,0);

	#if defined(TARGET_OSX) && defined(BIG_ENDIAN)
		convertPixels(impl->offscreenGWorldPixels, pixels, width, height);
	#endif

	if (bUseTexture == true){
		tex.loadData(pixels, width, height, GL_RGB);
	}

	bStarted 				= false;
	bLoaded 				= true;
	bPlaying 				= false;
	bHavePixelsChanged 		= false;
	speed 					= 1;

	return true;
}

void ofVideoPlayer :: implStart() {
	if (bLoaded == true && bStarted == false){
		SetMovieActive(impl->moviePtr, true);

		//------------------ set the movie rate to default
		//------------------ and preroll, so the first frames come correct

		TimeValue timeNow 	= 	GetMovieTime(impl->moviePtr, 0);
		Fixed playRate 		=	GetMoviePreferredRate(impl->moviePtr); 		//Not being used!

		PrerollMovie(impl->moviePtr, timeNow, X2Fix(speed));
		SetMovieRate(impl->moviePtr,  X2Fix(speed));
		setLoopState(OF_LOOP_NORMAL);

		// get some pixels in there right away:
		MoviesTask(impl->moviePtr,0);
		#if defined(TARGET_OSX) && defined(BIG_ENDIAN)
			convertPixels(impl->offscreenGWorldPixels, pixels, width, height);
		#endif
		bHavePixelsChanged = true;
		if (bUseTexture == true){
			tex.loadData(pixels, width, height, GL_RGB);
		}

		bStarted = true;
		bPlaying = true;
	}
}

void ofVideoPlayer :: implPlay() {
	// ------------ lower level "startMovie"
	// ------------ use desired speed & time (-1,1,etc) to Preroll...
	TimeValue timeNow;
	timeNow = GetMovieTime(impl->moviePtr, nil);
	PrerollMovie(impl->moviePtr, timeNow, X2Fix(speed));
	SetMovieRate(impl->moviePtr,  X2Fix(speed));
	MoviesTask(impl->moviePtr, 0);
}

void ofVideoPlayer :: implStop() {
	StopMovie (impl->moviePtr);
	SetMovieActive (impl->moviePtr, false);
	bStarted = false;
}

void ofVideoPlayer :: implSetVolume(int volume) {
	SetMovieVolume(impl->moviePtr, volume);
}

void ofVideoPlayer :: implSetLoopState(int state) {
	Movie moviePtr = impl->moviePtr;
	TimeBase myTimeBase;
	long myFlags = 0L;
	myTimeBase = GetMovieTimeBase(moviePtr);
	myFlags = GetTimeBaseFlags(myTimeBase);
	switch (state) {
		case OF_LOOP_NORMAL:
			myFlags |= loopTimeBase;
			myFlags &= ~palindromeLoopTimeBase;
			SetMoviePlayHints(moviePtr, hintsLoop, hintsLoop);
			SetMoviePlayHints(moviePtr, 0L, hintsPalindrome);
			break;
		case OF_LOOP_PALINDROME:
			myFlags |= loopTimeBase;
			myFlags |= palindromeLoopTimeBase;
			SetMoviePlayHints(moviePtr, hintsLoop, hintsLoop);
			SetMoviePlayHints(moviePtr, hintsPalindrome, hintsPalindrome);
			break;
		case OF_LOOP_NONE:
			default:
			myFlags &= ~loopTimeBase;
			myFlags &= ~palindromeLoopTimeBase;
			SetMoviePlayHints(moviePtr, 0L, hintsLoop |
			hintsPalindrome);
			break;
	}
	SetTimeBaseFlags(myTimeBase, myFlags);
}

void ofVideoPlayer :: implSetPosition(float pct) {
	TimeRecord tr;
	tr.base 		= GetMovieTimeBase(impl->moviePtr);
	long total 		= GetMovieDuration(impl->moviePtr );
	long newPos 	= (long)((float)total * pct);
	SetMovieTimeValue(impl->moviePtr, newPos);
	MoviesTask(impl->moviePtr,0);
}

void ofVideoPlayer :: implSetFrame(int frame) {
	Movie moviePtr = impl->moviePtr;

	// frame 0 = first frame...

	// this is the simple way...
	//float durationPerFrame = getDuration() / getTotalNumFrames();

	// seems that freezing, doing this and unfreezing seems to work alot
	// better then just SetMovieTimeValue() ;

	if (!bPaused) SetMovieRate(moviePtr, X2Fix(0));

	// this is better with mpeg, etc:
	double frameRate = 0;
	double movieTimeScale = 0;
	MovieGetStaticFrameRate(moviePtr, &frameRate);
	movieTimeScale = GetMovieTimeScale(moviePtr);

	if (frameRate > 0){
		double frameDuration = 1 / frameRate;
		TimeValue t = (TimeValue)(frame * frameDuration * movieTimeScale);
		SetMovieTimeValue(moviePtr, t);
		MoviesTask(moviePtr, 0);
	}

   if (!bPaused) SetMovieRate(moviePtr, X2Fix(speed));
}

float ofVideoPlayer :: implGetDuration() {
	Movie moviePtr = impl->moviePtr;
	return (float) (GetMovieDuration (moviePtr) / (double) GetMovieTimeScale (moviePtr));
}

float ofVideoPlayer :: implGetPosition() {
	Movie moviePtr = impl->moviePtr;
	long total 		= GetMovieDuration(moviePtr);
	long current 	= GetMovieTime(moviePtr, nil);
	float pct 		= ((float)current/(float)total);
	return pct;
}

bool ofVideoPlayer :: implGetIsMovieDone() {
	bool bIsMovieDone = (bool)IsMovieDone(impl->moviePtr);
	return bIsMovieDone;
}

void ofVideoPlayer :: implSetSpeed(float _speed) {
	if (bPlaying == true){
		//setMovieRate actually plays, so let's call it only when we are playing
		SetMovieRate(impl->moviePtr, X2Fix(_speed));
	}
}

void ofVideoPlayer :: implSetPaused(bool _bPause) {
	// there might be a more "quicktime-ish" way (or smarter way)
	// to do this for now, to pause, just set the movie's speed to zero,
	// on un-pause, set the movie's speed to "speed"
	// (and hope that speed != 0...)
	if (bPlaying == true){
		if (bPaused == true) 	SetMovieRate(impl->moviePtr, X2Fix(0));
		else 					SetMovieRate(impl->moviePtr, X2Fix(speed));
	}
}


int ofVideoPlayer :: implGetTotalNumFrames() {
	return nFrames;
}


#endif	// OF_VIDEO_PLAYER_QUICKTIME
