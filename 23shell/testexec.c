/*--------------------------------------------------------------------*/
/* textexec.c                                                         */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the system-level execvp() function and the
   standard C perror() function.
   As usual, argc is the command-line argument count, and argv
   contains the command-line arguments. */

int main(int argc, char *argv[])
{
   char *apcArgv[2];

   printf("%d testexec\n", (int)getpid());

   apcArgv[0] = "./hello";
   apcArgv[1] = NULL;

   execvp("./hello", apcArgv);

   perror(argv[0]);
   /* Alternative:
      fprintf(stderr, "%s: %s\n", argv[0], strerror(errno)); */

   exit(EXIT_FAILURE);
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 hello.c -o hello

$ gcc217 testexec.c -o testexec

$ ./testexec
22440 testexec
22440 hello

$ mv hello nothello

$ ./testexec
22454 testexec
./testexec: No such file or directory

$ mv nothello hello

$ ./testexec
22463 testexec
22463 hello

*/
