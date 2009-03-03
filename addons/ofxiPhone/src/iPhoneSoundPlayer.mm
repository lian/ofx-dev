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
#include "ofSoundPlayer.h"
void ofSoundStopAll(){
}

//--------------------
void ofSoundSetVolume(float vol){
}

//--------------------
float * ofSoundGetSpectrum(int nBands){
	return NULL;
}

// ------------------------------------------------------------
// ------------------------------------------------------------


// now, the individual sound player:
//------------------------------------------------------------
ofSoundPlayer::ofSoundPlayer(){
}

ofSoundPlayer::~ofSoundPlayer(){
}


//---------------------------------------
// this should only be called once
void ofSoundPlayer::initializeFmod(){
}


//---------------------------------------
void ofSoundPlayer::closeFmod(){
}

//------------------------------------------------------------
void ofSoundPlayer::loadSound(string fileName, bool stream){
}

//------------------------------------------------------------
void ofSoundPlayer::unloadSound(){
}

//------------------------------------------------------------
bool ofSoundPlayer::getIsPlaying(){
	return false;
}

//------------------------------------------------------------
float ofSoundPlayer::getSpeed(){
	return 0;
}

//------------------------------------------------------------
float ofSoundPlayer::getPan(){
	return 0;
}

//------------------------------------------------------------
void ofSoundPlayer::setVolume(float vol){
}

//------------------------------------------------------------
void ofSoundPlayer::setPosition(float pct){
}

//------------------------------------------------------------
float ofSoundPlayer::getPosition(){
	return 0;
}

//------------------------------------------------------------
void ofSoundPlayer::setPan(float p){
}


//------------------------------------------------------------
void ofSoundPlayer::setPaused(bool bP){
}


//------------------------------------------------------------
void ofSoundPlayer::setSpeed(float spd){
}


//------------------------------------------------------------
void ofSoundPlayer::setLoop(bool bLp){
}

// ----------------------------------------------------------------------------
void ofSoundPlayer::setMultiPlay(bool bMp){
}

// ----------------------------------------------------------------------------
void ofSoundPlayer::play(){
}

// ----------------------------------------------------------------------------
void ofSoundPlayer::stop(){
}
