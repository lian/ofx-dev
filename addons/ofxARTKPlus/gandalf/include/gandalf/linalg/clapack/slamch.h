/**************************************************************************
*
* File:          $RCSfile: slamch.h,v $
* Module:        CLAPACK function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.2 $
* Last edited:   $Date: 2005/02/25 09:30:24 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_SLAMCH_H
#define _GAN_SLAMCH_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/linalg_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* only declare this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

float gan_slamch(Gan_LapackLamchFlag cmach);
Gan_Bool gan_slamc1(long *beta, long *t, Gan_Bool *rnd, Gan_Bool *ieee1);
Gan_Bool gan_slamc2(long *beta, long *t, Gan_Bool *rnd, 
                    float *eps, long *emin, float *rmin, long *emax, 
                    float *rmax);
float gan_slamc3(float a, float b);
Gan_Bool gan_slamc4(long *emin, float start, long base);
Gan_Bool gan_slamc5(long beta, long p, long emin, Gan_Bool ieee,
                    long *emax, float *rmax);

#endif /* #if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_SLAMCH_H */

