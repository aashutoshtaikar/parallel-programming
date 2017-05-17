#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

int	NowYear;		// 2017 - 2022
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
float	TmpNowHeight;

int		NowNumDeer;		// number of deer in the current population
int 	TmpNumDeer;

int 	hunters;
int 	NumDeerHunted;

unsigned int seed;

const float GRAIN_GROWS_PER_MONTH =	8.0;
const float ONE_DEER_EATS_PER_MONTH = 0.5;
//const float ONE_HUNTER_KILLS_PER_MONTH = 30.0;

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
	NowNumDeer=TmpNumDeer-NumDeerHunted;
	if (NowNumDeer<0)
	{
		NowNumDeer=0;
	}
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
	TmpNowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
 	TmpNowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
 	if (TmpNowHeight<0)
 	{
 		TmpNowHeight=0;
 	}
 		// DoneComputing barrier:-------
	#pragma omp barrier
	//do somthing global
 	NowHeight = TmpNowHeight;
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
	printf("-------------------------------------------------------------\n");
	printf("Month:%d \n", NowMonth);
	printf("Year:%d \n", NowYear);
	printf("Total GrainDeers before hunting:%d\n",TmpNumDeer );
	printf("Number of GrainDeer:%d\n",NowNumDeer );
	printf("Number of Hunters:%d\n",hunters );
	printf("Number of deer hunted:%d\n",NumDeerHunted );
	printf("grain growth in cm:%f \n ",NowHeight * 2.54); 
	printf("temperature in degrees Celcius (°C) :%f \n", (5./9.)*(NowTemp-32));
	printf("precipitation in cm:%f \n", NowPrecip * 2.54);
	//increment month count
	NowMonth++;
	//increment now year
	if (NowMonth%12==0)
	{
		NowYear++;

	}
	//compute new temperature and precipitation
	float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
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


int hunterguard()
{

	NumDeerHunted=0;
	int TmpDeerTobeKilled=TmpNumDeer; // temporary variable to store the temporary number of deer from the graindeer used for 
	// compute a temporary next-value for this quantity
	// based on the current state of the simulation:
	if (NowMonth%5==0 || NowMonth%6==0 || NowMonth%7==0 || NowMonth%8==0 && TmpNumDeer<=4) // less hunters in summer for less deers: May, June, July, August
	{

		hunters=rand() % 8;	

			for (int i=0;i<=TmpDeerTobeKilled && i<=hunters;i++)
			{
				int huntsuccess=rand() % 2; // probability of getting killed 0 or 1
				if (huntsuccess==1)
				{
					NumDeerHunted++;
					TmpDeerTobeKilled--;
				}
			}

	}

	else 
	{
		hunters=TmpNumDeer;	

			for (int i=0;i<=TmpDeerTobeKilled && i<=hunters;i++)
			{
				int huntsuccess=rand() % 2; // probability of getting killed 0 or 1
				if (huntsuccess==1)
				{
					NumDeerHunted++;
					TmpDeerTobeKilled--;
				}
			}
	}

	
	

	// DoneComputing barrier:
	#pragma omp barrier
	NumDeerHunted=NumDeerHunted;

	// DoneAssigning barrier:
	#pragma omp barrier
		

	// DonePrinting barrier:
	#pragma omp barrier
		
	
}


int main(int argc, char const *argv[])
{

	// starting date and time:
	NowMonth =    0;
	NowYear  = 2017;

	// starting state (feel free to change this if you want):
	NowNumDeer = 1;
	NowHeight =  1.;

	TmpNumDeer = 1;
	seed = 0;
	float ang = ( 30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	
	NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
	NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
	if( NowPrecip < 0. )
	{
		NowPrecip = 0.; 
	}

	omp_set_num_threads( 4 );	// same as # of sections
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

			#pragma omp section
			{
				hunterguard( );	// your own
			}
		}       // implied barrier -- all functions must return in order
		// to allow any of them to get past here
	
	}

	return 0;
}

