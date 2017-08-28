#include "../includes/mathfunctions.h"

/**********************************************************
 *                 FUNCTIONS FOR STEP 1                   *
 **********************************************************
 *               FUNCIONES PARA EL PASO 1                 *
 **********************************************************/

int fnAbs( int x )
{
    if ( x < 0 )
        return -x;

    return x;
}

int fnMax( int a, int b )
{
    if ( a > b )
        return a;

    return b;
}

int fnMin( int a, int b )
{
    if ( a < b )
        return a;

    return b;
}

int fnGCD( int a, int b )
{
    int iRemainder, iMax, iMin;

    iMax = fnMax( fnAbs( a ), fnAbs( b ) );
    iMin = fnMin( fnAbs( a ), fnAbs( b ) );

    /* GCD(a, 0) = a
     */
    if ( iMin == 0 )
        return iMax;

    iRemainder = iMax % iMin;

    /* GCD( a, b ) = GCD( b, r  ),
     * donde, a > b y a = b * q + r
     */
    while ( iRemainder != 0 )
    {
        iMax = iMin;
        iMin = iRemainder;

        iRemainder = iMax % iMin;
    }

    return iMin;
}

int fnLCM( int a, int b )
{
    int iMin, iMax;

    iMin = fnMin( fnAbs( a ), fnAbs( b ) );
    iMax = fnMax( fnAbs( a ), fnAbs( b ) );

    /* LCM( a, b ) = a * b / GCD( a, b )
     *
     * Encontramos primero el número mayor y menor.
     * Y dividimos el número mayor por el GCD antes
     * de multiplicar con el número menor, para evitar
     * un posible desbordamiento.
     */
    return ( iMax / fnGCD( a, b ) ) * iMin ;
}

//TODO: Implementar con listas ligadas y hacerlo iterativo
int fnLCMOfAList( int *numberList, int first, int listSize)
{
    if ( listSize == 2 )
        return fnLCM( numberList[ first ], numberList[ first + 1 ] );

    return fnLCM( numberList[ first ], fnLCMOfAList( numberList, first + 1, listSize - 1 ) );
}

/**********************************************************
 *                  FUNCTION FOR STEP 3                   *
 **********************************************************
 *                 FUNCIÓN PARA EL PASO 3                 *
 **********************************************************/

int fnMaxInAList(int *numberList, int listSize)
{
    int i, iMax;
    iMax = numberList[0];

    for ( i = 1; i < listSize; i++)
    {
        if ( iMax < numberList[i] )
            iMax = numberList[i];
    }

    return iMax;
}
