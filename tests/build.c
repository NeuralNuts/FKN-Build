#include "../include/FKN_build.h"
#include <stdio.h>

struct BuildFiles build_files[] = {
    { .file_path = "./main.c", },
    { .file_path = "./add.c" },
    { .file_path = "./minus.c" }
};

void build() {
    for(int i = 0; i < FKN_GET_ARRAY_LENGTH(build_files); i++) {
        FKN_BUILD(build_files, FKN_GET_ARRAY_LENGTH(build_files), "my_program");
    }
}

int main() {
    build();
}
