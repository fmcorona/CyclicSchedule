#ifndef MATHFUNCTIONS_H_INCLUDED
#define MATHFUNCTIONS_H_INCLUDED

/**********************************************************
 *                 FUNCTIONS FOR STEP 1                   *
 *   Necessary functions for calculate the hyperperiod    *
 **********************************************************
 *               FUNCIONES PARA EL PASO 1                 *
 *   Funciones necesarias para calcular el hiperperiodo   *
 **********************************************************/

/**
 * @brief Calcula el valor absoluto.
 * @param x N�mero del cual se desea calcular su valor absoluto.
 * @return  Valor absoluto de x.
 */
int fnAbs( int x );

/**
 * @brief Encuentra el m�ximo de dos n�meros.
 * @param a Primer n�mero.
 * @param b Segundo n�mero.
 * @return  N�mero mayor.
 */
int fnMax( int a, int b );

/**
 * @brief Encuentra el m�nimo de dos n�mero.
 * @param a Primero n�mero.
 * @param b Segundo n�mero.
 * @return  N�mero menor.
 */
int fnMin( int a, int b );

/**
 * @brief Calcula el m�ximo com�n divisor de dos n�meros.
 * @param a Primer n�mero.
 * @param b Segundo n�mero.
 * @return  M�ximo com�n divisor.
 */
int fnGCD( int a, int b );

/**
 * @brief Calcula el m�nimo com�n m�ltiplo de dos n�meros.
 * @param a Primer n�mero.
 * @param b Segundo n�mero.
 * @return  M�nimo com�n m�ltiplo.
 */
int fnLCM( int a, int b );

/**
 * @brief Calcula el m�nimo com�n m�ltiplo de una lista de n�meros.
 * @param numberList    Puntero al primer elemento de la lista.
 * @param first         Posici�n del primer n�mero de la lista.
 * @param listSize      Tama�o de la lista.
 * @return              M�nimo com�n m�ltiplo.
 */
int fnLCMOfAList( int *numberList, int first, int listSize);

/**********************************************************
 *                  FUNCTION FOR STEP 3                   *
 *      Necessary function for calculate the possible     *
 *                      frame sizes                       *
 **********************************************************
 *                 FUNCI�N PARA EL PASO 3                 *
 *   Funci�n necesaria para calcular los posibles frames  *
 **********************************************************/

/**
 * @brief Encuentra el m�ximo valor de una lista de n�meros.
 * @param numberList    Puntero al primero elemento de la lista.
 * @param listSize      Tama�o de la lista.
 * @return              N�mero mayor.
 */
int fnMaxInAList(int *numberList, int listSize);

#endif // MATHFUNCTIONS_H_INCLUDED
