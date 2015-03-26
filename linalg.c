#include "linalg.h"

#include <stdio.h>
#include <stdlib.h>

Vec3D e1 = {1.0, 0.0, 0.0};
Vec3D e2 = {0.0, 1.0, 0.0};
Vec3D e3 = {0.0, 0.0, 1.0};

double vmulv(Vec3D* a, Vec3D* b)
{
	return (a->x)*(b->x) + (a->y)*(b->y) + (a->z)*(b->z);
}

void mmull(Vec3D* self, Mat3D* m)
{
	self->x = m->m11*self->x + m->m12*self->y + m->m13*self->z;
	self->y = m->m21*self->x + m->m22*self->y + m->m23*self->z;
	self->z = m->m31*self->x + m->m32*self->y + m->m33*self->z;
}

Vec3D* mmulv(Mat3D* m, Vec3D* v)
{
	Vec3D* ret;
	ret = malloc(sizeof(Vec3D));
	*ret = *v;
	mmull(ret, m);
	return ret;
}

Vec3D* new_Vec3D(double x, double y, double z)
{
	Vec3D* ret = (Vec3D*)malloc(sizeof(Vec3D));
	ret->x = x; ret->y = y; ret->z = z;
	return ret;
}

char* show(Mat3D* self)
{
	char* ret = (char*)malloc(60);
	char* fmt = "| %.1f %.1f %.1f |\n| %.1f %.1f %.1f |\n| %.1f %.1f %.1f |\n";
	snprintf(ret, 59, fmt,
			self->m11, self->m12, self->m13,
			self->m21, self->m22, self->m23,
			self->m31, self->m32, self->m33);
	return ret;
}
