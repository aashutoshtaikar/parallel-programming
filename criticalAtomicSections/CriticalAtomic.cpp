/* Atomic vs critical 
Comment out the respective section to see the difference between the performance, 
you won't see much difference as the computation is not intense

But you can clearly know the difference between atomic and critical by running this

*/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char *argv[ ] )
{
	int a=1;
	//omp_set_num_threads( NUMT );

	const int SomeBigNumber = 100000000;	// keep < 2B

	double time0= omp_get_wtime();
//-----------------------------------------ATOMIC section--------------------------------------------------------------	
	#pragma omp parallel num_threads(NUMT)
 	#pragma omp atomic
	a++; // it is
	
	printf("this is thread %d  executing out of %d threads\n",omp_get_thread_num(), omp_get_num_threads());

	for( unsigned int j = 0; j < SomeBigNumber; j++)
	{
			a = a + 2.; //some random computation	
	}
//---------------------------------------CRITICAL section--------------------------------------------------------------
#pragma omp parallel num_threads(NUMT) // <--- if you don't put this, the atomic construct will cause this to run on 1 thread ; try commenting it
	#pragma omp critical 

		printf("this is %d thread executing out of %d threads\n",omp_get_thread_num(), omp_get_num_threads());
		for( unsigned int j = 0; j < SomeBigNumber; j++)
		{	
			a = a + 2.;	
		}
		double time1= omp_get_wtime();

		double megaMultsFix1 = SomeBigNumber*4/(time1-time0)/1000000.;
		printf( "Performance:%8.2lf MegaMults/Sec\n", megaMultsFix1);


		return 0;
}
