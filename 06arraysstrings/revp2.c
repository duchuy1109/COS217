/*--------------------------------------------------------------------*/
/* revp2.c                                                            */
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
   int *piCurrent;
   int *piAfterLast;

   piAfterLast = aiNums + ARRAY_LENGTH;

   printf("Enter %d integers:\n", ARRAY_LENGTH);
   piCurrent = aiNums;
   while (piCurrent != piAfterLast)  /* Could use "for" statement. */
   {
      scanf("%d", piCurrent);
      piCurrent++;
   }

   printf("\n");

   printf("The integers in reverse order are:\n");
   while (piCurrent != aiNums)
   {
      piCurrent--;
      printf("%d\n", *piCurrent);
   }

   return 0;
}
