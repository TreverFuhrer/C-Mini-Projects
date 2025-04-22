#include "utils.h"

static char output[MAX_FILEPATHS][MAX_NAME_LEN];
static int output_count = 0;

void add_line(const char *line) {
    if (output_count >= MAX_FILEPATHS) return;
    strncpy(output[output_count], line, MAX_NAME_LEN - 1);
    output[output_count][MAX_NAME_LEN - 1] = '\0';
    output_count++;
}

void collect_recursive(const char *path, int include_hidden, int recursive) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    static char names[MAX_FILEPATHS][MAX_NAME_LEN];
    int name_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!include_hidden && entry->d_name[0] == '.') continue;
        if (name_count >= MAX_FILEPATHS) break;

        strncpy(names[name_count], entry->d_name, MAX_NAME_LEN - 1);
        names[name_count][MAX_NAME_LEN - 1] = '\0';
        name_count++;
    }

    closedir(dir);

    if (recursive) {
        char header[MAX_NAME_LEN];
        snprintf(header, MAX_NAME_LEN, "%s:", path);
        add_line(header);
    }

    for (int i = 0; i < name_count; i++) {
        add_line(names[i]);
    }

    if (!recursive) return;

    dir = opendir(path);
    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (!include_hidden && entry->d_name[0] == '.') continue;

        char subpath[MAX_NAME_LEN];
        snprintf(subpath, MAX_NAME_LEN, "%s/%s", path, entry->d_name);

        DIR *subdir = opendir(subpath);
        if (subdir) {
            closedir(subdir);
            collect_recursive(subpath, include_hidden, recursive);
        }
    }

    closedir(dir);
}

void minils(int argc, char *argv[]) {
    int include_hidden = 0;
    int recursive = 0;
    char *path = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            include_hidden = 1;
        } else if (strcmp(argv[i], "-R") == 0) {
            recursive = 1;
        } else if (argv[i][0] == '-') {
            usage(); return;
        } else {
            if (path != NULL) {
                usage(); return;
            }
            path = argv[i];
        }
    }

    if (path == NULL) {
        usage(); return;
    }

    DIR *check = opendir(path);
    if (!check) {
        usage(); return;
    }
    closedir(check);

    output_count = 0;

    collect_recursive(path, include_hidden, recursive);

    qsort(output, output_count, sizeof(output[0]), cmp);

    for (int i = 0; i < output_count; i++) {
        printf("%s\n", output[i]);
    }
}
