/**************************************************************************
*
* File:          $RCSfile: dlamch.h,v $
* Module:        CLAPACK function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.2 $
* Last edited:   $Date: 2005/02/25 09:30:23 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_DLAMCH_H
#define _GAN_DLAMCH_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/linalg_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* only declare this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

double gan_dlamch(Gan_LapackLamchFlag cmach);
Gan_Bool gan_dlamc1(long *beta, long *t, Gan_Bool *rnd, Gan_Bool *ieee1);
Gan_Bool gan_dlamc2(long *beta, long *t, Gan_Bool *rnd, 
                    double *eps, long *emin, double *rmin, long *emax, 
                    double *rmax);
double gan_dlamc3(double a, double b);
Gan_Bool gan_dlamc4(long *emin, double start, long base);
Gan_Bool gan_dlamc5(long beta, long p, long emin, Gan_Bool ieee,
                    long *emax, double *rmax);

#endif /* #if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_DLAMCH_H */

