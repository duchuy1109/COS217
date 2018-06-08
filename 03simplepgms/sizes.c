/*--------------------------------------------------------------------*/
/* sizes.c                                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*  Write the size, in bytes, of each fundamental data type
    to stdout. Return 0. */
    
int main(void)
{
    printf("Bytes per char:            %d\n", 
       (int)sizeof(char));
    printf("Bytes per unsigned char:   %d\n", 
       (int)sizeof(unsigned char));
    printf("Bytes per short:           %d\n",
       (int)sizeof(short));
    printf("Bytes per unsigned short:  %d\n",
       (int)sizeof(unsigned short));
    printf("Bytes per int:             %d\n",
       (int)sizeof(int));
    printf("Bytes per unsigned int:    %d\n",
       (int)sizeof(unsigned int));
    printf("Bytes per long:            %d\n",
       (int)sizeof(long));
    printf("Bytes per unsigned long:   %d\n",
       (int)sizeof(unsigned long));
    printf("Bytes per size_t:          %d\n",
       (int)sizeof(size_t));
    printf("Bytes per float:           %d\n",
       (int)sizeof(float));
    printf("Bytes per double:          %d\n",
       (int)sizeof(double));
    printf("Bytes per long double:     %d\n",
       (int)sizeof(long double));
    printf("Bytes per pointer:         %d\n",
       (int)sizeof(void*));

    return 0;
}

/* Example execution:

$ gcc217 sizes.c -o sizes

$ ./sizes
Bytes per char:            1
Bytes per unsigned char:   1
Bytes per short:           2
Bytes per unsigned short:  2
Bytes per int:             4
Bytes per unsigned int:    4
Bytes per long:            8
Bytes per unsigned long:   8
Bytes per size_t:          8
Bytes per float:           4
Bytes per double:          8
Bytes per long double:     16
Bytes per pointer:         8
*/
