#include <stdio.h>
#include "includes/queue.h"
#include "includes/mathfunctions.h"
#include "includes/cyclicschedule.h"
#include "includes/fordfulkerson.h"

/*********** MOVER ***********/
int fnQuit( );
void fnCyclicSchedule( int iNumberOfTasks );
int fnGetTotalExecutionTime( sPeriodicTask* task, int iNumOfTasks );
void fnGetScheduling( sPeriodicTask* task, int iNumOfJobs, int iNumOfFrames );
/*****************************/

int main( )
{
    int iNumOfTasks;

    printf( "Cyclic Schedule [Version 1]\n" );
    printf( "2017 F. M. Corona Ventura.\n" );

    do
    {
        printf( "\n Number of tasks: " );
        scanf( "%d", &iNumOfTasks );

        if( iNumOfTasks > 1 )
            fnCyclicSchedule( iNumOfTasks );
        else
            printf( "\n Error: The number of tasks must be at least 2.\n" );
    } while( !fnQuit( ) );

    return 0;
}

int fnQuit( )
{
    char cQuit;

    do
    {
        fflush( stdin );

        printf( " Quit (y/n)? " );
        scanf( "%c", &cQuit );
    } while( cQuit != 'y' && cQuit != 'n' );

    if( cQuit == 'y' )
        return 1;

    return 0;
}

void fnCyclicSchedule( int iNumberOfTasks )
{
    int iHyperperiod,
        iSmallerFrameSize,
        iNumberOfFrames,
        iNumberOfJobs,
        iFrameSize,
        iTotalExecutionTime,
        iDegreeOfAdjacencyMatrix,
        iFlowMax,
        i;

    sPeriodicTask task[ iNumberOfTasks ];

    fnInitTasks( task, iNumberOfTasks );

    // Encontrar el hiperperiodo
    iHyperperiod = fnHyperperiod( task, iNumberOfTasks );

    printf( "\n STEP 1:\n\n  Hyperperiod: %d\n\n", iHyperperiod );

    // Encontrar el número jobs para cada tarea
    fnFindJobs( task, iHyperperiod, iNumberOfTasks );

    printf( " STEP 2:\n\n" );
    printf( "  task\t jobs" );

    for ( i = 0; i < iNumberOfTasks; i++ )
        printf( "\n   %d\t  %d", i + 1, task[ i ].jobs );

    /* CONDICIÓN 1
     * Encontrar el menor tamaño posible de frame
     */
    iSmallerFrameSize = fnFrameSizeCond1( task, iNumberOfTasks );
    // iSmallerFrameSize = 1;

    printf( "\n\n STEP 3:\n\n" );
    printf( "  Frame size >= %d\n", iSmallerFrameSize );

    /* CONDICIÓN 2
     * Encontrar todos los tamaños de frame que cumplan las
     * condiciones 1 y 2
     */
    fnFindPossibleFS( task, iNumberOfTasks, iSmallerFrameSize );

    printf( "  Possible frame sizes: " );

    for ( i = 0;  i < g_iSizeOfSetFS; i++ )
        printf( "%d, ", g_setOfFS[ i ] );

    /* CONDICIÓN 3
     * Encontrar todo los tamaños de frames que cumplan las
     * condiciones 1, 2 y 3.
     */
    fnFindFSWithFSConstrains( task, iNumberOfTasks );

    printf( "\n  Frames than meet frame-size constraints: " );

    if ( g_iSizeOfSetFS == 0 )
        printf( "no frame meets the constrains." );
    else
    {
        for ( i = 0;  i < g_iSizeOfSetFS; i++ )
        printf( "%d, ", g_setOfFS[ i ] );

        /* Construcción del grafo de flujo de red */
        printf( "\n\n STEP 4:" );

        // TODO: MOVER
        iTotalExecutionTime = fnGetTotalExecutionTime( task, iNumberOfTasks );

        i = g_iSizeOfSetFS - 1;

        while( i >= 0 )
        {
            iFrameSize = g_setOfFS[ i ];

            printf( "\n\n  For a frame size of: %d\n", iFrameSize );

            iNumberOfFrames = fnGetNumberOfFrames( iHyperperiod, iFrameSize );
            iNumberOfJobs = fnGetNumberOfJobs( task, iNumberOfTasks );

            // num_source + num_jobs + num_frames + num_sink
            iDegreeOfAdjacencyMatrix = 1 + iNumberOfJobs + iNumberOfFrames + 1;

            if ( iDegreeOfAdjacencyMatrix > MAX_DEGREE_ADJACENCY_MATRIX - 1 )
            {
                printf( "\n Error: Degree of adjacency matrix. " );
                printf( "Increase the grade to at least %d.", iDegreeOfAdjacencyMatrix + 1 );

                break;
            }

            fnFillAdjacencyMatrix( task, iNumberOfTasks, iNumberOfJobs, iNumberOfFrames, iFrameSize );

            iFlowMax = fnFordFulkerson( g_adjacencyMatrix, iDegreeOfAdjacencyMatrix );

            printf( "\n  Flow Max: %d; Total Execution Time: %d.", iFlowMax, iTotalExecutionTime );

            if ( iFlowMax == iTotalExecutionTime )
            {
                fnGetScheduling( task, iNumberOfJobs, iNumberOfFrames );
                break;
            }
            else
                printf( "\n\n  For a frame size of %d the scheduler is not feasible.", iFrameSize );

            i--;
        }
    }

    printf( "\n\n" );
}

int fnGetTotalExecutionTime( sPeriodicTask* task, int iNumOfTasks )
{
    int i, iTotalExecutionTime = 0;

    for ( i = 0; i < iNumOfTasks; i++ )
        iTotalExecutionTime += task[ i ].jobs * task[ i ].executionTime;

    return iTotalExecutionTime;
}

void fnGetScheduling( sPeriodicTask* task, int iNumOfJobs, int iNumOfFrames )
{
    int iRow = iNumOfJobs + 1,
        iCurrTask,
        iJobCurrTask,
        iNumOfJobsCurrTask,
        i, j;

    for ( i = 0; i < iNumOfFrames; i++ )
    {
        iCurrTask = 0;
        iJobCurrTask = 0;
        iNumOfJobsCurrTask = task[ iCurrTask ].jobs;

        printf( "\n\n  Frame %d:\n\n", i + 1 );
        printf( "   task\t time" );

        for ( j = 0; j < iNumOfJobs ; j++ )
        {
            if ( iJobCurrTask == iNumOfJobsCurrTask )
            {
                iCurrTask++;
                iJobCurrTask = 0;
                iNumOfJobsCurrTask = task[ iCurrTask ].jobs;
            }

            if ( g_residualGraph[ iRow + i ][ 1 + j ] != 0)
                printf( "\n    %d\t  %d", iCurrTask + 1, g_residualGraph[ iRow + i ][ 1 + j ] );

            iJobCurrTask++;
        }
    }
}

