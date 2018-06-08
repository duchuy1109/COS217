/*--------------------------------------------------------------------*/
/* teststack.c (Version 6)                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

/*--------------------------------------------------------------------*/

/* Write an error message to stderr indicating that not enough memory
   is available.  Then exit with status EXIT_FAILURE. */

static void handleMemoryError(void)
{
   fprintf(stderr, "Insufficient memory\n");
   exit(EXIT_FAILURE);
}


/*--------------------------------------------------------------------*/

/* Print string pvItem using format string pvExtra. */

static void printString(void *pvItem, void *pvExtra)
{
   assert(pvItem != NULL);
   assert(pvExtra != NULL);
   printf((char*)pvExtra, (char*)pvItem);
}

/*--------------------------------------------------------------------*/

/* Accumulate double *pvItem into *pvExtra. */

static void sumDouble(void *pvItem, void *pvExtra)
{
   double *pdItem;
   double *pdSum;
   assert(pvItem != NULL);
   assert(pvExtra != NULL);
   pdItem = (double*)pvItem;
   pdSum = (double*)pvExtra;
   *pdSum += *pdItem;
}

/*--------------------------------------------------------------------*/

/* Free pvItem.  pvExtra is unused. */

static void freeDouble(void *pvItem, void *pvExtra)
{
   assert(pvItem != NULL);
   free(pvItem);
}

/*--------------------------------------------------------------------*/

/* Test the Stack ADT.  Return 0, or EXIT_FAILURE if not enough memory
   is available. */

int main(void)
{
   Stack_T oStack1;
   Stack_T oStack2;
   int iSuccessful;
   double *pd;
   double dSum = 0.0;

   /* Create and use a Stack of strings. */

   oStack1 = Stack_new();
   if (oStack1 == NULL) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Ruth");
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Gehrig");
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Mantle");
   if (! iSuccessful) handleMemoryError();

   Stack_map(oStack1, printString, "%s\n");

   Stack_free(oStack1);
   oStack1 = NULL; /* Unnecessary but safe. */

   /* Create and use a Stack of doubles. */

   oStack2 = Stack_new();
   if (oStack2 == NULL) handleMemoryError();

   pd = (double*)malloc(sizeof(double));
   if (pd == NULL) handleMemoryError();
   *pd = 1.1;
   iSuccessful = Stack_push(oStack2, pd);
   if (! iSuccessful) handleMemoryError();

   pd = (double*)malloc(sizeof(double));
   if (pd == NULL) handleMemoryError();
   *pd = 2.2;
   iSuccessful = Stack_push(oStack2, pd);
   if (! iSuccessful) handleMemoryError();

   pd = (double*)malloc(sizeof(double));
   if (pd == NULL) handleMemoryError();
   *pd = 3.3;
   iSuccessful = Stack_push(oStack2, pd);
   if (! iSuccessful) handleMemoryError();
   
   pd = NULL; /* Unnecessary. */

   Stack_map(oStack2, sumDouble, &dSum);

   printf("The sum is %g.\n", dSum);

   Stack_map(oStack2, freeDouble, NULL);

   Stack_free(oStack2);
   oStack2 = NULL; /* Unnecessary but safe. */

   return 0;
}
