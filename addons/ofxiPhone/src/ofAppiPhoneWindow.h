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

#include "ofAppBaseWindow.h"


class ofAppiPhoneWindow : public ofAppBaseWindow{
public:
	
	ofAppiPhoneWindow();
	virtual ~ofAppiPhoneWindow(){};
	
	virtual void		setupOpenGL(int w, int h, int screenMode);
	virtual void		initializeWindow();
	virtual void		runAppViaInfiniteLoop(ofBaseApp * appPtr);
	
	virtual void		hideCursor() {};
	virtual void		showCursor() {};
	
	virtual void		setWindowPosition(int x, int y) {};
	virtual void		setWindowShape(int w, int h) {};
	
	virtual int			getFrameNum();
	virtual float		getFrameRate();
	
	virtual ofPoint		getWindowPosition();
	virtual ofPoint		getWindowSize();
	virtual ofPoint		getScreenSize();
	
	virtual void		setFrameRate(float targetRate);
	virtual void		setWindowTitle(string title);
	
	virtual int			getWindowMode();
	
	virtual void		setFullscreen(bool fullscreen);
	virtual void		toggleFullscreen();
	
	virtual void		enableSetupScreen();
	virtual void		disableSetupScreen();
	
	void timerLoop();

	int					windowMode;
	
	// cache these, they're not gonne change during duration of app
	ofPoint				screenSize;
	ofPoint				windowSize;
	ofPoint				windowPos;
	
	float				timeNow, timeThen, fps;
	int					nFramesForFPS;
	int					nFrameCount;
	bool				bEnableSetupScreen;
	float				ofFrameRate;
};



