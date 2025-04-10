/*********************************************************************
* Author: Trever Fuhrer
* Created: 03/31grep Way sample.txt
/25
*
* This program implements a simplified version of the Unix grep command.
* It searches for a given pattern in a file and prints out any lines
* containing that pattern.
*********************************************************************/

#include "text.h"

#define MAX_PATTERN_LENGTH 10
#define MAX_LINE_LENGTH 1024

// Helper to convert a string to lowercase
void lowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Check if a line contains the pattern
int containsPattern(const char *line, const char *pattern, int ignoreCase) {
    char lineCopy[MAX_LINE_LENGTH];
    char patternCopy[MAX_PATTERN_LENGTH + 1];

    if (ignoreCase) {
        strncpy(lineCopy, line, MAX_LINE_LENGTH);
        lineCopy[MAX_LINE_LENGTH - 1] = '\0';

        strncpy(patternCopy, pattern, MAX_PATTERN_LENGTH + 1);
        patternCopy[MAX_PATTERN_LENGTH] = '\0';

        lowerCase(lineCopy);
        lowerCase(patternCopy);

        return strstr(lineCopy, patternCopy) != NULL;
    } 
    else {
        return strstr(line, pattern) != NULL;
    }
}

void grepLite(int argc, char *argv[]) {

    if (argc < 3) {
        usage();
        return;
    }

    char *pattern = argv[1];
    char *filename = argv[2];

    // Pattern must be 1–10 characters
    if (strlen(pattern) == 0 || strlen(pattern) > MAX_PATTERN_LENGTH) {
        usage();
        return;
    }

    int ignoreCase = 0;
    int showLineNums = 0;

    // Check optional flags
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            ignoreCase = 1;
        } 
        else if (strcmp(argv[i], "-n") == 0) {
            showLineNums = 1;
        } 
        else {
            usage();
            return;
        }
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        usage();
        return;
    }

    char line[MAX_LINE_LENGTH];
    int lineNum = 1;
    int matchFound = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line[strcspn(line, "\n")] = '\0';

        if (containsPattern(line, pattern, ignoreCase)) {
            if (showLineNums) {
                printf("%d:%s\n", lineNum, line);
            } 
            else {
                printf("%s\n", line);
            }
            matchFound = 1;
        }
        lineNum++;
    }

    if (!matchFound) {
        printf("No matches found for pattern \"%s\" in file %s.\n", pattern, filename);
    }

    fclose(file);
}
