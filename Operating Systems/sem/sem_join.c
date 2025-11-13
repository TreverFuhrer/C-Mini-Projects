#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t s;

void *child_routine(void *arg) {
    int id = *(int *)arg;
    printf("child %d: running\n", id);
    int localCount = 0;
    for(int i = 0; i < 1000; i++){
        localCount ++; // just simulating some work
    }
    printf("child %d: done, signaling parent\n", id);
    sem_post(&s); // signal parent
    return NULL;
}

int main(void) {
    pthread_t c1, c2;
    unsigned int x;
    int id1 = 1, id2 = 2;

    printf("Enter initial value of semaphore: x=");
    scanf("%u", &x);
    sem_init(&s, 0, x); // initialize semaphore with input x

    printf("parent: begin\n");

    // Create two child threads
    pthread_create(&c1, NULL, child_routine, &id1);
    pthread_create(&c2, NULL, child_routine, &id2);

    printf("parent: waiting for children...\n");

    // Wait for both children
    sem_wait(&s);
    printf("parent: got one signal!\n");
    sem_wait(&s);
    printf("parent: received both signals, ending now\n");

    return 0;
}
