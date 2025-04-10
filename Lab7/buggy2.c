#include <stdlib.h>
#include <stdio.h>

int square(int x) {
    int sq = x * x;
    return sq;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing argument.");
        return 1;
    }
    printf("This program will square an integer.\n");
    int numToSquare = atoi(argv[1]);
    int squaredNum = square(numToSquare);
    printf("%d squared is %d\n", numToSquare, squaredNum);

    return 0;
}