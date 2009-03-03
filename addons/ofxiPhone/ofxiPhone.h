/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 
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

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import "iPhoneGlobals.h"

#define		OF_DEVICE_IPHONE				0
#define		OF_DEVICE_IPODTOUCH				1



// return device type
int iPhoneGetDeviceType();

// whether device has audio in
bool iPhoneHasAudioIn();

// enable or disable the iPhone idle timer
// (screen dims and goes off after x amount of inactivity)
void iPhoneDisableIdleTimer();
void iPhoneEnableIdleTimer();


// returns normalized (0...1) Average and Peak audio levels on mic
float iPhoneGetMicAverageLevel();
float iPhoneGetMicPeakLevel();

void iPhoneEnableMultitouch();


// load an image from the app bundle into a texture
void iPhoneLoadImageFromBundle(NSString *filename, GLuint *spriteTexture);

// load an image from UIImage into a texture
void iPhoneLoadImageFromUIImage(UIImage *image, GLuint *spriteTexture);



// save current opengl screen to photos app
// based on code from http://www.bit-101.com/blog/?p=1861
void iPhoneScreenGrab(id delegate);

