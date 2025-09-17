#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int countDir(const char *basePath) {
    DIR* dirp = opendir(basePath);
    struct dirent *entry;
    int count = 0;

    if(dirp == NULL) {
        perror("can't open basePath");
    }

    for(;;) {
        entry = readdir(dirp);
        if (entry == NULL) break;
        if (!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) {
            char newPath[1024];
            strcpy(newPath, basePath);
            strcat(newPath, "/");

            char *name = entry->d_name;
            strcat(newPath, name);

            // Extra credit
            int len = strlen(name);
            if (strcmp(name + len - 4, ".txt") == 0) {
                printf("%s ", name);
            }
            
            DIR* entp = opendir(newPath);
            if (entp != NULL) {
                ++count;
                count += countDir(newPath);
            }

        }
    }

    return count;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Invalid amount of args\n");
        exit(1);
    }

    printf("\n%s\n", "Only Text files:");
    int count = countDir(argv[1]);
    printf("\n\nNumber of directories = %d\n", count);

    return 0;
}