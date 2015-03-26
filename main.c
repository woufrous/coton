#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linalg.h"
#include "photon.h"

static void init_random()
{
	time_t now;

	time(&now);
	srand(now);
}

int main(int argc, char *argv[])
{
	(void)argc;(void)argv;
	printf("Coton v0.1 pre alpha\n");

	init_random();

	return 0;
}

