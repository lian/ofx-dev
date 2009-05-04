#include "testApp.h"
#include "Particle.h"
#include "msaColor.h"
#include "ParticleSystem.h"


#define FLUID_WIDTH			150


#pragma mark Custom methods



void fadeToColor(float r, float g, float b, float speed) {
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, speed);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(myApp->window.width, 0);
    glVertex2f(myApp->window.width, myApp->window.height);
    glVertex2f(0, myApp->window.height);
    glEnd();
}


// add force and dye to fluid, and create particles
void testApp::addToFluid(float x, float y, float dx, float dy, bool addColor, bool addForce) {
    float speed = dx * dx  + dy * dy * window.aspectRatio2;    // balance the x and y components of speed with the screen aspect ratio
	
    if(speed > 0) {
        if(x<0) x = 0; 
        else if(x>1) x = 1;
        if(y<0) y = 0; 
        else if(y>1) y = 1;
		
        float colorMult = 50;
        float velocityMult = 30;
		
        int index = fluidSolver.getIndexForNormalizedPosition(x, y);
		
		if(addColor) {
			msaColor drawColor;
			int hue = lroundf((x + y) * 180 + ofGetFrameNum()) % 360;
			drawColor.setHSV(hue, 1, 1);
			
			fluidSolver.r[index]  += drawColor.r * colorMult;
			fluidSolver.g[index]  += drawColor.g * colorMult;
			fluidSolver.b[index]  += drawColor.b * colorMult;

			if(drawParticles) particleSystem.addParticles(x * window.width, y * window.height, 10);
		}
		
		if(addForce) {
			fluidSolver.u[index] += dx * velocityMult;
			fluidSolver.v[index] += dy * velocityMult;
		}
		
		if(!drawFluid && ofGetFrameNum()%5 ==0) fadeToColor(0, 0, 0, 0.1);
    }
}





#pragma mark App callbacks

//--------------------------------------------------------------
void testApp::setup() {	 
	// initialize stuff according to current window size
	windowResized(ofGetWidth(), ofGetHeight());	
	
	// setup fluid stuff
	fluidSolver.setup(FLUID_WIDTH, FLUID_WIDTH / window.aspectRatio);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
	
	drawFluid			= true;
	drawParticles		= true;
	renderUsingVA		= true;
	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
#ifdef USE_TUIO
	tuioClient.start(3333);
#endif

	
#ifdef USE_GUI 
	gui.addSlider("fs.viscocity", &fluidSolver.viscocity, 0.0, 0.0002, 0.5); 
	gui.addSlider("fs.colorDiffusion", &fluidSolver.colorDiffusion, 0.0, 0.0003, 0.5); 
	gui.addSlider("fs.fadeSpeed", &fluidSolver.fadeSpeed, 0.0, 0.1, 0.5); 
	gui.addSlider("fs.solverIterations", &fluidSolver.solverIterations, 1, 20); 
	gui.addSlider("fd.drawMode", &fluidDrawer.drawMode, 0, FLUID_DRAW_MODE_COUNT-1); 
	gui.addToggle("fs.doRGB", &fluidSolver.doRGB); 
	gui.addToggle("fs.doVorticityConfinement", &fluidSolver.doVorticityConfinement); 
	gui.addToggle("drawFluid", &drawFluid); 
	gui.addToggle("drawParticles", &drawParticles); 
	gui.addToggle("renderUsingVA", &renderUsingVA); 
#endif
	
}


//--------------------------------------------------------------
void testApp::update(){
#ifdef USE_TUIO
	tuioClient.getMessage();
	
	// do finger stuff
	list<ofxTuioCursor*>cursorList = tuioClient.getTuioCursors();
	for(list<ofxTuioCursor*>::iterator it=cursorList.begin(); it != cursorList.end(); it++) {
		ofxTuioCursor *tcur = (*it);
        float vx = tcur->getXSpeed() * tuioCursorSpeedMult;
        float vy = tcur->getYSpeed() * tuioCursorSpeedMult;
        if(vx == 0 && vy == 0) {
            vx = ofRandom(-tuioStationaryForce, tuioStationaryForce);
            vy = ofRandom(-tuioStationaryForce, tuioStationaryForce);
        }
        addToFluid(tcur->getX(), tcur->getY(), vx, vy);
    }
#endif
	
	fluidSolver.update();
	
	// save old mouse position (openFrameworks doesn't do this automatically like processing does)
	pmouseX = mouseX;
	pmouseY = mouseY;
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetBackgroundAuto(drawFluid);
	
	if(drawFluid) {
		glColor3f(1, 1, 1);
		fluidDrawer.draw(0, 0, window.width, window.height);
	}
	if(drawParticles) particleSystem.updateAndDraw();

#ifdef USE_GUI 
	gui.draw();
#endif
}


void testApp::windowResized(int w, int h) {
	printf("TEST windowResized(%i, %i)\n", w, h);
	window.width		= w;
	window.height		= h;
	
	window.invWidth		= 1.0f/window.width;
	window.invHeight	= 1.0f/window.height;
	window.aspectRatio	= window.width * window.invHeight;
	window.aspectRatio2 = window.aspectRatio * window.aspectRatio;
}


#pragma mark Input callbacks

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
    switch(key) {
#ifdef USE_GUI
		case ' ':
			
			gui.toggleDraw();	
			glClear(GL_COLOR_BUFFER_BIT);
			break;
#endif			
		case 'f':
			ofToggleFullscreen();
			break;
		case 's':
			static char fileNameStr[255];
			sprintf(fileNameStr, "output_%0.4i.png", ofGetFrameNum());
			static ofImage imgScreen;
			imgScreen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			printf("Saving file: %s\n", fileNameStr);
			imgScreen.saveImage(fileNameStr);
			break;
			
    }
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	float mouseNormX = x * window.invWidth;
    float mouseNormY = y * window.invHeight;
    float mouseVelX = (x - pmouseX) * window.invWidth;
    float mouseVelY = (y - pmouseY) * window.invHeight;

    addToFluid(mouseNormX, mouseNormY, mouseVelX, mouseVelY, true);
}

void testApp::mouseDragged(int x, int y, int button) {
	float mouseNormX = x * window.invWidth;
    float mouseNormY = y * window.invHeight;
    float mouseVelX = (x - pmouseX) * window.invWidth;
    float mouseVelY = (y - pmouseY) * window.invHeight;
	
	addToFluid(mouseNormX, mouseNormY, mouseVelX, mouseVelY, false);
}

