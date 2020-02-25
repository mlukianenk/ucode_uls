#include "uls.h"

//АУДИТОР
int mx_compare_time(t_list *node1, t_list *node2, int asc, int is_dir) {
    if (is_dir) {
        if ((((t_dnode*)(node1->data))->dir_stats)->last_modification ==
            (((t_dnode*)(node2->data))->dir_stats)->last_modification)
            return (mx_compare_name(node1, node2, asc, is_dir));
        if ((asc &&
            ((((t_dnode*)(node1->data))->dir_stats)->last_modification <
            (((t_dnode*)(node2->data))->dir_stats)->last_modification)) ||
            (!asc &&
            ((((t_dnode*)(node1->data))->dir_stats)->last_modification >
            (((t_dnode*)(node2->data))->dir_stats)->last_modification)))
            return 0;
    }
    else 
    {
        if (((t_f_stat*)(node1->data))->last_modification ==
            ((t_f_stat*)(node2->data))->last_modification)
            return (mx_compare_name(node1, node2, asc, is_dir));
        if ((asc && ((t_f_stat*)(node1->data))->last_modification <
            ((t_f_stat*)(node2->data))->last_modification) ||
            (!asc && ((t_f_stat*)(node1->data))->last_modification >
            ((t_f_stat*)(node2->data))->last_modification))
            return 0;
    }
    return 1;
}
