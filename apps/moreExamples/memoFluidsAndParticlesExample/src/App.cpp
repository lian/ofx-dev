#include "App.h"

float			App::camThreshold	= 30;
float			App::camSilAlpha		= 0.2f;
bool			App::mirrorVideo	= true;

float		CAM_FLUID_CREATE =		0.01f;							// factor for how much cam movement creates fluid
float		CAM_FLUID_SPEED	 =		0.0025f;							// factor for how much cam movement affects fluid speed


//--------------------------------------------------------------
void App::setup(){
	ofBackground(0, 0, 0);
	//ofHideCursor();
	
	mouseX = mouseY = mouseOldX = mouseOldY = mouseVelX = mouseVelY = 0;
	ofSeedRandom();

	ofSetFrameRate(FPS);
	
	showVideoColor		= false;
	showVideoGrey		= false;
	showVideoBGDiff		= false;
	showVideoCurDiff	= true;
	showPiano			= true;
	showDebugVideo		= true;
	showFluid			= true;
	showConsole			= true;
	showGlitter			= true;
	showBalls			= true;
	doOpticalFlow		= true;

	ofSetBackgroundAuto(true);				// change this to false later
	
	glDepthMask(false);						// disable writing to depth buffer
	glDisable(GL_DEPTH_TEST);				// disable sorting (dont really need both but whatever)
	glEnable( GL_BLEND );					// enable blending
	glBlendFunc(GL_ONE, GL_ONE);			// set to additive (ignoring all alpha values, don't need'em)
	
	// init objects
	for(int i=0; i<NUM_CAMERAS; i++ ) motionTracker[i].init(320, 240, i);
	fluid.init(WIDTH, HEIGHT, FLUID_NX, FLUID_NY, FLUID_DT, FLUID_VISC, FLUID_FADE_SPEED);
	balls.init(BALL_MAX_SPEED, BALL_FLUID_VEL_MULT, 0.2f, &fluid, BALL_MAX_COUNT, "ball.png");
	glitter.init(GLITTER_MAX_SPEED, GLITTER_FLUID_VEL_MULT, 0.2f, &fluid, GLITTER_MAX_COUNT, "glitter.png");
}

//--------------------------------------------------------------
void App::update(){
	//	printf("***************\nStarting UPDATE loop \n");
	
	mouseVelX = mouseX - mouseOldX;
	mouseVelY = mouseY - mouseOldY;
	
	if(showBalls) balls.update();
	if(showGlitter) glitter.update();
	fluid.update();

	if(doOpticalFlow) for(int i=0; i<NUM_CAMERAS; i++ ) {
		motionTracker[i].update();
		if(motionTracker[i].bHasNewFrame) {
		
			int fx, fy;			// fluid coordinates
			float dx, dy;		// get cam velocity into these vars
			float scrX, scrY;	// will store screen coordinates
			float camX;			// will store cam velmap x coordinate

			float speed2;		// absolute speed squared
			
			int startX	= motionTracker[i].index * CAM_FLUID_WIDTH;
			int endX	= startX + CAM_FLUID_WIDTH;
			float max = 0;
			
			float colR = sin(ofGetElapsedTimeMillis() * 0.01f) * 0.5 + 0.5;//ofRandom(0, 1);
			float colG = cos(ofGetElapsedTimeMillis() * 0.01f) * 0.5 + 0.5;
			float colB = sin(ofGetElapsedTimeMillis() * 0.0001f) * 0.5 + 0.5;
			
			for ( fx = startX; fx < endX; fx+= FLUID_INJECT_STEP ) {
				camX = (fx - startX) * CAM_FLUID_INV_WIDTH;			// x coordinate in the camera velocity map
				scrX = fx * FLUID_INV_NX * WIDTH;					// screen X coordinate
				
				for ( fy = 0; fy < FLUID_NY; fy+= FLUID_INJECT_STEP) {
					scrY = fy * FLUID_INV_NY * HEIGHT;
				
					motionTracker[i].getVelAtNorm(camX, fy * FLUID_INV_NY, &dx, &dy);
					speed2 = dx * dx + dy * dy;
					max = MAX(speed2, max);
					
					if(speed2 > BALL_TRIGGER_THRESH * 2.0f) {
						if(ofRandom(0, speed2) > BALL_TRIGGER_THRESH)	// pick a random number and create if above threshold (so less for slow)
							balls.add(scrX, scrY, dx, dy);
					}
					if(speed2 > GLITTER_TRIGGER_THRESH ) {		// if above speed threshold create glitter
						if(ofRandom(0, speed2) > GLITTER_TRIGGER_THRESH * 2.0)	// pick a random number and create if above threshold (so less for slow)
							glitter.add(scrX + ofRandom(-GLITTER_DIST_RADIUS, GLITTER_DIST_RADIUS), scrY + ofRandom(-GLITTER_DIST_RADIUS, GLITTER_DIST_RADIUS), dx, dy);
					}
					
					fluid.addAtPixel(fx, fy, dx, dy, CAM_FLUID_CREATE * FLUID_INJECT_STEP * FLUID_INJECT_STEP, CAM_FLUID_SPEED * FLUID_INJECT_STEP * FLUID_INJECT_STEP, colR, colG, colB, speed2 * speed2);
				}
			}
			
		}
	}
	//	printf("** ending UPDATE loop \n");
}

//--------------------------------------------------------------
void App::draw(){
	//	printf("Starting DRAW loop \n");

	glDisable( GL_BLEND );				// see if this is quicker than clearing backgronud every frame
	if(showFluid) fluid.draw();
	glEnable( GL_BLEND );
	
	if(showBalls) balls.render();
	if(showGlitter) glitter.render();
	
	for(int i=0; i<NUM_CAMERAS; i++ ) {
		glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
		if(showVideoColor) motionTracker[i].drawColor();
		if(showVideoGrey) motionTracker[i].drawGrey();
		if(showVideoBGDiff) motionTracker[i].drawBGDiff();
		if(showVideoCurDiff) motionTracker[i].drawCurDiff();
		
		if(showDebugVideo) motionTracker[i].drawDebugVideo();
		
	}

	if(showConsole) {
		glColor3f(1.0f, 1.0f, 1.0f);
		ofDrawBitmapString(		"fps: "+ofToString(ofGetFrameRate())
						   + " performanceDuration: " + ofToString(performanceDuration)
						   + " visc: " + ofToString(fluid.getVisc()) +
						   + " fluid_create: " + ofToString(CAM_FLUID_CREATE)
						   + " fluid_speed: " + ofToString(CAM_FLUID_SPEED)
						   + " camThreshold: " + ofToString(camThreshold)
						   + " camSilAlpha: " +  ofToString(camSilAlpha)
						   + " avgColor: " + ofToString(fluid.getAvgDensity())
						   + " uniformity: " + ofToString(fluid.getUniformity())
						   , 20, 30);
	}
	
	mouseOldX = mouseX;
	mouseOldY = mouseY;
	
	//	printf("ending DRAW loop \n");
}

//--------------------------------------------------------------
void App::keyPressed  (int key){
	for(int i=0; i<NUM_CAMERAS; i++) motionTracker[i].keyPressed(key);			// checks T (Settings) key and S (save background)
	
	switch(key) {
	
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '6':
		case '7':
		case '8':
		case '9': fluid.setVisc((key - '0') * 0.0001f);		break;
			
		case 'f': ofToggleFullscreen();							break;
		case ']': CAM_FLUID_CREATE *= 1.05f;					break;
		case '[': CAM_FLUID_CREATE *= 0.95f;					break;
		case '.': CAM_FLUID_SPEED *= 1.05f;					break;
		case ',':  CAM_FLUID_SPEED *= 0.95f;					break;
		case '>': camSilAlpha *= 1.05f;							break;
		case '<': camSilAlpha *= 0.95f;							break;
		case 'c': showConsole = !showConsole;					break;
		case 'g': showGlitter = !showGlitter;					break;
		case 'b': showBalls = !showBalls;						break;
		case 'l': showFluid = !showFluid;						break;
		case 'v': showDebugVideo = !showDebugVideo;				break;
		case 'p': showPiano = !showPiano;						break;
		case 'm': mirrorVideo = !mirrorVideo;					break;
		case 'o': doOpticalFlow = !doOpticalFlow;				break;

		case 'q': showVideoColor = !showVideoColor;				break;		
		case 'w': showVideoGrey = !showVideoGrey;				break;		
		case 'e': showVideoBGDiff = !showVideoBGDiff;			break;		
		case 'r': showVideoCurDiff = !showVideoCurDiff;			break;	
		
		case OF_KEY_BACKSPACE: fluid.reset();					break;
					
		case '+':	
			camThreshold ++;
			if (camThreshold > 255) camThreshold = 255;
			break;
		case '-':
			camThreshold --;
			if (camThreshold < 0) camThreshold = 0;
			break;
	}
}

//--------------------------------------------------------------
void App::keyReleased  (int key){
}

//--------------------------------------------------------------
void App::mouseMoved(int x, int y ){
	mouseX = x * INV_WIDTH;
	mouseY = y * INV_HEIGHT;
	if(mouseOldX == 0) mouseOldX = mouseX;
	if(mouseOldY == 0) mouseOldY = mouseY;
}

//--------------------------------------------------------------
void App::mouseDragged(int x, int y, int button){
	mouseX = x * INV_WIDTH;
	mouseY = y * INV_HEIGHT;

	fluid.addAtNorm(mouseX, mouseY, mouseVelX, mouseVelY, 50000000000.0f, 5.0f, ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1));
}

//--------------------------------------------------------------
void App::mousePressed(int x, int y, int button){
	//	printf("framerate : %.2f\n", ofGetFrameRate());
	mouseX = x * INV_WIDTH;
	mouseY = y * INV_HEIGHT;
	
	mouseDown = true;
	
	balls.add(mouseX * WIDTH, mouseY * HEIGHT, mouseVelX * WIDTH, mouseVelY * HEIGHT);
}

//--------------------------------------------------------------
void App::mouseReleased(){
	mouseDown = false;
	
}
