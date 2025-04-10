#include "header.h"

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Invalid amount of args\n");
        exit(1);
    }

    FILE* fp;

    fp = fopen(argv[2], "r");

    if (fp == NULL) {
        printf("Invalid file.");
        exit(0);
    }

    if (strcmp(argv[1], "-1") == 0) {
        int lines = countLines(fp);
        printf("File has %d lines", lines);
    }
    else if (strcmp(argv[1], "-w") == 0) {
        int words = countWords(fp);
        printf("File has %d words", words);
    }
    else {
        printf("Invalid arg.");
    }

    fclose(fp);
}