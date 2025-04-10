/**************************************************************************************************************************************
*
* Description: This program tests the functionality of a static and dynamic stack implementation.
*
* How to Compile and execute the program:
* make
* ./mystack
**************************************************************************************************************************************/

#include "dslib.h"
#include <assert.h>

void custom_assert(int testcase, int condition, const char *msg, int expected, int actual) {
    if (condition) {
        printf("Testcase %d succeeded: %s (Expected: %d, Actual: %d)\n", testcase, msg, expected, actual);
    } else {
        printf("\033[31mTestcase %d failed: %s (Expected: %d, Actual: %d)\033[0m\n", testcase, msg, expected, actual);
        assert(condition);
    }
}

int main() {
    printf("*********************************************************************************\nTESTING STATIC STACK\n*********************************************************************************\n\n");
    int static_stack[STATIC_CAPACITY];
    int top = 0;

    for (int i = 10; i <= 50; i += 10) {
        static_stack_push(static_stack, &top, i);
    }

    int testcase = 1; 
    // Check pushed values
    int expected_values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < STATIC_CAPACITY; i++) {
        custom_assert(testcase++, static_stack[i] == expected_values[i], "Pushed Value", expected_values[i], static_stack[i]);
    }
    
    printf("\n");
    custom_assert(testcase++, top == STATIC_CAPACITY, "Full Stack. Stack top should equal capacity", STATIC_CAPACITY, top);

    // Attempt to push into a full stack
    int previous_top = top;
    static_stack_push(static_stack, &top, 60);
    custom_assert(testcase++, top == previous_top, "Full Stack. Stack top should not exceed capacity", previous_top, top);
    printf("\n");

    // Pop values and check
    for (int i = STATIC_CAPACITY - 1; i >= 0; i--) {
        int popped_value = pop(static_stack, &top);
        custom_assert(testcase++, popped_value == expected_values[i], "Popped value", expected_values[i], popped_value);
    }
    printf("\n");
    
    // At this point, the stack should be empty
    custom_assert(testcase++, top == 0, "Empty Stack. Stack top should be 0 after popping all", 0, top);

    // Attempting to pop from an empty stack
    int popped_value = pop(static_stack, &top);
    custom_assert(testcase++, popped_value == -1, "Empty Stack. Popping from empty stack should return -1", -1, popped_value);
    printf("\n");

    // Attempt to push 60 again but into an empty stack 
    int newItem = 60;
    static_stack_push(static_stack, &top, newItem);
    custom_assert(testcase++, static_stack[0] == newItem, "Pushed Value", newItem, static_stack[0]);
    printf("\n");


    printf("*********************************************************************************\nTESTING DYNAMIC STACK\n*********************************************************************************\n\n");
    int dynamic_stack_capacity = 5; // initial capacity of the dynamic stack
    int *dynamic_stack = dynamic_stack_init(&dynamic_stack_capacity);
    top = 0; 

    //push items in stack and check pushed values
    for (int i = 10; i <= 50; i += 10) {
        dynamic_stack_push(dynamic_stack, &top, &dynamic_stack_capacity, i);
    }

    for (int i = 0; i < top; i++) {
        custom_assert(testcase++, dynamic_stack[i] == expected_values[i], "Pushed Value", expected_values[i], dynamic_stack[i]);
    }
    
    printf("\n");
    custom_assert(testcase++, top == 5, "Stack full. Stack top should equal capacity", 5, top);

    // Attempt to push into a full stack
    int previous_capacity = dynamic_stack_capacity;
    dynamic_stack_push(dynamic_stack, &top, &dynamic_stack_capacity, 60);
    custom_assert(testcase++, dynamic_stack_capacity == previous_capacity * 2, "Stack capacity should be double", previous_capacity * 2, dynamic_stack_capacity);
    printf("\n");

    // Pop values and check
    int new_expected_values[] = {10, 20, 30, 40, 50, 60};
    for (int i = top - 1; i >= 0; i--) {
        popped_value = pop(dynamic_stack, &top);
        custom_assert(testcase++, popped_value == new_expected_values[i], "Popped value", new_expected_values[i], popped_value);
    }
    printf("\n");
    
    // At this point, the stack should be empty
    custom_assert(testcase++, top == 0, "Empty Stack. Stack top should be 0 after popping all", 0, top);

    // Attempting to pop from an empty stack
    popped_value = pop(dynamic_stack, &top);
    custom_assert(testcase++, popped_value == -1, "Empty Stack. Popping from empty stack should return -1", -1, popped_value);
    printf("\n");

    dynamic_stack_deallocate(dynamic_stack);
    
    return 0;
}