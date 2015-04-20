//
// Created by Mitra on 4/18/2015.
//

#include <stdio.h>


#define INFINITY 999999999
#define SIZE 100000000

#ifndef CPROGRAMMING_2014_3_H
#define CPROGRAMMING_2014_3_H

#endif //CPROGRAMMING_2014_3_H


int findF(int Stamps[], int AmtStamps,int K){
    int i,j;
    int* storage;

    storage = (int*)malloc((SIZE) * sizeof(int*));
    storage[0] = 0;

    for(i=1;i<=SIZE;i++){
        storage[i] = INFINITY;
        for(j=1;j<=AmtStamps;j++){
            if (Stamps[j] <= i && storage[i-Stamps[j]] + 1 < storage[i] ){
                storage[i] = storage[i-Stamps[j]] + 1;
            }
        }
        if (storage[i] > K){
            free(storage);
            return i;
        }
    }
    // freeing memory
    free(storage);
    return -1;
}