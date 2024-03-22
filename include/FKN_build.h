#ifndef FKN_BUILD_H
#define FKN_BUILD_H

#ifdef __cplusplus
extern "C" {
#endif

    struct BuildFiles {
        const char *file_path;
    };

    void FKN_BUILD(struct BuildFiles build_files[], int array_length, char exe_name[]);

    int FKN_GET_ARRAY_LENGTH(struct BuildFiles build_files[]);

    void FKN_BUILD(struct BuildFiles build_files[], int array_length, char exe_name[]);

    void FKN_BUILD_IT_FOR_ME(const char *dir_path, const char *file_extension, char exe_name[]);

#ifdef __cplusplus
}
#endif
#endif // FKN_BUILD_H
