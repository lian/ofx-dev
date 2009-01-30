#ifndef _CAMCALIBRATION_H
#define _CAMCALIBRATION_H

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include <vector>
#include <math.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
// #include <cv.h>
#include "cv.h"
#include "ofxCvColorImage.h"

#include "../../starter/geometry/homography.h"

struct ProjObs;

/**
\class   CamCalibration
\ingroup geomcalib
\brief Calibrates one or more cameras from homographies and 2D/3D correspondances.

Implements functions to calibrate a set of cameras
at one time using planar 2D-2D correspondances.
Provides functions to output the resulting matrices
including intrinsic and extrinsic camera parameters
as well as statistical functions.

See \ref singlecalib.cpp for a single camera simple example, or \ref
multicam.cpp for a complete example.

\author  Andreas Geiger
\author  Computer Vision Laboratory, http://cvlab.epfl.ch/
\author  Swiss Federal Institute of Technology, Lausanne
\date    20.02.2006
*/
class CamCalibration {

public:
  /**
  \brief Constructor of the CamCalibration class.
  */
  CamCalibration();

  /**
  \brief Deconstructor of the CamCalibration class.

  The class should be destroyed with the deconstructor after having
  done its job.
  */
  ~CamCalibration();

  /**
  \brief Add a camera.

  This function adds a camera with the specified \b width and \b height to
  the CamCalibration class. Before adding a homography you should
  create the camera. The first added camera is numbered 0, the
  following with increasing numbers.
  */
  void AddCamera( int width, int height );

  /**
  \brief Add an empty homography (without data) to camera c.

  This adds an empty homography to the camera specified by \b c. If the
  camera does not exist this function returns false, otherwise true.
  This function should be used if the homographie is not available
  (i.e. due to too much noise in the picture).
  */
  bool AddHomography( int c );

  /**
  \brief Transfer structure for AddHomography().

  This structure is needed to pass the feature points in the original
  image pattern and on the screen to a given homography. Create an
  vector of (s_struct_points) and pass it to AddHomography(...).
  Parameters are:
  \b u , \b v : Correspondence coordinates on the screen (image plane)
  \b x , \b y : Correspondence coordinates in the world  (z=0)
  */
  struct s_struct_points {
    double u,v,x,y;
    s_struct_points(){}
    s_struct_points( double u, double v, double x, double y ) : u(u), v(v), x(x), y(y) {}
  };

  /**
  \brief Add a homography with data to camera c.

  This adds a homography to the camera specified by \b c. If the
  camera does not exist this function returns false, otherwise true.
  The parameter \b p specifies the array of correspondances described
  above, \b n is the corresponcance number and \b ready specifies a matrix
  with the homography in OpenCV format. If \b ready equals NULL the
  homography is calculated internally by the class. Nevertheless it
  is recommanded to provide the homography here!
  */
  bool AddHomography( int c, std::vector<CamCalibration::s_struct_points> p, CvMat* ready );

  /**
  \brief Stores initial homography structure to file.

  Stores the whole homography structure to a file specified by
  \b file_name. This function is useful, if the aquiring system
  you use takes time and you want to tune parameters without
  waiting each time you run the optimization.
  */
  bool StoreHomographiesToFile( char* file_name );

  /**
  \brief Loads initial homography structure from file.

  Loads the whole homography structure from a file specified by
  \b file_name. Recovers the homographies you saved with
  \b StoreHomographiesToFile().
  */
  bool LoadHomographiesFromFile( char* file_name );

  /**
  \brief Starts the camera calibration process.

  After adding all cameras and homographies this function will
  estimate the intrinsic and extrinsic parameters of the cameras as
  well as the rotation and translation of the image pattern at every
  time step. You have to specify a number of parameters here:\n
  - \b p_HomographyNum : Maximal number of homographies to use for optimization.
  - \b p_PreFilter: Filtering method to use: 0=Greedy, 1=Padding, 2=Probabilistic
  - \b p_PreFilter_a: For Padding filter: Specifies ratio, for Probabilistic filter: specifies weight 1
  - \b p_PreFilter_b: For Probabilistic filter: specifies weight 2
  - \b p_PreFilter_c: For Probabilistic filter: specifies weight 3
  - \b p_InitialGuess_a: Specifies alpha
  - \b p_InitialGuess_b: Specifies beta
  - \b p_InitialGuess_c: Specifies gamma
  - \b p_Iterations: Specifies maximal number of Levenberg-Marquardt iterations
  - \b p_Epsilon: Specifies maximal accuracy of Levenberg-Marquardt optimization
  - \b p_PostFilter: Specifies post filter threshold tau\n

  \b Note: For a more detailed parameter description have a look at the report attached to this project!
  */
  bool Calibrate( int p_HomographyNum, int p_PreFilter, int p_Solutions, double p_PreFilter_a, double p_PreFilter_b, double p_PreFilter_c,
    double p_InitialGuess_a, double p_InitialGuess_b, double p_InitialGuess_c,
    int p_Iterations, double p_Epsilon, double p_PostFilter );

  /**
  \brief Prints resulting matrices seperated to 3 files.

  The output files are:\n
  - \b "camera_c" : Contains the resulting camera calibration matrices (intrinsic parameters)
  - \b "camera_r_t" : Contains the resulting camera rotation/translation matrices. These
  matrices transform a point from the reference system to the specified
  camera coordinate system.
  - \b "view_r_t" : Contains the resulting view rotation/translation matrices. These
  matrices transform a point from the specified view coordinate system
  to the reference system.\n

  \b Note: A projection matrix can be built by applying the following matrix multiplication:
  \b camera_c*camera_r_t*view_r_t
  */
  void PrintOptimizedResultsToFile1();

  /**
  \brief Prints resulting projection matrices to many separated files.

  This function calculates a projection matrix for each view-to-camera combination
  available and stores the result to separated files (1 file per matrix). You have
  to specify a \b file_descripter, which contains 2x \b "%04d" or similar. The first
  indicates the camera number, the second stands for the view number. A possible
  example is given by: \b "cam%04d\\img%04d.tdir".\n
  Please note that if you use directories (like this example demonstrates), they
  are NOT created, but have to exist before. Otherwise the results will not be saved. \n
  If you want to create png files into a new directory, simply enable the \b create_png
  flag and set the corresponding parameters. The directories have to exist before, for image
  creation, too.
  */
  void PrintOptimizedResultsToFile2(  char* file_descriptor, bool create_png = false, char* sequence_descriptor = "", 
    char* png_descriptor = "", int c_start = 0, int h_start = 0 );

  /////////////////////////////////////////////////////////////////////////////////////
  // Functions below this line are used by CamCalibration and CamAugmentation only ! //
  /////////////////////////////////////////////////////////////////////////////////////

  /**
  \brief Decomposes \b RotTrans into \b Rot and \b Trans.

  Note: By definition, the translation vector is inversed.
  */
  static void ExtractRotationTranslationFrom3x4Matrix( CvMat* RotTrans , CvMat* Rot, CvMat*Trans );

  /**
  \brief Composes \b Rot and \b Trans to \b RotTrans.

  Note: By definition, the translation vector is inversed.
  */
  static void ComposeRotationTranslationTo3x4Matrix( CvMat* RotTrans , CvMat* Rot, CvMat*Trans );

  /**
  \brief Multiplies 3x4 matrices \b m_A and \b m_B to \b m_C.
  */
  static void Mat3x4Mul( CvMat* m_A, CvMat* m_B, CvMat* m_C );

  /**
  \brief Inverts 3x4 matrix \b m_A and stores result to \b m_B.
  */
  static void Mat3x4Inverse( CvMat* m_A, CvMat* m_B );

  /**
  \brief Divides \b mat by its last element.
  */
  static void HomogenousNormalizeVector( CvMat* mat );

  void PlotPointsToImagesAfterOptimization();

  void ClearAll();

private:

  /**
  \brief Structure specifying 2D-to-2D correspondances.

  This structure specifies 2D-to-2D correspondances which are the base for
  the homographies used in this algorithm. \b p is the number of points in
  this structure. \b px and \b py are the coordinate arrays of planar points on
  the calibration pattern. \b v_m_wp is contains artificial world points in a matrix-vector format,
  while \b v_m_pp contains the points on the image plane. \b r and \b t specifies
  translation and rotation parameters for creating artificial world points.
  Note that if this algorithm is only used to do calibration on real world data, only
  \b p , \b px , \b py and \b v_m_pp are important!
  */
  struct s_struct_plane {
    int                 p;
    double             *px;
    double             *py;
    std::vector<CvMat*> v_m_wp;
    std::vector<CvMat*> v_m_pp;
    double              rx,ry,rz;
    double              tx,ty,tz;

    s_struct_plane() {
      px     = NULL;
      py     = NULL;
    }

    ~s_struct_plane() {
      delete px;
      delete py;
      for( int i = 0; i < (int)v_m_wp.size(); i++ ) cvReleaseMat(&v_m_wp[i]);
      v_m_wp.clear();
      for( int i = 0; i < (int)v_m_pp.size(); i++ ) cvReleaseMat(&v_m_pp[i]);
      v_m_pp.clear();
    }
  };

  /**
  \brief Structure specifying one homography of a single camera.

  This structure describes exactly one homography. On the one side it contains "raw data" like
  \b s_plane_object or \b m_homography. On the other side estimation matrices like 
  \b m_estim_r_t_matrix and \b m_jacobian_matrix are saved in this structure. \b b_discard
  is a parameter used by the pre-filtering function: This method sets this parameter to 
  false if it wants to keep a homography and afterwards removes all homographies with the
  \b b_discard flag still enabled. Therefore this flag is initialized with true (one could
  translate this with "discard candidate", it's like in real life, we are all "discard candidates"
  somehow, cheerless, but true ;).
  */
  struct s_struct_homography {
    s_struct_plane*    s_plane_object;
    homography*     m_homography;
    CvMat*      m_estim_r_t_matrix;
    CvMat*      m_jacobian_matrix;
    bool      b_discard;

    s_struct_homography(){
      s_plane_object     = new s_struct_plane();
      b_discard     = true; // specifies discarding candidates
      m_homography       = NULL; // NULL  = not valid!
      m_estim_r_t_matrix = cvCreateMat( 3, 4, CV_64FC1 );
      m_jacobian_matrix  = cvCreateMat( 3, 9, CV_64FC1 );
    }
    ~s_struct_homography(){
      if( s_plane_object ) delete s_plane_object;
      if( m_homography   ) delete m_homography;
      cvReleaseMat(&m_estim_r_t_matrix);
      cvReleaseMat(&m_jacobian_matrix );
    }
  };

  /**
  \brief Structure specifying a camera's intrinsic parameters.

  Used by s_struct_camera.
  */
  struct s_struct_intrinsic {
    double focal;
    double aspect;
    double u0,v0;
  };

  /**
  \brief Structure specifying a single camera.

  This structure describes a single camera. The camera's widht and height are specified
  by \b w and \b h. \b s_intrinsic, \b m_calibration_matrix and \b m_rot_trans_matrix are
  only important if you create artificial calibration data for testing issues. \b s_estim_int
  are the estimated intrinsic parameters and by \b v_homography specifies a vector of homography
  structures is given for this camera. Finally, \b m_estim_calib_matrix and \b m_estinvcalib_matrix
  stand for the estimated calibration matrices (resp. its inversed matrices) resulting from
  the first initial guess performed using the technique of Zhengyou Zhang.
  */
  struct s_struct_camera {
    int         w,h;
    s_struct_intrinsic     s_intrinsic;
    s_struct_intrinsic     s_estim_int;
    std::vector<s_struct_homography*> v_homography;
    CvMat*        m_calibration_matrix;
    CvMat*        m_rot_trans_matrix;
    CvMat*        m_estim_calib_matrix;
    CvMat*        m_estinvcalib_matrix;  

    s_struct_camera( int width, int height ){
      w = width;
      h = height;
      m_calibration_matrix = cvCreateMat( 3, 3, CV_64FC1 );
      m_rot_trans_matrix   = cvCreateMat( 3, 4, CV_64FC1 );
      m_estim_calib_matrix = cvCreateMat( 3, 3, CV_64FC1 );
      m_estinvcalib_matrix = cvCreateMat( 3, 3, CV_64FC1 );
    }

    ~s_struct_camera(){
      for( int i = 0; i < (int)v_homography.size(); i++ ) delete v_homography[i];
      v_homography.clear();
      cvReleaseMat(&m_calibration_matrix);
      cvReleaseMat(&m_rot_trans_matrix  );
      cvReleaseMat(&m_estim_calib_matrix);
      cvReleaseMat(&m_estinvcalib_matrix);
    }
  };

  /**
  \brief The main camera vector which contains the whole hierarchy.
  */
  std::vector<s_struct_camera*> v_camera;

  /**
  \brief A candidate solution created by the probabilistic filter.
  */
  struct s_struct_solution {
    int c,h;
    s_struct_solution( int c, int h ) : c(c), h(h) {}
  };

  /**
  \brief The optimal structure.

  This structure contains all matrices after they have been transformed
  into the new reference centralized system: \b c_max and \b h_max specify
  the camera and homography number with maximal connections. \b h_max is the
  view which we call \b "reference view"! In this new system a projection
  always consists of multiplying 3 matrices: \b v_camera_c*v_camera_r_t*v_homograph
  */
  struct s_struct_optimal {
    int     c_max, h_max;
    std::vector<CvMat*> v_camera_c;
    std::vector<CvMat*> v_camera_r_t;
    std::vector<CvMat*> v_camera_r_t_jacobian;
    std::vector<CvMat*> v_homography_r_t;
    std::vector<CvMat*> v_homography_r_t_jacobian;
    /// old code:
    /*deleteall(){
    for( int i = 0; i < (int)v_camera_c.size(); i++ )
    if( v_camera_c[i] ) cvReleaseMat( &v_camera_c[i] );
    v_camera_c.clear();
    for( int i = 0; i < (int)v_camera_r_t.size(); i++ )
    if( v_camera_r_t[i] ) cvReleaseMat( &v_camera_r_t[i] );
    v_camera_r_t.clear();
    for( int i = 0; i < (int)v_camera_r_t_jacobian.size(); i++ )
    if( v_camera_r_t_jacobian[i] ) cvReleaseMat( &v_camera_r_t_jacobian[i] );
    v_camera_r_t_jacobian.clear();
    for( int i = 0; i < (int)v_homography_r_t.size(); i++ )
    if( v_homography_r_t[i] ) cvReleaseMat( &v_homography_r_t[i] );
    v_homography_r_t.clear();
    for( int i = 0; i < (int)v_homography_r_t_jacobian.size(); i++ )
    if( v_homography_r_t_jacobian[i] ) cvReleaseMat( &v_homography_r_t_jacobian[i] );
    v_homography_r_t_jacobian.clear();
    }*/
    s_struct_optimal(){
    }
    ~s_struct_optimal(){
      //deleteall();
    }
  };

  /**
  \brief Instance of the optimal structure.

  Base of the final Levenberg-Marquardt iteration in the new reference
  coordinate system.
  */
  s_struct_optimal s_optimal;

  /**
  \brief Parameter vector in new reference coordinate system.

  This vector contains all of the parameters in the new reference system
  in order to do optimization:

  - all camera intrinsic parameters (f1,g1,u1,v1,f2,g2,...)
  - all camera RT parameters (t1x,t1y,t1z,r1x,r1y,r1z,t2x,t2y,...)
  - all view RT parameters (t1x,t1y,t1z,r1x,r1y,r1z,t2x,t2y,...)
  */
  std::vector<double> v_opt_param;

  /**
  \brief Connection matrix.

  Matrix which serves for transforming the old system into the new one: \n
  The rows are identified with the cameras and the columns stand for the
  views. If a connection between a camera and a view exists, its entry is 1
  else it equals 0. \b CreateMatrixCH tries to fill this matrix with connections
  if it can establish a chain in order to recalculate a missing connection.
  Connections which could not be established are indicated with a 0 entry.
  */
  CvMat *m_CH;

  /**
  \brief Matrix descriptor.

  Enumeration which facilates the handling of matrices. Used by GetM.
  */
  enum matrix_desc { m_calibration,
    m_rot_trans,
    m_estim_calib,
    m_estinvcalib,
    m_estim_r_t,
    m_jacobian };

  /**
  \brief Error histogram iteration counter.

  Counter which is increased after every successful LM-iteration.
  Serves to plot the iteration number to the error histogram screen
  and file.
  */
  int  errorgraphic_counter;

  /**
  \brief Was used for statistics. Experimental.
  */
  int  stat_HomographyNum;

  /**
  \brief Was used for statistics. Experimental.
  */
  time_t stat_ExpStartTime;

  /**
  \brief Returns floating-point random variable between min and max.
  */
  double  GetRandomValue( double min, double max );

  /**
  \brief Adds gaussian noise with deviation sigma = \b noise to the first 2 entries of \b mat.
  */
  void    AddGaussianNoise( CvMat* mat, double noise );

  /**
  \brief Set intrinsic parameters of camera \b c.

  - \b f = focal length
  - \b a = aspect ratio
  - \b u = principal point (x-coordinate)
  - \b v = principal point (y-coordinate)
  */
  void SetIntrinsicParam( int c, double f, double a, double u, double v );

  /**
  \brief Creates an artificial calibration plane.

  Creates an artificial plane for camera \b c and homography \b h. You have to input
  the number of points \b p, their position \b px and \b py, and the rotation \b rx,
  \b ry, \b rz as well as the translation \b tx, \b ty and \b tz of the artificial
  plane object. This function is \b NOT used with real calibration data, but for
  performance testing issues.
  */
  void SetPlaneObject( int c, int h, int p, double px[], double py[],
    double rx, double ry, double rz, double tx, double ty, double tz );

  /**
  \brief Creates a calibration matrix from intrinsic parameters.

  Takes the intrinsic parameters out of s_struct_intrinsic \b s_intrinsic of camera \b c and puts
  them into \b m_calibration_matrix. This function is \b NOT used with real calibration data, but for
  performance testing issues.
  */
  void CreateCalibrationMatrixFromIntrinsicParameters( int c );

  /**
  \brief Creates an estimated calibration matrix from estimated intrinsic parameters.

  Takes the estimated intrinsic parameters out of s_struct_intrinsic \b s_estim_int of camera \b c and puts
  them into \b m_estim_calib_matrix.
  */
  void CreateEstimatedCalibrationMatrixFromEstimatedIntrinsicParameters( int c );

  /**
  \brief Creates an estimated inverse calibration matrix from estimated intrinsic parameters.

  Takes the estimated intrinsic parameters out of s_struct_intrinsic \b s_estim_int of camera \b c 
  and calculates directly \b m_estinvcalib_matrix.
  */
  void CreateEstimatedInverseCalibrationMatrixFromEstimatedIntrinsicParameters( int c );

  /**
  \brief Creates rotation-translation matrix.

  For this function \b m_estinvcalib_matrix and homography \b h of camera \b c have to
  preexist. It then calculates the corresponding rotation-translation matrix using
  the SVD for orthonormal approximation. Puts the output into \b m_estim_r_t.
  */
  void    CreateRotationTranslationMatrixFromInverseCalibrationMatrixAndHomography( int c, int h );

  /**
  \brief Creates all rotation-translation matrices for camera \b c.

  Simply loops through all homographies of camera \c and applies
  CreateRotationTranslationMatrixFromInverseCalibrationMatrixAndHomography.
  */
  void    CreateAllRotationTranslationMatrices( int c );

  /**
  \brief Creates rotation-translation identity matrix for camera \b c.

  This function is \b NOT used with real calibration data, but for
  performance testing issues.
  */
  void    CreateRotationTranslationIdentityMatrix( int c );

  /**
  \brief Creates rotation-translation matrix for camera \b c.

  This function is \b NOT used with real calibration data, but for
  performance testing issues.
  */
  void    CreateRotationTranslationMatrix( int c, double rx, double ry, double rz,
    double tx, double ty, double tz );

  /**
  \brief Calculates the artificial world points of camera \b c and homography \b h.

  This function is \b NOT used with real calibration data, but for
  performance testing issues.
  */
  void CreatePlaneObjectWorldPoints( int c, int h );

  /**
  \brief Calculates the artificial plane points of camera \b c and homography \b h.

  Therefore uses the plane points. This function is \b NOT used with real calibration data, but for
  performance testing issues.
  */
  void CreatePlaneObjectPlanePoints( int c, int h, double noise );

  /**
  \brief Creates a homography for camera \b c.

  Therefore uses the plane points and the world points. If a homography (\b ready) is passed
  it simply copies it. This is recommended.
  */
  void CreateWorldPlaneHomography( int c, int h, CvMat* ready );

  /**
  \brief Checks if homography \b h of camera \b c is singular.

  Projects a standard square with the help of the homography and measures angles using
  the initial guess parameters. Returns true if homography should not be considered
  for initial guessing process (Zhang's method).
  */
  bool    HomographySingular( int c, int h, double p_InitialGuess_a, double p_InitialGuess_b, double p_InitialGuess_c );

  /**
  \brief Calculates angle between vectors v2-v1 and v4-v3.
  */
  double  VectorAngle( CvMat* v1, CvMat* v2, CvMat* v3, CvMat* v4 );

  /**
  \brief Calculates euclidean distance between \b v1 and \b v2.
  */
  double  PointDistance( CvMat* v1, CvMat* v2 );

  /**
  \brief Deletes homography \b h of camera \b c.
  */
  void    DeleteWorldPlaneHomography( int c, int h );

  /**
  \brief Returns a random solution for the probabilistic filter of size \b num.
  */
  std::vector<s_struct_solution> GetRandomSolution( int num );

  /**
  \brief Returns the euclidean distance on the screen of 2 homographies of camera \b c.

  Projects the point (0,0,1) using the 2 homographies \b h1 and \b h2 and returns euclidean
  distance between them. Used by the probabilistic filter function.
  */
  double GetScreenDistance( int c, int h1, int h2 );

  /**
  \brief Returns the quality of \b solution.

  Returns a weighted sum according to the parameters representing the quality of the solution.
  Used by the probabilistic filter function.
  */
  double  GetSolutionQuality( std::vector<s_struct_solution> solution, double p_PreFilter_a, double p_PreFilter_b, double p_PreFilter_c );

  /**
  \brief Greedy homography filter to reduce dimensions of optimization.

  This filter does not make much sense. It's just a quantitative filter without
  regarding qualitative aspects. For testing issues only, or if you want to take
  all homographies: Set \b num >= the number of homographies you provide!
  */
  bool    FilterBestHomographiesGreedyMethod( int num );

  /**
  \brief Padding homography filter to reduce dimensions of optimization.

  This filter filters \b num homographies out of all. It owns an additional parameter,
  the  Padding_Ratio called \b PreFilter_a. It implies 2 phases: in the first phase
  Homography_Num/(Camera_Num*Padding_Ratio) homographies for each of the cameras are
  extracted to ensure enough calibration data for each of the cameras. In a second phase
  the remaining amount of homographies is filled with the views endowing the most of the
  connections in a descending order. This ensures good connectivity which turned out to be
  very important for the system. \n
  This filter is state-of-the-art and should be used for this algorithm. It provides
  best results up to the moment you come and make a better one! So if you do so, let
  me know!
  */
  bool    FilterBestHomographiesFillingMethod( int num, double p_PreFilter_a );

  /**
  \brief Probabilistic homography filter to reduce dimensions of optimization.

  This filter filters \b num homographies out of all. It is based on a fitness function
  which depends on the number of correspondances \b p_PreFilter_a, on the number of
  connections \b p_PreFilter_b and the distances between homographies \b p_PreFilter_c.
  \b p_Solutions describes how many solutions should be generated to evaluate them
  and take the best one. The problem is that only a small space of all solutions is
  covered and therefore leads to a suboptimal result. Therefore this filter is still
  experimental. Better use the padding filter instead!
  */
  bool    FilterBestHomographiesRandomMethod( int num, int p_Solutions, double p_PreFilter_a, double p_PreFilter_b, double p_PreFilter_c );

  /**
  \brief Extract intrinsic parameters of camera \b c.

  Zhengyou Zhang strikes back! Here the initial guess of the intrinsic parameters takes
  place. You need to specify the parameters for rejecting singular homographies
  (\b p_InitialGuess_a, \b p_InitialGuess_b, \b p_InitialGuess_c).
  */
  bool    ExtractIntrinsicParameters( int c, double p_InitialGuess_a, double p_InitialGuess_b, double p_InitialGuess_c );

  /**
  \brief Returns normalized frobenius distance between \b h1 and \b h2 of camera \b c.

  Is not used anymore. Feel free to do so!
  */
  double  GetFrobeniusDistance( int c, int h1, int h2 );

  /**
  \brief Returns homographies \b h1 and \b h2 of camera \b c with largest distance.

  Is not used anymore. Feel free to do so!
  */
  bool    GetDistalHomographiesForCalibration( int c, int *h1, int *h2 );

  /**
  \brief Filters views with an average error bigger than \b p_PostFilter.

  Operates in the new reference coordinate system (s_optimal).
  Returns true if at least one view has been filtered.
  */
  bool FilterHomographiesAfterOptimization( double p_PostFilter );

  /**
  \brief Performs the global Levenberg-Marquardt optimization.

  Performs LM-opt with maximal \b iter iterations or \b eps accuracy.
  If one of them has been reached views with an average error bigger than
  \b p_PostFilter are filtered. Continues optimization until no more
  improvements could be observed. Results are stored in the s_struct_optimal \b s_optimal
  structure.
  */
  bool OptimizeCalibrationByMinimalParameterMethod( int iter, double eps, double p_PostFilter );

  /**
  \brief Creates connection matrix.

  Creates the global private matrix \b m_CH: Inserts 1 for existing connection
  and 0 for failure. Tries to recover not existing connections and - if successful -
  adds 1 entry to \b m_CH. The recovered rotation-translation matrices are stored
  (like the others) in v_camera[c]->v_homography[h]->m_estim_r_t_matrix.
  */
  bool    CreateMatrixCH();

  /**
  \brief Compresses parameters from \b s_optimal to \b v_opt_param.
  */
  void    GetParameterSetFromOptimalStructure();

  /**
  \brief Extracts parameters from \b v_opt_param to \b s_optimal.
  */
  void    SetParameterSetToOptimalStructure();

  /**
  \brief Recovers rotation-translation matrix using 3 other ones.

  Recovers r/t-matrix (\b c2,\b h1) using (\b c1,\b h1), (\b c1,\b h2) and (\b c2,\b h2).
  */
  void    CreateEstimated3ChainMatrixRT( int h1, int c1, int h2, int c2 );

  /**
  \brief Recovers homography-homography rotation-translation matrix.

  Calculates \b h1 -> \b h2 rotation-translation matrix using camera \b c1
  as connection between them.
  */
  void CreateEstimatedOptimalHomographyMatrixRT( int h1, int c1, int h2 );

  /**
  \brief Creates rotation-translation matrix for camera \b c.

  Uses view \b h as reference system.
  */
  void CreateEstimatedOptimalCameraMatrixRT( int c, int h );

  /**
  \brief Copies calibration matrix to new camera structure.
  */
  void CreateEstimatedOptimalCameraMatrixC( int c );

  /**
  \brief Creates the whole new camera structure stored in \b s_optimal.

  Creates the camera structure with the reference system. Therefore
  uses the subroutines CreateEstimatedOptimalHomographyMatrixRT, 
  CreateEstimatedOptimalCameraMatrixRT and CreateEstimatedOptimalCameraMatrixC.
  Returns false if connection matrix construction failed, else true.
  */
  bool CreateOptimalCameraStructure();

  /**
  \brief Releases the structure stored in \b s_optimal.

  Must be called before new one is created in order to delete the old one
  and free memory.
  */
  void ReleaseOptimalCameraStructure();

  /**
  \brief Returns the number of parameters (DOF) in \b s_optimal.

  This equals to the number of dimensions in which we force LM to optimize.
  */
  int     GetParameterNumber();

  /**
  \brief Returns the number of observations.
  */
  int     GetObservationNumber();

  /**
  \brief Helper function to gain quick access to matrices in the first system.

  Such are defined by the enum type \b matrix_desc.
  */
  CvMat* GetM( enum matrix_desc desc, int c, int h );

  /**
  \brief Translates a 4x4 matrix \b v by \b x, \b y and \b z.
  */
  void Translate3DVector( CvMat* v, double x, double y, double z );

  /**
  \brief Rotates a 4x4 matrix \b v by \b x, \b y and \b z.

  No OpenCV rodrigues rotation, but pitch, roll, yaw.
  */
  void Rotate3DVector( CvMat* v, double x, double y, double z );

  /**
  \brief Converts 3x4 matrix \b m_A to 4x4 matrix \b m_B.

  Used to be able to perform multiplications, etc.
  */
  static void Mat3x4ToMat4x4( CvMat* m_A, CvMat* m_B );

  /**
  \brief Converts 4x4 matrix \b m_A to 3x4 matrix \b m_B.

  Used to be able to perform multiplications, etc.
  */
  static void Mat4x4ToMat3x4( CvMat* m_A, CvMat* m_B );

  /**
  \brief Updates the matrices of \b s_optimal according to the new parameters.

  Used by OptimizeCalibrationByMinimalParameterMethod.
  */
  static void updateCB(double *params, void **user_data);

  /**
  \brief Projects point x and calculates gradient.

  Used by OptimizeCalibrationByMinimalParameterMethod.\n
  - x[0] = camera
  - x[1] = homography
  - x[2] = axis
  - x[3] = point
  - params = current calibration parameters (=v_opt_param)
  - f = result of projection
  - grad = result gradient
  */
  //static void projFunc( double *x, double *params, int na, double *f, double *grad, int *ind, LsqData *Data );

  /**
  \brief Prints optimized result errors after each iteration as well as an error histogram.
  */
  void PrintOptimizedResultErrors(  double *params );

  /**
  \brief Appends time needed for optimization to stat.txt.

  Used only for performance tests.
  */
  void PrintStatisticToFile();

  friend struct ProjObs;
};

#endif
