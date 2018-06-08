/*--------------------------------------------------------------------*/
/* rect.c                                                             */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

static int iLength;  /* Bad style. */
static int iWidth;   /* Bad style. */
static int iPerim;   /* Bad style. */

/*--------------------------------------------------------------------*/

/* Read a rectangle's length and width from stdin, and write its
   perimeter to stdout.  Return 0. */

int main(void)
{
   printf("Rectangle length:  ");
   scanf("%d", &iLength);   /* Should validate. */
   
   printf("Rectangle width:  ");
   scanf("%d", &iWidth);    /* Should validate. */
   
   iPerim = 2 * (iLength + iWidth);
   
   printf("The rectangle's perimeter is %d.\n", iPerim);
   
   return 0;
}
