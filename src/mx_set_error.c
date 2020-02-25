#include "uls.h"

void mx_set_errno_to_nsfod(char *filename) {
    struct stat file_info;

    lstat(filename, &file_info);
}

void mx_set_errno_to_nopermission(char *dirname) {
    DIR *dir_p;

    dir_p = opendir(dirname);
}

void mx_set_perror(char *str) {
    char *errmsg;

    errmsg = mx_strjoin("uls: ", str);
    perror(errmsg);
    mx_strdel(&errmsg);
    exit(1);
}
