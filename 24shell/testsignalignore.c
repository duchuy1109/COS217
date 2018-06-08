/*--------------------------------------------------------------------*/
/* testsignalignore.c                                                 */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>   /* Required for splint. */

/*--------------------------------------------------------------------*/

/* Demonstrate ignoring signals and restoring default signal behavior.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. The function never returns. */

int main(int argc, char *argv[])
{
   void (*pfRet)(int);
   sigset_t sSet;
   int iRet;

   /* Make sure SIGINT signals are not blocked. */
   iRet = sigemptyset(&sSet);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }
   iRet = sigaddset(&sSet, SIGINT);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }   
   iRet = sigprocmask(SIG_UNBLOCK, &sSet, NULL);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   for (;;)
   {
      printf("\nFor the next 3 sec SIGINT signals are ignored.");
      iRet = fflush(stdout);
      if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); } 
      /* Ignore SIGINT signals. */
      pfRet = signal(SIGINT, SIG_IGN);
      if (pfRet == SIG_ERR) {perror(argv[0]); exit(EXIT_FAILURE); }
      sleep(3);
      
      printf("\nFor the next 3 sec SIGINT signals are not ignored.");
      iRet = fflush(stdout);
      if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); } 
      /* Restore the default behavior for SIGINT signals. */
      pfRet = signal(SIGINT, SIG_DFL);
      if (pfRet == SIG_ERR) {perror(argv[0]); exit(EXIT_FAILURE); }
      sleep(3);
   }
        
   /* Will not reach this point. */
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testsignalignore.c -o testsignalignore

$ ./testsignalignore

For the next 3 sec SIGINT signals are ignored.^C^C^C
For the next 3 sec SIGINT signals are not ignored.
For the next 3 sec SIGINT signals are ignored.^C^C^C^C
For the next 3 sec SIGINT signals are not ignored.^C

*/
