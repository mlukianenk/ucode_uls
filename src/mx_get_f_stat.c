#include "uls.h"

//АУДИТОР
t_list *mx_get_f_stat(char *path, char *flags, int isarg) {
    struct stat file_info;
    t_f_stat *file_stat;
    t_list *file_stat_node;

    if (!isarg && ((mx_is_hidden(path) && (!flags || (flags[1] != 'a' &&
        flags[8] != 'A'))) || (flags && flags[8] == 'A' && flags[1] != 'a' &&
        (mx_compare("..", mx_get_filename(path)) || mx_compare(".",
        mx_get_filename(path))))))
        return (NULL);
    if ((isarg && !(file_stat = mx_new_file_stat(path, path))) ||
            (!isarg && !(file_stat = mx_new_file_stat(path, mx_get_filename(path)))))
        return (NULL);
    if (lstat(path, &file_info) != 0)
        file_stat->file_type = 'X';
    else if (mx_fill_file_stat(&file_stat, file_info) == -1)
    {
        mx_free_file_obj(&file_stat);
        return (NULL);
    }
    file_stat_node = mx_listnew(NULL, 0);
    file_stat_node->data = file_stat;
    file_stat_node->data_size = sizeof(file_stat);
    return (file_stat_node);
}
