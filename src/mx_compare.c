#include "uls.h"

int	mx_compare(char const *s1, char const *s2) {
    if (!s1 || !s2)
        return (0);
    return (mx_strcmp(s1, s2) ? 0 : 1);
}

int	mx_compare_name(t_list *node1, t_list *node2, int asc, int is_dir) {
    if (is_dir) {
        if ((asc && mx_strcmp(((t_dnode*)(node1->data))->dir_stats->name,
            (((t_dnode*)(node2->data))->dir_stats)->name) > 0) ||
            (!asc && mx_strcmp(((t_dnode*)(node1->data))->dir_stats->name,
            ((t_dnode*)(node2->data))->dir_stats->name) < 0))
            return 0;
    }
    else
    {
        if ((asc && mx_strcmp(((t_f_stat*)(node1->data))->name,
            ((t_f_stat*)(node2->data))->name) > 0) ||
            (!asc && mx_strcmp(((t_f_stat*)(node1->data))->name,
            ((t_f_stat*)(node2->data))->name) < 0))
            return 0;
    }
    return 1;
}
