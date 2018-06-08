/*--------------------------------------------------------------------*/
/* testdynarray.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "dynarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* Print string *pvItem using format pvFormat. */

static void printString(void *pvItem, void *pvFormat)
{
   assert(pvItem != NULL);
   assert(pvFormat != NULL);
   printf((char*)pvFormat, (char*)pvItem);
}

/*--------------------------------------------------------------------*/

/* Return -1, 0, or 1 depending upon whether *pvOne is
   less than, equal to, or greater than *pvTwo, respectively. */

static int compareString(const void *pvOne, const void *pvTwo)
{
   assert(pvOne != NULL);
   assert(pvTwo != NULL);
   return strcmp((char*)pvOne, (char*)pvTwo);
}

/*--------------------------------------------------------------------*/

/* Demonstrate the DynArray ADT. Return 0. */

int main(void)
{
   DynArray_T oDynArray;
   size_t uLength;
   char **ppcArray;
   size_t u;
   char *pcElement;
   size_t uIndex = 0;
   int iFound;

   /* Demonstrate DynArray_new. */

   oDynArray = DynArray_new(0);
   if (oDynArray == NULL) exit(EXIT_FAILURE);

   /* Demonstrate DynArray_add. */

   if (! DynArray_add(oDynArray, "Ruth")) exit(EXIT_FAILURE);
   if (! DynArray_add(oDynArray, "Gehrig")) exit(EXIT_FAILURE);
   if (! DynArray_add(oDynArray, "Mantle")) exit(EXIT_FAILURE);
   if (! DynArray_add(oDynArray, "Jeter")) exit(EXIT_FAILURE);

   /* Demonstrate DynArray_getLength. */

   printf("-----------------------------------------------------\n");
   uLength = DynArray_getLength(oDynArray);
   printf("DynArray length:  %lu\n", uLength);

   /* Demonstrate DynArray_get. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 4 elements\n");
   printf("-----------------------------------------------------\n");
   uLength = DynArray_getLength(oDynArray);
   for (u = 0; u < uLength; u++)
      printf("%s\n", (char*)DynArray_get(oDynArray, u));

   /* Demonstrate DynArray_set. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 4 elements\n");
   printf("-----------------------------------------------------\n");
   (void)DynArray_set(oDynArray, 2, "Berra");
   uLength = DynArray_getLength(oDynArray);
   for (u = 0; u < uLength; u++)
      printf("%s\n", (char*)DynArray_get(oDynArray, u));

   /* Demonstrate DynArray_addAt. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 5 elements\n");
   printf("-----------------------------------------------------\n");
   if (! DynArray_addAt(oDynArray, 1, "Maris")) exit(EXIT_FAILURE);
   uLength = DynArray_getLength(oDynArray);
   for (u = 0; u < uLength; u++)
      printf("%s\n", (char*)DynArray_get(oDynArray, u));

   /* Demonstrate DynArray_removeAt. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 4 elements\n");
   printf("-----------------------------------------------------\n");
   pcElement = (char*)DynArray_removeAt(oDynArray, 1);
   uLength = DynArray_getLength(oDynArray);
   for (u = 0; u < uLength; u++)
      printf("%s\n", (char*)DynArray_get(oDynArray, u));
   printf("Removed element: %s\n", pcElement);

   /* Demonstrate DynArray_toArray. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 4 elements\n");
   printf("-----------------------------------------------------\n");
   uLength = DynArray_getLength(oDynArray);
   ppcArray = (char**)calloc((size_t)uLength, sizeof(char*));
   if (ppcArray == NULL) exit(EXIT_FAILURE);
   DynArray_toArray(oDynArray, (void**)ppcArray);
   for (u = 0; u < uLength; u++)
      printf("%s\n", ppcArray[u]);
   free(ppcArray);

   /* Demonstrate DynArray_map. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 4 elements\n");
   printf("-----------------------------------------------------\n");
   DynArray_map(oDynArray, printString, "%s\n");

   /* Demonstrate DynArray_sort. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 4 elements in ascending order\n");
   printf("-----------------------------------------------------\n");
   DynArray_sort(oDynArray, compareString);
   DynArray_map(oDynArray, printString, "%s\n");

   /* Demonstrate DynArray_search. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 1 element\n");
   printf("-----------------------------------------------------\n");
   iFound = DynArray_search(oDynArray, "Ruth", &uIndex, compareString);
   if (iFound)
      printf("%s\n", (char*)DynArray_get(oDynArray, uIndex));

   /* Demonstrate DynArray_bsearch. */

   printf("-----------------------------------------------------\n");
   printf("This output should list 1 element\n");
   printf("-----------------------------------------------------\n");
   iFound = DynArray_bsearch(oDynArray, "Ruth", &uIndex, compareString);
   if (iFound)
      printf("%s\n", (char*)DynArray_get(oDynArray, uIndex));

   /* Demonstrate DynArray_free. */

   DynArray_free(oDynArray);

   return 0;
}
