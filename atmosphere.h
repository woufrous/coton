#ifndef __ATMOSPHERE_H
#define __ATMOSPHERE_H

#include "photon.h"
#include "linalg.h"

typedef double (*PropDistFunction)(double);

typedef struct {
	PropDistFunction pdf;
	double beta_scat;
} Scatterer;

typedef struct {
	Vec3D pos;
	Vec3D dim;
	double beta_abs;
	Scatterer* molecular;
	Scatterer* cloud;
} Box;

double rayleighPDF(double r);
double henyeyGreensteinPDF(double r);
double tauPDF(double r);
double azimuthPDF(double r);
double unityPDF(double r);


#endif // __ATMOSPHERE_H
