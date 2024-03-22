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

#define TICK "✓"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

struct FoundFiles {
    char file_name[256];
};

void print_found_files(struct FoundFiles found_files[]) {
    for(int i = 0; i < 255; i++) {
        if(found_files[i].file_name[0] == '\0') {
            break;
        }
        else {
            printf(CYN "[BUILD_FILES] " RESET "%s\t" CYN "[OUTCOME] " GRN TICK "\n", found_files[i].file_name);
        }
    }
}

void insert_into_found_files(struct FoundFiles found_files[], char *file_name) {
    for(int i = 0; i < 255; i++) {
        if(found_files[i].file_name[0] == '\0') {
            strcpy(found_files[i].file_name, file_name);

            found_files[i].file_name[sizeof(found_files[i].file_name) - 1] = '\0';

            break;
        }
    }
}

void check_file_extension(struct FoundFiles found_files[], const char *file_extension, char *file_name) {
    const char *ext = strrchr(file_name, FILE_EXT_DOT);

    if (ext != NULL && strcmp(ext + 1, file_extension) == 0) {
        insert_into_found_files(found_files, file_name);
    }
}

void get_build_files(struct FoundFiles found_files[], const char *dir_path, const char *file_extension) {
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

        check_file_extension(found_files, file_extension, dir_entry->d_name);
    }

    closedir(folder);
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

    struct FoundFiles found_files[255] = {0};
    
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strncpy(result, GCC_O, total_length);
    strncat(result, exe_name, strnlen(exe_name, MAX_EXE_NAME));

    get_build_files(found_files, dir_path, file_extension);

    for(int i = 0; i < 3; i++) {
        strncat(result, " ", 2);
        strncat(result, dir_path, total_length);
        strncat(result, found_files[i].file_name, total_length);
    }

    print_found_files(found_files);

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
        strncat(result, " ", 2); 
        strncat(result, build_files[i].file_path, total_length);

        printf(CYN "[BUILD_FILES] " RESET "%s\t" CYN "[OUTCOME] " GRN TICK "\n", build_files[i].file_path);
    }

    system(result);
    free(result);

    return;
}
