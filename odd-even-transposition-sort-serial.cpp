
//Main for "odd-even-transposition-sort-serial" C++ application
//Created by r4m0nl1m4 28/10/2020

//library(ies)
#include <stdlib.h>

//new library(ies)
#include "./oddeven.h"
#include "./report.h"

int main(int argc, char** argv){

    /* Allocate serie environment variables */
    int problemSize, *array;
    double executeTime;
    struct timeval start, end;

    gettimeofday(&start, 0);
    
    array = getRandomArrayByTerminal(&argc, const_cast<const char**>(argv));

    problemSize = argc-1;

    oddEvenTranspositionSort(array, problemSize);

    gettimeofday(&end, 0);

    executeTime = getExecuteTime(start, end); 

    saveResultReportOnFile("result_report-serie-runtime.txt", executeTime);

    //printArray(array, problemSize);

    return 0;
}