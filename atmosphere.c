#include "atmosphere.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "photon.h"
#include "linalg.h"

#define		NORM_R(r)	if ((r>1) || (r<0)) r = 1./fabs(r);

Photon* process_photon(Box* b, Photon* p)
{
	Vec3D scat_pos;
	Vec3D scat_dir;
	Vec3D helper;
	Mat3D* rot1, *rot2;

	while (1) {
		/* normalize photon direction */
		_normalize(p->dir);

		/* calculate scattering position */
		scat_pos = *(p->dir);
		_vmuls(&scat_pos, p->tau_r/b->molecular->beta_scat);
		_vaddv(&scat_pos, p->pos);

		if ((scat_pos.z < b->pos->z) || (scat_pos.z > (b->pos->z + b->dim->z))) {
			*(p->pos) = scat_pos;
			return p;
		}

		/* calculate scattered direction */
		double t_scat = b->molecular->pdf((double)rand()/RAND_MAX);
		double p_scat = azimuthPDF((double)rand()/RAND_MAX);

		/* construct helper vector */
		helper.x = 0; helper.y = -p->dir->z; helper.z = p->dir->y;
		if (helper.y == 0) helper.z = 1; /* just in case the original vector is e_x */

		/* rotate direction vector */
		_normalize(&helper);
		rot1 = new_Mat3D_rotationAround(&helper, acos(t_scat));
		rot2 = new_Mat3D_rotationAround(p->dir, p_scat);

		scat_dir = *(p->dir);
		_mmulv(&scat_dir, rot1);
		_mmulv(&scat_dir, rot2);

		/* update photon */
		*(p->pos) = scat_pos;
		*(p->dir) = scat_dir;
		p->tau_r = tauPDF((double)rand()/RAND_MAX);

		free(rot1);
		free(rot2);
	}
	/* just to shut gcc up! */
	return p;
}

static Box* insert_Box(Box* base, Box* n)
{
	if (base == NULL) {
		base = n;
	} else if (n->pos->z < base->pos->z) {
		if (base->lower == NULL) {
			base->lower = n;
			n->upper = base;
			n->dim->z = base->pos->z - n->pos->z;
		} else
			insert_Box(base->lower, n);
	} else if (n->pos->z > base->pos->z) {
		if (base->upper == NULL) {
			base->upper = n;
			n->lower = base;
			base->dim->z = n->pos->z - base->pos->z;
		} else
			insert_Box(base->upper, n);
	}
	return n;
}

void plot_boxes(Box* n)
{
	/* find "uppest" element */
	while (n->upper != NULL)
		n = n->upper;

	printf("|--------------TOA----------------\n");
	while (n != NULL) {
		printf("| beta_scat_m = %e 1/km\n", (n->molecular == NULL)? 0 : n->molecular->beta_scat);
		printf("| beta_scat_c = %e 1/km\n", (n->cloud == NULL)? 0 : n->cloud->beta_scat);
		printf("| beta_abs = %e 1/km\n", n->beta_abs);
		printf("| height = %.2f km\n", n->dim->z);
		printf("|----------------------------- %.0f km\n", n->pos->z);
		n = n->lower;
	}
}


Box* read_atmosphere(const char* fn)
{
	FILE* fd = NULL;
	char buf[100];
	Box* ret = NULL;

	fd = fopen(fn, "r");
	if (fd == NULL) {
		fprintf(stderr, "inputfile could not be opened: %s\n", fn);
		return NULL;
	}

	/* create double linked box list from atmosphere file */
	while (fgets(buf, sizeof(buf), fd) != 0) {
		float z, beta_scat, beta_abs;
		Box* tmp_box = NULL;
		sscanf(buf, "%e %e %e", &z, &beta_scat, &beta_abs);
		tmp_box = new_Box(new_Vec3D(0,0,z), new_Vec3D(0,0,0), beta_abs, new_HenyeyGreensteinScatterer(beta_scat), NULL);
		ret = insert_Box(ret, tmp_box);
	}

	fclose(fd);

	return ret;
}

Scatterer* new_HenyeyGreensteinScatterer(double beta)
{
	Scatterer* ret = (Scatterer*)malloc(sizeof(Scatterer));
	ret->beta_scat = beta;
	ret->pdf = henyeyGreensteinPDF;
	return ret;
}

Box* new_Box(Vec3D* pos, Vec3D* dim, double b_abs, Scatterer* m, Scatterer* c)
{
	Box* ret = (Box*)malloc(sizeof(Box));
	ret->pos = pos;
	ret->dim = dim;
	ret->beta_abs = b_abs;
	ret->molecular = m;
	ret->cloud = c;
	ret->lower = NULL;
	ret->upper = NULL;

	return ret;
}

double rayleighPDF(double r)
{
	double u=0, d=0, q=0;
	NORM_R(r);
	q = -8*r + 4;
	d = 1 + (pow(q, 2) / 4.);
	u = pow(-(q/2.) + sqrt(d), 1./3.);
	return (u - (1/u));
}

double henyeyGreensteinPDF(double r)
{
	/* hardcode assymetry parameter to 0.85...good enough */
	double g = 0.85;
	double u=0, v=0, w=0;
	NORM_R(r);
	w = g * (2*r - 1) + 1;
	v = (1.-pow(g, 2))/w;
	u = -pow(v, 2) + pow(g, 2) + 1;
	return u/(2*g);
}

double tauPDF(double r)
{
	NORM_R(r);
	return -log(1.-r);
}

double azimuthPDF(double r)
{
	NORM_R(r);
	return 2*M_PI*r;
}

double unityPDF(double r)
{
	return r;
}

