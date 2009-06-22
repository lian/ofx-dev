#include "blobTracker.h"

//-------------------------------------------
blobTracker::blobTracker(){
	setup(500);
}

//-------------------------------------------
blobTracker::~blobTracker(){
	storedBlobs.clear();
}

//-------------------------------------------
void blobTracker::setup(int timeToLiveMs){
	storedBlobs.clear();

	numStoredBlobs	= 0;
	genID			= 0;
	lastTime		= 0;
	deathTime		= timeToLiveMs;
}

//-------------------------------------------
void blobTracker::resetCounter(){
	genID = 0;
	storedBlobs.clear();

	//printf("------- RESET \n");
}

//-------------------------------------------
void blobTracker::begin(){
	for(int j = 0; j < storedBlobs.size(); j++){
		storedBlobs[j].assigned = false;
	}
}

//-------------------------------------------
void blobTracker::end(){

	if(storedBlobs.size() <= 0)return;

	int timeMillis = ofGetElapsedTimeMillis();
	vector <int> eraseList;
	eraseList.clear();


	//we do it in reverse order so when we erase from the list it doesn't mess up the other indexes
	for(int j = storedBlobs.size()-1; j >= 0; j--){
		if( storedBlobs[j].assigned )storedBlobs[j].lastAliveTime = timeMillis;
		else if( timeMillis - storedBlobs[j].lastAliveTime > deathTime ){
			eraseList.push_back(j);
		}
	}

	//now kill the old stored trackedBlobs
	for(int j = 0; j < eraseList.size(); j++){
		//printf("deleting trackedBlob %i \n", eraseList[j]);
		storedBlobs.erase(storedBlobs.begin() + eraseList[j]);
	}


	numStoredBlobs = storedBlobs.size();
    //printf("finished deleteing - %i left\n", numStoredBlobs);

	if( numStoredBlobs == 0)resetCounter();

}


//------------------------------------------
int blobTracker::addBlob(trackedBlob & blobIn){

		blobIn.id				= genID;
		blobIn.birthTime		= ofGetElapsedTimeMillis();
		blobIn.lastAliveTime	= blobIn.birthTime;
		blobIn.assigned		    = true;
		blobIn.activity		    = 20;
		blobIn.bNew				= true;

		storedBlobs.push_back(blobIn);
		genID++;

		return blobIn.id;
}

//------------------------------------------
bool blobTracker::matchTrackedBlob(trackedBlob & blobIn, int maxDist, float activityThresh, float cacheRate){

		float shortestDistance 	= 99999999;
		int tmpID				= -1;
		int which 				= -1;
		bool found 				= false;
		float speed 			= 0.0;
		ofxVec2f dist;

		for(int j = 0; j < storedBlobs.size(); j++){
			if( storedBlobs[j].assigned )continue;

			dist.set(blobIn.centroid.x - storedBlobs[j].centroid.x, blobIn.centroid.y - storedBlobs[j].centroid.y);
			float len = dist.length();

			if(len < maxDist && len < shortestDistance){
                speed = 0.0;

				shortestDistance = len;
				tmpID = storedBlobs[j].id;
				found = true;
				which = j;

                float activity = (2000.0 * len) / (storedBlobs[j].area + 1);

				//this is so we don't update speed if it is a tiny amount
				if( activity > activityThresh ) speed = activity - activityThresh;
				else speed = 0.0;
			}
		}

		if(found){
			//if we have found our trackedBlob
			//then we fist update the cached trackedBlob with the new stuff
			//it needs then we copy the cached trackedBlob to our current trackedBlob

			//this says we found a trackedBlob - so that it shouldn't be killed :)
			storedBlobs[which].assigned = true;
			storedBlobs[which].bNew		= false;

            //printf("matched to %i - speed is %f \n", which, speed);

			if(storedBlobs[which].activity < 0.001){
				storedBlobs[which].activity = 0.0;
			}
			else{
				//this should be contrable
				//and maybe based on frame rate
				storedBlobs[which].activity *= cacheRate;
			}

			storedBlobs[which].activity += speed;
			storedBlobs[which].activity = MIN(20, storedBlobs[which].activity);

			//okay because some data will need to be new if we are
			//not a cached trackedBlob - we just compute the activity and assign the id
			//so we know which previous trackedBlob we belong to.
			blobIn.activity			= storedBlobs[which].activity;
			blobIn.id				= storedBlobs[which].id;
			blobIn.assigned			= true;
			blobIn.bNew				= false;
			return true;
		}

		return false;
}
