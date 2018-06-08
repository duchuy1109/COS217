/*--------------------------------------------------------------------*/
/* ptrs.c                                                             */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Illustrate pointers. Return 0. */

int main(void)
{
   /*-----------------------------------------------------------------*/
   /* Pointer Fundamentals                                            */
   /*-----------------------------------------------------------------*/

   int i1;      /* i1 is a variable of type int. */

   int i2;      /* i2 is a variable of type int. */

   int *pi3;    /* pi3 is a variable of type int*. */
                /* pi3 is an integer pointer. */

   int* pi4;    /* pi4 is a variable of type int*. */
                /* Spacing before and after "*" doesn't matter. */

   i1 = 5;

   /* pi4 = 6;     Compiletime warning: type mismatch. */
   /* pi3 = i1;    Compiletime warning: type mismatch. */
   /* i1 = pi3;    Compiletime warning: type mismatch. */

   pi3 = &i1;   /* "&" is the "address of" operator. */

   /* pi3 = 6;     Still compiletime warning. */

   *pi3 = 6;    /* "*" is the "dereference" operator. */
                /* Changes value of *pi3 and i1. */
                /* *pi3 and i1 are aliases. */
                /* Here: undesirable.  Elsewhere: useful. */

   /* *pi4 = 7;    Runtime error. Seg fault, or memory corruption. */

   pi4 = &i2;   /* Hereafter, *pi4 and i2 are aliases. */

   i2 = *pi3;   /* Assigns an int to an int variable. */

   *pi4 = *pi3; /* Same as previous. */

   pi4 = pi3;   /* Assigns an address to a pointer. */
                /* *pi3 and *pi4 are now aliases. */

   pi4 = &i2;   /* Restore pi4 to previous value */

   /* & and * are inverse operators:
         If you write &*pi3, then you might as well write pi3 instead.
         If you write *&i1, then you might as well write i1 instead. */

   /*-----------------------------------------------------------------*/
   /* The NULL address                                                */
   /*-----------------------------------------------------------------*/

   pi3 = NULL;  /* Indicates that pi3 points to no valid memory
                   location. */

   /* NULL is a #defined constant in several standard header files. */
   /* #define NULL (void*)0 */

   /* NULL differs from "unpredictable value." */
   /* *pi3 = 8;    Runtime error: Seg fault. */

   pi3 = &i1;   /* Restore value of pi3 */

   /*-----------------------------------------------------------------*/
   /* Pointers and Relational Operators                               */
   /*-----------------------------------------------------------------*/

   if (*pi3 == *pi4)  /* Compares ints. Evaluates to TRUE (1). */
      printf("Integers are equal\n");

   if (pi3 == pi4)    /* Compares addresses. Evaluates to FALSE (0). */
      printf("Pointers are equal\n");

   if (pi3 != pi4)    /* Compares addresses. Evaluates to TRUE (1). */
      printf("Pointers are unequal\n");

   /* Note:
      if (pi3 == pi4) is TRUE,
         then (*pi3 == *pi4) is TRUE.
      if (*pi3 == *pi4) is TRUE,
         then (pi3 == pi4) may or may not be TRUE.  */

   if (pi3 == NULL)   /* Compares addresses. Evaluates to FALSE (0). */
      printf("Pointer is NULL\n");

   return 0;
}
