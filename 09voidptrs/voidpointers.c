/*--------------------------------------------------------------------*/
/* voidpointers.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Demonstrate void pointers.  Return 0. */

int main(void)
{
   int i = 5;
   double d = 5.5;
   int *pi;
   double *pd;
   void *pv;

   pi = &i;                       /* OK */
   printf("%d\n", *pi);           /* OK */

   pd = &d;                       /* OK */
   printf("%f\n", *pd);           /* OK */

   pi = &d;                       /* Compiletime warning */
   pd = &i;                       /* Compiletime warning */

   pv = &i;                       /* OK */
   printf("%d\n", *pv);           /* Compiletime error */
   printf("%d\n", *(int*)pv);     /* OK */

   pv = &d;                       /* OK */
   printf("%f\n", *pv);           /* Compiletime error */
   printf("%f\n", *(double*)pv);  /* OK */

   pv = &i;                       /* OK */
   d = *(double*)pv;              /* Runtime error */

   return 0;
}

/*--------------------------------------------------------------------*/

/*

$ gcc217 voidpointers.c
voidpointers.c: In function 'main':
voidpointers.c:26: warning: assignment from incompatible pointer type
voidpointers.c:27: warning: assignment from incompatible pointer type
voidpointers.c:30: warning: dereferencing 'void *' pointer
voidpointers.c:30: error: invalid use of void expression
voidpointers.c:34: warning: dereferencing 'void *' pointer
voidpointers.c:34: error: invalid use of void expression

*/
