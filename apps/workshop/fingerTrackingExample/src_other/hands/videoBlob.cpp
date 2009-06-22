#include "videoBlob.h"


//---------------------------------------------------------------------------------
void videoBlob::set(ofxCvBlob myBlob, ofxCvColorImage myImage, ofxCvGrayscaleImage myMask){

	memcpy(&blob, &myBlob, sizeof(ofxCvBlob));

	// now, let's get the data in, 
	int w = blob.boundingRect.width;
	int h = blob.boundingRect.height;
	int imgw = myImage.width;
	int imgh = myImage.height;
	int imgx = blob.boundingRect.x;
	int imgy = blob.boundingRect.y;

	unsigned char * blobRGBA = new unsigned char [ w * h * 4 ];
	unsigned char * colorPixels 	= myImage.getPixels();
	unsigned char * grayPixels 		= myMask.getPixels();
	
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			int posTex = (j * w + i)*4;
			int posGray = ((j+imgy)*imgw + (i + imgx));
			int posCol = posGray * 3;
			blobRGBA[posTex + 0] = colorPixels[posCol + 0];
			blobRGBA[posTex + 1] = colorPixels[posCol + 1];
			blobRGBA[posTex + 2] = colorPixels[posCol + 2];
			blobRGBA[posTex + 3] = grayPixels[posGray];
		}
	}
	
//	myTexture.clear();
//	myTexture.allocate(w,h,GL_RGBA);
	
	unsigned char * black = new unsigned char [ofNextPow2(w) * ofNextPow2(h) * 4];
	memset(black, 0, ofNextPow2(w) * ofNextPow2(h) * 4);
//	myTexture.loadData(black, ofNextPow2(w), ofNextPow2(h), GL_RGBA);
//	myTexture.loadData(blobRGBA, w, h, GL_RGBA);
	
	delete black;
	delete blobRGBA;
	
	pos.x = blob.centroid.x;
	pos.y = blob.centroid.y;
	scale = 1;
	angle = 0;
	
}

//------------------------------------------------------------
void videoBlob::update(){
	
	// ---------------------------------- (a)
	// compute non-translated points
	int w = blob.boundingRect.width;
	int h = blob.boundingRect.height;
	int x = blob.boundingRect.x;
	int y = blob.boundingRect.y;
	
	texPts[0].x = x;
	texPts[0].y = y;
	texPts[1].x = x+w;
	texPts[1].y = y;
	texPts[2].x = x + w;
	texPts[2].y = y + h;
	texPts[3].x = x;
	texPts[3].y = y+h;
	
	nPts = blob.nPts;
	for (int i = 0; i < nPts; i++){
		pts[i] = blob.pts[i];
	}
	
	// ---------------------------------- (b)
	// 0,0 position is the rotation point
	for (int i = 0; i < 4; i++){
		texPts[i].x -= blob.centroid.x;
		texPts[i].y -= blob.centroid.y;
	}
	
	for (int i = 0; i < nPts; i++){
		pts[i].x -= blob.centroid.x;
		pts[i].y -= blob.centroid.y;
	}
	
	
	// ---------------------------------- (c)
	// scale
	for (int i = 0; i < 4; i++){
		texPts[i].x *= scale;
		texPts[i].y *= scale;
	}
	
	for (int i = 0; i < nPts; i++){
		pts[i].x *= scale;
		pts[i].y *= scale;
	}
	
	// ---------------------------------- (d)
	// rotation by angle
	float sinangle = sin(angle);
	float cosangle = cos(angle);
	for (int i = 0; i < 4; i++){
		float oldx = texPts[i].x;
		float oldy = texPts[i].y;
		texPts[i].x= oldx*cosangle-oldy*sinangle;
 		texPts[i].y= oldx*sinangle+oldy*cosangle;
	}
	
	for (int i = 0; i < nPts; i++){
		float oldx = pts[i].x;
		float oldy = pts[i].y;
		pts[i].x= oldx*cosangle-oldy*sinangle;
 		pts[i].y= oldx*sinangle+oldy*cosangle;
	}
	
	// ---------------------------------- (e)
	// move back to pos
	for (int i = 0; i < 4; i++){
		texPts[i].x += pos.x;
		texPts[i].y += pos.y;
	}
	
	for (int i = 0; i < nPts; i++){
		pts[i].x += pos.x;
		pts[i].y += pos.y;
	}


}

//---------------------------------------------------------------------------------
void videoBlob::draw(){
	
	ofEnableAlphaBlending();
	
	glPushMatrix();
		glScalef(3,3,1);
//		(myTexture).draw(texPts);
	glPopMatrix();
	ofDisableAlphaBlending();
	
}
		
//---------------------------------------------------------------------------------	
void videoBlob::drawDiagnostically(){
	glPushMatrix();
	glScalef(3,3,1);
	for (int i = 0; i < nPts; i+=2){
		float x = pts[i].x;	
		float y = pts[i].y;
		ofCircle(x,y,1.33);	
	}
	ofCircle(pos.x, pos.y, 1.33);
	glPopMatrix();	
}

//---------------------------------------------------------------------------------
// useful for checking for occlusion, etc with another image
// (via image arithmatic. &= etc)
void videoBlob::draw(ofxCvGrayscaleImage &mom, int color){
	
	if (nPts > 0 ){
	   CvPoint * ptsTemp = new CvPoint[nPts];
	   for (int i = 0; i < nPts ; i++){
	           ptsTemp[i].x = pts[i].x;
	           ptsTemp[i].y = pts[i].y;
	   }
	   cvFillPoly( mom.getCvImage(), &ptsTemp, &(nPts),1,
	           CV_RGB(color,color,color));
	   delete ptsTemp;

	}
}


//---------------------------------------------------------------------------------	
void videoBlob::drawOutline(){
	glPushMatrix();
	glScalef(3,3,1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < nPts; i+=2){
		float x = pts[i].x;	
		float y = pts[i].y;
		glVertex2f(x,y);
	}
	glEnd();
	glPopMatrix();	
}

//---------------------------------------------------------------------------------
// useful for triggers behaviors, dragging, etc
bool videoBlob::pointInsideMe(float x, float y){
	// code via Randolph Franklin...
	int i, j, c = 0;
	for (i = 0, j = nPts-1; i < nPts; j = i++) {
	if ((((pts[i].y <= y) && (y < pts[j].y)) ||
	     ((pts[j].y <= y) && (y < pts[i].y))) &&
	    (x < (pts[j].x - pts[i].x) * (y - pts[i].y) / (pts[j].y - pts[i].y) + pts[i].x))
	  c = !c;
	}
	return (bool) c;
}