#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofxVec2f gravity(0, 1);
	physics = new ofxPhysics2d(gravity);
	physics->checkBounds(false);
	physics->enableCollisions(true);
	physics->setNumIterations(5);
	
	bCreateParticles = false;
	mouseParticle = new ofxParticle();
	mouseParticle->setActive(false);
	mouseSpring = NULL;
	newParticle = NULL;
		
	newParticleIncrement = 0;
	bCreateParticleString = false;
	beginParticleString = NULL;
	endParticleString = NULL;
}

//--------------------------------------------------------------
void testApp::update(){
	mouseParticle->set(mouseX, mouseY);
	if(newParticle){
		newParticle->setRadius((sin(newParticleIncrement)*100) + 5);
		newParticleIncrement+= 0.01f;
		newParticle->moveTo(mouseX, mouseY);
	}
	if(bCreateParticles){
		if(ofGetFrameNum() % 5 == 0){
			float radius = ofRandom(10, 50);
			float mass = radius * 0.5f;
			ofxParticle* p = new ofxParticle(mouseX, mouseY, radius, mass);
			float randomStep = 5;
			ofxVec2f impulse(ofRandom(-randomStep, randomStep), ofRandom(-randomStep, randomStep));
			p->applyImpulse(impulse);
			particles.push_back(p);
			physics->add(p);
		}
	}
	for(int i=0; i<particles.size(); i++){
		if(particles[i]->y > ofGetHeight() + particles[i]->getRadius()){
			while(physics->getConstraintWithParticle(particles[i]) != NULL){
				physics->deleteConstraintsWithParticle(particles[i]);
			}
			physics->deleteParticle(particles[i]);
			particles.erase(particles.begin()+i);
		}
	}
	physics->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofNoFill();
	ofSetColor(240, 240, 240);
	physics->renderParticles();
	ofSetColor(100, 100, 100);
	physics->renderConstraints();
	ofSetColor(255,255,255);
	string info = "num particles: " + ofToString(physics->getNumParticles()) + "\n" + 
				  "num constraints: " + ofToString(physics->getNumConstraints()) + "\n" + 
				  "fps: " + ofToString(ofGetFrameRate());
	ofDrawBitmapString(info, 20,20);
}

void testApp::createParticleString(ofxParticle*begin, ofxParticle*end, int numParticles){
	ofxVec2f step = (*end - *begin) / (numParticles-1);
	ofxVec2f particlePos = *begin;
	ofxParticle* prevParticle = begin;
	prevParticle->setActive(false);
	end->setActive(false);
	particlePos += step;
	if(!physics->has(begin)) physics->add(begin);
	if(!physics->has(end)) physics->add(end);
	for(int i=1; i<numParticles; i++){
		ofxParticle* p = new ofxParticle(particlePos, 5);
		float rest = prevParticle->distanceTo(p);
		ofxSpring* s = new ofxSpring(prevParticle, p, rest, 1.1);
		physics->add(p);
		physics->add(s);
		if(i==numParticles-1)p->setActive(false);
		prevParticle = p;
		particlePos += step;
	}
	float rest = prevParticle->distanceTo(end);
	ofxSpring* s = new ofxSpring(prevParticle, end, rest);
	physics->add(s);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' '){
		bCreateParticleString = true;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == 'c' or key == 'C'){
		physics->deleteAll();
		particles.clear();
	}
	if(key == ' '){
		bCreateParticleString = false;
	}
	
	if(key == 'b' or key == 'B'){
		physics->checkBounds(!physics->boundsCheck());
	}
	
	if(key == ' '){
		if(beginParticleString){
			physics->deleteParticle(beginParticleString);
			beginParticleString = NULL;
		}
	}
	
	if(key == 'r' or key == 'R'){
		for(int i=0; i<particles.size(); i++){
			if(ofRandomuf() < 0.2f){
				float rest = ofRandom(50, 200);
				ofxParticle*b = particles[(int)ofRandom(0, particles.size())];
				while(b == particles[i]){
					b = particles[(int)ofRandom(0, particles.size())];
				}
				ofxSpring*s = new ofxSpring(particles[i], b, rest);
				physics->add(s);
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(button == 0){
		if(bCreateParticleString){
			beginParticleString = new ofxParticle(x, y, 5);
			beginParticleString->setActive(false);
			physics->add(beginParticleString);
		} else {
			ofPoint mousePoint = ofPoint(x, y);
			ofxParticle* particleUnderMouse = physics->getParticleUnderPoint(mousePoint);
			if(particleUnderMouse){
				float rest = mouseParticle->distanceTo(particleUnderMouse);
				mouseSpring = new ofxSpring(mouseParticle, particleUnderMouse, rest);
				physics->add(mouseSpring);
			} else {
				if(newParticle == NULL){
					newParticle = new ofxParticle(x, y, 1);
					newParticle->setActive(false);
					physics->add(newParticle);
					particles.push_back(newParticle);
				} 
			}
			
		}
	}
	if(button == 2){
		bCreateParticles = true;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(bCreateParticleString){
		if(beginParticleString){
			endParticleString = new ofxParticle(x, y, 5);
			endParticleString->setActive(false);
			int numParticles = (int)(beginParticleString->distanceTo(endParticleString)/10);
			createParticleString(beginParticleString, endParticleString, numParticles);
			beginParticleString = NULL;
			endParticleString = NULL;
		}
		bCreateParticleString = false;
	} 
	
	if(mouseSpring){
		physics->deleteConstraint(mouseSpring);
		mouseSpring = NULL;
	}
	if(newParticle){
		newParticle->setActive(true);
		newParticle->setMass(newParticle->getRadius() * 0.5);
		newParticle = NULL;
		newParticleIncrement = 0;
	}
	bCreateParticles = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

