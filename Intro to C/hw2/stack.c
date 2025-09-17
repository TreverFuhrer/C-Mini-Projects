/*********************************************************************
* Author: Trever Fuhrer
* Created: 2/23/25
*
* This program implements stack operations using both a static 
* stack with a fixed capacity and a dynamic stack that resizes 
* as needed using realloc.
**********************************************************************/

#include "dslib.h"

#define GROWTH_FACTOR 2

/*
* Pushes a value onto the stack if not full
* input - stack array, top index, int value, index the value will be added in the array
* output - no outputs
*/
void static_stack_push(int *stack, int *top, int value) {
    if (*top < STATIC_CAPACITY) {
        stack[*top] = value;
        ++*top;
    }
}

/*
* Pops a value from the top of the stack and returns it.
* input - stack array, top index, where the value will be removed from the stack
* output - the value being removed, -1 if stack is empty
*/
int pop(int *stack, int *top) {
    if (*top == 0) {
        return -1;
    }
    --*top;
    return stack[*top];
}

/*
* Creates a new int array to act as a stack using malloc.
* input - int capacity, the size of the new array
* output - new int array created with malloc
*/
int* dynamic_stack_init(int *capacity) {
    int *arr = malloc(*capacity * sizeof(int));
    if (arr == NULL) {
        printf("Dynamic stack memory allocation failed\n");
        exit(1);
    }
    return arr;
}

/*
* Pushes a value onto the stack and resizes it if too small.
* input - stack array, top index, stack capacity, value to be pushes
* output - no outputs
*/
void dynamic_stack_push(int *stack, int *top, int *capacity, int value) {
    // Double stack size if at full capacity
    if (*top >= *capacity) {
        *capacity *= GROWTH_FACTOR;
        int *new_stack = realloc(stack, *capacity * sizeof(int));
        if (new_stack == NULL) {
            printf("Dynamic stack memory reallocation failed\n");
            exit(1);
        }
        stack = new_stack;
    }
    stack[*top] = value;
    ++*top;
}

/*
* Deallocates the memory the stack is using so other things could use it.
* input - stack array, the stack that will be deallocated
* output - no outputs
*/
void dynamic_stack_deallocate(int *stack) {
    free(stack);
    stack = NULL;
}
