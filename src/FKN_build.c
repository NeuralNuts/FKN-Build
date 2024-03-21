// std
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FKN BUILD 
#include "../include/FKN_build.h"

#define GCC_O "gcc -o "
#define MAX_EXE_NAME 255
#define MAX_FILE_EXT 255
#define FILE_EXT_DOT '.'

char *check_file_extension(const char *file_extension, char *file_name) {
    const char *ext = strrchr(file_name, FILE_EXT_DOT);

    if (ext != NULL && strcmp(ext + 1, file_extension) == 0) {
        printf("[FILES_FOUND] %s\t\n", file_name);
    }

    return 0;
}

char *get_build_files(const char *dir_path, const char *file_extension) {
    DIR *folder;
    struct dirent *dir_entry;

    folder = opendir(dir_path);

    if (folder == NULL) {
        printf("ERROR: cannot open directory '%s'\n", dir_path);
        exit(-1);
    }

    while ((dir_entry = readdir(folder)) != NULL) {
        if (strcmp(dir_entry->d_name, ".") == 0 ||
            strcmp(dir_entry->d_name, "..") == 0) continue;

        check_file_extension(file_extension, dir_entry->d_name);
    }

    closedir(folder);
    return 0;
}

int FKN_GET_ARRAY_LENGTH(struct BuildFiles build_files[]) {
    size_t array_length = 0;

    while(build_files[array_length].file_path != NULL) {
        array_length++;
    }
    return array_length;
}

void FKN_BUILD_IT_FOR_ME(const char *dir_path, const char *file_extension, char exe_name[]) {
    size_t total_length = strnlen(GCC_O, sizeof(GCC_O)) +
                          strnlen(exe_name, 255) +
                          (FILENAME_MAX + 2) + 1;

    char *result = malloc(total_length);
    
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strncpy(result, GCC_O, total_length);
    strncat(result, exe_name, strnlen(exe_name, MAX_EXE_NAME));


    strncat(result, " ", 2); 
    strncat(result, get_build_files(dir_path, file_extension), total_length);

    (void)printf("[BUILD_FILES] \t %s \n", get_build_files(dir_path, file_extension));

    system(result);
    free(result);

    return;
}

void FKN_BUILD(struct BuildFiles build_files[], int array_length, char exe_name[]) {
    size_t total_length = strnlen(GCC_O, sizeof(GCC_O)) +
                          strnlen(exe_name, 255) +
                          (size_t)array_length *
                          (FILENAME_MAX + 2) + 1;

    char *result = malloc(total_length);
    
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strncpy(result, GCC_O, total_length);
    strncat(result, exe_name, strnlen(exe_name, MAX_EXE_NAME));

    for (int i = 0; i < (size_t)array_length; i++) {
        size_t file_count = 0;

        strncat(result, " ", 2); 
        strncat(result, build_files[i].file_path, total_length);

        (void)printf("[BUILD_FILES] \t %s \n", build_files[i].file_path);
    }

    system(result);
    free(result);

    return;
}
