#include "uls.h"

void mx_print_multi_column(t_wlists *wlists) {	
    int unique_dir;
    int col;
    t_mc_list mc_list;

    col = mx_get_terminal_width();
    mx_print_nonexistent(wlists->nonexistent_list);
    if (wlists->file_list) 	{
        mx_get_mc_list_stats(wlists->file_list, col, &mc_list);
        mx_print_multi_column_list(wlists->file_list, &mc_list);

    }
    if (wlists->file_list && wlists->dir_list)
        mx_printlast("");
    unique_dir = mx_listlen(wlists->file_list) == 0 &&
        mx_listlen(wlists->dir_list) == 1 &&
        mx_listlen(wlists->nonexistent_list) == 0;
    mx_print_multi_column_dlist(wlists->dir_list, col, unique_dir);
}

void mx_print_multi_column_list(t_list *list,  t_mc_list *mc_list) {
    t_list *node;
    t_list *first;
    int i;
    int c = 0;

    first = list;
    node = first;
    while (c < mc_list->lst_len) {
        mx_putstr_w(((t_f_stat*)(node->data))->name, mc_list->max, 1);
        mx_printchar('\t');
        i = -1;
        while (node && ++i < mc_list->rows)
            node = node->next;
        if (!node) {
            node = first->next;
            first = node;
            mx_printlast("");
        }
        c++;
    }
}

//как правильно переносить 1 строку?
void mx_print_multi_column_dlist(t_list *dlist, int col,
        int unique_dir) {
    t_list *dnode;
    t_mc_list mc_list;

    dnode = dlist;
    while (dnode) {
        if (!unique_dir) {
            if (dnode != dlist)
                mx_printlast("");
            mx_printstr((((t_dnode*)(dnode->data))->dir_stats)->path);
            mx_printlast(":");
        }
        if ((((t_dnode*)(dnode->data))->dir_stats)->permissions[1] == '-') {
            mx_set_errno_to_nopermission((((t_dnode*)(dnode->data))-> //правильный ли тут перенос?
                        dir_stats)->path);
            mx_set_perror((((t_dnode*)(dnode->data))->dir_stats)->name);
        }
        mx_get_mc_list_stats(((t_dnode*)(dnode->data))->f_list, col, &mc_list);
        mx_print_multi_column_list(((t_dnode*)(dnode->data))->f_list, &mc_list);
        dnode = dnode->next;
    }
}
