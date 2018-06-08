/*--------------------------------------------------------------------*/
/* fnpointers.c                                                       */
/* Author: Bob Dondero                                                */
/* A nonsensical program to illustrate function pointers              */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Return i squared. */

static int sqr(int i)
{
   return i * i;
}

/*--------------------------------------------------------------------*/

/* Demonstrate function pointers.  Return 0. */

int main(void)
{
   int i;

   int (*pf)(int);  /* pf is a function pointer.
                       pf is a variable which, when dereferenced,
                       yields a function that takes an int and
                       returns an int. */

   /* An ordinary function call: */

   i = sqr(5);
   printf("%d\n", i);

   /* A function call through a function pointer: */

   pf = sqr;
   i = (*pf)(5);
   printf("%d\n", i);

   /* Unusual ways of using function pointers: */

   pf = &sqr;
   i = (*pf)(5);
   printf("%d\n", i);

   pf = *sqr;
   i = (*pf)(5);
   printf("%d\n", i);

   pf = sqr;
   i = pf(5);
   printf("%d\n", i);

   pf = &sqr;
   i = pf(5);
   printf("%d\n", i);

   pf = *sqr;
   i = pf(5);
   printf("%d\n", i);

   return 0;
}
