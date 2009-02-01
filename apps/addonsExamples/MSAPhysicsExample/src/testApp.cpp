#include "testApp.h"

#define	SPRING_MIN_STRENGTH		0.005
#define SPRING_MAX_STRENGTH		0.01

#define	SPRING_MIN_WIDTH		3
#define SPRING_MAX_WIDTH		10

#define PARTICLE_MIN_MASS		1
#define PARTICLE_MAX_MASS		3

#define PARTICLE_MIN_SIZE		10
#define PARTICLE_MAX_SIZE		30

#define	FIX_PROBABILITY			10		// % probability of a particle being fixed on creation
#define SPRING_PROBABILITY		50		// % probability of a particle being attached on a spring on creation

#define FORCE_AMOUNT			50

#define EDGE_BOUNCE				0.8
#define EDGE_DRAG				0.8

#define ROT_SPEED				0

bool drawWire = true;
bool drawMesh = false;

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	physics.setGravity(0, 1, 0);
	
	initScene();
	
	// setup lighting
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
}

void testApp::initScene() {
	physics.clear();									// clear all particles and springs etc
	
	physics.makeParticle(-WIDTH/4, 0, -WIDTH/4, PARTICLE_MIN_MASS)->makeFixed();		// create a node in top left back and fix
	physics.makeParticle( WIDTH/4, 0, -WIDTH/4, PARTICLE_MIN_MASS)->makeFixed();		// create a node in top right back and fix
	physics.makeParticle(-WIDTH/4, 0,  WIDTH/4, PARTICLE_MIN_MASS)->makeFixed();		// create a node in top left front and fix
	physics.makeParticle( WIDTH/4, 0,  WIDTH/4, PARTICLE_MIN_MASS)->makeFixed();		// create a node in top right front and fix
	
	for(int i=0; i<20; i++) addRandomParticle();
}


void testApp::addRandomParticle() {
	ofxMSAParticle* p = physics.makeParticle(ofRandom(-WIDTH/2, WIDTH/2), ofRandom(0, HEIGHT), ofRandom(-WIDTH/2, WIDTH/2), ofRandom(PARTICLE_MIN_MASS, PARTICLE_MAX_MASS));		// create a node in a random position
	if(ofRandom(0, 100) < FIX_PROBABILITY) p->makeFixed();
	
	if(ofRandom(0, 100) < SPRING_PROBABILITY) {
		ofxMSAParticle *a = physics.getParticle((int)ofRandom(0, physics.numberOfParticles()-1));
		physics.makeSpring(a, p, ofRandom(SPRING_MIN_STRENGTH, SPRING_MAX_STRENGTH), ofRandom(10, WIDTH/2));
	}
	
}

void testApp::addRandomSpring() {
	ofxMSAParticle *a = physics.getParticle((int)ofRandom(0, physics.numberOfParticles()));
	ofxMSAParticle *b = physics.getParticle((int)ofRandom(0, physics.numberOfParticles()));
	physics.makeSpring(a, b, ofRandom(SPRING_MIN_STRENGTH, SPRING_MAX_STRENGTH), ofRandom(10, WIDTH/2));
}


//--------------------------------------------------------------
void testApp::update() {
	for(int i=0; i<physics.numberOfParticles(); i++) {
		ofxMSAParticle *p = physics.getParticle(i);
		ofxVec3f vel = p->getVelocity();
		if(p->y > HEIGHT) {
			p->moveTo(p->x, HEIGHT, p->z);
			p->setVelocity(vel.x * EDGE_DRAG, -vel.y * EDGE_BOUNCE, vel.z * EDGE_DRAG);
		}
		if(p->x < -WIDTH/2) {
			p->moveTo(-WIDTH/2, p->y, p->z);
			p->setVelocity(-vel.x * EDGE_BOUNCE, vel.y * EDGE_DRAG, vel.z * EDGE_DRAG);
		} else if(p->x > WIDTH/2) {
			p->moveTo(WIDTH/2, p->y, p->z);
			p->setVelocity(-vel.x * EDGE_BOUNCE, vel.y * EDGE_DRAG, vel.z * EDGE_DRAG);
		}
		if(p->z < -WIDTH/2) {
			p->moveTo(p->x, p->y, -WIDTH/2);
			p->setVelocity(vel.x * EDGE_DRAG, vel.y * EDGE_DRAG, -vel.z * EDGE_BOUNCE);
		} else if(p->z > WIDTH/2) {
			p->moveTo(p->x, p->y, WIDTH/2);
			p->setVelocity(vel.x * EDGE_DRAG, vel.y * EDGE_DRAG, -vel.z * EDGE_BOUNCE);
		}
	}
	
	physics.update();
}


static float rot = 0;

//--------------------------------------------------------------
void testApp::draw() {
	glPushMatrix();
	
	glTranslatef(WIDTH/2, 0, -WIDTH/2);		// center scene
	glRotatef(rot, 0, 1, 0);			// rotate scene
	rot += ROT_SPEED;						// slowly increase rotation (to get a good 3D view)
	
	if(drawWire) {
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		
		// draw springs
		glColor4f(1, 1, 1, 1);
		for(int i=0; i<physics.numberOfSprings(); i++) {
			ofxMSASpring *spring = (ofxMSASpring *) physics.getSpring(i);
			ofxMSAParticle *a = spring->getOneEnd();
			ofxMSAParticle *b = spring->getTheOtherEnd();
			ofxVec3f vec = (*b - *a);
			float dist = vec.length();
			float angle = acos( vec.z / dist ) * RAD_TO_DEG;
			if(vec.z <= 0 ) angle = -angle;
			float rx = -vec.y * vec.z;
			float ry =  vec.x * vec.z;
			
			glPushMatrix();
			glTranslatef(a->x, a->y, a->z);
			glRotatef(angle, rx, ry, 0.0);
			float size  = (spring->strength - SPRING_MIN_STRENGTH) / (SPRING_MAX_STRENGTH - SPRING_MIN_STRENGTH) * (SPRING_MAX_WIDTH - SPRING_MIN_WIDTH) + SPRING_MIN_WIDTH;
			
			glScalef(size, size, dist);
			glTranslatef(0, 0, 0.5);
			glutSolidCube(1);
			glPopMatrix();
		}
		
		// draw particles
		for(int i=0; i<physics.numberOfParticles(); i++) {
			ofxMSAParticle *p = physics.getParticle(i);
			if(p->isFixed()) glColor4f(1, 0, 0, 1);
			else glColor4f(1, 1, 1, 1);
			
			glPushMatrix();
			glTranslatef(p->x, p->y, p->z);
			float size  = (p->getMass() - PARTICLE_MIN_MASS) / (PARTICLE_MAX_MASS - PARTICLE_MIN_MASS) * (PARTICLE_MAX_SIZE - PARTICLE_MIN_SIZE) + PARTICLE_MIN_SIZE;
			glutSolidSphere (size, 15, 15);
			glPopMatrix();
		}
	}
	
	if(drawMesh) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		
		glBegin(GL_TRIANGLES);			
		for(int i=0; i<physics.numberOfSprings(); i++) {
			glColor4f(cos(i*438) * 0.5 + 1, cos(i*7894) * 0.5 + 1, cos(i*437786) * 0.5 + 1, 0.05);
			ofxMSASpring *spring = (ofxMSASpring *)physics.getSpring(i);
			ofxMSAParticle *a = spring->getOneEnd();
			ofxMSAParticle *b = spring->getTheOtherEnd();
			glVertex3f(a->x, a->y, a->z);
			glVertex3f(b->x, b->y, b->z);			
		}
		glEnd();
		
	}
	
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor4f(1, 1, 1, 1);
	ofDrawBitmapString( " FPS: " + ofToString(ofGetFrameRate(), 2)
					   + " | Number of particles: " + ofToString(physics.numberOfParticles())
					   + " | Number of springs: " + ofToString(physics.numberOfSprings())
					   , 20, 15);
	
	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	switch(key) {
		case '1':
			drawWire ^= true;
			break;
		case '2':
			drawMesh ^= true;
			break;
			
		case 'p':
			addRandomParticle();
			break;
		case 's':
			addRandomSpring();
			break;
		case 'f':
			for(int i=0; i<physics.numberOfParticles(); i++) {
				ofxMSAParticle *p = physics.getParticle(i);
				if(p->isFree()) p->addVelocity(ofRandom(-FORCE_AMOUNT, FORCE_AMOUNT), ofRandom(-FORCE_AMOUNT, FORCE_AMOUNT), ofRandom(-FORCE_AMOUNT, FORCE_AMOUNT));
			}
			break;
		case 'l':
			for(int i=0; i<physics.numberOfParticles(); i++) {
				ofxMSAParticle *p = physics.getParticle(i);
				if(ofRandom(0, 100) < FIX_PROBABILITY) p->makeFixed();
				else p->makeFree();
			}
			break;
		case 'u':
			for(int i=0; i<physics.numberOfParticles(); i++) {
				ofxMSAParticle *p = physics.getParticle(i);
				p->makeFree();
			}
			break;
			
		case ' ':
			initScene();
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
