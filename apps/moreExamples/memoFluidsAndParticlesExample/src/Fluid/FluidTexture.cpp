/***********************************************************************
 
 This class is for drawing a fluidsolver using the OpenFrameworks texture
 
 -----------------------------------
 
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


#include "FluidTexture.h"
#include "ImageFilters.h"

void FluidTexture::init(int w, int h, int NX, int NY, float dt, float visc, float fadeSpeed) {
	FluidSolver::init(NX, NY, dt, visc, fadeSpeed);
	renderWidth = w;
	renderHeight = h;
	
	allocate(_NX+2, _NY+2, GL_RGB);
	
	byteCount = _size * 3;
	pixels = new unsigned char [byteCount];
}

FluidTexture::~FluidTexture() {
	if(pixels) delete pixels;
}

void FluidTexture::reset() {
	_reset();
}

void FluidTexture::update() {
	solve();
	
	int index;
	for(int i=0, index=0; i<_size; i++, index += 3) {
		pixels[index]	= MIN(_r[i] * 255, 255);
		pixels[index+1]	= MIN(_g[i] * 255, 255);		
		pixels[index+2]	= MIN(_b[i] * 255, 255);		
	}  
	boxBlur(pixels, _NX+2, _NY+2, 2);
}


void FluidTexture::draw() {
	loadData(pixels, _NX+2, _NY+2, GL_RGB);

	glEnable( getTextureData().textureTarget);
	glBindTexture( getTextureData().textureTarget, (GLuint)getTextureData().textureID );
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin( GL_QUADS );
	glTexCoord2f(0, 0);				glVertex3i(-1, -1, 0);
	glTexCoord2f(getTextureData().tex_t, 0);			glVertex3i(renderWidth+1, 0, 0);
	glTexCoord2f(getTextureData().tex_t, getTextureData().tex_u);		glVertex3i(renderWidth+1, renderHeight+1, 0);
	glTexCoord2f(0, getTextureData().tex_u);			glVertex3i(0, renderHeight+1, 0);
	glEnd();
	glPopMatrix();
	
	glDisable( getTextureData().textureTarget );
}

