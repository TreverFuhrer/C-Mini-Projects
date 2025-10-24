/**
 * Program: Virtual Memory 
 * Description: 
 *   This program simulates page replacement algorithms: FIFO and LRU
 *
 * Usage:
 *   ./tvm filename fifo|lru frame_count
 *
 */

 #include "utils.h"

void usage(char *str) {
    printf("%s\n", str);
    fprintf(stderr, "Usage: ./tvm filename fifo|lru frame_count\n");
    exit(1);
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        usage("Error: Invalid number of arguments.\n");
    }
    
    int frame_count = atoi(argv[3]);
    char *policy = argv[2];
    char *filename = argv[1];

    if(frame_count < 2 || frame_count > 256){
        usage("Error: Invalid frame count.\n");
    }

    if (strcmp(policy, "fifo") == 0) {
        fifo(filename, frame_count);
    } 
    else if (strcmp(policy, "lru") == 0) {
        lru(filename, frame_count);
    } 
    else {
        usage("Error: Unknown page replacement policy.\n");
    }
    
    return 0;
}

