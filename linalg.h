#ifndef __LINALG_H
#define __LINALG_H

typedef struct {
	double x;
	double y;
	double z;
} Vec3D;

extern Vec3D e1;
extern Vec3D e2;
extern Vec3D e3;

Vec3D* new_Vec3D(double x, double y, double z);

typedef struct {
	double m11, m12, m13;
	double m21, m22, m23;
	double m31, m32, m33;
} Mat3D;

char* show(Mat3D* self);

double vmulv(Vec3D* a, Vec3D* b);
Vec3D* mmulv(Mat3D* m, Vec3D* v);


#endif // __LINALG_H
