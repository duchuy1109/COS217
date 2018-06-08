/*--------------------------------------------------------------------*/
/* stackao.h                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#ifndef STACKAO_INCLUDED
#define STACKAO_INCLUDED

/* The Stack object is a last-in-first-out collection of doubles. */

/*--------------------------------------------------------------------*/

/* Initialize the Stack object.  Return 1 (TRUE) if successful, or
   0 (FALSE) if insufficient memory is available. */

int Stack_init(void);

/*--------------------------------------------------------------------*/

/* Free the resources consumed by the Stack object, and uninitialize
   it. */

void Stack_free(void);

/*--------------------------------------------------------------------*/

/* Push dItem onto the Stack object.  Return 1 (TRUE) if successful,
   or 0 (FALSE) if insufficient memory is available. */

int Stack_push(double dItem);

/*--------------------------------------------------------------------*/

/* Pop and return the top item of the Stack object. */

double Stack_pop(void);

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if the Stack object is empty, or 0 (FALSE)
   otherwise. */

int Stack_isEmpty(void);

#endif
