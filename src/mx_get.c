#include "uls.h"

int mx_get_terminal_width(void) {
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return (w.ws_col);
}

void mx_get_mc_list_stats(t_list *list, int col, t_mc_list *mc_list) {
    mc_list->max = mx_get_max_filename_length(list);
    mc_list->lm = mx_get_lm(mc_list->max);
    mc_list->columns = (col - 1) / mc_list->lm;
    mc_list->columns = mc_list->columns == 0 ? 1 : mc_list->columns;
    mc_list->lst_len = mx_listlen(list);
    mc_list->rows = mc_list->lst_len / mc_list->columns +
        ((mc_list->lst_len % mc_list->columns) != 0);
}

int mx_get_max_filename_length(t_list *list) {
    int len;
    int max_len;
    t_list *node;

    max_len = 0;
    node = list;
    while (node) {
        if ((len = mx_strlen(((t_f_stat*)(node->data))->name)) > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len;
}

int	mx_get_lm(int n) {
    int lowest_multiple;

    lowest_multiple = 0;
    while (lowest_multiple <= n)
        lowest_multiple += 8;
    return (lowest_multiple);
}

