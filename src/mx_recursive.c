#include "uls.h"

void mx_recursive(t_wlists *wlists, char *flags) {
    int unique_dir;

    unique_dir = mx_listlen(wlists->file_list) == 0 &&
        mx_listlen(wlists->dir_list) == 1 &&
        mx_listlen(wlists->nonexistent_list) == 0;
    mx_sort(wlists, flags);
    if (flags && flags[0] == 'R') {
        if (unique_dir) {
            mx_print_stats(wlists, flags);
            mx_single_stream_recursion(((t_dnode*)(wlists->dir_list->
            data))->f_list, flags);
        }
        else
            mx_multi_stream_recursion(wlists, flags);
    }
    else
        mx_print_stats(wlists, flags);
}

void mx_single_stream_recursion(t_list *flist, char *flags) {
    while (flist) {
        if (((t_f_stat*)(flist->data))->file_type == 'd') {
            if (!flags || flags[1] != 'a' ||
                (!mx_compare(((t_f_stat*)(flist->data))->name, ".") &&
                !mx_compare(((t_f_stat*)(flist->data))->name, "..")))
            mx_recursive_lookthrough(((t_f_stat*)(flist->data)), flags);
            flist->data = NULL; //это относится к первому if? или ко второму?
        }
        flist = flist->next;
    }
}


void mx_recursive_lookthrough(t_f_stat *dir, char *flags) {
    t_wlists wlists;
    t_list *new_node;
    t_dnode *new_dnode;

    mx_init_wlist(&wlists);
    new_node = mx_get_dir_stat(dir->path, flags);
    if ((new_dnode = (t_dnode*)malloc(sizeof(t_dnode)))) {
        mx_create_and_append_dnode(new_dnode, new_node, &wlists, dir);
        mx_sort(&wlists, flags);
        mx_printlast("");
        if (flags && (flags[2] == 'l' || flags[5] == 'g' || flags[6] == 'o'))
            mx_print_dir_content(wlists.dir_list, 1, 1, flags);
        else if ((flags && flags[7] == '1') || !isatty(1))
            mx_print_dir_content(wlists.dir_list, 0, 1, flags);
        else
            mx_print_multi_column_dlist(wlists.dir_list,
                    mx_get_terminal_width(), 0);
        mx_single_stream_recursion(new_dnode->f_list, flags);
    }
    mx_free_wlists(&wlists);
}

void mx_multi_stream_recursion(t_wlists *wlists, char *flags) {
    t_list *new_node;

    new_node = wlists->dir_list;
    wlists->dir_list = NULL;
    mx_print_stats(wlists, flags);
    while (new_node) {
        mx_recursive_lookthrough(((t_dnode*)(new_node->data))->dir_stats,
                flags);
        ((t_dnode*)(new_node->data))->dir_stats = NULL;
        new_node = new_node->next;
    }
}
