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


#import "ofxAccelerometer.h"

/************ Interface for iPhone Accelerometer Delegate ************/
@interface ofxIPhoneAccelerometerDelegate : NSObject <UIAccelerometerDelegate> {
}

@end

// define instance of delegate 
static ofxIPhoneAccelerometerDelegate* iPhoneAccelerometerDelegate;



/************ Impementation of standard C++ accel interface tailored for iPhone ************/
// call this to setup the accelerometer
void ofxAccelerometerHandler::setup() {
//	printf("ofxAccelerometer::setup()\n");
	[iPhoneAccelerometerDelegate release];		// in case we've already called it for some reason
	iPhoneAccelerometerDelegate = [[ofxIPhoneAccelerometerDelegate alloc] init];
//	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications]; 

//#if TARGET_IPHONE_SIMULATOR
//	update(0, -1, 0);
//#endif
}
	
// call this when accelerometer is no longer needed
void ofxAccelerometerHandler::exit() {
//	printf("ofxAccelerometer::exit()\n");
	[iPhoneAccelerometerDelegate release];
}





/************ Implementation of iPhone Accelerometer Delegate ************/
@implementation ofxIPhoneAccelerometerDelegate

-(ofxIPhoneAccelerometerDelegate*) init {
	if(self = 	[super init]) {
		UIAccelerometer *accelerometer = [UIAccelerometer sharedAccelerometer];
		accelerometer.delegate = self;
		accelerometer.updateInterval = 1.0f/30.0f;
	}
	return self;
}


-(void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration*)accel {
	ofxAccelerometer.update(accel.x, accel.y, accel.z);
}

@end
