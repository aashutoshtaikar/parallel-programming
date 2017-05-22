#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define THREADS 4
#define N 17

int main ( ) {
  int i;
double time0=omp_get_wtime();
  #pragma omp parallel for schedule(static,10) num_threads(THREADS)
  for (i = 0; i < N; i++) {
    /* wait for i seconds */
    sleep(i);

    printf("Thread %d has completed iteration %d.\n", omp_get_thread_num( ), i);
  }
double time1=omp_get_wtime();
double time=time1-time0;

  /* all threads done */
  printf("All done!\n");
  printf("execution time:%lf\n",time);
  return 0;
}
