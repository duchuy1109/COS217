/*--------------------------------------------------------------------*/
/* testforkexit.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the common pattern of using the system-level fork()
   function and the standard C exit() function. Return 0.
   As usual, argc is the command-line argument count, and argv
   contains the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;

   printf("%d parent\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      /* This code is executed by the child process only. */
      printf("%d child\n", (int)getpid());
      exit(0);
   }

   /* This code is executed by the parent process only. */
   printf("%d parent\n", (int)getpid());

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 testforkexit.c -o testforkexit

$ ./testforkexit
29595 parent
29595 parent
29596 child

$ ./testforkexit
29600 parent
29600 parent
29601 child

*/
