#include "uls.h"

void mx_print_formatted_list(t_list *list, t_c_widths *cwidths, char *flags) {
    t_list *node;

    node = list;
    while (node) {
        mx_print_per_lc_usr_grp(((t_f_stat*)(node->data)), cwidths, flags);
        mx_print_file_size(((t_f_stat*)(node->data)), cwidths);
        mx_print_l_modif(((t_f_stat*)(node->data))->last_modification);
        mx_printstr(" ");
        mx_printstr(((t_f_stat*)(node->data))->name);
        if (((t_f_stat*)(node->data))->file_type == 'l') {
            mx_printstr(" -> ");
            mx_printstr(((t_f_stat*)(node->data))->link);
        }
        mx_printchar('\n');
        node = node->next;
    }
}

void mx_print_per_lc_usr_grp(t_f_stat *f_stat, t_c_widths *cwidths, char *flags) {
    mx_printstr(f_stat->permissions);
    mx_printstr(" ");
    mx_putnbr_w(f_stat->link_count, cwidths->lc_width);
    mx_printstr(" ");
    if (!flags || flags[5] != 'g') {
        mx_putstr_w(f_stat->user, cwidths->uid_width, 1);
        mx_printstr("  ");
    }
    if (!flags || flags[6] != 'o') {
        mx_putstr_w(f_stat->group,
                cwidths->group_width, 1);
        mx_printstr("  ");
    }
    if (flags && flags[5] == 'g' && flags[6] == 'o')
        mx_printstr("  ");
}

void mx_print_file_size(t_f_stat *f_stat, t_c_widths *cwidths) {
    if (f_stat->file_type == 'b' || f_stat->file_type == 'c') {
        mx_putnbr_w(f_stat->major, mx_max(3, cwidths->longest_major));
        mx_printchar(',');
        mx_putnbr_w(f_stat->minor, mx_max(4, cwidths->fs_width));
    }
    else if (cwidths->longest_major != 0)
        mx_putnbr_w(f_stat->file_size, mx_max(4, cwidths->fs_width) +
            mx_max(3, cwidths->longest_major) + 1);
    else
        mx_putnbr_w(f_stat->file_size, cwidths->fs_width);
    mx_printstr(" ");
}

int mx_max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

void mx_print_l_modif(time_t lm) {
    char *str;
    time_t ct;

    if (!(str = mx_strnew(24)))
        return;
    if (!(str = mx_strdup(ctime(&lm))))
        return;
    ct = time(0);
    if (mx_put_abs(ct - lm) > SEC_IN_SIX_MONTHS) {
        str[11] = '\0';
        str[24] = '\0';
        mx_printstr(str + 4);
        mx_printstr(str + 19);
    }
    else {
        str[16] = '\0';
        mx_printstr(str + 4);
    }
    mx_strdel(&str);
}
