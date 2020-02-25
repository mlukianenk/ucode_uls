#include "uls.h"

void mx_sort(t_wlists *wlists, char *flags) {
    int ascending;
    int (*cmp)(t_list *, t_list *, int, int);
    t_list *node;

    ascending = flags && flags[3] == 'r' ? 0 : 1;
    cmp = flags && flags[4] == 't' ? &mx_compare_time : &mx_compare_name;
    cmp = flags && flags[9] == 'S' ? &mx_compare_size : cmp;
    mx_sort_w_list(&(wlists->nonexistent_list), 1, &mx_compare_name, 0);
    mx_sort_w_list(&(wlists->file_list), ascending, cmp, 0);
    mx_sort_w_list(&(wlists->dir_list), ascending, cmp, 1);
    node = wlists->dir_list;
    while (node) {
        mx_sort_w_list(&(((t_dnode *)(node->data))->f_list), ascending, cmp, 0);
        node = node->next;
    }
}

//надо проверить по аудитору как правильно переходить на новую строку
void mx_sort_w_list(t_list **list, int ascending,
        int (*cmp)(t_list *, t_list *, int, int), int is_dir) {
    t_list *nodei;
    t_list *nodej;
    t_list *nodep;

    if (!list || !(*list) || !((*list)->next))
        return;
    nodei = *list;
    while (nodei->next) {
        nodep = nodei;
        nodej = nodei->next;
        while (nodej) {
            if (!((*cmp)(nodep, nodej, ascending, is_dir)))
                nodep = nodej;
            nodej = nodej->next;
        }
        if (nodep != nodei)
             mx_swap(nodei, nodep);
        nodei = nodei->next;
    }
}

void mx_swap(t_list *node1, t_list *node2) {
    mx_swap_mem(&(node1->data), &(node2->data), sizeof(void*));
    mx_swap_mem(&(node1->data_size), &(node2->data_size), sizeof(size_t));
}

void mx_swap_mem(void *s1, void *s2, size_t size) {
    unsigned char *tmp;

    tmp = (unsigned char*)malloc(size * sizeof(unsigned char));
    if (tmp == NULL)
        return;
    mx_memmove(tmp, s1, size);
    mx_memmove(s1, s2, size);
    mx_memmove(s2, tmp, size);
    free(tmp);
}
