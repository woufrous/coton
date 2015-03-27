#ifndef __ATMOSPHERE_H
#define __ATMOSPHERE_H

#include "photon.h"
#include "linalg.h"

typedef double (*PropDistFunction)(double);

typedef struct {
	PropDistFunction pdf;
	double beta_scat;
} Scatterer;

Scatterer* new_HenyeyGreensteinScatterer(double beta);

typedef struct Box {
	Vec3D* pos;
	Vec3D* dim;
	double beta_abs;
	Scatterer* molecular;
	Scatterer* cloud;
	struct Box* upper;
	struct Box* lower;
} Box;

Box* read_atmosphere(const char* fn);

void free_atmosphere(Box* atm);

void plot_boxes(Box* n);
Box* get_toa(Box* atm);

Box* new_Box(Vec3D* pos, Vec3D* dim, double b_abs, Scatterer* m, Scatterer* c);

Photon* process_photon(Box* b, Photon* p);

double rayleighPDF(double r);
double henyeyGreensteinPDF(double r);
double tauPDF(double r);
double azimuthPDF(double r);
double unityPDF(double r);


#endif // __ATMOSPHERE_H
