#include <assert.h>
#include <cv.h>
// #include <highgui.h>
#include "CamAugmentation.h"
#include "../../starter/optimization/ls_minimizer2.h"

/**
\brief Calculates gradient.

Calculates gradient of point \b p using a calibration matrix \n
with specified intrinsic parameters \b fx , \b fy , \b cx , \b cy , \n
rotation matrix \b R and translation vector \b Rx , \b Ry , \b Rz , \n
rotation matrix \b S and translation vector \b Sx , \b Sy , \b Sz. \n
The jacobian matrices have to be specified: \b R_jacobian , \b S_Jacobian. \n
The result for all parameters is given in \b cgret[24] , the first 12
parameters for the u-coordinate, the following 12 for the v-coordinate,
each of the specifying the two multiplied Rt-matrices.
*/
extern void twomat_gradian (
                            double fx,
                            double fy,
                            double cx,
                            double cy,
                            double R_matrix[3][3],
                            double Rx,
                            double Ry,
                            double Rz,
                            CvMat *R_jacobian, 
                            double S_matrix[3][3],
                            double Sx,
                            double Sy,
                            double Sz,
                            CvMat *S_jacobian,
                            double p[3],
                            double cgret[24],
                            double uv[2] );

/**
\brief Special function to print the connection matrix.

Prints the connection matrix. Therefore it uses only rows that exist
(at least 1 existing connection to a camera) and displays the number
of the view.
*/
extern void showmatrix_ch(CvMat &M);

/**
\brief Utility function to print a matrix to the screen.

Prints a matrix to the screen. If it is a 3x3 matrix, the
determinant is shown, too.
*/
extern void showmatrix(CvMat &M);

/**
\brief Utility function to print a matrix to the screen.

Prints a matrix to the screen. If it is a 3x3 matrix, the
determinant is shown, too. \b header specifies a title
string.
*/
extern void showmatrix(CvMat &M,const char *header);

/**
\brief Utility function to print a matrix to the screen.

Prints a matrix to the screen. If it is a 3x3 matrix, the
determinant is shown, too. \b header specifies a title
string.
*/
extern void showmatrix(const char *header,CvMat &M);

/**
\brief Utility function to print a matrix to a file.

Prints the matrix \b M to file \b stream.
*/
extern void showmatrix_file(CvMat &M,FILE *stream);

CamAugmentation::CamAugmentation(){
  v_homography_r_t = cvCreateMat( 3, 4, CV_64FC1 );
  v_homography_r_t_jacobian = cvCreateMat( 3, 9, CV_64FC1 );
}

CamAugmentation::~CamAugmentation(){
  ClearAll();
  cvReleaseMat(&v_homography_r_t);
  cvReleaseMat(&v_homography_r_t_jacobian);
}

void CamAugmentation::ReleaseOptimalCameraStructure(){
  for( int i = 0; i < (int)s_optimal.v_camera_c.size(); i++ ) cvReleaseMat(&s_optimal.v_camera_c[i]);
  s_optimal.v_camera_c.clear();
  for( int i = 0; i < (int)s_optimal.v_camera_r_t.size(); i++ ) cvReleaseMat(&s_optimal.v_camera_r_t[i]);
  s_optimal.v_camera_r_t.clear();
  for( int i = 0; i < (int)s_optimal.v_camera_r_t_jacobian.size(); i++ ) cvReleaseMat(&s_optimal.v_camera_r_t_jacobian[i]);
  s_optimal.v_camera_r_t_jacobian.clear();
}

void CamAugmentation::ClearAll(){
  for( int i = 0; i < (int)v_homography.size(); i++ )
    delete	v_homography[i];
  v_homography.clear();
  ReleaseOptimalCameraStructure();
  v_opt_param.clear();
}

bool CamAugmentation::LoadOptimalStructureFromFile( char* cam_c_file, char *cam_rt_file ){
  FILE *stream;

  // Load camera calibration matrices into optimal structure:
  if( (stream = fopen( cam_c_file, "r+t" )) != NULL ){
    int num,width,height;
    while( fscanf( stream, "no: %i\nwidth: %i\nheight: %i\n", &num, &width, &height ) != EOF ){
      float h;
      CvMat* m = cvCreateMat( 3, 3, CV_64FC1 );			
      for(int i=0; i < 3; i++)
        for(int j=0; j < 3; j++) {
          fscanf( stream, "%f", &h );
          cvmSet(m,i,j,h);
        }
        fscanf( stream, "\n" );
        s_optimal.v_camera_width.push_back( width );
        s_optimal.v_camera_height.push_back( height );
        s_optimal.v_camera_c.push_back( m );
        printf( "Calibration matrix %i loaded!\n", num );
    }
    fclose( stream );
  } else {
    printf( "WARNING: Could not load matrices from file %s.", cam_c_file );
    return false;
  }

  // Load camera rotation-translation matrices into optimal structure:
  if( (stream = fopen( cam_rt_file, "r+t" )) != NULL ){
    int num,width,height;
    while( fscanf( stream, "no: %i\nwidth: %i\nheight: %i\n", &num, &width, &height ) != EOF ){
      float h;
      CvMat* m = cvCreateMat( 3, 4, CV_64FC1 );
      for(int i=0; i < 3; i++)
        for(int j=0; j < 4; j++) {
          fscanf( stream, "%f", &h );
          cvmSet(m,i,j,h);
        }
        fscanf( stream, "\n" );
        s_optimal.v_camera_r_t.push_back( m );

        // Create jacobian:
        CvMat* R = cvCreateMat( 3, 3, CV_64FC1 );
        CvMat* r = cvCreateMat( 3, 1, CV_64FC1 );
        CvMat* j = cvCreateMat( 3, 9, CV_64FC1 );
        CamCalibration::ExtractRotationTranslationFrom3x4Matrix( m, R, NULL );
        cvRodrigues2( R, r, j );
        s_optimal.v_camera_r_t_jacobian.push_back( j );
        printf( "Rotation-Translation matrix %i loaded and jacobian created!\n", num );
    }
    fclose( stream );
  } else {
    printf( "WARNING: Could not load matrices from file %s.", cam_rt_file );
    return false;
  }
  return true;
}

void CamAugmentation::AddHomography(){
  // Create new, empty homography structure:
  s_struct_homography *s_homography = new s_struct_homography();

  // Push the homography to the vector:
  v_homography.push_back( s_homography );
}

void CamAugmentation::AddHomography( std::vector<CamCalibration::s_struct_points> p, CvMat* ready ){
  // Create new, empty homography structure:
  s_struct_homography *s_homography = new s_struct_homography();

  // Copy points and homography:
  s_homography->v_point		= p;
  s_homography->m_homography  = new homography();
  cvCopy(ready, s_homography->m_homography);

  // Push the homography to the vector:
  v_homography.push_back( s_homography );
}

CvMat* CamAugmentation::InverseCalibrationMatrix( CvMat *in ){
  if( cvmGet( in, 1, 1 ) != 0 ){
    CvMat* out	= cvCreateMat( 3, 3, CV_64FC1 );
    double tau	= cvmGet( in, 0, 0 )/cvmGet( in, 1, 1 );
    double f	= cvmGet( in, 1, 1 );
    double u0	= cvmGet( in, 0, 2 );
    double v0	= cvmGet( in, 1, 2 );
    cvmSet( out, 0, 0, 1.00/(tau*f)		);
    cvmSet( out, 0, 1, 0.00				);
    cvmSet( out, 0, 2, -(u0)/(tau*f)	);
    cvmSet( out, 1, 0, 0.00				);
    cvmSet( out, 1, 1, 1.00/f			);
    cvmSet( out, 1, 2, -(v0)/f			);
    cvmSet( out, 2, 0, 0.00 			);
    cvmSet( out, 2, 1, 0.00 			);
    cvmSet( out, 2, 2, 1.00 			);
    return out;
  } else
    return NULL;
}

bool CamAugmentation::CreateHomographyRotationTranslationMatrix( int c ){
  int i;

  // Get pointer to homography:
  CvMat* m_homography = v_homography[c]->m_homography;

  if( m_homography ){

    // Vectors holding columns of H and R:
    double a_H1[3];
    CvMat  m_H1 = cvMat( 3, 1, CV_64FC1, a_H1 );
    for( i = 0; i < 3; i++ ) cvmSet( &m_H1, i, 0, cvmGet( m_homography, i, 0 ) );

    double a_H2[3];
    CvMat  m_H2 = cvMat( 3, 1, CV_64FC1, a_H2 );
    for( i = 0; i < 3; i++ ) cvmSet( &m_H2, i, 0, cvmGet( m_homography, i, 1 ) );

    double a_H3[3];
    CvMat  m_H3 = cvMat( 3, 1, CV_64FC1, a_H3 );
    for( i = 0; i < 3; i++ ) cvmSet( &m_H3, i, 0, cvmGet( m_homography, i, 2 ) );

    double a_CinvH1[3];
    CvMat  m_CinvH1 = cvMat( 3, 1, CV_64FC1, a_CinvH1 );

    double a_R1[3];
    CvMat  m_R1 = cvMat( 3, 1, CV_64FC1, a_R1 );

    double a_R2[3];
    CvMat  m_R2 = cvMat( 3, 1, CV_64FC1, a_R2 );

    double a_R3[3];
    CvMat  m_R3 = cvMat( 3, 1, CV_64FC1, a_R3 );

    // The rotation matrix:
    double a_R[9];
    CvMat  m_R = cvMat( 3, 3, CV_64FC1, a_R );

    // The translation vector:
    double a_T[3];
    CvMat  m_T = cvMat( 3, 1, CV_64FC1, a_T );

    ////////////////////////////////////////////////////////
    // Create inverse calibration matrix:
    CvMat* m_Cinv = InverseCalibrationMatrix( s_optimal.v_camera_c[c] );

    // Create norming factor lambda:
    cvGEMM( m_Cinv, &m_H1, 1, NULL, 0, &m_CinvH1, 0 );

    // Search next orthonormal matrix:
    if( cvNorm( &m_CinvH1, NULL, CV_L2, NULL ) != 0 ){
      double lambda = 1.00/cvNorm( &m_CinvH1, NULL, CV_L2, NULL );

      // Create normalized R1 & R2:
      cvGEMM( m_Cinv, &m_H1, lambda, NULL, 0, &m_R1, 0 );
      cvGEMM( m_Cinv, &m_H2, lambda, NULL, 0, &m_R2, 0 );

      // Get R3 orthonormal to R1 and R2:
      cvCrossProduct( &m_R1, &m_R2, &m_R3 );

      // Put the rotation column vectors in the rotation matrix:
      for( i = 0; i < 3; i++ ){
        cvmSet( &m_R, i, 0,  cvmGet( &m_R1, i, 0 ) );
        cvmSet( &m_R, i, 1,  cvmGet( &m_R2, i, 0 ) );
        cvmSet( &m_R, i, 2,  cvmGet( &m_R3, i, 0 ) );
      }

      // Calculate Translation Vector T (- because of its definition):
      cvGEMM( m_Cinv, &m_H3, -lambda, NULL, 0, &m_T, 0 );

      // Transformation of R into - in Frobenius sense - next orthonormal matrix:
      double a_W[9];	CvMat  m_W  = cvMat( 3, 3, CV_64FC1, a_W  );
      double a_U[9];	CvMat  m_U  = cvMat( 3, 3, CV_64FC1, a_U  );
      double a_Vt[9];	CvMat  m_Vt = cvMat( 3, 3, CV_64FC1, a_Vt );
      cvSVD( &m_R, &m_W, &m_U, &m_Vt, CV_SVD_MODIFY_A | CV_SVD_V_T );
      cvMatMul( &m_U, &m_Vt, &m_R );


      // Put the rotation matrix and the translation vector together:
      double a_view_to_cam[12];
      CvMat  m_view_to_cam = cvMat( 3, 4, CV_64FC1, a_view_to_cam );
      CamCalibration::ComposeRotationTranslationTo3x4Matrix( &m_view_to_cam, &m_R, &m_T );

      // Transfer to global reference coordinate system:
      double a_cam_inv[12];
      CvMat  m_cam_inv = cvMat( 3, 4, CV_64FC1, a_cam_inv );
      CamCalibration::Mat3x4Inverse( s_optimal.v_camera_r_t[c], &m_cam_inv );
      CamCalibration::Mat3x4Mul( &m_cam_inv, &m_view_to_cam, v_homography_r_t );

      return true;
    }
  }
  return false;
}

bool CamAugmentation::EstimateHomographyRT(){

  // Search for first existing homography:
  for( int c = 0; c < (int)v_homography.size(); c++ ){

    // If homography and corresponding camera exists, yipiee:
    if( v_homography[c]->m_homography && (int)s_optimal.v_camera_c.size() > c  ){
      return CreateHomographyRotationTranslationMatrix( c );
    }
  }
  return false;
}

int CamAugmentation::GetObservationNumber(){
  int num = 0;
  for( int c = 0; c < (int)v_homography.size(); c++ ){
    num += (int)v_homography[c]->v_point.size();
  }
  return num*2; //TODO: ohne 2 mit neuem LM-optimizer!
}

void CamAugmentation::updateCB( double *params, void **user_data ){
  CamAugmentation *cam = (CamAugmentation*) user_data[0];

  // Pass parameters to global parameter array:
  int parameter_number = 6;
  for( int i = 0; i < parameter_number; i++ )
    cam->v_opt_param[i] = params[i];

  // Update the structure:
  cam->SetParameterSet();
}

void CamAugmentation::GetParameterSet(){

  // Clear old vector:
  v_opt_param.clear();

  double a_R[9];		CvMat m_R 	  = cvMat( 3, 3, CV_64FC1, a_R );
  double a_r[3];		CvMat m_r 	  = cvMat( 3, 1, CV_64FC1, a_r );
  double a_T[3];		CvMat m_T	  = cvMat( 3, 1, CV_64FC1, a_T );

  // Pack Homography RT matrix:
  CamCalibration::ExtractRotationTranslationFrom3x4Matrix( v_homography_r_t, &m_R, &m_T);
  v_opt_param.push_back( -cvmGet( &m_T, 0, 0 ) );
  v_opt_param.push_back( -cvmGet( &m_T, 1, 0 ) );
  v_opt_param.push_back( -cvmGet( &m_T, 2, 0 ) );
  cvRodrigues2( &m_R, &m_r, v_homography_r_t_jacobian );
  v_opt_param.push_back( cvmGet( &m_r, 0, 0 ) );
  v_opt_param.push_back( cvmGet( &m_r, 1, 0 ) );
  v_opt_param.push_back( cvmGet( &m_r, 2, 0 ) );
}

void CamAugmentation::SetParameterSet(){

  double a_R[9];		CvMat m_R 	  = cvMat( 3, 3, CV_64FC1,     a_R );
  double a_r[3];		CvMat m_r 	  = cvMat( 3, 1, CV_64FC1,     a_r );
  double a_T[3];		CvMat m_T	  = cvMat( 3, 1, CV_64FC1,     a_T );

  // Unpack Homography RT matrix:
  cvmSet( &m_T, 0, 0, -v_opt_param[0] );
  cvmSet( &m_T, 1, 0, -v_opt_param[1] );
  cvmSet( &m_T, 2, 0, -v_opt_param[2] );
  cvmSet( &m_r, 0, 0,  v_opt_param[3] );
  cvmSet( &m_r, 1, 0,  v_opt_param[4] );
  cvmSet( &m_r, 2, 0,  v_opt_param[5] );
  cvRodrigues2( &m_r, &m_R, v_homography_r_t_jacobian );
  CamCalibration::ComposeRotationTranslationTo3x4Matrix( v_homography_r_t, &m_R, &m_T);
}

struct PoseObs : ls_minimizer2::observation
{
  double target[2];
  int cam;
  int point;
  PoseObs() {
    b = target;
  }
  virtual int get_nb_measures() const { return 2; };
  virtual void eval_func(const double *params, double *f, double *J, void **user_data) const;
};

//void CamAugmentation::projFunc( double *x, double *params, int na, double *f, double *grad, int *ind, LsqData *Data ){
void PoseObs::eval_func(const double *params, double *f, double *J, void **user_data) const {
                        CamAugmentation *cam = (CamAugmentation*) *user_data;

  // Unpack arguments:
  int c     = this->cam;

  // Project the point (CRTp) and set f:
  double a_p[4];		double a_p3[3]; double a_p4[3];
  double a_RT[12];	CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
  a_p[0] = cam->v_homography[c]->v_point[point].x; a_p[2] = 0;
  a_p[1] = cam->v_homography[c]->v_point[point].y; a_p[3] = 1;
  CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
  CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
  CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
  CamCalibration::Mat3x4Mul( cam->s_optimal.v_camera_r_t[c], cam->v_homography_r_t, &m_RT );
  cvMatMul( &m_RT, &m_p, &m_p3 );
  cvMatMul( cam->s_optimal.v_camera_c[c], &m_p3, &m_p4 );
  CamCalibration::HomogenousNormalizeVector( &m_p4 );
  f[0] = cvmGet( &m_p4, 0, 0 );
  f[1] = cvmGet( &m_p4, 1, 0 );

  int gc = 0;
  if( J ){

    double *grad0 = J;
    double *grad1 = J+6;
    double a_R1[9];		CvMat m_R1 	  = cvMat( 3, 3, CV_64FC1, a_R1 );
    double a_T1[3];		CvMat m_T1	  = cvMat( 3, 1, CV_64FC1, a_T1 );
    double a_R2[9];		CvMat m_R2 	  = cvMat( 3, 3, CV_64FC1, a_R2 );
    double a_T2[3];		CvMat m_T2	  = cvMat( 3, 1, CV_64FC1, a_T2 );
    CamCalibration::ExtractRotationTranslationFrom3x4Matrix( cam->s_optimal.v_camera_r_t[c], &m_R1, &m_T1 );
    CamCalibration::ExtractRotationTranslationFrom3x4Matrix( cam->v_homography_r_t, &m_R2, &m_T2 );

    double R1[3][3];
    for( int i = 0; i < 3; i++ )
      for( int j = 0; j < 3; j++ )
        R1[i][j] = cvmGet( &m_R1, i, j );

    double R2[3][3];
    for( int i = 0; i < 3; i++ )
      for( int j = 0; j < 3; j++ )
        R2[i][j] = cvmGet( &m_R2, i, j );

    double cgret[24];
    double uv[2];

    twomat_gradian (	cvmGet( cam->s_optimal.v_camera_c[c], 0, 0 ),
      cvmGet( cam->s_optimal.v_camera_c[c], 1, 1 ),
      cvmGet( cam->s_optimal.v_camera_c[c], 0, 2 ),
      cvmGet( cam->s_optimal.v_camera_c[c], 1, 2 ),
      R1,
      -cvmGet( &m_T1, 0, 0 ),
      -cvmGet( &m_T1, 1, 0 ),
      -cvmGet( &m_T1, 2, 0 ),
      cam->s_optimal.v_camera_r_t_jacobian[c],
      R2,
      -cvmGet( &m_T2, 0, 0 ),
      -cvmGet( &m_T2, 1, 0 ),
      -cvmGet( &m_T2, 2, 0 ),
      cam->v_homography_r_t_jacobian,
      a_p,
      cgret, uv );

    gc=0;
    for( int i = 0; i < 3; i++ )
      grad0[gc++] = cgret[6+i+3];
    for( int i = 0; i < 3; i++ )
      grad0[gc++] = cgret[6+i];
    gc=0;
    for( int i = 0; i < 3; i++ )
      grad1[gc++] = cgret[12+6+i+3];
    for( int i = 0; i < 3; i++ )
      grad1[gc++] = cgret[12+6+i];
  }
}

bool CamAugmentation::OptimizeCurrentView( int iter, double eps ){

  // Get number parameters and observations:
  int parameter_number   = 6;
  int observation_number = GetObservationNumber();

  ls_minimizer2 minimizer(parameter_number);
  minimizer.set_user_data(0, this);
  minimizer.set_state_change_callback(updateCB);
  minimizer.lm_set_max_iterations(iter);

  // Feed with initial parameters:
  GetParameterSet();
  //FillLsqParams( lsqData, &v_opt_param[0], 0, 0 );

  // Add the observations for ...
  int test = 0;
  for( int c = 0; c < (int)v_homography.size(); c++ )   // ... cameras
    if( v_homography[c]->m_homography ){                   
      int points = (int)v_homography[c]->v_point.size();
      for( int point = 0; point < points; point++ ){ // ... points 
        PoseObs *o = new PoseObs();
        o->cam = c;
        o->point = point;
        o->target[0] = v_homography[c]->v_point[point].u;
        o->target[1] = v_homography[c]->v_point[point].v;
        minimizer.add_observation(o, true, false);
      }
    }

    minimizer.minimize_using_levenberg_marquardt_from(&v_opt_param[0]);

    void *ptr = this;
    updateCB(minimizer.state, &ptr);

    return true;
}

bool CamAugmentation::Accomodate( int iter, double eps ){
  if( EstimateHomographyRT() ){
    return OptimizeCurrentView( iter, eps );
  } else
    return false;
}

void CamAugmentation::Clear(){
  for( int i = 0; i < (int)v_homography.size(); i++ )
    delete v_homography[i];
  v_homography.clear();
}

CvMat* CamAugmentation::GetProjectionMatrix( int c ){

  // If enough cameras mounted (calibrated):
  if( s_optimal.v_camera_c.size() > (unsigned)c ){

    // If all necessary matrices exist:
    if( s_optimal.v_camera_c[c] && s_optimal.v_camera_r_t[c] && v_homography_r_t ){
      CvMat* m_proj  = cvCreateMat( 3, 4, CV_64FC1 );
      cvMatMul( s_optimal.v_camera_c[c], s_optimal.v_camera_r_t[c], m_proj );
      CamCalibration::Mat3x4Mul( m_proj, v_homography_r_t, m_proj );
      return m_proj;
    } else
      return NULL;
  } else
    return NULL;
}

CvMat* CamAugmentation::GetRefProjectionMatrix( int c ){

  // If enough cameras mounted (calibrated):
  if( s_optimal.v_camera_c.size() > (unsigned)c ){

    // If all necessary matrices exist:
    if( s_optimal.v_camera_c[c] && s_optimal.v_camera_r_t[c] ){
      CvMat* m_proj  = cvCreateMat( 3, 4, CV_64FC1 );
      cvMatMul( s_optimal.v_camera_c[c], s_optimal.v_camera_r_t[c], m_proj );
      return m_proj;
    } else
      return NULL;
  } else
    return NULL;
}

CvMat* CamAugmentation::GetCamEyeMatrix( int c ){

  // If enough cameras mounted (calibrated):
  if( s_optimal.v_camera_c.size() > (unsigned)c ){

    if(s_optimal.v_camera_r_t[c])
      return cvCloneMat(s_optimal.v_camera_r_t[c]);
    else
      return NULL;
  } else
    return NULL;
}

CvMat* CamAugmentation::GetObjectToWorld(){
  if (v_homography_r_t)
    return cvCloneMat(v_homography_r_t);
  return 0;
}
