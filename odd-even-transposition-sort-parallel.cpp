
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

int compare (const void * a, const void * b)
{
    return ( *(int*)a > *(int*)b );
}

MPI_Status status;

int main(int argc, char *argv[]){

    /* Allocate serie environment variables */
	int numtasks, taskid;
	int problemSize, nLocal, *data, recdata[100], recdata2[100], *temp, i;

	/* Start parallel computing */
	MPI_Init(&argc, &argv);

    /* Getting the current processes (rank) */
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    /* Getting the number of processes (size) */
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    /* Allocate parallel environment variables */
    bool isMaster, isEven, isOdd;

    isMaster = (taskid == 0);
    if(isMaster){

        /* Getting the problemSize */
        printf("\n Please enter the number of numbers to sort: ");
        fflush(stdout);
        scanf("%i", &problemSize);

        nLocal = problemSize/numtasks;

        /* Getting the array to order */
    	data = (int*)malloc(sizeof(int)*problemSize);
        for( i=0; i<problemSize; i++) {
           data[i] = rand()%100;
        }

        printf("\n Array data is: ");
        for(i=0; i<problemSize; i++){
       	    printf("%d ", data[i]);
        }
        printf("\n");

    }
    else{
    	data=NULL;
    }

    /* Broadcasts a message from the master to all other processes of the communicator */
    MPI_Bcast(&nLocal, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* Sends data from one process to all other processes in a communicator */
    MPI_Scatter(data, nLocal, MPI_INT, &recdata, 100, MPI_INT, 0, MPI_COMM_WORLD);

    /* Getting the received data */
    printf(" %d received data ",taskid);
    for( i=0; i<nLocal; i++){
        printf("%d ",recdata[i] );
    }
    printf("\n");

    /* Sort elements in range */
    sort(recdata, recdata+nLocal);

    /* Begin the odd-even sort */
    int oddrank, evenrank;

    isEven = ( taskid % 2 == 0 );
    if(isEven){
    	oddrank = taskid-1; 
    	evenrank = taskid+1;
	}
 	else { /* Odd */
 		oddrank = taskid+1;
 		evenrank = taskid-1;
	}

    /* Set the ranks of the processors at the end of the linear */
    if(oddrank == -1 || oddrank == numtasks)
        oddrank = MPI_PROC_NULL;
    if(evenrank == -1 || evenrank == numtasks)
        evenrank = MPI_PROC_NULL;
    
    for( int phase=0; phase<numtasks-1; phase++ ) {

        isOdd = ( phase % 2 == 1 );
        if (isOdd) /* Odd */
            MPI_Sendrecv(recdata, nLocal, MPI_INT, oddrank, 1, recdata2,
            nLocal, MPI_INT, oddrank, 1, MPI_COMM_WORLD, &status);
        else /* Even */
            MPI_Sendrecv(recdata, nLocal, MPI_INT, evenrank, 1, recdata2,
            nLocal, MPI_INT, evenrank, 1, MPI_COMM_WORLD, &status);        

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
    MPI_Gather(recdata, nLocal, MPI_INT, data, nLocal, MPI_INT, 0, MPI_COMM_WORLD);

    isMaster = (taskid == 0);
    if(isMaster){
        printf("\n Final sorted data: ");
        for( i=0; i<problemSize; i++ ){
            printf("%d ",data[i] );
        }
        printf("\n");
    }

    MPI_Finalize();

}