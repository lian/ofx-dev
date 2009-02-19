/**************************************************************************
*
* File:          $RCSfile: extern.h,v $
* Module:        CLAPACK function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.10 $
* Last edited:   $Date: 2003/01/31 18:57:29 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_CLAPACK_EXTERN_H
#define _GAN_CLAPACK_EXTERN_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_LAPACK

#define integer long
#define real float
#define doublereal double
typedef long int logical;
typedef logical (*L_fp)();

/* these are prototypes for all the LAPACK functions used in Gandalf */

/* double precision functions */
int dpptrf_ ( char *uplo, integer *n, doublereal *ap, integer *info );
int dpptri_ ( char *uplo, integer *n, doublereal *ap, integer *info );
int dtptri_ ( char *uplo, char *diag, integer *n, doublereal *ap,
              integer *info );
int dgetf2_ ( integer *m, integer *n, doublereal *a, integer *lda,
              integer *ipiv, integer *info );
int dgetrf_ ( integer *m, integer *n, doublereal *a, integer *lda,
              integer *ipiv, integer *info );
int dgetri_ ( integer *n, doublereal *a, integer *lda, integer *ipiv,
              doublereal *work, integer *lwork, integer *info );
int dspev_ ( char *jobz, char *uplo, integer *n, doublereal *ap,
             doublereal *w, doublereal *z, integer *ldz, doublereal *work, 
             integer *info );
int dgeqrf_ ( integer *m, integer *n, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *lwork,
              integer *info );
int dgeqr2_ ( integer *m, integer *n, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *info );
int dgelqf_ ( integer *m, integer *n, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *lwork,
              integer *info );
int dgelq2_ ( integer *m, integer *n, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *info );
int dorgqr_ ( integer *m, integer *n, integer *k, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *lwork, 
              integer *info );
int dorg2r_ ( integer *m, integer *n, integer *k, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *info );
int dorglq_ ( integer *m, integer *n, integer *k, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *lwork,
              integer *info );
int dorgl2_( integer *m, integer *n, integer *k, doublereal *a, integer *lda,
             doublereal *tau, doublereal *work, integer *info );
int dorg2l_ ( integer *m, integer *n, integer *k, doublereal *a, integer *lda,
              doublereal *tau, doublereal *work, integer *info );
int dgesvd_ ( char *jobu, char *jobvt, integer *m, integer *n, 
              doublereal *a, integer *lda, doublereal *s,
              doublereal *u, integer *ldu, doublereal *vt, integer *ldvt,
              doublereal *work, integer *lwork, integer *info );
int dgeev_ ( char *jobvl, char *jobvr, integer *n, doublereal *a, integer *lda,
             doublereal *wr, doublereal *wi, doublereal *vl, 
             integer *ldvl, doublereal *vr, integer *ldvr, doublereal *work, 
             integer *lwork, integer *info );
int dgees_ ( char *jobvs, char *sort, L_fp select, integer *n, 
             doublereal *a, integer *lda, integer *sdim, doublereal *wr, 
             doublereal *wi, doublereal *vs, integer *ldvs, doublereal *work, 
             integer *lwork, logical *bwork, integer *info );
int dgesv_ ( integer *n, integer *nrhs, doublereal *a, integer *lda,
             integer *ipiv, doublereal *b, integer *ldb, integer *info );

/* single precision functions */
int spptrf_ ( char *uplo, integer *n, real *ap, integer *info );
int spptri_ ( char *uplo, integer *n, real *ap, integer *info );
int stptri_ ( char *uplo, char *diag, integer *n, real *ap,
              integer *info );
int sgetf2_ ( integer *m, integer *n, real *a, integer *lda,
              integer *ipiv, integer *info );
int sgetrf_ ( integer *m, integer *n, real *a, integer *lda,
              integer *ipiv, integer *info );
int sgetri_ ( integer *n, real *a, integer *lda, integer *ipiv,
              real *work, integer *lwork, integer *info );
int sspev_ ( char *jobz, char *uplo, integer *n, real *ap,
             real *w, real *z, integer *ldz, real *work, 
             integer *info );
int sgeqrf_ ( integer *m, integer *n, real *a, integer *lda,
              real *tau, real *work, integer *lwork,
              integer *info );
int sgeqr2_ ( integer *m, integer *n, real *a, integer *lda,
              real *tau, real *work, integer *info );
int sgelqf_ ( integer *m, integer *n, real *a, integer *lda,
              real *tau, real *work, integer *lwork,
              integer *info );
int sgelq2_ ( integer *m, integer *n, real *a, integer *lda,
              real *tau, real *work, integer *info );
int sorgqr_ ( integer *m, integer *n, integer *k, real *a, integer *lda,
              real *tau, real *work, integer *lwork, 
              integer *info );
int sorg2r_ ( integer *m, integer *n, integer *k, real *a, integer *lda,
              real *tau, real *work, integer *info );
int sorglq_ ( integer *m, integer *n, integer *k, real *a, integer *lda,
              real *tau, real *work, integer *lwork,
              integer *info );
int sorgl2_( integer *m, integer *n, integer *k, real *a, integer *lda,
             real *tau, real *work, integer *info );
int sorg2l_ ( integer *m, integer *n, integer *k, real *a, integer *lda,
              real *tau, real *work, integer *info );
int sgesvd_ ( char *jobu, char *jobvt, integer *m, integer *n, 
              real *a, integer *lda, real *s,
              real *u, integer *ldu, real *vt, integer *ldvt,
              real *work, integer *lwork, integer *info );
int sgeev_ ( char *jobvl, char *jobvr, integer *n, real *a, integer *lda,
             real *wr, real *wi, real *vl, 
             integer *ldvl, real *vr, integer *ldvr, real *work, 
             integer *lwork, integer *info );
int sgees_ ( char *jobvs, char *sort, L_fp select, integer *n, 
             real *a, integer *lda, integer *sdim, real *wr, real *wi,
             real *vs, integer *ldvs, real *work, integer *lwork,
             logical *bwork, integer *info );
int sgesv_ ( integer *n, integer *nrhs, real *a, integer *lda, 
             integer *ipiv, real *b, integer *ldb, integer *info );

#undef integer
#undef real
#undef doublereal

#endif /* #ifdef HAVE_LAPACK */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_CLAPACK_EXTERN_H */
