#ifndef _LIGHTCOLLECTOR_H
#define _LIGHTCOLLECTOR_H

#include <cv.h>

class LightMap;

/*!
 * \ingroup photocalib
 * Collects lighting clues. This class apply an homography to a planar mesh and
 * average colors within triangles. The LightMap class can use these measures
 * to estimate a radiance map.
 */
class LightCollector {
public:
	LightCollector();
	LightCollector(const LightCollector &lc);
	~LightCollector();
	const LightCollector &operator=(LightCollector &lc);
	void copy(const LightCollector &lc);

	//! Generate a regular grid given its 4 corners.
	bool genGrid(float corners[4][2], int nx, int ny);

	void averageImage(IplImage *im, CvMat *_homography);

	int serializeSize();
	void serialize(char *buffer);
	void load(const char *buffer, int size);
	void invalidate();

	// for debugging
	void drawGrid(IplImage *im, CvMat *_homography);
	void drawAvg(IplImage *im);

	CvMat *worldRT;

	bool cmpWithRef(const LightCollector &ref, float *val, const float *scale=0, const float *shift=0);

	//friend LightMap;
//private:
	float *avg;
	CvMat *vertices, *transformed;
	int *triangles;
	int nbTri;
	int nx, ny;
	int avgChannels;
	int nbPix;
};

#endif
