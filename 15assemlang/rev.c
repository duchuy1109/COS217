/*--------------------------------------------------------------------*/
/* rev.c                                                              */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* The number of elements in the array. */
enum {ARRAY_LENGTH = 5};

long alNums[ARRAY_LENGTH];  /* Bad style */
long lIndex;                /* Bad style */
   
/*--------------------------------------------------------------------*/

/* Read ARRAY_LENGTH integers from stdin, and write them in reverse
   order to stdout.  Return 0. */

int main(void)
{
   printf("Enter %d integers:\n", ARRAY_LENGTH);
   for (lIndex = 0; lIndex < ARRAY_LENGTH; lIndex++)
      scanf("%ld", &alNums[lIndex]);

   printf("\n");

   printf("The integers in reverse order are:\n");
   for (lIndex = ARRAY_LENGTH-1; lIndex >= 0; lIndex--)
      printf("%ld\n", alNums[lIndex]);

   return 0;
}
