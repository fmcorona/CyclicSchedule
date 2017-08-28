#ifndef FORDFULKERSON_H_INCLUDED
#define FORDFULKERSON_H_INCLUDED

// TODO: MEJORAR
#define MAX 999999;
#define MAX_DEGREE_ADJACENCY_MATRIX 547

int g_residualGraph[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ];

/**
 * @brief Inicializa el grafo residual.
 * @param adjacencyMatrix   Matriz de adyacencia.
 * @param iDegree           Grado de la matriz de adyacencia.
 */
void fnInitResidualGraph( int adjacencyMatrix[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ], int iDegree );

/**
 * @brief Inicializa nodos visitados.
 * @param visited   Puntero a la lista de nodos visitados.
 * @param iDegree   Grado de la matriz de adyacencia (n�mero de nodos).
 */
void fnInitVisited( int* visited, int iDegree );

/**
 * @brief
 * @param parent    Puntero a la lista de nodos padre.
 * @param iDegree   Grado de la matriz de adyacencia (n�mero de nodos).
 * @param iSource   Posici�n del nodo source.
 * @param iSink     Posici�n del nodo sink.
 * @return
 */
int fnBestFirstSearch( int* parent, int iDegree, int iSource, int iSink );

/**
 * @brief Calcula el flujo m�ximo.
 * @param adjacencyMatrix   Matriz de adyacencia.
 * @param iDegree           Grado de la matriz.
 * @return                  Flujo m�ximo.
 */
int fnFordFulkerson( int adjacencyMatrix[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ], int iDegree );

#endif // FORDFULKERSON_H_INCLUDED
