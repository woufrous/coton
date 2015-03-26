#ifndef __LINALG_H
#define __LINALG_H

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

double radtodeg(double rad);
double degtorad(double deg);

typedef struct {
	double x;
	double y;
	double z;
} Vec3D;

extern Vec3D e1;
extern Vec3D e2;
extern Vec3D e3;

Vec3D* new_Vec3D(double x, double y, double z);
Vec3D* new_Vec3D_spherical(double r, double t, double p);

typedef struct {
	double m11, m12, m13;
	double m21, m22, m23;
	double m31, m32, m33;
} Mat3D;

/* rotation matrices
 * -----------------
 *  several rotation matrices
 */
Mat3D* new_Mat3D_rotationAround(Vec3D* n, double a);

char* show(Mat3D* self);

/* vector algebra
 * ---------------
 *  functions starting with an underscore modify the self vector and return self
 *
 *  functions without underscore allocate a new vector
 */

double vmulv(Vec3D* v1, Vec3D* v2);

Vec3D* vmuls(Vec3D* v, double s);
Vec3D* _vmuls(Vec3D* self, double s);

Vec3D* vsubv(Vec3D* v1, Vec3D* v2);
Vec3D* _vsubv(Vec3D* self, Vec3D* v);

Vec3D* vaddv(Vec3D* v1, Vec3D* v2);
Vec3D* _vaddv(Vec3D* self, Vec3D* v);

Vec3D* normalize(Vec3D* v);
Vec3D* _normalize(Vec3D* self);

Vec3D* mmulv(Vec3D* v, Mat3D* m);
Vec3D* _mmulv(Vec3D* self, Mat3D* m);

// Vec3D* perpendicular(Vec3D* v);

double length(Vec3D* v);


#endif // __LINALG_H
