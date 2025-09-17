#include "sort.h"

int main() {
    int arr[SIZE];
    
    printf("Enter %d integers:\n", SIZE);

    for (int i = 0; i < SIZE; ++i) {
        printf("int at index %d: ", i);
        scanf("%d", &arr[i]);
    }   

    printf("\nOriginal array:\n");
    print_array(arr);

    bubble_sort(arr);    
    
    printf("\nSorted array:\n");
    print_array(arr);

    return 0;
}
