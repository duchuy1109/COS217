/*--------------------------------------------------------------------*/
/* stack.c (Version 1)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "stack.h"
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* Increase the physical length of *psStack.  Return 1 (TRUE) if
   successful, or 0 (FALSE) if insufficient memory is available. */

static int Stack_grow(struct Stack *psStack)
{
   enum {GROWTH_FACTOR = 2};
    
   size_t uNewPhysLength;
   double *pdNewArray;

   assert(psStack != NULL);

   uNewPhysLength = GROWTH_FACTOR * psStack->uPhysLength;

   pdNewArray = (double*)
      realloc(psStack->pdArray, sizeof(double) * uNewPhysLength);
   if (pdNewArray == NULL)
      return 0;

   psStack->uPhysLength = uNewPhysLength;
   psStack->pdArray = pdNewArray;

   return 1;
}

/*--------------------------------------------------------------------*/

struct Stack *Stack_new(void)
{
   enum {INITIAL_PHYS_LENGTH = 2};
    
   struct Stack *psStack;

   psStack = (struct Stack*)malloc(sizeof(struct Stack));
   if (psStack == NULL)
      return NULL;

   psStack->pdArray =
      (double*)calloc(INITIAL_PHYS_LENGTH, sizeof(double));
   if (psStack->pdArray == NULL)
   {
      free(psStack);
      return NULL;
   }

   psStack->uTop = 0;
   psStack->uPhysLength = INITIAL_PHYS_LENGTH;
   return psStack;
}

/*--------------------------------------------------------------------*/

void Stack_free(struct Stack *psStack)
{
   assert(psStack != NULL);

   free(psStack->pdArray);
   free(psStack);
}

/*--------------------------------------------------------------------*/

int Stack_push(struct Stack *psStack, double dItem)
{
   int iSuccessful;
   assert(psStack != NULL);

   if (psStack->uTop == psStack->uPhysLength)
   {
      iSuccessful = Stack_grow(psStack);
      if (! iSuccessful)
         return 0;
   }
   
   (psStack->pdArray)[psStack->uTop] = dItem;
   (psStack->uTop)++;
   return 1;
}

/*--------------------------------------------------------------------*/

double Stack_pop(struct Stack *psStack)
{
   assert(psStack != NULL);
   assert(psStack->uTop > 0);

   (psStack->uTop)--;
   return (psStack->pdArray)[psStack->uTop];
}

/*--------------------------------------------------------------------*/

int Stack_isEmpty(struct Stack *psStack)
{
   assert(psStack != NULL);

   return psStack->uTop == 0;
}
