/*--------------------------------------------------------------------*/
/* powerstack.c                                                       */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Read a non-negative base and exponent from stdin.  Write base
   raised to the exponent power to stdout.  Return 0. */

int main(void)
{
   long lBase;
   long lExp;
   long lPower = 1;
   long lIndex;

   printf("Enter the base:  ");
   scanf("%ld", &lBase);   /* Should validate. */

   printf("Enter the exponent:  ");
   scanf("%ld", &lExp);    /* Should validate. */

   for (lIndex = 1; lIndex <= lExp; lIndex++)
      lPower *= lBase;

   printf("%ld to the %ld power is %ld.\n", lBase, lExp, lPower);

   return 0;
}
