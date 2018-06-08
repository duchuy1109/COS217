/*--------------------------------------------------------------------*/
/* testlowlevelin.c                                                   */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the open(), read(), and close() system-level functions.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. Return 0. */

int main(int argc, char *argv[])
{
   enum {BYTE_COUNT = 9};

   int iFd;
   int iRet;
   char acBuffer[BYTE_COUNT];
   int i;
   ssize_t lByteCount;
   
   /* Read "somedata\n" from a file named tempfile. */

   iFd = open("tempfile", O_RDONLY);
   if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   lByteCount = read(iFd, acBuffer, BYTE_COUNT);
   if (lByteCount == -1) {perror(argv[0]); exit(EXIT_FAILURE);}

   iRet = close(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Write the data to verify that the previous worked. */

   for (i = 0; i < BYTE_COUNT; i++)
      putchar(acBuffer[i]);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testlowlevelin.c -o testlowlevelin

$ ./testlowlevelin
somedata

*/
