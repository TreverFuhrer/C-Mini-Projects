/*********************************************************************
* Author: Trever J. Fuhrer, September 2025
* myuniq: collapse adjacent duplicate lines; with -c, print counts.
* Usage: ./myuniq [-c] <filename>
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    char prev[MAX_LINE + 2];
    char curr[MAX_LINE + 2];
    int have_prev = 0;
    int count = 0;
    int withCount = 0;
    char *path = NULL;

    if (argc == 2) {
        path = argv[1];
    }
    else if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        withCount = 1;
        path = argv[2];
    }
    else {
        printf("Usage: ./myuniq [-c] <filename>\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("myuniq: cannot open %s\n", path); 
        return 1; 
    }

    //Check for read error
    if (ferror(file)) { 
        printf("myuniq: read error\n"); 
        fclose(file); 
        return 1; 
    }

    // Read first line
    while (fgets(curr, sizeof(curr), file) != NULL) {
        if (!have_prev) {
            strcpy(prev, curr);
            have_prev = 1;
            count = 1;
            continue;
        }

        if (strcmp(curr, prev) == 0) {
            count++;
        } 
        else {
            if (withCount) {
                printf("%d %s", count, prev);
            } 
            else {
                fputs(prev, stdout);
            }
            strcpy(prev, curr);
            count = 1;
        }
    }

    if (have_prev) {
        if (withCount) {
            printf("%d %s", count, prev);
        } 
        else {
            fputs(prev, stdout);
        }
    }

    // Close file
    fclose(file);
    return 0;
}