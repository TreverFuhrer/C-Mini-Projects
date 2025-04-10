#include "arrays.h"
#include <stdlib.h>
#include <stdio.h>

int* createArrayWithMalloc(int size) {
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < size; ++i) {
        printf("M- What goes in index %d? ", i);
        scanf("%d", (arr+i));
    }
    return arr;
}

int* createArrayWithCalloc(int size) {
    int *arr = calloc(size, sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i < size; ++i) {
        printf("C- What goes in index %d? ", i);
        scanf("%d", (arr+i));
    }
    return arr;
}

int* concatenateArrays(int* arr1, int size1, int* arr2, int size2) {
    // TODO: Calculate the total size of the concatenated array
    int totalSize = size1 + size2;

    // TODO: Allocate memory for the concatenated array and check for NULL
    int* concatenatedArray = malloc(totalSize * sizeof(int));
    if (concatenatedArray == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // TODO: Copy elements from arr1 to concatenatedArray using a loop from 0-size1
    for (int i = 0; i < size1; ++i) {
        concatenatedArray[i] = arr1[i];
    }
    // TODO: Copy elements from arr2 to concatenatedArray using another loop. From which
    // index does this loop start?
    for (int i = 0; i < size2; ++i) {
        concatenatedArray[size1 + i] = arr2[i];
    }

    return concatenatedArray;
}

void freeSpace(int *arr) {
    free(arr);
    arr = NULL;
}