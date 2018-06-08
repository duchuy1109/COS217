/*--------------------------------------------------------------------*/
/* testdupin.c                                                        */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the open(), close, and dup() system-level functions.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments.  Return 0. */

int main(int argc, char *argv[])
{
   enum {BUFFER_LENGTH = 100};
   int iFd;
   int iRet;
   char acBuffer[BUFFER_LENGTH];

   iFd = open("tempfile", O_RDONLY);
   if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = close(0);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = dup(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iRet = close(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   fgets(acBuffer, BUFFER_LENGTH, stdin);

   /* Write the data to verify that the call of fgets worked. */
   fputs(acBuffer, stdout);
   
   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testdupin.c -o testdupin

$ ./testdupin
somedata

*/
