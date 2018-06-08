/*--------------------------------------------------------------------*/
/* teststack.c (Version 3)                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "stack.h"
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

/* Test the Stack ADT.  Return 0, or EXIT_FAILURE if not enough memory
   is available. */

int main(void)
{
   Stack_T oStack1;
   Stack_T oStack2;
   int iSuccessful;

   /* Use a Stack object referenced by oStack1. */
   
   oStack1 = Stack_new();
   if (oStack1 == NULL) handleMemoryError();
   
   iSuccessful = Stack_push(oStack1, 1.1);
   if (! iSuccessful) handleMemoryError();
   
   iSuccessful = Stack_push(oStack1, 2.2);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack1, 3.3);
   if (! iSuccessful) handleMemoryError();

   while (! Stack_isEmpty(oStack1))
      printf("%g\n", Stack_pop(oStack1));

   Stack_free(oStack1);
   
   /* Use a Stack object referenced by oStack2. */
      
   oStack2 = Stack_new();
   if (oStack2 == NULL) handleMemoryError();
   
   iSuccessful = Stack_push(oStack2, 4.4);
   if (! iSuccessful) handleMemoryError();
   
   iSuccessful = Stack_push(oStack2, 5.5);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack2, 6.6);
   if (! iSuccessful) handleMemoryError();
   
   while (! Stack_isEmpty(oStack2))
      printf("%g\n", Stack_pop(oStack2));

   Stack_free(oStack2);

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
