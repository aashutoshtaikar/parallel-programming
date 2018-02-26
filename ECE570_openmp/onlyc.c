#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /* for uint64 definition */
#include <time.h> /* for clock_gettime */
#define CHUNKSIZE 10
#define N 100
#define BILLION 1000000000L

int main (int argc, char *argv[])
{
	int i;
	float a[N], b[N], c[N];
	uint64_t diff; /* Elapsed time */
	struct timespec start, end;
/* Some initializations */
	for (i=0; i < N; i++)
		a[i] = b[i] = i * 1.0;
clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
	for (i=0; i<N; i++){
		c[i] = a[i] + b[i];
		printf("c[%d]= %f\n",i,c[i]);
	}
clock_gettime(CLOCK_MONOTONIC, &end); /* mark the end time */
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("\nElapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
}