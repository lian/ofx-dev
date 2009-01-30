#include <fstream>
#include <iostream>
#include <string.h> // for memset
#include "camera.h"
#include "matvec.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_GL

#ifdef HAVE_APPLE_OPENGL_FRAMEWORK
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#else

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#define HAVE_GL
#endif

#endif

using namespace std;

PerspectiveProjection::PerspectiveProjection()
{
	set(640,480,1000,1000,320,240,0);
}

PerspectiveProjection::PerspectiveProjection(int w, int h, double f, double g, double cx, double cy, double s)
{
	set(w,h,f,g,cx,cy,s);
}

void PerspectiveProjection::set(int w, int h, double f, double g, double cx, double cy, double s)
{
	this->width = w;
	this->height = h;
	this->f = f;
	this->g = g;
	this->cx = cx;
	this->cy = cy;
	this->s = s;
	distortion = 0;

	nearPlane = f/16;
	farPlane = f*16;
	cmpEyeToImageMat();
}

/*! Set near and far clipping planes. Both values have to be positive. Far
 * should also be larger than near. If the values are incorrect, the near and
 * far are not modified.
 * \return true if near and far are valid and accepted, false otherwise.
 */
bool PerspectiveProjection::setPlanes(double nearPlane, double farPlane)
{
	if ((nearPlane > 0) && (nearPlane < farPlane)) {
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
		return true;
	}
	return false;
}


/*! Project eye coordinates to image coordinates.
 * uv[0] is the horizontal axis (left -> right) and uv[1] is the vertical axis,
 * pointing up.
 */ 
void PerspectiveProjection::eyeToImage(const double eye[3], double uv[2]) const
{
	uv[0] = (f * eye[0] + s * eye[1]) / eye[2] + cx;
	uv[1] = (g * eye[1]) / eye[2] + cy;
}

/*! Find the 3D eye coordinate of a given pixel.
 * u is the horizontal axis (left -> right) and v is the vertical axis,
 * pointing up.
 */ 
void PerspectiveProjection::imageToEye(double u, double v, double eye[3], double w) const
{
	if (w==0) w = nearPlane;

	eye[1] = (v - cy)*(f/g);
	eye[0] = (u - cx - s*eye[1]);
	eye[2] = f;

	//double l = this->nearPlane / sqrt(eye[0]*eye[0] + eye[1]*eye[1] + eye[2]*eye[2]);
	double l = w / f;
	eye[0] *= l;
	eye[1] *= l;
	eye[2] *= l;
}

void PerspectiveProjection::imageToEye(const double uv[2], double eye[3], double w) const
{
	imageToEye(uv[0], uv[1], eye, w);
}

/*!
 * This will produce the exact same projection in the case s=0. Otherwise,
 * there might be some clipping problems.
 *
 * The trick is to remember that OpenGL has a negative Z projection.
 * You should glScale(1,1,-1); if you use positive Z.
 *
 * OpenGl, after projection, clips coordinates to [-1, 1] on all axis. It is
 * converted then to window coordinates.
 */
void PerspectiveProjection::setGlProjection() const 
{
#ifdef HAVE_GL
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble m[16];
	for (int i=0; i<16; ++i) m[i]=0;
	double w = (double) width;
	double h = (double) height;

	double _near = this->nearPlane;
	double _far = this->farPlane;

	m[0 + 0*4] = 2*f/w;
	m[0 + 1*4] = 2*s/w;
	m[0 + 2*4] = (-2*cx/w +1);
	m[1 + 1*4] = 2*g/h;
	m[1 + 2*4] = (-2*cy/h +1);
	m[2 + 2*4] = -(_far+_near)/(_far-_near);
	m[2 + 3*4] = -2*_far*_near/(_far-_near);
	m[3 + 2*4] = -1;

	glLoadMatrixd(m);
#else
	cerr << "camera.cpp was not compiled with OpenGL support.\n";
#endif
}

void PerspectiveProjection::cmpEyeToImageMat()
{
	eyeToImageMat.m[0][0] = f;
	eyeToImageMat.m[1][0] = 0;
	eyeToImageMat.m[2][0] = 0;
	eyeToImageMat.m[0][1] = s;
	eyeToImageMat.m[1][1] = g;
	eyeToImageMat.m[2][1] = 0;
	eyeToImageMat.m[0][2] = cx;
	eyeToImageMat.m[1][2] = cy;
	eyeToImageMat.m[2][2] = 1;
}

/*! Inverse V axis (projected image upside/down)
 */
void PerspectiveProjection::flip()
{
	g= -g;
	cy = height -1 -cy;
	cmpEyeToImageMat();
}

bool PerspectiveProjection::getUndistortMap(CvMat *xmap, CvMat *ymap)
{
	if (distortion == 0) return false;

	for (int y=0; y<xmap->height; y++) {
		for (int x=0; x<ymap->height; y++) {
			float image[2], distor[2];

			image[0] = (x - (cx))/f;
			image[1] = (y - (cy))/g;

			distor[0] = image[0] - distortion * image[0] * (image[0]*image[0]+image[1]*image[1]);
			distor[1] = image[1] - distortion * image[1] * (image[0]*image[0]+image[1]*image[1]);


			cvSetReal2D(xmap, y, x, distor[0]*f + cx);
			cvSetReal2D(ymap, y, x, distor[1]*g + cy);
		}
	}
	return true;
}

PerspectiveCamera::PerspectiveCamera()
{
	clearExternalParams();
	translate(0,0,-f);
}

void PerspectiveCamera::worldToImage(const Vec3 &p, Vec3 &uvw) const
{
	uvw.setMul(worldToImageMat, p);
	uvw.v[0] /= uvw.v[2];
	uvw.v[1] /= uvw.v[2];
}

void PerspectiveCamera::worldToImage(const double p[3], double uvw[3]) const
{
	worldToImage(*((Vec3 *)p), *((Vec3 *)uvw));
}

void PerspectiveCamera::worldToEye(const Vec3 &src, Vec3 &dst) const
{
	dst.setMul(worldToEyeMat, src);
}

void PerspectiveCamera::worldToEye(const double src[3], double dst[3]) const
{
	((Vec3 *)dst)->setMul(worldToEyeMat, *((Vec3 *)src));
}

void PerspectiveCamera::setGlModelView() const
{
#ifdef HAVE_GL
	GLdouble m[16];

	for (int i=0; i<3; ++i) 
		for (int j=0;j<4; ++j) 
			m[i+j*4] = worldToEyeMat.m[i][j];
	m[3+0*4] = m[3+1*4] = m[3+2*4] = 0;
	m[3+3*4]=1;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1,1,-1);
	glMultMatrixd(m);
#else
	cerr << "camera.cpp was not compiled with OpenGL support.\n";
#endif
}

void PerspectiveCamera::setByTarget(const Vec3 pos, const Vec3 target, double roll)
{
	Vec3 x,y,z;

	// TODO: is this correct ?
       	Vec3 up(sin(roll), cos(roll), 0);

	z.setSub(target, pos);
	z.normalize();
	
	x.setCross(z,up);
	y.setCross(x,z);

	for (int i=0; i<3; i++) {
		worldToEyeMat.m[0][i] = x[i];
		worldToEyeMat.m[1][i] = y[i];
		worldToEyeMat.m[2][i] = z[i];
	}

	for (int i=0; i<3; ++i) {
		worldToEyeMat.m[i][3] = -worldToEyeMat.m[i][0]*pos[0]
			- worldToEyeMat.m[i][1]*pos[1]
			- worldToEyeMat.m[i][2]*pos[2];
	}
	cmpWorldToImageMat();
}

static void get3x3MulWithTransposed(const double m[3][4], double mmt[3][3])
{
	double t7 = m[0][0]*m[0][0];
	double t8 = m[0][1]*m[0][1];
	double t9 = m[0][2]*m[0][2];
	double t14 = m[0][0]*m[1][0]+m[0][1]*m[1][1]+m[0][2]*m[1][2];
	double t18 = m[0][0]*m[2][0]+m[0][1]*m[2][1]+m[0][2]*m[2][2];
	double t19 = m[1][0]*m[1][0];
	double t20 = m[1][1]*m[1][1];
	double t21 = m[1][2]*m[1][2];
	double t26 = m[1][0]*m[2][0]+m[1][1]*m[2][1]+m[1][2]*m[2][2];
	double t27 = m[2][0]*m[2][0];
	double t28 = m[2][1]*m[2][1];
	double t29 = m[2][2]*m[2][2];
	mmt[0][0] = t7+t8+t9;
	mmt[0][1] = t14;
	mmt[0][2] = t18;
	mmt[1][0] = t14;
	mmt[1][1] = t19+t20+t21;
	mmt[1][2] = t26;
	mmt[2][0] = t18;
	mmt[2][1] = t26;
	mmt[2][2] = t27+t28+t29;
}

/*!
 * This function separate intrinsic and extrinsic parameters from a single
 * projection matrix. The resulting rotation matrix (worldToEyeMat) determinant
 * is always positive.
 */
void PerspectiveCamera::loadTdir(const double _tdir[3][4], int w, int h)
{
	this->width=w;
	this->height=h;
	double tdir[3][4];

	double ppt[3][3];

	double l = sqrt(_tdir[2][0]*_tdir[2][0]
			+ _tdir[2][1]*_tdir[2][1]
			+ _tdir[2][2]*_tdir[2][2]);
	for (int i=0; i<3; ++i)
		for (int j=0;j<4; ++j)
			tdir[i][j] = _tdir[i][j]/l;

	get3x3MulWithTransposed(tdir, ppt);

	worldToEyeMat.m[2][0] = tdir[2][0];
	worldToEyeMat.m[2][1] = tdir[2][1];
	worldToEyeMat.m[2][2] = tdir[2][2];
	worldToEyeMat.m[2][3] = tdir[2][3];

	cx = ppt[2][0];
	cy = ppt[2][1];

	// sign is unkown!
	g = sqrt(ppt[1][1]-cy*cy);

	s = (ppt[1][0]-cx*cy)/g;

	// sign is also unknown!
	f = sqrt(ppt[0][0]-cx*cx-s*s);

	worldToEyeMat.m[1][0] = (tdir[1][0] - cy*worldToEyeMat.m[2][0])/g;
	worldToEyeMat.m[0][0] = (tdir[0][0] - s*worldToEyeMat.m[1][0] - cx*worldToEyeMat.m[2][0])/f; 

	worldToEyeMat.m[1][1] = (tdir[1][1] - cy*worldToEyeMat.m[2][1])/g;
	worldToEyeMat.m[0][1] = (tdir[0][1] - s*worldToEyeMat.m[1][1] - cx*worldToEyeMat.m[2][1])/f; 

	worldToEyeMat.m[1][2] = (tdir[1][2] - cy*worldToEyeMat.m[2][2])/g;
	worldToEyeMat.m[0][2] = (tdir[0][2] - s*worldToEyeMat.m[1][2] - cx*worldToEyeMat.m[2][2])/f; 

	worldToEyeMat.m[1][3] = (tdir[1][3] - cy*worldToEyeMat.m[2][3])/g;
	worldToEyeMat.m[0][3] = (tdir[0][3] - s*worldToEyeMat.m[1][3] - cx*worldToEyeMat.m[2][3])/f;

	if (worldToEyeMat.det() < 0) {
		g=-g;
		for (int i=0;i<4;++i) worldToEyeMat.m[1][i] = -worldToEyeMat.m[1][i];
	}

	cmpEyeToImageMat();
	eyeToWorldMat.setInverseByTranspose(worldToEyeMat);
	memcpy(&worldToImageMat, tdir, sizeof(worldToImageMat));

}

/*! Load external and internal parameters from a tdir file. The w and h specify
 * the size of the projection rectangle.
 *
 * \return true on success, false on failure.
 */
bool PerspectiveCamera::loadTdir(const char *tdirFile, int w, int h)
{
	ifstream file;
	file.open(tdirFile);

	if (!file.good()) return false;
	double tdir[3][4];

	for (int j=0; j<3; ++j) 
		for (int i=0; i<4; ++i) 
			file >> tdir[j][i];
	char line[256];
	while (file.getline(line,256)) {
		if (memcmp(line, "distortion:", 11)==0) {
			double d;
			if (sscanf(line+11, "%lf", &d)==1) {
				distortion = d;
				printf("Camera distortion: %f\n", d);
			}
		} else if (memcmp(line, "width:", 6)==0) {
			int nw;
			if (sscanf(line+6, "%d", &nw)==1) {
				w = nw;
			}
		} else if (memcmp(line, "height:", 7)==0) {
			int nh;
			if (sscanf(line+7, "%d", &nh)==1) {
				h = nh;
			}
		} else if (memcmp(line, "near:", 5)==0) {
			double d;
			if (sscanf(line+5, "%lf", &d)==1) {
				nearPlane = d;
				printf("Near clipping plane: %f\n", d);
			}
		} else if (memcmp(line, "far:", 4)==0) {
			double d;
			if (sscanf(line+4, "%lf", &d)==1) {
				farPlane = d;
				printf("Near clipping plane: %f\n", d);
			}
		}
	}
	file.close();
	loadTdir(tdir, w,h);

	// look for a .plane file.
	if (strlen(tdirFile) > 5) {
		char fn[512];
		strncpy(fn, tdirFile, 511);
		strcpy(fn + strlen(fn) - strlen(".tdir"), ".plane");
		file.open(fn);

		if (file.good()) {
			double d,n=nearPlane,f=farPlane;
			for (int i=0; i<4; ++i)
				file >> d;
			if (file.good())  file >> n;
			if (file.good()) file >> f;

			file.close();
			if (setPlanes(n,f))
				std::cout << "Reading clipping planes from " << fn 
					<< ": near=" << n 
					<< " far=" << f << endl;
			else
				std::cerr << "Troubles loading " << fn << "!\n";
		}
	}
	return true;
}

struct GuessMode {
	int w, h;
};
static double diag(double x, double y)
{
	return sqrt(x*x+y*y);
}

static double diagDiff(const GuessMode &m, double dx, double dy)
{
	double mdiag = diag(double(m.w), double(m.h));
	return fabs(double(mdiag - diag(2*dx,2*dy)));
}


/*! Load external and internal parameters from a tdir file, estimating image
 * width and height.
 *
 * THE WIDTH AND HEIGHT ESTIMATION MIGHT BE WRONG!
 *
 * \return true on success, false on failure.
 */
bool PerspectiveCamera::loadTdir(const char *tdirFile)
{
	if (!loadTdir(tdirFile,0,0)) return false;

	if ((width !=0) && (height !=0)) return true;

	static const GuessMode mode[] = {
		{ 640, 480 },
		{ 320, 240 },
		{ 720, 576 },
		{ 360, 288 },
		{ 800, 600 },
		{ 1024, 768},
		{ 512, 384},
		{ 1280, 1024},
		{ -1, -1}
	};

	int best=0;
	double bestDelta = diagDiff(mode[0], cx, cy);	
	for (int i=1; mode[i].w != -1; ++i) {
		double delta = diagDiff(mode[i], cx, cy);
		if (delta < bestDelta) {
			best = i;
			bestDelta = delta;
		}
	}
	width = mode[best].w;
	height = mode[best].h;

	return true;
}


void PerspectiveCamera::clearExternalParams()
{
	worldToEyeMat.setIdentity();
	cmpWorldToImageMat();
}

void PerspectiveCamera::cmpWorldToImageMat()
{
	worldToImageMat.setMul(eyeToImageMat, worldToEyeMat);
	eyeToWorldMat.setInverseByTranspose(worldToEyeMat);
}

void PerspectiveCamera::eyeToWorld(const Vec3 &uvw, Vec3 &w) const
{
	w.setMul(eyeToWorldMat, uvw);
}

void PerspectiveCamera::imageToWorld(double u, double v, Vec3 &w, double depth) const
{
	Vec3 uvw;
	imageToEye(u,v, uvw.v, depth);
	eyeToWorld(uvw, w);
}

void PerspectiveCamera::translate(double dx, double dy, double dz) 
{
	worldToEyeMat.m[0][3] -= dx;
	worldToEyeMat.m[1][3] -= dy;
	worldToEyeMat.m[2][3] -= dz;
	cmpWorldToImageMat();
}

void PerspectiveCamera::setWorldToEyeMat(const Mat3x4 &m)
{
	worldToEyeMat = m;
	cmpWorldToImageMat();
}

bool PerspectiveCamera::saveTdir(const char *file)
{
	ofstream f(file);

	if (!f.good()) return false;

	for (int l=0; l<3; l++) {
		for (int c=0; c<4; c++) {
			f << worldToImageMat.m[l][c] << " ";
		}
		f << "\n";
	}
	f << "width: " << width << endl;
	f << "height: " << height << endl;
	f << "distortion: " << distortion << endl;
	f << "near: " << nearPlane << endl;
	f << "far: " << farPlane << endl;
	return true;
}

ostream& operator << (ostream& os, const PerspectiveProjection &cam)
{
	os << "fx=" << cam.f
		<< ", fy="<< cam.g
		<< ", cx="<< cam.cx
		<< ", cy="<< cam.cy
		<< ", s="<< cam.s
		<< ", near="<< cam.nearPlane
		<< ", far="<< cam.farPlane
		<< ", width="<<cam.width
		<< ", height="<<cam.height;
	return os;
}

ostream& operator << (ostream& os, const PerspectiveCamera &cam) 
{
	os << ((PerspectiveProjection) cam) << endl;
	os << cam.getWorldToEyeMat();
	return os;
}


