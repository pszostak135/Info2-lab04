#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include <stdlib.h>
#include "rk4.h"

double fun(double t, double y)
{
	return 2*y;
}

double y_anl(double t, double t0, double y0)
{
	return y0*exp(2*(t-t0));
}

void main()
{
	double t0=0;
    double y0=1;
	double tk=2;
	double h=0.1;
	double t=t0;
	double y_eul=y0;
	double y_rk4=y0;
	double eps_eul;
	double eps_rk4;

	for(int i=0;t<tk;i++)
	{
		y_eul+=h*fun(t,y_eul);
		y_rk4= rk4(t, y_rk4, h, fun);
		t+=h;
		eps_eul= abs((y_eul-y_anl(t,t0,y0))/y_anl(t,t0,y0));
		eps_rk4= abs((y_rk4-y_anl(t,t0,y0))/y_anl(t,t0,y0));
		printf("t%d=%.2lf\t y_eul=%.6lf\t y_rk4=%.6lf\t eps_eul=%.6lf\t eps_rk4=%.6lf\n ", i,t,y_eul,y_rk4,eps_eul,eps_rk4);
	}

		FILE *f;
	f=fopen("info0204.txt", "w");

	double N;
	for(int i=0;i<7;i++)
	{
		N=pow(2.0,i);
		h=(tk-to)/N;
		t=t0;
	    y_eul=y0;
	    y_rk4=y0;
		for(int j=0;j<=N;j++)
	    {
		    t+=h;
		    y_eul+=h*fun(t,y_eul);
		    y_rk4= rk4(t, y_rk4, h, fun);
			eps_eul= abs((y_eul-y_anl(t,t0,y0))/y_anl(t,t0,y0));
		    eps_rk4= abs((y_rk4-y_anl(t,t0,y0))/y_anl(t,t0,y0)); 	
	    }
		fprintf(f, "liczba krokow N: %lf\t dlugosc kroku h: %lf\t blad metody eulera: %lf\t blad metody rk4: %lf\n", N,h,eps_eul,eps_rk4);		
	}
	
	fclose(f);
	
	

	wait();
}