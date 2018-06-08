/*--------------------------------------------------------------------*/
/* myname2.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/* Accept a name as argv[1], somehow use it, and write it to stdout.
   Return 0 if successful, and EXIT_FAILURE otherwise. */

int main(int argc, char *argv[])
{
   char *pcName;
   
   if (argc != 2)
   {
      fprintf(stderr, "Wrong number of command-line arguments.\n");
      return EXIT_FAILURE;
   }

   pcName = argv[1];
   
   /* Do something with pcName. */
   
   printf("Thank you %s\n", pcName);
   return 0;
}
   
/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 myname2.c -o myname2

$ ./myname2 Bob
Thank you Bob

$ ./myname2 Bob
Thank you Bob

$ ./myname2 Bob
Thank you Bob

*/
