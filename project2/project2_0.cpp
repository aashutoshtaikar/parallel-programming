#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int NUMT=4;
double array[32000];

float Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

int main()
{

/*
#ifndef _OPENMP
 fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (double)numMuled/(time1-time0)/1000000. );
        return 1;
#endif
*/

int i,j,prod;

#pragma omp parallel for schedule(static) num_threads(NUMT)
for (i=0;i<32000-1;i++)
{
array[i]=Ranf(-1.f,1.f);
for(j=0;j<i;j++)
{
array[j];
prod*=array[j];
}
}


}

