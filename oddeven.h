
//Main for "oddeven" C application
//Created by r4m0nl1m4 28/10/2020

//Guard
#ifndef ODDEVEN_H
#define ODDEVEN_H

//library(ies)
#include <stdbool.h>
#include <stdlib.h>
#include <cstdio>

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