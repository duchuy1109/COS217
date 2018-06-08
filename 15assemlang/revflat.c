/*--------------------------------------------------------------------*/
/* revflat.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* The number of elements in the array. */
enum {ARRAY_LENGTH = 5};

long alNums[ARRAY_LENGTH];  /* Bad style */
long lIndex;                /* Bad style */
   
/*--------------------------------------------------------------------*/

/* Read ARRAY_LENGTH integers from stdin, and write them in reverse
   order to stdout.  Return 0. */

int main(void)
{
   printf("Enter %d integers:\n", ARRAY_LENGTH);
   
   lIndex = 0;
loop1:
   if (lIndex >= ARRAY_LENGTH) goto loopend1;
   scanf("%ld", &alNums[lIndex]);
   lIndex++;
   goto loop1;
loopend1:
   
   printf("\n");
   printf("The integers in reverse order are:\n");
   
   lIndex = ARRAY_LENGTH-1;
loop2:
   if (lIndex < 0) goto loopend2;
   printf("%ld\n", alNums[lIndex]);
   lIndex--;
   goto loop2;
loopend2:
   
   return 0;
}
