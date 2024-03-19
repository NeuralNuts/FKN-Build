#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/FKN_build.h"

char *read_dir(char *dir_path) {
    DIR *folder;

    struct dirent *dir_entry;
    int files = 0;

    folder = opendir(dir_path);

    if(folder == NULL) {
        puts("ERROR: cannot open dir, REASON: inavlid dir name/path");
        exit(-1);
    }

    while((dir_entry = readdir(folder))) {
        files++;

        printf("[FILE_NUMBER]: %2d, [FILE_NAME]: %10s, [FILE_TYPE]: %2d\n", 
                files,
                dir_entry->d_name,
                dir_entry->d_type);
    }
    closedir(folder);
    return 0;
}

void check_file_extension(char *file_extension, struct dirent *dir_entry) {
    char *ext = strchr(dir_entry->d_name, '.');

    if(!ext || strcmp(ext, file_extension) == 1);
    else {
        printf("file: %s, extension: %s\n", dir_entry->d_name, ext + 1);
    }
}

int FKN_GET_ARRAY_LENGTH(struct BuildFiles build_files[]) {
    size_t array_length = 0;

    while(build_files[array_length].file_path != NULL) {
        array_length++;
    }
    return array_length;
}

void FKN_BUILD(struct BuildFiles build_files[], int array_length, char exe_name[]) {
    size_t total_length = strlen("gcc -o ") + strlen(exe_name) + array_length * (FILENAME_MAX + 2) + 1;
    char *result = malloc(total_length);

    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strcpy(result, "gcc -o ");
    strcat(result, exe_name);

    for (int i = 0; i < array_length; i++) {
        strcat(result, " ");
        strcat(result, build_files[i].file_path);
    }

    printf("%s\n", result);

    system(result);

    free(result);
}
