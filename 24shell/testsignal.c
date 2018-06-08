/*--------------------------------------------------------------------*/
/* testsignal.c                                                       */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>   /* Required for splint. */

/*--------------------------------------------------------------------*/

/* The name of the executable binary file. */

static const char *pcPgmName;

/*--------------------------------------------------------------------*/

/* This function is intended to be a signal handler.  Write a message
   to stdout that contains iSignal, the number of the signal that
   caused the function to be called. */

static void myHandler(int iSignal)
{
   int iRet;
   /* Really shouldn't call printf() or fflush() here.
      See Bryant & O'Hallaron page 766. */
   printf("In myHandler with parameter %d\n", iSignal);
   iRet = fflush(stdout);
   if (iRet == EOF) {perror(pcPgmName); exit(EXIT_FAILURE); }
}

/*--------------------------------------------------------------------*/

/* Demonstrate the signal() function and the sigprocmask() system-levl
   function. As usual, argc is the command-line argument count, and
   argv contains the command-line arguments. The function never
   returns. */

int main(int argc, char *argv[])
{
   void (*pfRet)(int);
   sigset_t sSet;
   int iRet;
   
   pcPgmName = argv[0];

   /* Make sure SIGINT signals are not blocked. */
   iRet = sigemptyset(&sSet);
   if (iRet == -1) {perror(pcPgmName); exit(EXIT_FAILURE); }
   iRet = sigaddset(&sSet, SIGINT);
   if (iRet == -1) {perror(pcPgmName); exit(EXIT_FAILURE); }
   iRet = sigprocmask(SIG_UNBLOCK, &sSet, NULL);
   if (iRet == -1) {perror(pcPgmName); exit(EXIT_FAILURE); }

   /* Install myHandler as the handler for SIGINT signals. */
   pfRet = signal(SIGINT, myHandler);
   if (pfRet == SIG_ERR) {perror(pcPgmName); exit(EXIT_FAILURE); }

   printf("Entering an infinite loop\n");
   iRet = fflush(stdout);
   if (iRet == EOF) {perror(pcPgmName); exit(EXIT_FAILURE); }

   for (;;)
      sleep(1);

   /* Will not reach this point. */
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testsignal.c -o testsignal

$ ./testsignal
Entering an infinite loop
^CIn myHandler with parameter 2
^CIn myHandler with parameter 2
^CIn myHandler with parameter 2
^CIn myHandler with parameter 2
^CIn myHandler with parameter 2
^\Quit

*/

/* Note:  Can use kill command or Ctrl-\ to stop process. */
