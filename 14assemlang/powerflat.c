/*--------------------------------------------------------------------*/
/* powerflat.c                                                        */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

static long lBase;       /* Bad style. */
static long lExp;        /* Bad style. */
static long lPower = 1;  /* Bad style. */
static long lIndex;      /* Bad style. */

/*--------------------------------------------------------------------*/

/* Read a non-negative base and exponent from stdin.  Write base
   raised to the exponent power to stdout.  Return 0. */

int main(void)
{
   printf("Enter the base:  ");
   scanf("%ld", &lBase);

   printf("Enter the exponent:  ");
   scanf("%ld", &lExp);

   lIndex = 1;
loop1:
   if (lIndex > lExp) goto loopend1;
   lPower *= lBase;
   lIndex++;
   goto loop1;
loopend1:

   printf("%ld to the %ld power is %ld.\n", lBase, lExp, lPower);

   return 0;
}
