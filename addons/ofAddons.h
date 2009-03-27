#warning ______________________________________________________________________________
#warning !!! ofAddons.h is deprecated - from OF 007 and on this file will NOT EXIST !!!
#warning To see the new usage for using addons in OF please see www.openframeworks.cc/006-Important-Notes
#warning ______________________________________________________________________________

// these #define are kept around to make sure that old code doesn't break, but from 0.07 we will be using a non #define system for addons.
// see:  http://www.openframeworks.cc/006-Important-Notes

//-------------------------------------------- openCV
#ifdef OF_ADDON_USING_OFXOPENCV
	#include "ofxOpenCv.h"
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

//-------------------------------------------- ofShader
#ifdef OF_ADDON_USING_OFSHADER
	#include "ofShader.h"
#endif

//-------------------------------------------- ofTodd
#ifdef OF_ADDON_USING_OFXTODD
	#include "ofTodd.h"
#endif

//-------------------------------------------- ofxTuio
#ifdef OF_ADDON_USING_OFXMOREUTILS
	#include "ofMoreUtils.h"
#endif

//-------------------------------------------- ofxGui
#ifdef OF_ADDON_USING_OFXGUI
	#include "ofxGui.h"
#endif

//-------------------------------------------- ofxSimpleGui
#ifdef OF_ADDON_USING_OFXSIMPLEGUI
	#include "ofxSimpleGui.h"
#endif

//-------------------------------------------- ofxMSAPhysics
#ifdef OF_ADDON_USING_OFXMSAPHYSICS
	#include "ofxMSAPhysics.h"
#endif

//-------------------------------------------- ofxMSAShape3D
#ifdef OF_ADDON_USING_OFXMSASHAPE3D
	#include "MSAShape3D.h"
#endif

//-------------------------------------------- ofxMSASpline
#ifdef OF_ADDON_USING_OFXMSASPLINE
	#include "ofxMSASpline.h"
#endif

//-------------------------------------------- ofxQRCodes
#ifdef OF_ADDON_USING_OFXQRCODES
	#include "ofxQRCodes.h"
#endif

//-------------------------------------------- ofxTuio
#ifdef OF_ADDON_USING_OFXTUIO
	#include "ofxTuio.h"
#endif

//-------------------------------------------- ofxFiducialFinder
#ifdef OF_ADDON_USING_OFXFIDUCIALFINDER
	#include "ofxFidMain.h"
#endif

//-------------------------------------------- ofxCvHaarFinder
#ifdef OF_ADDON_USING_OFXCVHAARFINDER
	#include "ofxCvHaarFinder.h"
#endif

//-------------------------------------------- ofxBox2D
#ifdef OF_ADDON_USING_OFXBOX2D
	#include "ofxBox2D.h"
#endif

//-------------------------------------------- ofxBazAR
#ifdef OF_ADDON_USING_OFXBAZAR
	#include "ofxBazAR.h"
#endif

//-------------------------------------------- ofxFreeFrame
#ifdef OF_ADDON_USING_OFXFREEFRAME
	#include "ofxFreeFrame.h"
#endif
