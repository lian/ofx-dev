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



#include "MSAShape3D.h"


MSAShape3D::MSAShape3D() {
	reservedSize = DEFAULT_RESERVE_AMOUNT;
	reset();
}

void MSAShape3D::reserve(int reservedSize) {
	this->reservedSize = reservedSize;
	
	vertexArray.reserve(reservedSize * 3);
	normalArray.reserve(reservedSize * 3);
	colorArray.reserve(reservedSize * 4);
	texCoordArray.reserve(reservedSize * 2);
}

void MSAShape3D::reset() {
	colorChanged		= false;
	normalChanged		= false;
	texCoordChanged		= false;
	doingShape			= false;
	numVertices			= 0;
	
	vertexArray.clear();
	normalArray.clear();
	colorArray.clear();
	texCoordArray.clear();
	
	reserve(reservedSize);
}


void MSAShape3D::glBegin(GLenum drawMode) {
	this->drawMode = drawMode;
	reset();
	doingShape			= true;	
}



void MSAShape3D::glEnd() {
	if(colorChanged) {
		glEnableClientState(GL_COLOR_ARRAY);	
		glColorPointer(4, GL_FLOAT, 0, &colorArray[0]);
	}
	else glDisableClientState(GL_COLOR_ARRAY);
	
	if(normalChanged) {
		glEnableClientState(GL_NORMAL_ARRAY);	
		glNormalPointer(GL_FLOAT, 0, &normalArray[0]);
	}
	else glDisableClientState(GL_NORMAL_ARRAY);	
	
	if(texCoordChanged) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoordArray[0]);
	}
	else glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray[0]);
	
	glDrawArrays(drawMode, 0, numVertices);
}


void MSAShape3D::draw() {
	glEnd();
}



void MSAShape3D::glVertex(float x, float y, float z) {
	vertexArray.push_back(x);
	vertexArray.push_back(y);
	vertexArray.push_back(z);
	
	normalArray.push_back(curNormal[0]);
	normalArray.push_back(curNormal[1]);
	normalArray.push_back(curNormal[2]);
	
	colorArray.push_back(curColor[0]);
	colorArray.push_back(curColor[1]);
	colorArray.push_back(curColor[2]);
	colorArray.push_back(curColor[3]);
	
	texCoordArray.push_back(curTexCoord[0]);
	texCoordArray.push_back(curTexCoord[1]);
	
	numVertices++;
}

void MSAShape3D::glVertex3v(float *v) {
	glVertex(v[0], v[1], v[2]);
}

void MSAShape3D::glVertex2v(float *v) {
	glVertex(v[0], v[1]);
}


void MSAShape3D::glNormal(float x, float y, float z) {
	glNormal3f(x, y, z);
	normalChanged = true;
	curNormal[0] = x;
	curNormal[1] = y;
	curNormal[2] = z;
}

void MSAShape3D::glNormal3v(float *v) {
	glNormal(v[0], v[1], v[2]);
}




void MSAShape3D::glColor(float r, float g, float b, float a){
	glColor4f(r, g, b, a);
	colorChanged = true;
	curColor[0] = r;
	curColor[1] = g;
	curColor[2] = b;
	curColor[3] = a;
}


void MSAShape3D::glColor(int hexColor){
	float r = ((hexColor >> 16) & 0xff) * 1.0f/255;
	float g = ((hexColor >> 8) & 0xff)  * 1.0f/255;
	float b = ((hexColor >> 0) & 0xff)  * 1.0f/255;
	glColor(r, g, b);
}

void MSAShape3D::glColor3v(float *v) {
	glColor(v[0], v[1], v[2]);
}

void MSAShape3D::glColor4v(float *v) {
	glColor(v[0], v[1], v[2], v[3]);
}



void MSAShape3D::glTexCoord(float u, float v) {
	curTexCoord[0] = u;
	curTexCoord[1] = v;
	texCoordChanged = true;
}

void MSAShape3D::glTexCoord2v(float *v) {
	glTexCoord(v[0], v[1]);
}


void MSAShape3D::glRect(float x1, float y1, float x2, float y2) {
	glBegin(GL_TRIANGLE_STRIP);
	glVertex(x1, y1);
	glVertex(x2, y1);
	glVertex(x1, y2);
	glVertex(x2, y2);
	glEnd();
}
