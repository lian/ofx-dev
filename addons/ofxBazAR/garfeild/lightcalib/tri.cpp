/*! \file Statistics over a triangle
 *  \author Julien Pilet
 */
#include <cv.h>

static const bool no_clipping=false;

static int edge_pair(IplImage *im, int sum[], int _a[2], int _b[2], int _c[2], int _d[2])
{
	int a[2];
	int b[2];
	int c[2];
	int d[2];

	if (_a[1] > _b[1]) {
		b[0] = _a[0];
		b[1] = _a[1];
		a[0] = _b[0];
		a[1] = _b[1];
	} else {
		a[0] = _a[0];
		a[1] = _a[1];
		b[0] = _b[0];
		b[1] = _b[1];
	}

	if (_c[1] > _d[1]) {
		d[0] = _c[0];
		d[1] = _c[1];
		c[0] = _d[0];
		c[1] = _d[1];
	} else {
		c[0] = _c[0];
		c[1] = _c[1];
		d[0] = _d[0];
		d[1] = _d[1];
	}

	int y_start = MAX(a[1], c[1]);
	int y_stop = MIN(b[1], d[1]);

	if (y_start >= y_stop) return 0;

	if (y_start < 0) {
		if (no_clipping) return 0;
		y_start = 0;
	}
	if (y_stop >= im->height) {
		if (no_clipping) return 0;
		y_stop = im->height - 1;
	}
	
	float slope1 = float(b[0] - a[0])/float(b[1]-a[1]);
	float delta1 = a[0] - slope1*a[1];

	float slope2 = float(d[0] - c[0])/float(d[1]-c[1]);
	float delta2 = c[0] - slope2*c[1];

	int x_step = im->nChannels;
	assert (im->depth == IPL_DEPTH_8U);

	int r=0;

	for (int y = y_start; y<y_stop; ++y) {

		float fy = (float) y;
		float x1 = slope1 * fy + delta1;
		float x2 = slope2 * fy + delta2;
		float minx = (x1 < x2 ? x1 : x2);
		int maxx = (int)(x1 > x2 ? x1 : x2);
		if (maxx < 0) continue;
		int x_start = (int)minx;
		if (x_start > im->width) {
			if (no_clipping) return 0;
			continue;
		}
		if (x_start < 0) {
			if (no_clipping) return 0;
			x_start = 0;
		}

		if (maxx >= im->width) maxx=im->width-1;
		int len = maxx-x_start;
		if (len >0) {
			r += len;
			unsigned char *ptr = (unsigned char *)im->imageData + y*im->widthStep + x_start*x_step;

			if (im->nChannels>1) 
				for (int x=0; x<len; ++x) {
					for (int c=0;c<im->nChannels;++c) {
						sum[c] += *ptr++;
					}
				} 
			else
				for (int x=0; x<len; ++x)
					sum[0] += *ptr++;
		}
	}
	return r;
}

/*! Compute the average color over a triangle.
 *
 *  \param im the input image. Must be 8 bits unsigned (IPL_DEPTH_8U). The
 *  color channels can be RGB, BGR or gray levels.
 *  \param pts image plane coordinates of the 3 vertices. Clipping is handled
 *  correctly.
 *  \param avg result average. avg[0] is either red or gray level. avg[1] and
 *  avg[2] are either green and blue or -1. If no pixel is read because the
 *  triangle is completely outside the image, the average values is set to -1.
 *  Otherwise, it is a value between 0 and 255.
 *  \return the function returns the number of pixels averaged.
 */
int stat_triangle(IplImage *im, int pts[3][2], float avg[3]) 
{
	int sum[3] = {0,0,0};
	// for every edge pair...
	int a = edge_pair(im, sum, pts[0], pts[1], pts[0], pts[2]);
	int b = edge_pair(im, sum, pts[0], pts[1], pts[1], pts[2]);
	int c = edge_pair(im, sum, pts[1], pts[2], pts[0], pts[2]);
	int tot = a+b+c;
	if (no_clipping) {
		if (a==0 || b==0 || c==0) tot=0;
	}
	if (tot>0) {
		float ftot = (float)tot;
		avg[0] = float(sum[0])/ftot;
		avg[1] = float(sum[1])/ftot;
		avg[2] = float(sum[2])/ftot;
	} else {
		avg[0] = avg[1] = avg[2] = -1;
	}
	if (im->nChannels==1) {
		avg[1] = avg[2] = -1;
	}
	return tot;
}

