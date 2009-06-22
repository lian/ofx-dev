/*
 *  fingerDetector.cpp
 *  openFrameworks
 *
 *  Created by Dani Quilez on 3/30/09.
 *  Copyright 2009 Mechanics_of_destruction. All rights reserved.
 *
 */

#include "fingerDetector.h"

fingerDetector::fingerDetector()
{
	//k is used for fingers and smk is used for hand detection
	k=35;
	smk=200;
	teta=0.f;
	handspos[0]=0;
	handspos[1]=0;
}
bool fingerDetector::findFingers (ofxCvBlob blob)
{
	ppico.clear();
	kpointcurv.clear();
	bfingerRuns.clear();
	
	for(int i=k; i<blob.nPts-k; i++)
	{
		
		//calculating angre between vectors
		v1.set(blob.pts[i].x-blob.pts[i-k].x,blob.pts[i].y-blob.pts[i-k].y);
		v2.set(blob.pts[i].x-blob.pts[i+k].x,blob.pts[i].y-blob.pts[i+k].y);
		
		v1D.set(blob.pts[i].x-blob.pts[i-k].x,blob.pts[i].y-blob.pts[i-k].y,0);
		v2D.set(blob.pts[i].x-blob.pts[i+k].x,blob.pts[i].y-blob.pts[i+k].y,0);
		
		vxv = v1D.cross(v2D);
		
		v1.normalize();
		v2.normalize();
		teta=v1.angle(v2);
		
		//control conditions 
		if(fabs(teta) < 40)
		{	//pik?
			if(vxv.z > 0)
			{
				bfingerRuns.push_back(true);
				//we put the select poins into ppico vector
				ppico.push_back(blob.pts[i]);
				kpointcurv.push_back(teta);
			}
		}
	}
	if(ppico.size()>0)
	{
		return true;
	}
	else 
	{
		return false;
	}
	
}
bool fingerDetector::findHands(ofxCvBlob smblob)
{
	smppico.clear();
	smkpointcurv.clear();
	lhand.clear();
	rhand.clear();
	
	hcentroid=smblob.centroid;

	for(int i=smk; i<smblob.nPts-smk; i++)
	{
		
		v1.set(smblob.pts[i].x-smblob.pts[i-smk].x,smblob.pts[i].y-smblob.pts[i-smk].y);
		v2.set(smblob.pts[i].x-smblob.pts[i+smk].x,smblob.pts[i].y-smblob.pts[i+smk].y);
		
		v1D.set(smblob.pts[i].x-smblob.pts[i-smk].x,smblob.pts[i].y-smblob.pts[i-smk].y,0);
		v2D.set(smblob.pts[i].x-smblob.pts[i+smk].x,smblob.pts[i].y-smblob.pts[i+smk].y,0);
		
		vxv = v1D.cross(v2D);
		
		v1.normalize();
		v2.normalize();
		
		teta=v1.angle(v2);
		
		if(fabs(teta) < 30)
		{	//pik?
			if(vxv.z > 0)
			{
				smppico.push_back(smblob.pts[i]);
				smkpointcurv.push_back(teta);
			}
		}
	}
	for(int i=0; i<smppico.size();i++)
	{
		if(i==0)
		{
			lhand.push_back(smppico[i]);
		}
		else
		{
			aux1.set(smppico[i].x-smppico[0].x,smppico[i].y-smppico[0].y);
			dlh=aux1.length();
		
			//we detect left and right hand and 
		
			if(dlh<100)
			{
				lhand.push_back(smppico[i]);
			}
			if(dlh>100)
			{
				rhand.push_back(smppico[i]);
			}
		}
	}
	//try to find for each hand the point wich is farder to the centroid of the Blob
	if(lhand.size()>0)
	{
		
		aux1.set(lhand[0].x-hcentroid.x,lhand[0].y-hcentroid.y);
		lhd=aux1.length();
		max=lhd;
		handspos[0]=0;
		for(int i=1; i<lhand.size(); i++)
		{
			aux1.set(lhand[i].x-hcentroid.x,lhand[i].y-hcentroid.y);
			lhd=aux1.length();
			if(lhd>max)
			{
				max=lhd;
				handspos[0]=i;
			}
		}
	}
	if(rhand.size()>0)
	{
		aux1.set(rhand[0].x-hcentroid.x,rhand[0].y-hcentroid.y);
		lhd=aux1.length();
		max=lhd;
		handspos[1]=0;
		for(int i=1; i<rhand.size(); i++)
		{
			aux1.set(rhand[i].x-hcentroid.x,rhand[i].y-hcentroid.y);
			lhd=aux1.length();
			if(lhd>max)
			{
				max=lhd;
				handspos[1]=i;
			}
		}
	}
	if(rhand.size()>0 || lhand.size()>0) return true;
	return false;
	//Positions of hands are in (lhand[handspos[0]].x, y+lhand[handspos[0]].y) for left hand and (rhand[handspos[1]].x, y+rhand[handspos[1]].y) for right hand
}
void fingerDetector::draw(float x, float y)
{
	for(int i=0; i<ppico.size(); i++)
	{
		ofEnableAlphaBlending(); 
		ofFill();
		 ofSetColor(255,0,0,20);
		 ofCircle(x+ppico[i].x, y+ppico[i].y, 10);
	}
}
void fingerDetector::drawhands(float x, float y)
{
	ofFill();
	//control condition
	if(lhand.size()>0)
	{
		ofSetColor(255,255,0);
		ofCircle(x+lhand[handspos[0]].x, y+lhand[handspos[0]].y, 50);
	}
	if(rhand.size()>0)
	{
		ofSetColor(0,0,255);
		ofCircle(x+rhand[handspos[1]].x, y+rhand[handspos[1]].y, 50);
	}
}
