#ifndef GROWMAT_H
#define GROWMAT_H

#include <cv.h>

class CvGrowMat : public CvMat {
public:

	CvGrowMat(int maxlines, int maxcols, int type);
	~CvGrowMat();

	void resize(int lines, int cols);

private:
	CvMat *mat;
};

#endif
