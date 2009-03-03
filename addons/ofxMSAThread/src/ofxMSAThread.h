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

#pragma once

#define OF_ADDON_USING_OFXTHREAD
#include "ofMain.h"
#include "ofAddons.h"


class ofxMSAThread : public ofxThread {
public:	
	void start(bool _blocking = false, bool _verbose = false){
		startThread(_blocking, _verbose);  
	}
	
	void stop(){
		stopThread(); 
	}
	
	bool safeToRun() {
		if(!threadRunning) return true;
		return lock();
	}
	
	void threadedFunction(){
		while(isThreadRunning() != 0){
			if(lock()){
				update();
				unlock();
				ofSleepMillis(1000/60);		// try to run at 60fps
			}
		}
	}
	
	virtual void update() = 0;
};