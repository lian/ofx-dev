/***********************************************************************
 
 Copyright (c) 2008, Memo Akten, www.memo.tv
 
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

#include "ofMain.h"

class MSATexture : public ofTexture {
public:
	MSATexture() {
		printf("MSATexture::MSATexture()");
	}
	
	void bind() {
		glEnable(texData.textureTarget);
		glBindTexture( texData.textureTarget, (GLuint)texData.textureName[0] );
	}
	
	
	void unbind() {
		glDisable(texData.textureTarget);
		glDisable(texData.textureTarget);
	}
	
	void getTextureCoords(float &tt, float &tu) {
		tt = texData.tex_t;
		tu = texData.tex_u;
	}
	
	int getTextureName() {
		return texData.textureName[0];
	}
	
	void quickDraw(float x, float y, float w, float h){
		GLint px0 = 0;		// up to you to get the aspect ratio right
		GLint py0 = 0;
		GLint px1 = (GLint)w;
		GLint py1 = (GLint)h;
		
		if (texData.bFlipTexture == true){
			GLint temp = py0;
			py0 = py1;
			py1 = temp;
		}
		
		// for rect mode center, let's do this:
		if (ofGetRectMode() == OF_RECTMODE_CENTER){
			px0 = (GLint)-w/2;
			py0 = (GLint)-h/2;
			px1 = (GLint)+w/2;
			py1 = (GLint)+h/2;
		}
		
		GLfloat offsetw = 0;
		GLfloat offseth = 0;
		
		if (texData.textureTarget == GL_TEXTURE_2D){
			offsetw = 1.0f/(texData.tex_w);
			offseth = 1.0f/(texData.tex_h);
		}
		// -------------------------------------------------
		
		GLfloat tx0 = 0+offsetw;
		GLfloat ty0 = 0+offseth;
		GLfloat tx1 = texData.tex_t - offsetw;
		GLfloat ty1 = texData.tex_u - offseth;
		
		glPushMatrix();
		glTranslated(x, y, 0);
		glBegin( GL_QUADS );
		glTexCoord2f(tx0,ty0);			glVertex3i(px0, py0,0);
		glTexCoord2f(tx1,ty0);			glVertex3i(px1, py0,0);
		glTexCoord2f(tx1,ty1);			glVertex3i(px1, py1,0);
		glTexCoord2f(tx0,ty1);			glVertex3i(px0, py1,0);
		glEnd();
		glPopMatrix();
	}
};