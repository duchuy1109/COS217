/*--------------------------------------------------------------------*/
/* hello.c                                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the system-level getpid() function. Return 0. */

int main(void)
{
   pid_t iPid;
   iPid = getpid();
   printf("%d hello\n", (int)iPid);
   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 hello.c -o hello

$ ./hello
22386 hello

$ ./hello
22387 hello

*/
