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
struct ccm_complex {double re,im;};
typedef struct ccm_complex Cpx;
#define CPX 1
#endif
void ccm_trnm(double *a,int m);
void ccm_trncm(Cpx *s,int n);
void ccm_house(double *w,double *v,double *u,int m);
int ccm_qrevec(double *ev,double *v,double *d,int m);
int ccm_qreval(double *e,double *d,int m);
void ccm_hconj(Cpx *a,int m);
void ccm_chouse(Cpx *h,double *e,double *d,int m);
void ccm_chousv(Cpx *h,double *d, double *u,int m);
void ccm_qrecvc(double *e,Cpx *v,double *d,int m);
void ccm_cmmul(Cpx *a,Cpx *b,Cpx *c,int m);
void ccm_atou1(double *r,int i,int j);
void ccm_atovm(double *r,int i);
int ccm_qrbdu1(double *w,double *x,double *y,int k,double *z,int l);
void ccm_ldumat(double *x,double *y,int i,int k);
void ccm_ldvmat(double *x,double *y,int k);
int ccm_qrbdv(double *x,double *y,double *z,int i,double *w,int j);
int ccm_qrbdi(double *x,double *y,int l);
