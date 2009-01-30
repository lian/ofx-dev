#include <assert.h>
#include <cv.h>
#include <cxcore.h>
#include <cvtypes.h>
// #include <highgui.h>

#include "CamCalibration.h"
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

int imin(int a, int b) {
  return (a<b ? a:b);
}

CamCalibration::CamCalibration(){
  m_CH = NULL;
  srand( (unsigned)time(NULL) );
  printf("Welcome to AMCC!\n");
  printf("================\n\n");
}

CamCalibration::~CamCalibration(){
  ClearAll(); 
}

void CamCalibration::ClearAll(){
  if( m_CH ) cvReleaseMat( &m_CH );
  for( int i = 0; i < (int)v_camera.size(); i++ )
    delete v_camera[i];
  v_camera.clear();
  ReleaseOptimalCameraStructure();
  v_opt_param.clear();
  if( m_CH ) cvReleaseMat( &m_CH ); m_CH = NULL;
}

void CamCalibration::AddCamera( int width, int height ){
  v_camera.push_back( new s_struct_camera( width, height ) );
}

bool CamCalibration::AddHomography( int c ){
  // Check if camera is allocated:
  if( (int)v_camera.size() <= c ){
    printf("ERROR: Homography has not been added: Camera %i does not exist!\n",c);
    return false;
  }

  // Create new, empty homography structure:
  s_struct_homography *s_homography = new s_struct_homography();

  // Push the homography to the vector:
  v_camera[c]->v_homography.push_back( s_homography );

  return true;
}

bool CamCalibration::AddHomography( int c, std::vector<CamCalibration::s_struct_points> p, CvMat* ready ){
  // Check if camera is allocated:
  if( (int)v_camera.size() <= c ){
    printf("ERROR: Homography has not been added because Camera %i doesn't exist!\n",c);
    return false;
  }

  // Create new homography structure:
  s_struct_homography *s_homography = new s_struct_homography();

  // Allocate space:
  s_homography->s_plane_object->px = new double[p.size()];
  s_homography->s_plane_object->py = new double[p.size()];

  // Store m_pp and (px,py) in structure:
  for( unsigned i = 0; i < p.size(); i++ ){
    // printf("%f %f %f %f\n", p[i].x, p[i].y, p[i].u, p[i].v);
    s_homography->s_plane_object->px[i] = p[i].x;
    s_homography->s_plane_object->py[i] = p[i].y;
    CvMat *plane_point = cvCreateMat( 3, 1, CV_64FC1 );
    cvmSet( plane_point, 0, 0, p[i].u );
    cvmSet( plane_point, 1, 0, p[i].v );
    cvmSet( plane_point, 2, 0, 1      );
    s_homography->s_plane_object->v_m_pp.push_back( plane_point );
  }

  // Tell point number:
  s_homography->s_plane_object->p = p.size();

  // Push the homography to the vector:
  v_camera[c]->v_homography.push_back( s_homography );

  // Create homography from m_pp and (px,py) in structure:
  CreateWorldPlaneHomography( c, (int)v_camera[c]->v_homography.size()-1, ready );
  return true;
}

bool CamCalibration::StoreHomographiesToFile( char* file_name ){
  FILE *stream;
  char buffer[1000];
  int  length;
  if( (stream = fopen( file_name, "w+t" )) != NULL ){
    for( int c = 0; c < (int)v_camera.size(); c++ ){
      for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ ){
        if( v_camera[c]->v_homography[h]->m_homography ){
          // Camera & Homography & Point number:
          s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;
          int p = (*s_plane_object).p;
          length = sprintf(buffer,"%i %i %i %i %i\n",c,h,p,v_camera[c]->w,v_camera[c]->h);
          fwrite( buffer, sizeof(char), length, stream );
          // Points:
          for( int i = 0; i < p; i++ ){
            double x = (*s_plane_object).px[i];
            double y = (*s_plane_object).py[i];
            double u = cvmGet( (*s_plane_object).v_m_pp[i], 0, 0 );
            double v = cvmGet( (*s_plane_object).v_m_pp[i], 1, 0 );
            length = sprintf(buffer,"%f %f %f %f\n",x,y,u,v);
            fwrite( buffer, sizeof(char), length, stream );
          }
          // Homography:
          homography *m_homography = v_camera[c]->v_homography[h]->m_homography;
          for(int i=0; i < 3; i++) {
            for(int j=0; j < 3; j++) {
              length = sprintf(buffer,"%f ",m_homography->cvmGet(i,j));
              fwrite( buffer, sizeof(char), length, stream );
            }
            length = sprintf(buffer,"\n");
            fwrite( buffer, sizeof(char), length, stream );
          }
        } else {
          length = sprintf(buffer,"%i %i 0 %i %i\n",c,h,v_camera[c]->w,v_camera[c]->h);
          fwrite( buffer, sizeof(char), length, stream );
        }
      }
    }
    printf("\n----------------------------\n");
    printf("Homographies stored to file!\n");
    printf("----------------------------\n\n");
    fclose( stream );
    return true;
  } else 
    return false;
}

bool CamCalibration::LoadHomographiesFromFile( char* file_name ){
  FILE *stream;
  int  curr_cam = -1;
  if( (stream = fopen( file_name, "r+t" )) != NULL ){
    int c,h,p,iw,ih;
    c=-1;h=-1;p=-1;iw=-1;ih=-1;
    while( fscanf( stream, "%i %i %i %i %i\n", &c, &h, &p, &iw, &ih ) != EOF ){
      if( c != curr_cam ){
        curr_cam = c;
        AddCamera( iw, ih );
      }
      if( p > 0 ){
        float x,y,u,v;
        std::vector<CamCalibration::s_struct_points> points;
        for( int i = 0; i < p; i++ ){
          fscanf( stream, "%f %f %f %f\n", &x, &y, &u, &v );
          points.push_back( CamCalibration::s_struct_points(u,v,x,y) );
        }
        // Homography:
        homography*  m_homography = new homography();
        float h;
        for(int i=0; i < 3; i++)
          for(int j=0; j < 3; j++) {
            fscanf( stream, "%f", &h );
            m_homography->cvmSet(i,j,h);
          }
          AddHomography( c, points, m_homography );
      } else
        AddHomography( c );
    }
    fclose( stream );
    return true;
  } else
    return false;
}

std::vector<CamCalibration::s_struct_solution> CamCalibration::GetRandomSolution( int num ){
  std::vector<s_struct_solution> current_solution;
  do {
    // Get random c and h:
    int c,h;
    while ((int)v_camera.size() <= (c = rand()/(RAND_MAX/(int)v_camera.size())) );
    while ((int)v_camera[0]->v_homography.size() <= (h = rand()/(RAND_MAX/(int)v_camera[0]->v_homography.size())) );

    // Check if there is a connection:
    if( v_camera[c]->v_homography[h]->m_homography ){

      // Check if it is already in the vector:
      bool in_vector = false;
      for( int i = 0; i < (int)current_solution.size(); i++ )
        if( current_solution[i].c == c && current_solution[i].h == h )
          in_vector = true;

      // If not already in vector, add element:
      if( !in_vector )
        current_solution.push_back(s_struct_solution(c,h));
    }
  } while( (int)current_solution.size() < num );
  return current_solution;
}

double CamCalibration::GetScreenDistance( int c, int h1, int h2 ){
  // Initialze measure point, projected points & homographies:
  double a_w[] = { 0, 0, 1 }; CvMat m_w = cvMat( 3, 1, CV_64FC1, a_w );
  double a_p1[3]; CvMat m_p1 = cvMat( 3, 1, CV_64FC1, a_p1 );
  double a_p2[3]; CvMat m_p2 = cvMat( 3, 1, CV_64FC1, a_p2 );
  double a_h1[9]; CvMat m_h1 = cvMat( 3, 3, CV_64FC1, a_h1  );
  double a_h2[9]; CvMat m_h2 = cvMat( 3, 3, CV_64FC1, a_h2  );

  // Copy homographies to matrices:
  for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 3; j++ ){
      cvmSet( &m_h1, i, j, cvmGet( v_camera[c]->v_homography[h1]->m_homography, i, j ) );
      cvmSet( &m_h2, i, j, cvmGet( v_camera[c]->v_homography[h2]->m_homography, i, j ) );
    }

    // Project points using the homographies:
    cvMatMul( &m_h1, &m_w, &m_p1 ); HomogenousNormalizeVector( &m_p1 );
    cvMatMul( &m_h2, &m_w, &m_p2 ); HomogenousNormalizeVector( &m_p2 );

    // Return euclidean distance:
    return sqrt( pow(cvmGet(&m_p1,0,0)-cvmGet(&m_p2,0,0),2) + 
      pow(cvmGet(&m_p1,1,0)-cvmGet(&m_p2,1,0),2) );
}

double CamCalibration::GetSolutionQuality( std::vector<s_struct_solution> solution, double p_PreFilter_a, double p_PreFilter_b, double p_PreFilter_c ){
  //////////////////////////////
  // Q1 - Number of points:
  int overall_points = 0;
  for( int c = 0; c < (int)v_camera.size(); c++ )
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
      if( v_camera[c]->v_homography[h]->m_homography )
        overall_points += v_camera[c]->v_homography[h]->s_plane_object->p;

  int solution_points = 0;
  for( int i = 0; i < (int)solution.size(); i++ )
    solution_points += v_camera[solution[i].c]->v_homography[solution[i].h]->s_plane_object->p;

  //TODO: Should be max_points instead of overall_points here:
  double q1 = (double)solution_points/(double)overall_points;

  //////////////////////////////
  // Q2 - Number of connections:
  int overall_connections  = (int)v_camera.size()*(int)v_camera[0]->v_homography.size();
  int solution_connections = 0; 
  for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ ){
    int current_connections = 0;
    for( int i = 0; i < (int)solution.size(); i++ )
      if( solution[i].h == h )
        current_connections++;

    solution_connections += (int)pow((double)current_connections,2.);
  }
  double q2 = (double)solution_connections/(double)overall_connections;

  //////////////////////////////
  // Q3 - Distances:
  double overall_distances  = 0;
  double solution_distances = 0; 
  for( int c = 0; c < (int)v_camera.size(); c++ ){
    int hom_cam_num = 0;
    for( int i = 0; i < (int)solution.size(); i++ )
      if( solution[i].c == c )
        hom_cam_num++;

    double overall_cam_distances  = pow((double)hom_cam_num,2.)*sqrt(pow((double)v_camera[c]->w,2.)+pow((double)v_camera[c]->h,2.));
    double solution_cam_distances = 0;
    for( int i = 0; i < (int)solution.size(); i++ )
      if( solution[i].c == c )
        for( int j = 0; j < (int)solution.size(); j++ )
          if( solution[j].c == c )
            solution_cam_distances += GetScreenDistance(c,solution[i].h,solution[j].h);

    overall_distances  += overall_cam_distances;
    solution_distances += solution_cam_distances;
  }

  double q3 = solution_distances/overall_distances;
  return p_PreFilter_a*q1+p_PreFilter_b*q2+p_PreFilter_c*q3;
}

// Greedy filter:
bool CamCalibration::FilterBestHomographiesGreedyMethod( int num ){
  int cnt = 0;
  printf( "INFO: Starting pre-filtering process, greedy method...\n" );
  for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ )
    for( int c = 0; c < (int)v_camera.size(); c++ )
      if( v_camera[c]->v_homography[h]->m_homography ){
        if( cnt >= num ){
          DeleteWorldPlaneHomography(c,h);
          printf( "INFO: View %i of camera %i has been deleted!\n", h, c );
        }
        cnt++;
      }

      if( cnt < num )
        printf( "WARNING: Only %i homographies available instead of the requested %i ones!\n", cnt, num );

      printf( "INFO: Pre-filtering process finished\n" );
      return true;
}

static void fill_random(int array[],int size)
{
  for (int i=0; i<size; ++i) {
    array[i]=i;
  }
  for (int i=0; i<size; ++i) {
    int n = (size*rand())/RAND_MAX;
    if (n==i) continue;
    if (n<0) n=0;
    if (n>=size) n=size-1;
    int tmp = array[i];
    array[i] = array[n];
    array[n] = tmp;
  }
}

// Padding filter:
bool CamCalibration::FilterBestHomographiesFillingMethod( int num, double p_PreFilter_a ){
  double ratio = p_PreFilter_a; // Ratio of individual and group homographies
  int  cam  = (int)v_camera.size();
  int  min  = (int)floor((double)num/((double)cam*ratio));
  int  cnt  = 0;
  int totalHom = 0;

  // 1. PHASE - retain individual cam homographies:
  for( int c = 0; c < cam; c++ ){   
    int hnum = 0;
    for( unsigned h = 0; h < v_camera[c]->v_homography.size(); h++ )
      if (v_camera[c]->v_homography[h]->m_homography) {
	      v_camera[c]->v_homography[h]->b_discard=true;
	      totalHom++;
      }
    printf("Camera %d: %d homographies\n", c, totalHom);

    for( int i = 0; i < min; i++ ){
      int pmax = 0;
      int hmax = 0;
      // Find discarded homography with most inliers:
      for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
        if( v_camera[c]->v_homography[h]->m_homography             &&
          v_camera[c]->v_homography[h]->s_plane_object->p > pmax &&
          v_camera[c]->v_homography[h]->b_discard                    ){
            pmax = (int)v_camera[c]->v_homography[h]->s_plane_object->p;
            hmax = h;
        }
        // Set this homography to "not discarded":
        if( pmax > 0 ){
          //printf("individuals: %i %i\n",c,hmax);
          v_camera[c]->v_homography[hmax]->b_discard = false;
          cnt++; hnum++;
        }
    }
    // You will need at least 3 individual homographies for calibration:
    if( hnum < 2 ){
      printf( "ERROR: Could not detect >= 2 homographies for camera %i\n", c );
      return false;
    }
  }

  int *random_h = new int [v_camera[0]->v_homography.size()];
  fill_random(random_h,v_camera[0]->v_homography.size());
  // 2. PHASE - fill with group cam homographies:
  for( int i = cam; i > 0; i-- ){
    for( int _h = 0; _h < (int)v_camera[0]->v_homography.size(); _h++ ){
      int h = random_h[_h];
      int con = 0;
      for( int c = 0; c < cam; c++ )
        if( v_camera[c]->v_homography[h]->m_homography )
          con++;
      if( con == i )
        for( int c2 = 0; c2 < cam; c2++ ){
          if( v_camera[c2]->v_homography[h]->m_homography ){
            if( v_camera[c2]->v_homography[h]->b_discard ){
              v_camera[c2]->v_homography[h]->b_discard = false;
              cnt++;
              //printf("multi: %i %i\n",c2,h);
            }
          }
          if( cnt >= num )
            break;
        }
        if( cnt >= num )
          break;
    }
    if( cnt >= num )
      break;
  }

  // Phase 2.5: try every possible pair, just in case we missed some.
  for( int i = 0; i < cam; i++ ){
    for( int j = 0; j < cam; j++ ){
      int taken=0;
      int missed=0;
      for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ ) {
        if (v_camera[i]->v_homography[h]->m_homography 
          && v_camera[j]->v_homography[h]->m_homography) {
            if (!v_camera[i]->v_homography[h]->b_discard
              && !v_camera[j]->v_homography[h]->b_discard)
              taken++;
            else
              missed++;
        }
      }
      if (taken > 5 || missed ==0) continue;
      int required = imin(missed,5);
      for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ ) {
        if (v_camera[i]->v_homography[h]->m_homography 
          && v_camera[j]->v_homography[h]->m_homography) {
            if (v_camera[i]->v_homography[h]->b_discard
              || v_camera[j]->v_homography[h]->b_discard) 
            {
              v_camera[i]->v_homography[h]->b_discard=false;
              v_camera[j]->v_homography[h]->b_discard=false;
              if (--required==0) break;
            }
        }
      }
    }
  }

  // 3. PHASE - discard unused homographies:
  for( int c = 0; c < cam; c++ )
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
      if( v_camera[c]->v_homography[h]->m_homography && 
        v_camera[c]->v_homography[h]->b_discard       )
        DeleteWorldPlaneHomography(c,h);

  // ensure we did not intensionally drop connectivity
  for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ ) {
    bool taken=false;
    for( int c = 0; c < cam; c++ ) {
      taken = taken || (v_camera[c]->v_homography[h]->m_homography &&
        !v_camera[c]->v_homography[h]->b_discard);
    }
    if (taken)
      for( int c = 0; c < cam; c++ ) {
        if (v_camera[c]->v_homography[h]->m_homography && v_camera[c]->v_homography[h]->b_discard) {
          v_camera[c]->v_homography[h]->b_discard=false;
          cnt++;
        }
      }
  }

  // Return true only if homography number is sufficient:
  if( cnt >= num ) {
    printf( "Selected %d homographies out of %d. Minimum was: %d\n", cnt, totalHom, num );
    return true;
  } else {
    printf( "ERROR: Only %i homographies available instead of the requested %i ones!\n", cnt, num );
    return false;
  }
}

bool CamCalibration::FilterBestHomographiesRandomMethod( int num, int p_Solutions, double p_PreFilter_a, double p_PreFilter_b, double p_PreFilter_c  ){

  int hom_num = 0;

  // 1. PHASE - count all homographies:
  for( int c = 0; c < (int)v_camera.size(); c++ )
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
      if( v_camera[c]->v_homography[h]->m_homography )
        hom_num++;

  // If not enough homographies available, print error message:
  if( num > hom_num ){
    printf( "ERROR: Only %i homographies available instead of the requested %i ones!\n", hom_num, num );
    return false;
  } else
    printf( "Filtering %i homographies out of %i ones ...\n", num, hom_num );

  // 2. PHASE - create random solutions and take best one:
  std::vector<s_struct_solution> best_solution;
  double best_quality = 0;
  for( int i = 0; i < p_Solutions; i++ ){
    std::vector<s_struct_solution> current_solution = GetRandomSolution( num );
    printf("Solution %i, ",i);

    double current_quality = GetSolutionQuality( current_solution, p_PreFilter_a, p_PreFilter_b, p_PreFilter_c  );
    printf("quality: %f",current_quality);
    if( current_quality > best_quality ){
      best_solution = current_solution;
      best_quality  = current_quality;
    }
    printf("best: %f",best_quality);
    printf("\n");
  }

  // 3. PHASE - filter best Solutions:
  int deleted = 0;
  for( int c = 0; c < (int)v_camera.size(); c++ )
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
      if( v_camera[c]->v_homography[h]->m_homography ){    
        bool del_hom = true;

        // Search in best solution if homography is there:
        for( int i = 0; i < (int)best_solution.size(); i++ )
          if( c == best_solution[i].c && h == best_solution[i].h )
            del_hom = false;

        if( del_hom ){
          DeleteWorldPlaneHomography(c,h);
          deleted++;
        }
      }

      return true;
}

bool CamCalibration::Calibrate( int p_HomographyNum, int p_PreFilter, int p_Solutions, double p_PreFilter_a, double p_PreFilter_b, double p_PreFilter_c,
                               double p_InitialGuess_a, double p_InitialGuess_b, double p_InitialGuess_c,
                               int p_Iterations, double p_Epsilon, double p_PostFilter ){

                                 // Starting values for statistics:
                                 stat_HomographyNum = p_HomographyNum;
                                 stat_ExpStartTime  = time(0);

                                 bool filter_ok;
                                 switch( p_PreFilter ){
    case  0: filter_ok = FilterBestHomographiesGreedyMethod ( p_HomographyNum );  break;
    case  1: filter_ok = FilterBestHomographiesFillingMethod( p_HomographyNum, p_PreFilter_a ); break; 
    case  2: filter_ok = FilterBestHomographiesRandomMethod ( p_HomographyNum, p_Solutions, p_PreFilter_a, p_PreFilter_b, p_PreFilter_c );  break;
    default: filter_ok = FilterBestHomographiesFillingMethod( p_HomographyNum, p_PreFilter_a ); break;
                                 }

                                 if( !filter_ok ){
                                   printf("ERROR: Homography filtering process failed!\n");
                                   return false;
                                 }

                                 // Perform initial guess:
                                 for( int c = 0; c < (int)v_camera.size(); c++ ){
                                   if( !ExtractIntrinsicParameters( c, p_InitialGuess_a, p_InitialGuess_b, p_InitialGuess_c ) ){
                                     printf("ERROR: Extraction of intrinsic parameters of camera %i failed!\n",c);
                                     return false;
                                   }
                                   CreateEstimatedCalibrationMatrixFromEstimatedIntrinsicParameters( c );
                                   CreateEstimatedInverseCalibrationMatrixFromEstimatedIntrinsicParameters( c );
                                   CreateAllRotationTranslationMatrices( c );
                                 }

                                 // Do optimization:
                                 if( OptimizeCalibrationByMinimalParameterMethod( p_Iterations, p_Epsilon, p_PostFilter ) ){
                                   return true;
                                 } else
                                   return false;
}

void CamCalibration::PrintStatisticToFile(){
  FILE * stat;
  stat = fopen( "stat.txt", "a" );
  fprintf( stat, "%i %ld", stat_HomographyNum, time(0)-stat_ExpStartTime);
  for( int i = 0; i < (int)v_camera.size(); i++ )
    for( int j = 0; j < 4; j++ )
      fprintf( stat, " %f", v_opt_param[i*4+j] );
  fprintf( stat, "\n" );
  printf("Statistic has successfully been saved!\n");
  fclose( stat );
}

void CamCalibration::CreateAllRotationTranslationMatrices( int c ){
  for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
    if( v_camera[c]->v_homography[h]->m_homography )
      CreateRotationTranslationMatrixFromInverseCalibrationMatrixAndHomography( c, h );
}

CvMat* CamCalibration::GetM( enum matrix_desc desc, int c, int h ){
  switch( desc ){
    case m_calibration: return v_camera[c]->m_calibration_matrix;
    case m_rot_trans  : return v_camera[c]->m_rot_trans_matrix;
    case m_estim_calib: return v_camera[c]->m_estim_calib_matrix;
    case m_estinvcalib: return v_camera[c]->m_estinvcalib_matrix;
    case m_estim_r_t  : return v_camera[c]->v_homography[h]->m_estim_r_t_matrix;
    case m_jacobian   : return v_camera[c]->v_homography[h]->m_jacobian_matrix;\
    default     : return NULL;
  }
}

double CamCalibration::GetRandomValue( double min, double max ){
  double delta = max - min;
  double value = (double)rand()/(double)RAND_MAX;
  return min + delta*value; 
}

// Box-Muller method:
void CamCalibration::AddGaussianNoise( CvMat* mat, double noise ){
  double u1 = GetRandomValue( 0, 1 );
  double u2 = GetRandomValue( 0, 1 );
  cvmSet( mat, 0, 0, cvmGet( mat, 0, 0 ) + noise*sqrt(-2.00*log(u1))*cos(2*M_PI*u2) );
  cvmSet( mat, 1, 0, cvmGet( mat, 1, 0 ) + noise*sqrt(-2.00*log(u1))*sin(2*M_PI*u2) );
}

void CamCalibration::HomogenousNormalizeVector( CvMat* mat ){
  if( cvGetDimSize( mat, 0 ) > 1 ){
    double d = cvmGet( mat, cvGetDimSize( mat, 0 )-1, 0 );
    if( d != 0 )
      for( int i = 0; i < cvGetDimSize( mat, 0 ); i++ )
        cvmSet( mat, i, 0, cvmGet( mat, i, 0 )/d );
  } else {
    double d = cvmGet( mat, 0, cvGetDimSize( mat, 1 )-1 );
    if( d != 0 )
      for( int i = 0; i < cvGetDimSize( mat, 1 ); i++ )
        cvmSet( mat, 0, i, cvmGet( mat, 0, i )/d );
  }
}

void CamCalibration::SetIntrinsicParam( int c, double f, double a, double u, double v ){
  v_camera[c]->s_intrinsic.focal = f;
  v_camera[c]->s_intrinsic.aspect = a;
  v_camera[c]->s_intrinsic.u0  = u;
  v_camera[c]->s_intrinsic.v0  = v;
}

void CamCalibration::SetPlaneObject( int c, int h, int p, double px[], double py[],
                                    double rx, double ry, double rz, double tx, double ty, double tz ){
                                      // Get pointer:
                                      s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;

                                      // Delete old data if necessary:
                                      if( (*s_plane_object).px   ) delete (*s_plane_object).px;
                                      if( (*s_plane_object).py   ) delete (*s_plane_object).py;
                                      if( (*s_plane_object).v_m_wp.size() > 0 ){
                                        for( int i = 0; i < (int)(*s_plane_object).v_m_wp.size(); i++ )
                                          cvReleaseMat( &(*s_plane_object).v_m_wp[i] );
                                        (*s_plane_object).v_m_wp.clear();
                                      }
                                      if( (*s_plane_object).v_m_pp.size() > 0 ){
                                        for( int i = 0; i < (*s_plane_object).p; i++ )
                                          cvReleaseMat( &(*s_plane_object).v_m_pp[i] );
                                        (*s_plane_object).v_m_pp.clear();
                                      }

                                      // Create new sized data structures:
                                      (*s_plane_object).px   = new double[p];
                                      (*s_plane_object).py   = new double[p];
                                      for( int i = 0; i < p; i++ ){
                                        (*s_plane_object).v_m_wp.push_back(cvCreateMat( 4, 1, CV_64FC1 ));
                                        (*s_plane_object).v_m_pp.push_back(cvCreateMat( 3, 1, CV_64FC1 ));
                                      }

                                      // Set plane number:
                                      (*s_plane_object).p = p;

                                      // Set x/y coordinates on plane:
                                      for( int i = 0; i < p; i++ ){
                                        (*s_plane_object).px[i] = px[i];
                                        (*s_plane_object).py[i] = py[i];
                                      }

                                      // Set rotation translation:
                                      (*s_plane_object).rx = rx;
                                      (*s_plane_object).ry = ry;
                                      (*s_plane_object).rz = rz;
                                      (*s_plane_object).tx = tx;
                                      (*s_plane_object).ty = ty;
                                      (*s_plane_object).tz = tz;
}

void CamCalibration::Translate3DVector( CvMat* v, double x, double y, double z ){
  double a_T[] = { 1, 0, 0, -x,
    0, 1, 0, -y,
    0, 0, 1, -z,
    0, 0, 0,  1 };
  CvMat m_T  = cvMat( 4, 4, CV_64FC1, a_T );
  cvMatMul( &m_T, v, v );
}

void CamCalibration::Rotate3DVector( CvMat* v, double x, double y, double z ){
  x *= 2*M_PI/360.00;
  y *= 2*M_PI/360.00;
  z *= 2*M_PI/360.00;
  double a_Rx[] = {   1,    0,    0, 0,
    0,  cos(x), -sin(x), 0,
    0,  sin(x),  cos(x), 0, 
    0,    0,    0, 1 };
  double a_Ry[] = { cos(y),    0, -sin(y), 0,
    0,    1,    0, 0,
    sin(y),    0,  cos(y), 0,
    0,    0,    0, 1 };
  double a_Rz[] = { cos(z), -sin(z),    0, 0,
    sin(z),  cos(z),    0, 0,
    0,    0,       1, 0,
    0,    0,     0, 1 };
  CvMat m_Rx = cvMat( 4, 4, CV_64FC1, a_Rx );
  CvMat m_Ry = cvMat( 4, 4, CV_64FC1, a_Ry );
  CvMat m_Rz = cvMat( 4, 4, CV_64FC1, a_Rz );
  cvMatMul( &m_Rx, v, v );
  cvMatMul( &m_Ry, v, v );
  cvMatMul( &m_Rz, v, v );
}

void CamCalibration::ExtractRotationTranslationFrom3x4Matrix( CvMat* RotTrans , CvMat* Rot, CvMat*Trans ){
  if( Rot != NULL ){
    cvmSet(   Rot, 0, 0, cvmGet( RotTrans, 0, 0 ) );
    cvmSet(   Rot, 0, 1, cvmGet( RotTrans, 0, 1 ) );
    cvmSet(   Rot, 0, 2, cvmGet( RotTrans, 0, 2 ) );
    cvmSet(   Rot, 1, 0, cvmGet( RotTrans, 1, 0 ) );
    cvmSet(   Rot, 1, 1, cvmGet( RotTrans, 1, 1 ) );
    cvmSet(   Rot, 1, 2, cvmGet( RotTrans, 1, 2 ) );
    cvmSet(   Rot, 2, 0, cvmGet( RotTrans, 2, 0 ) );
    cvmSet(   Rot, 2, 1, cvmGet( RotTrans, 2, 1 ) );
    cvmSet(   Rot, 2, 2, cvmGet( RotTrans, 2, 2 ) );
  }
  if( Trans != NULL ){
    cvmSet( Trans, 0, 0, -cvmGet( RotTrans, 0, 3 ) );
    cvmSet( Trans, 1, 0, -cvmGet( RotTrans, 1, 3 ) );
    cvmSet( Trans, 2, 0, -cvmGet( RotTrans, 2, 3 ) );
  }
}

void CamCalibration::ComposeRotationTranslationTo3x4Matrix( CvMat* RotTrans , CvMat* Rot, CvMat*Trans ){
  cvmSet( RotTrans, 0, 0, cvmGet( Rot, 0, 0 ) );
  cvmSet( RotTrans, 0, 1, cvmGet( Rot, 0, 1 ) );
  cvmSet( RotTrans, 0, 2, cvmGet( Rot, 0, 2 ) );
  cvmSet( RotTrans, 1, 0, cvmGet( Rot, 1, 0 ) );
  cvmSet( RotTrans, 1, 1, cvmGet( Rot, 1, 1 ) );
  cvmSet( RotTrans, 1, 2, cvmGet( Rot, 1, 2 ) );
  cvmSet( RotTrans, 2, 0, cvmGet( Rot, 2, 0 ) );
  cvmSet( RotTrans, 2, 1, cvmGet( Rot, 2, 1 ) );
  cvmSet( RotTrans, 2, 2, cvmGet( Rot, 2, 2 ) );
  cvmSet( RotTrans, 0, 3, -cvmGet( Trans, 0, 0 ) );
  cvmSet( RotTrans, 1, 3, -cvmGet( Trans, 1, 0 ) );
  cvmSet( RotTrans, 2, 3, -cvmGet( Trans, 2, 0 ) );
}

void CamCalibration::Mat3x4ToMat4x4( CvMat* m_A, CvMat* m_B ){
  for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 4; j++ )
      cvmSet( m_B, i, j, cvmGet( m_A, i, j ) );
  cvmSet( m_B, 3, 0, 0 );
  cvmSet( m_B, 3, 1, 0 );
  cvmSet( m_B, 3, 2, 0 );
  cvmSet( m_B, 3, 3, 1 );
}

void CamCalibration::Mat4x4ToMat3x4( CvMat* m_A, CvMat* m_B ){
  for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 4; j++ )
      cvmSet( m_B, i, j, cvmGet( m_A, i, j ) );
}

void CamCalibration::Mat3x4Mul( CvMat* m_A, CvMat* m_B, CvMat* m_C ){
  double a_A2[16]; CvMat m_A2 = cvMat( 4, 4, CV_64FC1, a_A2 );
  double a_B2[16]; CvMat m_B2 = cvMat( 4, 4, CV_64FC1, a_B2 );
  double a_C2[16]; CvMat m_C2 = cvMat( 4, 4, CV_64FC1, a_C2 );
  Mat3x4ToMat4x4( m_A, &m_A2 );
  Mat3x4ToMat4x4( m_B, &m_B2 );
  cvMatMul( &m_A2, &m_B2, &m_C2 );
  Mat4x4ToMat3x4( &m_C2, m_C );
}

void CamCalibration::Mat3x4Inverse( CvMat* m_A, CvMat* m_B ){
  double a_R[9]; CvMat m_R = cvMat( 3, 3, CV_64FC1, a_R );
  double a_T[3]; CvMat m_T = cvMat( 3, 1, CV_64FC1, a_T );
  ExtractRotationTranslationFrom3x4Matrix( m_A, &m_R, &m_T );
  cvTranspose( &m_R, &m_R );
  cvGEMM( &m_R, &m_T, -1.00, NULL, +1.00, &m_T, 0 );
  ComposeRotationTranslationTo3x4Matrix( m_B, &m_R, &m_T );
}

void CamCalibration::CreatePlaneObjectWorldPoints( int c, int h ){
  s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;
  for( int i = 0; i < (*s_plane_object).p; i++ ){

    // Create Point in plane Z=0:
    cvmSet( (*s_plane_object).v_m_wp[i], 0, 0, (*s_plane_object).px[i] );
    cvmSet( (*s_plane_object).v_m_wp[i], 1, 0, (*s_plane_object).py[i] );
    cvmSet( (*s_plane_object).v_m_wp[i], 2, 0, 0.0                     );
    cvmSet( (*s_plane_object).v_m_wp[i], 3, 0, 1.0                     );

    // Translate and Rotate the Point to its World Position:
    Rotate3DVector   (  (*s_plane_object).v_m_wp[i], 
      (*s_plane_object).rx,
      (*s_plane_object).ry,
      (*s_plane_object).rz      );

    Translate3DVector(  (*s_plane_object).v_m_wp[i], 
      (*s_plane_object).tx,
      (*s_plane_object).ty,
      (*s_plane_object).tz      );
  }
}

void CamCalibration::CreatePlaneObjectPlanePoints( int c, int h, double noise ){
  s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;
  for( int i = 0; i < (*s_plane_object).p; i++ ){
    double a_P[12]; CvMat m_P = cvMat( 3, 4, CV_64FC1, a_P );
    cvMatMul( GetM(m_calibration,c,h), GetM(m_rot_trans,c,h), &m_P );
    cvMatMul( &m_P, (*s_plane_object).v_m_wp[i], (*s_plane_object).v_m_pp[i] );
    HomogenousNormalizeVector( (*s_plane_object).v_m_pp[i] );
    AddGaussianNoise( (*s_plane_object).v_m_pp[i], noise );
  }
}

void CamCalibration::CreateWorldPlaneHomography( int c, int h, CvMat *ready ){
  s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;

  homography* m_homography = v_camera[c]->v_homography[h]->m_homography = new homography();
  if (ready){
    cvCopy(ready, m_homography);
  } else {
    m_homography->set_match_number( (*s_plane_object).p );

    for( int i = 0; i < (*s_plane_object).p; i++ ){
      HomogenousNormalizeVector( (*s_plane_object).v_m_pp[i] );
      m_homography->add_match( (float)(*s_plane_object).px[i],
                               (float)(*s_plane_object).py[i],
                               (float)cvmGet( (*s_plane_object).v_m_pp[i], 0, 0 ),
                               (float)cvmGet( (*s_plane_object).v_m_pp[i], 1, 0 ) );
    }
    m_homography->estimate();
    m_homography->release_matches();
  }
}

double CamCalibration::VectorAngle( CvMat* v1, CvMat* v2, CvMat* v3, CvMat* v4 ){
  double x1 = cvmGet( v2, 0, 0 ) - cvmGet( v1, 0, 0 );
  double y1 = cvmGet( v2, 1, 0 ) - cvmGet( v1, 1, 0 );
  double x2 = cvmGet( v4, 0, 0 ) - cvmGet( v3, 0, 0 );
  double y2 = cvmGet( v4, 1, 0 ) - cvmGet( v3, 1, 0 );
  double a  = x1*x2+y1*y2;
  double b  = sqrt(pow(x1,2)+pow(y1,2)) * sqrt(pow(x2,2)+pow(y2,2));
  if( b != 0 )
    return acos(a/b);
  else
    return 0;
}

double CamCalibration::PointDistance( CvMat* v1, CvMat* v2 ){
  double x = cvmGet( v2, 0, 0 ) - cvmGet( v1, 0, 0 );
  double y = cvmGet( v2, 1, 0 ) - cvmGet( v1, 1, 0 );
  return sqrt(pow(x,2)+pow(y,2));
}

void CamCalibration::DeleteWorldPlaneHomography( int c, int h ){
  delete v_camera[c]->v_homography[h]->m_homography;
  v_camera[c]->v_homography[h]->m_homography = NULL;
}

bool CamCalibration::HomographySingular( int c, int h, double p_InitialGuess_a, double p_InitialGuess_b, double p_InitialGuess_c ){

  // Initialze 4 standard measure points:
  double a_w1[] = { -1, -1, 1 }; CvMat m_w1 = cvMat( 3, 1, CV_64FC1, a_w1 );
  double a_w2[] = { -1,  1, 1 }; CvMat m_w2 = cvMat( 3, 1, CV_64FC1, a_w2 );
  double a_w3[] = {  1,  1, 1 }; CvMat m_w3 = cvMat( 3, 1, CV_64FC1, a_w3 );
  double a_w4[] = {  1, -1, 1 }; CvMat m_w4 = cvMat( 3, 1, CV_64FC1, a_w4 );
  double a_p1[3]; CvMat m_p1 = cvMat( 3, 1, CV_64FC1, a_p1 );
  double a_p2[3]; CvMat m_p2 = cvMat( 3, 1, CV_64FC1, a_p2 );
  double a_p3[3]; CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 );
  double a_p4[3]; CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 );
  double a_h[9];  CvMat m_h  = cvMat( 3, 3, CV_64FC1, a_h  );

  // Copy homography to matrix:
  for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 3; j++ )
      cvmSet( &m_h, i, j, cvmGet( v_camera[c]->v_homography[h]->m_homography, i, j ) );

  // Project points using the homography:
  cvMatMul( &m_h, &m_w1, &m_p1 ); HomogenousNormalizeVector( &m_p1 );
  cvMatMul( &m_h, &m_w2, &m_p2 ); HomogenousNormalizeVector( &m_p2 );
  cvMatMul( &m_h, &m_w3, &m_p3 ); HomogenousNormalizeVector( &m_p3 );
  cvMatMul( &m_h, &m_w4, &m_p4 ); HomogenousNormalizeVector( &m_p4 );

  // Check for correct angles:
  double a1 = VectorAngle( &m_p1, &m_p4, &m_p1, &m_p2 );
  double a2 = VectorAngle( &m_p2, &m_p3, &m_p2, &m_p1 );
  double a3 = VectorAngle( &m_p3, &m_p4, &m_p3, &m_p2 );
  double a4 = VectorAngle( &m_p4, &m_p1, &m_p4, &m_p3 );
  double e1 = p_InitialGuess_a;
  double e2 = p_InitialGuess_b;
  if( a1 < e2 || (a1 > (M_PI/2.00) - e1 && a1 < (M_PI/2.00) + e1) || a1 > M_PI - e2 || 
    a2 < e2 || (a2 > (M_PI/2.00) - e1 && a2 < (M_PI/2.00) + e1) || a2 > M_PI - e2 || 
    a3 < e2 || (a3 > (M_PI/2.00) - e1 && a3 < (M_PI/2.00) + e1) || a3 > M_PI - e2 || 
    a4 < e2 || (a4 > (M_PI/2.00) - e1 && a4 < (M_PI/2.00) + e1) || a4 > M_PI - e2   ){
      return true;
  }

  // Check for correct distances:
  double d1 = PointDistance( &m_p1, &m_p2 );
  double d2 = PointDistance( &m_p2, &m_p3 );
  double d3 = PointDistance( &m_p3, &m_p4 );
  double d4 = PointDistance( &m_p4, &m_p1 );
  double d5 = (d1+d2+d3+d4)/4.00;
  double e3 = p_InitialGuess_c;
  if( d1 < d5*e3 || d2 < d5*e3 || d3 < d5*e3 || d4 < d5*e3 ){
    return true;
  }

  return false;
}

double CamCalibration::GetFrobeniusDistance( int c, int h1, int h2 ){

  // First normalize to get comparable values:
  double na = 0;
  double nb = 0;
  for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 3; j++ ){
      na += pow(cvmGet( v_camera[c]->v_homography[h1]->m_homography, i, j ),2);
      nb += pow(cvmGet( v_camera[c]->v_homography[h2]->m_homography, i, j ),2);
    }
    na /= 10000.00;
    nb /= 10000.00;

    // Then build Frobenius norm:
    double sum = 0;
    for( int i = 0; i < 3; i++ )
      for( int j = 0; j < 3; j++ ){
        double a = cvmGet( v_camera[c]->v_homography[h1]->m_homography, i, j )/na;
        double b = cvmGet( v_camera[c]->v_homography[h2]->m_homography, i, j )/nb;
        sum += pow( a - b, 2 );
      }
      return sum;
}

bool CamCalibration::GetDistalHomographiesForCalibration( int c, int *h1, int *h2 ){
  double dist = 0;
  for( int i = 0; i < (int)v_camera[c]->v_homography.size(); i++ )
    for( int j = 0; j < (int)v_camera[c]->v_homography.size(); j++ )
      if( v_camera[c]->v_homography[i]->m_homography &&
        v_camera[c]->v_homography[j]->m_homography    ){
          double dnew = GetFrobeniusDistance( c, i, j );
          if( dnew > dist ){
            dist = dnew;
            *h1  = i;
            *h2  = j;
          }
      }

      if( dist > 0 )
        return true;
      else
        return false;
}

bool CamCalibration::ExtractIntrinsicParameters( int c, double p_InitialGuess_a, double p_InitialGuess_b, double p_InitialGuess_c ){
  int homs = 0;
  for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
    if( v_camera[c]->v_homography[h]->m_homography )
      if( !HomographySingular( c, h, p_InitialGuess_a, p_InitialGuess_b, p_InitialGuess_c ) )
        homs++;

  // Check if enough homographies to calculate intrinsic parameters:
  if( homs < 2 ){
    printf( "ERROR: Could not extract intrinsic parameters of camera %i\n", c );
    printf( "       because there are fewer than 2 views available!\n" );
    return false;
  }

  int rows_of_a = 2*homs;
  CvMat* m_A = cvCreateMat( rows_of_a, 4, CV_64FC1 );
  CvMat* m_X = cvCreateMat(         4, 1, CV_64FC1 );
  CvMat* m_B = cvCreateMat( rows_of_a, 1, CV_64FC1 );

  homs = 0;
  for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
    if( v_camera[c]->v_homography[h]->m_homography )
      if( !HomographySingular( c, h, p_InitialGuess_a, p_InitialGuess_b, p_InitialGuess_c ) ){

        // Get pointer:
        homography* m_homography = v_camera[c]->v_homography[h]->m_homography;

        double v_h11 = m_homography->cvmGet( 0, 0 );
        double v_h12 = m_homography->cvmGet( 0, 1 );
        double v_h21 = m_homography->cvmGet( 1, 0 );
        double v_h22 = m_homography->cvmGet( 1, 1 );
        double v_h31 = m_homography->cvmGet( 2, 0 );
        double v_h32 = m_homography->cvmGet( 2, 1 );

        // First row:
        cvmSet( m_A, homs*2,   0, (pow(v_h21,2)-pow(v_h22,2)  ));
        cvmSet( m_A, homs*2,   1, 2*( v_h11*v_h31-v_h12*v_h32 ));
        cvmSet( m_A, homs*2,   2, 2*( v_h21*v_h31-v_h22*v_h32 ));
        cvmSet( m_A, homs*2,   3, (pow(v_h31,2)-pow(v_h32,2) ));
        cvmSet( m_B, homs*2,   0, (pow(v_h12,2)-pow(v_h11,2) ));

        // Second row:
        cvmSet( m_A, homs*2+1, 0, (v_h22*v_h21 )      );
        cvmSet( m_A, homs*2+1, 1, (v_h11*v_h32 + v_h12*v_h31 ));
        cvmSet( m_A, homs*2+1, 2, (v_h32*v_h21 + v_h22*v_h31 ));
        cvmSet( m_A, homs*2+1, 3, (v_h32*v_h31)    );
        cvmSet( m_B, homs*2+1, 0, (-v_h11*v_h12)    );

        homs++;
      }

      // Solve least squares
      cvSolve( m_A, m_B, m_X, CV_SVD );

      // Grab omegas out of X
      double v_w22 = cvmGet( m_X, 0, 0 );
      double v_w13 = cvmGet( m_X, 1, 0 );
      double v_w23 = cvmGet( m_X, 2, 0 );
      double v_w33 = cvmGet( m_X, 3, 0 );

      // Release temporary matices:
      cvReleaseMat( &m_A );
      cvReleaseMat( &m_X );
      cvReleaseMat( &m_B );

      // Set the estimated intrinsic parameters if possible:
      double f2 = (v_w22*v_w33-v_w22*pow(v_w13,2)-pow(v_w23,2))/pow(v_w22,2);
      double a2 =  v_w22;
      if( a2 < 0 || f2 < 0 ){
        printf("ERROR: Intrinsic parameters of camera %i could not be estimated (complex values)!\n",c);
        return false;
      }

      // Assign results:
      v_camera[c]->s_estim_int.focal  =   sqrt(f2);
      v_camera[c]->s_estim_int.aspect =   sqrt(a2);
      v_camera[c]->s_estim_int.u0  =  -v_w13;
      v_camera[c]->s_estim_int.v0  =  -v_w23/v_w22;

      printf( "Estimated camera %i (%03d views): %f %f %f %f\n", c, homs,
        v_camera[c]->s_estim_int.focal, v_camera[c]->s_estim_int.aspect,
        v_camera[c]->s_estim_int.u0, v_camera[c]->s_estim_int.v0   );

      return true;
}

/*
void CamCalibration::ExtractIntrinsicParameters( int c, int h1, int h2 ){
int rows_of_a = 2*2;

CvMat* m_A = cvCreateMat( rows_of_a, 4, CV_64FC1 );
CvMat* m_X = cvCreateMat(         4, 1, CV_64FC1 );
CvMat* m_B = cvCreateMat( rows_of_a, 1, CV_64FC1 );

for( int h = 0; h < 2; h++ ){
// Get the homography number (of first or second):
int hom = h1;
if( h == 1 ) hom = h2; 

// Get pointer:
homography* m_homography = v_camera[c]->v_homography[hom]->m_homography;

double v_h11 = m_homography->cvmGet( 0, 0 );
double v_h12 = m_homography->cvmGet( 0, 1 );
double v_h21 = m_homography->cvmGet( 1, 0 );
double v_h22 = m_homography->cvmGet( 1, 1 );
double v_h31 = m_homography->cvmGet( 2, 0 );
double v_h32 = m_homography->cvmGet( 2, 1 );

// First row:
cvmSet( m_A, h*2,   0, (pow(v_h21,2)-pow(v_h22,2)));
cvmSet( m_A, h*2,   1, 2*( v_h11*v_h31-v_h12*v_h32 ));
cvmSet( m_A, h*2,   2, 2*( v_h21*v_h31-v_h22*v_h32 ));
cvmSet( m_A, h*2,   3, (pow(v_h31,2)-pow(v_h32,2) ));
cvmSet( m_B, h*2,   0, (pow(v_h12,2)-pow(v_h11,2) ));

// Second row:
cvmSet( m_A, h*2+1, 0, (v_h22*v_h21 )      );
cvmSet( m_A, h*2+1, 1, (v_h11*v_h32 + v_h12*v_h31 ));
cvmSet( m_A, h*2+1, 2, (v_h32*v_h21 + v_h22*v_h31 ));
cvmSet( m_A, h*2+1, 3, (v_h32*v_h31)    );
cvmSet( m_B, h*2+1, 0, (-v_h11*v_h12)    );
}

// Solve least squares
cvSolve( m_A, m_B, m_X, CV_SVD );

// Grab omegas out of X
double v_w22 = cvmGet( m_X, 0, 0 );
double v_w13 = cvmGet( m_X, 1, 0 );
double v_w23 = cvmGet( m_X, 2, 0 );
double v_w33 = cvmGet( m_X, 3, 0 );

// Set the estimated intrinsic parameters if possible:
double f2 = (v_w22*v_w33-v_w22*pow(v_w13,2)-pow(v_w23,2))/pow(v_w22,2);
double a2 =  v_w22;
if( a2 < 0 || f2 < 0 ){
printf("ERROR: Intrinsic parameters of camera %i could not be estimated (complex values)!\n",c);
return false; // complex value
}
v_camera[c]->s_estim_int.focal  =   sqrt(f2);
v_camera[c]->s_estim_int.aspect =   sqrt(a2);
v_camera[c]->s_estim_int.u0  =  -v_w13;
v_camera[c]->s_estim_int.v0  =  -v_w23/v_w22;

// Realease temporary matices:
cvReleaseMat( &m_A );
cvReleaseMat( &m_X );
cvReleaseMat( &m_B );
}*/

/*
bool CamCalibration::ExtractIntrinsicParameters( int c ){

int homs = 0;
for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
if( v_camera[c]->v_homography[h]->m_homography )
homs++;

// Check if enough homographies to calculate intrinsic parameters:
if( homs < 2 ){
printf( "ERROR: Could not extract intrinsic parameters of camera %i\n", c );
printf( "       because there are fewer than 2 views available!\n" );
return false;
}

int rows_of_a = 2*homs;
CvMat* m_A   = cvCreateMat( rows_of_a, 5, CV_64FC1 );
CvMat* m_ATA = cvCreateMat(         5, 5, CV_64FC1 );
CvMat* m_EVA = cvCreateMat(         5, 1, CV_64FC1 );
CvMat* m_EVE = cvCreateMat(         5, 5, CV_64FC1 );

homs = 0;
for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
if( v_camera[c]->v_homography[h]->m_homography ){
// Get pointer:
homography* m_homography = v_camera[c]->v_homography[h]->m_homography;

double v_h11 = m_homography->cvmGet( 0, 0 );
double v_h12 = m_homography->cvmGet( 0, 1 );
double v_h21 = m_homography->cvmGet( 1, 0 );
double v_h22 = m_homography->cvmGet( 1, 1 );
double v_h31 = m_homography->cvmGet( 2, 0 );
double v_h32 = m_homography->cvmGet( 2, 1 );

// First row:
cvmSet( m_A, homs*2,   0, pow(v_h11,2)-pow(v_h12,2)     );
cvmSet( m_A, homs*2,   1, pow(v_h21,2)-pow(v_h22,2)     );
cvmSet( m_A, homs*2,   2, 2*( v_h11*v_h31-v_h12*v_h32 ) );
cvmSet( m_A, homs*2,   3, 2*( v_h21*v_h31-v_h22*v_h32 ) );
cvmSet( m_A, homs*2,   4, pow(v_h31,2)-pow(v_h32,2)     );

// Second row:
cvmSet( m_A, homs*2+1, 0, v_h11*v_h12         );
cvmSet( m_A, homs*2+1, 1, v_h22*v_h21         );
cvmSet( m_A, homs*2+1, 2, v_h11*v_h32 + v_h12*v_h31 );
cvmSet( m_A, homs*2+1, 3, v_h32*v_h21 + v_h22*v_h31 );
cvmSet( m_A, homs*2+1, 4, v_h32*v_h31        );

homs++;
}

// Get Eigenvectors:
cvGEMM( m_A, m_A, 1, NULL, 0, m_ATA, CV_GEMM_A_T );
cvEigenVV( m_ATA, m_EVE, m_EVA, DBL_EPSILON ); 


// Grab omegas out of X
double v_w11 = cvmGet( m_EVE, 4, 0 );
double v_w22 = cvmGet( m_EVE, 4, 1 );
double v_w13 = cvmGet( m_EVE, 4, 2 );
double v_w23 = cvmGet( m_EVE, 4, 3 );
double v_w33 = cvmGet( m_EVE, 4, 4 );

// Set the estimated intrinsic parameters if possible:
double f2 = (v_w11*v_w22*v_w33-v_w22*pow(v_w13,2)-v_w11*pow(v_w23,2))/(v_w11*pow(v_w22,2));
double a2 =  v_w22/v_w11;
if( a2 < 0 || f2 < 0 ){
printf("ERROR: Intrinsic parameters of camera %i could not be estimated (complex values)!\n",c);
return false; // complex value
}

v_camera[c]->s_estim_int.focal  =   sqrt(f2);
v_camera[c]->s_estim_int.aspect =   sqrt(a2);
v_camera[c]->s_estim_int.u0  =  -v_w13/v_w11;
v_camera[c]->s_estim_int.v0  =  -v_w23/v_w22;

// Realease temporary matices:
cvReleaseMat( &m_EVE );
cvReleaseMat( &m_EVA );
cvReleaseMat( &m_ATA );
cvReleaseMat( &m_A   );

printf( "%f %f %f %f\n", v_camera[c]->s_estim_int.focal, v_camera[c]->s_estim_int.aspect, v_camera[c]->s_estim_int.u0, v_camera[c]->s_estim_int.v0 );
if( c == 4)
return false;

return true;
}*/

void CamCalibration::CreateCalibrationMatrixFromIntrinsicParameters( int c ){
  cvmSet( GetM(m_calibration,c,0), 0, 0, v_camera[c]->s_intrinsic.aspect*v_camera[c]->s_intrinsic.focal );
  cvmSet( GetM(m_calibration,c,0), 0, 1, 0.00               );
  cvmSet( GetM(m_calibration,c,0), 0, 2, v_camera[c]->s_intrinsic.u0         );
  cvmSet( GetM(m_calibration,c,0), 1, 0, 0.00               );
  cvmSet( GetM(m_calibration,c,0), 1, 1, v_camera[c]->s_intrinsic.focal        );
  cvmSet( GetM(m_calibration,c,0), 1, 2, v_camera[c]->s_intrinsic.v0         );
  cvmSet( GetM(m_calibration,c,0), 2, 0, 0.00               );
  cvmSet( GetM(m_calibration,c,0), 2, 1, 0.00               );
  cvmSet( GetM(m_calibration,c,0), 2, 2, 1.00               );
}

void CamCalibration::CreateEstimatedCalibrationMatrixFromEstimatedIntrinsicParameters( int c ){
  cvmSet( GetM(m_estim_calib,c,0), 0, 0, v_camera[c]->s_estim_int.aspect*v_camera[c]->s_estim_int.focal );
  cvmSet( GetM(m_estim_calib,c,0), 0, 1, 0.00               );
  cvmSet( GetM(m_estim_calib,c,0), 0, 2, v_camera[c]->s_estim_int.u0         );
  cvmSet( GetM(m_estim_calib,c,0), 1, 0, 0.00               );
  cvmSet( GetM(m_estim_calib,c,0), 1, 1, v_camera[c]->s_estim_int.focal        );
  cvmSet( GetM(m_estim_calib,c,0), 1, 2, v_camera[c]->s_estim_int.v0         );
  cvmSet( GetM(m_estim_calib,c,0), 2, 0, 0.00               );
  cvmSet( GetM(m_estim_calib,c,0), 2, 1, 0.00               );
  cvmSet( GetM(m_estim_calib,c,0), 2, 2, 1.00               );
}

void CamCalibration::CreateEstimatedInverseCalibrationMatrixFromEstimatedIntrinsicParameters( int c ){
  double tau = v_camera[c]->s_estim_int.aspect;
  double f   = v_camera[c]->s_estim_int.focal;
  cvmSet( GetM(m_estinvcalib,c,0), 0, 0, 1.00/(tau*f) );
  cvmSet( GetM(m_estinvcalib,c,0), 0, 1, 0.00               );
  cvmSet( GetM(m_estinvcalib,c,0), 0, 2, -(v_camera[c]->s_estim_int.u0)/(tau*f)      );
  cvmSet( GetM(m_estinvcalib,c,0), 1, 0, 0.00               );
  cvmSet( GetM(m_estinvcalib,c,0), 1, 1, 1.00/f              );
  cvmSet( GetM(m_estinvcalib,c,0), 1, 2, -(v_camera[c]->s_estim_int.v0)/f        );
  cvmSet( GetM(m_estinvcalib,c,0), 2, 0, 0.00               );
  cvmSet( GetM(m_estinvcalib,c,0), 2, 1, 0.00               );
  cvmSet( GetM(m_estinvcalib,c,0), 2, 2, 1.00               );
}

void CamCalibration::CreateRotationTranslationMatrixFromInverseCalibrationMatrixAndHomography( int c, int h ){
  int i;

  // Get pointer to homography:
  homography* m_homography = v_camera[c]->v_homography[h]->m_homography;

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
    // Create norming factor lambda:
    cvGEMM( GetM(m_estinvcalib,c,0), &m_H1, 1, NULL, 0, &m_CinvH1, 0 );

    // Search next orthonormal matrix:
    if( cvNorm( &m_CinvH1, NULL, CV_L2, NULL ) != 0 ){
      double lambda = 1.00/cvNorm( &m_CinvH1, NULL, CV_L2, NULL );

      // Create normalized R1 & R2:
      cvGEMM( GetM(m_estinvcalib,c,0), &m_H1, lambda, NULL, 0, &m_R1, 0 );
      cvGEMM( GetM(m_estinvcalib,c,0), &m_H2, lambda, NULL, 0, &m_R2, 0 );

      // Get R3 orthonormal to R1 and R2:
      cvCrossProduct( &m_R1, &m_R2, &m_R3 );

      // Put the rotation column vectors in the rotation matrix:
      for( i = 0; i < 3; i++ ){
        cvmSet( &m_R, i, 0,  cvmGet( &m_R1, i, 0 ) );
        cvmSet( &m_R, i, 1,  cvmGet( &m_R2, i, 0 ) );
        cvmSet( &m_R, i, 2,  cvmGet( &m_R3, i, 0 ) );
      }

      // Calculate Translation Vector T (- because of its definition):
      cvGEMM( GetM(m_estinvcalib,c,0), &m_H3, -lambda, NULL, 0, &m_T, 0 );

      // Transformation of R into - in Frobenius sense - next orthonormal matrix:
      double a_W[9]; CvMat  m_W  = cvMat( 3, 3, CV_64FC1, a_W  );
      double a_U[9]; CvMat  m_U  = cvMat( 3, 3, CV_64FC1, a_U  );
      double a_Vt[9]; CvMat  m_Vt = cvMat( 3, 3, CV_64FC1, a_Vt );
      cvSVD( &m_R, &m_W, &m_U, &m_Vt, CV_SVD_MODIFY_A | CV_SVD_V_T );
      cvMatMul( &m_U, &m_Vt, &m_R );

      // Put the rotation matrix and the translation vector together:
      ComposeRotationTranslationTo3x4Matrix( GetM(m_estim_r_t,c,h), &m_R, &m_T );
    }
  }
}

void CamCalibration::CreateRotationTranslationIdentityMatrix( int c ){
  for( int i=0; i<3; i++ )
    for( int j=0; j<4; j++ )
      cvmSet( GetM(m_rot_trans,c,0), i, j, 0.0 );
  cvmSet( GetM(m_rot_trans,c,0), 0, 0, 1.0 );
  cvmSet( GetM(m_rot_trans,c,1), 1, 1, 1.0 );
  cvmSet( GetM(m_rot_trans,c,2), 2, 2, 1.0 );
}

void CamCalibration::CreateRotationTranslationMatrix( int c, double rx, double ry, double rz,
                                                     double tx, double ty, double tz ){
                                                       rx *= 2*M_PI/360.00;
                                                       ry *= 2*M_PI/360.00;
                                                       rz *= 2*M_PI/360.00;
                                                       double a_R[]  = {    1,    0,     0,
                                                         0,    1,     0,
                                                         0,    0,        1 };
                                                       double a_Rx[] = {    1,    0,     0,
                                                         0, cos(rx), -sin(rx),
                                                         0,    sin(rx),  cos(rx) };
                                                       double a_Ry[] = { cos(ry),    0, -sin(ry),
                                                         0,    1,     0,
                                                         sin(ry),    0,   cos(ry) };
                                                       double a_Rz[] = { cos(rz), -sin(rz),      0,
                                                         sin(rz),  cos(rz),     0,
                                                         0,    0,        1 };
                                                       CvMat m_R  = cvMat( 3, 3, CV_64FC1, a_R  );
                                                       CvMat m_Rx = cvMat( 3, 3, CV_64FC1, a_Rx );
                                                       CvMat m_Ry = cvMat( 3, 3, CV_64FC1, a_Ry );
                                                       CvMat m_Rz = cvMat( 3, 3, CV_64FC1, a_Rz );
                                                       cvMatMul( &m_Rx, &m_R, &m_R );
                                                       cvMatMul( &m_Ry, &m_R, &m_R );
                                                       cvMatMul( &m_Rz, &m_R, &m_R );

                                                       for( int i = 0; i < 3; i++ )
                                                         for( int j = 0; j < 3; j++ )
                                                           cvmSet( GetM(m_rot_trans,c,0), i, j, cvmGet( &m_R, i, j ) );

                                                       cvmSet( GetM(m_rot_trans,c,0), 0, 3, -tx );
                                                       cvmSet( GetM(m_rot_trans,c,0), 1, 3, -ty );
                                                       cvmSet( GetM(m_rot_trans,c,0), 2, 3, -tz );
}

void CamCalibration::CreateEstimated3ChainMatrixRT( int h1, int c2, int h2, int c1 ){
  double a_RTinv[12]; CvMat m_RTinv = cvMat( 3, 4, CV_64FC1, a_RTinv );
  CvMat *m_RT11 = v_camera[c1]->v_homography[h1]->m_estim_r_t_matrix;
  CvMat *m_RT12 = v_camera[c1]->v_homography[h2]->m_estim_r_t_matrix;
  CvMat *m_RT21 = v_camera[c2]->v_homography[h1]->m_estim_r_t_matrix;
  CvMat *m_RT22 = v_camera[c2]->v_homography[h2]->m_estim_r_t_matrix;
  Mat3x4Inverse( m_RT22, &m_RTinv );
  Mat3x4Mul( m_RT21, &m_RTinv, m_RT11 );
  Mat3x4Mul( m_RT11,  m_RT12,  m_RT11 );
}

void CamCalibration::CreateEstimatedOptimalHomographyMatrixRT( int h1, int c1, int h2 ){
  double a_RTinv[12]; CvMat m_RTinv = cvMat( 3, 4, CV_64FC1, a_RTinv );
  CvMat *m_RT11 = v_camera[c1]->v_homography[h1]->m_estim_r_t_matrix;
  CvMat *m_RT12 = v_camera[c1]->v_homography[h2]->m_estim_r_t_matrix;
  Mat3x4Inverse( m_RT12, &m_RTinv );
  s_optimal.v_homography_r_t[h1] = cvCreateMat( 3, 4, CV_64FC1 );
  Mat3x4Mul( &m_RTinv, m_RT11, s_optimal.v_homography_r_t[h1] );
}

void CamCalibration::CreateEstimatedOptimalCameraMatrixC( int c ){
  s_optimal.v_camera_c[c] = cvCloneMat( v_camera[c]->m_estim_calib_matrix );
}

void CamCalibration::CreateEstimatedOptimalCameraMatrixRT( int c, int h ){
  s_optimal.v_camera_r_t[c] = cvCloneMat( v_camera[c]->v_homography[h]->m_estim_r_t_matrix );
}

bool CamCalibration::CreateMatrixCH(){

  // Release old CV matrix:
  if( m_CH )
    cvReleaseMat( &m_CH );

  m_CH  = cvCreateMat( v_camera.size(), v_camera[0]->v_homography.size(), CV_64FC1 );
  s_optimal.c_max = -1; s_optimal.h_max = -1;

  // Search for all existing connections:
  int cnt = 0;
  for( int c = 0; c < (int)v_camera.size(); c++ )
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ ){
      cvmSet( m_CH, c, h, v_camera[c]->v_homography[h]->m_homography ? 1 : 0 );
      if( v_camera[c]->v_homography[h]->m_homography )
        cnt++;
    }

    printf("\nOriginal connection matrix (connections: %i):\n",cnt);
    showmatrix_ch(*m_CH);

    // Find plane with most camera connections:
    int cmax = -1; int hmax = -1; int max = -1;
    for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ ){
      int i = 0;
      for( int c = 0; c < (int)v_camera.size(); c++ )
        if( cvmGet( m_CH, c, h ) == 1 )
          i++;
      if( i > max ){
        max  = i;
        hmax = h;
      }
    }

    // Find camera inside plane with most plane connections:
    max = -1;
    for( int c = 0; c < (int)v_camera.size(); c++ ){
      if( cvmGet( m_CH, c, hmax ) == 1 ){
        int i = 0;
        for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
          if( cvmGet( m_CH, c, h ) == 1 )
            i++;
        if( i > max ){
          max  = i;
          cmax = c;
        }
      }
    }

    // If no maximum row or column found return false:
    if( cmax == -1 || hmax == -1 ){
      cvReleaseMat( &m_CH );
      m_CH = NULL;
      if( cmax == -1 )
        printf("ERROR: Camera with maximal plane connections could not be estimated!\n");
      else
        printf("ERROR: Plane with maximal camera connections could not be estimated!\n");
      return false;
    }

    bool big_briged;
    do{
      big_briged = false;
      for( int c1 = 0; c1 < (int)v_camera.size(); c1++ ){
        for( int h1 = 0; h1 < (int)v_camera[c1]->v_homography.size(); h1++ ){
          if( cvmGet( m_CH, c1, h1 ) == 0 ){
            bool briged = false;
            for( int c2 = 0; c2 < (int)v_camera.size(); c2++ ){
              for( int h2 = 0; h2 < (int)v_camera[c2]->v_homography.size(); h2++ ){
                if( (cvmGet( m_CH, c1, h2 ) == 1 || cvmGet( m_CH, c1, h2 ) == 2) && 
                  (cvmGet( m_CH, c2, h1 ) == 1 || cvmGet( m_CH, c2, h1 ) == 2) && 
                  (cvmGet( m_CH, c2, h2 ) == 1 || cvmGet( m_CH, c2, h2 ) == 2) &&
                  c1 != c2 && h1 != h2 ){  

                    briged     = true;
                    big_briged = true;
                    cvmSet( m_CH, c1, h1, 1 );
                    CreateEstimated3ChainMatrixRT( h1, c2, h2, c1 );   
                }
                if( briged ) break;
              }
              if( briged ) break;
            }
          }
        }
      }
    } while( big_briged );

    s_optimal.c_max = cmax;
    s_optimal.h_max = hmax;

    printf("\nNew connection matrix (cmax: %i, hmax: %i, connections: %i):\n",cmax,hmax,cnt);
    showmatrix_ch(*m_CH);

    // Check if all cameras are connected:
    for( int c = 0; c < (int)v_camera.size(); c++ ){
      if( cvmGet( m_CH, c, hmax ) == 0 ){
        printf("ERROR: Not enough links to connect camera %i to main camera %i!\n",c,cmax);
        return false;
      }
    }

    return true;
}

void CamCalibration::ReleaseOptimalCameraStructure(){
  for( int i = 0; i < (int)s_optimal.v_camera_c.size(); i++ ) cvReleaseMat(&s_optimal.v_camera_c[i]);
  s_optimal.v_camera_c.clear();
  for( int i = 0; i < (int)s_optimal.v_camera_r_t.size(); i++ ) cvReleaseMat(&s_optimal.v_camera_r_t[i]);
  s_optimal.v_camera_r_t.clear();
  for( int i = 0; i < (int)s_optimal.v_camera_r_t_jacobian.size(); i++ ) cvReleaseMat(&s_optimal.v_camera_r_t_jacobian[i]);
  s_optimal.v_camera_r_t_jacobian.clear();
  for( int i = 0; i < (int)s_optimal.v_homography_r_t.size(); i++ ) cvReleaseMat(&s_optimal.v_homography_r_t[i]);
  s_optimal.v_homography_r_t.clear();
  for( int i = 0; i < (int)s_optimal.v_homography_r_t_jacobian.size(); i++ ) cvReleaseMat(&s_optimal.v_homography_r_t_jacobian[i]);
  s_optimal.v_homography_r_t_jacobian.clear();
}

bool CamCalibration::CreateOptimalCameraStructure(){
  ReleaseOptimalCameraStructure();

  if( !CreateMatrixCH() ){
    printf("ERROR: Connection matrix could not be constructed!\n");
    return false;
  }

  // Create all camera & calibration matrices:
  for( int c = 0; c < m_CH->height; c++ ){
    s_optimal.v_camera_r_t.push_back( NULL );
    CreateEstimatedOptimalCameraMatrixRT( c, s_optimal.h_max );
    s_optimal.v_camera_c.push_back( NULL );
    CreateEstimatedOptimalCameraMatrixC( c );
    s_optimal.v_camera_r_t_jacobian.push_back( cvCreateMat( 3, 9, CV_64FC1 ) );
  }

  // Create all possible plane matrices (others = NULL):
  for( int h = 0; h < m_CH->width; h++ ){
    s_optimal.v_homography_r_t.push_back( NULL );
    if( cvmGet( m_CH, s_optimal.c_max, h ) == 1 || cvmGet( m_CH, s_optimal.c_max, h ) == 2 )
      CreateEstimatedOptimalHomographyMatrixRT( h, s_optimal.c_max, s_optimal.h_max );
    s_optimal.v_homography_r_t_jacobian.push_back( cvCreateMat( 3, 9, CV_64FC1 ) );
  }

  return true;
}

struct ProjObs : ls_minimizer2::observation
{
  double target[2];
  int cam;
  int hom;
  int point;
  static int parameterNumber;
  ProjObs() {
    b = target;
  }
  virtual int get_nb_measures() const { return 2; };
  virtual void eval_func(const double *params, double *f, double *J, void **user_data) const;
};

int ProjObs::parameterNumber=0;

void CamCalibration::updateCB( double *params , void **user_data){
  CamCalibration *cam = (CamCalibration*) *user_data;

  // Pass parameters to global parameter array:
  int parameter_number = cam->GetParameterNumber();
  for( int i = 0; i < parameter_number; i++ )
    cam->v_opt_param[i] = params[i];

  // Update the optimization structure:
  cam->SetParameterSetToOptimalStructure();
  cam->PrintOptimizedResultErrors(params);
}

//void CamCalibration::projFunc( double *x, double *params, int na, double *f, double *grad, int *ind, LsqData *Data ){
void ProjObs::eval_func(const double *params, double *f, double *J, void **user_data) const {
  CamCalibration *cam = (CamCalibration*) *user_data;

  // Unpack arguments:
  int c     = this->cam;
  int h     = hom;

  double *grad0 = J;
  double *grad1 = J+parameterNumber;

  // Project the point (CRTp) and set f:
  double a_p[4];  double a_p3[3]; double a_p4[3];
  double a_RT[12]; CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
  a_p[0] = cam->v_camera[c]->v_homography[h]->s_plane_object->px[point]; a_p[2] = 0;
  a_p[1] = cam->v_camera[c]->v_homography[h]->s_plane_object->py[point]; a_p[3] = 1;
  CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
  CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
  CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
  cam->Mat3x4Mul( cam->s_optimal.v_camera_r_t[c], cam->s_optimal.v_homography_r_t[h], &m_RT );
  cvMatMul( &m_RT, &m_p, &m_p3 );
  cvMatMul( cam->s_optimal.v_camera_c[c], &m_p3, &m_p4 );
  cam->HomogenousNormalizeVector( &m_p4 );
  f[0] = cvmGet( &m_p4, 0, 0 );
  f[1] = cvmGet( &m_p4, 1, 0 );

  int gc = 0;
  if( J ){

    // Gradient of camera calibration parameters:
    for( int g_c = 0; g_c < (int)cam->s_optimal.v_camera_c.size(); g_c++ ){
      if( g_c == c ){
        grad0[gc] = cvmGet(&m_p3,0,0)/cvmGet(&m_p3,2,0);
        grad0[gc+1] = 0;
        grad0[gc+2] = 1;
        grad0[gc+3] = 0;
        grad1[gc] = 0;
        grad1[gc+1] = cvmGet(&m_p3,1,0)/cvmGet(&m_p3,2,0);
        grad1[gc+2] = 0;
        grad1[gc+3] = 1;
      } else {
        grad0[gc] = 0;
        grad0[gc+1] = 0;
        grad0[gc+2] = 0;
        grad0[gc+3] = 0;
        grad1[gc] = 0;
        grad1[gc+1] = 0;
        grad1[gc+2] = 0;
        grad1[gc+3] = 0;
      }
      gc+=4;
    }

    double a_R1[9];  CvMat m_R1    = cvMat( 3, 3, CV_64FC1, a_R1 );
    double a_T1[3];  CvMat m_T1   = cvMat( 3, 1, CV_64FC1, a_T1 );
    double a_R2[9];  CvMat m_R2    = cvMat( 3, 3, CV_64FC1, a_R2 );
    double a_T2[3];  CvMat m_T2   = cvMat( 3, 1, CV_64FC1, a_T2 );
    cam->ExtractRotationTranslationFrom3x4Matrix( cam->s_optimal.v_camera_r_t[c],     &m_R1, &m_T1 );
    cam->ExtractRotationTranslationFrom3x4Matrix( cam->s_optimal.v_homography_r_t[h], &m_R2, &m_T2 );

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

    twomat_gradian ( params[c*4+0],
      params[c*4+1],
      params[c*4+2],
      params[c*4+3],
      R1,
      -cvmGet( &m_T1, 0, 0 ),
      -cvmGet( &m_T1, 1, 0 ),
      -cvmGet( &m_T1, 2, 0 ),
      cam->s_optimal.v_camera_r_t_jacobian[c],
      R2,
      -cvmGet( &m_T2, 0, 0 ),
      -cvmGet( &m_T2, 1, 0 ),
      -cvmGet( &m_T2, 2, 0 ),
      cam->s_optimal.v_homography_r_t_jacobian[h],
      a_p,
      cgret, uv );

    // Gradient of camera RT matrices:
    for( int g_c = 0; g_c < (int)cam->s_optimal.v_camera_r_t.size(); g_c++ ){
      if( g_c == c ){
        for( int i = 0; i < 3; i++ )
          grad0[gc+i] = cgret[i+3];
        for( int i = 0; i < 3; i++ )
          grad0[gc+3+i] = cgret[i];
        for( int i = 0; i < 3; i++ )
          grad1[gc+i] = cgret[12+i+3];
        for( int i = 0; i < 3; i++ )
          grad1[gc+3+i] = cgret[12+i];
      } else {
        for( int i = 0; i < 6; i++ ) {
          grad0[gc+i] = 0;
          grad1[gc+i] = 0;
        }
      }
      gc+=6;
    }

    // Gradient of homography RT matrices:
    for( int g_h = 0; g_h < (int)cam->s_optimal.v_homography_r_t.size(); g_h++ ){

      // If not plane itself (Identity) and plane is connected to main plane:
      if( g_h != cam->s_optimal.h_max && cvmGet( cam->m_CH, cam->s_optimal.c_max, g_h ) == 1 ){
        if( g_h == h ){
          for( int i = 0; i < 3; i++ )
            grad0[gc+i] = cgret[6+i+3];
          for( int i = 0; i < 3; i++ )
            grad0[gc+i+3] = cgret[6+i];
          for( int i = 0; i < 3; i++ )
            grad1[gc+i] = cgret[12+6+i+3];
          for( int i = 0; i < 3; i++ )
            grad1[gc+i+3] = cgret[12+6+i];
        } else {
          for( int i = 0; i < 6; i++ ) {
            grad0[gc+i] = 0;
            grad1[gc+i] = 0;
          }
        }
        gc+=6;
      } 
    }
  }
}

int CamCalibration::GetParameterNumber(){
  int i = 0;

  for( int c = 0; c < (int)s_optimal.v_camera_r_t.size(); c++ )
    i+=6;

  for( int h = 0; h < (int)s_optimal.v_homography_r_t.size(); h++ )
    // If connection found and not plane itself (Identity)
    if( h != s_optimal.h_max && cvmGet( m_CH, s_optimal.c_max, h ) == 1 /*|| cvmGet( m_CH, s_optimal.c_max, h ) == 2)*/ )
      i+=6;

  return 4*(int)s_optimal.v_camera_r_t.size()+i;
}

int CamCalibration::GetObservationNumber(){
  int i = 0;
  for( int c = 0; c < (int)v_camera.size(); c++ )
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )
      if( v_camera[c]->v_homography[h]->m_homography )
        i += v_camera[c]->v_homography[h]->s_plane_object->p*2;
  return i;
}

void CamCalibration::GetParameterSetFromOptimalStructure(){
  // Clear old vector:
  v_opt_param.clear();

  // Pack camera calibration parameters:
  for( int c = 0; c < (int)s_optimal.v_camera_c.size(); c++ ){
    v_opt_param.push_back( cvmGet( s_optimal.v_camera_c[c], 0, 0 ) ); // f
    v_opt_param.push_back( cvmGet( s_optimal.v_camera_c[c], 1, 1 ) ); // g
    v_opt_param.push_back( cvmGet( s_optimal.v_camera_c[c], 0, 2 ) ); // u0
    v_opt_param.push_back( cvmGet( s_optimal.v_camera_c[c], 1, 2 ) ); // v0
  }

  double a_R[9];  CvMat m_R    = cvMat( 3, 3, CV_64FC1, a_R );
  double a_r[3];  CvMat m_r    = cvMat( 3, 1, CV_64FC1, a_r );
  double a_T[3];  CvMat m_T   = cvMat( 3, 1, CV_64FC1, a_T );

  // Pack Camera RT matrices:
  for( int c = 0; c < (int)s_optimal.v_camera_r_t.size(); c++ ){
    ExtractRotationTranslationFrom3x4Matrix( s_optimal.v_camera_r_t[c], &m_R, &m_T);
    v_opt_param.push_back( -cvmGet( &m_T, 0, 0 ) );
    v_opt_param.push_back( -cvmGet( &m_T, 1, 0 ) );
    v_opt_param.push_back( -cvmGet( &m_T, 2, 0 ) );
    cvRodrigues2( &m_R, &m_r, 0 );
    v_opt_param.push_back( cvmGet( &m_r, 0, 0 ) );
    v_opt_param.push_back( cvmGet( &m_r, 1, 0 ) );
    v_opt_param.push_back( cvmGet( &m_r, 2, 0 ) );
  }

  // Pack Homography RT matrices:
  for( int h = 0; h < (int)s_optimal.v_homography_r_t.size(); h++ ){
    // Pack to arguments if not reference plane itself (Identity)
    if( h != s_optimal.h_max && cvmGet( m_CH, s_optimal.c_max, h ) == 1 ){
      ExtractRotationTranslationFrom3x4Matrix( s_optimal.v_homography_r_t[h], &m_R, &m_T);
      v_opt_param.push_back( -cvmGet( &m_T, 0, 0 ) );
      v_opt_param.push_back( -cvmGet( &m_T, 1, 0 ) );
      v_opt_param.push_back( -cvmGet( &m_T, 2, 0 ) );
      cvRodrigues2( &m_R, &m_r, 0 );
      v_opt_param.push_back( cvmGet( &m_r, 0, 0 ) );
      v_opt_param.push_back( cvmGet( &m_r, 1, 0 ) );
      v_opt_param.push_back( cvmGet( &m_r, 2, 0 ) );
    }
  }
}

static CvPoint cvPoint(double a, double b)
{
  return cvPoint((int)a, (int)b);
}

void CamCalibration::SetParameterSetToOptimalStructure(){
  int i = 0;

  // Unpack camera calibration parameters:
  for( int c = 0; c < (int)s_optimal.v_camera_c.size(); c++ ){
    cvmSet( s_optimal.v_camera_c[c], 0, 0, v_opt_param[i++] ); // f
    cvmSet( s_optimal.v_camera_c[c], 1, 1, v_opt_param[i++] ); // g
    cvmSet( s_optimal.v_camera_c[c], 0, 2, v_opt_param[i++] ); // u0
    cvmSet( s_optimal.v_camera_c[c], 1, 2, v_opt_param[i++] ); // v0
  }

  double a_R[9];  CvMat m_R    = cvMat( 3, 3, CV_64FC1,     a_R );
  double a_r[3];  CvMat m_r    = cvMat( 3, 1, CV_64FC1,     a_r );
  double a_T[3];  CvMat m_T   = cvMat( 3, 1, CV_64FC1,     a_T );

  // Unpack Camera RT matrices:
  for( int c = 0; c < (int)s_optimal.v_camera_r_t.size(); c++ ){
    cvmSet( &m_T, 0, 0, -v_opt_param[i++] );
    cvmSet( &m_T, 1, 0, -v_opt_param[i++] );
    cvmSet( &m_T, 2, 0, -v_opt_param[i++] );
    cvmSet( &m_r, 0, 0,  v_opt_param[i++] );
    cvmSet( &m_r, 1, 0,  v_opt_param[i++] );
    cvmSet( &m_r, 2, 0,  v_opt_param[i++] );
    cvRodrigues2( &m_r, &m_R, s_optimal.v_camera_r_t_jacobian[c] );
    ComposeRotationTranslationTo3x4Matrix( s_optimal.v_camera_r_t[c], &m_R, &m_T);
  }

  // Unpack Homography RT matrices:
  for( int h = 0; h < (int)s_optimal.v_homography_r_t.size(); h++ ){
    // Pack to arguments if not plane itself (Identity)
    if( h != s_optimal.h_max && (cvmGet( m_CH, s_optimal.c_max, h ) == 1 || cvmGet( m_CH, s_optimal.c_max, h ) == 1) ){
      cvmSet( &m_T, 0, 0, -v_opt_param[i++] );
      cvmSet( &m_T, 1, 0, -v_opt_param[i++] );
      cvmSet( &m_T, 2, 0, -v_opt_param[i++] );
      cvmSet( &m_r, 0, 0,  v_opt_param[i++] );
      cvmSet( &m_r, 1, 0,  v_opt_param[i++] );
      cvmSet( &m_r, 2, 0,  v_opt_param[i++] );
      cvRodrigues2( &m_r, &m_R, s_optimal.v_homography_r_t_jacobian[h] );
      ComposeRotationTranslationTo3x4Matrix( s_optimal.v_homography_r_t[h], &m_R, &m_T);
    }
  }
}

void CamCalibration::PlotPointsToImagesAfterOptimization(){
  char  file_name[200];
  IplImage * image[5]; // TODO: flexibel!!
  int cnt = 0;
  for( int h = 0; h < (int)v_camera[0]->v_homography.size(); h++ ){
    for( int c = 0; c < (int)v_camera.size(); c++ ){
      if( cvmGet( m_CH, c, h ) == 1 ){
        sprintf(file_name,"E:\\andreas_camcal_16_12_2005\\cam%02d%04d.bmp",c+1,h+2048); //TODO: 2048!!!!!
		  
		ofImage _img = ofImage();
		_img.loadImage(file_name);
		ofxCvColorImage _im = ofxCvColorImage();
		_im = _img.getPixels();
		  
		if( image[c] = _im.getCvImage() ){         //!!!!!!!!!!!!!!!
			
          // Draw box:
          FILE * boxfile;
          if( (boxfile = fopen( "box.txt", "r+t" )) != NULL ){
            for( int j = 0; j < 6; j++ ){
              double p[4][2];
              for( int i = 0; (i < 4 && j < 2) || i < 2; i++ ){
                double a_p[4];  double a_p3[3]; double a_p4[3];
                double a_RT[12]; CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
                float x, y, z;
                fscanf( boxfile, "%f %f %f\n", &x, &y, &z );
                a_p[0] = x; a_p[1] = y; a_p[2] = z; a_p[3] = 1;
                CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
                CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
                CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
                Mat3x4Mul( s_optimal.v_camera_r_t[c], s_optimal.v_homography_r_t[h], &m_RT );
                cvMatMul( &m_RT, &m_p, &m_p3 );
                cvMatMul( s_optimal.v_camera_c[c], &m_p3, &m_p4 );
                HomogenousNormalizeVector( &m_p4 );
                p[i][0] = cvmGet( &m_p4, 0, 0 );
                p[i][1] = cvmGet( &m_p4, 1, 0 );
              }
              CvScalar color = CV_RGB ( 0,0,0 );
              if( j == 0 ) color = CV_RGB ( 255,200,0 );
              if( j >= 1 ) color = CV_RGB ( 155,100,0 );
              cvLine( image[c], cvPoint( p[0][0],p[0][1] ), cvPoint( p[1][0],p[1][1] ), color,4,CV_AA,0 );
              if( j < 2 ){
                cvLine( image[c], cvPoint( p[1][0],p[1][1] ), cvPoint( p[2][0],p[2][1] ), color,4,CV_AA,0 );
                cvLine( image[c], cvPoint( p[2][0],p[2][1] ), cvPoint( p[3][0],p[3][1] ), color,4,CV_AA,0 );
                cvLine( image[c], cvPoint( p[3][0],p[3][1] ), cvPoint( p[0][0],p[0][1] ), color,4,CV_AA,0 );
              }
            }
            fclose(boxfile);
          }
        }
      }
    }
    if( cvmGet( m_CH, 0, h ) == 1 && 
      cvmGet( m_CH, 1, h ) == 1 &&
      cvmGet( m_CH, 2, h ) == 1 &&
      cvmGet( m_CH, 3, h ) == 1 &&
      cvmGet( m_CH, 4, h ) == 1    ){ //TODO: 0 (alle testen!) intelligenter!!!
        // Save image:
        IplImage *im = cvCreateImage(cvSize(980,480), IPL_DEPTH_8U, 3);
        cvSetImageROI(im, cvRect(0,0,320,240));  cvResize(image[0], im, CV_INTER_LINEAR );
        cvSetImageROI(im, cvRect(320,0,320,240)); cvResize(image[1], im, CV_INTER_LINEAR );
        cvSetImageROI(im, cvRect(640,0,320,240)); cvResize(image[2], im, CV_INTER_LINEAR );
        cvSetImageROI(im, cvRect(0,240,320,240));   cvResize(image[3], im, CV_INTER_LINEAR );
        cvSetImageROI(im, cvRect(320,240,320,240)); cvResize(image[4], im, CV_INTER_LINEAR );
        cvResetImageROI(im);
        cvLine( im, cvPoint( 0,240 ), cvPoint( 980,240 ), CV_RGB ( 255,255,255 ),2,CV_AA,0 );
        cvLine( im, cvPoint( 320,0 ), cvPoint( 320,480 ), CV_RGB ( 255,255,255 ),2,CV_AA,0 );
        cvLine( im, cvPoint( 640,0 ), cvPoint( 640,480 ), CV_RGB ( 255,255,255 ),2,CV_AA,0 );
        sprintf(file_name,"__cam%04d_%04d.bmp",cnt,h);
		
//		cvSaveImage( file_name, im );
		
        cvReleaseImage( &image[0] ); //TODO!
        cvReleaseImage( &image[1] ); //TODO!
        cvReleaseImage( &image[2] ); //TODO!
        cvReleaseImage( &image[3] ); //TODO!
        cvReleaseImage( &image[4] ); //TODO!
        cvReleaseImage( &im ); //TODO!
        printf("File __cam%04d.bmp written!\n",cnt);
        cnt++;
    }
  }
}

/*
void CamCalibration::PlotPointsToImagesAfterOptimization(){
char  file_name[200];
IplImage * image1;
for( int c = 0; c < (int)v_camera.size(); c++ )         // ... cameras
for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )   // ... homographies
if( cvmGet( m_CH, c, h ) == 1  ){
sprintf(file_name,"E:\\andreas_camcal_16_12_2005\\cam%02d%04d.bmp",c+1,h+2048);
image1 = cvLoadImage( file_name, 1 );
int points = v_camera[c]->v_homography[h]->s_plane_object->p;
for( int point = 0; point < points; point++ ){
s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;
HomogenousNormalizeVector( (*s_plane_object).v_m_pp[point] );
double u1 = cvmGet( (*s_plane_object).v_m_pp[point], 0, 0 );
double v1 = cvmGet( (*s_plane_object).v_m_pp[point], 1, 0 );
double a_p[4];  double a_p3[3]; double a_p4[3];
double a_RT[12]; CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
a_p[0] = v_camera[c]->v_homography[h]->s_plane_object->px[point]; a_p[2] = 0;
a_p[1] = v_camera[c]->v_homography[h]->s_plane_object->py[point]; a_p[3] = 1;

// In the new system (u2 - rot):
CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
Mat3x4Mul( s_optimal.v_camera_r_t[c], s_optimal.v_homography_r_t[h], &m_RT );
cvMatMul( &m_RT, &m_p, &m_p3 );
cvMatMul( s_optimal.v_camera_c[c], &m_p3, &m_p4 );
HomogenousNormalizeVector( &m_p4 );
double u2 = cvmGet( &m_p4, 0, 0 );
double v2 = cvmGet( &m_p4, 1, 0 );

// In the old system (u4 - hellblau):
cvMatMul( v_camera[c]->v_homography[h]->m_estim_r_t_matrix, &m_p, &m_p3 );
cvMatMul( v_camera[c]->m_estim_calib_matrix, &m_p3, &m_p4 );
HomogenousNormalizeVector( &m_p4 );
double u4 = cvmGet( &m_p4, 0, 0 );
double v4 = cvmGet( &m_p4, 1, 0 );

double u3;
double v3;
v_camera[c]->v_homography[h]->m_homography->transform_point(
v_camera[c]->v_homography[h]->s_plane_object->px[point],
v_camera[c]->v_homography[h]->s_plane_object->py[point],
&u3,&v3 );

// Originalmessung gruen:
cvCircle( image1, cvPoint( u1,v1 ), 1, CV_RGB ( 1,255,1 ), 1, CV_AA, 0 );

// Original Homography gelb:
cvLine( image1, cvPoint( u1,v1 ), cvPoint( u3,v3 ), CV_RGB ( 255,255,1 ),1,CV_AA,0 );
cvCircle( image1, cvPoint( u3,v3 ), 1, CV_RGB ( 255,255,1 ), 1, CV_AA, 0 );

// Altes System hellblau:
cvCircle( image1, cvPoint( u4,v4 ), 1, CV_RGB ( 1,255,255 ), 2, CV_AA, 0 );
cvLine( image1, cvPoint( u1,v1 ), cvPoint( u4,v4 ), CV_RGB ( 1,255,255 ),2,CV_AA,0 );

// Endresultat rot:
cvCircle( image1, cvPoint( u2,v2 ), 1, CV_RGB ( 255,1,1 ), 1, CV_AA, 0 );
cvLine( image1, cvPoint( u1,v1 ), cvPoint( u2,v2 ), CV_RGB ( 255,1,1 ),1,CV_AA,0 );
}

////////////////////////////////////////////////////////////////////////
// Draw box:
FILE * boxfile;
if( (boxfile = fopen( "box.txt", "r+t" )) != NULL ){
for( int j = 0; j < 6; j++ ){
double p[4][2];
for( int i = 0; (i < 4 && j < 2) || i < 2; i++ ){
double a_p[4];  double a_p3[3]; double a_p4[3];
double a_RT[12]; CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
float x, y, z;
fscanf( boxfile, "%f %f %f\n", &x, &y, &z );
a_p[0] = x; a_p[1] = y; a_p[2] = z; a_p[3] = 1;
CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
Mat3x4Mul( s_optimal.v_camera_r_t[c], s_optimal.v_homography_r_t[h], &m_RT );
cvMatMul( &m_RT, &m_p, &m_p3 );
cvMatMul( s_optimal.v_camera_c[c], &m_p3, &m_p4 );
HomogenousNormalizeVector( &m_p4 );
p[i][0] = cvmGet( &m_p4, 0, 0 );
p[i][1] = cvmGet( &m_p4, 1, 0 );
}
CvScalar color;
if( j == 0 ) color = CV_RGB ( 255,255,255 );
if( j >= 1 ) color = CV_RGB ( 155,155,155 );
cvLine( image1, cvPoint( p[0][0],p[0][1] ), cvPoint( p[1][0],p[1][1] ), color,1,CV_AA,0 );
if( j < 2 ){
cvLine( image1, cvPoint( p[1][0],p[1][1] ), cvPoint( p[2][0],p[2][1] ), color,1,CV_AA,0 );
cvLine( image1, cvPoint( p[2][0],p[2][1] ), cvPoint( p[3][0],p[3][1] ), color,1,CV_AA,0 );
cvLine( image1, cvPoint( p[3][0],p[3][1] ), cvPoint( p[0][0],p[0][1] ), color,1,CV_AA,0 );
}
//printf("lines drawn %f %f %f %f\n",p[0][0],p[0][1],p[1][0],p[1][1]);
}
fclose(boxfile);
}

// Save image:
sprintf(file_name,"__cam%02d%04d.bmp",c,h);
printf("Image %s saved!\n",file_name);
cvSaveImage( file_name, image1 );
}
}*/


void CamCalibration::PrintOptimizedResultErrors( double *params){
  CamCalibration *cam = this;

  double total_error_opt = 0;
  double total_error_org = 0;
  double chi_error_opt   = 0;
  double chi_error_org   = 0;
  float  error_opt[50000]; //!TODO: Max 50.000 observations for this check!
  float  error_org[50000]; //!TODO: Max 50.000 observations for this check!
  float  error_gra[10][3000]; //!TODO: Das hier dynamischer gestalten!!!
  int    obs = 0;

  // Calculate errors:
  for( int c = 0; c < (int)cam->v_camera.size(); c++ )         // ... cameras
    for( int h = 0; h < (int)cam->v_camera[c]->v_homography.size(); h++ ){    // ... homographies
      error_gra[c][h] = 0;
      if( cam->v_camera[c]->v_homography[h]->m_homography ){
        int points = cam->v_camera[c]->v_homography[h]->s_plane_object->p;
        for( int point = 0; point < points; point++ ){

          // Original point on the screen:
          cam->HomogenousNormalizeVector( cam->v_camera[c]->v_homography[h]->s_plane_object->v_m_pp[point] );
          double u1 = cvmGet( cam->v_camera[c]->v_homography[h]->s_plane_object->v_m_pp[point], 0, 0 );
          double v1 = cvmGet( cam->v_camera[c]->v_homography[h]->s_plane_object->v_m_pp[point], 1, 0 );

          // Projected point on the screen:
          double a_p[4];  double a_p3[3]; double a_p4[3];
          double a_RT[12]; CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
          a_p[0] = cam->v_camera[c]->v_homography[h]->s_plane_object->px[point]; a_p[2] = 0;
          a_p[1] = cam->v_camera[c]->v_homography[h]->s_plane_object->py[point]; a_p[3] = 1;
          CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
          CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
          CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
          cam->Mat3x4Mul( cam->s_optimal.v_camera_r_t[c], cam->s_optimal.v_homography_r_t[h], &m_RT );
          cvMatMul( &m_RT, &m_p, &m_p3 );
          cvMatMul( cam->s_optimal.v_camera_c[c], &m_p3, &m_p4 );
          cam->HomogenousNormalizeVector( &m_p4 );
          double u2 = cvmGet( &m_p4, 0, 0 );
          double v2 = cvmGet( &m_p4, 1, 0 );

          // Projected points with original homography:
          double u3,v3;
          cam->v_camera[c]->v_homography[h]->m_homography->transform_point(
            cam->v_camera[c]->v_homography[h]->s_plane_object->px[point],
            cam->v_camera[c]->v_homography[h]->s_plane_object->py[point],
            &u3,&v3 );

          // Calculate error:
          double current_error_opt = sqrt( pow(u1-u2,2) + pow(v1-v2,2) );
          double current_error_org = sqrt( pow(u1-u3,2) + pow(v1-v3,2) );
          chi_error_opt += pow(u1-u2,2) + pow(v1-v2,2);
          chi_error_org += pow(u1-u3,2) + pow(v1-v3,2);
          error_opt[obs]    = (float)current_error_opt;
          total_error_opt  += current_error_opt;
          error_org[obs]    = (float)current_error_org;
          total_error_org  += current_error_org;
          obs++;

          // For error graphic:
          error_gra[c][h] += (float)( current_error_opt/(double)points );
        }
      }
    }

    // Print results to screen if more than one observation has been found:
    if( obs > 0 ){
      chi_error_opt /= (double)obs * 2.0;
      chi_error_org /= (double)obs * 2.0;
      double avg_error_opt = total_error_opt / (double)obs;
      double avg_error_org = total_error_org / (double)obs;
      double std_dev_opt   = 0;
      double std_dev_org   = 0;
      double max_error_opt = 0;
      double max_error_org = 0;
      double min_error_opt = total_error_opt;
      double min_error_org = total_error_org;
      for( int j = 0; j < obs; j++ ){
        if( error_opt[j] > max_error_opt ) max_error_opt = error_opt[j];
        if( error_org[j] > max_error_org ) max_error_org = error_org[j];
        if( error_opt[j] < min_error_opt ) min_error_opt = error_opt[j];
        if( error_org[j] < min_error_org ) min_error_org = error_org[j];
        std_dev_opt += pow( error_opt[j]-avg_error_opt, 2 );
        std_dev_org += pow( error_org[j]-avg_error_org, 2 );
      }
      std_dev_opt = sqrt(std_dev_opt/(double)obs);
      std_dev_org = sqrt(std_dev_org/(double)obs);

      // Plot cameras:
      printf("\n                  Focal   Aspect      u_0      v_0  Hnum\n");
      for( int c = 0; c < (int)cam->v_camera.size(); c++ )
        if( params[c*4+1] != 0 ){
          int hom = 0;
          for( int h = 0; h < (int)cam->v_camera[c]->v_homography.size(); h++ )
            if( cam->v_camera[c]->v_homography[h]->m_homography )
              hom++;
          printf( "Camera %02d:     %8.3f %8.3f %8.3f %8.3f %5d\n",
            c, 
            params[c*4+1], params[c*4]/params[c*4+1] ,  params[c*4+2], params[c*4+3],
            hom );
        }

        // Plot Errors:
        printf("\n                                 Optimal  Original\n");
        printf("Maximal error in observations:  %8.3f  %8.3f\n", max_error_opt, max_error_org );
        printf("Minimal error in observations:  %8.3f  %8.3f\n", min_error_opt, min_error_org );
        printf("Average error in observations:  %8.3f  %8.3f\n", avg_error_opt, avg_error_org );
        printf("Chi^2 error in observations:    %8.3f  %8.3f\n", chi_error_opt, chi_error_org );
        printf("Standard deviation of error:    %8.3f  %8.3f\n", std_dev_opt,   std_dev_org   );
        printf("Number of observations:         %8i  %8i\n", obs, obs);

        // Init error histogram graphic:
        int width  = 1024; //TODO: Hier groesse aus Parametern!
        int height = 768;
        IplImage *im = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, 3 );
        CvFont font;
        cvInitFont( &font, CV_FONT_HERSHEY_PLAIN, 1, 1, 0, 2, 8 );

        // Get maximal error for scaling:
        double max_error = 0;
        for( int c = 0; c < (int)cam->v_camera.size(); c++ )        // ... cameras
          for( int h = (int)cam->v_camera[c]->v_homography.size()-1; h >= 0 ; h-- )  // ... homographies
            if( cam->v_camera[c]->v_homography[h]->m_homography )
              if( error_gra[c][h] > max_error )
                max_error = error_gra[c][h];
        max_error *= 1.2;

        // Draw background:
        double cut_error = 1; //TODO: Hier Parameter wert!
        int y_cut = (int)((double)height-(double)height*cut_error/max_error);
        cvRectangle( im, cvPoint( 0,     0 ), cvPoint( width,  y_cut ), CV_RGB ( 100,100,100 ), CV_FILLED, 8, 0 );
        cvRectangle( im, cvPoint( 0, y_cut ), cvPoint( width, height ), CV_RGB ( 0,    0,  0 ), CV_FILLED, 8, 0 );

        // Draw error histogram:
        char info[200];
        for( int c = 0; c < (int)cam->v_camera.size(); c++ )        // ... cameras
          for( int h = (int)cam->v_camera[c]->v_homography.size()-1; h >= 0 ; h-- )  // ... homographies
            if( cam->v_camera[c]->v_homography[h]->m_homography ){
              int x = (int)((double)width*(double)h/(double)cam->v_camera[c]->v_homography.size());
              int y = (int)((double)height-(double)height*error_gra[c][h]/max_error);
              cvLine( im, cvPoint( x,y ), cvPoint( x,height ), CV_RGB ( 255,255,255 ), 2, CV_AA, 0 );
              cvCircle( im, cvPoint( x,y ), 2, CV_RGB ( 255,200,0 ), 2, CV_AA, 0 );
              if( error_gra[c][h]/max_error > 0.3 ){
                sprintf( info, "%i", h );
                cvPutText( im, info, cvPoint( x+1,y-1 ), &font, CV_RGB ( 255,200,0 ) );
              }
            }

            // Titles:
            sprintf( info, "%.3f", max_error );
            cvPutText( im, info, cvPoint( 10,30 ), &font, CV_RGB ( 255,0,0 ) );
            sprintf( info, "%.3f", 0 );
            cvPutText( im, info, cvPoint( 10,height-10 ), &font, CV_RGB ( 255,0,0 ) );
            if( cut_error > 0.1*max_error && cut_error < 0.9*max_error ){  
              sprintf( info, "%.3f", cut_error );
              cvPutText( im, info, cvPoint( 10,y_cut-5 ), &font, CV_RGB ( 255,0,0 ) );
            }
            sprintf( info, "Maximal Camera Error in Pixel over homographies", 0 );  
            cvPutText( im, info, cvPoint( 150,30 ), &font, CV_RGB ( 200,255,100 ) );

            /*
            // Print errorgraphic to file:
            char file_name[200];
            sprintf( file_name, "error_graphic_%02d.jpg", cam->errorgraphic_counter++ );
            cvSaveImage( file_name, im );
            */
            IplImage *im2 = cvCreateImage(cvSize(800,600), IPL_DEPTH_8U, 3); //TODO: Hier echte groesse von parametern!
            cvResize(im, im2, CV_INTER_LINEAR );
		
//            cvShowImage( "Error Histogram", im2 );
		
//            cvWaitKey(10);
            cvReleaseImage( &im );
            cvReleaseImage( &im2 );
            //printf( "File error_graphic_%02d.jpg successfully stored!\n\n", cam->errorgraphic_counter );
            printf( "==================================================\n" );
    } else {
      printf("\n\n----------   Calibration results:   ----------\n");
      printf("ERROR: No observations found!\n\n");
    }
}

bool CamCalibration::FilterHomographiesAfterOptimization( double p_PostFilter ){
  bool filtered = false;
  printf( "INFO: Starting post-filtering process...\n" );

  // Post filter homographies:
  for( int c = 0; c < (int)v_camera.size(); c++ )        // ... cameras
    for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ ){   // ... homographies
      if( v_camera[c]->v_homography[h]->m_homography ){
        int    points = v_camera[c]->v_homography[h]->s_plane_object->p;
        double error  = 0;
        for( int point = 0; point < points; point++ ){

          // Original point on the screen:
          HomogenousNormalizeVector( v_camera[c]->v_homography[h]->s_plane_object->v_m_pp[point] );
          double u1 = cvmGet( v_camera[c]->v_homography[h]->s_plane_object->v_m_pp[point], 0, 0 );
          double v1 = cvmGet( v_camera[c]->v_homography[h]->s_plane_object->v_m_pp[point], 1, 0 );

          // Projected point on the screen:
          double a_p[4];  double a_p3[3]; double a_p4[3];
          double a_RT[12]; CvMat m_RT = cvMat( 3, 4, CV_64FC1, a_RT );
          a_p[0] = v_camera[c]->v_homography[h]->s_plane_object->px[point]; a_p[2] = 0;
          a_p[1] = v_camera[c]->v_homography[h]->s_plane_object->py[point]; a_p[3] = 1;
          CvMat m_p  = cvMat( 4, 1, CV_64FC1, a_p );  // plane point (flat)
          CvMat m_p3 = cvMat( 3, 1, CV_64FC1, a_p3 ); // eye point 2
          CvMat m_p4 = cvMat( 3, 1, CV_64FC1, a_p4 ); // image point
          Mat3x4Mul( s_optimal.v_camera_r_t[c], s_optimal.v_homography_r_t[h], &m_RT );
          cvMatMul( &m_RT, &m_p, &m_p3 );
          cvMatMul( s_optimal.v_camera_c[c], &m_p3, &m_p4 );
          HomogenousNormalizeVector( &m_p4 );
          double u2 = cvmGet( &m_p4, 0, 0 );
          double v2 = cvmGet( &m_p4, 1, 0 );

          // Calculate error:
          double current_error_opt = sqrt( pow(u1-u2,2) + pow(v1-v2,2) );
          error += current_error_opt/(double)points;
        }
        if( error > p_PostFilter ){
          for( int c2 = 0; c2 < (int)v_camera.size(); c2++ ){
            DeleteWorldPlaneHomography( c2, h );
            cvmSet( m_CH, c2, h, 0 );
            cvReleaseMat( &s_optimal.v_homography_r_t[h] );
            cvReleaseMat( &s_optimal.v_homography_r_t_jacobian[h] );
          }
          printf( "INFO: View %i has been deleted for all cameras!\n", h );
          filtered = true;
        }
      }
    }

    if( !filtered )
      printf( "INFO: Nothing filtered!\n" );

    // Return true if at least one homography has been filtered:
    printf( "INFO: Post-filtering process finished.\n\n" );
    return filtered;
}

bool CamCalibration::OptimizeCalibrationByMinimalParameterMethod( int iter, double eps, double p_PostFilter ){

  // Create optimal camera structure for the first time:
  if( !CreateOptimalCameraStructure() ){
    printf("ERROR: Optial camera structure estimation failed!\n");
    return false;
  }

  // Reset counter for error histogram and create an output window:
  errorgraphic_counter = 0;
  // cvNamedWindow( "Error Histogram", CV_WINDOW_AUTOSIZE );
  // cvWaitKey(10);

  // Start calibration:
  //double post_filter_offset = 20;
  do {

    // Get number parameters and observations:
    int parameter_number   = GetParameterNumber();
    /* int observation_number = GetObservationNumber(); */ 

    ls_minimizer2 minimizer(parameter_number);
    minimizer.set_state_change_callback(updateCB);
    minimizer.set_user_data(0, this);
    minimizer.lm_set_max_iterations(iter);
    //minimizer.set_verbose_level(3);
    ProjObs::parameterNumber = parameter_number;

    // Feed with initial parameters:
    GetParameterSetFromOptimalStructure();

    /*
    LsqData *lsqData = AllocateLsqData( parameter_number, observation_number );
    SetLsqGlobals( lsqData, iter, eps, GAUSS_JORDAN, updateCB, true );
    LsqObs *obs      = AllocateLsqObs( lsqData, sizeof(LsqObs), observation_number, 4 );
    lsqData->slot1   = this;

    // Feed with initial parameters:
    GetParameterSetFromOptimalStructure();
    FillLsqParams( lsqData, &v_opt_param[0], 0, 0 );
    lsqData->Dsp.F = PrintOptimizedResultErrors;
    */

    // Add the observations for ...
    for( int c = 0; c < (int)v_camera.size(); c++ )         // ... cameras
      for( int h = 0; h < (int)v_camera[c]->v_homography.size(); h++ )   // ... homographies
        if( v_camera[c]->v_homography[h]->m_homography ){     
          int points = v_camera[c]->v_homography[h]->s_plane_object->p;
          for( int point = 0; point < points; point++ ) { // ... points 

            // Add homography number and point:
            ProjObs *o = new ProjObs();
            o->cam = c;
            o->hom = h;
            o->point = point;

            // Add screen plane point (reference!):
            s_struct_plane* s_plane_object = v_camera[c]->v_homography[h]->s_plane_object;
            HomogenousNormalizeVector( (*s_plane_object).v_m_pp[point] );
            o->target[0] = cvmGet( (*s_plane_object).v_m_pp[point], 0, 0 );
            o->target[1] = cvmGet( (*s_plane_object).v_m_pp[point], 1, 0 );

            minimizer.add_observation(o, true, false);
          }
        }

        minimizer.minimize_using_levenberg_marquardt_from(&v_opt_param[0]);
        void *ptr=this;
        updateCB( minimizer.state, &ptr);

        // post filter offset in test phase! remove, please!
        //if( post_filter_offset > 1 )
        // post_filter_offset -= 10;

        // Redo calibration if at least one homography was post-filtered:
  } while( FilterHomographiesAfterOptimization( p_PostFilter/*+post_filter_offset*/ ) );

  // Destroy histogram output window:
// 	cvDestroyAllWindows();
  return true;
}

void CamCalibration::PrintOptimizedResultsToFile1()
{
  FILE *stream;

  // Print cameras intrinsic matrix to file:
  if( (stream = fopen( "camera_c.txt", "w+t" )) != NULL ){
    for( int c = 0; c < (int)s_optimal.v_camera_c.size(); c++ ){
      fprintf( stream, "no: %i\n", c );
      fprintf( stream, "width: %i\n", v_camera[c]->w );
      fprintf( stream, "height: %i\n", v_camera[c]->h );
      showmatrix_file( *s_optimal.v_camera_c[c], stream );
    }
    fclose( stream );
  }

  // Print cameras extrinsic matrix to file:
  if( (stream = fopen( "camera_r_t.txt", "w+t" )) != NULL ){
    for( int c = 0; c < (int)s_optimal.v_camera_c.size(); c++ ){
      fprintf( stream, "no: %i\n", c );
      fprintf( stream, "width: %i\n", v_camera[c]->w );
      fprintf( stream, "height: %i\n", v_camera[c]->h );
      showmatrix_file( *s_optimal.v_camera_r_t[c], stream );
    }
    fclose( stream );
  }

  // Print views to file:
  if( (stream = fopen( "view_r_t.txt", "w+t" )) != NULL ){
    for( int h = 0; h < (int)s_optimal.v_homography_r_t.size(); h++ ){
      if( s_optimal.v_homography_r_t[h] ){
        fprintf( stream, "no: %i\n", h );
        showmatrix_file( *s_optimal.v_homography_r_t[h], stream );
      }
    }
    fclose( stream );
  }
}

void CamCalibration::PrintOptimizedResultsToFile2( char* file_descriptor, bool create_png, char* sequence_descriptor, 
                                                   char* png_descriptor, int c_start, int h_start )
{
  FILE *stream;
  char file_name[200];
  char image_in[200];
  char image_out[200];

  // Print files (and copy images to new location):
  for( int c = 0; c < (int)s_optimal.v_camera_c.size(); c++ ){
    for( int h = 0; h < (int)s_optimal.v_homography_r_t.size(); h++ ){
      if( cvmGet( m_CH, c, h ) == 1 ){
        sprintf( file_name, file_descriptor, c, h );
        if( (stream = fopen( file_name, "w+t" )) != NULL ){
          double a_proj[12];
          CvMat m_proj  = cvMat( 3, 4, CV_64FC1, a_proj );
          cvMatMul( s_optimal.v_camera_c[c], s_optimal.v_camera_r_t[c], &m_proj );
          Mat3x4Mul( &m_proj, s_optimal.v_homography_r_t[h], &m_proj );
          showmatrix_file( m_proj, stream );
          fclose( stream );
        }
      }/*
       if( create_png ){
       // Image:
       sprintf(image_in,sequence_descriptor,c_start+c,h_start+h);
       sprintf(image_out,png_descriptor,c,h);
       IplImage * myimage = cvLoadImage( image_in, 0 );
       cvSaveImage( image_out, myimage );
       printf("Print to file: %i %i \n",c,h);
       }*/
    }
  }
}
