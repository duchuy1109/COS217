/*--------------------------------------------------------------------*/
/* powerunsigned.c                                                    */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

static unsigned long ulBase;       /* Bad style. */
static unsigned long ulExp;        /* Bad style. */
static unsigned long ulPower = 1;  /* Bad style. */
static unsigned long ulIndex;      /* Bad style. */

/*--------------------------------------------------------------------*/

/* Read a non-negative base and exponent from stdin.  Write base
   raised to the exponent power to stdout.  Return 0. */

int main(void)
{
   printf("Enter the base:  ");
   scanf("%lu", &ulBase);   /* Should validate. */

   printf("Enter the exponent:  ");
   scanf("%lu", &ulExp);    /* Should validate. */

   for (ulIndex = 1; ulIndex <= ulExp; ulIndex++)
      ulPower *= ulBase;

   printf("%lu to the %lu power is %lu.\n", ulBase, ulExp, ulPower);

   return 0;
}
