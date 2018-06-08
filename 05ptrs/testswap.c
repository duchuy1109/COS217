/*--------------------------------------------------------------------*/
/* testswap.c                                                         */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* Swap the values of *piFirst and *piSecond. */

static void swap(int *piFirst, int *piSecond)
{
   int iTemp;

   assert(piFirst != NULL);
   assert(piSecond != NULL);

   iTemp = *piFirst;
   *piFirst = *piSecond;
   *piSecond = iTemp;
}

/*--------------------------------------------------------------------*/

/* Test the swap function.  Return 0. */

int main(void)
{
   int i1 = 8;
   int i2 = 12;

   printf("Before:  %d %d\n", i1, i2);

   swap(&i1, &i2);

   printf("After:  %d %d\n", i1, i2);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample Execution:

$ ./testswap
Before:  8 12
After:  12 8

*/
