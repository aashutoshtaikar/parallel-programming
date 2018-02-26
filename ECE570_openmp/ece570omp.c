#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /* for uint64 definition */
#include <time.h> /* for clock_gettime */
#include <omp.h>
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
	for (i=0; i < N; i++){
		a[i] = b[i] = i * 1.0;
	}
	omp_set_num_threads(4);
clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
	#pragma omp parallel for schedule(static, CHUNKSIZE) num_threads(4)
	
	for (i=0; i<N; i++){
		c[i] = a[i] + b[i];
		printf("Thread number:%d,c[%d]= %f\n", omp_get_thread_num(),i,c[i]);
		printf("Number of threads being used:%d\n",omp_get_num_threads());
	}

clock_gettime(CLOCK_MONOTONIC, &end); /* mark the end time */
	
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("\nElapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
}
//14686224 nanoseconds