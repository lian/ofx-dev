/**************************************************************************
*
* File:          $RCSfile: extern.h,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.6 $
* Last edited:   $Date: 2001/10/04 16:27:00 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_CBLAS_EXTERN_H
#define _GAN_CBLAS_EXTERN_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_LAPACK

#define integer long
#define real float
#define doublereal double

/* these are prototypes for all the BLAS functions used in Gandalf */

/* double precision functions */
int dscal_ ( integer *n, doublereal *da, doublereal *dx, 
             integer *incx );
int dspr_ ( char *uplo, integer *n, doublereal *alpha, 
            doublereal *x, integer *incx, doublereal *ap );
int dspr2_ ( char *uplo, integer *n, doublereal *alpha, 
             doublereal *x, integer *incx, doublereal *y, integer *incy, 
             doublereal *ap );
doublereal ddot_ ( integer *n, doublereal *dx, integer *incx, doublereal *dy, 
                   integer *incy );
int dgemm_ ( char *transa, char *transb, integer *m, integer *n, integer *k,
             doublereal *alpha, doublereal *a, integer *lda, 
             doublereal *b, integer *ldb, doublereal *beta, doublereal *c,
             integer *ldc );
int dgemv_ ( char *trans, integer *m, integer *n, doublereal *alpha,
             doublereal *a, integer *lda, doublereal *x, integer *incx, 
             doublereal *beta, doublereal *y, integer *incy);
int dtpsv_ ( char *uplo, char *trans, char *diag, integer *n, 
             doublereal *ap, doublereal *x, integer *incx );
int daxpy_ ( integer *n, doublereal *da, doublereal *dx, 
             integer *incx, doublereal *dy, integer *incy );
int dcopy_ ( integer *n, doublereal *dx, integer *incx, 
             doublereal *dy, integer *incy );
int dspmv_ ( char *uplo, integer *n, doublereal *alpha, 
             doublereal *ap, doublereal *x, integer *incx, doublereal *beta, 
             doublereal *y, integer *incy );
int dger_ ( integer *m, integer *n, doublereal *alpha, 
            doublereal *x, integer *incx, doublereal *y, integer *incy, 
            doublereal *a, integer *lda );

/* single precision functions */
int sscal_ ( integer *n, real *da, real *dx, integer *incx );
int sspr_ ( char *uplo, integer *n, real *alpha, 
            real *x, integer *incx, real *ap );
int sspr2_ ( char *uplo, integer *n, real *alpha, 
             real *x, integer *incx, real *y, integer *incy, real *ap );
doublereal sdot_ ( integer *n, real *dx, integer *incx, real *dy,
                   integer *incy );
int sgemm_ ( char *transa, char *transb, integer *m, integer *n, integer *k,
             real *alpha, real *a, integer *lda, 
             real *b, integer *ldb, real *beta, real *c,
             integer *ldc );
int sgemv_ ( char *trans, integer *m, integer *n, real *alpha,
             real *a, integer *lda, real *x, integer *incx, 
             real *beta, real *y, integer *incy);
int stpsv_ ( char *uplo, char *trans, char *diag, integer *n, 
             real *ap, real *x, integer *incx );
int saxpy_ ( integer *n, real *da, real *dx, 
             integer *incx, real *dy, integer *incy );
int scopy_ ( integer *n, real *dx, integer *incx, real *dy, integer *incy );
int sspmv_ ( char *uplo, integer *n, real *alpha, 
             real *ap, real *x, integer *incx, real *beta, 
             real *y, integer *incy );
int sger_ ( integer *m, integer *n, real *alpha, 
            real *x, integer *incx, real *y, integer *incy, 
            real *a, integer *lda );

#undef real
#undef doublereal
#undef integer

#endif /* #ifdef HAVE_LAPACK */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_CBLAS_EXTERN_H */
