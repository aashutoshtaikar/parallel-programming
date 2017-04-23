#include <omp.h>
#include <stdio.h>
#include <math.h>


#define ARRAYSIZE       1000000	
#define NUMTRIES        10	

float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];


int main()
{
#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
#endif
/*	int numthreads=omp_get_num_threads();
	printf("number of threads supported by the system is %d", numthreads); */
  printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
int NUMT=1;
omp_set_num_threads( NUMT );
fprintf( stderr, "Using %d thread(s)....\n", NUMT );

double maxMegaMults = 0.;
double sumMegaMults = 0.;
double ex1, ex4; 

for( int t = 0; t < NUMTRIES; t++ )
{
	double time0 = omp_get_wtime( );

   	#pragma omp parallel for
   	for( int i = 0; i < ARRAYSIZE; i++ )
   	{
     		C[i] = A[i] * B[i];
    	}
		
	double time1 = omp_get_wtime( );
	double megaMults = (double)ARRAYSIZE/(time1-time0)/1000000.; 
	sumMegaMults += megaMults;
        if( megaMults > maxMegaMults )
          maxMegaMults = megaMults;
    
	ex1=time1-time0;
}
	

        double avgMegaMults = (sumMegaMults/(double)NUMTRIES);
        
	printf( "Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults );
        printf( "Average Performance = %8.2lf MegaMults/Sec\n", avgMegaMults );
	printf( "Performance difference = %8.2lf MegaMults/Sec\n",maxMegaMults-avgMegaMults );
	printf("Execution time for 1 thread(s):%lf\n",ex1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        NUMT=4;
        omp_set_num_threads( NUMT );
	printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
        fprintf( stderr, "Using %d thread(s)....\n", NUMT );

        double maxMegaMults4 = 0.;
        double sumMegaMults4 = 0.;
                 

        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

                #pragma omp parallel for
                for( int i = 0; i < ARRAYSIZE; i++ )
                {
                        C[i] = A[i] * B[i];
                }

                double time1 = omp_get_wtime( );
                double megaMults4 = (double)ARRAYSIZE/(time1-time0)/1000000.;
                sumMegaMults4 += megaMults4;
                if( megaMults4 > maxMegaMults4 )
                        maxMegaMults4 = megaMults4;

                ex4=time1-time0;
    }
        

        double avgMegaMults4 = sumMegaMults4/(double)NUMTRIES;
        printf( "Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults4 );
        printf( "Average Performance = %8.2lf MegaMults/Sec\n", avgMegaMults4 );
        printf( "Performance difference = %8.2lf MegaMults/Sec\n",maxMegaMults4-avgMegaMults4 );
        printf("Execution time for 4 thread(s):%lf\n",ex4);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("///////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	printf("---------------Speedup-------------\n");
	double S=ex1/ex4;
	printf("Speedup by execution time(S):%8.2lf\n",S);
	printf("Speedup by performance(S):%8.2lf\n",maxMegaMults4/maxMegaMults);
	printf("---------------Parallel fraction-------------\n");
	
	double fp=((4./3.)*( 1. - (1./S)));
	printf("Parallel Fraction(fp):%lf\n",fp);

	// note: %lf stands for "long float", which is what printf calls a "double"
	//        %d stands for "decimal integer", not "double"

        return 0;
}
