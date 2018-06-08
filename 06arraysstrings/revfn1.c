/*--------------------------------------------------------------------*/
/* revfn1.c                                                           */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* The number of elements in the array. */
enum {ARRAY_LENGTH = 5};

/*--------------------------------------------------------------------*/

/* piNums is a pointer to the 0th element of an array.  Read
   integers from stdin into that array.  */

static void getNumbers(int *piNums)
{
   int i;

   assert(piNums != NULL);

   for (i = 0; i < ARRAY_LENGTH; i++)
      scanf("%d", &piNums[i]);
}

/*--------------------------------------------------------------------*/

/* piNums is a pointer to the 0th element of an array.  Print the
   elements of that array to stdout in reverse order.  */

static void putNumbers(int *piNums)
{
   int i;

   assert(piNums != NULL);

   for (i = ARRAY_LENGTH-1; i >= 0; i--)
      printf("%d\n", piNums[i]);
}

/*--------------------------------------------------------------------*/

/* Read ARRAY_LENGTH integers from stdin, and write them in reverse
   order to stdout.  Return 0. */

int main(void)
{
   int aiNums[ARRAY_LENGTH];

   printf("Enter %d integers:\n", ARRAY_LENGTH);
   getNumbers(aiNums);

   printf("\n");
   printf("The integers in reverse order are:\n");
   putNumbers(aiNums);

   return 0;
}
