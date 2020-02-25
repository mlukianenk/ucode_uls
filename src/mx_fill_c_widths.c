#include "uls.h"

static void fill_file_size_width(t_list *node, t_c_widths *cwidths) {
    int len;

    if (((t_f_stat*)(node->data))->file_type == 'b' ||
            ((t_f_stat*)(node->data))->file_type == 'c') {
        if ((len = mx_intlen(((t_f_stat*)(node->data))->minor)) >
                cwidths->fs_width) {
            cwidths->fs_width = len;
        }
        if ((len = mx_intlen(((t_f_stat*)(node->data))->major)) >
                cwidths->longest_major) {
            cwidths->longest_major = len;
        }
    }
    else if ((len = mx_intlen(((t_f_stat*)(node->data))->file_size)) >
            cwidths->fs_width) {
        cwidths->fs_width = len;
    }
}

//ПОДОГНАТЬ ПОД АУДИТОР
void mx_fill_c_widths(t_list *f_list, t_c_widths *cwidths) {
    t_list *node;
    int len;

    cwidths->lc_width = 0;
    cwidths->uid_width = 0;
    cwidths->group_width = 0;
    cwidths->fs_width = 0;
    cwidths->longest_major = 0;
    node = f_list;
    while (node) {
        if ((len = mx_intlen(((t_f_stat*)(node->data))->link_count)) >
                cwidths->lc_width)
            cwidths->lc_width = len;
        if ((len = (int)mx_strlen(((t_f_stat*)(node->data))->user)) >
                cwidths->uid_width)
            cwidths->uid_width = len;
        if ((len = (int)mx_strlen(((t_f_stat*)(node->data))->group)) >
                cwidths->group_width)
            cwidths->group_width = len;
        fill_file_size_width(node, cwidths);
        node = node->next;
    }
}

int mx_intlen(int n) {
    int c;

    if (n == 0)
        return 1;
    c = 0;
    while (n != 0) {
        n /= 10;
        c++;
    }
    return c;
}
