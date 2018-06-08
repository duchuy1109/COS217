/*--------------------------------------------------------------------*/
/* testdupout.c                                                       */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the creat(), close(), and dup() system-level functions.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. Return 0. */

int main(int argc, char *argv[])
{
   int iFd;
   int iRet;

   /* The permissions of the newly-created file. */
   enum {PERMISSIONS = 0600};

   iFd = creat("tempfile", PERMISSIONS);
   if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = close(1);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = dup(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = close(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   fputs("somedata\n", stdout);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testdupout.c -o testdupout

$ ./testdupout

$ cat tempfile
somedata

*/
