#include <stdio.h>
#include "../includes/cyclicschedule.h"
#include "../includes/mathfunctions.h"

int g_iSizeOfSetFS = 0;

/**********************************************************
 *              FUNCTION TO INITIALIZE TASKS              *
 **********************************************************
 *          FUNCIÓN PARA INICIALIZAR LAS TAREAS           *
 **********************************************************/

void fnInitTasks( sPeriodicTask *task, int iNumOfTasks )
{
    int i;

    for( i = 0; i < iNumOfTasks; i++ )
    {
        printf( "\n  Task %d:\n\n", i + 1 );
        printf( "   Period: " );
        scanf( "%d", &task[ i ].period );

        printf( "   Execution time: " );
        scanf( "%d", &task[ i ].executionTime );

        printf( "   Deadline: " );
        scanf( "%d", &task[ i ].deadline );
    }
}

/**********************************************************
 *                  FUNCTION FOR STEP 1                   *
 **********************************************************
 *                 FUNCIÓN PARA EL PASO 1                 *
 **********************************************************/

int fnHyperperiod( sPeriodicTask *task, int numOfTasks )
{
    int numberList[ numOfTasks ], i;

    for ( i = 0; i < numOfTasks; i++ )
        numberList[ i ] = task[ i ].period;

    return fnLCMOfAList( numberList, 0, numOfTasks );
}

/**********************************************************
 *                 FUNCTIONS FOR STEP 2                   *
 **********************************************************
 *               FUNCIONES PARA EL PASO 2                 *
 **********************************************************/

int fnGetJobs( int hyperperiod, int period )
{
    return hyperperiod / period;
}

void fnFindJobs( sPeriodicTask *task, int hyperperiod, int numOfTasks )
{
    int i;

    for ( i = 0; i < numOfTasks; i++ )
        task[i].jobs = fnGetJobs( hyperperiod, task[i].period );
}

/**********************************************************
 *                 FUNCTIONS FOR STEP 3                   *
 **********************************************************
 *               FUNCIONES PARA EL PASO 3                 *
 **********************************************************/

int fnFrameSizeCond1( sPeriodicTask *task, int numOfTasks )
{
    int i, listOfExeTime[ numOfTasks ];

    for ( i = 0; i < numOfTasks; i++ )
        listOfExeTime[ i ] = task[ i ].executionTime;

    return fnMaxInAList( listOfExeTime, numOfTasks );
}

int fnFrameSizeCond2( int frameSize, int period )
{
    if ( period % frameSize == 0 )
        return 1;

    return 0;
}

int fnFrameSizeCond3( int frameSize, sPeriodicTask *task, int numOfTasks )
{
    int i;

    for ( i = 0; i < numOfTasks; i++ )
    {
        if ( 2 * frameSize - fnGCD( task[ i ].period, frameSize ) > task[ i ].deadline )
            return 0;
    }

    return 1;
}

int fnIsInSetOfFS( int element )
{
    int i;

    for ( i = 0; i < g_iSizeOfSetFS; i++ )
    {
        if ( g_setOfFS[ i ] == element )
            return 1;
    }

    return 0;
}

void fnAddToSetOfFS( int iFrameSize )
{
    int iPos;

    if ( !fnIsInSetOfFS( iFrameSize ) )
    {
        iPos = g_iSizeOfSetFS;

        while( iPos > 0 )
        {
            if( iFrameSize > g_setOfFS[ iPos - 1 ] )
                break;

            g_setOfFS[ iPos ] = g_setOfFS[ iPos - 1 ];
            iPos--;
        }

        g_setOfFS[ iPos ] = iFrameSize;
        g_iSizeOfSetFS++;
    }
}

void fnRemoveToSetOfFS( int index )
{
    int i;

    if ( g_iSizeOfSetFS > 0 && index >= 0 && index < g_iSizeOfSetFS )
    {
        for ( i = index; i < g_iSizeOfSetFS - 1; i++ )
        g_setOfFS[ i ] = g_setOfFS[ i + 1 ];

        g_iSizeOfSetFS--;
    }
}

void fnFindFactorsGEq( int num, int greatOrEqual )
{
    int i;

    for( i = greatOrEqual; i <= num + 1; i++ )
    {
        if ( num % i == 0 )
            fnAddToSetOfFS( i );
    }
}

void fnFindPossibleFS( sPeriodicTask *task, int numOfTasks, int smallerFrameSize )
{
    int i;//, f;

    for ( i = 0; i < numOfTasks; i++ )
        fnFindFactorsGEq( task[ i ].period, smallerFrameSize );

    // Aplicando la condición 3 antes de agregar al conjunto de tamaños de frame
    /*for ( i = 0; i < numOfTasks; i++ )
    {
        for ( f = smallerFrameSize; f <= task[ i ].period; f++ )
        {
            if ( task[ i ].period % f == 0)
            {
                if ( fnFrameSizeCond3( f, task, numOfTasks ) )
                    fnAddToSetOfFS( f );
            }
        }
    }*/
}

void fnFindFSWithFSConstrains( sPeriodicTask *task, int numOfTasks )
{
    int i = 0;

    while ( i < g_iSizeOfSetFS )
    {
        /* Si se elimina un elemento no se aumenta el índice,
         * para no "saltar" elementos.
         */
        if ( !fnFrameSizeCond3( g_setOfFS[ i ], task, numOfTasks ) )
            fnRemoveToSetOfFS( i );
        else
            i++;
    }
}

/**********************************************************
 *                 FUNCTIONS FOR STEP 4                   *
 **********************************************************
 *               FUNCIONES PARA EL PASO 4                 *
 **********************************************************/

int fnGetNumberOfFrames( int iHyperperiod, int iFrameSize )
{
    return iHyperperiod / iFrameSize ;
}

int fnGetNumberOfJobs( sPeriodicTask *task, int iNumOfTasks )
{
    int i, iNumOfJobs = 0;

    for( i = 0; i < iNumOfTasks; i++ )
        iNumOfJobs += task[ i ].jobs;

    return iNumOfJobs;
}

void fnInitAdjacencyMatrix( int iDegree )
{
    int i, j;

    for ( i = 0; i < iDegree; i++ )
        for( j = 0; j < iDegree; j++ )
            g_adjacencyMatrix[ i ][ j ] = 0;
}

void fnFillAdjacencyMatrix( sPeriodicTask *task, int iNumOfTasks, int iNumOfJobs, int iNumOfFrames, int iFrameSize )
{
    int iDegree,
        iColumn = 1,
        i, j;

    sFrame frame[ iNumOfFrames ];
    sJob job[ iNumOfJobs ];

    // degree = source + number of jobs + number of frames + sink
    iDegree = 1 + iNumOfJobs + iNumOfFrames + 1;

    fnInitAdjacencyMatrix( iDegree );

    /* Del nodo fuente (source) hay una arista a cada nodo job, etiquetada
     * con el tiempo de ejecución del correspondiente job.
     */
    for ( i = 0; i < iNumOfTasks; i++ )
    {
        for ( j = 0; j < task[ i ].jobs; j++ )
            g_adjacencyMatrix[ 0 ][ iColumn + j ] = task[ i ].executionTime;

        // iColumn += task[ i ].jobs;
        iColumn += j;
    }

    /* Para cada frame hay un nodo; y de cado uno de esos nodos hay
     * una arista al nodo sumidero (sink), nodo destino, etiquetada
     * con el tamaño del frame.
     */
    for ( i = 0; i < iNumOfFrames; i++ )
        g_adjacencyMatrix[ iColumn + i ][ iDegree - 1 ] = iFrameSize;

    fnMakeFrameTable( frame, iNumOfFrames, iFrameSize );
    fnMakeJobTable( task, job, iNumOfTasks );

    /******** SÓLO PARA PRUEBAS *******/
    printf( "\n  Frame table:\n\n   frame  start  end\n" );

    for ( i = 0; i < iNumOfFrames; i++ )
        printf( "    %d\t   %d\t  %d\n", i + 1, frame[ i ].iStart, frame[ i ].iEnd );

    printf( "\n  Job table:\n\n   job  arrival  deadline\n" );

    for ( i = 0; i < iNumOfJobs; i++ )
        printf( "    %d\t  %d\t  %d\n", i + 1, job[ i ].iArrival, job[ i ].iDeadline );
    /**********************************/

    /* Hay una arista del nodo job J al nodo frame f, si:
     *          start frame f >= arrival job J
     * y
     *           end frame f <= deadline job J
     */
    for ( i = 0; i < iNumOfJobs; i++ )
    {
        for( j = 0; j < iNumOfFrames; j++ )
        {
            /* Se le suma uno al número de renglón y columna por
             * los nodos fuente (source) y sumidero (sink).
             */
            if ( frame[ j ].iStart >= job[ i ].iArrival )
            {
                if ( frame[ j ].iEnd <= job[ i ].iDeadline )
                    g_adjacencyMatrix[ i + 1 ][ iNumOfJobs + j + 1 ] = iFrameSize ;
            }
        }
    }
}

void fnMakeFrameTable( sFrame* frame, int iNumOfFrames, int iFrameSize )
{
    int i;

    for ( i = 0; i < iNumOfFrames; i++ )
    {
        frame[ i ].iStart = i * iFrameSize ;
        frame[ i ].iEnd = frame[ i ].iStart + iFrameSize;
    }
}

void fnMakeJobTable( sPeriodicTask* tasks, sJob* job, int iNumOfTasks )
{
    int i, j, iRow = 0;

    for ( i = 0; i < iNumOfTasks; i++ )
    {
        for ( j = 0; j < tasks[ i ].jobs; j++  )
        {
            job[ iRow + j ].iArrival = j * tasks[ i ].period;
            job[ iRow + j ].iDeadline = job[ iRow + j ].iArrival + tasks[ i ].deadline;
        }

        // iRow += tasks[ i ].jobs ;
        iRow += j;
    }
}
