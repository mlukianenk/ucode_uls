#include "uls.h"

void mx_error_exit(char *err_msg, char ***file_list, char **flags) {
    if (err_msg)
        mx_printlast(err_msg);
    mx_free_input(file_list, flags);
    exit(EXIT_FAILURE);
}

/*
функция для вывода 
uls: illegal option -- 
usage: uls [-1AGSRaglort] [file ...] 
*/

static char get_invalid_flag(char *flags) {
    int i = 1;

    if (!flags || flags[1] == '\0')
        return 0;
    while (flags[i] != '\0') {
        if (flags[i] != 'r' && flags[i] != 'a' && flags[i] != 'R' &&
            flags[i] != 'l' && flags[i] != 't' && flags[i] != 'g' &&
            flags[i] != 'o' && flags[i] != '1' && flags[i] != 'A' &&
            flags[i] != 'S')
            return (flags[i]);
        i++;
    }
    return 0;
}

void mx_error_usage(char *invalid_flag_args) {
    char c;

    c = get_invalid_flag(invalid_flag_args);
    mx_printerr("uls: illegal option -- ");
    write (2, &c, 1);
    mx_printerr("\n");
    mx_printerr(ERR_USAGE);
    mx_printerr("\n");
}
