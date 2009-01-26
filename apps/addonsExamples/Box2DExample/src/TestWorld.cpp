/*
* this class is a testing class for the box2d system
* christopher baker <http://christopherbaker.net>
*/

#include "TestWorld.h"


TestWorld::TestWorld() {
	
	numBodies = 500; // this is just the same as the b2Body* bodies[500]; array in the header
					 // also b2Settings.h will allow you to have more than 512 bodies

	// this allows us to get from pixels to meters units of the projection
	pixels_per_meter = 100.0f;	// pixels/meter (so one pixel = 
	meters_per_pixel = 1.0f / pixels_per_meter;
	
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	timeStep = 1.0f / 60.0f;
	iterations = 2;
	
	/* build the world */
	// much of this is just taken from help files and explained in the box2d tutorial
	
	
	// set up world bounding box
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(p2m(-5000.0f), p2m(-5000.0f));
	worldAABB.upperBound.Set(p2m(5000.0f), p2m(1000.0f));
	
	// Define the gravity vector.
	gravity = new b2Vec2(p2m(0.0f), p2m(-10.0f));
	
	// Do we want to let bodies sleep?
	bool doSleep = true;
	
	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(worldAABB, *gravity, doSleep);
	
	// make the stage
	makeStage();
	
	// Define the dynamic bodies. We set its position and call the body factory.
	b2BodyDef bodyDef; // this is reuseable because the body factory just copies it
	b2CircleDef circleDef;  // this is reuseable because the body factory just copies it
	
	for(int i = 0; i < numBodies; i++) {
		
		// create a body at a random position on screen.
		// make sure to use the p2m() and m2p() functions to set the appropriate positions in the b2World
		bodyDef.position.Set(p2m(ofRandom(10,ofGetWidth()-10)),p2m(ofRandom(10,ofGetHeight()-10)));
		
		// create the body in the world
		bodies[i] = world->CreateBody(&bodyDef);
		
		// now add collision shapes to that body (just make abunch of random ones)
		circleDef.radius = p2m(ofRandom(5,5));
		circleDef.density = ofRandom(0.1f,10.25f);
		circleDef.friction = ofRandom(0.1f,1.0f);
		circleDef.restitution = ofRandom(0.1f,1.0f);
		
		// Add the shape(s) to the body.
		bodies[i]->CreateShape(&circleDef);
		bodies[i]->SetMassFromShapes();
		
	}
	
	// make a simple massless obstacle
	// reuse the bodyDef and circleDef from above
	
	// create a body at a random position on screen.
	// make sure to use the p2m() and m2p() functions to set the appropriate positions in the b2World
		bodyDef.position.Set(p2m(ofGetWidth()/2.0f),p2m(ofGetHeight()/2.0f));
		
		// create the body in the world
		obstacle = world->CreateBody(&bodyDef);
		
		// now add collision shapes to that body (just make abunch of random ones)
		circleDef.radius = p2m(100);
		circleDef.density = 0;
		circleDef.friction = 0.1f;
		circleDef.restitution = 0.1f;
		
		// Add the shape(s) to the body.
		obstacle->CreateShape(&circleDef);
		obstacle->SetMassFromShapes(); // should be zero

	
	
	
	
	
}

TestWorld::~TestWorld() {
	delete gravity;
	delete world; // when deleted the world will take all of it's bodies with it
	delete[] bodies; // 
}


/* these are the pixel to meters converters */
float TestWorld::m2p(float meters) {
	return meters * pixels_per_meter;
}


float TestWorld::p2m(float pixels) {
	return pixels * meters_per_pixel;
}



void TestWorld::update() {
	
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	world->Step(timeStep, iterations);
	
	
}

void TestWorld::reverseGravity() {
	
	(*gravity) *= -1; // reverse gravity vector
	
	world->SetGravity(*gravity); // set a new gravity vector

	// cycle through the bodies and make sure they're awake.
	// you could do this or just shoot another body at the crowd 
	// to wake them up.
	
	for(int i = 0; i < numBodies; i++) {
		bodies[i]->WakeUp();
	}

	printf("GRAVITY change!! %4.2f %4.2f %4.2f\n", gravity->x, gravity->y);
	
}

void TestWorld::draw() {

	ofBackground(0,0,0);
	

	// cycle through the bodies and draw them.
	for(int i = 0; i < numBodies; i++) {
		ofFill();
		
		// color sleeping bodies blue, active bodies red
		if(bodies[i]->IsSleeping()) {
			ofSetColor(0,0,255); // blue ellispe
		} else {
			ofSetColor(255,0,0); // red ellipse

		}
		
		b2Vec2 dbPosition = bodies[i]->GetPosition();
		float32 dbAngle = bodies[i]->GetAngle();
		
		ofEllipse(m2p(dbPosition.x),m2p(dbPosition.y),10, 10);
		
		// yellow angle pointer
		ofSetColor(255,255,0);
		ofLine(m2p(dbPosition.x),m2p(dbPosition.y),m2p(dbPosition.x)+10*cos(dbAngle),m2p(dbPosition.y)+10*sin(dbAngle));
	}
	
	// draw the obstacle
	b2Vec2 dbPosition = obstacle->GetPosition();
	ofSetColor(127,127,127);
	ofEllipse(m2p(dbPosition.x),m2p(dbPosition.y),200,200);
	
	
	// draw the stage (the red bounding box)
	drawStage();

	
}



void TestWorld::drawStage() {
	
	// this is the position of the stage body
	b2Vec2 p = stage->GetPosition();
	
	// make a green dot at the center of the massless stage for reference
	ofSetColor(0,255,0);
	ofEllipse(m2p(p.x),m2p(p.y),2,2);
	
	
	// now get all of the shapes attached to the massless stage body
	for (b2Shape* shape = stage->GetShapeList(); shape; shape = shape->GetNext())
	{
	
		// make sure to only draw the polygon shapes
		if(shape->GetType()==e_polygonShape) {
			
			b2PolygonShape* poly = (b2PolygonShape*)shape; // get the poly shape
			int32 vertexCount = poly->GetVertexCount(); // get the number of vertices in the shape (they are squares)
			
			const b2Vec2* vertices = poly->GetVertices();
			
			b2Assert(vertexCount <= b2_maxPolygonVertices);  // this just makes sure there aren't too many 
															 // b2_maxPolygonVertices is defined in b2Settings.h
			
			
			// draw the box shapes in red 
			ofSetColor(255,0,0);
			ofBeginShape();
			
			for (int32 j = 0; j < vertexCount; ++j)
			{
				
				b2Vec2 worldPoint = stage->GetWorldPoint(vertices[j]); // get the "world" points of the shapes
																	   // if you don't get the "world" points
																	   // it will just give you the local vertex points
				
				ofVertex(m2p(worldPoint.x), m2p(worldPoint.y)); // use m2p to convert the box2D meters to screen pixels
			}
		
			ofEndShape();
		}
	}	
	
}

void TestWorld::makeStage() {
	
	/* make a stage that encloses the whole screen */
	
	float offset = p2m(400);
	float half_thickness = p2m(5); // thickness of the wall
	float half_height = p2m(ofGetHeight()/2.0F);
	float half_width =  p2m(ofGetWidth()/2.0F);
	
	float centerX = p2m(ofGetWidth()/2.0f);
	float centerY = p2m(ofGetHeight()/2.0f);
	
	// create a body right in the middle
	b2BodyDef bd;
	bd.position.Set(centerX,centerY);
	stage = world->CreateBody(&bd);
	
	// define the boundary shapes
	b2PolygonDef sd;
	sd.density = 0.0f; // 0 mass so they don't move
	
	// check the tutorial for creating shapes using SetAsBox
	
	// LEFT WALL
	sd.SetAsBox(half_thickness, half_height, b2Vec2(-half_width, 0.0f), 0.0f);
	stage->CreateShape(&sd);
	
	// RIGHT WALL
	sd.SetAsBox(half_thickness, half_height, b2Vec2(half_width, 0.0f), 0.0f);
	stage->CreateShape(&sd);
	
	//  TOP WALL
	sd.SetAsBox(half_thickness, half_width, b2Vec2(0.0f, -half_height), 0.5f * b2_pi);
	stage->CreateShape(&sd);
	
	//	BOTTOM WALL
	sd.SetAsBox(half_thickness, half_width, b2Vec2(0.0f, half_height), -0.5f * b2_pi);
	stage->CreateShape(&sd);
	
	
}