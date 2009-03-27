/*
 *  ofFBOTexture.cpp
 *  openFrameworks
 *
 *  Created by Zach Gage on 3/28/08.
 *  Copyright 2008 STFJ.NET. All rights reserved.
 *
 */

#include "ofFBOTexture.h"

void ofFBOTexture::allocate(int w, int h, bool autoC)
{
    texData.width = w;
    texData.height = h;

	//-------------ofTexture-------------
	// 	can pass in anything (320x240) (10x5)
	// 	here we make it power of 2 for opengl (512x256), (16x8)

    if (GLEE_ARB_texture_rectangle){
        texData.tex_w = w;
        texData.tex_h = h;
        texData.textureTarget = GL_TEXTURE_RECTANGLE_ARB;   // zach  -- added to get texture target right
    } else {
        texData.tex_w = ofNextPow2(w);
        texData.tex_h = ofNextPow2(h);
    }

	if (GLEE_ARB_texture_rectangle){
		texData.tex_t = w;
		texData.tex_u = h;
	} else {
		texData.tex_t = 1.0f;
		texData.tex_u = 1.0f;
	}

	// attempt to free the previous bound texture, if we can:
	clean();

	texData.width = w;
	texData.height = h;
	texData.bFlipTexture = true;

	//--FBOTexture-------------------
	autoClear = autoC;
	// Setup our FBO
	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

	// Create the render buffer for depth
	glGenRenderbuffersEXT(1, &depthBuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, texData.tex_w, texData.tex_h);

	// Now setup a texture to render to
	glGenTextures(1, (GLuint *)texData.textureName);   // could be more then one, but for now, just one

	glEnable(texData.textureTarget);

	glBindTexture(texData.textureTarget, (GLuint)texData.textureName[0]);
		glTexImage2D(texData.textureTarget, 0, GL_RGBA, texData.tex_w, texData.tex_h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, 0);  // init to black...
		glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(texData.textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(texData.textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// attach it to the FBO so we can render to it

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texData.textureTarget, (GLuint)texData.textureName[0], 0);


	// Attach the depth render buffer to the FBO as it's depth attachment
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);


	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		cout<<"glBufferTexture failed to initialize. Perhaps your graphics card doesnt support the framebuffer extension? If you are running osx prior to system 10.5, that could be the cause"<<endl;
		std::exit(1);
	}
	clear();

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now

	glDisable(texData.textureTarget);
}


void ofFBOTexture::setupScreenForMe(){

	int w = texData.width;
	int h = texData.height;

	float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;

	float eyeX 		= (float)w / 2.0;
	float eyeY 		= (float)h / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)w/(float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glScalef(1, -1, 1);           // invert Y axis so increasing Y goes down.
  	glTranslatef(0, -h, 0);       // shift origin up to upper-left corner.

    glViewport(0,0, texData.width, texData.height);

}

void ofFBOTexture::setupScreenForThem(){

    int w, h;

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;

	float eyeX 		= (float)w / 2.0;
	float eyeY 		= (float)h / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)w/(float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glScalef(1, -1, 1);           // invert Y axis so increasing Y goes down.
  	glTranslatef(0, -h, 0);       // shift origin up to upper-left corner.


    glViewport(0,0,w, h);
}

void ofFBOTexture::swapIn()
{

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo); // bind the FBO to the screen so we can draw to it

	if(autoClear)
	{
		clear();
	}

	// Save the view port and set it to the size of the texture
}

void ofFBOTexture::swapOut()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); //unbind the FBO

}

void ofFBOTexture::clean()
{
	// try to free up the texture memory so we don't reallocate
	// http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/deletetextures.html
	if (texData.textureName[0] != 0){
		glDeleteTextures(1, (GLuint *)texData.textureName);
	}
	texData.width = 0;
	texData.height = 0;
	texData.bFlipTexture = false;
}

void ofFBOTexture::clear()
{
	glClearColor(1,1,1,0); //clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
}
