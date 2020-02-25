#include "uls.h"

//АУДИТОР
int mx_compare_size(t_list *node1, t_list *node2, int asc, int is_dir) {
    if (is_dir)
    {
        if ((((t_dnode*)(node1->data))->dir_stats)->file_size ==
            (((t_dnode*)(node2->data))->dir_stats)->file_size)
            return (mx_compare_name(node1, node2, asc, is_dir));
        if ((asc &&
            ((((t_dnode*)(node1->data))->dir_stats)->file_size <
            (((t_dnode*)(node2->data))->dir_stats)->file_size)) ||
            (!asc &&
            ((((t_dnode*)(node1->data))->dir_stats)->file_size >
            (((t_dnode*)(node2->data))->dir_stats)->file_size)))
            return 0;
    }
    else
    {
        if (((t_f_stat*)(node1->data))->file_size ==
            ((t_f_stat*)(node2->data))->file_size)
            return (mx_compare_name(node1, node2, asc, is_dir));
        if ((asc && ((t_f_stat*)(node1->data))->file_size <
            ((t_f_stat*)(node2->data))->file_size) ||
            (!asc && ((t_f_stat*)(node1->data))->file_size >
            ((t_f_stat*)(node2->data))->file_size))
            return 0;
    }
    return 1;
}




