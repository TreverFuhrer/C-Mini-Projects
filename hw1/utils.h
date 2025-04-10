#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void readGrid(int rows, int columns, int grid[rows][columns]);
void computeStats(int rows, int columns, int grid[rows][columns], int count[SIZE]);
void printStats(int count[SIZE]);
void findPath(int rows, int columns, int grid[rows][columns]);
