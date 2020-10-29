
//Main for "odd-even-transposition-sort-serial" C application
//Created by r4m0nl1m4 28/10/2020

//library(ies)
#include <stdlib.h>

//new library(ies)
#include "./oddeven.h"
#include "./report.h"

int main(int argc, char** argv){

    /* Allocate serie environment variables */
    int a[] = {15, 21, 26, 27, 35, 49, 59, 62, 63, 77, 83, 86, 86, 90, 92, 93};
    int n = sizeof(a)/sizeof(a[0]);
    double executeTime;
    struct timeval start, end;

    gettimeofday(&start, 0);

    oddEvenTranspositionSort(a, n);

    gettimeofday(&end, 0);

    executeTime = getExecuteTime(start, end); 

    printf("\n");
    for(int i=0; i<15; i++ ) printf(" %d ", a[i]); 
    printf("\n");

    //saveResultReportOnFile("result_report-serie.txt", a, executeTime);

    return 0;
}