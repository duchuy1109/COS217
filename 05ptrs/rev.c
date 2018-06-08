/*--------------------------------------------------------------------*/
/* rev.c                                                              */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* The number of elements in the array. */
enum {ARRAY_LENGTH = 5};

/*--------------------------------------------------------------------*/

/* Read ARRAY_LENGTH integers from stdin, and write them in reverse
   order to stdout.  Return 0. */

int main(void)
{
   int aiNums[ARRAY_LENGTH];
   int i;

   printf("Enter %d integers:\n", ARRAY_LENGTH);
   for (i = 0; i < ARRAY_LENGTH; i++)
      scanf("%d", &aiNums[i]);

   printf("\n");

   printf("The integers in reverse order are:\n");
   for (i = ARRAY_LENGTH-1; i >= 0; i--)
      printf("%d\n", aiNums[i]);

   return 0;
}
