/*--------------------------------------------------------------------*/
/* circle2.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Read a circle's radius from stdin, and compute and write its
   diameter and circumference to stdout.  Return 0. */

int main(void)
{
   int iRadius;
   int iDiam;
   double dCircum;
   const double PI = 3.14159;  /* or (4.0 * atan(1.0)) */

   printf("Enter the circle's radius:\n");
   scanf("%d", &iRadius);

   iDiam = 2 * iRadius;
   dCircum = PI * (double)iDiam;

   printf("A circle with radius %d has diameter %d\n",
          iRadius, iDiam);
   printf("and circumference %f.\n", dCircum);
   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 circle2.c -o circle2

$ ./circle2
Enter the circle's radius:
5
A circle with radius 5 has diameter 10
and circumference 31.415900.

$ ./circle2
Enter the circle's radius:
1
A circle with radius 1 has diameter 2
and circumference 6.283180.

*/
