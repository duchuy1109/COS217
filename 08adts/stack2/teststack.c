/*--------------------------------------------------------------------*/
/* teststack.c (Version 2)                                            */
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
   struct Stack *psStack1;
   struct Stack *psStack2;
   int iSuccessful;

   /* Use a Stack object referenced by psStack1. */
   
   psStack1 = Stack_new();
   if (psStack1 == NULL) handleMemoryError();
   
   iSuccessful = Stack_push(psStack1, 1.1);
   if (! iSuccessful) handleMemoryError();
   
   iSuccessful = Stack_push(psStack1, 2.2);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(psStack1, 3.3);
   if (! iSuccessful) handleMemoryError();

   while (! Stack_isEmpty(psStack1))
      printf("%g\n", Stack_pop(psStack1));

   /***********************************************/
   /* Cannot access the fields of *psStack1 here. */
   /***********************************************/

   Stack_free(psStack1);
   psStack1 = NULL; /* Unnecessary but safe. */

   /* Use a Stack object referenced by psStack2. */
      
   psStack2 = Stack_new();
   if (psStack2 == NULL) handleMemoryError();
   
   iSuccessful = Stack_push(psStack2, 4.4);
   if (! iSuccessful) handleMemoryError();
   
   iSuccessful = Stack_push(psStack2, 5.5);
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(psStack2, 6.6);
   if (! iSuccessful) handleMemoryError();
   
   while (! Stack_isEmpty(psStack2))
      printf("%g\n", Stack_pop(psStack2));

   /***********************************************/
   /* Cannot access the fields of *psStack2 here. */
   /***********************************************/

   Stack_free(psStack2);
   psStack2 = NULL; /* Unnecessary but safe. */

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
