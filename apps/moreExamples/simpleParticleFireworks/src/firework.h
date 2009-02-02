#ifndef FIREWORK
#define FIREWORK

#include "ofMain.h"
#define OF_ADDON_USING_OFXVECTORMATH
#include "ofAddons.h"

#include "particle.h"

class firework
	{
    public:
        ofxVec3f pos;
        ofxVec3f vel;
        ofxVec3f frc;   // frc is also know as acceleration (newton says "f=ma")
		
        firework();
		virtual ~firework(){};
		
        void seed();
		void launch();
		void addForce(float x, float y, float z);
		void addDampingForce();
		void resetForce();
		void update();
		void explode();
		bool exploded;
		void draw();
		
		float damping;
		
		bool isFinished();
		bool finished;
		int finishedCounter;
		
		vector <particle> particles;
		
    protected:
    private:
	};

#endif // PARTICLE_H
