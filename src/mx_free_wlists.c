#include "uls.h"

static void free_t_f_stat_list(t_list **list) {
    t_list *node;
    t_f_stat *file_stat;
    t_list *prev;

    node = *list;
    while (node)     {
        file_stat = (t_f_stat*)(node->data);
        mx_free_file_obj(&file_stat);
        prev = node;
        node = node->next;
        free(prev);
    }
    *list = NULL;
}

static void free_dnode_list(t_list **list) {
    t_list	*main_node;
    t_dnode	*dnode;
    t_list	*prev;

    main_node = (*list);
    while (main_node) {
        dnode = ((t_dnode*)(main_node->data));
        free_t_f_stat_list(&(dnode->f_list));
        if (dnode->dir_stats)
            mx_free_file_obj(&(dnode->dir_stats));
        prev = main_node;
        main_node = main_node->next;
        free(prev);
    }
    *list = NULL;
}

void mx_free_wlists(t_wlists *wlists) {
    if (wlists->dir_list)
        free_dnode_list(&(wlists->dir_list));
    if (wlists->file_list)
        free_t_f_stat_list(&(wlists->file_list));
    if (wlists->nonexistent_list)
        free_t_f_stat_list(&(wlists->nonexistent_list));
}

void mx_free_file_obj(t_f_stat **file_stat) {
    if (!file_stat || !(*file_stat))
        return ;
    if ((*file_stat)->name)
        mx_strdel(&((*file_stat)->name));
    if ((*file_stat)->path)
        mx_strdel(&((*file_stat)->path));
    if ((*file_stat)->link)
        mx_strdel(&((*file_stat)->link));
    if ((*file_stat)->user)
        mx_strdel(&((*file_stat)->user));
    if ((*file_stat)->group)
        mx_strdel(&((*file_stat)->group));
    free(*file_stat);
    *file_stat = NULL;
}
