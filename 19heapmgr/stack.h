/*--------------------------------------------------------------------*/
/* stack.h (Version 3)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#ifndef STACK_INCLUDED
#define STACK_INCLUDED

/* A Stack_T object is a last-in-first-out collection of doubles. */

typedef struct Stack *Stack_T;

/*--------------------------------------------------------------------*/

/* Return a new Stack_T object, or NULL if insufficient memory is
   available. */

Stack_T Stack_new(void);

/*--------------------------------------------------------------------*/

/* Free oStack. */

void Stack_free(Stack_T oStack);

/*--------------------------------------------------------------------*/

/* Push dItem onto oStack.  Return 1 (TRUE) if successful, or 0
   (FALSE) if insufficient memory is available. */

int Stack_push(Stack_T oStack, double dItem);

/*--------------------------------------------------------------------*/

/* Pop and return the top item of oStack. */

double Stack_pop(Stack_T oStack);

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if oStack is empty, or 0 (FALSE) otherwise. */

int Stack_isEmpty(Stack_T oStack);

#endif
