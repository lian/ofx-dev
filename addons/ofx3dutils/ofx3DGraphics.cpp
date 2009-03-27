

#include "ofx3DGraphics.h"

GLuint sphereList = 0;
GLuint boxList = 0;
GLuint capsuleList = 0;
GLuint coneList = 0;
int sphereResolution = 30;
int capsuleResolution = 30;
int coneResolution = 30;


//////////////
//sphere
void ofxCreateSphereList(){
	if(!(bool)glIsEnabled(GL_NORMALIZE)) glEnable(GL_NORMALIZE);
	sphereList = glGenLists(1);
	glNewList(sphereList, GL_COMPILE);
	float theta,nextTheta, phi, x, y, z;
	for(int i=0; i<sphereResolution; i++){
		theta = (float)i/(sphereResolution-1) * TWO_PI;
		nextTheta = (float)((i+1)%sphereResolution)/(sphereResolution-1) * TWO_PI;
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<sphereResolution; j++){
			phi = (float)j/(sphereResolution-1) * PI;
			x = cos(theta) * sin(phi);
			y = sin(theta) * sin(phi);
			z = cos(phi);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
			x = cos(nextTheta) * sin(phi);
			y = sin(nextTheta) * sin(phi);
			z = cos(phi);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	glEndList();
}
void ofxSphere(float x, float y, float z, float size){
	if(sphereList == 0) ofxCreateSphereList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glCallList(sphereList);
	glPopMatrix();
}
void ofxSphere(float x, float y, float z, float width, float height, float depth){
	if(sphereList == 0) ofxCreateSphereList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(width, height, depth);
	glCallList(sphereList);
	glPopMatrix();
}

void ofxSphere(float x, float y, float z, float width, float height, float depth, float rotX, float rotY, float rotZ){
	if(sphereList == 0) ofxCreateSphereList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
	glScalef(width, height, depth);
	glCallList(sphereList);
	glPopMatrix();
	
}
//overloaded for ofxVec
void ofxSphere(ofxVec3f position, float size){
	if(sphereList == 0) ofxCreateSphereList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size, size, size);
	glCallList(sphereList);
	glPopMatrix();
}
void ofxSphere(ofxVec3f position, ofxVec3f size){
	if(sphereList == 0) ofxCreateSphereList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size.x, size.y, size.z);
	glCallList(sphereList);
	glPopMatrix();
	
}
void ofxSphere(ofxVec3f position, ofxVec3f size, ofxVec3f rotation){
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);
	glCallList(sphereList);
	glPopMatrix();
	
}

void ofxSetSphereResolution(int _resolution){
	sphereResolution = _resolution;
	if(sphereList == 0){
		ofxCreateSphereList();
	} else {
		glDeleteLists(sphereList, 1);
		ofxCreateSphereList();
	}
}

///////////
//box

void ofxCreateBoxList(){
	if(!(bool)glIsEnabled(GL_NORMALIZE)) glEnable(GL_NORMALIZE);
	boxList = glGenLists(1);
	glNewList(boxList, GL_COMPILE);
	glBegin(GL_QUADS);
	
	//top side
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	
	//bottom side
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	
	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	
	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	
	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	
	//back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	
	glEnd();
	glEndList();
	
}
void ofxBox(float x, float y, float z, float size){
	if(boxList == 0) ofxCreateBoxList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glCallList(boxList);
	glPopMatrix();
}
void ofxBox(float x, float y, float z, float width, float height, float depth){
	if(boxList == 0) ofxCreateBoxList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(width, height, depth);
	glCallList(boxList);
	glPopMatrix();
}
void ofxBox(float x, float y, float z, float width, float height, float depth, float rotX, float rotY, float rotZ){
	if(boxList == 0) ofxCreateBoxList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
	glScalef(width, height, depth);
	glCallList(boxList);
	glPopMatrix();
}
//ofxVec3f:
void ofxBox(ofxVec3f position, float size){
	if(boxList == 0) ofxCreateBoxList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size, size, size);
	glCallList(boxList);
	glPopMatrix();
}
void ofxBox(ofxVec3f position, ofxVec3f size){
	if(boxList == 0) ofxCreateBoxList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size.x, size.y, size.z);
	glCallList(boxList);
	glPopMatrix();
}
void ofxBox(ofxVec3f position, ofxVec3f size, ofxVec3f rotation){
	if(boxList == 0) ofxCreateBoxList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);
	glCallList(boxList);
	glPopMatrix();
}


//////////////
//cone
void ofxCreateConeList(){
	if(!(bool)glIsEnabled(GL_NORMALIZE)) glEnable(GL_NORMALIZE);
	coneList = glGenLists(1);
	glNewList(coneList, GL_COMPILE);
	float angle, x, y, z;
	
	ofxVec3f vecA, vecB, normalVec;
	//the cone
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, -0.5f, 0.0f);
	for(int i=0; i<coneResolution; i++){
		angle = (float)i / (coneResolution-1) * TWO_PI;
		x = sin(angle);
		y = 0.5f;
		z = cos(angle);
		glNormal3f(x/2, 0.0f, z/2);
		glVertex3f(x, y, z);
	}
	glEnd();
	
	//the bottom cap
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	for(int i=0; i<coneResolution; i++){
		angle = (float)i /( coneResolution-1) * TWO_PI;
		x = sin(angle);
		y = 0.5f;
		z = cos(angle);
		glVertex3f(x, y, z);
	}
	glEnd();
	
	glEndList();
	
}

void ofxCone( float x, float y, float z, float size){
	if(coneList == 0) ofxCreateConeList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glCallList(coneList);
	glPopMatrix();
}
void ofxCone(float x, float y, float z, float width, float height, float depth){
	if(coneList == 0) ofxCreateConeList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(width, height, depth);
	glCallList(coneList);
	glPopMatrix();
}

void ofxCone(float x, float y, float z, float width, float height, float depth, float rotX, float rotY, float rotZ){
	if(coneList == 0) ofxCreateConeList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
	glScalef(width, height, depth);
	glCallList(coneList);
	glPopMatrix();
}
//ofxVec3f
void ofxCone(ofxVec3f position, float size){
	if(coneList == 0) ofxCreateConeList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size, size, size);
	glCallList(coneList);
	glPopMatrix();
}
void ofxCone(ofxVec3f position, ofxVec3f size){
	if(coneList == 0) ofxCreateConeList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size.x, size.y, size.z);
	glCallList(coneList);
	glPopMatrix();
}
void ofxCone(ofxVec3f position, ofxVec3f size, ofxVec3f rotation){
	if(coneList == 0) ofxCreateConeList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);
	glCallList(coneList);
	glPopMatrix();
}

void ofxSetConeResolution(int _resolution){
	coneResolution = _resolution;
	if(coneList == 0){
		ofxCreateConeList();
	} else {
		glDeleteLists(coneList, 1);
		ofxCreateConeList();
	}
}
//////////////////
//capsule:
void ofxCreateCapsuleList(){
	if(!(bool)glIsEnabled(GL_NORMALIZE)) glEnable(GL_NORMALIZE);
	capsuleList = glGenLists(1);
	glNewList(capsuleList, GL_COMPILE);
	
	float theta,nextTheta, phi, x, y, z;
	int halfResolution = capsuleResolution/2;
	
	//the capsule
	for(int i=0; i<halfResolution; i++){
		theta = (float)i / (halfResolution-1) * PI;
		nextTheta = (float)((i+1)%halfResolution) / (halfResolution-1) * PI;
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<capsuleResolution; j++){
			phi = (float)j / (capsuleResolution-1) * PI;
			x = cos(theta) * sin(phi);
			y = sin(theta) * sin(phi);
			z = cos(phi);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
			
			x = cos(nextTheta) * sin(phi);
			y = sin(nextTheta) * sin(phi);
			z = cos(phi);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	
	//the bottom cap
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	float angle;
	for(int i=0; i<capsuleResolution; i++){
		angle = (float)i / (capsuleResolution-1) * TWO_PI;
		x = cos(angle);
		y = 0.0f;
		z = sin(angle);
		glVertex3f(x, y, z);
	}
	glEnd();
	glEndList();
	
}
void ofxCapsule(float x, float y, float z, float size){
	if(capsuleList == 0)ofxCreateCapsuleList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glCallList(capsuleList);
	glPopMatrix();
}
void ofxCapsule(float x, float y, float z, float width, float height, float depth){
	if(capsuleList == 0)ofxCreateCapsuleList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(width, height, depth);
	glCallList(capsuleList);
	glPopMatrix();
}
void ofxCapsule(float x, float y, float z, float width, float height, float depth, float rotX, float rotY, float rotZ){
	if(capsuleList == 0)ofxCreateCapsuleList();
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotX, 0.0f, 0.0f, 1.0f);
	glScalef(width, height, depth);
	glCallList(capsuleList);
	glPopMatrix();
}
//ofxVec3f
void ofxCapsule(ofxVec3f position, float size){
	if(capsuleList == 0)ofxCreateCapsuleList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size, size, size);
	glCallList(capsuleList);
	glPopMatrix();
}
void ofxCapsule(ofxVec3f position, ofxVec3f size){
	if(capsuleList == 0)ofxCreateCapsuleList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(size.x, size.y, size.z);
	glCallList(capsuleList);
	glPopMatrix();
			 
}
void ofxCapsule(ofxVec3f position, ofxVec3f size, ofxVec3f rotation){
	if(capsuleList == 0)ofxCreateCapsuleList();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);
	glCallList(capsuleList);
	glPopMatrix();
}
void ofxSetCapsuleResolution(int _resolution){
	capsuleResolution = _resolution;
	if(capsuleList == 0){
		ofxCreateCapsuleList();
	} else {
		glDeleteLists(capsuleList, 1);
		ofxCreateCapsuleList();
	}
}

///////////////////
//lines, points, etc..
void ofxLine(float x1, float y1, float z1, float x2, float y2, float z2){
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}
void ofxLine(ofxVec3f pos1, ofxVec3f pos2){
	glBegin(GL_LINES);
	glVertex3f(pos1.x, pos1.y, pos1.z);
	glVertex3f(pos2.x, pos2.y, pos2.z);
	glEnd();
}

void ofxPoint(float x, float y, float z){
	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();
}
void ofxPoint(ofxVec3f pos){
	glBegin(GL_POINTS);
	glVertex3f(pos.x, pos.y, pos.z);
	glEnd();
}

void ofxQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
	glBegin(GL_QUADS);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glVertex3f(x4, y4, z4);
	glEnd();
}
void ofxQuad(ofxVec3f pos1, ofxVec3f pos2, ofxVec3f pos3, ofxVec3f pos4){
	glBegin(GL_QUADS);
	glVertex3f(pos1.x, pos1.y, pos1.z);
	glVertex3f(pos2.x, pos2.y, pos2.z);
	glVertex3f(pos3.x, pos3.y, pos3.z);
	glVertex3f(pos4.x, pos4.y, pos4.z);
	glEnd();
}

void ofxTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
	glBegin(GL_TRIANGLES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glEnd();
}
void ofxTriangle(ofxVec3f pos1, ofxVec3f pos2, ofxVec3f pos3){
	glBegin(GL_TRIANGLES);
	glVertex3f(pos1.x, pos1.y, pos1.z);
	glVertex3f(pos2.x, pos2.y, pos2.z);
	glVertex3f(pos3.x, pos3.y, pos3.z);
	glEnd();
}


/*
 INCOMPLETE!!!
////////////////
//Polygons!
static GLUtesselator *theTesselator;
static GLuint shapeMode;
static bool bTessInited = false;
vector<GLfloat>vertices;
vector<float>normals;
vector<GLdouble*>newVertexes;

void CALLBACK ofxTessVertex(void * data){
	glVertex3dv((GLdouble*)data);
}

void CALLBACK ofxTessError(GLenum errCode){
	const GLubyte* estring;
	estring = gluErrorString( errCode);
	fprintf( stderr, "ERROR : %s\n", estring);
}

void CALLBACK ofxTessCombine( GLdouble coords[3], void* vertex_data[4], GLfloat weight[4], void** outData){
    double* vertex = new double[3];
    newVertexes.push_back(vertex);
    vertex[0] = coords[0];
    vertex[1] = coords[1];
    vertex[2] = coords[2];
    *outData = vertex;
}

ofxVec3f calcNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
	ofxVec3f vecA = ofxVec3f(x2-x1, y2-y1, z2-z1);
	ofxVec3f vecB = ofxVec3f(x3-x2, y3-y2, z3-z2);
	ofxVec3f normalVec = vecA.cross(vecB);
	normalVec.normalize();
	return normalVec;
}

void initTesselator();
void drawShapewithTesselator();
void drawShapeWithTesselatorAndNormals();

void drawShapeWithTesselator(){
	if(bTessInited == false){
		bTessInited = true;
		initTesselator();
	}
	
	gluTessBeginPolygon(theTesselator, NULL);
	gluTessBeginContour(theTesselator);
	gluTessNormal(theTesselator, 0,0,1);
	for(int i=0; i<vertices.size(); i+=3){
		gluTessVertex(theTesselator, (GLdouble*)&vertices[i], &vertices);
	}
	gluTessEndContour(theTesselator);
	gluTessEndPolygon(theTesselator);
}

void drawShapeWithTesselatorAndNormals(){
	if(bTessInited == false){
		bTessInited = true;
		initTesselator();
	}
}

void initTesselator(){
	theTesselator = gluNewTess();
	gluTessCallback( theTesselator, GLU_TESS_BEGIN, (void(CALLBACK*)())&glBegin);
	gluTessCallback( theTesselator, GLU_TESS_VERTEX, (void(CALLBACK*)())&ofxTessVertex);
	gluTessCallback( theTesselator, GLU_TESS_COMBINE, (void(CALLBACK*)())&ofxTessCombine);
	gluTessCallback( theTesselator, GLU_TESS_END, (void(CALLBACK*)())&glEnd);
	gluTessCallback( theTesselator, GLU_TESS_ERROR, (void(CALLBACK*)())&ofxTessError);
	
}

void ofxBeginShape(){
	shapeMode = OFX_POLYGON;
	vertices.clear();
	normals.clear();
	if(newVertexes.size() > 0){
		for(int i=0; i<newVertexes.size(); i++){
			delete[] newVertexes[i];
		}
		newVertexes.clear();
	}
}

void ofxBeginShape(GLuint _shapeMode){
	shapeMode = _shapeMode;
	vertices.clear();
	normals.clear();
	if(newVertexes.size() > 0){
		for(int i=0; i<newVertexes.size(); i++){
			delete[] newVertexes[i];
		}
		newVertexes.clear();
	}
}

void ofxVertex(float x, float y, float z){
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void ofxVertex(ofxVec3f vertex){
	vertices.push_back(vertex.x);
	vertices.push_back(vertex.y);
	vertices.push_back(vertex.z);
}

void ofxEndShape(bool bClose){
	if(bClose){
		vertices.push_back(vertices[0]);
		vertices.push_back(vertices[1]);
		vertices.push_back(vertices[2]);
	}
	if((bool)glIsEnabled(GL_LIGHTING)){
		if(shapeMode == OFX_POLYGON) drawShapeWithTesselatorAndNormals();
		else {
			int numFaces = vertices.size() / 3;
			if(shapeMode == OFX_QUADS or shapeMode == OFX_QUAD_STRIP){
				numFaces /= 4;
			}
			ofxVec3f normalVec;
			for(int i=0; i<vertices.size()/3; i+=9){
				normalVec = calcNormal(vertices[i], vertices[i+1], vertices[i+2],
									   vertices[i+3], vertices[i+4], vertices[i+5],
									   vertices[i+6], vertices[i+7], vertices[i+8]);
				for(int j=0; j<3; j++){
					normals.push_back(normalVec.x);
					normals.push_back(normalVec.y);
					normals.push_back(normalVec.z);
				}
			}
			
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, &normals[0]);
			glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
			glDrawArrays(shapeMode, 0, numFaces);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
	} else {
		if(shapeMode == OFX_POLYGON) drawShapeWithTesselator();
		else {
			int numFaces = vertices.size() / 3;
			if(shapeMode == OFX_QUADS or shapeMode == OFX_QUAD_STRIP){
				numFaces /= 4;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
			glDrawArrays(shapeMode, 0, numFaces);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	}
}
*/




