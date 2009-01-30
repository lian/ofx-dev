#ifndef _CAMAUGMENTATION_H
#define _CAMAUGMENTATION_H

#include "CamCalibration.h"

struct PoseObs;

/*!\defgroup geomcalib Geometric calibration and augmentation of a set of camera.
 * \ingroup garfeild
 */
/*!
 \class   CamAugmentation
 \ingroup geomcalib
 \brief   Turns homographies into 2D poses from calibrated views.
 \author  Andreas Geiger

 Implements functions to estimate rotation and translation of a view for each
 of multiple cameras which was taken at the same time. Demands the calibration
 results of class CamCalibration.

 \author  Computer Vision Laboratory, http://cvlab.epfl.ch/
 \author  Swiss Federal Institute of Technology, Lausanne
 \date    20.03.2006
*/
class CamAugmentation {

public:
  /**
   \brief Constructor of the CamAugmentation class.
   */
  CamAugmentation();

  /**
  \brief Destructor of the CamAugmentation class.

  The class should be destroyed with the deconstructor after having
  done its job.
  */
  ~CamAugmentation();

  /**
  \brief Add an empty homography.

  This adds an empty homography, if detection failed for a specific camera.
  */
  void AddHomography();

  /**
  \brief Add a homography.

  This adds a homography. Unlike in CamCalibration, this time homographies
  are added for each different camera view. The order of the cameras should
  always remain the same. Therefore, if you don't have data for a specific
  camera, use AddHomography() to add an empty homography. If you want to
  estimate another view and therefore reset the structures, use Clear().
  For this function (AddHomography) you have to specify a vector of 
  point correspondances and a matrix \b ready, specifying the homography.
  */
  void AddHomography( std::vector<CamCalibration::s_struct_points> p, CvMat* ready );

  /**
  \brief Accomodates the given data.

  This function starts the non-linear Levenberg-Marquardt estimation
  progress with the given maximal number of iterations \b iter and the
  maximal accuracy \b eps. There are 6 parameters to determine: The rotation
  and translation parameters which transform a point from the given view 
  coordinate system to the reference coordinate system which was
  determined by CamCalibration. Therefore this function is pretty fast.
  The output may be grabbed with GetProjectionMatrix().
  */
  bool Accomodate( int iter, double eps );

  /**
  \brief Reset the internal structures.

  If you want to add a new view with new homographies for each camera,
  you need to clear the internal structures with the help of this function.
  */
  void Clear();

  /**
  \brief Get the estimated projection matrix.

  Returns the projection matrix estimate which results from Accomodate().
  This projection matrix can be used to do any kind of augmentation, using
  OpenGL or DirectX, for example.
  \return null on error. Otherwise, the CvMat is a 3x4 matrix. 
  The caller has to call cvReleaseMat() to free memory.
  */
  CvMat* GetProjectionMatrix( int c );

  /**
  \brief Get the world coordinate projection matrix for cam c2.

  Returns the world projection matrix as calibrated.
  */
  CvMat* GetRefProjectionMatrix( int c );

  //! return the rotation/translation matrix for camera c.
  CvMat *GetCamEyeMatrix( int c );

  //! Returns the object current pose
  CvMat* GetObjectToWorld();

  /**
  \brief Loads the calibration results from a file.

  The following 2 files have to be provided, coming from CamCalibration

  - \b cam_c_file: Contains all calibration matrices of the cameras
  - \b cam_rt_file: Contains all rotation-translation matrices of the cameras

  Has to be called before Homographies may be added and finally accomodation
  takes place.
  */
  bool LoadOptimalStructureFromFile( char* cam_c_file, char *cam_rt_file );

  void ClearAll();

private:

  /**
  \brief The optimal structure.

  This structure contains all matrices after they have been transformed
  into the new reference centralized system (see CamCalibration): In this new system a projection
  always consists of multiplying 3 matrices: \b v_camera_c * \b v_camera_r_t * \b v_homography_r_t.
  */
  struct s_struct_optimal {
    std::vector<int> v_camera_width;
    std::vector<int> v_camera_height;
    std::vector<CvMat*> v_camera_c;
    std::vector<CvMat*> v_camera_r_t;
    std::vector<CvMat*> v_camera_r_t_jacobian;
  };

  /**
  \brief Instance of the optimal structure.

  Contains all data from the calibrated cameras (intrinsic and extrinsic
  parameters in the new coordinate system). Must be filled before
  calling Accomodate().
  */
  s_struct_optimal s_optimal;

  /**
  \brief Homography structure.

  This structure contains the homography (\b m_homography) as well as the correspondance 
  points of a view (\b v_point). There has to exist one structure for each of the
  cameras' views. This is done by pushing them back to the vector
  \b v_homography. The deconstructor automatically frees used memory.
  */
  struct s_struct_homography {
    std::vector<CamCalibration::s_struct_points>   v_point;
    homography*   m_homography;

    s_struct_homography(){
      m_homography = NULL;
    }
    ~s_struct_homography(){
      v_point.clear();
      delete m_homography;
    }
  };

  /**
  \brief Vector of homographies.

  This vector contains a homography structure for each camera. It has to
  be filled with the results of object detection before calling 
  Accomodate().
  */
  std::vector<s_struct_homography*> v_homography;

  /**
  \brief Resultant rotation-translation matrix.

  This is the matrix where the results will be saved after processing
  Accomodate(). A projection may than be assembled by
  \b v_camera_c * \b v_camera_r_t * \b v_homography_r_t.
  */
  CvMat*         v_homography_r_t; //TODO: warum v?? m!!!

  /**
  \brief Jacobian of the resultant rotation-translation matrix.

  This matrix is used internally for the global optimization process.
  */
  CvMat*         v_homography_r_t_jacobian;

  /**
  \brief Parameter vector in reference coordinate system.

  This vector contains the following 6 parameters in the reference system
  in order to do optimization:

  - the view RT parameters (tx,ty,tz,rx,ry,rz)
  */
  std::vector<double> v_opt_param;

  /**
  \brief Estimates the RT matrix from the given homographies.

  After adding all homographies this function performs an initial guess
  in order to provide the 6 free parameters to optimize on. Therefore
  it calls CreateHomographyRotationTranslationMatrix for an existing
  view (one with homography). If successfull it returns true.
  */
  bool EstimateHomographyRT();

  /**
  \brief Inverts the given calibration matrix \b in.

  Only works for calibration matrices with skew factor = 0.
  */
  CvMat* InverseCalibrationMatrix( CvMat *in );

  /**
  \brief Estimates the RT matrix from the given homographies.

  This function searches for the RT matrix from the new view to a given
  camera \b c. Makes use of a SVD to orthonormalize R. The result is saved
  in \b v_homography_r_t and serves as a starting point for the LM-optization.
  */
  bool CreateHomographyRotationTranslationMatrix( int c );

  /**
  \brief Performs Levenberg-Marquardt optimization.

  Optimizes \b v_homography_r_t with the maximal number of iterations
  \b iter and the maximal accuracy \b eps.
  */
  bool OptimizeCurrentView( int iter, double eps );

  /**
  \brief Returns the number of observation for all homographies together.
  */
  int GetObservationNumber();

  /**
  \brief Converts \b v_homography_r_t into \b v_opt_param.
  */
  void GetParameterSet();

  /**
  \brief Converts \b v_opt_param into \b v_homography_r_t.
  */
  void SetParameterSet();

  /**
  \brief Updates the matrix \b v_homography_r_t according to the new parameters.

  Used by OptimizeCurrentView.
  */
  static void updateCB(double *params, void **user_data);

  /**
  \brief Does nothing.

  Easy to use. Without bugs. Worthless.
  */
  //static void PrintIterationResult(  double *params );

  /**
  \brief Projects point x and calculates gradient.

  Used by OptimizeCurrentView.\n
  - x[0] = camera
  - x[1] = axis
  - x[2] = point
  - params = current calibration parameters (=v_opt_param)
  - f = result of projection
  - grad = resultant gradient
  */
  //static void projFunc( double *x, double *params, int na, double *f, double *grad, int *ind, LsqData *Data );

  void ReleaseOptimalCameraStructure();

  friend class PoseObs;
};

#endif
