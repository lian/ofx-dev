#include <stdio.h>
#include <iostream>
#include <cv.h>

using namespace std;

/**
\brief Special function to print the connection matrix.

Prints the connection matrix. Therefore it uses only rows that exist
(at least 1 existing connection to a camera) and displays the number
of the view.
*/
void showmatrix_ch(CvMat &M){
  //ios::sync_with_stdio();

  for(int i=0; i < M.cols; i++) {
    bool detected = false;
    for(int j=0; j < M.rows; j++) {
      if( cvmGet(&M,j,i) != 0 )
        detected = true;
    }
    if( detected ){
      printf("View %i:",i);
      for(int j=0; j < M.rows; j++) {
        printf(" %i",(int)cvmGet(&M,j,i) );
      }
      printf("\n");
    }
  }
  printf("\n");
}

/**
\brief Utility function to print a matrix to the screen.

Prints a matrix to the screen. If it is a 3x3 matrix, the
determinant is shown, too.
*/
void showmatrix(CvMat &M){
  //ios::sync_with_stdio();

  for(int i=0; i < M.rows; i++) {
    for(int j=0; j < M.cols; j++) {
      printf(" %12.6f ",cvmGet(&M,i,j) );
    }
    printf("\n");
  }
  if (M.rows >=3 && M.cols >=3 && (M.rows == M.cols)) {
    CvMat sub;
    cvGetSubRect(&M, &sub, cvRect(0,0, 3, 3));
    printf("Det: %f\n", cvDet(&sub));
  }
  printf("\n");
}

/**
\brief Utility function to print a matrix to the screen.

Prints a matrix to the screen. If it is a 3x3 matrix, the
determinant is shown, too. \b header specifies a title
string.
*/
void showmatrix(CvMat &M,const char *header){
  cout << header << "\n";
  showmatrix(M);
}

/**
\brief Utility function to print a matrix to the screen.

Prints a matrix to the screen. If it is a 3x3 matrix, the
determinant is shown, too. \b header specifies a title
string.
*/
void showmatrix(const char *header,CvMat &M){
  showmatrix(M,header);
}

/**
\brief Utility function to print a matrix to a file.

Prints the matrix \b M to file \b stream.
*/
void showmatrix_file(CvMat &M,FILE *stream){
  //ios::sync_with_stdio();
  char buffer[1000];
  int  length;
  for(int i=0; i < M.rows; i++) {
    for(int j=0; j < M.cols; j++) {
      length = sprintf(buffer," %12.6f ",cvmGet(&M,i,j));
      fwrite( buffer, sizeof(char), length, stream );
    }
    length = sprintf(buffer,"\n");
    fwrite( buffer, sizeof(char), length, stream );
  }
  length = sprintf(buffer,"\n");
  fwrite( buffer, sizeof(char), length, stream );
}

void twomat_gradian (
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
                     double uv[2] )
{

  double t24;

  double t7;

  double t208;

  double t2;

  double t158;

  double t26;

  double t8;

  double t276;

  double t5;

  double t29;

  double t1;

  double t60;

  double t280;

  double t282;

  double t284;

  double t86;

  double t11;

  double t327;

  double t17;

  double t168;

  double t458;

  double t460;

  double t376;

  double t380;

  double t266;

  double t57;

  double t81;

  double t82;

  double t13;

  double t137;

  double t402;

  double t404;

  double t187;

  double t189;

  double t191;

  double t4;

  double t109;

  double t110;

  double t36;

  double t62;

  double t111;

  double t114;

  double t116;

  double t38;

  double t235;

  double t237;

  double t217;

  double t219;

  double t221;

  double t40;

  double t15;

  double t64;

  double t141;
  double t108;

  double t139;

  double t22;

  double t88;

  double t311;

  double t313;

  double t315;

  double t319;

  double t229;

  double t258;

  double t264;

  double t430;

  double t426;

  double t432;

  double t434;

  double t268;

  double t272;

  double t274;

  double t20;

  double t305;

  double t225;

  double t227;

  double t233;

  double t406;

  double t84;

  double t321;

  double t323;

  double t329;

  double t331;

  double t352;

  double t164;

  double t166;

  double t378;

  double t118;

  double t427;

  double t462;

  t1 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 1-1 + (1-1)*3);

  t2 = S_matrix[1-1][1-1];

  t4 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 2-1 + (1-1)*3);

  t5 = S_matrix[2-1][1-1];

  t7 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 3-1 + (1-1)*3);

  t8 = S_matrix[3-1][1-1];

  t11 = p[0];

  t13 = S_matrix[1-1][2-1];

  t15 = S_matrix[2-1][2-1];

  t17 = S_matrix[3-1][2-1];

  t20 = p[1];

  t22 = S_matrix[1-1][3-1];

  t24 = S_matrix[2-1][3-1];

  t26 = S_matrix[3-1][3-1];

  t29 = p[2];

  t36 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 1-1 + (3-1)*3);

  t38 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 2-1 + (3-1)*3);

  t40 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 3-1 + (3-1)*3);

  t57 = (t36 * t2 + t38 * t5 + t40 * t8) * t11 + (t36 * t13 + t38 * t15 + t40 * t17) * t20 + (t36 * t22 + t38 * t24 + t40 * t26) * t29 + t36 * Sx + t38 * Sy + t40 * Sz;

  t60 = R_matrix[3-1][1-1];

  t62 = R_matrix[3-1][2-1];

  t64 = R_matrix[3-1][3-1];

  t81 = (t60 * t2 + t62 * t5 + t64 * t8) * t11 + (t60 * t13 + t62 * t15 + t64 * t17) * t20 + (t60 * t22 + t62 * t24 + t64 * t26) * t29 + t60 * Sx + t62 * Sy + t64 * Sz + Rz;

  t82 = 0.1e1 / t81;

  t84 = R_matrix[1-1][1-1];

  t86 = R_matrix[1-1][2-1];

  t88 = R_matrix[1-1][3-1];
  t108 = fx * ((t84 * t2 + t86 * t5 + t88 * t8) * t11 + (t84 * t13 + t86 * t15 + t88 * t17) * t20 + (t84 * t22 + t86 * t24 + t88 * t26) * t29 + t84 * Sx + t86 * Sy + t88 * Sz + Rx) + cx * t81;
  t109 = t81 * t81;

  t110 = 0.1e1 / t109;

  t111 = (fx * ((t84 * t2 + t86 * t5 + t88 * t8) * t11 + (t84 * t13 + t86 * t15 + t88 * t17) * t20 + (t84 * t22 + t86 * t24 + t88 * t26) * t29 + t84 * Sx + t86 * Sy + t88 * Sz + Rx) + cx * t81) * t110;

  t114 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 1-1 + (1-1)*3);

  t116 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 2-1 + (1-1)*3);

  t118 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 3-1 + (1-1)*3);

  t137 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 1-1 + (3-1)*3);

  t139 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 2-1 + (3-1)*3);

  t141 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 3-1 + (3-1)*3);

  t158 = (t137 * t2 + t139 * t5 + t141 * t8) * t11 + (t137 * t13 + t139 * t15 + t141 * t17) * t20 + (t137 * t22 + t139 * t24 + t141 * t26) * t29 + t137 * Sx + t139 * Sy + t141 * Sz;

  t164 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 1-1 + (1-1)*3);

  t166 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 2-1 + (1-1)*3);

  t168 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 3-1 + (1-1)*3);

  t187 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 1-1 + (3-1)*3);

  t189 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 2-1 + (3-1)*3);

  t191 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 3-1 + (3-1)*3);

  t208 = (t187 * t2 + t189 * t5 + t191 * t8) * t11 + (t187 * t13 + t189 * t15 + t191 * t17) * t20 + (t187 * t22 + t189 * t24 + t191 * t26) * t29 + t187 * Sx + t189 * Sy + t191 * Sz;

  t217 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 1-1 + (1-1)*3);

  t219 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 1-1 + (2-1)*3);

  t221 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 1-1 + (3-1)*3);

  t225 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 2-1 + (1-1)*3);

  t227 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 2-1 + (2-1)*3);

  t229 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 2-1 + (3-1)*3);

  t233 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 3-1 + (1-1)*3);

  t235 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 3-1 + (2-1)*3);

  t237 = CV_MAT_ELEM(*S_jacobian, double, 1-1, 3-1 + (3-1)*3);

  t258 = (t60 * t217 + t62 * t219 + t64 * t221) * t11 + (t60 * t225 + t62 * t227 + t64 * t229) * t20 + (t60 * t233 + t62 * t235 + t64 * t237) * t29;

  t264 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 1-1 + (1-1)*3);

  t266 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 1-1 + (2-1)*3);

  t268 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 1-1 + (3-1)*3);

  t272 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 2-1 + (1-1)*3);

  t274 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 2-1 + (2-1)*3);

  t276 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 2-1 + (3-1)*3);

  t280 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 3-1 + (1-1)*3);

  t282 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 3-1 + (2-1)*3);

  t284 = CV_MAT_ELEM(*S_jacobian, double, 2-1, 3-1 + (3-1)*3);

  t305 = (t60 * t264 + t62 * t266 + t64 * t268) * t11 + (t60 * t272 + t62 * t274 + t64 * t276) * t20 + (t60 * t280 + t62 * t282 + t64 * t284) * t29;

  t311 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 1-1 + (1-1)*3);

  t313 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 1-1 + (2-1)*3);

  t315 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 1-1 + (3-1)*3);

  t319 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 2-1 + (1-1)*3);

  t321 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 2-1 + (2-1)*3);

  t323 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 2-1 + (3-1)*3);

  t327 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 3-1 + (1-1)*3);

  t329 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 3-1 + (2-1)*3);

  t331 = CV_MAT_ELEM(*S_jacobian, double, 3-1, 3-1 + (3-1)*3);

  t352 = (t60 * t311 + t62 * t313 + t64 * t315) * t11 + (t60 * t319 + t62 * t321 + t64 * t323) * t20 + (t60 * t327 + t62 * t329 + t64 * t331) * t29;

  t376 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 1-1 + (2-1)*3);

  t378 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 2-1 + (2-1)*3);

  t380 = CV_MAT_ELEM(*R_jacobian, double, 1-1, 3-1 + (2-1)*3);

  t402 = R_matrix[2-1][1-1];

  t404 = R_matrix[2-1][2-1];

  t406 = R_matrix[2-1][3-1];

  t426 = fy * ((t402 * t2 + t404 * t5 + t406 * t8) * t11 + (t402 * t13 + t404 * t15 + t406 * t17) * t20 + (t402 * t22 + t404 * t24 + t406 * t26) * t29 + t402 * Sx + t404 * Sy + t406 * Sz + Ry) + cy * t81;

  t427 = (fy * ((t402 * t2 + t404 * t5 + t406 * t8) * t11 + (t402 * t13 + t404 * t15 + t406 * t17) * t20 + (t402 * t22 + t404 * t24 + t406 * t26) * t29 + t402 * Sx + t404 * Sy + t406 * Sz + Ry) + cy * t81) * t110;

  t430 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 1-1 + (2-1)*3);

  t432 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 2-1 + (2-1)*3);

  t434 = CV_MAT_ELEM(*R_jacobian, double, 2-1, 3-1 + (2-1)*3);

  t458 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 1-1 + (2-1)*3);

  t460 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 2-1 + (2-1)*3);

  t462 = CV_MAT_ELEM(*R_jacobian, double, 3-1, 3-1 + (2-1)*3);

  cgret[0] = (fx * ((t1 * t2 + t4 * t5 + t7 * t8) * t11 + (t1 * t13 + t4 * t15 + t7 * t17) * t20 + (t1 * t22 + t4 * t24 + t7 * t26) * t29 + t1 * Sx + t4 * Sy + t7 * Sz) + cx * t57) * t82 - t111 * t57;

  cgret[1] = (fx * ((t114 * t2 + t116 * t5 + t118 * t8) * t11 + (t114 * t13 + t116 * t15 + t118 * t17) * t20 + (t114 * t22 + t116 * t24 + t118 * t26) * t29 + t114 * Sx + t116 * Sy + t118 * Sz) + cx * t158) * t82 - t111 * t158;

  cgret[2] = (fx * ((t164 * t2 + t166 * t5 + t168 * t8) * t11 + (t164 * t13 + t166 * t15 + t168 * t17) * t20 + (t164 * t22 + t166 * t24 + t168 * t26) * t29 + t164 * Sx + t166 * Sy + t168 * Sz) + cx * t208) * t82 - t111 * t208;

  cgret[3] = fx * t82;

  cgret[4] = 0;

  cgret[5] = cx * t82 - t111;

  cgret[6] = (fx * ((t84 * t217 + t86 * t219 + t88 * t221) * t11 + (t84 * t225 + t86 * t227 + t88 * t229) * t20 + (t84 * t233 + t86 * t235 + t88 * t237) * t29) + cx * t258) * t82 - t111 * t258;

  cgret[7] = (fx * ((t84 * t264 + t86 * t266 + t88 * t268) * t11 + (t84 * t272 + t86 * t274 + t88 * t276) * t20 + (t84 * t280 + t86 * t282 + t88 * t284) * t29) + cx * t305) * t82 - t111 * t305;

  cgret[8] = (fx * ((t84 * t311 + t86 * t313 + t88 * t315) * t11 + (t84 * t319 + t86 * t321 + t88 * t323) * t20 + (t84 * t327 + t86 * t329 + t88 * t331) * t29) + cx * t352) * t82 - t111 * t352;

  cgret[9] = (fx * t84 + cx * t60) * t82 - t111 * t60;

  cgret[10] = (fx * t86 + cx * t62) * t82 - t111 * t62;

  cgret[11] = (fx * t88 + cx * t64) * t82 - t111 * t64;

  cgret[12] = (fy * ((t376 * t2 + t378 * t5 + t380 * t8) * t11 + (t376 * t13 + t378 * t15 + t380 * t17) * t20 + (t376 * t22 + t378 * t24 + t380 * t26) * t29 + t376 * Sx + t378 * Sy + t380 * Sz) + cy * t57) * t82 - t427 * t57;

  cgret[13] = (fy * ((t430 * t2 + t432 * t5 + t434 * t8) * t11 + (t430 * t13 + t432 * t15 + t434 * t17) * t20 + (t430 * t22 + t432 * t24 + t434 * t26) * t29 + t430 * Sx + t432 * Sy + t434 * Sz) + cy * t158) * t82 - t427 * t158;

  cgret[14] = (fy * ((t458 * t2 + t460 * t5 + t462 * t8) * t11 + (t458 * t13 + t460 * t15 + t462 * t17) * t20 + (t458 * t22 + t460 * t24 + t462 * t26) * t29 + t458 * Sx + t460 * Sy + t462 * Sz) + cy * t208) * t82 - t427 * t208;

  cgret[15] = 0;

  cgret[16] = fy * t82;

  cgret[17] = cy * t82 - t427;

  cgret[18] = (fy * ((t402 * t217 + t404 * t219 + t406 * t221) * t11 + (t402 * t225 + t404 * t227 + t406 * t229) * t20 + (t402 * t233 + t404 * t235 + t406 * t237) * t29) + cy * t258) * t82 - t427 * t258;

  cgret[19] = (fy * ((t402 * t264 + t404 * t266 + t406 * t268) * t11 + (t402 * t272 + t404 * t274 + t406 * t276) * t20 + (t402 * t280 + t404 * t282 + t406 * t284) * t29) + cy * t305) * t82 - t427 * t305;

  cgret[20] = (fy * ((t402 * t311 + t404 * t313 + t406 * t315) * t11 + (t402 * t319 + t404 * t321 + t406 * t323) * t20 + (t402 * t327 + t404 * t329 + t406 * t331) * t29) + cy * t352) * t82 - t427 * t352;
  cgret[21] = (fy * t402 + cy * t60) * t82 - t427 * t60;
  cgret[22] = (fy * t404 + cy * t62) * t82 - t427 * t62;
  cgret[23] = (fy * t406 + cy * t64) * t82 - t427 * t64;


  uv[0] = t108 * t82;
  uv[1] = t426 * t82;

}
