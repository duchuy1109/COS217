/*--------------------------------------------------------------------*/
/* myname1.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/* Read a name from stdin, somehow use it, and write it to stdout. 
   Return 0 if successful, and EXIT_FAILURE otherwise. */

int main(void)
{
   enum {ARRAY_LENGTH = 100};
   char acName[ARRAY_LENGTH];
   char *pcRet;
   
   printf("What is your name?\n");
   pcRet = fgets(acName, ARRAY_LENGTH, stdin);
   if (pcRet == NULL)
   {
      fprintf(stderr, "Read failure.\n");
      return EXIT_FAILURE;
   } 
   
   /* Do something with acName. */
   
   printf("Thank you %s", acName);
   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 myname1.c -o myname1

$ ./myname1
What is your name?
Bob
Thank you Bob

$ ./myname1
What is your name?
Bob
Thank you Bob

$ ./myname1
What is your name?
Bob
Thank you Bob

*/

