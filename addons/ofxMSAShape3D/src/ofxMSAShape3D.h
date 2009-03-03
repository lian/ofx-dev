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

#include "ofMain.h"

#define DEFAULT_RESERVE_AMOUNT		5000

#define SIZEOF_FLOAT		4

//#define USE_IMMEDIATE_MODE

class ofxMSAShape3D {
public:
	ofxMSAShape3D() {
		vertexArray = normalArray = colorArray = texCoordArray = 0;
		colorEnabled = normalEnabled = texCoordEnabled = false;
		setSafeMode(true);
		reserve(DEFAULT_RESERVE_AMOUNT);
	}
	
	~ofxMSAShape3D() {
		if(vertexArray) free(vertexArray);
		if(normalArray) free(normalArray);
		if(colorArray) free(colorArray);
		if(texCoordArray) free(texCoordArray);	
	}
	
	// reserve space for this many vertices
	// Not actually nessecary, arrays are resized automatically...
	// ... but reserving the size upfront improves performance
	inline void reserve(int reservedSize) {
		printf("ofxMSAShape3D::reserve( %i )\n", reservedSize);
		
		this->reservedSize = reservedSize;
		
		vertexArray		= (float*)realloc(vertexArray, 3 * reservedSize * SIZEOF_FLOAT);
		normalArray		= (float*)realloc(normalArray, 3 * reservedSize * SIZEOF_FLOAT);
		colorArray		= (float*)realloc(colorArray, 4 * reservedSize * SIZEOF_FLOAT);
		texCoordArray	= (float*)realloc(texCoordArray, 2 * reservedSize * SIZEOF_FLOAT);
		
		if(safeMode == false) setClientStates();
		
		reset();
	}
	
	// similar to OpenGL glBegin
	// starts primitive draw mode
	inline void begin(GLenum drawMode) {
#ifndef USE_IMMEDIATE_MODE
		this->drawMode = drawMode;
		reset();
#else	
		glBegin(drawMode);
#endif	
	}
	
	// similar to OpenGL glEnd()
	// sends all data to server to be drawn
	inline void end() {
#ifndef USE_IMMEDIATE_MODE
		if(safeMode) setClientStates();
		glDrawArrays(drawMode, 0, numVertices);
#else
		glEnd();
#endif	
	}
	
	// redraws currently cached shape
	inline void draw() {
		this->end();
	}
	
	
	// vertex position methods
	// x,y,z coordinates (if z is omitted, assumed 0)	
	inline void addVertex(float x, float y, float z = 0) {
#ifndef USE_IMMEDIATE_MODE
		if(safeMode) {
			if(numVertices >= reservedSize) reserve(reservedSize * 1.1);		// if we hit limit, increase reserve by 10%
			memcpy(colorArray + numVertices*3, curColor, 3*SIZEOF_FLOAT);
			memcpy(colorArray + numVertices*4, curColor, 4*SIZEOF_FLOAT);
			memcpy(colorArray + numVertices*2, curColor, 2*SIZEOF_FLOAT);
		} else {
			if(normalEnabled) memcpy(colorArray + numVertices*3, curColor, 3*SIZEOF_FLOAT);
			if(colorEnabled) memcpy(colorArray + numVertices*4, curColor, 4*SIZEOF_FLOAT);
			if(texCoordEnabled) memcpy(colorArray + numVertices*2, curColor, 2*SIZEOF_FLOAT);
		}
		
		vertexArray[vertexIndex++]		= x;
		vertexArray[vertexIndex++]		= y;
		vertexArray[vertexIndex++]		= z;
		
		numVertices++;
#else
		glVertex3f(x, y, z);
#endif	
	}

	// pointer to x,y,z coordinates
	inline void addVertex3v(float *v) {
			this->addVertex(v[0], v[1], v[2]);
	}					
	
	// pointer to x,y coordinates. z is assumed 0
	inline void addVertex2v(float *v) {
			this->addVertex(v[0], v[1]);
	}						
	
	
	
	// normal methods
	// x,y,z components of normal
	inline void setNormal(float x, float y, float z) {
#ifndef USE_IMMEDIATE_MODE
		if(safeMode) normalEnabled = true;
		curNormal[0] = x;
		curNormal[1] = y;
		curNormal[2] = z;
#endif
		glNormal3f(x, y, z);
	}
	
	
	inline void setNormal3v(float *v) {
		this->setNormal(v[0], v[1], v[2]);
	}						// pointer to x,y,z components of normal
	
	// color methods
	// r,g,b,a color components (if a is omitted, assumed 0)	
	inline void setColor(float r, float g, float b, float a = 1) {
#ifndef USE_IMMEDIATE_MODE
		if(safeMode) colorEnabled = true;
		curColor[0] = r;
		curColor[1] = g;
		curColor[2] = b;
		curColor[3] = a;
#endif	
		glColor4f(r, g, b, a);
	}
	
	// 0xFFFFFF hex color, alpha is assumed 1	
	inline void setColor(int hexColor) {
		float r = ((hexColor >> 16) & 0xff) * 1.0f/255;
		float g = ((hexColor >> 8) & 0xff)  * 1.0f/255;
		float b = ((hexColor >> 0) & 0xff)  * 1.0f/255;
		this->setColor(r, g, b);
	}		
	
	// pointer to r,g,b components. alpha is assumed 1
	inline void setColor3v(float *v) {
		this->setColor(v[0], v[1], v[2]);
	}						
	
	// pointer to r,g,b,a components
	inline void setColor4v(float *v) {
		this->setColor(v[0], v[1], v[2], v[3]);		
	}						
	
	
	// texture coordinate methods
	// u,v texture coordinates
	inline void setTexCoord(float u, float v) {
#ifndef USE_IMMEDIATE_MODE
		if(safeMode) texCoordEnabled = true;
		curTexCoord[0] = u;
		curTexCoord[1] = v;
#else		
		glTexCoord2f(u, v);
#endif	
	}				
	
	// pointer to u,v texture coordinates
	inline void setTexCoord2v(float *v) {
		this->setTexCoord(v[0], v[1]);
	}					
	
	
	// rectangle from (x1, y1) to (x2, y2)
	inline void drawRect(float x1, float y1, float x2, float y2) {
		this->begin(GL_TRIANGLE_STRIP);
		this->addVertex(x1, y1);
		this->addVertex(x2, y1);
		this->addVertex(x1, y2);
		this->addVertex(x2, y2);
		this->end();
	}
	

	
	/********* Advanced use ***********/
	
	// safe mode is TRUE by default
	// if safe mode is on, all clientstates are set as needed in end()
	// this may not be efficient if lots of shapes are drawn
	// by disabling safe mode, you can manually set the clientstates (using the below methods)
	// and avoid this overhead
	// if you don't know what this means, don't touch it
	inline void setSafeMode(bool b) {
		safeMode = b;
	}
	
	// set whether the shape will be using any of the below
	inline void enableNormal(bool b) {
		normalEnabled = b;
		if(normalEnabled) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, &normalArray[0]);
		}
		else glDisableClientState(GL_NORMAL_ARRAY);
	}
	
	inline void enableColor(bool b) {
		colorEnabled = b;
		if(colorEnabled) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, 0, &colorArray[0]);
		}
		else glDisableClientState(GL_COLOR_ARRAY);	
	}
	
	inline void enableTexCoord(bool b) {
		texCoordEnabled = b;
		if(texCoordEnabled) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, &texCoordArray[0]);
		}
		else glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	// enables or disables all client states based on information provided in above methods
	inline void setClientStates() {
		enableColor(colorEnabled);
		enableNormal(normalEnabled);
		enableTexCoord(texCoordEnabled);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &vertexArray[0]);
	}
	
	
protected:
	inline void reset() {
		if(safeMode) {
			colorEnabled		= false;
			normalEnabled		= false;
			texCoordEnabled		= false;
		}
		numVertices			= 0;
		
		vertexIndex = 0;
//		normalIndex = colorIndex = texCoordIndex = 0;
	}

	float	*vertexArray;	// 3
	float	*normalArray;	// 3
	float	*colorArray;	// 4
	float	*texCoordArray;	// 2
	int		sizeOfFloat;

	
	float	curNormal[3];
	float	curColor[4];
	float	curTexCoord[2];
	
	bool	normalEnabled;
	bool	colorEnabled;
	bool	texCoordEnabled;
	
	bool	safeMode;
	
	int		numVertices;
	int		vertexIndex;
//	int		normalIndex;
//	int		colorIndex;
//	int		texCoordIndex;	

	int		reservedSize;
	GLenum	drawMode;
};
