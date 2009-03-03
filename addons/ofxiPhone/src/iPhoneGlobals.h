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

#include "ofAppRunner.h"
#include "ofAppiPhoneWindow.h"
#include "iPhoneAppDelegate.h"
#include "EAGLView.h"



class iPhoneGlobalsStruct {
public:
	
	ofBaseApp				*baseApp;
	UIWindow				*window;
	ofAppiPhoneWindow		*iPhoneOFWindow;
	EAGLView				*glView;
	int						deviceType;
	id						appDelegate;
	
	iPhoneGlobalsStruct() {
		window = 0;
		baseApp = 0;
		iPhoneOFWindow = 0;
		glView = 0;
		appDelegate = 0;
	}
};


extern iPhoneGlobalsStruct iPhoneGlobals;