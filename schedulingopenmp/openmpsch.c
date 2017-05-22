#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define N 17 

int main ( ) {
printf("1");
int i;

double time0=omp_get_wtime();
printf("3");
omp_set_num_threads(NUMT);
 #pragma omp parallel for schedule(TYPE, CHUNKSIZE)  
 for (i = 0; i < N; i++) {
    /* wait for i seconds */
	printf("-");
    sleep(i);
//    printf("---%d--",omp_get_thread_num());
//	printf("Thread %d has completed iteration %d.\n", omp_get_thread_num( ), i);
// printf("ash");
}

double time1=omp_get_wtime();
double time=time1-time0;
  /* all threads done */
  printf("All done!\n");
  printf("execution time:%lf\n",time);			

long int numMuled = (long int)17 * (long int)(17+1) / 2;  // count of how many multiplications were done:

	fprintf( stderr, "Threads = %2d; ChunkSize = ; MegaMults/sec = %10.2lf\n; EXT:%lf", NUMT,(double)numMuled/(time1-time0)/1000000., time );
  return 0;
}
