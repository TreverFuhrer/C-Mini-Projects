/*******************************************************************
* Description: 
* This C program extend grep command to search a pattern in all text files in a directory with multi processes. 

Usage:
* Compile it using a C compiler and run the executable from the command line with appropriate arguments.
*    - To run the program: ./mgrep <pattern> <directory> -c -H [-i]
*    - optional arguments are specified in [ ]
*******************************************************************/

#include "utils.h" 


void usage_message() {
    fprintf(stderr, "Usage: ./mgrep <pattern> <directory> -c -H [-i]\n");
    exit(1);
}


int main(int argc, char *argv[]) {
    if (argc < 5) {
        usage_message();
        return 1;
    }

    grep_extended(argc, argv);

    return 0;
}
