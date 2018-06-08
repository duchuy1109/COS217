/*--------------------------------------------------------------------*/
/* testswapbad.c                                                      */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Swap the values of iFirst and iSecond. */

static void swap(int iFirst, int iSecond)
{
   int iTemp;

   iTemp = iFirst;
   iFirst = iSecond;
   iSecond = iTemp;
}

/*--------------------------------------------------------------------*/

/* Test the swap function. Return 0. */

int main(void)
{
   int i1 = 8;
   int i2 = 12;

   printf("Before:  %d %d\n", i1, i2);

   swap(i1, i2);

   printf("After:  %d %d\n", i1, i2);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample Execution:

$ ./testswapbad
Before:  8 12
After:  8 12

*/
