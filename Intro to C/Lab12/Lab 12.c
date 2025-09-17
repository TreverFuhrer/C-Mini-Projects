#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int parentToChild[2];
    
    int P2C = pipe(parentToChild);
    if (P2C == -1) {  // always check if pipe failed
        perror("Pipe creation failed");
        exit(1);
    }

    int childToParent[2];
    int C2P = pipe(childToParent);
    if (C2P == -1) { 
        perror("Pipe creation failed");
        exit(1);
    }

    pid_t pidOrZero = fork();
    if (pidOrZero < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pidOrZero > 0) {   // Parent process
        close(parentToChild[0]); // Close the read end of the pipe (parent only writes)

        // Write five numbers to the pipe using the write end (index 1)
        int numbers[] = {5, 10, 15, 20, 25}; 
        for (int i = 0; i < 5; i++) {
            write(parentToChild[1], &numbers[i], sizeof(int));      
            printf("Parent sent: %d\n", numbers[i]);
            sleep(1);    // pass 2 and see what happens
        }
        close(parentToChild[1]); // Close the write end of the pipe
        wait(NULL);

        // TODO: Parent reads sum from the second pipe childToParent
        close(childToParent[1]);
        int sum = 0;
        read(childToParent[0], &sum, sizeof(int));
        printf("Parent received sum: %d\n", sum);
        close(childToParent[0]);
    }
    else if (pidOrZero == 0) {   // Child process
        close(parentToChild[1]); // Close the write end of the pipe (child only reads)

        int numBuffer;
        ssize_t bytesRead;
        int sum = 0;

        // Read data from the pipe using the read end (index 0) and sum them
        while ((bytesRead = read(parentToChild[0], &numBuffer, sizeof(int))) > 0) {
            printf("Child read: %d\n", numBuffer);
            sum += numBuffer;            
        }
        close(parentToChild[0]); // Close the read end of the pipe
        printf("Child is done calculating sum: %d\n", sum);
        
        // TODO: Child writes sum to the second pipe childToParent
        close(childToParent[0]);
        write(childToParent[1], &sum, sizeof(int)); 
        close(childToParent[1]);

        return 0;
    }

    return 0;
}
