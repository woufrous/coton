#include "photon.h"

#include <stdlib.h>

Photon* generate_photon(Vec3D* pos, Vec3D* dir)
{
	Photon* ret;
	ret = (Photon*)malloc(sizeof(Photon));
	ret->pos = pos;
	ret->dir = dir;
	return ret;
}
