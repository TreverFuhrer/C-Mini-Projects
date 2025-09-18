#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    char buffer[MAX_LINE + 2];

    if (argc < 2) {
        printf("Usage: ./myhead <filename>\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("myhead: cannot open %s\n", argv[1]); 
        return 1; 
    }

    // Read first 3 lines
    for (int i = 0; i < 3; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) break;
        fputs(buffer, stdout);
    }

    //Check for read error
    if (ferror(file)) { 
        printf("myhead: read error\n"); 
        fclose(file); 
        return 1; 
    }

    // Close file
    fclose(file);
    return 0;
}