/*********************************************************************
* Author: Trever Fuhrer
* Created: September 2025
*
* Program: mycat
* Purpose: Display the contents of one file, or combine and display 
*          the contents of two files. Works like a simplified version
*          of the Unix `cat` command.
* Usage:   ./mycat filename
*          ./mycat file1 file2
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    char buffer[MAX_LINE + 2];

    if (argc == 2) {
        // Open file
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("mycat: cannot open %s\n", argv[1]); 
            return 1; 
        }

        // Read file contents
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            fputs(buffer, stdout);
        }

        // Check for read error
        if (ferror(file)) { 
            printf("mycat: read error\n"); 
            fclose(file); 
            return 1; 
        }

        // Close file
        fclose(file);
    }
    else if (argc == 3) {
        // Open file
        FILE *file1 = fopen(argv[1], "r");
        FILE *file2 = fopen(argv[2], "r");
        if (!file1 || !file2) {
            printf("mycat: cannot open one of your files.\n"); 
            return 1;
        }

        // Read file1
        while (fgets(buffer, sizeof(buffer), file1) != NULL) {
            fputs(buffer, stdout);
        }
        // Check for file1 read error
        if (ferror(file1)) { 
            printf("mycat: read error, cannot read file1\n"); 
            fclose(file1);
            return 1; 
        }

        // Read file2
        while (fgets(buffer, sizeof(buffer), file2) != NULL) {
            fputs(buffer, stdout);
        }
        // Check for file2 read error
        if (ferror(file2)) { 
            printf("mycat: read error, cannot read file2\n"); 
            fclose(file2);
            return 1; 
        }

        // Close files
        fclose(file1);
        fclose(file2);
    }
    else {
        printf("Must have at least 2 args Ex: ./mycat file or ./mycat file1 file2\n"); 
        return 1; 
    }

    return 0;
}