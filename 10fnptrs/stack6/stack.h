/*--------------------------------------------------------------------*/
/* stack.h (Version 6)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#ifndef STACK_INCLUDED
#define STACK_INCLUDED

/* A Stack_T is a last-in-first-out collection of items. */

typedef struct Stack *Stack_T;

/*--------------------------------------------------------------------*/

/* Return a new Stack_T object, or NULL if insufficient memory is
   available. */

Stack_T Stack_new(void);

/*--------------------------------------------------------------------*/

/* Free oStack. */

void Stack_free(Stack_T oStack);

/*--------------------------------------------------------------------*/

/* Push pvItem onto oStack.  Return 1 (TRUE) if successful, or 0
   (FALSE) if insufficient memory is available. */

int Stack_push(Stack_T oStack, const void *pvItem);

/*--------------------------------------------------------------------*/

/* Pop and return the top item of oStack. */

void *Stack_pop(Stack_T oStack);

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if oStack is empty, or 0 (FALSE) otherwise. */

int Stack_isEmpty(Stack_T oStack);

/*--------------------------------------------------------------------*/

/* Apply function *pfApply to each element of oStack, passing
   pvExtra as an extra argument.  That is, for each element pvItem
   of oStack, call (*pfApply)(pvItem, pvExtra). */

void Stack_map(Stack_T oStack,
               void (*pfApply)(void *pvItem, void *pvExtra),
               const void *pvExtra);

#endif
