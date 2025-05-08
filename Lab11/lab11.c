#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;

    if (argc < 2) {
        return 0;
    }

    // === Child 1: Run ls ===
    pid = fork();
    if (pid < 0) {
        perror("Fork failed for ls");
        return 1;
    }
    if (pid == 0) { // Child 1 starts 
        printf("Child 1 is launching ls:\n");
        char *args[] = {"ls", ".", "-a", NULL}; // TODO: try adding a flag for ls like -a or -R
        execvp(args[0], args);
        perror("execvp for ls failed");
        return 1;
    } // Child 1 ends

    waitpid(pid, NULL, 0);
    printf("Child 1 done.\n\n");


    // === Child 2: Run grep ===
    pid = fork();
    if (pid < 0) {
        perror("Fork failed for grep");
        return 1;
    }
    if (pid == 0) { // Child 2 starts
        printf("Child 2 is launching grep:\n");
        char *args[] = {"grep", argv[1], "sample.txt", NULL};
        execvp(args[0], args);
        // TODO: run grep with execvp in this child process
        perror("execvp for grep failed");
        return 1;
    }// Child 2 ends

    waitpid(pid, NULL, 0);
    printf("Child 2 done.\n\n");

    // === Child 3: Run Greeter ===
    pid = fork();
    if (pid < 0) {
        perror("Fork failed for greeter");
        return 1;
    }
    if (pid == 0) { // Child 3 starts
        printf("Child 3 is launching greeter:\n");
        char *args[] = {"./greeter", argv[1], NULL};
        execvp(args[0], args);
        // TODO: run greeter with execvp in this child process
        perror("execvp for greeter failed");
        return 1;

    }// Child 3 ends

    waitpid(pid, NULL, 0);
    printf("Child 3 done.\n");

    return 0;
}
