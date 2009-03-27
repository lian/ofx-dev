#ifndef _RENDER_MANAGER_H
#define _RENDER_MANAGER_H

#include "ofxXmlSettings.h"
#include "ofTextureAdv.h"

class renderManager {


    public:

        renderManager();
        void allocateForNScreens(int numScreens, int renderWidth, int renderHeight);

        void drawInputDiagnostically(float x, float y, float w, float h); // can't specify abs dimensions, since might be diff apsect ratio...
        void drawOutputDiagnostically(float x, float y, float w, float h); // can't specify abs dimensions, since might be diff apsect ratio...

        void drawScreen(int nScreen);

        void startOffscreenDraw();
        void endOffscreenDraw();

        bool mouseSelectInputPoint(ofRectangle drawRect, ofPoint mousePoint, float clickRadius = 15);
        bool mouseDragInputPoint(ofRectangle drawRect, ofPoint mousePoint);

        bool mouseSelectOutputPoint(ofRectangle drawRect, ofPoint mousePoint, float clickRadius = 15);
        bool mouseDragOutputPoint(ofRectangle drawRect, ofPoint mousePoint);

        void resetCoordinates();

        void reloadFromXml();
        void loadFromXml(string xmlFileName);
        void saveToXml();
        void saveToXml(string xmlFileName);


        int    activeScreenIn;
        int    activePointIn;

        int    activeScreenOut;
        int    activePointOut;

        float width, height;
        float screenWidth, screenHeight;
        int nScreens;

        bool bInputSelected;

        ofPoint ** outputPositions;
        ofPoint ** inputPositions;

        string xmlFile;

        ofTextureAdv myOffscreenTexture;
        ofxXmlSettings xml;
};

#endif

