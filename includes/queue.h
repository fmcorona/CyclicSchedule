#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdlib.h>

#define MAX_ELEMENTS 100

typedef struct
{	int data[ MAX_ELEMENTS ];
	int iHead,
		iTail;
} sQueue;

/**
 * @brief Inicializa una cola.
 * @return Puntero a la cola.
 */
sQueue* fnInitQueue( );

/**
 * @brief Libera la memoria solicitada en la inicializaci�n.
 * @param Q     Puntero a la cola.
 */
void fnDestroyQueue( sQueue* Q );

/**
 * @brief Obtiene la siguiente posici�n a partir de la posici�n
 *        actual.
 * @param curr  Posici�n actual.
 * @return      Posici�n siguiente a partir de posici�n actual.
 */
int fnNext( int curr );

/**
 * @brief Comprueba si la cola est� llena.
 * @param Q     Puntero a la cola.
 * @return      1 si est� llena; 0 si no esta llena.
 */
int fnIsFull( sQueue* Q );

/**
 * @brief Comprueba si la cola est� vac�a.
 * @param Q     Puntero a la cola.
 * @return      1 si est� vac�a; 0 si no est� vac�a.
 */
int fnIsEmpty( sQueue* Q );

/**
 * @brief Encola un elemento.
 * @param Q     Puntero a la cola.
 * @param data  Data que se desea encolar.
 * @return      1 si el elemento fue encolado; 0 en otro caso.
 */
int fnEnqueue( sQueue* Q, int data );

/**
 * @brief Desencola el elemento que se encuentra en la cabeza
 *        de la cola.
 * @param Q     Puntero a la cola.
 * @return      Elemento que fue desencolado.
 */
int fnDequeue( sQueue* Q );

#endif // QUEUE_H_INCLUDED
