#ifndef _LASER_TRACKING_H
#define _LASER_TRACKING_H

#include "ofMain.h"
#include "ofAddons.h"

#include "laserUtils.h"

class laserTracking{

	public:
	
		laserTracking();

		void calcColorRange(float hue, float hueThresh, float sat, float satThresh, float value);
		void drawColorRange(float x, float y, float w, float h);

		int r0Min, r0Max, g0Min, g0Max, b0Min, b0Max, r1Min, r1Max, g1Min, g1Max, b1Min, b1Max;
};

#endif
