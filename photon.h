#ifndef __PHOTON_H
#define __PHOTON_H

#include "linalg.h"

typedef struct {
	Vec3D *pos;
	Vec3D *dir;
	double tau_r;
} Photon;

Photon* generate_photon(Vec3D* pos, Vec3D* dir);

#endif // __PHOTON_H
