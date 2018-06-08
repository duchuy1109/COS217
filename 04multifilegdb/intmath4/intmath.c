/*--------------------------------------------------------------------*/
/* intmath.c (Version 4)                                              */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "intmath.h"
#include <assert.h>

/*--------------------------------------------------------------------*/

int IntMath_gcd(int iFirst, int iSecond)
{
   int iTemp;

   assert(iFirst > 0);
   assert(iSecond > 0);

   /* Use Euclid's algorithm. */

   while (iSecond != 0)
   {
     iTemp = iFirst % iSecond;
     iFirst = iSecond;
     iSecond = iTemp;
   }

   return iFirst;
}

/*--------------------------------------------------------------------*/

int IntMath_lcm(int iFirst, int iSecond)
{
   assert(iFirst > 0);
   assert(iSecond > 0);

   return (iFirst / IntMath_gcd(iFirst, iSecond)) * iSecond;
}
