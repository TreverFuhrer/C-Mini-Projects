#include "utils.h"

void readGrid(int rows, int columns, int grid[rows][columns]) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            printf("\n0 = Safe Zone\n1 = Giant Spiders\n2 = Treacherous Swamps\n3 = Werewolves\n4 = Venomous Snakes\n");
            printf("\nFor row %d and column %d, which is there: ", row, col);
            scanf("%d", &grid[row][col]);
        }
    }
}

void computeStats(int rows, int columns, int grid[rows][columns], int count[SIZE]) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            ++count[grid[row][col]];
        }
    }
}

void printStats(int count[SIZE]) {
    printf("Count of Obstacles:");
    printf("\nSafe Zone: %d\nGiant Spiders: %d\nTreacherous Swamps: %d\nWerewolves: %d\nVenomous Snakes: %d\n\n",
        count[0], count[1], count[2], count[3], count[4]);
}

void findPath(int rows, int columns, int grid[rows][columns]) {
    int row = 0, col = 0;

    printf("Path:\nStart ");

    while (row < rows - 1 || col < columns - 1) {        
        if (col + 1 < columns && grid[row][col + 1] == 0) {
            col++;
            printf("right ");
        } 
        else if (row + 1 < rows && grid[row + 1][col] == 0) {
            row++;
            printf("down ");
        } 
        else {
            printf("\nYou died :(\n");
            return;
        }
    }
    printf("\nYou destroyed the Ring!\n");
}