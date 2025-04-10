#include <stdio.h>
#include <stdlib.h>

#define STATIC_CAPACITY 5  // Capacity for the static stack

void static_stack_push(int *stack, int *top, int value);

int* dynamic_stack_init(int *capacity);
void dynamic_stack_push(int *stack, int *top, int *capacity, int value);
void dynamic_stack_deallocate(int *stack);

int pop(int *stack, int *top);