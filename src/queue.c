#include "../includes/queue.h"

sQueue* fnInitQueue( )
{
    sQueue* Q = ( sQueue* ) malloc( sizeof( sQueue ) ) ;

	Q -> iHead = 0;
	Q -> iTail = MAX_ELEMENTS - 1;

	return Q;
}

void fnDestroyQueue( sQueue* Q )
{
    free( Q );
}

int fnNext( int curr )
{
	return ( curr + 1 ) % MAX_ELEMENTS;
}

int fnIsEmpty( sQueue* Q )
{
	if ( Q -> iHead == fnNext( Q -> iTail ) )
		return 1;

	return 0;
}

int fnIsFull( sQueue* Q )
{
    // Hay un espacio que no se usa, por eso se compara la
    // cabeza con el siguiente del siguiente de la cola.
	if ( Q -> iHead == fnNext( fnNext( Q -> iTail ) ) )
		return 1;

	return 0;
}

int fnEnqueue( sQueue* Q, int data )
{
	if ( !fnIsFull( Q ) )
	{
		Q -> iTail = fnNext( Q -> iTail );
		Q -> data [ Q -> iTail ] = data;

		return 1;
	}

	// TODO: MEJORAR
    return 0;
}

int fnDequeue( sQueue* Q )
{
	int iTmp;

	if ( !fnIsEmpty( Q ) )
	{
		iTmp = Q -> data[ Q -> iHead ];
		Q -> iHead = fnNext( Q -> iHead );

		return iTmp;
	}

	//TODO: MEJORAR
	// Considerando -1 como un valor inválido
	return -1;
}
