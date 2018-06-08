/*--------------------------------------------------------------------*/
/* formattedio.c                                                      */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Read from stdin, and write to stdout, one literal of each
   fundamental data type.  Ignore the possibility of bad input.
   Return 0. */

int main(void)
{
    int iTypical;
    unsigned int uiTypical;
    long lTypical;
    unsigned long ulTypical;
    short sTypical;
    unsigned short usTypical;
    char cTypical;
    unsigned char ucTypical;
    double dTypical;
    float fTypical;
    long double ldTypical;

    /*----------------------------------------------------------------*/
    /* char                                                           */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type char:\n");
    /* Place a space before %c to skip leading whitespace
       characters. Do not place a space before %c to read
       whitespace characters. */
    scanf(" %c", &cTypical);

    printf("You entered %c.\n", (int)cTypical);

    /*----------------------------------------------------------------*/
    /* unsigned char                                                  */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type unsigned char:\n");
    scanf(" %c", &ucTypical);

    printf("You entered %c.\n", (unsigned int)ucTypical);

    /*----------------------------------------------------------------*/
    /* short                                                          */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type short:\n");
    scanf("%hd", &sTypical);

    printf("You entered %hd.\n", sTypical);

    /*----------------------------------------------------------------*/
    /* unsigned short                                                 */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type unsigned short:\n");
    scanf("%hu", &usTypical);

    printf("You entered %hu.\n", usTypical);

    /*----------------------------------------------------------------*/
    /* int                                                            */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type int:\n");
    scanf("%d", &iTypical);

    printf("You entered %d.\n", iTypical);

    /*----------------------------------------------------------------*/
    /* unsigned int                                                   */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type unsigned int:\n");
    scanf("%u", &uiTypical);

    printf("You entered %u.\n", uiTypical);

    /*----------------------------------------------------------------*/
    /* long                                                           */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type long:\n");
    scanf("%ld", &lTypical);

    printf("You entered %ld.\n", lTypical);

    /*----------------------------------------------------------------*/
    /* unsigned long                                                  */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type unsigned long:\n");
    scanf("%lu", &ulTypical);

    printf("You entered %lu.\n", ulTypical);

    /*----------------------------------------------------------------*/
    /* float                                                          */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type float:\n");
    scanf("%f", &fTypical);  /* %e or %g work identically.  */

    printf("You entered %f.\n", (double)fTypical);
    printf("You entered %e.\n", (double)fTypical);
    printf("You entered %E.\n", (double)fTypical);
    printf("You entered %g.\n", (double)fTypical);
    printf("You entered %G.\n", (double)fTypical);

    /*----------------------------------------------------------------*/
    /* double                                                         */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type double:\n");
    scanf("%lf", &dTypical);  /* %le or %lg work identically.  */

    /* Note the assymmetry of the following with scanf().  */
    printf("You entered %f.\n", dTypical);
    printf("You entered %e.\n", dTypical);
    printf("You entered %E.\n", dTypical);
    printf("You entered %g.\n", dTypical);
    printf("You entered %G.\n", dTypical);

    /*----------------------------------------------------------------*/
    /* long double                                                    */
    /*----------------------------------------------------------------*/

    printf("\n");
    printf("Enter a constant of type long double:\n");
    scanf("%Lf", &ldTypical);  /* %Le or %Lg work identically.  */

    printf("You entered %Lf.\n", ldTypical);
    printf("You entered %Le.\n", ldTypical);
    printf("You entered %LE.\n", ldTypical);
    printf("You entered %Lg.\n", ldTypical);
    printf("You entered %LG.\n", ldTypical);

    return 0;
}
