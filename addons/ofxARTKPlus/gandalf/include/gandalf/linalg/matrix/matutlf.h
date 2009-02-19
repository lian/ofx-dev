/*  matutl.h    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 */

/* Utility routines for real and complex matrix computations
 */
#ifndef CPX
struct ccmf_complex {float re,im;};
typedef struct ccmf_complex Cpx;
#define CPX 1
#endif
void ccmf_trnm(float *a,int m);
void ccmf_trncm(Cpx *s,int n);
void ccmf_house(float *w,float *v,float *u,int m);
int ccmf_qrevec(float *ev,float *v,float *d,int m);
int ccmf_qreval(float *e,float *d,int m);
void ccmf_hconj(Cpx *a,int m);
void ccmf_chouse(Cpx *h,float *e,float *d,int m);
void ccmf_chousv(Cpx *h,float *d, float *u,int m);
void ccmf_qrecvc(float *e,Cpx *v,float *d,int m);
void ccmf_cmmul(Cpx *a,Cpx *b,Cpx *c,int m);
void ccmf_atou1(float *r,int i,int j);
void ccmf_atovm(float *r,int i);
int ccmf_qrbdu1(float *w,float *x,float *y,int k,float *z,int l);
void ccmf_ldumat(float *x,float *y,int i,int k);
void ccmf_ldvmat(float *x,float *y,int k);
int ccmf_qrbdv(float *x,float *y,float *z,int i,float *w,int j);
int ccmf_qrbdi(float *x,float *y,int l);
