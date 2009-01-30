#include <vector>
#include <math.h>
#include "lightcollector.h"
#include "../../starter/geometry/homography.h"

LightCollector::LightCollector() {
	vertices=0;
	transformed=0;
	triangles=0;
	nbTri=0;
	avg=0;
	nx=ny=0;
	avgChannels=0;
	worldRT=0;
}

LightCollector::LightCollector(const LightCollector &lc)
{
	if (lc.vertices) vertices = cvCloneMat(lc.vertices);
	else vertices=0;
	if (lc.transformed) transformed = cvCloneMat(lc.transformed);
	else transformed=0;
	nbTri = lc.nbTri;
	nx = lc.nx;
	ny = lc.ny;
	if (lc.triangles) {
		triangles = new int[nbTri*3];
		memcpy(triangles, lc.triangles, sizeof(int)*nbTri*3);
	} else triangles=0;
	avgChannels = lc.avgChannels;
	avg=0;
	if (lc.worldRT) cvIncRefData(lc.worldRT);
	worldRT = lc.worldRT;
	//assert(lc.avg==0);
}

const LightCollector &LightCollector::operator =(LightCollector &lc)
{
	vertices=0;
	transformed=0;
	triangles=0;
	nbTri = lc.nbTri;
	nx = lc.nx;
	ny = lc.ny;
	avgChannels = lc.avgChannels;
	avg = lc.avg;
	lc.avg=0;
	if (lc.worldRT) cvIncRefData(lc.worldRT);
	if (worldRT) cvDecRefData(worldRT);
	worldRT = lc.worldRT;
	return *this;
}

void LightCollector::copy(const LightCollector &lc)
{
	if (lc.vertices) vertices = cvCloneMat(lc.vertices);
	else vertices=0;
	if (lc.transformed) transformed = cvCloneMat(lc.transformed);
	else transformed=0;
	nbTri = lc.nbTri;
	nx = lc.nx;
	ny = lc.ny;
	avgChannels = lc.avgChannels;
	if (lc.triangles) {
		triangles = new int[nbTri*3];
		memcpy(triangles, lc.triangles, sizeof(int)*nbTri*3);
	} else 
		triangles=0;
	if (lc.avg) {
		avg = new float[avgChannels*nbTri];
		memcpy(avg, lc.avg, sizeof(float)*avgChannels*nbTri);
	} else 
		avg=0;
	if (lc.worldRT) worldRT=cvCloneMat(lc.worldRT);
	else worldRT = 0;
}

LightCollector::~LightCollector() {
	if (avg) delete[] avg;
	if (vertices) cvReleaseMat(&vertices);
	if (transformed) cvReleaseMat(&transformed);
	if (worldRT) cvDecRefData(&worldRT);
}

// from tri.cpp
int stat_triangle(IplImage *im, int pts[3][2], float avg[3]);

/*! Transform the grid with given homograhy and average colors over
 * triangles.
 */
void LightCollector::averageImage(IplImage *im, CvMat *_homography)
{
	if (avgChannels != im->nChannels) {
		if (avgChannels < im->nChannels) { 
			delete[] avg;
			avg = 0;
		}
		avgChannels = im->nChannels;
	}
	if (!avg) avg = new float[avgChannels*nbTri];
	
	// apply the homography to every mesh vertex
	if (_homography)
		cvMatMul(_homography, vertices, transformed);
	else
		cvCopy(vertices, transformed);
	CvMat r1,r2,r3;
	cvGetRow(transformed, &r1, 0);
	cvGetRow(transformed, &r2, 1);
	cvGetRow(transformed, &r3, 2);
	cvDiv(&r1,&r3,&r1);
	cvDiv(&r2,&r3,&r2);
	
	nbPix=0;
	for (int t=0; t<nbTri;t++) {
		int pts[3][2];
		for (int i=0; i<3; i++) {
			assert(triangles[t*3+i] < transformed->cols);
			pts[i][0] = cvRound(CV_MAT_ELEM(*transformed, float, 0, triangles[t*3+i]));
			pts[i][1] = cvRound(CV_MAT_ELEM(*transformed, float, 1, triangles[t*3+i]));
		}
		nbPix+=stat_triangle(im, pts, avg+t*avgChannels);
	}
}

bool LightCollector::genGrid(float corners[4][2], int nx, int ny)
{
	if (nx<1 || ny<1) return false;
	if (avg) delete[] avg; avg=0;
	if (vertices) cvReleaseMat(&vertices);
	if (transformed) cvReleaseMat(&transformed);

	// generate vertices
	vertices = cvCreateMat(3, (nx+1)*(ny+1), CV_32FC1);
	transformed = cvCreateMat(3, vertices->cols, CV_32FC1);
	for (int y=0; y<(ny+1); ++y)
		for (int x=0; x<(nx+1); ++x) {
			CV_MAT_ELEM(*vertices, float, 0, y*(nx+1)+x) = float(x)/float(nx);
			CV_MAT_ELEM(*vertices, float, 1, y*(nx+1)+x) = float(y)/float(ny);
			CV_MAT_ELEM(*vertices, float, 2, y*(nx+1)+x) = 1;
		}

	// generate triangles
	nbTri = nx*ny*2;
	triangles = new int[nbTri*3];
	int *tri = triangles;
	for (int y=0; y<ny; ++y)
		for (int x=0; x<nx; ++x) {
			tri[0] = y*(nx+1)+x;
			tri[1] = y*(nx+1)+x+1;
			tri[2] = (y+1)*(nx+1)+x;
			tri+=3;
			tri[0] = y*(nx+1)+x+1;
			tri[1] = (y+1)*(nx+1)+x+1;
			tri[2] = (y+1)*(nx+1)+x;
			tri+=3;
		}

	homography H;
	if (!H.estimate(0, 0, corners[0][0], corners[0][1],
				1, 0, corners[1][0], corners[1][1],
				1, 1, corners[2][0], corners[2][1],
				0, 1, corners[3][0], corners[3][1]))
		return false;

	cvMatMul(&H, vertices, transformed);
	CvMat r1,r2,r3, d1, d2;
	cvGetRow(transformed, &r1, 0);
	cvGetRow(transformed, &r2, 1);
	cvGetRow(transformed, &r3, 2);
	cvGetRow(vertices, &d1, 0);
	cvGetRow(vertices, &d2, 1);
	cvDiv(&r1,&r3,&d1);
	cvDiv(&r2,&r3,&d2);
	return true;
}

void LightCollector::drawGrid(IplImage *im, CvMat *_homography)
{
	// apply the homography to every mesh vertex
	cvMatMul(_homography, vertices, transformed);
	CvMat r1,r2,r3;
	cvGetRow(transformed, &r1, 0);
	cvGetRow(transformed, &r2, 1);
	cvGetRow(transformed, &r3, 2);
	cvDiv(&r1,&r3,&r1);
	cvDiv(&r2,&r3,&r2);
	
	for (int t=0; t<nbTri;t++) {
		int pts[3][2];
		for (int i=0; i<3; i++) {
			pts[i][0] = cvRound(CV_MAT_ELEM(*transformed, float, 0, triangles[t*3+i]));
			pts[i][1] = cvRound(CV_MAT_ELEM(*transformed, float, 1, triangles[t*3+i]));
		}
		cvLine(im, cvPoint(pts[0][0], pts[0][1]), cvPoint(pts[1][0], pts[1][1]), cvScalarAll(255), 1,4,0);
		cvLine(im, cvPoint(pts[1][0], pts[1][1]), cvPoint(pts[2][0], pts[2][1]), cvScalarAll(255), 1,4,0);
		cvLine(im, cvPoint(pts[2][0], pts[2][1]), cvPoint(pts[0][0], pts[0][1]), cvScalarAll(255), 1,4,0);
	}
}

void LightCollector::drawAvg(IplImage *im)
{
	for (int t=0; t<nbTri;t++) {
		CvPoint pts[3];
		for (int i=0; i<3; i++) {
			pts[i].x = cvRound(CV_MAT_ELEM(*transformed, float, 0, triangles[t*3+i]));
			pts[i].y = cvRound(CV_MAT_ELEM(*transformed, float, 1, triangles[t*3+i]));
		}
		CvScalar col;
		if (avgChannels >1) {
			float *c = avg + avgChannels*t;
			col = CV_RGB(c[0], c[1], c[2]);
		} else {
			col = cvScalarAll(avg[t]);
		}
		cvFillConvexPoly(im, pts, 3, col);
	}
}

struct Hdr {
	int nx,ny,nbTri,avgChannels,nbPix;
};
int LightCollector::serializeSize()
{
	return sizeof(Hdr)+nbTri*avgChannels*sizeof(float);
}

void LightCollector::serialize(char *buffer) 
{
	Hdr *hdr = (Hdr *) buffer;
	hdr->nx = nx;
	hdr->ny = ny;
	hdr->nbTri = nbTri;
	hdr->avgChannels = avgChannels;
	hdr->nbPix = nbPix;
	assert(nbTri!=0 && avgChannels!=0);
	memcpy(buffer + sizeof(Hdr), avg, nbTri*avgChannels*sizeof(float));
}

void LightCollector::load(const char *buffer, int size)
{
	const Hdr *hdr = (const Hdr *) buffer;
	//assert(nx == hdr->nx);
	//assert(ny == hdr->ny);
	nx = hdr->nx;
	ny = hdr->ny;
	nbTri = hdr->nbTri;
	if (avg && avgChannels < hdr->avgChannels) {
		delete[] avg;
		avg=0;
	}
	avgChannels = hdr->avgChannels;
	if (!avg) avg = new float[avgChannels*nbTri];
	if (size != serializeSize()) {
		printf("problem!\n");
	}
	assert(size == serializeSize());
	memcpy(avg, buffer + sizeof(Hdr), nbTri*avgChannels*sizeof(float));
}

void LightCollector::invalidate()
{
	if (avg) {
		delete[] avg;
		avg = 0;
	}
}

bool LightCollector::cmpWithRef(const LightCollector &ref, float *val, const float *_scale, const float *_shift)
{
	if (avg==0) return false;
	assert(avgChannels==ref.avgChannels);

	const float ones[3] = {1,1,1};
	const float zeroes[3] = {0,0,0};
	const float *scale = (_scale ? _scale : ones);
	const float *shift = (_shift ? _shift : zeroes);
	vector<float> values[3];

	values[0].reserve(nbTri);
	values[1].reserve(nbTri);
	values[2].reserve(nbTri);

	for (int i=0; i<nbTri; i++) {
		for (int c=0; c<avgChannels; c++) {
			float v = avg[i*avgChannels+c];
			float rv = ref.avg[i*avgChannels+c];
			if (v>= 5 && v<=250 && rv >= 5 && rv <= 250) {
				values[c].push_back((scale[c]*v+shift[c])/rv);
			}
		}
	}
	for (int i=0; i<avgChannels; i++) {
		if (values[i].size()>0) {
			val[i] = values[i][values[i].size()/2];
		} else {
			return false;
		}
	}
	return true;
}

