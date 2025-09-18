#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char buffer[1024];
    char *token;
    char *args[100];
    

    while (1) {
        int argc = 0;

        printf("myshell> ");

        // Load line into buffer and exit if null
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        // Ignore empty lines
        if (strcmp(buffer, "\0") == 0) {
            continue; 
        }

        // Check if user typed exit
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Tokenize input
        token = strtok(buffer, " ");

        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;


        // Temp printing of args
        for (int i = 0; args[i] != NULL; i++) {
            printf("arg[%d] = '%s'\n", i, args[i]);
        }
        printf("\n");

        // Check for output redirection
        char *outfile = NULL;
        for (int i = 0; i < argc; ++i) {
            if (strcmp(args[i], "-o") == 0) {
                if (i != argc - 2) {
                    printf("Error: -o must be followed by a filename\n");
                    break;
                }
                printf("Output redirection detected\n");
                outfile = args[argc-1];
                args[i] = NULL;
                args[argc-1] = NULL;
                break;
            }
        }

        if (outfile) {
            printf("\n");
        }

        pid_t pid = fork();

        // Child process
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } 
        // Parent process
        else if (pid > 0) {
            waitpid(pid, NULL, 0);
        } 
        // Fork failed
        else {
            perror("fork");
        }


    }

    return 0;
}