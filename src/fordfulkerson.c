#include "../includes/fordfulkerson.h"
#include "../includes/mathfunctions.h"
#include "../includes/queue.h"

void fnInitResidualGraph( int adjacencyMatrix[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ], int iDegree )
{
    int i, j;

    for ( i = 0; i < iDegree; i++ )
        for ( j = 0; j < iDegree; j++ )
            g_residualGraph[ i ][ j ] = adjacencyMatrix[ i ][ j ];
}

void fnInitVisited( int* visited, int iDegree )
{
    int i;

    for ( i = 0; i < iDegree; i++ )
        visited[ i ] = 0 ;
}

int fnBestFirstSearch(int* parent, int iDegree, int iSource, int iSink )
{
    int visited[ iDegree ],
        iVertexU,
        i;
    sQueue* Q;

    fnInitVisited( visited, iDegree );
    Q = fnInitQueue( );

    fnEnqueue( Q, iSource );

    visited[ iSource ] = 1;
    parent[ iSource ] = -1; // No tiene padre, es el nodo inicial

    while ( !fnIsEmpty( Q ) )
    {
        iVertexU = fnDequeue( Q );

        for ( i = 0; i < iDegree; i++ )
        {
            if ( visited[ i ] == 0 && g_residualGraph[ iVertexU ][ i ] > 0 )
            {
                fnEnqueue( Q, i );

                parent[ i ] = iVertexU;
                visited[ i ] = 1;
            }
        }
    }

    return visited[ iSink ] == 1;
}

/* Suponemos que el nodo source y el nodo sink siempre están en
 * la posición 0 y iDegree - 1, respectivamente.
 */
int fnFordFulkerson( int adjacencyMatrix[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ], int iDegree )
{
    int parent[ iDegree ],
        iSource = 0,
        iSink = iDegree - 1,
        iMaxFlow = 0,
        iPathFlow,
        iVertexU,
        iVertexV;

    fnInitResidualGraph( adjacencyMatrix, iDegree );

    while( fnBestFirstSearch( parent, iDegree, iSource, iSink ) )
    {
        iPathFlow = MAX;
        iVertexV = iSink;

        while ( iVertexV != iSource )
        {
            iVertexU = parent[ iVertexV ];
            iPathFlow = fnMin( iPathFlow, g_residualGraph[ iVertexU ][ iVertexV ] );

            iVertexV = parent[ iVertexV ];
        }

        iVertexV = iSink;

        while ( iVertexV != iSource )
        {
            iVertexU = parent[ iVertexV ];

            g_residualGraph[ iVertexU ][ iVertexV ] -= iPathFlow;
            g_residualGraph[ iVertexV ][ iVertexU ] += iPathFlow;

            iVertexV = parent[ iVertexV ];
        }

        iMaxFlow += iPathFlow;
    }

    return iMaxFlow;
}
