
// here is where you paste any "add me to ofAddons.h" code
// for the addon you want to add
// you will also need to follow the other steps
// like adding the library linking paths, etc,etc.

//-------------------------------------------- openCV
#ifdef OF_ADDON_USING_OFXOPENCV
	#include "ofxCvMain.h"
#endif

//-------------------------------------------- obj loader
#ifdef OF_ADDON_USING_OFXOBJLOADER
	#include "ofxObjLoader.h"
#endif

//-------------------------------------------- dir list
#ifdef OF_ADDON_USING_OFXDIRLIST
	#include "ofxDirList.h"
#endif

//-------------------------------------------- vector math
#ifdef OF_ADDON_USING_OFXVECTORMATH
	#include "ofxVectorMath.h"
#endif

//-------------------------------------------- network
#ifdef OF_ADDON_USING_OFXNETWORK
	#include "ofxNetwork.h"
#endif

//-------------------------------------------- vector graphics
#ifdef OF_ADDON_USING_OFXVECTORGRAPHICS
	#include "ofxVectorGraphics.h"
#endif

//-------------------------------------------- OSC
#ifdef OF_ADDON_USING_OFXOSC
	#include "ofxOsc.h"
#endif

//-------------------------------------------- ofthread
#ifdef OF_ADDON_USING_OFXTHREAD
	#include "ofxThread.h"
#endif

//-------------------------------------------- ofXML
#ifdef OF_ADDON_USING_OFXXMLSETTINGS
	#include "ofxXmlSettings.h"
#endif
