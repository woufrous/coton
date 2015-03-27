#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "linalg.h"
#include "photon.h"
#include "atmosphere.h"

static void init_random()
{
	time_t now;

	time(&now);
	srand(now);
}

typedef int (*mainfunc)(int,char**);

typedef struct {
	char* action_name;
	mainfunc main_func;
} dispatch_item;

int main_t1(int, char**);
int main_t2(int, char**);
int main_t3(int, char**);

dispatch_item dispatcher[] = {
	{ "t1", main_t1 },
	{ "t2", main_t2 },
	{ "t3", main_t3 },
};

int dispatch(int argc, char* argv[])
{
	int n_items = sizeof(dispatcher)/sizeof(dispatch_item);

	for (int i=0; i<n_items; ++i) {
		if (strncmp(argv[1], dispatcher[i].action_name, 2) != 0)
			continue;
		mainfunc tmp_main = dispatcher[i].main_func;
		return tmp_main(argc, argv);
	}
	fprintf(stderr, "Unknown action: %s\n", argv[1]);

	return -1;
}

int main(int argc, char* argv[])
{
	init_random();

	if (argc < 2) {
		fprintf(stderr, "Usage: %s ACTION [params]\n", argv[0]);
		return -1;
	}

	return dispatch(argc, argv);
}

int main_t1(int argc, char* argv[])
{
	(void)argc;(void)argv;

	for(int i=0; i<100000; ++i) {
		double r = (double)rand()/(double)RAND_MAX;
		// printf("%e\n", rayleighPDF(r));
		printf("%e\n", henyeyGreensteinPDF(r));
		// printf("%e\n", tauPDF(r));
		// printf("%e\n", azimuthPDF(r));
		// printf("%e\n", unityPDF(r));
	}

	return 0;
}

int main_t2(int argc, char* argv[])
{
	int top=0, bottom=0;
	int total, n_photons;
	double sza, tau;

	if (argc < 5) {
		fprintf(stderr, "Usage: %s t2 tau sca nPhotons\n", argv[0]);
		return -1;
	}
	tau = atof(argv[2]);
	sza = atof(argv[3]);
	n_photons = atoi(argv[4]);

	Vec3D* dir_0 = new_Vec3D_spherical(1.0, M_PI-degtorad(sza), 0);
	Vec3D* pos_0 = new_Vec3D(0, 0, 1);

	Box* b = new_Box(new_Vec3D(0,0,0), new_Vec3D(0,0,1), 0, new_HenyeyGreensteinScatterer(tau), NULL);

	for (int i=0; i<n_photons; ++i) {
		Photon* p = process_photon(b, new_Photon(pos_0, dir_0, tauPDF((double)rand()/RAND_MAX)));
		if (p->pos->z < b->pos->z)
			bottom++;
		else
			top++;
		free(p->pos);
		free(p->dir);
		free(p);
	}


	total = top+bottom;
	printf("Top: %d, Bottom: %d\nT = %.3f, R = %.3f\n", top, bottom, bottom/(double)total, top/(double)total);

	free(b->pos);
	free(b->dim);
	free(b->molecular);
	free(b);
	free(pos_0);
	free(dir_0);


	return 0;
}

int main_t3(int argc, char* argv[])
{
	int top=0, bottom=0, total=0;
	int n_photons=0;
	double sza=0;

	if (argc < 5) {
		fprintf(stderr, "Usage: %s t3 atmophereFile sca nPhotons\n", argv[0]);
		return -1;
	}

	Box* atm = read_atmosphere(argv[2]);
	if (atm == NULL)
		return -1;
	plot_boxes(atm);

	sza = atof(argv[3]);
	n_photons = atoi(argv[4]);

	Vec3D* dir_0 = new_Vec3D_spherical(1.0, M_PI-degtorad(sza), 0);
	Vec3D* pos_0 = new_Vec3D(0, 0, 120.);

	for (int i=0; i<n_photons; ++i) {
		int escaped = 0, count = 0;
		atm = get_toa(atm);
		Photon* p = new_Photon(pos_0, dir_0, tauPDF((double)rand()/RAND_MAX));
		while (!escaped && count < 1000) {
			p = process_photon(atm, p);
			if (p->pos->z <= atm->pos->z) {
				// puts("Photon exited below");
				if (atm->lower == NULL) {
					printf("out we go @ (%.2f %.2f %.2f) -> (%.2f %.2f %.2f)\n", p->pos->x, p->pos->y, p->pos->z,
							p->dir->x, p->dir->y, p->dir->z);
					bottom += p->weight;
					escaped = 1;
				} else
					atm = atm->lower;
			} else {
				// puts("Photon exited above");
				if (atm->upper == NULL) {
					top += p->weight;
					escaped = 1;
				} else
					atm = atm->upper;
			}
			++count;
		}
		if (count >= 1000)
			printf("something's fucky @ (%.2f %.2f %.2f) -> (%.2f %.2f %.2f)\n", p->pos->x, p->pos->y, p->pos->z,
					p->dir->x, p->dir->y, p->dir->z);
		free(p->pos);
		free(p->dir);
		free(p);
	}

	total = top+bottom;
	printf("Top: %d, Bottom: %d\nT = %.3f, R = %.3f\n", top, bottom, bottom/(double)n_photons, top/(double)n_photons);

	free_atmosphere(atm);

	free(pos_0);
	free(dir_0);

	return 0;
}
