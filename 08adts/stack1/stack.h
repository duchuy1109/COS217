/*--------------------------------------------------------------------*/
/* stack.h (Version 1)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <stddef.h>

/* A Stack object is a last-in-first-out collection of doubles. */

struct Stack
{
   /* The array in which items are stored. */
   double *pdArray;

   /* The index one beyond the top element. */
   size_t uTop;

   /* The number of elements in the array. */
   size_t uPhysLength;
};

/*--------------------------------------------------------------------*/

/* Return the address of a new Stack object, or NULL if insufficient
   memory is available. */

struct Stack *Stack_new(void);

/*--------------------------------------------------------------------*/

/* Free psStack. */

void Stack_free(struct Stack *psStack);

/*--------------------------------------------------------------------*/

/* Push dItem onto *psStack.  Return 1 (TRUE) if successful, or 0
   (FALSE) if insufficient memory is available. */

int Stack_push(struct Stack *psStack, double dItem);

/*--------------------------------------------------------------------*/

/* Pop and return the top item of *psStack. */

double Stack_pop(struct Stack *psStack);

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if *psStack is empty, or 0 (FALSE) otherwise.  */

int Stack_isEmpty(struct Stack *psStack);

#endif
