#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int global_data = 0;

int main() {
    //printf("Before fork(): I am the only process now. PID=%d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    //printf("After fork(): I am one of the two processes running after the fork. My PID=%d\n", getpid());
    
    if (pid == 0) { // Child process
        printf("Child: I am the child process. My PID is %d, My parent PID is %d\n", getpid(), getppid());
        printf("Child: global_data=%d\n", global_data);

        //int local_data = 5;
        //printf("Child: local_data=%d\n", local_data);

        // TODO: write a loop that runs 1000 times and increment global_data
        while (global_data < 1000) {
            ++global_data;
            printf("Child: Incrementing, global_data=%d\n", global_data);
        }
        printf("Child: After Incrementing, global_data=%d\n", global_data);

        for (int i = 5; i > 0; --i) {
            sleep(1);
            printf("Child Countdown: %d\n", i);
        }
        printf("Child process done with countdown.\n");

    }
    else{
        printf("Parent: I am the parent process. My PID is %d\n", getpid());
        
        printf("Parent: global_data=%d\n", global_data);
        
        //printf("Parent: local_data=%d\n", local_data);

        // TODO: write a loop that runs 1000 times and increment global_data same as in the child process
        while (global_data < 1000) {
            ++global_data;
            printf("Parent: Incrementing, global_data=%d\n", global_data);
        }
        printf("Parent: After Incrementing, global_data=%d\n", global_data);

        waitpid(pid, NULL, 0);
        printf("Parent: Child has finished.\n"); 
    }
    
    return 0;
}
