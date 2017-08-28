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
 * @brief Libera la memoria solicitada en la inicialización.
 * @param Q     Puntero a la cola.
 */
void fnDestroyQueue( sQueue* Q );

/**
 * @brief Obtiene la siguiente posición a partir de la posición
 *        actual.
 * @param curr  Posición actual.
 * @return      Posición siguiente a partir de posición actual.
 */
int fnNext( int curr );

/**
 * @brief Comprueba si la cola está llena.
 * @param Q     Puntero a la cola.
 * @return      1 si está llena; 0 si no esta llena.
 */
int fnIsFull( sQueue* Q );

/**
 * @brief Comprueba si la cola está vacía.
 * @param Q     Puntero a la cola.
 * @return      1 si está vacía; 0 si no está vacía.
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
