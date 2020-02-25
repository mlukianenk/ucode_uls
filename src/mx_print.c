#include "uls.h"

void mx_printlast(char const *s) {
    if (s) 	{
        write(1, s, mx_strlen(s));
        mx_printchar('\n');
    }
}

//как переносить 1 строку
void mx_print_dir_content(t_list *dir_list, int format, int with_title,
        char *flags) {
    t_list *dnode;
    t_c_widths cwidths;

    dnode = dir_list;
    while (dnode) {
        if (with_title) {
            if (dnode != dir_list) {
                mx_printlast("");
                mx_printstr((((t_dnode*)(dnode->data))->dir_stats)->path);
                mx_printlast(":");
            }
        }
        if ((((t_dnode*)(dnode->data))->dir_stats)->permissions[1] == '-') { //как тут переносить?
            mx_set_errno_to_nopermission((((t_dnode*)(dnode->data))->
                        dir_stats)->path);
            mx_set_perror((((t_dnode*)(dnode->data))->dir_stats)->name);
        }
        mx_print_content_with_format(dnode, format, &cwidths, flags);
        dnode = dnode->next;
    }
}

void mx_print_content_with_format(t_list *dnode, int format,
        t_c_widths *cwidths, char *flags) {
    t_list *node;

    if (!format) {
        node = ((t_dnode*)(dnode->data))->f_list;
        while (node) {
            mx_printlast(((t_f_stat*)(node->data))->name);
            node = node->next;
        }
    }
    else {
        mx_print_total(((t_dnode*)(dnode->data))->f_list);
        mx_fill_c_widths(((t_dnode*)(dnode->data))->f_list, cwidths);
        mx_print_formatted_list(((t_dnode*)(dnode->data))->f_list, cwidths,
                flags);
    }
}

void mx_print_total(t_list *f_list) {
    int total;

    if (!f_list)
        return ;
    total = 0;
    while (f_list) {
        total += ((t_f_stat*)(f_list->data))->blocks_allocated;
        f_list = f_list->next;
    }
    mx_printstr("total ");
    mx_putnbr(total);
    mx_printlast("");
}
