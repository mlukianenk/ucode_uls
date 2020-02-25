#include "uls.h" 

void mx_fill_input(char ***file_list, char **flags, char **argv, int argc) {
    int i = 1;
    int j = 0;

    while (i < argc && argv[i][0] == '-')
        i++;
    if (i < argc &&
        !(*file_list = (char**)malloc(sizeof(char*) * (argc - i) + 1))) {
        mx_error_exit(NULL, file_list, flags);
    }
    while (i < argc) {
        if (!((*file_list)[j] = mx_strnew(mx_strlen(argv[i]))))
            mx_error_exit(NULL, file_list, flags);
        (*file_list)[j] = mx_strcpy((*file_list)[j], argv[i]);
        i++;
        j++;
    }
    (*file_list)[j] = NULL;
}
