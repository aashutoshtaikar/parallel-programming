#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Generates a random number on the interval [LO, HI)
#define RAND_RANGE(LO,HI) (LO + rand() / (RAND_MAX / (LO + HI) + 1))
#define LEN(ARR) (sizeof ARR / sizeof *ARR)

// r = stone , p = paper , s = scissor

// r = 0
// p = 1
// s = 2
// 0 > 2
// 1 > 0
// 2 > 1


 
int ranfunct()
{
   char array[] = { 0, 1, 2};
   srand(time(NULL));
   size_t index = RAND_RANGE(0, LEN(ARRAY));
   printf("%c\n", array[index]);
   deer=array[index];
   srand(time(NULL));
   size_t index = RAND_RANGE(0, LEN(ARRAY));
   printf("%c\n", array[index]);
   ant=array[index];
}

int game (int a1, int a2)
{
	if (a1 == a2)
		result = 0;

	else if (a1 == 0 && a2 == 2) // a1 deer wins
		result = 1;

	else if (a1 == 1 && a2 == 0) // a1 deer wins
		result = 2;

	else if (a1 == 2 && a2 == 1) // a1 deer wins
		result = 3;

	else if (a2 == 0 && a1 == 2) // a2 ant wins
		result = 4;

	else if (a2 == 1 && a1 == 0) // a2 ant wins
		result = 5;

	else if (a1 == 2 && a1 == 1) // a2 ant wins
		result = 6;
}