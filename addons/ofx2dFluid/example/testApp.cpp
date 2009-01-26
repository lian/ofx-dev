#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(111, 111, 111);
	ofSetFrameRate(60);
	//set screen size
	fluid.set_size( ofGetWidth() , ofGetHeight() );
	//set mouse position outside range
	mx = my = -100;
	//make ball2 green
	ball2.set_color(0, 255, 0);
	//make ball2 fast
	ball2.add_velocity(5, 5);
	//uncomment this to turn alpha channel on
	//fluid.set_alpha(true);
	//**for more features check out the fluid setters**
	//set up the color switch bool
	colorSwitch = false;
	//fade out the fluid a little
	fluid.set_fade(true, 0.3);
	

}

//--------------------------------------------------------------
void testApp::update(){
	
	//**Adding Objects to the fluid**//
	//each object must have a unique int id 
	f_object.set_id(1); //setting id
	f_object.randomize_color();//randomises its color you can also use
	//set_color(r, g, b); integers from 0 to 255
	f_object.set_position(mx, my);
	fluid.add_object(f_object);//adding object to the fluid
	
	//adding another fluid object just for fun
	f_object.set_id(2);
	f_object.randomize_color();
	//f_object.set_position(mx + 350 , my + 150); //you can do it like this
	fluid.add_object(f_object);
	
	//**Doing this to show how to use a pointer and get_fluid function
	//to affect the objects you need to do it before update or it wont work
	//this is why you cant set the position in the mouse functions
	ofxFluidObject * ob;
	ob = fluid.get_fluid(2);
	ob->set_position(mx + 350 , my + 150);
	
	//**Adding a force to the fluid at ball2 position**//
	force.set_id(1);
	force.set_position(ball2.x, ball2.y);
	fluid.add_force(force);

	//update fluid
	fluid.update();
	
	//get fluid velocity at ball position
	vel 	= fluid.get_velocity ( ball.x, ball.y );
	//get fluid density at ball position
	dens	= fluid.get_dencity ( ball.x, ball.y );
	//if density is bigger than 0.3 add velocity to the ball
	if (dens > 0.3) ball.add_velocity( vel.x, vel.y );
	//update the ball
	ball.update();
	ball2.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	//draw field
	fluid.draw();
	//draw the ball
	ball.draw();
	ball2.draw();
	
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(		"fps: "+ofToString(ofGetFrameRate()) , 20, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (key == 'c') {
		//create a pointer fluid object
		ofxFluidObject * ob;
		//if colorswitch is false target fluid 1
		if (!colorSwitch) {
			colorSwitch = true;
			ob = fluid.get_fluid(1);
		} else { //else target fluid 2
			colorSwitch = false;
			ob = fluid.get_fluid(2);
		}
		//if pointer is not null randomize color
		if (ob != 0) ob->randomize_color(true);
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
	mx = x;
	my = y;

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	mx = my = -100;
}
