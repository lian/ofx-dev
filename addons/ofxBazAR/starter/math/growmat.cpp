#include "growmat.h"

CvGrowMat::CvGrowMat(int maxlines, int maxcols, int type)
{
	mat = cvCreateMat(maxlines, maxcols, type);
	cvSetZero(mat);
	cvGetSubRect(mat, this, cvRect(0,0,maxcols,maxlines));
}

CvGrowMat::~CvGrowMat()
{
	cvReleaseMat(&mat);
}

void CvGrowMat::resize(int lines, int cols)
{
	if (lines <= mat->rows && cols <= mat->cols) {
		cvGetSubRect(mat, this, cvRect(0,0,cols,lines));
		//this->rows = lines;
		//this->cols = cols;
	} else {
		int nl = (lines > mat->rows ? lines*2 : mat->rows);
		int nc = (cols > mat->cols ? cols*2 : mat->cols);
		CvMat *nm = cvCreateMat(nl, nc, mat->type);
		cvSetZero(nm);
		if (this->rows && this->cols) {
			CvMat sub;
			cvGetSubRect(nm, &sub, cvRect(0,0,this->cols, this->rows));
			cvCopy(this, &sub);
			cvGetSubRect(nm, this, cvRect(0,0,cols, lines));
		} else {
			cvGetSubRect(nm, this, cvRect(0,0,mat->cols, mat->rows));
			this->rows = lines;
			this->cols = cols;
		}
		cvReleaseMat(&mat);
		mat = nm;
	}
}

