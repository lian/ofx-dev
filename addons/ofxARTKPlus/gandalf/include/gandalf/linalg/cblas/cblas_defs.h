/**************************************************************************
*
* File:          $RCSfile: cblas_defs.h,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.3 $
* Last edited:   $Date: 2001/10/04 16:27:00 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_CLAPACK_H
#define _GAN_CLAPACK_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_LAPACK
typedef enum { GAN_TRANSPOSE, GAN_NOTRANSPOSE }
 Gan_TposeFlag;

typedef enum { GAN_INVERT, GAN_NOINVERT }
 Gan_InvertFlag;

typedef enum { GAN_LOWER, GAN_UPPER }
 Gan_UpLoFlag;

typedef enum { GAN_UNIT, GAN_NOUNIT }
 Gan_UnitFlag;

#endif /* #ifndef HAVE_LAPACK */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_CLAPACK_H */

