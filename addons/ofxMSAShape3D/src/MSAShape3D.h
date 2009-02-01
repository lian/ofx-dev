/***********************************************************************
 
 MSAShape3D v0.2
 
 ----------------------------------------------------------------------

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

#include "ofMain.h"

#include <vector>

#define DEFAULT_RESERVE_AMOUNT		1000

class MSAShape3D {
public:
	MSAShape3D();	
	
	// reserve space for this many vertices
	// Not actually nessecary, arrays are resized automatically...
	// ... but reserving the size upfront improves performance
	void reserve(int reservedSize);

	// similar to OpenGL glBegin
	// starts primitive draw mode
	void glBegin(GLenum drawMode);	
	
	// similar to OpenGL glEnd()
	// sends all data to server to be drawn
	void glEnd();	
	
	// redraws currently cached shape
	void draw();
	
	
	// vertex position methods
	void glVertex(float x, float y, float z = 0);	// x,y,z coordinates (if z is omitted, assumed 0)
	void glVertex3v(float *v);						// pointer to x,y,z coordinates
	void glVertex2v(float *v);						// pointer to x,y coordinates. z is assumed 0
	
	// normal methods
	void glNormal(float x, float y, float z);		// x,y,z components of normal
	void glNormal3v(float *v);						// pointer to x,y,z components of normal

	// color methods
	void glColor(float r, float g, float b, float a = 1);	// r,g,b,a color components (if a is omitted, assumed 0)
	void glColor(int hexColor);						// 0xFFFFFF hex color, alpha is assumed 1
	void glColor3v(float *v);						// pointer to r,g,b components. alpha is assumed 1
	void glColor4v(float *v);						// pointer to r,g,b,a components
	
	// texture coordinate methods
	void glTexCoord(float u, float v);				// u,v texture coordinates
	void glTexCoord2v(float *v);					// pointer to u,v texture coordinates
	
	
	// rectangle from (x1, y1) to (x2, y2)
	void glRect(float x1, float y1, float x2, float y2);
	
	
protected:	
	void reset();	
	
	vector<float>	vertexArray;	// 3
	vector<float>	normalArray;	// 3
	vector<float>	colorArray;		// 4
	vector<float>	texCoordArray;	// 2
	
	float			curNormal[3];
	float			curColor[4];
	float			curTexCoord[2];
	
	bool			normalChanged;
	bool			colorChanged;
	bool			texCoordChanged;
	
	bool			doingShape;
	int				numVertices;
	int				reservedSize;
	GLenum			drawMode;
	
};