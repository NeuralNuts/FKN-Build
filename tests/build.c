#include "../include/FKN_build.h"

#include <stdio.h>

#define EXE_NAME "my_math_program"

struct BuildFiles build_files[] = {
    { .file_path = "./main.c", },
    { .file_path = "./add.c" },
    { .file_path = "./minus.c" }
};

void build() {
    size_t number_of_files = FKN_GET_ARRAY_LENGTH(build_files);

    for(int i = 0; i < number_of_files; i++) {
        FKN_BUILD(build_files, number_of_files, EXE_NAME);
        break;
    }
}

int main() {
    build();
}
