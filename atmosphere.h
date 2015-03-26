#ifndef __ATMOSPHERE_H
#define __ATMOSPHERE_H

#include "photon.h"
#include "linalg.h"

typedef Photon* (*ScatterFunction)(Photon*);

typedef struct {
	Vec3D pos;
	Vec3D dim;
	double beta_scat;
	double beta_abs;
	ScatterFunction scatter;
} Box;

Photon* rayleighScatter(Photon*);
double rayleighPDF(double r);
double henyeyGreensteinPDF(double r);
double tauPDF(double r);
double azimuthPDF(double r);
double unityPDF(double r);

#endif // __ATMOSPHERE_H
