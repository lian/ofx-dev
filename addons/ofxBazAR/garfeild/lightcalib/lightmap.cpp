#include <stdio.h>
#include <iostream>
#include <fstream>

//also includes opengl if available
#include "lightmap.h"
// #include <highgui.h>


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

using namespace std;

LightMap::LightMap()
{
	ARB=true;
	initialized=false;
	lightParams=0;
	normals=0;
	nbCam=0;
}

LightMap::LightMap(const LightMap &a)
{
	ARB=a.ARB;
	initialized=false;
	if (a.map.getIm())
		map.setImage(cvCloneImage(a.map.getIm()));
	reflc.copy(a.reflc);
	lightParams=0;
	normals=0;
	nbCam=0;
}

LightMap::~LightMap()
{
	IplImage *im = map.getIm();
	if(im) cvReleaseImage(&im);
	if (lightParams) cvReleaseMat(&lightParams);
	if (normals) delete normals;
}

bool LightMap::init(int nbCam, IplImage *model, float corners[4][2], int nx, int ny)
{
	IplImage *im = map.getIm();
	if(im) cvReleaseImage(&im);
	map.setImage(cvCreateImage(cvSize(128,64), IPL_DEPTH_32F, model->nChannels));
	cvSet(map.getIm(), cvScalarAll(.1));
	if (model->nChannels == 3) {
		im = map.getIm();
		im->channelSeq[0]='B';
		im->channelSeq[1]='G';
		im->channelSeq[2]='R';
	}

	if (!model) return false;

	reflc.genGrid(corners, nx, ny);
	reflc.averageImage(model,0);

	/*
	FILE *IRef= fopen("IRef.txt","w");
	if (IRef) {
		for (int i=0; i<reflc.nbTri; i++) 
			fprintf(IRef, "%.6f	", reflc.avg[i]);
		fprintf(IRef, "\n");
		fclose(IRef);
	}
	*/

	setCamNum(nbCam);
	return reflc.avg != 0;
}

void LightMap::normal2uv(const float n[3], float uv[2]) {
	float l = 1/sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	float n0 = n[0]*l;
	float n1 = n[1]*l;
	float n2 = n[2]*l;
	uv[0] = n0*.25f +.25f + (n2>0 ? 0:.5f);
	uv[1] = .5f+n1*.5f;
}

void LightMap::uv2normal(const float uv[2], float n[3]) {
	n[0] = (uv[0]-(uv[0]>.5f ? .5f : 0)-.25f)*4;
	n[1] = 2*uv[1]-1;
	float len = n[0]*n[0] + n[1]*n[1];
	if (len>=1) {
		float f = 1/sqrt(len);
		n[0]*=f;
		n[1]*=f;
		n[2]=(uv[0]>.5f ? -0.0f : 0.0f);
	}
	else n[2] = sqrt(1-len)*(uv[0]>.5f ? -1 : 1);

	float l = 1/sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	n[0]*=l;
	n[1]*=l;
	n[2]*=l;
}

CvScalar LightMap::readMap(const float normal[3])
{
	if (!isReady()) return cvScalarAll(1);
	float uv[2];
	normal2uv(normal, uv);
	
	IplImage *im = map.getIm();
	assert(im!=0);
	int iu = cvRound(uv[0]*(double)im->width);
	int iv = cvRound(uv[1]*(double)im->height);
	if (iu<0) iu=0;
	if (iv<0) iv=0;
	if (iu>=im->width) iu = im->width-1;
	if (iv>=im->height) iv = im->height-1;
	return cvGet2D(im, iv, iu );
}

bool LightMap::addNormal(float normal[3], LightCollector &lc, int cam)
{
	if (lightParams)
		return addNormalLightMap(normal,lc,cam);
	else
		return addNormalCalib(normal,lc,cam);
}

const float *LightMap::getGain(int cam)
{
	static const float ones[3] = {1, 1, 1};
	if (!isReady()) return ones;
	return &CV_MAT_ELEM(*lightParams, float, 2*cam, 0);
}

const float *LightMap::getBias(int cam)
{
	static const float zeroes[3] = {0, 0, 0};
	if (!isReady()) return zeroes;
	return &CV_MAT_ELEM(*lightParams, float, 2*cam+1, 0);
}

bool LightMap::addNormalLightMap(float normal[3], LightCollector &lc, int cam)
{
	if (lightParams==0) return false;
	assert(map.getIm()!=0);
	assert(cam < nbCam);

	float l = 1/sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
	normal[0]*=l;
	normal[1]*=l;
	normal[2]*=l;

	float val[3];
	if (lc.cmpWithRef(reflc, val, getGain(cam), getBias(cam)))
		return updateLightMap(normal, val);
	return false;
}

bool LightMap::updateLightMap(float normal[3], float *val)
{
	if (val[0]<0) return false;

	const int nc = map.getIm()->nChannels;

	for (int y=0; y<map.getIm()->height; y++) {
		float *line = (float *)(map.getIm()->imageData + y*map.getIm()->widthStep);

		for (int x=0; x<map.getIm()->width; x++) {
			float n[3];
			float uv[2] = { float(x)/float(map.getIm()->width), float(y)/float(map.getIm()->height) };
			uv2normal(uv, n);
			float dot = n[0]*normal[0] + n[1]*normal[1] + n[2]*normal[2];
#if 0
			if (dot>0) {
				dot = acos(dot)*2/M_PI;
				float s = .2;
				float f = (1/sqrt(2*M_PI))*exp(-(1-dot)/(2*s*s));
				line[x] = (1.0f-f)*line[x] + f*val;
			}
#else
			float min_dot=0;
			if (dot>min_dot) {
				//dot = pow(dot, 16)/2;
				float angle = (float)(acos(dot)*2/M_PI);
				//dot = (dot-min_dot)/(1-min_dot);
				float s = .2f;
				//float f = (1/sqrt(2*M_PI))*exp(-(1-dot)/(2*s*s));
				//float f = (1/sqrt(2*M_PI))*exp(-(angle)/(2*s*s));
				float f = exp(-(angle)/(2*s*s));
				for (int c=0; c<nc; c++)
					line[x*nc +c] = (1.0f-f)*line[x*nc + c] + f*val[c];
			}
#endif
		}
	}
	map.update();
	return true;
}

#ifdef HAVE_GLEW
static void printShaderInfoLog(GLuint obj, const char *str, bool ARB)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	if (ARB) glGetObjectParameterivARB(obj, GL_INFO_LOG_LENGTH,&infologLength);
	else glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		if (ARB) glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
		else glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		if (strlen(infoLog)>0) {
			if (str) printf("%s\n", str);
			printf("%s\n",infoLog);
		}
		free(infoLog);
	}
}
#endif

#ifdef HAVE_GLEW
static std::string readFile(const char * const file)
{
  std::string ret = "";
  FILE * fp = fopen(file, "rb");
  if (!fp) return "";
  fseek(fp, 0, SEEK_END);
  int size = (int)ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char * buf = new char[size + 1];
  fread(buf, size, 1, fp);
  fclose(fp);
  buf[size] = 0;
  ret = buf;
  delete [] buf;
  return ret;
}

static bool checkErrors(const char *file, int line, bool exitOnFailure=false)
{
	GLenum error;
	bool r=true;
	while ((error = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "%s:%d: %s\n", 
				file, line,
				(char *) gluErrorString(error));
		if (exitOnFailure)
			exit(-1);
		r=false;
	}
	return r;
	}
#endif

bool LightMap::initGL()
{
#ifdef HAVE_GLEW
	if (initialized) return true;
  glewInit();
	initialized = true;

  ARB = GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader;
  if (!ARB && !glewIsSupported("GL_VERSION_2_0"))
  {
    printf("No GLSL support\n");
    return false;
  }
  std::string ret;
  const char * shaderProg;

  bool ok=true;
  ret = readFile("myvert.glsl");
  shaderProg = ret.c_str();
 
  if (ARB) g_vertShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
  else g_vertShader = glCreateShader(GL_VERTEX_SHADER);
  ok = ok && checkErrors(__FILE__,__LINE__);
  
  if (ARB) glShaderSourceARB(g_vertShader, 1, &shaderProg, 0);
  else glShaderSource(g_vertShader, 1, &shaderProg, 0);
  printShaderInfoLog(g_vertShader, "Vertex shader myvert.glsl", ARB);
  ok = ok && checkErrors(__FILE__,__LINE__);

  if (ARB) glCompileShaderARB(g_vertShader);
  else glCompileShader(g_vertShader);
 
  printShaderInfoLog(g_vertShader, "Vertex shader myvert.glsl", ARB);
  ok = ok && checkErrors(__FILE__,__LINE__);

  ret = readFile("myfrag.glsl");
  shaderProg = ret.c_str();
  if (ARB) g_fragShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
  else g_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  if (ARB) glShaderSourceARB(g_fragShader, 1, &shaderProg, 0);
  else glShaderSource(g_fragShader, 1, &shaderProg, 0);

  if (ARB) glCompileShaderARB(g_fragShader);
  else glCompileShader(g_fragShader);

  printShaderInfoLog(g_fragShader, "Fragment shader myfrag.glsl", ARB);
  ok = ok && checkErrors(__FILE__,__LINE__);
  //if (!ok) return false;

  if (ARB) g_shaderProgram = glCreateProgramObjectARB();
  else g_shaderProgram = glCreateProgram();

  if (ARB) glAttachObjectARB(g_shaderProgram, g_vertShader);
  else glAttachShader(g_shaderProgram, g_vertShader);

  if (ARB) glAttachObjectARB(g_shaderProgram, g_fragShader);
  else glAttachShader(g_shaderProgram, g_fragShader);

  if (ARB) glLinkProgramARB(g_shaderProgram);
  else  glLinkProgram(g_shaderProgram);
  ok = ok && checkErrors(__FILE__,__LINE__);

  if (ARB) glValidateProgramARB(g_shaderProgram);
  else glValidateProgram(g_shaderProgram);
  ok = ok && checkErrors(__FILE__,__LINE__);
  printShaderInfoLog(g_shaderProgram, "glValidateProgram(g_shaderProgram)", ARB);
  if (ok) {
	  cout << "GLSL shaders sucessfully initialized using "
		<< (ARB ? "ARB extensions" : "OpenGL 2.0") << ".\n";
  } else
	  cout << "Failed to initialize GLSL shaders.\n";
  return ok;
#else
	return false;
#endif
}

void LightMap::enableShader(int cam, CvMat *obj2world)
{
#ifdef HAVE_GLEW
	assert(cam < nbCam);
	if (!initialized) {
		if (!initGL()) return;
	}
  if (ARB) glUseProgramObjectARB(g_shaderProgram);
  else glUseProgram(g_shaderProgram);
  if (!checkErrors(__FILE__,__LINE__)) {
	  printShaderInfoLog(g_shaderProgram, "glUseProgram(g_shaderProgram)", ARB);
	  return;
  }

  GLuint shaderTexture, worldToObjectNormal, gain, bias;
  if (ARB) {
	  shaderTexture = glGetUniformLocationARB(g_shaderProgram, "main_texture");
	  worldToObjectNormal = glGetUniformLocationARB(g_shaderProgram, "worldToObjectNormal");
	  gain = glGetUniformLocationARB(g_shaderProgram, "gain");
	  bias = glGetUniformLocationARB(g_shaderProgram, "bias");
  } else {
	  shaderTexture = glGetUniformLocation(g_shaderProgram, "main_texture");
	  worldToObjectNormal = glGetUniformLocation(g_shaderProgram, "worldToObjectNormal");
	  gain = glGetUniformLocation(g_shaderProgram, "gain");
	  bias = glGetUniformLocation(g_shaderProgram, "bias");
  }
  checkErrors(__FILE__,__LINE__);

  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, shaderTexture);
  checkErrors(__FILE__,__LINE__);

  if (ARB) glUniform1iARB(shaderTexture, 0);
  else glUniform1i(shaderTexture, 0);
  checkErrors(__FILE__,__LINE__);

  // The sign change is required because we do not like OpenGL's Z axis direction.
  // Thus, we flip all normals.
  float mat[9];
  for (int i=0; i<3; ++i)
	  for (int j=0; j<3; ++j)
		  mat[j*3 +i] = -(float)cvGet2D(obj2world, i, j).val[0];

  float g[3],b[3];
  for (int i=0;i<lightParams->cols; i++) {
	  if (lightParams) {
		  g[i] = 1/cvGet2D(lightParams, cam*2, i).val[0];
		  b[i] = g[i]*cvGet2D(lightParams, cam*2+1, i).val[0];
	  } else {
		  g[i] = 1;
		  b[i] = 0;
	  }
  }
  if (ARB) {
	  glUniform1iARB(shaderTexture, 0);
	  glUniformMatrix3fvARB(worldToObjectNormal, 1, GL_FALSE, mat);
	  glUniform4fARB(gain, g[2], g[1], g[0], 1);
	  glUniform4fARB(bias, b[2], b[1], b[0], 0);
  } else {
	  glUniform1i(shaderTexture, 0);
	  glUniformMatrix3fv(worldToObjectNormal, 1, GL_FALSE, mat);
	  glUniform4f(gain, g[2], g[1], g[0], 1);
	  glUniform4f(bias, b[2], b[1], b[0], 0);
  }
  checkErrors(__FILE__,__LINE__);
  map.loadTexture();
  checkErrors(__FILE__,__LINE__);
#endif
}

void LightMap::disableShader()
{
#ifdef HAVE_GLEW
	if (ARB) glUseProgramObjectARB(0);
	else glUseProgram(0);
	map.disableTexture();
#endif
}

void LightMap::setCamNum(int n)
{
	obs.clear();
	obs.reserve(300000);

	if (normals) delete normals;
	normals = new CvGrowMat(256,3, CV_32FC1);
	normals->resize(0,3);
	nbCam=n;

	if (lightParams)
		cvReleaseMat(&lightParams);
	lightParams=0;
}

static void normalize(float normal[3])
{
	float l = 1/sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
	normal[0]*=l;
	normal[1]*=l;
	normal[2]*=l;
}

bool LightMap::addNormalCalib(float normal[3], LightCollector &lc, int cam)
{
	assert(nbCam>0);
	if (lc.avg==0 || reflc.avg==0) return false;

	bool hasObs=false;

	assert(lc.nbTri == reflc.nbTri);

	int normIdx = normals->rows + nbCam*2;
	bool newT=true;
	float maxdot= .999;

	normalize(normal);

	// is the normal already in the database ?
	for (int i=0; i<normals->rows; i++) {
		float *n2 = (float *)CV_MAT_ELEM_PTR(*normals, i, 0);
		float ndot = n2[0]*normal[0] +
			n2[1]*normal[1] +
			n2[2]*normal[2];
		if (ndot > maxdot) {
			newT=false;
			maxdot = ndot;
			normIdx = i + nbCam*2;
		}
	}

//	if (newT) {
//		obsMat->resize(obsMat->rows, obsMat->cols+1);
//	} 

	for (int i=0; i<lc.nbTri; ++i) {
		float *rv = reflc.avg+i*reflc.avgChannels;
		float *v = lc.avg+i*lc.avgChannels;
		bool ok=true;
		for (int c=0; c<reflc.avgChannels; c++)
			if (!(v[c]>5 && rv[c] >5 && v[c]<250 && rv[c] <250)) 
				ok=false;
		if (ok) {
			hasObs = true;

			Observation o;
			o.camCol = cam*2;
			o.normalCol = normIdx;
			
			for (int c=0; c<reflc.avgChannels; c++) {
				o.camVal[c] = - v[c]/255.0f;
				o.normalVal[c] = rv[c]/255.0f;
			}
			obs.push_back(o);
		}
	}

	if (newT&&hasObs){
		// add the normal vector
		normals->resize(normals->rows+1, normals->cols);
		float *n = (float *)CV_MAT_ELEM_PTR(*normals, normals->rows-1,0);
		n[0] = normal[0];
		n[1] = normal[1];
		n[2] = normal[2];
	}
	return true;
}

static bool saveMat(const CvMat *m, const char *fn)
{
	ofstream f(fn);

	if (!f.good()) return false;

	for (int j=0; j<m->rows; j++) {
		for (int i=0; i<m->cols; i++) {
			double v = cvGet2D(m, j, i).val[0];
			f << v;
			if (i+1 < m->cols) f<<'\t';
		}
		f << endl;
	}
	f.close();
	return true;
}

static CvGrowMat *loadMat(const char *fn)
{
	ifstream f(fn);

	if (!f.good()) return 0;

	CvGrowMat *m = new CvGrowMat(128,3, CV_32FC1);
	m->resize(1,1);

	int nrow=0;
	do {
		char line[4096];
		f.getline(line, 4095);
		line[4095]=0;
		if (!f.good()) break;

		++nrow;

		int ncols=1;
		int len = strlen(line);
		char *last=line;
		for (int i=0;i<len+1;i++) {
			if (line[i]==' ' || line[i]=='\t' || line[i]==0) {
				line[i] = 0;
				float val;
				if (sscanf(last, "%f", &val)==1) {
					m->resize(nrow,max(ncols, m->cols));
					cvSet2D(m, nrow-1, ncols-1, cvScalarAll(val));
					ncols++;
				}
			last = line+i+1;
			}
		}
	} while (f.good());

	return m;
}

double LightMap::getObsMat(int i, int j, int c)
{
	if (j == obs[i].camCol) return (double)obs[i].camVal[c];
	if (j == (obs[i].camCol+1)) return 1;
	if (j == obs[i].normalCol) return (double)obs[i].normalVal[c];
	return 0;
}

double LightMap::getObsElem(const vector<Observation>::iterator &it, int i, int c)
{
	if (it->camCol == i) return it->camVal[c];
	if (it->camCol+1 == i) return 1;
	if (it->normalCol == i) return it->normalVal[c];
	return 0;
}

void LightMap::computeAtA(CvMat *AtA, int channel)
{
	for (vector<Observation>::iterator it = obs.begin();
			it!=obs.end(); ++it) 
	{
		int idx[3] = {it->camCol, it->camCol+1, it->normalCol};
		for (unsigned i=0; i<3; i++) {
			for (unsigned j=0; j<3; j++) {
				int i_ = idx[i];
				int j_ = idx[j];
				if (i_ <= j_) {
					double v = getObsElem(it,i_, channel)*getObsElem(it,j_, channel);
					if (v!=0) {
						double d = v+cvGetReal2D(AtA, i_, j_);
						cvSetReal2D(AtA, i_, j_, d);
						cvSetReal2D(AtA, j_, i_, d);
					}
				}
			}
		}
	}
	/*
	for (int y=1;y<AtA->height; y++)
		for (int x=0;x<y; x++) {
			CV_MAT_ELEM(*AtA, float, y, x) = CV_MAT_ELEM(*AtA, float, x, y);
		}
	*/
}

bool LightMap::save(const char *lightParamsFN, const char *normalsFN)
{
	return saveMat(lightParams,lightParamsFN) &&
		saveMat(normals, normalsFN);
}

bool LightMap::computeLightParams()
{
	int obsMatCols=normals->rows+2*nbCam;
	int sizes[] = {obs.size(), obsMatCols};

	if (lightParams) cvReleaseMat(&lightParams);
	lightParams = cvCreateMat(obsMatCols, reflc.avgChannels, CV_32FC1);
	sizes[0] = sizes[1] = obsMatCols;

	// create temporary matrices
	CvMat *AtA = cvCreateMat(obsMatCols,obsMatCols, CV_32FC1);
	CvMat *w = cvCreateMat(obsMatCols, 1, CV_32FC1);
	CvMat *V = cvCreateMat(obsMatCols, obsMatCols, CV_32FC1);

	for (int c=0; c<reflc.avgChannels; c++) {
		cvSetZero(AtA);
		computeAtA(AtA, c);

		/* char atafn[64];
		sprintf(atafn,"ata%d.mat",c);
		saveMat(AtA, atafn);
		*/

		cvSVD(AtA, w, 0, V, CV_SVD_MODIFY_A);

		CvMat sub, lpc;
		cvGetCol(V, &sub, V->cols-1);
		cvGetCol(lightParams, &lpc, c);
		cvScale(&sub, &lpc, 1.0/cvGet2D(&sub,0,0).val[0]);

		/*
		   std::cout << "Eigen values:";
		   for (int i=0; i<w->rows; ++i) {
		   float v = (float)cvGet2D(w, i, 0).val[0];
		   std::cout << " " << v;
		   }
		   std::cout << std::endl;
		 */
	}
	cvReleaseMat(&V);
	cvReleaseMat(&AtA);

	// construct light map
	cvSet(map.getIm(), cvScalarAll(.1));
	cvReleaseMat(&w);

	/*
	std::cout << "Camera Values:\n";
	for (int c=0; c<nbCam; ++c) {
		float g = (float)cvGet2D(lightParams, c*2, 0).val[0];
		float b = (float)cvGet2D(lightParams, c*2+1, 0).val[0];
		std::cout <<"     cam " << c << ": "<< g <<", " << b << std::endl;
	}
	*/
	buildMapFromSamples();
	return true;
}

void LightMap::buildMapFromSamples()
{
	for (int i=0; i<normals->rows; ++i) {
		updateLightMap((float *)CV_MAT_ELEM_PTR(*normals, i, 0), 
				&CV_MAT_ELEM(*lightParams, float, i+2*nbCam, 0));
	}
}

bool LightMap::load(const char *lightParamsFN, const char *normalsFN)
{
	CvGrowMat *lp= loadMat(lightParamsFN);
	if (!lp) return false;
	lightParams = cvCreateMat(lp->rows, lp->cols, CV_32FC1);
	cvCopy(lp, lightParams);
	printf("Loaded lightParams: %dx%d.\n", lp->rows, lp->cols);
	delete lp;
	normals = loadMat(normalsFN);
	int nlights = lightParams->rows - 2*nbCam;
	if (!normals || ((normals->rows) < nlights)) {
		if (normals) {
			printf("Not enough normals. Expecting %d cameras. Found %d normals and %d parameters.\n",
				nbCam, normals->rows, lightParams->rows);
		}
		cvReleaseMat(&lightParams);
		return false;
	}
	if (normals->rows > nlights)
		normals->resize(nlights,3);

	/*
	std::cout << "Camera Values:\n";
	for (int c=0; c<nbCam; ++c) {
		float g = (float)cvGet2D(lightParams, c*2, 0).val[0];
		float b = (float)cvGet2D(lightParams, c*2+1, 0).val[0];
		std::cout <<"     cam " << c << ": "<< g <<", " << b << std::endl;
	}
	*/

	buildMapFromSamples();
	
	return true;
}

bool LightMap::saveImage(const char *filename)
{
	IplImage *image = map.getIm();
	if (image==0) return false;
	IplImage *im = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U,image->nChannels);
	//double min=0, max=2;
	//cvMinMaxLoc(image, &min, &max);
	cvConvertScale(image, im, 128, 0);
//	int r = cvSaveImage(filename, im);
	int r = 1;
	cvReleaseImage(&im);
	return r!=0;
}
