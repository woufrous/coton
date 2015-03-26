#include "atmosphere.h"

#include <math.h>

#include "photon.h"
#include "linalg.h"

#define		NORM_R(r)	if ((r>1) || (r<0)) r = 1./fabs(r);
#define __USE_MISC

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

double rayleighPDF(double r)
{
	double u=0, d=0, q=0;

	NORM_R(r);

	q = -8*r + 4;
	d = 1 + (pow(q, 2) / 4.);
	u = pow(-(q/2.) + sqrt(d), 1./3.);

	return (u - (1/u));
}

double henyeyGreensteinPDF(double r)
{
	/* hardcode assymetry parameter to 0.85...good enough */
	double g = 0.85;
	double u=0, v=0, w=0;
	w = g * (2*r - 1) + 1;
	v = (1.-pow(g, 2))/w;
	u = -pow(v, 2) + pow(g, 2) + 1;

	return u/(2*g);
}

double tauPDF(double r)
{
	return -log(1.-r);
}

double azimuthPDF(double r)
{
	return 2*M_PI*r;
}

double unityPDF(double r)
{
	return r;
}

Photon* rayleighScatter(Photon* p_in)
{
	return p_in;
}

Photon* henyeyGreensteinScatter(Photon* p_in)
{
}

