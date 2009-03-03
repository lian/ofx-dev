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


#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "EAGLView.h"


#include "ofMain.h"
#include "iPhoneGlobals.h"


//CLASS IMPLEMENTATIONS:

@implementation EAGLView

@synthesize surfaceSize=_size, framebuffer = _framebuffer, pixelFormat = _format, depthFormat = _depthFormat, context = _context;

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (BOOL) _createSurface
{
	CAEAGLLayer*			eaglLayer = (CAEAGLLayer*)[self layer];
	CGSize					newSize;
	GLuint					oldRenderbuffer;
	GLuint					oldFramebuffer;
	
	if(![EAGLContext setCurrentContext:_context]) {
		return NO;
	}
	
	newSize = [eaglLayer bounds].size;
	newSize.width = roundf(newSize.width);
	newSize.height = roundf(newSize.height);
	
	glGetIntegerv(GL_RENDERBUFFER_BINDING_OES, (GLint *) &oldRenderbuffer);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, (GLint *) &oldFramebuffer);
	
	glGenRenderbuffersOES(1, &_renderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _renderbuffer);
	
	if(![_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(id<EAGLDrawable>)eaglLayer]) {
		glDeleteRenderbuffersOES(1, &_renderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_BINDING_OES, oldRenderbuffer);
		return NO;
	}
	
	glGenFramebuffersOES(1, &_framebuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, _framebuffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, _renderbuffer);
	if (_depthFormat) {
		glGenRenderbuffersOES(1, &_depthBuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, _depthBuffer);
		glRenderbufferStorageOES(GL_RENDERBUFFER_OES, _depthFormat, newSize.width, newSize.height);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, _depthBuffer);
	}
	
	_size = newSize;
	if(!_hasBeenCurrent) {
		glViewport(0, 0, newSize.width, newSize.height);
		glScissor(0, 0, newSize.width, newSize.height);
		_hasBeenCurrent = YES;
	}
	else {
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, oldFramebuffer);
	}
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, oldRenderbuffer);
	
	return YES;
}

- (void) _destroySurface
{
	EAGLContext *oldContext = [EAGLContext currentContext];
	
	if (oldContext != _context)
		[EAGLContext setCurrentContext:_context];
	
	if(_depthFormat) {
		glDeleteRenderbuffersOES(1, &_depthBuffer);
		_depthBuffer = 0;
	}
	
	glDeleteRenderbuffersOES(1, &_renderbuffer);
	_renderbuffer = 0;
	
	glDeleteFramebuffersOES(1, &_framebuffer);
	_framebuffer = 0;
	
	if (oldContext != _context)
		[EAGLContext setCurrentContext:oldContext];
}

- (id) initWithFrame:(CGRect)frame
{
	return [self initWithFrame:frame pixelFormat:GL_RGB565_OES depthFormat:0 preserveBackbuffer:NO];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format 
{
	return [self initWithFrame:frame pixelFormat:format depthFormat:0 preserveBackbuffer:NO];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format depthFormat:(GLuint)depth preserveBackbuffer:(bool)retained
{
	if((self = [super initWithFrame:frame])) {
		CAEAGLLayer*			eaglLayer = (CAEAGLLayer*)[self layer];
		
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		_format = format;
		_depthFormat = depth;
		
		_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		if(_context == nil) {
			[self release];
			return nil;
		}
		
		if(![self _createSurface]) {
			[self release];
			return nil;
		}
		
		self.multipleTouchEnabled = true;
		bzero(activeTouches, sizeof(activeTouches));
	}
	
	return self;
}

- (void) swapBuffers
{
	EAGLContext *oldContext = [EAGLContext currentContext];
	GLuint oldRenderbuffer;
	
	if(oldContext != _context)
		[EAGLContext setCurrentContext:_context];
	
	glGetIntegerv(GL_RENDERBUFFER_BINDING_OES, (GLint *) &oldRenderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _renderbuffer);
	
	if(![_context presentRenderbuffer:GL_RENDERBUFFER_OES])
		NSLog(@"Failed to swap renderbuffer in %s\n", __FUNCTION__);
	
	if(oldContext != _context)
		[EAGLContext setCurrentContext:oldContext];
}

- (void) dealloc
{
	[self _destroySurface];
	
	[_context release];
	_context = nil;
	
	[super dealloc];
}


/******************* TOUCH EVENTS ********************/
//------------------------------------------------------
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	multitouchData.numTouches = [[event touchesForView:self] count];
//	NSLog(@"touchesBegan: %i %i %i", [touches count],  [[event touchesForView:self] count], multitouchData.numTouches);

	for(UITouch *touch in touches) {
		int touchIndex = 0;
		while(touchIndex < OF_MAX_TOUCHES && activeTouches[touchIndex] != 0) touchIndex++;
		if(touchIndex==OF_MAX_TOUCHES) {
			NSLog(@"touchesBegan - weird!");
			touchIndex=0;	
		}
		
		activeTouches[touchIndex] = touch;
		
		CGPoint touchPoint = [touch locationInView:self];
		
		if( touchIndex==0 ){
			iPhoneGlobals.baseApp->mouseX = touchPoint.x;
			iPhoneGlobals.baseApp->mouseY = touchPoint.y;
			iPhoneGlobals.baseApp->mousePressed(touchPoint.x, touchPoint.y, 1);
		}
		
		if([touch tapCount] == 1) ofxMultiTouch.touchDown(touchPoint.x, touchPoint.y, touchIndex, &multitouchData);
		else ofxMultiTouch.touchDoubleTap(touchPoint.x, touchPoint.y, touchIndex, &multitouchData);
	}
}

//------------------------------------------------------
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	multitouchData.numTouches = [[event touchesForView:self] count];
//	NSLog(@"touchesMoved: %i %i %i", [touches count],  [[event touchesForView:self] count], multitouchData.numTouches);

	for(UITouch *touch in touches) {
		int touchIndex = 0;
		while(touchIndex < OF_MAX_TOUCHES && (activeTouches[touchIndex] != touch)) touchIndex++;
		if(touchIndex==OF_MAX_TOUCHES) {
			NSLog(@"touchesMoved - weird!");
			continue;	
		}
		
		CGPoint touchPoint = [touch locationInView:self];
		
		if( touchIndex==0 ){
			iPhoneGlobals.baseApp->mouseX = touchPoint.x;
			iPhoneGlobals.baseApp->mouseY = touchPoint.y;
			iPhoneGlobals.baseApp->mouseDragged(touchPoint.x, touchPoint.y, 1);
		}
		
		ofxMultiTouch.touchMoved(touchPoint.x, touchPoint.y, touchIndex, &multitouchData);
	}
}

//------------------------------------------------------
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	multitouchData.numTouches = [[event touchesForView:self] count] - [touches count];
//	NSLog(@"touchesEnded: %i %i %i", [touches count],  [[event touchesForView:self] count], multitouchData.numTouches);
	
	for(UITouch *touch in touches) {
		int touchIndex = 0;
		while(touchIndex < OF_MAX_TOUCHES && (activeTouches[touchIndex] != touch)) touchIndex++;
		if(touchIndex==OF_MAX_TOUCHES) {
			NSLog(@"touchesEnded - weird!");
			continue;	
		}
		
		activeTouches[touchIndex] = 0;
		
		CGPoint touchPoint = [touch locationInView:self];
		
		if( touchIndex==0 ){
			iPhoneGlobals.baseApp->mouseX = touchPoint.x;
			iPhoneGlobals.baseApp->mouseY = touchPoint.y;
			iPhoneGlobals.baseApp->mouseReleased(touchPoint.x, touchPoint.y, 1);
			iPhoneGlobals.baseApp->mouseReleased();
		}
		
		ofxMultiTouch.touchUp(touchPoint.x, touchPoint.y, touchIndex, &multitouchData);
	}
}

//------------------------------------------------------
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	multitouchData.numTouches = 0;
	
	for(int i=0; i<OF_MAX_TOUCHES; i++){
		if(activeTouches[i]){
	
			CGPoint touchPoint = [activeTouches[i] locationInView:self];
			activeTouches[i] = 0;

			if( i==0 ){
				iPhoneGlobals.baseApp->mouseX = touchPoint.x;
				iPhoneGlobals.baseApp->mouseY = touchPoint.y;
				iPhoneGlobals.baseApp->mouseReleased(touchPoint.x, touchPoint.y, 1);
				iPhoneGlobals.baseApp->mouseReleased();
			}
			ofxMultiTouch.touchUp(touchPoint.x, touchPoint.y, i, &multitouchData);
		}
	}
}

@end