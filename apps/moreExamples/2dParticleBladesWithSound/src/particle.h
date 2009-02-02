#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#define _OF_ADDON_USING_OFXVECTORMATH
#define _OF_ADDON_USEING_OPENCV
#include "ofAddons.h"
#include "ofxVectorMath.h"

class particle
{
    public:
        ofxVec2f pos;
        ofxVec2f vel;
        ofxVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
		void addClockwiseForce(particle &p, float radius, float scale);
		void addCounterClockwiseForce(particle &p, float radius, float scale);
	
		vector <ofxVec3f> trail;
		void addTrailPoint(int x, int y, int z);
		void drawTrail();
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float vx, float vy);
		void setColor(int red, int blue, int green, float alpha);
	
		int red,blue,green;
		float alpha;
	
        void update();
        void draw();
	
		void bounceOffWalls();
	
	
		float damping;

    protected:
    private:
};

#endif // PARTICLE_H
