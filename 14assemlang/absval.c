/*--------------------------------------------------------------------*/
/* absval.c                                                           */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/

static int iInput;   /* Bad style. */
static int iAbsVal;  /* Bad style. */

/*--------------------------------------------------------------------*/

/* Read an integer from stdin, and write its absolute value
   to stdout.  Return 0. */

int main(void)
{
   printf("Enter an integer:  ");
   scanf("%d", &iInput);  /* Should validate. */
   
   iAbsVal = abs(iInput);
   
   printf("The integer's absolute value is %d.\n", iAbsVal);
   
   return 0;
}
