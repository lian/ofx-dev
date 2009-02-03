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


#pragma once


#include "ofMain.h"
#include "FluidSolver.h"

class FluidTexture : public FluidSolver, public ofTexture {
	GLint			renderWidth, renderHeight;	// target width and height to render to
	unsigned char 	*pixels;		// pixels array to be drawn
	int				byteCount;		// number of byes in the pixel array (size * 3)
	
public:
	~FluidTexture();
	
	void init(int w, int h, int NX, int NY, float dt, float visc, float fadeSpeed);
	void update();
	void draw();
	void reset();
};
