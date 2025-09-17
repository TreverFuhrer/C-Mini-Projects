/*********************************************************************
* Author: Trever Fuhrer
* Created: 04/30/25
*
* This program uses forked child processes to search for a pattern
* in every .txt file inside a directory (including subdirectories).
* It uses grep through execvp to do the searching.
*********************************************************************/

#include "utils.h"

// Recursively goes through a directory and runs grep in child processes on .txt files
void explore_and_grep(const char *dir_path, const char *search_term, int use_ignore_case, int *file_counter) {
    
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        DIR *sub = opendir(full_path);
        if (sub != NULL) {
            closedir(sub);
            explore_and_grep(full_path, search_term, use_ignore_case, file_counter);
        }
        else {
            int path_len = strlen(full_path);
            if (path_len >= 4 && strcmp(full_path + path_len - 4, ".txt") == 0) {
                pid_t child = fork();

                if (child == 0) {
                    if (use_ignore_case) {
                        char *args[] = {"grep", "-H", "-c", "-i", (char *)search_term, full_path, NULL};
                        execvp("grep", args);
                    } 
                    else {
                        char *args[] = {"grep", "-H", "-c", (char *)search_term, full_path, NULL};
                        execvp("grep", args);
                    }
                    perror("execvp failed");
                    exit(1);
                } 
                else if (child > 0) {
                    (*file_counter)++;
                } 
                else {
                    perror("fork error");
                }
            }
        }
    }
    closedir(dir);
}

// Handles argument checking, starts search, and waits for all child processes
void grep_extended(int argc, char *argv[]) {
    
    if (argc != 5 && argc != 6) {
        usage_message();
    }

    const char *pattern = argv[1];
    const char *start_dir = argv[2];

    if (strcmp(argv[3], "-c") != 0 || strcmp(argv[4], "-H") != 0) {
        usage_message();
    }

    int ignore_case = 0;
    if (argc == 6) {
        if (strcmp(argv[5], "-i") != 0) {
            usage_message();
        }
        ignore_case = 1;
    }

    DIR *check = opendir(start_dir);
    if (check == NULL) {
        usage_message();
    }
    closedir(check);

    int total_txt_files = 0;

    explore_and_grep(start_dir, pattern, ignore_case, &total_txt_files);

    while (wait(NULL) > 0);

    printf("Finished searching all .txt files.\n");
    printf("Total .txt files searched: %d\n", total_txt_files);
}