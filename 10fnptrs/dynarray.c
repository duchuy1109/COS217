/*--------------------------------------------------------------------*/
/* dynarray.c                                                         */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "dynarray.h"
#include <assert.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/

/* The minimum physical length of a DynArray object. */

enum {MIN_PHYS_LENGTH = 2};

/*--------------------------------------------------------------------*/

/* A DynArray consists of an array, along with its logical and
   physical lengths. */

struct DynArray
{
   /* The number of elements in the DynArray from the client's
      point of view. */
   size_t uLength;

   /* The number of elements in the array that underlies the
      DynArray. */
   size_t uPhysLength;

   /* The array that underlies the DynArray. */
   const void **ppvArray;
};

/*--------------------------------------------------------------------*/

#ifndef NDEBUG

/* Check the invariants of oDynArray.  Return 1 (TRUE) iff oDynArray
   is in a valid state. */

static int DynArray_isValid(DynArray_T oDynArray)
{
   if (oDynArray->uPhysLength < MIN_PHYS_LENGTH) return 0;
   if (oDynArray->uLength > oDynArray->uPhysLength) return 0;
   if (oDynArray->ppvArray == NULL) return 0;
   return 1;
}

#endif

/*--------------------------------------------------------------------*/

/* Increase the physical length of oDynArray.  Return 1 (TRUE) if
   successful and 0 (FALSE) if insufficient memory is available. */

static int DynArray_grow(DynArray_T oDynArray)
{
   enum {GROWTH_FACTOR = 2};
   
   size_t uNewLength;
   const void **ppvNewArray;

   assert(oDynArray != NULL);

   uNewLength = GROWTH_FACTOR * oDynArray->uPhysLength;

   ppvNewArray = (const void**)
      realloc(oDynArray->ppvArray, sizeof(void*) * uNewLength);
   if (ppvNewArray == NULL)
      return 0;

   oDynArray->uPhysLength = uNewLength;
   oDynArray->ppvArray = ppvNewArray;
   return 1;
}

/*--------------------------------------------------------------------*/

DynArray_T DynArray_new(size_t uLength)
{
   DynArray_T oDynArray;

   oDynArray = (struct DynArray*)malloc(sizeof(struct DynArray));
   if (oDynArray == NULL)
      return NULL;

   oDynArray->uLength = uLength;
   if (uLength > MIN_PHYS_LENGTH)
      oDynArray->uPhysLength = uLength;
   else
      oDynArray->uPhysLength = MIN_PHYS_LENGTH;

   oDynArray->ppvArray =
      (const void**)calloc(oDynArray->uPhysLength, sizeof(void*));
   if (oDynArray->ppvArray == NULL)
   {
      free(oDynArray);
      return NULL;
   }

   return oDynArray;
}

/*--------------------------------------------------------------------*/

void DynArray_free(DynArray_T oDynArray)
{
   assert(oDynArray != NULL);
   assert(DynArray_isValid(oDynArray));

   free(oDynArray->ppvArray);
   free(oDynArray);
}

/*--------------------------------------------------------------------*/

size_t DynArray_getLength(DynArray_T oDynArray)
{
   assert(oDynArray != NULL);
   assert(DynArray_isValid(oDynArray));

   return oDynArray->uLength;
}

/*--------------------------------------------------------------------*/

void *DynArray_get(DynArray_T oDynArray, size_t uIndex)
{
   assert(oDynArray != NULL);
   assert(uIndex < oDynArray->uLength);
   assert(DynArray_isValid(oDynArray));

   return (void*)(oDynArray->ppvArray)[uIndex];
}

/*--------------------------------------------------------------------*/

void *DynArray_set(DynArray_T oDynArray, size_t uIndex,
                   const void *pvElement)
{
   const void *pvOldElement;

   assert(oDynArray != NULL);
   assert(uIndex < oDynArray->uLength);
   assert(DynArray_isValid(oDynArray));

   pvOldElement = oDynArray->ppvArray[uIndex];
   oDynArray->ppvArray[uIndex] = pvElement;

   assert(DynArray_isValid(oDynArray));

   return (void*)pvOldElement;
}

/*--------------------------------------------------------------------*/

int DynArray_add(DynArray_T oDynArray, const void *pvElement)
{
   assert(oDynArray != NULL);
   assert(DynArray_isValid(oDynArray));

   if (oDynArray->uLength == oDynArray->uPhysLength)
      if (! DynArray_grow(oDynArray))
         return 0;

   oDynArray->ppvArray[oDynArray->uLength] = pvElement;
   oDynArray->uLength++;

   assert(DynArray_isValid(oDynArray));

   return 1;
}

/*--------------------------------------------------------------------*/

int DynArray_addAt(DynArray_T oDynArray, size_t uIndex,
                   const void *pvElement)
{
   size_t u;

   assert(oDynArray != NULL);
   assert(uIndex <= oDynArray->uLength);
   assert(DynArray_isValid(oDynArray));

   if (oDynArray->uLength == oDynArray->uPhysLength)
      if (! DynArray_grow(oDynArray))
         return 0;

   for (u = oDynArray->uLength; u > uIndex; u--)
      oDynArray->ppvArray[u] = oDynArray->ppvArray[u-1];

   oDynArray->ppvArray[uIndex] = pvElement;
   oDynArray->uLength++;

   assert(DynArray_isValid(oDynArray));

   return 1;
}

/*--------------------------------------------------------------------*/

void *DynArray_removeAt(DynArray_T oDynArray, size_t uIndex)
{
   const void *pvOldElement;
   size_t u;

   assert(oDynArray != NULL);
   assert(uIndex < oDynArray->uLength);
   assert(DynArray_isValid(oDynArray));

   pvOldElement = oDynArray->ppvArray[uIndex];

   oDynArray->uLength--;

   for (u = uIndex; u < oDynArray->uLength; u++)
      oDynArray->ppvArray[u] = oDynArray->ppvArray[u+1];

   assert(DynArray_isValid(oDynArray));

   return (void*)pvOldElement;
}

/*--------------------------------------------------------------------*/

void DynArray_toArray(DynArray_T oDynArray, void **ppvArray)
{
   size_t u;

   assert(oDynArray != NULL);
   assert(ppvArray != NULL);
   assert(DynArray_isValid(oDynArray));

   for (u = 0; u < oDynArray->uLength; u++)
      ppvArray[u] = (void*)oDynArray->ppvArray[u];
}

/*--------------------------------------------------------------------*/

void DynArray_map(DynArray_T oDynArray,
                  void (*pfApply)(void *pvElement, void *pvExtra),
                  const void *pvExtra)
{
   size_t u;

   assert(oDynArray != NULL);
   assert(pfApply != NULL);
   assert(DynArray_isValid(oDynArray));

   for (u = 0; u < oDynArray->uLength; u++)
      (*pfApply)((void*)oDynArray->ppvArray[u], (void*)pvExtra);
}

/*--------------------------------------------------------------------*/

/* Sort the array of elements that resides in memory at
   addresses ppvLo...ppvHi in ascending order, as determined
   by *pfCompare.
   *pfCompare must return <0, 0, or >0 depending upon whether
   *pvElement1 is less than, equal to, or greater than *pvElement2,
   respectively. */

static void DynArray_qsort(
   const void **ppvLo,
   const void **ppvHi,
   int (*pfCompare) (const void *pvElement1, const void *pvElement2))
{
   /* This function implements a variation of the quicksort algorithm
      shown in the book "Algorithms + Data Structures = Programs" by 
      Niklaus Wirth. */
      
   /* This function uses pointers instead of indices to avoid
      complications with using unsigned integers as array indices. */

   const void **ppvRight;
   const void **ppvLeft;
   const void *pvPivot;
   const void *pvTemp;

   assert(ppvLo != NULL);
   assert(ppvHi != NULL);
   assert(pfCompare != NULL);
         
   ppvRight = ppvLo;
   ppvLeft = ppvHi;
   pvPivot = *(ppvLo + ((ppvHi - ppvLo) / 2));
      
   while (ppvRight <= ppvLeft)
   {
      while ((*pfCompare)(*ppvRight, pvPivot) < 0)
         ppvRight++;
      while ((*pfCompare)(pvPivot, *ppvLeft) < 0)
         ppvLeft--; 
      if (ppvRight <= ppvLeft)
      {
         /* Swap *ppvRight and *ppvLeft. */
         pvTemp = *ppvRight;
         *ppvRight = *ppvLeft;
         *ppvLeft = pvTemp;
         
         ppvRight++;
         ppvLeft--;
      }
   }
       
   if (ppvLo < ppvLeft)
      DynArray_qsort(ppvLo, ppvLeft, pfCompare);
   if (ppvRight < ppvHi)
      DynArray_qsort(ppvRight, ppvHi, pfCompare);
}

/*--------------------------------------------------------------------*/

void DynArray_sort(DynArray_T oDynArray,
                   int (*pfCompare)(const void *pvElement1,
                                    const void *pvElement2))
{
   assert(oDynArray != NULL);
   assert(pfCompare != NULL);
   assert(DynArray_isValid(oDynArray));
   
   if (oDynArray->uLength < 2)
      return;
   
   DynArray_qsort( 
      &oDynArray->ppvArray[0], 
      &oDynArray->ppvArray[oDynArray->uLength-1],
      pfCompare);

   assert(DynArray_isValid(oDynArray));
}

/*--------------------------------------------------------------------*/

int DynArray_search(DynArray_T oDynArray, 
                    void *pvSoughtElement,
                    size_t *puIndex,
                    int (*pfCompare)(const void *pvElement1,
                                     const void *pvElement2))
{
   size_t u;

   assert(oDynArray != NULL);
   assert(puIndex != NULL);
   assert(pfCompare != NULL);
   assert(DynArray_isValid(oDynArray));

   for (u = 0; u < oDynArray->uLength; u++)
      if ((*pfCompare)(oDynArray->ppvArray[u], pvSoughtElement) == 0)
      {
         *puIndex = u;
         return 1;
      }
   return 0;
}



/*--------------------------------------------------------------------*/

/* Binary search the array of elements that resides in memory at
   addresses ppvLo...ppvHi for pvSoughtElement.
   *pfCompare must return <0, 0, or >0 depending upon whether
   *pvElement1 is less than, equal to, or greater than *pvElement2,
   respectively. */
      
static const void **DynArray_bsearchHelp(
   void *pvSoughtElement,
   const void **ppvLo,
   const void **ppvHi,
   int (*pfCompare)(const void *pvElement1, const void *pvElement2))
{
   /* This function uses pointers instead of indices to avoid
      complications with using unsigned integers as array indices. */

   const void **ppvMid;
   int iCompare;

   assert(ppvLo != NULL);
   assert(ppvHi != NULL);
   assert(pfCompare != NULL);
   
   while (ppvLo <= ppvHi)
   {
      ppvMid = ppvLo + ((ppvHi - ppvLo) / 2);
      iCompare = (*pfCompare)(pvSoughtElement, *ppvMid);
      if (iCompare < 0)
         ppvHi = ppvMid - 1;
      else if (iCompare > 0)
         ppvLo = ppvMid + 1;
      else
         return ppvMid;
   }
   return NULL;
}
                     
/*--------------------------------------------------------------------*/

int DynArray_bsearch(DynArray_T oDynArray, 
                     void *pvSoughtElement,
                     size_t *puIndex,
                     int (*pfCompare)(const void *pvElement1,
                                      const void *pvElement2))
{
   const void **ppvElement;
   
   assert(oDynArray != NULL);
   assert(puIndex != NULL);
   assert(pfCompare != NULL);
   assert(DynArray_isValid(oDynArray));
   
   if (oDynArray->uLength == 0)
      return 0;
   
   ppvElement = DynArray_bsearchHelp(
      pvSoughtElement,
      &oDynArray->ppvArray[0], 
      &oDynArray->ppvArray[oDynArray->uLength-1],
      pfCompare);
   
   if (ppvElement == NULL)
      return 0;
   
   *puIndex = (size_t)(ppvElement - &oDynArray->ppvArray[0]);
   return 1;
}
