
//Main for "odd-even-transposition-sort-parallel" C application
//Created by r4m0nl1m4 28/10/2020

//library(ies)
#include <algorithm>
#include <iostream>
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//new library(ies)
#include "./oddeven.h"
#include "./report.h"

using namespace std;

MPI_Status status;

int main(int argc, char** argv){

    /* Allocate serie environment variables */
	int numtasks, taskid;
	int problemSize, nLocal, *array, recdata[100], recdata2[100], *temp, i;
    double timeStart, timeEnd, executeTime;

	/* Start parallel computing */
	MPI_Init(&argc, &argv);

    /* Getting the Start Time */
    timeStart = MPI_Wtime();

    /* Getting the current processes (rank) */
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    /* Getting the number of processes (size) */
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    /* Allocate parallel environment variables */
    bool isMaster, isEven, isOdd;

    isMaster = (taskid == 0);
    if(isMaster){

        array = getRandomArrayByTerminal(&argc, const_cast<const char**>(argv));

        problemSize = argc-1;

        nLocal = problemSize/numtasks;

    }
    else
    	array = NULL;

    /* Broadcasts a message from the master to all other processes of the communicator */
    MPI_Bcast(&nLocal, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* Sends data from one process to all other processes in a communicator */
    MPI_Scatter(array, nLocal, MPI_INT, &recdata, 100, MPI_INT, 0, MPI_COMM_WORLD);

    /* Getting the received data */
    //printf(" %d received data ",taskid);
    //printArray(recdata, nLocal);

    /* Sort elements in range */
    sort(recdata, recdata+nLocal);

    /* Begin the odd-even sort */
    int taskOdd, taskEven;

    isEven = ( taskid % 2 == 0 );
    if(isEven){
    	taskOdd = taskid-1; 
    	taskEven = taskid+1;
	}
 	else { /* Odd */
 		taskOdd = taskid+1;
 		taskEven = taskid-1;
	}

    /* Set the ranks of the processors at the end of the linear */
    if(taskOdd == -1 || taskOdd == numtasks)
        taskOdd = MPI_PROC_NULL;
    if(taskEven == -1 || taskEven == numtasks)
        taskEven = MPI_PROC_NULL;
    
    for( int phase=0; phase<numtasks-1; phase++ ) {

        isOdd = ( phase % 2 == 1 );
        if (isOdd) /* Odd */
            MPI_Sendrecv(recdata, nLocal, MPI_INT, taskOdd, 1, recdata2,
            nLocal, MPI_INT, taskOdd, 1, MPI_COMM_WORLD, &status);
        else /* Even */
            MPI_Sendrecv(recdata, nLocal, MPI_INT, taskEven, 1, recdata2,
            nLocal, MPI_INT, taskEven, 1, MPI_COMM_WORLD, &status);        

        /* Extract nLocal after sorting the two */
        temp = (int*)malloc(nLocal*sizeof(int));
        for( i=0; i<nLocal; i++){
        	temp[i] = recdata[i];
        }

        if(status.MPI_SOURCE==MPI_PROC_NULL)	continue;
        else if(taskid<status.MPI_SOURCE){
        	/* Store the smaller of the two */
        	int i,j,k;
         	for( i=j=k=0; k<nLocal; k++){
         		if( j==nLocal || (i<nLocal && temp[i]<recdata2[j]) )
         			recdata[k] = temp[i++];
         		else
         			recdata[k] = recdata2[j++];
            }
        }
        else{
     	    /* Store the larger of the two */
     	    int i,j,k;
     	    for(i=j=k=nLocal-1;k>=0;k--){
     		    if( j==-1 || (i>=0 && temp[i]>=recdata2[j]) )
     			    recdata[k] = temp[i--];
     		    else
     			    recdata[k] = recdata2[j--];
     	    }
        }
    }

    /* Gathers together values from a group of processes */
    MPI_Gather(recdata, nLocal, MPI_INT, array, nLocal, MPI_INT, 0, MPI_COMM_WORLD);

    isMaster = (taskid == 0);
    if(isMaster){

        timeEnd = MPI_Wtime();

        executeTime = timeEnd-timeStart;

        saveResultReportOnFile("result_report-parallel-runtime.txt", executeTime);
        saveOrderedArrayReportOnFile("result_report-ordered_array.txt", executeTime, problemSize, array);
    }

    MPI_Finalize();

}