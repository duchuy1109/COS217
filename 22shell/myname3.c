/*--------------------------------------------------------------------*/
/* myname3.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/* Accept a name as an environment variable, somehow use it, and 
   write it to stdout. Return 0 if successful, and EXIT_FAILURE
   otherwise. */

int main(int argc, char *argv[])
{
   char *pcName;
   
   pcName = getenv("MYNAME");
   if (pcName == NULL)
    {
      fprintf(stderr, "No MYNAME environment variable.\n");
      return EXIT_FAILURE;
   }     
 
   /* Do something with pcName. */
   
   printf("Thank you %s\n", pcName);
   return 0;
}
   
/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 myname3.c -o myname3

$ export MYNAME=Bob

$ ./myname3
Thank you Bob

$ ./myname3
Thank you Bob

$ ./myname3
Thank you Bob

*/

