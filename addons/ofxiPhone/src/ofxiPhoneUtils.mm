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


#include "ofxiPhone.h"


int iPhoneGetDeviceType() {
	return iPhoneGlobals.deviceType;
}


void iPhoneEnableIdleTimer() {
	[UIApplication sharedApplication].idleTimerDisabled = true;
}

void iPhoneDisableIdleTimer() {
	[UIApplication sharedApplication].idleTimerDisabled = false;
}



void iPhoneLoadImageFromBundle(NSString *filename, GLuint *spriteTexture) {
	iPhoneLoadImageFromUIImage([UIImage imageNamed:filename], spriteTexture);
}


void iPhoneLoadImageFromUIImage(UIImage *uiImage, GLuint *spriteTexture) {
	if(!uiImage) return;
	
	CGImageRef cgImage;
	CGContextRef spriteContext;
	GLubyte *spriteData;
	size_t	width, height;
	
	// Creates a Core Graphics image from an image file
	cgImage = uiImage.CGImage;
	
	// Get the width and height of the image
	width = CGImageGetWidth(cgImage);
	height = CGImageGetHeight(cgImage);
	
	// Allocated memory needed for the bitmap context
	spriteData = (GLubyte *) malloc(width * height * 4);
	// Uses the bitmatp creation function provided by the Core Graphics framework. 
	spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width * 4, CGImageGetColorSpace(cgImage), kCGImageAlphaPremultipliedLast);
	// After you create the context, you can draw the sprite image to the context.
	CGContextDrawImage(spriteContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), cgImage);
	// You don't need the context at this point, so you need to release it to avoid memory leaks.
	CGContextRelease(spriteContext);
	
	// Use OpenGL ES to generate a name for the texture.
	glGenTextures(1, spriteTexture);
	// Bind the texture name. 
	glBindTexture(GL_TEXTURE_2D, *spriteTexture);
	// Speidfy a 2D texture image, provideing the a pointer to the image data in memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
	// Release the image data
	free(spriteData);
	
	// Set the texture parameters to use a minifying filter and a linear filer (weighted average)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}




/******************** ofxiPhoneScreenGrab *********************/

@interface SaveDelegate : NSObject {
	id delegate;
}
@property (retain, nonatomic) id delegate;
@end


@implementation SaveDelegate
@synthesize delegate;

// callback for UIImageWriteToSavedPhotosAlbum
- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo {
//	NSLog(@"Save finished\n");
	[image release];		// release image
	[delegate saveComplete];
	
	[self release];
}

-(void)dealloc {
	[delegate release];
	[super dealloc];
}

@end



// callback for CGDataProviderCreateWithData
void releaseData(void *info, const void *data, size_t dataSize) {
//	NSLog(@"releaseData\n");
	free((void*)data);		// free the 
}


void iPhoneScreenGrab(id delegate) {
	CGRect rect = [[UIScreen mainScreen] bounds];
	int width = rect.size.width;
	int height =  rect.size.height;
	
	NSInteger myDataLength = width * height * 4;
	GLubyte *buffer = (GLubyte *) malloc(myDataLength);
	GLubyte *bufferFlipped = (GLubyte *) malloc(myDataLength);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	for(int y = 0; y <height; y++) {
		for(int x = 0; x <width * 4; x++) {
			bufferFlipped[int((height - 1 - y) * width * 4 + x)] = buffer[int(y * 4 * width + x)];
		}
	}
	free(buffer);	// free original buffer
	
	CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, bufferFlipped, myDataLength, releaseData);
	CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
	CGImageRef imageRef = CGImageCreate(width, height, 8, 32, 4 * width, colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);		
	
	CGColorSpaceRelease(colorSpaceRef);
	CGDataProviderRelease(provider);
	
	UIImage *image = [[UIImage alloc] initWithCGImage:imageRef];
	CGImageRelease(imageRef);
	
	SaveDelegate *saveDelegate = [SaveDelegate new];
	saveDelegate.delegate = delegate;
	UIImageWriteToSavedPhotosAlbum(image, saveDelegate, @selector(image:didFinishSavingWithError:contextInfo:), nil);
}



