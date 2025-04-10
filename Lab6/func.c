#include "header.h"

int countLines(FILE *fp) {
    char line[1024];
    int lines = 0;
    while (fgets(line, sizeof(line), fp)) {
        ++lines;
    }
    return lines;
}

int countWords(FILE *fp) {
    rewind(fp);
    char line[1024];
    const char delimiter[] = " ";
    int words = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *token;  
        token = strtok(line, delimiter);
        while (token != NULL) {
            ++words;
            token = strtok(NULL, delimiter);
        }
    }
    return words;
}