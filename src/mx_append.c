#include "uls.h"

void mx_append_lst(t_list **alst, t_list *new) {
    t_list *list;

    if (alst != NULL) {
        if (*alst == NULL)
            *alst = new;
        else {
            list = *alst;
            while (list->next != NULL)
                list = list->next;
            list->next = new;
        }
    }
}

char *mx_append_path(char *firstpath, char *secondpath) {
    char *str;
    char *temp;

    if (!(temp = mx_strjoin(firstpath, "/")))
        return NULL;
    if (!(str = mx_strjoin(temp, secondpath)))
        return NULL;
    mx_strdel(&temp);
    return str;
}
