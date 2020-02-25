#include "uls.h"

void mx_print_nonexistent(t_list *list) {
    t_list *node;

    node = list;
    if (node)
        mx_set_errno_to_nsfod(((t_f_stat*)(node->data))->name);
    while (node) {
        mx_set_perror(((t_f_stat*)(node->data))->name);
        node = node->next;
    }
}

void mx_print_stats(t_wlists *wlists, char *flags) {
    if (flags && (flags[2] == 'l' || flags[5] == 'g' || flags[6] == 'o'))
        mx_print_long_format(wlists, flags);
    else if ((flags && flags[7] == '1') || !isatty(1))
        mx_print_single_column(wlists, flags);
    else
        mx_print_multi_column(wlists);
}

void mx_print_long_format(t_wlists *wlists, char *flags) {
    t_c_widths cwidths;
    int unique_dir;

    mx_print_nonexistent(wlists->nonexistent_list);
    if (wlists->file_list) {
        mx_fill_c_widths(wlists->file_list, &cwidths);
        mx_print_formatted_list(wlists->file_list, &cwidths, flags);
        if (wlists->dir_list)
            mx_printlast("");
    }
    unique_dir = mx_listlen(wlists->file_list) == 0 &&
        mx_listlen(wlists->dir_list) == 1 &&
        mx_listlen(wlists->nonexistent_list) == 0;
        mx_print_dir_content(wlists->dir_list, 1, !unique_dir, flags);
}

void mx_print_single_column(t_wlists *wlists, char *flags) {
    t_list *node;
    int unique_dir;

    mx_print_nonexistent(wlists->nonexistent_list);
    node = wlists->file_list;
    while (node) {
        mx_printlast(((t_f_stat*)(node->data))->name);
        node = node->next;
    }
    if (wlists->file_list && wlists->dir_list)
        mx_printlast("");
    unique_dir = mx_listlen(wlists->file_list) == 0 &&
        mx_listlen(wlists->dir_list) == 1 &&
        mx_listlen(wlists->nonexistent_list) == 0;
    mx_print_dir_content(wlists->dir_list, 0, !unique_dir, flags);
}
