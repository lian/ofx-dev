#include "pointRecorder.h"


//------------------------------------------------------------------
pointRecorder::pointRecorder(){
	maxNumPts = 500;
}

//------------------------------------------------------------------
void pointRecorder::draw() {
	
	//ofNoFill();
	ofFill();
	ofBeginShape();
	for (int i = 1; i < pts.size(); i++){
		//drawArrow(pts[i-1].x,pts[i-1].y,pts[i].x, pts[i].y);
	//	ofVertex(pts[i].x, pts[i].y);
	}
	ofEndShape(false);
	//ofNoFill();
	if(pts.size()>0)
	{
	drawArrow(pts[0].x,pts[0].y,pts[pts.size()-1].x, pts[pts.size()-1].y);
	}
}

//------------------------------------------------------------------
void pointRecorder::addPoint(ofPoint pt) {
	pts.push_back(pt);
	if (pts.size() > maxNumPts){
		pts.erase(pts.begin());
	}
}


//----------------------------------------

void pointRecorder::drawArrow(float oX, float oY, float nX, float nY)
{
	float w = ((nX - oX)+(nY - oY))/2;
	
	double angle = atan2 (nY - oY, nX - oX) + M_PI;
	double arrow_degrees_ = 0.5f;
	
	float xDist = ABS(nX-oX);
	float yDist = ABS(nY-oY);
	double len = sqrt( pow(xDist,2) + pow(yDist,2) );
	len-=len/10;
	
	
	double x1 = nX + len * cos(angle - arrow_degrees_);
	double y1 = nY + len * sin(angle - arrow_degrees_);
	double x2 = nX + len * cos(angle + arrow_degrees_);
	double y2 = nY + len * sin(angle + arrow_degrees_);
	
	
	
	//ofFill();
	glLineWidth(2);
	ofLine(oX,oY,nX,nY);
	
	glLineWidth(1);
	ofBeginShape(); //arrow
	ofVertex( nX, nY );
	ofVertex( x1, y1 );
	ofVertex( x2, y2 );
	ofVertex( nX, nY );
	ofEndShape();
}