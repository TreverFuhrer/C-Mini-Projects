#include "arrays.h"
#include <stdio.h>

int main() {
    int size1, size2;
    // TODO: Prompt the user to enter size1 and size2
    printf("How big is size1: ");
    scanf("%d", &size1);
    printf("How big is size2: ");
    scanf("%d", &size2);

    // Create the first array using createArrayWithMalloc
    int *arr1 = createArrayWithMalloc(size1);
    
    // Create the second array using createArrayWithCalloc
    int *arr2 = createArrayWithCalloc(size2);
    
    // Concatenate the arrays using concatenateArrays
    int *ptr = concatenateArrays(arr1, size1, arr2, size2);
    
    // TODO: Print the contents of the concatenated array that ptr is pointing to
    for (int i = 0; i < size1+size2; ++i) {
        printf("%d ", ptr[i]);
    }
    
    // TODO: Free the memory allocated for all three arrays. The first one is done for you.
    freeSpace(arr1);
    freeSpace(arr2);
    freeSpace(ptr);
}