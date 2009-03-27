#ifndef _IMAGE_TEXTURE_ADV_H_
#define _IMAGE_TEXTURE_ADV_H_

#include "ofMain.h"
#include "ofFBOTexture.h"


#define GRID_X 12
#define GRID_Y 8



class ofTextureAdv : public ofFBOTexture {

	public :
		ofTextureAdv();
		~ofTextureAdv();
		void allocate(int w, int h, int internalGlDataType);
		void clear();
		void loadData(unsigned char * data, int w, int h, int glDataType);
		void setPoint(int which, float x, float y);
		void setPoints(ofPoint pts[4]);
		void setPoints(ofPoint inputPts[4], ofPoint outputPts[4]);
		void draw();
        void draw(float x, float y) { ofTexture::draw(x,y); };
        void draw(float x, float y, float w, float h) { ofTexture::draw(x,y,w,h); };
        void allocate(int w, int h, bool clear){ ofFBOTexture::allocate(w,h, clear);   };


		int width, height;

	protected:

		void updatePoints();

		ofPoint quad[4];
		ofPoint utQuad[4];
		ofPoint * grid;
		ofPoint * coor;


};

#endif
