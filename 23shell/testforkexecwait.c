/*--------------------------------------------------------------------*/
/* textforkexecwait.c                                                 */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the common pattern of using the system-level fork(),
   execvp(), and wait() functions. Return 0.
   As usual, argc is the command-line argument count, and argv
   contains the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;

   for (;;)
   {
      iRet = fflush(NULL);
      if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

      iPid = fork();
      if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      if (iPid == 0)
      {
         /* This code is executed by the child process only. */
         char *apcArgv[2];

         apcArgv[0] = "date";
         apcArgv[1] = NULL;

         execvp("date", apcArgv);
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }

      /* This code is executed by the parent process only. */

      /* Wait for the child process to exit. */
      iPid = wait(NULL);
      if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      /* Pause for three seconds. */
      sleep(3);
   }

   /* Should not reach this point. */
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testforkexecwait.c -o testforkexecwait

$ ./testforkexecwait
Wed Apr 26 16:37:52 EDT 2017
Wed Apr 26 16:37:55 EDT 2017
Wed Apr 26 16:37:58 EDT 2017
Wed Apr 26 16:38:01 EDT 2017
Wed Apr 26 16:38:04 EDT 2017
Wed Apr 26 16:38:07 EDT 2017
Wed Apr 26 16:38:10 EDT 2017
Wed Apr 26 16:38:13 EDT 2017
Wed Apr 26 16:38:16 EDT 2017
Wed Apr 26 16:38:19 EDT 2017
Wed Apr 26 16:38:22 EDT 2017
^C

*/
