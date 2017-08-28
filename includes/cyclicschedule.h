#ifndef CYCLICSCHEDULE_H_INCLUDED
#define CYCLICSCHEDULE_H_INCLUDED

#define MAX_TASKS 10
#define MAX_DEGREE_ADJACENCY_MATRIX 547

typedef struct
{
    int period,
        executionTime,
        deadline,
        jobs;
} sPeriodicTask;

typedef struct
{
    int iStart,
        iEnd;
} sFrame;

typedef struct
{
    int iArrival,
        iDeadline;
} sJob;

// TODO: Implementar con una lista ligada
int g_setOfFS[ 100 ];       // Arreglo de tamaños de frames
extern int g_iSizeOfSetFS;  // Tamaño del arreglo de tamaños de frames

// TODO: Construir el grafo de flujo de red con una lista ligada
int g_adjacencyMatrix[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ];

/**********************************************************
 *              FUNCTION TO INITIALIZE TASKS              *
 **********************************************************
 *          FUNCIÓN PARA INICIALIZAR LAS TAREAS           *
 **********************************************************/
void fnInitTasks( sPeriodicTask *task, int iNumOfTasks );

/**********************************************************
 *                  FUNCTION FOR STEP 1                   *
 *         Function to calculate the hyperperiod          *
 **********************************************************
 *                 FUNCIÓN PARA EL PASO 1                 *
 *         Función para calcular el hiperperiodo          *
 **********************************************************/

/**
 * @brief Calcula el hiperperiodo.
 *        El hiperperiodo, H, es el mínimo común múltiplo del período,
 *        pi, de todas las tareas, es decir
 *                      H = LCM(p1, p2, ..., pn)
 * @param task          Arreglo de tareas periódicas.
 * @param numOfTasks    Número de tareas.
 * @return              El hiperperiodo.
 */
int fnHyperperiod( sPeriodicTask *task, int numOfTasks );

/**********************************************************
 *                 FUNCTIONS FOR STEP 2                   *
 *   Functions to calculate the number of jobs per task   *
 **********************************************************
 *               FUNCIONES PARA EL PASO 2                 *
 *Funciones para calcular el número de trabajos por tarea *
 **********************************************************/

/**
 * @brief Calcula el número total de jobs, para una tarea.
 *        Para una tare Ti, el número de jobs, es igual a
 *                          H / pi
 * @param hyperperiod   Hiperperiodo.
 * @param period        Período de la tarea.
 * @return              Número de jobs de para la tarea.
 */
int fnGetJobs( int hyperperiod, int period );

/**
 * @brief Calcula el número de jobs para cada una de las tareas, Ti.
 * @param task          Areglo de tareas periódicas.
 * @param hyperperiod   Hiperperiodo.
 * @param numOfTasks    Número de tareas.
 */
void fnFindJobs( sPeriodicTask *task, int hyperperiod, int numOfTasks );

/**********************************************************
*                 FUNCTIONS FOR STEP 3                    *
*     Functions to calculate the possible frame sizes     *
***********************************************************
*               FUNCIONES PARA EL PASO 3                  *
* Funciones para calcular los posibles tamaños de frames  *
**********************************************************/

// Frame-size constraints.
/**
 * @brief CONDICIÓN 1:
 *        El tamaño de frame, f, tiene que ser mayor que el tiempo de
 *        ejecución, ei, de cada tarea Ti, i.e.,
 *                      f >= max( e1, e2,..., en )
 *        donde, n es el número de tareas.
 * @param task          Arreglo de tareas periódicas.
 * @param numOfTasks    Número de tareas.
 */
int fnFrameSizeCond1( sPeriodicTask *task, int numOfTasks );

/**
 * @brief CONDICIÓN 2:
 *        El tamaño del frame, f, debe divir al periodo, pi,
 *        de al menos una de las tareas.
 * @param frameSize     Posible tamaño de frame.
 * @param period        Período
 * @return              1 si el tamaño de frame, frameSize, cumple la
 *                      condición; 0 en caso contrario.
 */
int fnFrameSizeCond2( int frameSize, int period );

/**
 * @brief CONDICIÓN 3:
 *        Para toda i = 1, 2, ..., n, donde n es el número de tareas,
 *        se debe de cumplir, para cada tarea, que:
 *                          2f - gcd( pi, f ) <= Di
 *        donde,
 *               f  es el tamaño del frame (frame size)
 *               pi es el período (period) de la i-ésima tarea
 *               Di es el plazo (deadline) de la i-ésima tarea.
 * @param frameSize     Tamaño de frame.
 * @param task          Arreglo de tareas períodicas.
 * @param numOfTasks    Número de tareas.
 * @return              1 si se cumple la condición; 0 en caso contrario.
 */
int fnFrameSizeCond3( int frameSize, sPeriodicTask *task, int numOfTasks );

/**
 * @brief Verifica si un elemento está en el conjunto de todos los posibles
 *        tamaños de frame.
 * @param element   Un tamaño de frame.
 * @return          1 si element ya está en el conjuto de todos los posibles
 *                  tamaños de frame;
 *                  0 en caso contrario.
 */
int fnIsInSetOfFS( int element );

/**
 * @brief Añade un elemento, en orden,  al conjunto de todos los posibles
 *        tamaños de frame.
 * @param frameSize     Tamaño de frame.
 */
void fnAddToSetOfFS( int frameSize );

/**
 * @brief Remueve un elemento del conjunto de todos los posibles tamaños de frame.
 * @param index     Índice del elemento.
 */
void fnRemoveToSetOfFS( int index );

/**
 * @brief Encuentra todos los factores de num mayores o iguales que greatOrEqual y
 *        los agrega al conjunto de posibles tamaños de frame.
 * @param num           Número del cual se quieren encontrar todos sus factores.
 * @param greatOrEqual  Número a partir del cual se van a buscar los factores de num.
 */
void fnFindFactorsGEq( int num, int greatOrEqual );

/**
 * @brief Encuentra todos los posibles tamaños de frames y los agrega, indirectamente,
 *        al conjunto de todos los posibles tamaños de frame.
 * @param task              Arreglo de tareas períodicas.
 * @param numOfTasks        Número de Tareas.
 * @param smallerFrameSize  Tamaño de frame más pequeño.
 */
void fnFindPossibleFS( sPeriodicTask *task, int numOfTasks, int smallerFrameSize );

/**
 * @brief Encuentra todos los tamaños de frame que cumplen con las condición 3.
 * @param task          Arreglo de tareas períodicas.
 * @param numOfTasks    Número de tareas.
 */
void fnFindFSWithFSConstrains( sPeriodicTask *task, int numOfTasks );

/**********************************************************
 *                 FUNCTIONS FOR STEP 4                   *
 *                                                        *
 **********************************************************
 *               FUNCIONES PARA EL PASO 4                 *
 *          Construir un grafo de flujo de red            *
 **********************************************************/

/**
 * @brief Calcula el número de total de frames en el hiperperiodo para
 *        un tamaño de frame dado.
 * @param iHyperperiod  Hiperperiodo
 * @param iFrameSize    Tamaño de frame.
 * @return              Número total de frames en el hiperperiodo.
 */
int fnGetNumberOfFrames( int iHyperperiod, int iFrameSize );

/**
 * @brief Calcula el número total de jobs que se realizan en un hiperperiodo.
 * @param task          Arreglo de tareas períodicas.
 * @param iNumOfTasks   Número de tareas.
 * @return              Número total de jobs que se realizan en un hiperperiodo.
 */
int fnGetNumberOfJobs( sPeriodicTask *task, int iNumOfTasks );

/**
 * @brief Inicializa la matriz de adyacencia.
 * @param iDegree   Grado de la matriz de adyacencia.
 */
void fnInitAdjacencyMatrix( int iDegree );

/**
 * @brief Construye la matriz de adyacencia, de acuerdo a las siguiente reglas:
 *        1) Del nodo fuente (source) hay una arista a cada nodo job, etiquetada
 *        con el tiempo de ejecución del correspondiente job.
 *
 *        2) Para cada frame hay un nodo; y de cado uno de esos nodos hay
 *        una arista al nodo sumidero (sink), nodo destino, etiquetada
 *        con el tamaño del frame.
 *
 *
 *        3) Hay una arista del nodo job J al nodo frame f, si:
 *              start frame f >= arrival job J
 *        y
 *               end frame f <= deadline job J
 * @param task          Arreglo de tareas períodicas.
 * @param iNumOfTasks   Número de tareas.
 * @param iNumOfJobs    Número de jobs que se pueden realizar en un hiperperiodo.
 * @param iNumOfFrames  Número de frames de frames en un hiperperiodo.
 * @param iFrameSize    Tamaño de frame.
 */
void fnFillAdjacencyMatrix( sPeriodicTask *task, int iNumOfTasks, int iNumOfJobs, int iNumOfFrames, int iFrameSize );

/**
 * @brief Construyen la tabla de posibles tamaños de frame.
 * @param frame         Arreglo que contiene el inicio y final de cada frame.
 * @param iNumOfFrames  Número de posibles tamaños de frame.
 * @param iFrameSize    Tamaño de frame
 */
void fnMakeFrameTable( sFrame* frame, int iNumOfFrames, int iFrameSize );

/**
 * @brief Construye la tabla de jobs
 * @param tasks         Arreglo de tareas períodicas.
 * @param job           Arreglo que contiene la llegada y el plazo de cada job.
 * @param iNumOfTasks   Número de tareas.
 */
void fnMakeJobTable( sPeriodicTask* tasks, sJob* job, int iNumOfTasks );

#endif // CYCLICSCHEDULE_H_INCLUDED
