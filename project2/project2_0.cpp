#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>


int ARRAYSIZE=32000;
double array[32000];


float Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

int main()
{
int i,j,prod;

double time0=omp_get_wtime();
#pragma omp parallel for schedule(dynamic, chunksize) num_threads(NUMT)
for (i=0;i<32000-1;i++)
{
array[i]=Ranf(-1.f,1.f);
for(j=0;j<i;j++)
{
array[j];
prod*=array[j];
}
}
double time1=omp_get_wtime();

long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;  // count of how many multiplications were done:

fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, chunksize, (double)numMuled/(time1-time0)/1000000. );
}

