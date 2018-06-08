/*--------------------------------------------------------------------*/
/* sort5.c                                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* Grow the memory chunk pointed to by pdChunk so it can store
   uArrayLength elements of type double.  Return the address of the new
   memory chunk.  */

static double *grow(double *pdChunk, size_t uArrayLength)
{
   size_t uNewSize;
   double *pdNewChunk;

   assert(pdChunk != NULL);

   uNewSize = uArrayLength * sizeof(double);
   pdNewChunk = (double*)realloc(pdChunk, uNewSize);
   if (pdNewChunk == NULL)
   {
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }
      
   return pdNewChunk;
}

/*--------------------------------------------------------------------*/

/* Return -1, 0, or 1 depending upon whether double *pvItem1 is less
   than, equal to, or greater than double *pvItem2, respectively. */

static int compareDouble(const void *pvItem1, const void *pvItem2)
{
   assert(pvItem1 != NULL);
   assert(pvItem2 != NULL);

   if (*(double*)pvItem1 < *(double*)pvItem2) return -1;
   if (*(double*)pvItem1 > *(double*)pvItem2) return 1;
   return 0;
}

/*--------------------------------------------------------------------*/

/* Read numbers from stdin, and write them in ascending order to
   stdout.  Return 0 if successful, or EXIT_FAILURE if stdin contains
   a non-number. */

int main(void)
{
   enum {INITIAL_ARRAY_LENGTH = 2};
   enum {ARRAY_GROWTH_FACTOR = 2};

   double *pdNumbers;
   size_t uCount;
   size_t uArrayLength;
   double dNumber;
   size_t u;
   int iScanfRet;

   /* Create a small array. */
   uArrayLength = INITIAL_ARRAY_LENGTH;
   pdNumbers = (double*)calloc(uArrayLength, sizeof(double));
   if (pdNumbers == NULL)
   {
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }

   /* Read the numbers into the array, expanding the size of the
      array as necessary. */
   for (uCount = 0; ; uCount++)
   {
      iScanfRet = scanf("%lf", &dNumber);
      if (iScanfRet == 0)
      {
         fprintf(stderr, "Non-number in stdin\n");
         exit(EXIT_FAILURE);
      } 
      if (iScanfRet == EOF)
         break;
      if (uCount == uArrayLength)
      {
         uArrayLength *= ARRAY_GROWTH_FACTOR;
         pdNumbers = grow(pdNumbers, uArrayLength);

      }
      pdNumbers[uCount] = dNumber;
   }

   /* Sort the array. */
   qsort(pdNumbers, uCount, sizeof(double), compareDouble);

   /* Write the numbers from the array. */
   for (u = 0; u < uCount; u++)
      printf("%g\n", pdNumbers[u]);

   /* Free the array. */
   free(pdNumbers);

   return 0;
}
