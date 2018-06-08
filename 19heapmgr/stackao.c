/*--------------------------------------------------------------------*/
/* stackao.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "stackao.h"
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* In lieu of a boolean data type. */
enum {FALSE, TRUE};

/*--------------------------------------------------------------------*/

/* The state of the Stack object. */

/* The array in which items are stored. */
static double *pdArray;

/* The index one beyond the top element. */
static size_t uTop;

/* The number of elements in the array. */
static size_t uPhysLength;

/* Is the Stack initialized? */
static int iInitialized = FALSE;

/*--------------------------------------------------------------------*/

/* Increase the physical length of the Stack object.  Return 1 (TRUE) if
   successful, or 0 (FALSE) if insufficient memory is available. */

static int Stack_grow(void)
{
   enum {GROWTH_FACTOR = 2};

   size_t uNewPhysLength;
   double *pdNewArray;

   assert(iInitialized);

   uNewPhysLength = GROWTH_FACTOR * uPhysLength;
   pdNewArray = (double*)
      realloc(pdArray, sizeof(double) * uNewPhysLength);
   if (pdNewArray == NULL)
      return 0;

   uPhysLength = uNewPhysLength;
   pdArray = pdNewArray;

   return 1;
}

/*--------------------------------------------------------------------*/

int Stack_init(void)
{
   enum {INITIAL_PHYS_LENGTH = 2};
   
   assert(! iInitialized);

   pdArray = (double*)calloc(INITIAL_PHYS_LENGTH, sizeof(double));
   if (pdArray == NULL)
      return 0;

   uTop = 0;
   uPhysLength = INITIAL_PHYS_LENGTH;
   iInitialized = TRUE;
   return 1;
}

/*--------------------------------------------------------------------*/

void Stack_free(void)
{
   assert(iInitialized);
   free(pdArray);
   iInitialized = FALSE;
}

/*--------------------------------------------------------------------*/

int Stack_push(double dItem)
{
   assert(iInitialized);
   if (uTop == uPhysLength)
      if (! Stack_grow())
         return 0;

   pdArray[uTop] = dItem;
   uTop++;
   return 1;
}

/*--------------------------------------------------------------------*/

double Stack_pop(void)
{
   assert(iInitialized);
   assert(uTop > 0);
   uTop--;
   return pdArray[uTop];
}

/*--------------------------------------------------------------------*/

int Stack_isEmpty(void)
{
   assert(iInitialized);
   return uTop == 0;
}
