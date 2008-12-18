#include "ofxThread.h"

//-------------------------------------------------
ofxThread::ofxThread(){
	threadRunning = false;
}

//-------------------------------------------------
ofxThread::~ofxThread(){
	stopThread();
}

//-------------------------------------------------
bool ofxThread::isThreadRunning(){
	//should be thread safe - no writing of vars here
	if(threadRunning) return true;
	else return false;
}

//-------------------------------------------------
void ofxThread::startThread(bool _blocking, bool _verbose){

	//have to put this here because the thread can be running
	//before the call to create it returns
	threadRunning	= true;

	#ifdef TARGET_WIN32
		InitializeCriticalSection(&critSec);
		myThread = (HANDLE)_beginthreadex(NULL, 0, this->thread,  (void *)this, 0, NULL);
	#else
		pthread_mutex_init(&myMutex, NULL);
		pthread_create(&myThread, NULL, thread, (void *)this);
	#endif

	locked			= false;
	blocking		=	_blocking;
	verbose			= _verbose;
}

//-------------------------------------------------
//returns false if it can't lock
bool ofxThread::lock(){
	if(!threadRunning){
		if(verbose)printf("ofxThread: need to call startThread first\n");
		return false;
	}

	if(locked){
		if(verbose)printf("ofxThread: already locked! \n");
		return false;
	}

	#ifdef TARGET_WIN32
		if(blocking)EnterCriticalSection(&critSec);
		else {
			if(!TryEnterCriticalSection(&critSec)){
				if(verbose)printf("ofxThread: mutext is busy \n");
				return false;
			}
		}
		if(verbose)printf("ofxThread: we are in -- mutext is now locked \n");
	#else

		if(!blocking){
			pthread_mutex_lock(&myMutex);
			if(verbose)printf("ofxThread: we are in -- mutext is now locked \n");
		}else{
			int value = pthread_mutex_trylock(&myMutex);
			if(value == 0){
				if(verbose)printf("ofxThread: we are in -- mutext is now locked \n");
			}
			else{
				if(verbose)printf("ofxThread: mutext is busy locked =  %i \n",locked );
				return false;
			}
		}
	#endif

	locked = true;
	return true;
}

//-------------------------------------------------
bool ofxThread::unlock(){

	if(!threadRunning){
		if(verbose)printf("ofxThread: need to call startThread first\n");
		return false;
	}

	#ifdef TARGET_WIN32
		LeaveCriticalSection(&critSec);
	#else
		pthread_mutex_unlock(&myMutex);
	#endif

	locked = false;
	if(verbose)printf("ofxThread: we are out -- mutext is now unlocked \n");

	return true;
}

//-------------------------------------------------
void ofxThread::stopThread(){
	if(threadRunning){
		#ifdef TARGET_WIN32
			CloseHandle(myThread);
		#else
			pthread_mutex_destroy(&myMutex);
			pthread_detach(myThread);
		#endif
		if(verbose)printf("ofxThread: thread stopped\n");
		threadRunning = false;
	}else{
		if(verbose)printf("ofxThread: thread already stopped\n");
	}
}

