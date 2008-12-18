/*
 *  ofx2dSolver.h
 *  openFrameworks
 *
 *  Created by Alain Ramos a.k.a. ding
 *  Copyright 2008 Alain Ramos.
 *
 *
 For Free you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 */
//	----------------------------------------------------------------------------------------------------

#ifndef OF_2D_SOLVER_H
#define OF_2D_SOLVER_H


#include <math.h>

#define IX(i,j) ((i)+(N+2)*(j))
#define SWAP(x0,x) {float * tmp=x0;x0=x;x=tmp;}
#define SWAP_RGB(i0,i,j0,j,k0,k) {float * tmp; tmp=i0;i0=i;i=tmp; tmp=j0;j0=j;j=tmp; tmp=k0;k0=k;k=tmp;}
#define FOR_EACH_CELL for ( i=1 ; i<=N ; i++ ) { for ( j=1 ; j<=N ; j++ ) {
#define END_FOR }}


class ofx2dSolver {
		
	public:
	
		//////////
		// Constructors
		ofx2dSolver() {
						
			epsilon = 5; //curl
			smallf = 0.0000001f;
			
			N = 100; //grid
			dt = 0.2f; //timestep
			diff = 0.0005f; //diffuse
			visc = 0.0001f; //viscocity

			
			size = (N+2)*(N+2);
			
			r			= new float [size];
			g			= new float [size];
			b			= new float [size];
			r0			= new float [size];
			g0			= new float [size];
			b0			= new float [size];	
			u			= new float [size];
			v			= new float [size];
			u_prev		= new float [size];
			v_prev		= new float [size];
			dens		= new float [size];	
			dens_prev	= new float [size];
			blocked		= new bool	[size];
			
			for ( int i = 0 ; i < size ; i++ ) {
				u[i] = v[i] = u_prev[i] = v_prev[i] = dens[i] = dens_prev[i] = 0.0f;
				r[i] = r0[i] = g[i] = g0[i] = b[i] = b0[i] = 0.0f;
				blocked[i] = false;
			}
			
		}
	
		//constructor that sets the grid size
		ofx2dSolver(int _n) {
		
			epsilon = 5; //curl
			smallf = 0.0000001f;
		
			N = _n; //grid
			dt = 0.2f; //timestep
			diff = 0.0005f; //diffuse
			visc = 0.0001f; //viscocity
		
		
			size = (N+2)*(N+2);
		
			r			= new float [size];
			g			= new float [size];
			b			= new float [size];
			r0			= new float [size];
			g0			= new float [size];
			b0			= new float [size];	
			u			= new float [size];
			v			= new float [size];
			u_prev		= new float [size];
			v_prev		= new float [size];
			dens		= new float [size];	
			dens_prev	= new float [size];
			blocked		= new bool	[size];
		
			for ( int i = 0 ; i < size ; i++ ) {
				u[i] = v[i] = u_prev[i] = v_prev[i] = dens[i] = dens_prev[i] = 0.0f;
				r[i] = r0[i] = g[i] = g0[i] = b[i] = b0[i] = 0.0f;
				blocked[i] = false;
			}
		
		}
	
		//////////
		// Destructor
		 ~ofx2dSolver() {
		 	delete[] r;
			delete[] g;
			delete[] b;
			delete[] r0;
			delete[] g0;
			delete[] b0;
			delete[] u;
			delete[] v;
			delete[] u_prev;
			delete[] v_prev;
			delete[] dens;
			delete[] dens_prev;
			delete[] blocked;
		}
		
		
		//////////
		// The Variables
		bool * blocked;
	
		//color density variables
		float * r, * g, * b;
		float * r0, * g0, * b0;
		//gray scale density variables
		float * dens, * dens_prev;
		//velocities
		float * u, * v, * u_prev, * v_prev;
	
		int size;
		int N;
		float dt, diff, visc;
		float epsilon;
		float smallf;
	
		
	//////////
	// the solver
	
	//add source single color
	void add_source (float * x, float * s) {
		for ( int i=0 ; i<size ; i++ ) x[i] += dt*s[i];
	}
	
	void add_source_rgb (float * _r, float * _r0, float * _g, float * _g0, float * _b, float * _b0) {
		for ( int i=0 ; i<size ; i++ ) {
			_r[i] += dt*_r0[i];
			_g[i] += dt*_g0[i];
			_b[i] += dt*_b0[i];
		}
	}
	
	//set boundries for single color
	void set_bnd ( int b, float * x ) {
		int i,j;
		for ( i=1 ; i<=N ; i++ ) {
			x[IX(0  ,i)] = b==1 ? 0 : x[IX(1,i)];
			x[IX(N+1,i)] = b==1 ? 0 : x[IX(N,i)];
			x[IX(i,0  )] = b==2 ? 0 : x[IX(i,1)];
			x[IX(i,N+1)] = b==2 ? 0 : x[IX(i,N)];
		}
		
		FOR_EACH_CELL
		if(!blocked[IX(i,j)]) continue;
		if( (b==1) || (b==2) ) {
			x[IX(i,j)]=0;
		}
		else {
			int count  =0;
			float total=0;
			if(!blocked[IX(i+1,j)]) { count++; total+=x[IX(i+1,j)]; }
			if(!blocked[IX(i-1,j)]) { count++; total+=x[IX(i-1,j)]; }		
			if(!blocked[IX(i,j+1)]) { count++; total+=x[IX(i,j+1)]; }
			if(!blocked[IX(i,j-1)]) { count++; total+=x[IX(i,j-1)]; }
			if(count) total/=count;
			x[IX(i,j)]=total;
		}
		END_FOR
	}
	
	//set boundries for r g b
	void set_bnd_rgb ( int b, float * _r, float * _g, float * _b ) {
		int i,j;
		for ( i=1 ; i<=N ; i++ ) {
			_r[IX(0  ,i)] = b==1 ? 0 : _r[IX(1,i)];
			_r[IX(N+1,i)] = b==1 ? 0 : _r[IX(N,i)];
			_r[IX(i,0  )] = b==2 ? 0 : _r[IX(i,1)];
			_r[IX(i,N+1)] = b==2 ? 0 : _r[IX(i,N)];
			
			_g[IX(0  ,i)] = b==1 ? 0 : _g[IX(1,i)];
			_g[IX(N+1,i)] = b==1 ? 0 : _g[IX(N,i)];
			_g[IX(i,0  )] = b==2 ? 0 : _g[IX(i,1)];
			_g[IX(i,N+1)] = b==2 ? 0 : _g[IX(i,N)];
			
			_b[IX(0  ,i)] = b==1 ? 0 : _b[IX(1,i)];
			_b[IX(N+1,i)] = b==1 ? 0 : _b[IX(N,i)];
			_b[IX(i,0  )] = b==2 ? 0 : _b[IX(i,1)];
			_b[IX(i,N+1)] = b==2 ? 0 : _b[IX(i,N)];
		}
		
		FOR_EACH_CELL
		if(!blocked[IX(i,j)]) continue;
		if( (b==1) || (b==2) ) {
			_r[IX(i,j)]=0;
			_g[IX(i,j)]=0;
			_b[IX(i,j)]=0;
		}
		else {
			int count  =0;
			float total_r=0;
			float total_g=0;
			float total_b=0;
			if(!blocked[IX(i+1,j)]) { count++; total_r+=_r[IX(i+1,j)]; total_g+=_g[IX(i+1,j)]; total_b+=_b[IX(i+1,j)];}
			if(!blocked[IX(i-1,j)]) { count++; total_r+=_r[IX(i-1,j)]; total_g+=_g[IX(i-1,j)]; total_b+=_b[IX(i-1,j)];}		
			if(!blocked[IX(i,j+1)]) { count++; total_r+=_r[IX(i,j+1)]; total_g+=_g[IX(i,j+1)]; total_b+=_b[IX(i,j+1)];}
			if(!blocked[IX(i,j-1)]) { count++; total_r+=_r[IX(i,j-1)]; total_g+=_g[IX(i,j-1)]; total_b+=_b[IX(i,j-1)];}
			if(count){
				total_r/=count;
				total_g/=count;
				total_b/=count;
			}
			_r[IX(i,j)]=total_r;
			_g[IX(i,j)]=total_g;
			_b[IX(i,j)]=total_b;
		}
		END_FOR
	}
	
	//linear solver for single color//
	void lin_solve ( int b, float * x, float * x0, float a, float c ) {
		int i, j;
		
		for ( int k=0 ; k<20 ; k++ ) {
			FOR_EACH_CELL
			x[IX(i,j)] = (x0[IX(i,j)] + a*(x[IX(i-1,j)]+x[IX(i+1,j)]+x[IX(i,j-1)]+x[IX(i,j+1)]))/c;
			END_FOR
			
			set_bnd ( b, x );
		}
		
	}
	
	//linear solver for r g b
	void lin_solve_rgb ( int b, float * _r, float * _r0,
								float * _g, float * _g0,
								float * _b, float * _b0,
								float a, float c ) {
		int i, j;
		
		for ( int k=0 ; k<20 ; k++ ) {
			FOR_EACH_CELL
			_r[IX(i,j)] = (_r0[IX(i,j)] + a*(_r[IX(i-1,j)]+_r[IX(i+1,j)]+_r[IX(i,j-1)]+_r[IX(i,j+1)]))/c;
			_g[IX(i,j)] = (_g0[IX(i,j)] + a*(_g[IX(i-1,j)]+_g[IX(i+1,j)]+_g[IX(i,j-1)]+_g[IX(i,j+1)]))/c;
			_b[IX(i,j)] = (_b0[IX(i,j)] + a*(_b[IX(i-1,j)]+_b[IX(i+1,j)]+_b[IX(i,j-1)]+_b[IX(i,j+1)]))/c;
			END_FOR
			
			set_bnd_rgb ( b, _r, _g, _b );
		}
		
	}
	
	//diffuse single color
	void diffuse ( int N, int b, float * x, float * x0, float diff, float dt ) {
		float a=dt*diff*N*N;
		lin_solve ( b, x, x0, a, 1+4*a );
	}
	
	//diffuse r g b
	void diffuse_rgb ( int b, float * _r, float * _r0,
							  float * _g, float * _g0,
							  float * _b, float * _b0,
							  float diff, float dt ) {
		float a=dt*diff*N*N;
		lin_solve_rgb ( b, _r, _r0, _g, _g0, _b, _b0, a, 1+4*a );
	}
		
	//advect single color	
	void advect ( int N, int b, float * d, float * d0, float * u, float * v, float dt ) {
		int i, j, i0, j0, i1, j1;
		float x, y, s0, t0, s1, t1, dt0, vx, vy, tleft,t,tnext,distx,disty;
		
		dt0 = dt*N;
		
		
		FOR_EACH_CELL
		
		if(blocked[IX(i,j)]) continue;
		
		tleft=dt0;
		x=i;y=j;		
		
		while(tleft>smallf) {
			
			//enforce boundry contraints
			if (x<0.5f) x=0.5f; if (x>N+0.5f) x=N+0.5f; 
			if (y<0.5f) y=0.5f; if (y>N+0.5f) y=N+0.5f; 
			
			
			i0=(int)x; i1=i0+1;
			j0=(int)y; j1=j0+1;
			s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
			
			vx = -(s0*(t0*u[IX(i0,j0)]+t1*u[IX(i0,j1)])+
				   s1*(t0*u[IX(i1,j0)]+t1*u[IX(i1,j1)]));
			
			vy = -(s0*(t0*v[IX(i0,j0)]+t1*v[IX(i0,j1)])+
				   s1*(t0*v[IX(i1,j0)]+t1*v[IX(i1,j1)]));
			
			
			float speed2=vx*vx+vy*vy; 
			if(speed2>smallf) tnext=.5/sqrt(speed2);
			else tnext=tleft;
			
			t=tnext > tleft ? tleft : tnext;
			tleft-=t;
			
			
			x+=t*vx;
			y+=t*vy;
		}
		
		
		if (x<0.5f) x=0.5f; if (x>N+0.5f) x=N+0.5f; 
		if (y<0.5f) y=0.5f; if (y>N+0.5f) y=N+0.5f; 
		
		
		i0=(int)x; i1=i0+1;
		j0=(int)y; j1=j0+1;
		s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
		
		d[IX(i,j)] = s0*(t0*d0[IX(i0,j0)]+t1*d0[IX(i0,j1)])+
		s1*(t0*d0[IX(i1,j0)]+t1*d0[IX(i1,j1)]);
		END_FOR
		set_bnd ( b, d );
	}
	
	
	void advect_rgb (int b, float * _r, float * _r0,
							float * _g, float * _g0,
							float * _b, float * _b0,
							float * _u, float * _v, float dt ) {
		int i, j, i0, j0, i1, j1;
		float x, y, s0, t0, s1, t1, dt0, vx, vy, tleft,t,tnext,distx,disty;
		
		dt0 = dt*N;
		
		
		FOR_EACH_CELL
		
		if(blocked[IX(i,j)]) continue;
		
		tleft=dt0;
		x=i;y=j;		
		
		while(tleft>smallf) {
			
			//enforce boundry contraints
			if (x<0.5f) x=0.5f; if (x>N+0.5f) x=N+0.5f; 
			if (y<0.5f) y=0.5f; if (y>N+0.5f) y=N+0.5f; 
			
			
			i0=(int)x; i1=i0+1;
			j0=(int)y; j1=j0+1;
			s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
			
			vx = -(s0*(t0*u[IX(i0,j0)]+t1*u[IX(i0,j1)])+
				   s1*(t0*u[IX(i1,j0)]+t1*u[IX(i1,j1)]));
			
			vy = -(s0*(t0*v[IX(i0,j0)]+t1*v[IX(i0,j1)])+
				   s1*(t0*v[IX(i1,j0)]+t1*v[IX(i1,j1)]));
			
			
			float speed2=vx*vx+vy*vy; 
			if(speed2>smallf) tnext=.5/sqrt(speed2);
			else tnext=tleft;
			
			t=tnext > tleft ? tleft : tnext;
			tleft-=t;
			
			
			x+=t*vx;
			y+=t*vy;
		}
		
		
		if (x<0.5f) x=0.5f; if (x>N+0.5f) x=N+0.5f; 
		if (y<0.5f) y=0.5f; if (y>N+0.5f) y=N+0.5f; 
		
		
		i0=(int)x; i1=i0+1;
		j0=(int)y; j1=j0+1;
		s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
		
		_r[IX(i,j)] = s0*(t0*_r0[IX(i0,j0)]+t1*_r0[IX(i0,j1)])+s1*(t0*_r0[IX(i1,j0)]+t1*_r0[IX(i1,j1)]);
		_g[IX(i,j)] = s0*(t0*_g0[IX(i0,j0)]+t1*_g0[IX(i0,j1)])+s1*(t0*_g0[IX(i1,j0)]+t1*_g0[IX(i1,j1)]);
		_b[IX(i,j)] = s0*(t0*_b0[IX(i0,j0)]+t1*_b0[IX(i0,j1)])+s1*(t0*_b0[IX(i1,j0)]+t1*_b0[IX(i1,j1)]);
		END_FOR
		set_bnd_rgb ( b, _r, _g, _b );
	}
							  
	
	//prject velocities
	void project ( int N, float * u, float * v, float * p, float * div ) {
		int i, j;
		
		FOR_EACH_CELL
		div[IX(i,j)] = -0.5f*(u[IX(i+1,j)]-u[IX(i-1,j)]+v[IX(i,j+1)]-v[IX(i,j-1)])/N;
		p[IX(i,j)] = 0;
		END_FOR	
		set_bnd ( 0, div ); set_bnd ( 0, p );
		
		lin_solve ( 0, p, div, 1, 4 );
		
		FOR_EACH_CELL
		u[IX(i,j)] -= 0.5f*N*(p[IX(i+1,j)]-p[IX(i-1,j)]);
		v[IX(i,j)] -= 0.5f*N*(p[IX(i,j+1)]-p[IX(i,j-1)]);
		END_FOR
		set_bnd ( 1, u ); set_bnd ( 2, v );
	}
	
	
	//adds curl
	void add_vorocity(int N, float * u, float * v, float dt) {
		
		//vort is just the curl of the velocity field
#define vort(i,j) (( -0.5*( v[IX(i+1,j)]-v[IX(i-1,j)] + u[IX(i,j-1)]-u[IX(i,j+1)] )*N ))
		
		int i, j;
		
		int size = (N+2)*(N+2);
		
		float *fx	=	new float [size];
		float *fy	=	new float [size];
		
		FOR_EACH_CELL
		if(i==1 || j==1 || i==N || j==N) continue;
		
		float dvx = 0.5*(vort(i+1,j)-vort(i-1,j));
		float dvy = 0.5*(vort(i,j+1)-vort(i,j-1));
		
		float mag=sqrt(dvx*dvx+dvy*dvy);
		
		//apply a force equal to epsilon * cross(N,vor)
		fx[IX(i,j)]=mag > smallf ? epsilon*dt*dvy*vort(i,j)/(mag*N) : 0;
		fy[IX(i,j)]=mag > smallf ? epsilon*dt*dvx*vort(i,j)/(mag*N) : 0;
		END_FOR
		
		set_bnd ( 0, fx ); set_bnd ( 0, fy );
		
		
		FOR_EACH_CELL
		if(i==1 || j==1 || i==N || j==N) continue;
		
		if(u[IX(i,j)]) u[IX(i,j)]+=fx[IX(i,j)];
		if(v[IX(i,j)]) v[IX(i,j)]-=fy[IX(i,j)];
		END_FOR
		
		set_bnd ( 1, u ); set_bnd ( 2, v );
		
		delete[] fx;
		delete[] fy;
		
#undef vort
		
	}
	
	void dens_step ( int N, float * x, float * x0, float * u, float * v, float diff, float dt ) {
		add_source ( x, x0 );
		SWAP ( x0, x ); diffuse ( N, 0, x, x0, diff, dt );
		SWAP ( x0, x ); advect ( N, 0, x, x0, u, v, dt );
	}
	
	void dens_step_rgb (float * _r, float * _r0,
						float * _g, float * _g0,
						float * _b, float * _b0,
						float * _u, float * _v,
						float diff, float dt ) {
		add_source_rgb ( _r, _r0, _g, _g0, _b, _b0 );
		SWAP_RGB ( _r0, _r, _g0, _g, _b0, _b );
		diffuse_rgb ( 0, _r, _r0, _g, _g0, _b, _b0, diff, dt );
		SWAP_RGB ( _r0, _r, _g0, _g, _b0, _b );
		advect_rgb ( 0, _r, _r0, _g, _g0, _b, _b0, u, v, dt );
	}
	
	void vel_step ( int N, float * u, float * v, float * u0, float * v0, float visc, float dt ) {
		add_source ( u, u0 ); add_source ( v, v0 );
		SWAP ( u0, u ); diffuse ( N, 1, u, u0, visc, dt );
		SWAP ( v0, v ); diffuse ( N, 2, v, v0, visc, dt );
		project ( N, u, v, u0, v0 );
		SWAP ( u0, u ); SWAP ( v0, v );
		advect ( N, 1, u, u0, u0, v0, dt ); advect ( N, 2, v, v0, u0, v0, dt );
		project ( N, u, v, u0, v0 );
	}
	
};

#endif