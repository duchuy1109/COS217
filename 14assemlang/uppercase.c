/*--------------------------------------------------------------------*/
/* uppercase.c                                                        */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

enum {LOWER_TO_UPPER = -32};

/*--------------------------------------------------------------------*/

static char cChar;   /* Bad style. */

/*--------------------------------------------------------------------*/

/* Read a letter from stdin, and write its uppercase equivalent
   to stdout.  Return 0. */

int main(void)
{
   cChar = (char)getchar();       /* Should check for error. */
   
   cChar += LOWER_TO_UPPER;       /* Should call toupper(). */
   
   putchar((int)cChar); 
   putchar('\n');
   
   return 0;
}
