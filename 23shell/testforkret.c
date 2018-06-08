/*--------------------------------------------------------------------*/
/* testforkret.c                                                      */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate how to use the value returned by the system-level
   fork() function. Return 0;
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
      /* This code is executed by the child process only. */
      printf("%d child\n", (int)getpid());
   else
      /* This code is executed by the parent process only. */
      printf("%d parent\n", (int)getpid());

   /* This code is executed by both the parent and child processes. */
   printf("%d parent and child\n", (int)getpid());

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 testforkret.c -o testforkret

$ ./testforkret
29409 parent
29409 parent
29409 parent and child
29410 child
29410 parent and child

$ ./testforkret
29413 parent
29413 parent
29413 parent and child
29414 child
29414 parent and child

*/
