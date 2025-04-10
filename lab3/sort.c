#include "sort.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr) {
    // TODO: Implement the bubble sort algorithm using two loops.
    // Use the constant SIZE to determine the number of elements.
    // Remember: You can access elements of *arr like a regular array: arr[i]
    for (int j = 0; j < SIZE; ++j) {
        for (int k = 0; k < SIZE-j-1; ++k) {
            if (arr[k] > arr[k+1]) {
                swap(&arr[k], &arr[k+1]);
            }
        }
    }
}

void print_array(int *arr) {
    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
