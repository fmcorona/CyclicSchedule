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
int g_setOfFS[ 100 ];       // Arreglo de tama�os de frames
extern int g_iSizeOfSetFS;  // Tama�o del arreglo de tama�os de frames

// TODO: Construir el grafo de flujo de red con una lista ligada
int g_adjacencyMatrix[ MAX_DEGREE_ADJACENCY_MATRIX ][ MAX_DEGREE_ADJACENCY_MATRIX ];

/**********************************************************
 *              FUNCTION TO INITIALIZE TASKS              *
 **********************************************************
 *          FUNCI�N PARA INICIALIZAR LAS TAREAS           *
 **********************************************************/
void fnInitTasks( sPeriodicTask *task, int iNumOfTasks );

/**********************************************************
 *                  FUNCTION FOR STEP 1                   *
 *         Function to calculate the hyperperiod          *
 **********************************************************
 *                 FUNCI�N PARA EL PASO 1                 *
 *         Funci�n para calcular el hiperperiodo          *
 **********************************************************/

/**
 * @brief Calcula el hiperperiodo.
 *        El hiperperiodo, H, es el m�nimo com�n m�ltiplo del per�odo,
 *        pi, de todas las tareas, es decir
 *                      H = LCM(p1, p2, ..., pn)
 * @param task          Arreglo de tareas peri�dicas.
 * @param numOfTasks    N�mero de tareas.
 * @return              El hiperperiodo.
 */
int fnHyperperiod( sPeriodicTask *task, int numOfTasks );

/**********************************************************
 *                 FUNCTIONS FOR STEP 2                   *
 *   Functions to calculate the number of jobs per task   *
 **********************************************************
 *               FUNCIONES PARA EL PASO 2                 *
 *Funciones para calcular el n�mero de trabajos por tarea *
 **********************************************************/

/**
 * @brief Calcula el n�mero total de jobs, para una tarea.
 *        Para una tare Ti, el n�mero de jobs, es igual a
 *                          H / pi
 * @param hyperperiod   Hiperperiodo.
 * @param period        Per�odo de la tarea.
 * @return              N�mero de jobs de para la tarea.
 */
int fnGetJobs( int hyperperiod, int period );

/**
 * @brief Calcula el n�mero de jobs para cada una de las tareas, Ti.
 * @param task          Areglo de tareas peri�dicas.
 * @param hyperperiod   Hiperperiodo.
 * @param numOfTasks    N�mero de tareas.
 */
void fnFindJobs( sPeriodicTask *task, int hyperperiod, int numOfTasks );

/**********************************************************
*                 FUNCTIONS FOR STEP 3                    *
*     Functions to calculate the possible frame sizes     *
***********************************************************
*               FUNCIONES PARA EL PASO 3                  *
* Funciones para calcular los posibles tama�os de frames  *
**********************************************************/

// Frame-size constraints.
/**
 * @brief CONDICI�N 1:
 *        El tama�o de frame, f, tiene que ser mayor que el tiempo de
 *        ejecuci�n, ei, de cada tarea Ti, i.e.,
 *                      f >= max( e1, e2,..., en )
 *        donde, n es el n�mero de tareas.
 * @param task          Arreglo de tareas peri�dicas.
 * @param numOfTasks    N�mero de tareas.
 */
int fnFrameSizeCond1( sPeriodicTask *task, int numOfTasks );

/**
 * @brief CONDICI�N 2:
 *        El tama�o del frame, f, debe divir al periodo, pi,
 *        de al menos una de las tareas.
 * @param frameSize     Posible tama�o de frame.
 * @param period        Per�odo
 * @return              1 si el tama�o de frame, frameSize, cumple la
 *                      condici�n; 0 en caso contrario.
 */
int fnFrameSizeCond2( int frameSize, int period );

/**
 * @brief CONDICI�N 3:
 *        Para toda i = 1, 2, ..., n, donde n es el n�mero de tareas,
 *        se debe de cumplir, para cada tarea, que:
 *                          2f - gcd( pi, f ) <= Di
 *        donde,
 *               f  es el tama�o del frame (frame size)
 *               pi es el per�odo (period) de la i-�sima tarea
 *               Di es el plazo (deadline) de la i-�sima tarea.
 * @param frameSize     Tama�o de frame.
 * @param task          Arreglo de tareas per�odicas.
 * @param numOfTasks    N�mero de tareas.
 * @return              1 si se cumple la condici�n; 0 en caso contrario.
 */
int fnFrameSizeCond3( int frameSize, sPeriodicTask *task, int numOfTasks );

/**
 * @brief Verifica si un elemento est� en el conjunto de todos los posibles
 *        tama�os de frame.
 * @param element   Un tama�o de frame.
 * @return          1 si element ya est� en el conjuto de todos los posibles
 *                  tama�os de frame;
 *                  0 en caso contrario.
 */
int fnIsInSetOfFS( int element );

/**
 * @brief A�ade un elemento, en orden,  al conjunto de todos los posibles
 *        tama�os de frame.
 * @param frameSize     Tama�o de frame.
 */
void fnAddToSetOfFS( int frameSize );

/**
 * @brief Remueve un elemento del conjunto de todos los posibles tama�os de frame.
 * @param index     �ndice del elemento.
 */
void fnRemoveToSetOfFS( int index );

/**
 * @brief Encuentra todos los factores de num mayores o iguales que greatOrEqual y
 *        los agrega al conjunto de posibles tama�os de frame.
 * @param num           N�mero del cual se quieren encontrar todos sus factores.
 * @param greatOrEqual  N�mero a partir del cual se van a buscar los factores de num.
 */
void fnFindFactorsGEq( int num, int greatOrEqual );

/**
 * @brief Encuentra todos los posibles tama�os de frames y los agrega, indirectamente,
 *        al conjunto de todos los posibles tama�os de frame.
 * @param task              Arreglo de tareas per�odicas.
 * @param numOfTasks        N�mero de Tareas.
 * @param smallerFrameSize  Tama�o de frame m�s peque�o.
 */
void fnFindPossibleFS( sPeriodicTask *task, int numOfTasks, int smallerFrameSize );

/**
 * @brief Encuentra todos los tama�os de frame que cumplen con las condici�n 3.
 * @param task          Arreglo de tareas per�odicas.
 * @param numOfTasks    N�mero de tareas.
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
 * @brief Calcula el n�mero de total de frames en el hiperperiodo para
 *        un tama�o de frame dado.
 * @param iHyperperiod  Hiperperiodo
 * @param iFrameSize    Tama�o de frame.
 * @return              N�mero total de frames en el hiperperiodo.
 */
int fnGetNumberOfFrames( int iHyperperiod, int iFrameSize );

/**
 * @brief Calcula el n�mero total de jobs que se realizan en un hiperperiodo.
 * @param task          Arreglo de tareas per�odicas.
 * @param iNumOfTasks   N�mero de tareas.
 * @return              N�mero total de jobs que se realizan en un hiperperiodo.
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
 *        con el tiempo de ejecuci�n del correspondiente job.
 *
 *        2) Para cada frame hay un nodo; y de cado uno de esos nodos hay
 *        una arista al nodo sumidero (sink), nodo destino, etiquetada
 *        con el tama�o del frame.
 *
 *
 *        3) Hay una arista del nodo job J al nodo frame f, si:
 *              start frame f >= arrival job J
 *        y
 *               end frame f <= deadline job J
 * @param task          Arreglo de tareas per�odicas.
 * @param iNumOfTasks   N�mero de tareas.
 * @param iNumOfJobs    N�mero de jobs que se pueden realizar en un hiperperiodo.
 * @param iNumOfFrames  N�mero de frames de frames en un hiperperiodo.
 * @param iFrameSize    Tama�o de frame.
 */
void fnFillAdjacencyMatrix( sPeriodicTask *task, int iNumOfTasks, int iNumOfJobs, int iNumOfFrames, int iFrameSize );

/**
 * @brief Construyen la tabla de posibles tama�os de frame.
 * @param frame         Arreglo que contiene el inicio y final de cada frame.
 * @param iNumOfFrames  N�mero de posibles tama�os de frame.
 * @param iFrameSize    Tama�o de frame
 */
void fnMakeFrameTable( sFrame* frame, int iNumOfFrames, int iFrameSize );

/**
 * @brief Construye la tabla de jobs
 * @param tasks         Arreglo de tareas per�odicas.
 * @param job           Arreglo que contiene la llegada y el plazo de cada job.
 * @param iNumOfTasks   N�mero de tareas.
 */
void fnMakeJobTable( sPeriodicTask* tasks, sJob* job, int iNumOfTasks );

#endif // CYCLICSCHEDULE_H_INCLUDED
