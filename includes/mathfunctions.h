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
 * @param x Número del cual se desea calcular su valor absoluto.
 * @return  Valor absoluto de x.
 */
int fnAbs( int x );

/**
 * @brief Encuentra el máximo de dos números.
 * @param a Primer número.
 * @param b Segundo número.
 * @return  Número mayor.
 */
int fnMax( int a, int b );

/**
 * @brief Encuentra el mínimo de dos número.
 * @param a Primero número.
 * @param b Segundo número.
 * @return  Número menor.
 */
int fnMin( int a, int b );

/**
 * @brief Calcula el máximo común divisor de dos números.
 * @param a Primer número.
 * @param b Segundo número.
 * @return  Máximo común divisor.
 */
int fnGCD( int a, int b );

/**
 * @brief Calcula el mínimo común múltiplo de dos números.
 * @param a Primer número.
 * @param b Segundo número.
 * @return  Mínimo común múltiplo.
 */
int fnLCM( int a, int b );

/**
 * @brief Calcula el mínimo común múltiplo de una lista de números.
 * @param numberList    Puntero al primer elemento de la lista.
 * @param first         Posición del primer número de la lista.
 * @param listSize      Tamaño de la lista.
 * @return              Mínimo común múltiplo.
 */
int fnLCMOfAList( int *numberList, int first, int listSize);

/**********************************************************
 *                  FUNCTION FOR STEP 3                   *
 *      Necessary function for calculate the possible     *
 *                      frame sizes                       *
 **********************************************************
 *                 FUNCIÓN PARA EL PASO 3                 *
 *   Función necesaria para calcular los posibles frames  *
 **********************************************************/

/**
 * @brief Encuentra el máximo valor de una lista de números.
 * @param numberList    Puntero al primero elemento de la lista.
 * @param listSize      Tamaño de la lista.
 * @return              Número mayor.
 */
int fnMaxInAList(int *numberList, int listSize);

#endif // MATHFUNCTIONS_H_INCLUDED
