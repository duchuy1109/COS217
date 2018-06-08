/*--------------------------------------------------------------------*/
/* sort3.c                                                            */
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

/* The first number in stdin should be an integer which is a count of
   how many numbers follow in stdin.  Read that integer.  Then read the
   numbers from stdin, and write them in ascending order to stdout.
   Return 0 if successful, or EXIT_FAILURE if stdin contains a
   non-number. */

int main(void)
{
   double *pdNumbers;
   int iCount;
   int iArrayLength;
   double dNumber;
   int i;
   int iScanfRet;
   
   /* Read the integer that specifies how many numbers follow. */
   iScanfRet = scanf("%d", &iArrayLength);
   if ((iScanfRet != 1) || (iArrayLength < 0))
   {
      fprintf(stderr, "Improper number count\n");
      exit(EXIT_FAILURE);
   }
   
   /* Create an array with the specified number of elements. */   
   pdNumbers = (double*)calloc((size_t)iArrayLength, sizeof(double));
   if (pdNumbers == NULL)
   {
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }

   /* Read the numbers into the array. */
   for (iCount = 0; iCount < iArrayLength; iCount++)
   {
      iScanfRet = scanf("%lf", &dNumber);
      if (iScanfRet == 0)
      {
         fprintf(stderr, "Non-number in stdin\n");
         exit(EXIT_FAILURE);
      }         
      if (iScanfRet == EOF)
         break;
      pdNumbers[iCount] = dNumber;       
   }

   /* Sort the array. */
   insertionSort(pdNumbers, iCount);

   /* Write the numbers from the array. */
   for (i = 0; i < iCount; i++)
      printf("%g\n", pdNumbers[i]);

   /* Free the array. */
   free(pdNumbers);

   return 0;
}
