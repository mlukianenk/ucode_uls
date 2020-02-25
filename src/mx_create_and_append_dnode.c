#include "uls.h"

void mx_create_and_append_dnode(t_dnode *new_dnode, t_list *new_node,
        t_wlists *wlists, t_f_stat *dir) {
    new_dnode->f_list = new_node;
    new_dnode->dir_stats = dir;
    new_node = mx_listnew(NULL, 0);
    new_node->data = new_dnode;
    new_node->data_size = sizeof(new_dnode);
    mx_append_lst(&(wlists->dir_list), new_node);
}
