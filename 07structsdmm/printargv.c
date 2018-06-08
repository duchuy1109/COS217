/*--------------------------------------------------------------------*/
/* printargv.c                                                        */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* As always, argv is an array of command-line arguments, and argc
   is the count of commant-line arguments.  Write the argc strings of
   argv to stdout.  Return 0. */

int main(int argc, char *argv[])
{
   int i;

   /* Write the command-line argument count to stdout. */
   printf("argc:  %d\n", argc);
   
   /* Write the command-line arguments to stdout. */
   for (i = 0; i < argc; i++)
      printf("argv[%d]:  %s\n", i, argv[i]);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample Executions:

$ gcc217 printargv.c -o printargv

$ ./printargv one two three
argc:  4
argv[0]:  ./printargv
argv[1]:  one
argv[2]:  two
argv[3]:  three

$ ./printargv
argc:  1
argv[0]:  ./printargv

$ ./printargv one "two  three" four
argc:  4
argv[0]:  ./printargv
argv[1]:  one
argv[2]:  two  three
argv[3]:  four

*/
