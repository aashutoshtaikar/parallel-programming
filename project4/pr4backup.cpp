#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

int	NowYear;		// 2017 - 2022
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population

float PrevHeight;

int TmpNumDeer;

const float GRAIN_GROWS_PER_MONTH =	8.0;
const float ONE_DEER_EATS_PER_MONTH = 0.5;

const float AVG_PRECIP_PER_MONTH = 6.0;	// average
const float AMP_PRECIP_PER_MONTH = 6.0;	// plus or minus
const float RANDOM_PRECIP =	2.0;	// plus or minus noise

const float AVG_TEMP = 50.0;	// average
const float AMP_TEMP = 20.0;	// plus or minus
const float RANDOM_TEMP = 10.0;	// plus or minus noise

const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0; 


float
SQR( float x )
{
        return x*x;
}

float Ranf( unsigned int *seedp,  float low, float high )
{
	float r = (float) rand_r( seedp );              // 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

int GrainDeer()
{

		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		if (NowNumDeer<NowHeight)
		{
			TmpNumDeer++;
		}
		else if (NowNumDeer>NowHeight)
		{
			TmpNumDeer--;
		}
		else if (NowNumDeer=NowHeight)
		{
			TmpNumDeer++;
		}
		// DoneComputing barrier:
		#pragma omp barrier
		//do somthing global
		NowNumDeer=TmpNumDeer*1;
		// DoneAssigning barrier:
		#pragma omp barrier
		//do nothing
		#pragma omp barrier
}

int Grain()
{
	
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
		float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );
		NowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
 		NowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
 		if (NowHeight<0)
 		{
 			NowHeight=0;
 		}
		// DoneComputing barrier:-------
		#pragma omp barrier
		//do somthing global
 		NowHeight = NowHeight;
 		//PrevHeight = NowHeight - 1;
		// DoneAssigning barrier:-------
		#pragma omp barrier
  		//do nothing---------
		#pragma omp barrier
	
}

int Watcher()
{
	
		// do nothing 
		#pragma omp barrier
		//do nothing 
		#pragma omp barrier
		//print current set of global variables

		//increment month count
		NowMonth++;
		if (NowMonth%12==0)
		{
			NowYear++;
		printf("Number of GrainDeer:%d\n",NowNumDeer );
		printf("grain growth :%f inches\n ",NowHeight ); 
		printf("temperature :%f degrees Fahrenheit (°F)\n", NowTemp );
		printf("precipitation:%f inches\n", NowPrecip);
		}
		//compute new temperature and precipitation
		float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
		float temp = AVG_TEMP - AMP_TEMP * cos( ang );
		unsigned int seed = 0;
		NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );
		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
		NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
		if( NowPrecip < 0. )
		{
			NowPrecip = 0.;
		}
		// DonePrinting barrier:
		#pragma omp barrier
	
}

/*
int MyAgent()
{
	
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		

		// DoneComputing barrier:
		#pragma omp barrier
		

		// DoneAssigning barrier:
		#pragma omp barrier
		

		// DonePrinting barrier:
		#pragma omp barrier
			
	
}
*/

int main(int argc, char const *argv[])
{

	// starting date and time:
	NowMonth =    0;
	NowYear  = 2017;

	// starting state (feel free to change this if you want):
	NowNumDeer = 1;
	NowHeight =  1.;
	PrevHeight = 1.;
	TmpNumDeer = 1;

	float ang = ( 30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	unsigned int seed = 0;
	NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
	NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
	if( NowPrecip < 0. )
	{
		NowPrecip = 0.; 
	}

	omp_set_num_threads( 3 );	// same as # of sections
	while( NowYear < 2023 )
	{	
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer( );
		}

		#pragma omp section
		{
			Grain( );
		}

		#pragma omp section
		{
			Watcher( );
		}

		/*#pragma omp section
		{
			MyAgent( );	// your own
		}*/
	}       // implied barrier -- all functions must return in order
	// to allow any of them to get past here
	
	}
	return 0;
}

