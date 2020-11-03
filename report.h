
//Main for "report" C application
//Created by r4m0nl1m4 14/10/2020

//Guard
#ifndef REPORT_H
#define REPORT_H

//library(ies)
#include <sys/time.h>
#include <stdbool.h>
#include <stdio.h>

double getExecuteTime(struct timeval start, struct timeval end){
    double executeTime = (double)(end.tv_usec - start.tv_usec) / 1000000 + (double)(end.tv_sec - start.tv_sec);
    return executeTime;
}

void saveResultReportOnFile(const char* fileName, double executeTime){
    FILE *fp = fopen(fileName, "a");  
    bool fileOpened = (fp != NULL) ? true : false;  
    if(fileOpened)
    {
        fprintf(fp, " %1.2e", executeTime);
        fclose(fp);
    }
    else{
        fprintf(stderr, "Can't open output file %s!\n", fileName);
        exit(1);        
    }
}

void saveCPUReportOnFile(const char* fileName, int numtasks, int problemSize, double local[], double total[], double executeTime){
    FILE *fp = fopen(fileName, "a");  
    bool fileOpened = (fp != NULL) ? true : false;  
    if(fileOpened)
    {
        fprintf(fp, "\n    Runtime %1.2e [s] \n", executeTime);
        fprintf(fp, "\n    Process        Total  problemSize        Total        Local        Total\n");
        for( int process=0; process<numtasks; process++ )
            fprintf(fp, " %10d   %10d   %10d   %10d   %10lf   %10lf\n", process, numtasks, problemSize/numtasks, problemSize, local[process], total[process]);
        fprintf(fp, "--------------------------------------------------------------------------------\n");
        fclose(fp);
    }
    else{
        fprintf(stderr, "Can't open output file %s!\n", fileName);
        exit(1);        
    }
}

void saveOrderedArrayReportOnFile(const char* fileName, double executeTime, int problemSize, int *array){
    FILE *fp = fopen(fileName, "a");  
    bool fileOpened = (fp != NULL) ? true : false;  
    if(fileOpened)
    {
        fprintf(fp, "\n    Runtime %1.2e [s] \n\n    Ordened Array is:\n", executeTime);
        for(int i=0; i<problemSize; i++ ){
            if (i==0) fprintf(fp, "\n");
            fprintf(fp, "%d ", array[i]);
        }
        fprintf(fp, "\n--------------------------------------------------------------------------------\n");
        fclose(fp);
    }
    else{
        fprintf(stderr, "Can't open output file %s!\n", fileName);
        exit(1);        
    }
}

#endif