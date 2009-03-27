

#include "renderManager.h"

//---------------------------------------------------------------------------
renderManager::renderManager(){
    bInputSelected = false;

    activeScreenIn = -1;
    activePointIn  = -1;

    activeScreenOut = -1;
    activePointOut  = -1;

    xmlFile = "";

    nScreens = 0;
}

//---------------------------------------------------------------------------
void renderManager::allocateForNScreens(int numScreens, int renderWidth, int renderHeight){
    if( numScreens < 1){
        printf("renderManager::allocateForNScreens - you need at lease one screen!\n");
        return;
    }
    width   = renderWidth;
    height  = renderHeight;

    screenWidth  = (float)width / (float)numScreens;
    screenHeight = height;

    myOffscreenTexture.allocate(renderWidth, renderHeight, false);

    nScreens            = numScreens;
    outputPositions     = new ofPoint*[nScreens];
    inputPositions      = new ofPoint*[nScreens];

    float w_d_3 = (float)width / (float)nScreens;
    float inner_d_3 = 1.0f / (float)nScreens;
    for (int i = 0; i < nScreens; i++){

        inputPositions[i]  = new ofPoint[4];
        outputPositions[i] = new ofPoint[4];

        //-----------------------------------------
        outputPositions[i][0].set(w_d_3*(i),0,0);
        outputPositions[i][1].set(w_d_3*(i+1),0,0);
        outputPositions[i][2].set(w_d_3*(i+1),height,0);
        outputPositions[i][3].set(w_d_3*(i),height,0);

        inputPositions[i][0].set(inner_d_3*(i),0,0);
        inputPositions[i][1].set(inner_d_3*(i+1),0,0);
        inputPositions[i][2].set(inner_d_3*(i+1),1,0);
        inputPositions[i][3].set(inner_d_3*(i),1,0);

//
//        printf("input is \n");
//        printf("(%f %f)          ", inputPositions[i][0].x, inputPositions[i][0].y);
//        printf("(%f %f)\n\n\n\n\n", inputPositions[i][1].x, inputPositions[i][1].y);
//        printf("(%f %f)          ", inputPositions[i][2].x, inputPositions[i][2].y);
//        printf("(%f %f)\n", inputPositions[i][3].x, inputPositions[i][3].y);
//
//        printf("\noutput is \n");
//        printf("(%f %f)          ", outputPositions[i][0].x, outputPositions[i][0].y);
//        printf("(%f %f)\n\n\n\n\n", inputPositions[i][1].x, outputPositions[i][1].y);
//        printf("(%f %f)          ", outputPositions[i][2].x, outputPositions[i][2].y);
//        printf("(%f %f)\n", outputPositions[i][3].x, outputPositions[i][3].y);
    }
}

//---------------------------------------------------------------------------
void renderManager::startOffscreenDraw(){
    if( nScreens <= 0 ) return;

    myOffscreenTexture.swapIn();
    myOffscreenTexture.setupScreenForMe();
}

//---------------------------------------------------------------------------
void renderManager::endOffscreenDraw(){
    if( nScreens <= 0 ) return;

    myOffscreenTexture.swapOut();
    myOffscreenTexture.setupScreenForThem();
}

//---------------------------------------------------------------------------
void renderManager::drawInputDiagnostically(float x, float y, float w, float h){
   if( nScreens <= 0 ) return;

    myOffscreenTexture.draw(x, y, w,h);

    for (int i = 0; i < nScreens; i++){
        ofSetColor(0x33DD44);
        ofNoFill();
        ofBeginShape();
        for (int j = 0; j < 4; j++){
            ofVertex( inputPositions[i][j].x * w + x, inputPositions[i][j].y * h + y);
        }
        ofEndShape(true);

        ofFill();
        ofSetColor(0x3344FF);
        for (int j = 0; j < 4; j++){
            ofCircle(  inputPositions[i][j].x * w + x, inputPositions[i][j].y * h + y,3);
        }
    }

}

//---------------------------------------------------------------------------
void renderManager::drawOutputDiagnostically(float x, float y, float w, float h){
    if( nScreens <= 0 ) return;

    glPushMatrix();
    glTranslatef(x, y, 0);

    ofNoFill();
        ofSetColor(0x000000);
        ofRect(0, 0, w, h);
    ofFill();

    for (int i = 0; i < nScreens; i++){

        glPushMatrix();

            ofSetColor(255, 255, 255, 255);
            float wScale = ( w / screenWidth ) / nScreens;
            float hScale = h / screenHeight;
            glScalef(wScale, hScale, 1);
            drawScreen(i);

            ofSetColor(0x4444CC);
            ofNoFill();
            ofBeginShape();
            for (int j = 0; j < 4; j++){
                ofVertex( outputPositions[i][j].x  , outputPositions[i][j].y );
            }
            ofEndShape(true);

            ofFill();
            ofSetColor(0xFF3333);
            for (int j = 0; j < 4; j++){
                ofCircle(  outputPositions[i][j].x , outputPositions[i][j].y, 5 );
            }

        glPopMatrix();
    }

    glPopMatrix();

}

//---------------------------------------------------------------------------
void renderManager::drawScreen(int nScreen){
    if( nScreens <= 0 ) return;

    myOffscreenTexture.setPoints(inputPositions[nScreen], outputPositions[nScreen]);
    myOffscreenTexture.draw();
}


//---------------------------------------------------------------------------
void renderManager::resetCoordinates(){
    if( nScreens <= 0)return;

    float inner_d_3 = 1.0f / (float)nScreens;
    for (int i = 0; i < nScreens; i++){

        //-----------------------------------------
        outputPositions[i][0].set(screenWidth*(i),0,0);
        outputPositions[i][1].set(screenWidth*(i+1),0,0);
        outputPositions[i][2].set(screenWidth*(i+1),height,0);
        outputPositions[i][3].set(screenWidth*(i),height,0);

        inputPositions[i][0].set(inner_d_3*(i),0,0);
        inputPositions[i][1].set(inner_d_3*(i+1),0,0);
        inputPositions[i][2].set(inner_d_3*(i+1),1,0);
        inputPositions[i][3].set(inner_d_3*(i),1,0);
    }
}

//---------------------------------------------------------------------------
void renderManager::loadFromXml(string xmlFileName){
    xmlFile = xmlFileName;
    xml.loadFile(xmlFile);
    reloadFromXml();
}

//---------------------------------------------------------------------------
void renderManager::reloadFromXml(){
    if(xmlFile == "")return;

    for(int i = 0; i < nScreens; i++){

        float inner_d_3 = 1.0 / nScreens;

        if( xml.pushTag("QUAD_IN_"+ofToString(i)) ){

                float inner_d_3 = 1.0 / nScreens;

                inputPositions[i][0].x  = xml.getValue("pt0:x", inner_d_3*(i));
                inputPositions[i][0].y  = xml.getValue("pt0:y", 0.0f);

                inputPositions[i][1].x  = xml.getValue("pt1:x", inner_d_3*(i+1));
                inputPositions[i][1].y  = xml.getValue("pt1:y", 0.0f);

                inputPositions[i][2].x  = xml.getValue("pt2:x", inner_d_3*(i+1));
                inputPositions[i][2].y  = xml.getValue("pt2:y", 1.0f);

                inputPositions[i][3].x  = xml.getValue("pt3:x", inner_d_3*(i));
                inputPositions[i][3].y  = xml.getValue("pt3:y", 1.0f);

            xml.popTag();
        }
        if( xml.pushTag("QUAD_OUT_"+ofToString(i)) ){

                outputPositions[i][0].x  = xml.getValue("pt0:x", screenWidth*(i));
                outputPositions[i][0].y  = xml.getValue("pt0:y", 0);

                outputPositions[i][1].x  = xml.getValue("pt1:x", screenWidth*(i+1));
                outputPositions[i][1].y  = xml.getValue("pt1:y", 0);

                outputPositions[i][2].x  = xml.getValue("pt2:x", screenWidth*(i+1));
                outputPositions[i][2].y  = xml.getValue("pt2:y", height);

                outputPositions[i][3].x  = xml.getValue("pt3:x", screenWidth*(i));
                outputPositions[i][3].y  = xml.getValue("pt3:y", height);

            xml.popTag();
        }

    }
}


//---------------------------------------------------------------------------
void renderManager::saveToXml(){
    if(xmlFile != ""){
        saveToXml(xmlFile);
    }
}


void renderManager::saveToXml(string xmlFileName){
    if(xmlFileName == "")return;

    //clear out the file
    xml.clear();

    for(int i = 0; i < nScreens; i++){

        float inner_d_3 = 1.0 / nScreens;

        xml.addTag("QUAD_IN_"+ofToString(i) );
        if( xml.pushTag("QUAD_IN_"+ofToString(i)) ){

                float inner_d_3 = 1.0 / nScreens;

                xml.setValue("pt0:x", inputPositions[i][0].x);
                xml.setValue("pt0:y", inputPositions[i][0].y);

                xml.setValue("pt1:x", inputPositions[i][1].x);
                xml.setValue("pt1:y", inputPositions[i][1].y);

                xml.setValue("pt2:x", inputPositions[i][2].x);
                xml.setValue("pt2:y", inputPositions[i][2].y);

                xml.setValue("pt3:x",  inputPositions[i][3].x);
                xml.setValue("pt3:y",  inputPositions[i][3].y);

            xml.popTag();
        }

        xml.addTag("QUAD_OUT_"+ofToString(i) );
        if( xml.pushTag("QUAD_OUT_"+ofToString(i)) ){

                xml.setValue("pt0:x", outputPositions[i][0].x);
                xml.setValue("pt0:y", outputPositions[i][0].y);

                xml.setValue("pt1:x", outputPositions[i][1].x);
                xml.setValue("pt1:y", outputPositions[i][1].y);

                xml.setValue("pt2:x", outputPositions[i][2].x);
                xml.setValue("pt2:y", outputPositions[i][2].y);

                xml.setValue("pt3:x", outputPositions[i][3].x);
                xml.setValue("pt3:y", outputPositions[i][3].y);

            xml.popTag();
        }
    }

    xml.saveFile(xmlFileName);
}

//---------------------------------------------------------------------------
bool renderManager::mouseSelectInputPoint(ofRectangle drawRect, ofPoint mousePoint, float clickRadius){
    if( nScreens <= 0 ) return false;

    //this is not the best way
    activeScreenIn      = -1;
    activePointIn       = -1;
    activeScreenOut     = -1;
    activePointOut      = -1;

    float smallestDist  = 999999;

    bool bFound = false;

    for (int i = 0; i < nScreens; i++){
        for (int j = 0; j < 4; j++){
            ofPoint inputPt;
            inputPt.x = inputPositions[i][j].x * drawRect.width + drawRect.x;
            inputPt.y = inputPositions[i][j].y * drawRect.height + drawRect.y;
            inputPt.z = 0;
            float len = sqrt( (inputPt.x - mousePoint.x) * (inputPt.x - mousePoint.x) +
                              (inputPt.y - mousePoint.y) * (inputPt.y - mousePoint.y));
            if (len < clickRadius && len < smallestDist){
                activeScreenIn = i;
                activePointIn  = j;
                smallestDist = len;

                bFound = true;
            }
        }
    }

    return bFound;
}

//---------------------------------------------------------------------------
bool renderManager::mouseDragInputPoint(ofRectangle drawRect, ofPoint mousePoint){
    if( nScreens <= 0 ) return false;

    if (activeScreenIn > -1 && activePointIn > -1){

        float xpct = (mousePoint.x - drawRect.x) / drawRect.width;
        float ypct = (mousePoint.y - drawRect.y) / drawRect.height;
        inputPositions[activeScreenIn][activePointIn].x = xpct;
        inputPositions[activeScreenIn][activePointIn].y = ypct;

        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
bool renderManager::mouseSelectOutputPoint(ofRectangle drawRect, ofPoint mousePoint, float clickRadius){
    if( nScreens <= 0 ) return false;

    //this is not the best way
    activeScreenIn      = -1;
    activePointIn       = -1;
    activeScreenOut     = -1;
    activePointOut      = -1;

    float smallestDist  = 999999;

    bool bFound = false;

    for (int i = 0; i < nScreens; i++){
        for (int j = 0; j < 4; j++){
            ofPoint outputPt;

            //lets get the screen width and height at our scale
            outputPt.x = outputPositions[i][j].x;// * drawRect.width) + drawRect.x;
            outputPt.y = outputPositions[i][j].y;// * drawRect.height) + drawRect.y;
            outputPt.z = 0;

            outputPt.x *= ( (float)drawRect.width  / screenWidth )/nScreens;
            outputPt.y *= (float)drawRect.height / screenHeight;

            outputPt.x += drawRect.x;
            outputPt.y += drawRect.y;

            //printf("outputPt  is %f %f \n", outputPt.x, outputPt.y);

            float len = sqrt( (outputPt.x - mousePoint.x) * (outputPt.x - mousePoint.x) +
                              (outputPt.y - mousePoint.y) * (outputPt.y - mousePoint.y));
            if (len < clickRadius && len < smallestDist){
                activeScreenOut = i;
                activePointOut = j;
                smallestDist = len;

                //printf("setting point %i of screen %i \n", activePointOut, activeScreenOut);

                bFound = true;
            }
        }
    }
    return bFound;

}

//---------------------------------------------------------------------------
bool renderManager::mouseDragOutputPoint(ofRectangle drawRect, ofPoint mousePoint){
    if( nScreens <= 0 ) return false;

    if (activeScreenOut > -1 && activePointOut > -1){

        float xpct = (mousePoint.x - drawRect.x) / (drawRect.width / nScreens);
        float ypct = (mousePoint.y - drawRect.y) / drawRect.height;

        float outPtX = xpct * screenWidth;
        float outPtY = ypct * screenHeight;

        outputPositions[activeScreenOut][activePointOut].x = outPtX;
        outputPositions[activeScreenOut][activePointOut].y = outPtY;

        //printf("point - %i  of screen %i setting output position to %f %f \n",activePointOut,  activeScreenOut, outputPositions[activeScreenOut][activePointOut].x, outputPositions[activeScreenOut][activePointOut].y);

        return true;
    }
    return false;
}
