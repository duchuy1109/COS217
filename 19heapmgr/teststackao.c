/*--------------------------------------------------------------------*/
/* teststackao.c                                                      */
/* Author: Bob Dondero                                                */
/* A Stack abstract object client                                     */
/*--------------------------------------------------------------------*/

#include "stackao.h"
#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/

/* Write an error message to stderr indicating that not enough memory
   is available.  Then exit with status EXIT_FAILURE. */

static void handleMemoryError(void)
{
   fprintf(stderr, "Insufficient memory\n");
   exit(EXIT_FAILURE);
}

/*--------------------------------------------------------------------*/

/* Test the Stack abstract object.  Return 0, or EXIT_FAILURE if not
   enough memory is available. */

int main(void)
{
   int iSuccessful;
      
   iSuccessful = Stack_init();
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(1.1);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(2.2);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(3.3);
   if (! iSuccessful) handleMemoryError();

   while (! Stack_isEmpty())
      printf("%g\n", Stack_pop());
   
   Stack_free();

   iSuccessful = Stack_init();
   if (! iSuccessful) handleMemoryError();
   
   iSuccessful = Stack_push(4.4);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(5.5);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(6.6);
   if (! iSuccessful) handleMemoryError();

   while (! Stack_isEmpty())
      printf("%g\n", Stack_pop());
   
   Stack_free();

   return 0;
}

/*--------------------------------------------------------------------*/

/*
   Output:
   3.3
   2.2
   1.1
   6.6
   5.5
   4.4
*/
