#include "linalg.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vec3D e1 = {1.0, 0.0, 0.0};
Vec3D e2 = {0.0, 1.0, 0.0};
Vec3D e3 = {0.0, 0.0, 1.0};

double vmulv(Vec3D* v1, Vec3D* v2)
{
	return (v1->x)*(v2->x) + (v1->y)*(v2->y) + (v1->z)*(v2->z);
}

Vec3D* _vmuls(Vec3D* self, double s)
{
	self->x *= s;
	self->y *= s;
	self->z *= s;
	return self;
}

Vec3D* vmuls(Vec3D* v, double s)
{
	Vec3D* ret;
	ret = malloc(sizeof(Vec3D));
	*ret = *v;
	return _vmuls(ret, s);
}


Vec3D* _vsubv(Vec3D* self, Vec3D* v)
{
	self->x -= v->x;
	self->y -= v->y;
	self->z -= v->z;
	return self;
}

Vec3D* vsubv(Vec3D* v1, Vec3D* v2)
{
	Vec3D* ret;
	ret = malloc(sizeof(Vec3D));
	*ret = *v1;
	return _vsubv(ret, v2);
}

Vec3D* _vaddv(Vec3D* self, Vec3D* v)
{
	self->x += v->x;
	self->y += v->y;
	self->z += v->z;
	return self;
}

Vec3D* vaddv(Vec3D* v1, Vec3D* v2)
{
	Vec3D* ret;
	ret = malloc(sizeof(Vec3D));
	*ret = *v1;
	return _vaddv(ret, v2);
}

Vec3D* _mmulv(Vec3D* self, Mat3D* m)
{
	self->x = m->m11*self->x + m->m12*self->y + m->m13*self->z;
	self->y = m->m21*self->x + m->m22*self->y + m->m23*self->z;
	self->z = m->m31*self->x + m->m32*self->y + m->m33*self->z;
	return self;
}

Vec3D* mmulv(Vec3D* v, Mat3D* m)
{
	Vec3D* ret;
	ret = malloc(sizeof(Vec3D));
	*ret = *v;
	return _mmulv(ret, m);
}

double length(Vec3D* v)
{
	return sqrt(vmulv(v,v));
}

Vec3D* _normalize(Vec3D* self)
{
	double len = length(self);
	self->x /= len; self->y /= len; self->z /= len;
	return self;
}

Vec3D* normalize(Vec3D* v)
{
	Vec3D* ret;
	ret = malloc(sizeof(Vec3D));
	*ret = *v;
	return _normalize(ret);
}

Vec3D* new_Vec3D(double x, double y, double z)
{
	Vec3D* ret = (Vec3D*)malloc(sizeof(Vec3D));
	ret->x = x; ret->y = y; ret->z = z;
	return ret;
}

Vec3D* new_Vec3D_spherical(double r, double t, double p)
{
	Vec3D* ret = (Vec3D*)malloc(sizeof(Vec3D));
	ret->x = r * sin(t) * cos(p);
	ret->y = r * sin(t) * sin(p);
	ret->z = r * cos(t);
	return ret;
}

char* show(Mat3D* self)
{
	char* ret = (char*)malloc(60);
	char* fmt = "| %.1f %.1f %.1f |\n| %.1f %.1f %.1f |\n| %.1f %.1f %.1f |\n";
	size_t last = snprintf(ret, 59, fmt,
			self->m11, self->m12, self->m13,
			self->m21, self->m22, self->m23,
			self->m31, self->m32, self->m33);
	ret[last] = 0;
	return ret;
}
