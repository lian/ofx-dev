#pragma once

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxOpenCv.h"

class trackedBlob : public ofxCvBlob{

    public:

        //---------------------------------------------
        void operator = (const ofxCvBlob &A){
            //

            area            = A.area;
			length          = A.length;
			boundingRect    = A.boundingRect;
			centroid        = A.centroid;
            hole            = A.hole;
            nPts            = A.nPts;
			bNew			= true;
			
			pts.clear();
			pts.assign(nPts, ofPoint());
			
			for(int i = 0; i < nPts; i++){
				pts[i] = A.pts[i];
			}
		
        }
		
        //---------------------------------------------
        trackedBlob(){
            id              = 0;
            birthTime       = 0;
            lastAliveTime   = 0;
            activity        = 0;
            assigned        = false;
			bNew			= true;
        }

        //---------------------------------------------
        int   id;
        long  birthTime;
        long  lastAliveTime;
        float activity;
        bool  assigned;
		bool  bNew;

};




























