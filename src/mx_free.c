#include "uls.h"

void mx_free_flag_arguments(char ***flag_arguments) {
    int i;

    if (flag_arguments && *flag_arguments) {
        i = 0;
        while ((*flag_arguments)[i])
            mx_strdel((*flag_arguments) + (i++));
        free(*flag_arguments);
        *flag_arguments = NULL;
    }
    flag_arguments = NULL;
}

void mx_free_input(char ***file_list, char **flags) {
    int i;

    i = 0;
    if (file_list && *file_list) {
        while ((*file_list)[i])
            free((*file_list)[i++]);
        free(*file_list);
        *file_list = NULL;
    }
    if (flags && *flags) {
        free(*flags);
        *flags = NULL;
    }
}
