/*--------------------------------------------------------------------*/
/* testquorembad.c                                                    */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* Divide iDividend by iDivisor.  Assign the remainder to iRemainder,
   and return the quotient. */

static int quorem(int iDividend, int iDivisor, int iRemainder)
{
   assert(iDivisor != 0);
   iRemainder = iDividend % iDivisor;
   return iDividend / iDivisor;
}

/*--------------------------------------------------------------------*/

/* Test the quorem function.  Return 0. */

int main(void)
{
   int iQuo;
   int iRem;

   iQuo = quorem(11, 3, iRem);
   printf("Quotient: %d  Remainder: %d\n", iQuo, iRem);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample Execution:

$ ./testquorembad
Quotient: 3  Remainder: 8299968

*/
