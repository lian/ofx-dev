/**************************************************************************
*
* File:          $RCSfile: strtri.h,v $
* Module:        CLAPACK function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.5 $
* Last edited:   $Date: 2005/02/25 09:30:25 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_STRTRI_H
#define _GAN_STRTRI_H

#include <gandalf/common/misc_defs.h>
#include <gandalf/linalg/clapack/strti2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* only declare this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

/* we haven't defined this function designed to use level 3 BLAS, so define it
 * to the level 2 BLAS version we do have
 */
#define gan_strtri(upper,unit,n,a,lda,info) gan_strti2(upper,unit,n,a,lda,info)
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_STRTRI_H */

