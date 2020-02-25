#include "uls.h"

int mx_listlen(t_list *lst) {
    t_list *tmp;
    int i;

    i = 0;
    tmp = lst;
    while (tmp) {
        tmp = tmp->next;
        i++;
    }
    return i;
}


t_list *mx_listnew(void const *data, size_t data_size) {
    t_list *new;

    if (!(new = (t_list *)malloc(sizeof(*new))))
        return (NULL);
    if (!data) {
        new->data = NULL;
        new->data_size = 0;
    }
    else {
        if (!(new->data = (t_list *)malloc(data_size))) {
            free(new);
            return (NULL);
        }
        mx_memcpy(new->data, data, data_size);
        new->data_size = data_size;
    }
    new->next = NULL;
    return new;
}
