/**************************************************************************
*
* File:          $RCSfile: sgelqf.h,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.3 $
* Last edited:   $Date: 2005/02/25 09:30:24 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_SGELQF_H
#define _GAN_SGELQF_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/clapack/sgelq2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* only declare this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

/* we haven't defined this function designed to use level 3 BLAS, so define it
 * to the level 2 BLAS version we do have
 */
#define gan_sgelqf(m,n,a,lda,tau,work,lwork,info)\
           (assert(lwork>=m),gan_sgelq2(m,n,a,lda,tau,work,info))
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_SGELQF_H */

