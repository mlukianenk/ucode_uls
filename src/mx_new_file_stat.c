#include "uls.h"

t_f_stat *mx_new_file_stat(char *path, char *name) {
    t_f_stat *file_stat;

    if (!(file_stat = (t_f_stat*)malloc(sizeof(t_f_stat))))
        return NULL;
    if (!(file_stat->name = mx_strdup(name))) {
        free(file_stat);
        return NULL;
    }
    if (!(file_stat->path = mx_strdup(path))) {
        if (file_stat->name)
            mx_strdel(&(file_stat->name));
        free(file_stat);
        return NULL;
    }
    file_stat->link = NULL;
    file_stat->permissions = NULL;
    file_stat->user = NULL;
    file_stat->group = NULL;
    return file_stat;
}
