#ifndef __ATMOSPHERE_H
#define __ATMOSPHERE_H

typedef Photon* (*ScatterFunction)(Photon*);

typedef struct {
	Vec3D pos;
	Vec3D dim;
	double beta_scat;
	double beta_abs;
	ScatterFunction scatter;
} Box;

#endif // __ATMOSPHERE_H
