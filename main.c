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

dispatch_item dispatcher[] = {
	{ "t1", main_t1 },
	{ "t2", main_t2 },
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
	(void)argc; (void)argv;

	Vec3D *v = new_Vec3D_spherical(55.0, 30.*3.14/180., 0);

	double t = vmulv(normalize(v), &e1);

	printf("Angle: %.2f\n", t);

	return 0;
}
