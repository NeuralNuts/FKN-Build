#ifndef _FKN_BUILD_H_

struct BuildFiles {
    const char *file_path;
};

void check_file_extension(char *file_extension, struct dirent *dir_entry);

void FKN_BUILD(struct BuildFiles build_files[], int array_length, char exe_name[]);

char *read_dir(char *dir_path);

int FKN_GET_ARRAY_LENGTH(struct BuildFiles build_files[]);

void FKN_BUILD(struct BuildFiles build_files[], int array_length, char exe_name[]);

#endif
