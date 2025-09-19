/*********************************************************************
* Author: Trever J. Fuhrer, September 2025
* myshell: simple shell that runs commands and supports "-o" redirection.
* Usage: ./myshell  (type "exit" to quit)
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

int main(void) {
    char buffer[MAX_LINE + 2];
    char *args[MAX_ARGS];
    char *token;

    while (1) {
        int argc = 0;

        printf("myshell> ");

        // Load line into buffer and exit if null
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;

        buffer[strcspn(buffer, "\n")] = '\0';

        // Ignore empty lines
        if (buffer[0] == '\0') continue;

        // Check if user typed exit
        if (strcmp(buffer, "exit") == 0) break;

        // Tokenize input
        token = strtok(buffer, " ");

        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        // Check for output redirection
        char *outfile = NULL;
        int bad_output = 0;
        for (int i = 0; i < argc; ++i) {
            if (strcmp(args[i], "-o") == 0) {
                if (i == 0 || i != argc - 2) {
                    printf("Error: invalid -o usage\n");
                    outfile = NULL;
                    bad_output = 1;
                    break;
                }
                outfile = args[argc-1];
                args[i] = NULL;
                args[argc-1] = NULL;
                break;
            }
        }
        if (bad_output) continue;

        pid_t pid = fork();

        // Child process
        if (pid == 0) {
            if (outfile) {
                FILE *file = freopen(outfile, "w", stdout);
                if (file == NULL) {
                    perror("freopen");
                    exit(1);
                }
            }
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