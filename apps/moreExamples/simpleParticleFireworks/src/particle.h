#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#include "ofxVectorMath.h"

class particle
{
    public:
        ofxVec3f pos;
        ofxVec3f vel;
        ofxVec3f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};

        void resetForce();
        void addForce(float x, float y, float z);
        void addDampingForce();
	void setInitialCondition(float px, float py, float pz, float vx, float vy, float vz, int f_red, int f_green, int f_blue);
        void update();
		void addTrailPoint(int x, int y, int z);
        void draw();
		void drawTrails();
	
		float damping;
	
		int red;
		int green;
		int blue;
		int finalRed;
		int finalGreen;
		int finalBlue;
		int glow;
		int color;
	float opacity;
	
		void explode(float vx, float vy, float vz);
		int timeExploded;
		bool exploded;
	
	int lifeSpan;
	bool finished;
	
	vector <ofxVec3f> trail;
	
	ofImage image;

    protected:
    private:
};

#endif // PARTICLE_H
