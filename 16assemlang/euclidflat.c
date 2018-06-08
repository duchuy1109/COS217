/*--------------------------------------------------------------------*/
/* euclidflat.c                                                       */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/

/* Return the greatest common divisor of lFirst and lSecond. */

static long gcd(long lFirst, long lSecond)
{
   long lTemp;
   long lAbsFirst;
   long lAbsSecond;
   
   lAbsFirst = labs(lFirst);
   lAbsSecond = labs(lSecond);
   
loop1:
   if (lAbsSecond == 0) goto loopend1;
   lTemp = lAbsFirst % lAbsSecond;
   lAbsFirst = lAbsSecond;
   lAbsSecond = lTemp;
   goto loop1;
loopend1:

   return lAbsFirst;
}

/*--------------------------------------------------------------------*/

/* Read two integers from stdin. Compute their greatest common divisor,
   and write it to stdout. Return 0. */

int main(void)
{
   long l1;
   long l2;
   long lGcd;

   printf("Enter an integer: ");
   scanf("%ld", &l1);  /* Should validate. */
  
   printf("Enter an integer: ");
   scanf("%ld", &l2);  /* Should validate. */
   
   lGcd = gcd(l1, l2);
   
   printf("The gcd is %ld\n", lGcd);

   return 0;
}
