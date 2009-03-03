/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/



#include "ofMain.h"
#include "ofSoundStream.h"
#import <UIKit/UIKit.h>
#include <AudioToolbox/AudioToolbox.h>

#include "ofxiPhone.h"

//static int							nInputChannels	= 0;
//static int							nOutputChannels = 0;
//static int							nBuffers		= 0;


static ofBaseApp					*OFSAptr		= NULL;
static AudioQueueLevelMeterState	*levelMeters	= NULL;
static UInt32						levelMeterSize	= 0;


static bool							isSetup			= false;
static bool							isRunning		= false;
static bool							hasAudioIn		= false;


static struct AQRecorderState {
    AudioStreamBasicDescription  mDataFormat;
    AudioQueueRef                mQueue;
    AudioQueueBufferRef          *mBuffers;
    AudioFileID                  mAudioFile;
    UInt32                       bufferByteSize;
    SInt64                       mCurrentPacket;
} aqData;


static void audioInputCallback(void *aqData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer, const AudioTimeStamp *inStartTime, UInt32 inNumPackets, const AudioStreamPacketDescription *inPacketDesc) {
	AQRecorderState *pAqData = (AQRecorderState *) aqData; 	
	
	// check if CBR and if so calculate number of packets. if VBR inNumPackets is passed in as a parameter
	if(inNumPackets == 0 && pAqData->mDataFormat.mBytesPerPacket != 0) inNumPackets = inBuffer->mAudioDataByteSize / pAqData->mDataFormat.mBytesPerPacket;

	pAqData->mCurrentPacket += inNumPackets; 

	if (isRunning == 0) return;
	AudioQueueEnqueueBuffer(pAqData->mQueue, inBuffer, 0, NULL);
	
	AudioQueueGetProperty(inAQ, kAudioQueueProperty_CurrentLevelMeter, levelMeters, &levelMeterSize);
//	printf("audioInputCallback: %i, %.3f %.3f\n", levelMeterSize, levelMeters[0].mAveragePower, levelMeters[0].mPeakPower);
}


static inline void checkSoundStreamIsRunning() {
	if(!isSetup) ofSoundStreamSetup(0, 1, 22050, 22050 * 2/60, 2);
}


float iPhoneGetMicAverageLevel() {
//	if(!hasAudioIn) return 0;
	
	checkSoundStreamIsRunning();
#if TARGET_IPHONE_SIMULATOR
	levelMeters[0].mAveragePower = sin(ofGetElapsedTimef() * 1.5f) * 0.5f + 0.5f;
#endif	
	return levelMeters[0].mAveragePower;
}

float iPhoneGetMicPeakLevel() {
//	if(!hasAudioIn) return 0;

	checkSoundStreamIsRunning();
#if TARGET_IPHONE_SIMULATOR
	levelMeters[0].mPeakPower = cos(ofGetElapsedTimef() * 1.5f) * 0.5f + 0.5f;
#endif	
	return levelMeters[0].mPeakPower;
}

bool iPhoneHasAudioIn() {
	return hasAudioIn;
}




//---------------------------------------------------------
void ofSoundStreamSetup(int nOutputs, int nInputs, ofBaseApp * OFSA){
	ofSoundStreamSetup(nOutputs, nInputs, OFSA, 44100, 256, 2);
}

//---------------------------------------------------------
void ofSoundStreamSetup(int nOutputs, int nInputs, int sampleRate, int bufferSize, int nBuffers){
	ofSoundStreamSetup(nOutputs, nInputs, NULL, sampleRate, bufferSize, nBuffers);
}

//---------------------------------------------------------
void ofSoundStreamSetup(int nOutputs, int nInputs, ofBaseApp * OFSA, int sampleRate, int bufferSize, int nBuffers) {
	printf("ofSoundStreamSetup nOutputs: %i,  nInputs: %i, OFSA: %p, sampleRate: %i, bufferSize: %i, nBuffers: %i\n", nOutputs, nInputs, OFSA, sampleRate, bufferSize, nBuffers);
	
	// check to see if the device is an iPhone or not
	hasAudioIn = iPhoneGetDeviceType() == OF_DEVICE_IPHONE;
//	if(!hasAudioIn) return;
	
#if TARGET_IPHONE_SIMULATOR
	levelMeterSize = 8;
	levelMeters = (AudioQueueLevelMeterState*) malloc(levelMeterSize);
#else
	
	ofSoundStreamClose();	// cleanup and close if currently already stream setup
	
	OFSAptr 			= OFSA;
	
	// set Audio Queue data format
	aqData.mDataFormat.mFormatID			= kAudioFormatLinearPCM;
	aqData.mDataFormat.mSampleRate			= sampleRate;
	aqData.mDataFormat.mChannelsPerFrame	= nInputs;
	aqData.mDataFormat.mBitsPerChannel		= 16;
	aqData.mDataFormat.mBytesPerPacket		= aqData.mDataFormat.mBytesPerFrame = aqData.mDataFormat.mChannelsPerFrame * sizeof(SInt16);
	aqData.mDataFormat.mFramesPerPacket		= 1;
	aqData.mDataFormat.mFormatFlags			= kLinearPCMFormatFlagIsBigEndian | kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;

	aqData.bufferByteSize					= bufferSize;
	aqData.mCurrentPacket					= 0;
	
	// create input Audio Queue
	AudioQueueNewInput(&aqData.mDataFormat, audioInputCallback, &aqData, NULL, kCFRunLoopCommonModes, 0, &aqData.mQueue);
	
	// allocate buffers
	aqData.mBuffers = new AudioQueueBufferRef[nBuffers];
	for (int i = 0; i < nBuffers; ++i) {
		AudioQueueAllocateBuffer(aqData.mQueue, aqData.bufferByteSize, &aqData.mBuffers[i]);
		AudioQueueEnqueueBuffer(aqData.mQueue, aqData.mBuffers[i], 0, NULL);
	}
	
	// enable Audio Level Metering
	UInt32 trueValue = true;
	AudioQueueSetProperty(aqData.mQueue, kAudioQueueProperty_EnableLevelMetering, &trueValue, sizeof (UInt32));
	
	// get size required for Level Metering and allocate buffer
	AudioQueueGetPropertySize(aqData.mQueue, kAudioQueueProperty_CurrentLevelMeter, &levelMeterSize);
	levelMeters = (AudioQueueLevelMeterState*) malloc(levelMeterSize);
//	printf("iPhoneEnableLevelMetering levelMeterBufferSize:%i\n", levelMeterSize);
	
	// start stream
	ofSoundStreamStart();
#endif
	
	isSetup = true;
}

//---------------------------------------------------------
void ofSoundStreamStop(){
	if(isRunning) {
		printf("ofSoundStreamStop\n");
		AudioQueueStop(aqData.mQueue, true);
		isRunning = false;
	}
}



//---------------------------------------------------------
void ofSoundStreamStart(){
	if(isRunning == false) {
		printf("ofSoundStreamStart\n");
		AudioQueueStart(aqData.mQueue, NULL);
		isRunning = true;
	}
}


//---------------------------------------------------------
void ofSoundStreamClose() {
	if(isSetup) {
		printf("ofSoundStreamClose\n");
		AudioQueueDispose(aqData.mQueue, true);
		delete aqData.mBuffers;
		delete levelMeters;
	}
}


//---------------------------------------------------------
void ofSoundStreamListDevices(){
	printf("ofSoundStreamListDevices\n");
}
