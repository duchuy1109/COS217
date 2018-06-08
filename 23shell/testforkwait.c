/*--------------------------------------------------------------------*/
/* testforkwait.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the system-level fork() and wait() functions.
   Return 0.
   As usual, argc is the command-line argument count, and argv
   contains the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;
   int i = 0;

   printf("%d parent\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      /* This code is executed by the child process only. */
      for (i = 0; i < 10; i++)
         printf("%d child %d\n", (int)getpid(), i);
      exit(0);
   }

   /* This code is executed by the parent process only. */

   /* Wait for the child process to terminate. */
   iPid = wait(NULL);
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   for (i = 0; i < 10; i++)
      printf("%d parent %d\n", (int)getpid(), i);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testforkwait.c -o testforkwait

$ ./testforkwait
7275 parent
7276 child 0
7276 child 1
7276 child 2
7276 child 3
7276 child 4
7276 child 5
7276 child 6
7276 child 7
7276 child 8
7276 child 9
7275 parent 0
7275 parent 1
7275 parent 2
7275 parent 3
7275 parent 4
7275 parent 5
7275 parent 6
7275 parent 7
7275 parent 8
7275 parent 9

*/
