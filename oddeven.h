
//Main for "oddeven" C++ application
//Created by r4m0nl1m4 28/10/2020

//Guard
#ifndef ODDEVEN_H
#define ODDEVEN_H

//library(ies)
#include <stdbool.h>
#include <stdlib.h>
#include <cstdio>

int* getRandomArray(int n){
    int *array = (int*)malloc(sizeof(int)*n);
    for( int i=0; i<n; i++ )
       array[i] = rand() % 100;
    return array;
}

int* getRandomArrayByTerminal(int *argc, const char **argv){
    int size = *argc-1;
    int *array  = (int*)calloc( size, sizeof(int) );
    for( int i=0; i<size; i++ ){
        sscanf( argv[i+1], "%d", &array[i] );
    }
    return array;
}

void printArray(int* array, int arraySize){
    printf(" ");
    for(int i=0; i<arraySize; i++ ){
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void oddEvenTranspositionSort(int* array, int n){
    int i, temp;
    bool isEven;
    for ( int phase=0; phase<n; phase++ ){
    	isEven = ( phase % 2 == 0 );
        if (isEven){
            for( i=1; i<n; i+=2 ){
            	if( array[i-1] > array[i] ){
                    temp = array[i];
                    array[i] = array[i-1];
                    array[i-1] = temp;
            	}
            }
        }
        else{ /* isOdd */
            for( i=1; i<n-1; i+=2 ){
            	if( array[i] > array[i+1] ){
                    temp = array[i];
                    array[i] = array[i+1];
                    array[i+1] = temp;
            	}
            }
        }
    }
}

#endif