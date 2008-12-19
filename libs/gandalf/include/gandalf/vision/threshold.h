/**
 * Heqder for threshold.c file
 *
 **/

#ifndef _GAN_THRESHOLD_H
#define _GAN_THRESHOLD_H


#include <gandalf/image/io/image_io.h>
#include <math.h>
#include <float.h>
#include "bright_feature.h"


#ifdef __cplusplus
extern "C" {
#endif



GANDALF_API Gan_brightFeatureMap *
  gan_find_bright ( Gan_Image *strength,unsigned short thres, Gan_Matrix23_f *A,
                    Gan_Camera *camera,int status,
                    Gan_LocalFeatureMapParams *lpms,
                    Gan_brightFeatureMap *bright_map );






#ifdef __cplusplus
}
#endif

#endif
