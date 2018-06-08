/*--------------------------------------------------------------------*/
/* testforkloop.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate context switching among concurrent processes. Return 0.
   As usual, argc is the command-line argument count, and argv
   contains the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;
   int i;

   printf("%d parent\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      /* This code is executed by the child process only. */
      for (i = 0; i < 10 ; i++)
         printf("%d child %d\n", (int)getpid(), i);
      exit(0);
   }

   /* This code is executed by the parent process only. */
   for (i = 0; i < 10; i++)
      printf("%d parent %d\n", (int)getpid(), i);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testforkloop.c -o testforkloop

$ ./testforkloop
9857 parent
9857 parent 0
9857 parent 1
9857 parent 2
9857 parent 3
9857 parent 4
9857 parent 5
9857 parent 6
9857 parent 7
9858 child 0
9857 parent 8
9858 child 1
9857 parent 9
9858 child 2
9858 child 3
9858 child 4
9858 child 5
9858 child 6
9858 child 7
9858 child 8
9858 child 9

*/
