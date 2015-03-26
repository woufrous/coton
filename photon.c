#include "photon.h"

#include <stdlib.h>

Photon* new_Photon(Vec3D* pos, Vec3D* dir, double tau_r)
{
	Photon* ret;
	ret = (Photon*)malloc(sizeof(Photon));
	ret->pos = (Vec3D*)malloc(sizeof(Vec3D));
	*(ret->pos) = *pos;
	ret->dir = (Vec3D*)malloc(sizeof(Vec3D));
	*(ret->dir) = *dir;
	ret->tau_r = tau_r;
	return ret;
}
