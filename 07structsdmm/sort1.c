/*--------------------------------------------------------------------*/
/* sort1.c                                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* Sort pdNumbers[0..iCount-1] in ascending order. */

static void insertionSort(double *pdNumbers, int iCount)
{
   int i1;
   int i2;
   double dTemp;

   assert(pdNumbers != NULL);

   for (i1 = 1; i1 < iCount; i1++)
      for (i2 = i1; i2 > 0; i2--)
         if (pdNumbers[i2] < pdNumbers[i2-1])
         {
            dTemp = pdNumbers[i2];
            pdNumbers[i2] = pdNumbers[i2-1];
            pdNumbers[i2-1] = dTemp;
         }
}
   
/*--------------------------------------------------------------------*/

/* Read numbers from stdin, and write them in ascending order to
   stdout.  Return 0 if successful, or EXIT_FAILURE if stdin contains
   a non-number. */

int main(void)
{
   enum {ARRAY_LENGTH = 10};

   double adNumbers[ARRAY_LENGTH];
   int iCount;
   double dNumber;
   int i;
   int iScanfRet;

   /* Read the numbers into an array. */
   for (iCount = 0; iCount < ARRAY_LENGTH; iCount++)
   {
      iScanfRet = scanf("%lf", &dNumber);
      if (iScanfRet == 0)
      {
         fprintf(stderr, "Non-number in stdin\n");
         exit(EXIT_FAILURE);
      }         
      if (iScanfRet == EOF)
         break;
      adNumbers[iCount] = dNumber;
   }

   /* Sort the array. */
   insertionSort(adNumbers, iCount);

   /* Write the numbers from the array. */
   for (i = 0; i < iCount; i++)
      printf("%g\n", adNumbers[i]);

   return 0;
}
