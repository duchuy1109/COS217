/*--------------------------------------------------------------------*/
/* testlowlevelout.c                                                  */
/* Author: Bob Dondero                                                */
/* The creat, write, and close system calls.                          */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the creat(), write(), and close() system-level functions.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. Return 0. */

int main(int argc, char *argv[])
{
   int iFd;
   int iRet;
   ssize_t lByteCount;
   char *pcBuffer = "somedata\n";

   /* The permissions of the newly-created file. */
   enum {PERMISSIONS = 0600};

   /* Write "somedata\n" to a file named tempfile. */

   iFd = creat("tempfile", PERMISSIONS);
   if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   lByteCount = write(iFd, pcBuffer, strlen(pcBuffer));
   if (lByteCount == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = close(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testlowlevelout.c -o testlowlevelout

$ ./testlowlevelout

$ cat tempfile
somedata

*/
