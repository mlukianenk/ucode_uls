#ifndef ULS_H
#define ULS_H

#include "./libmx/inc/libmx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
 
#define SEC_IN_SIX_MONTHS 15778463
#define ERR_USAGE "usage: uls [-1ASRaglort] [file ...]"

#define MX_GETMAJ(x)     ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
#define MX_GETMIN(x)     ((int32_t)((x) & 0xffffff))

typedef struct s_f_stat
{
    char *name;
    char *path;
    char file_type;
    char *link;
    char *permissions;
    long link_count;
    char *user;
    char *group;
    unsigned int minor;
    unsigned int major;
    long long file_size;
    long long blocks_allocated;
    time_t last_modification;

} t_f_stat;

typedef struct s_wlists {
    t_list *dir_list;
    t_list *file_list;
    t_list *nonexistent_list;
} t_wlists;

typedef struct s_dnode {
    t_f_stat *dir_stats;
    t_list *f_list;
} t_dnode;

typedef struct	s_mc_list {
    int columns;
    int rows;
    int lst_len;
    int lm;
    int max;
} t_mc_list;

typedef struct	s_c_widths {
    int lc_width;
    int uid_width;
    int group_width;
    int fs_width;
    int longest_major;
} t_c_widths;

//mx_append.c
void mx_append_lst(t_list **alst, t_list *new);
char *mx_append_path(char *firstpath, char *secondpath);

//mx_check_flags.c
void mx_check_display_flags(char **flags, char c);
void mx_check_sort_flags(char **flags, char c);

//mx_compare_size.c
int	mx_compare_size(t_list *node1, t_list *node2, int asc, int is_dir);

//mx_compare_time.c
int mx_compare_time(t_list *node1, t_list *node2, int asc, int is_dir);

//mx_compare.c
int mx_compare(char const *s1, char const *s2);
int	mx_compare_name(t_list *node1, t_list *node2, int asc, int is_dir);

//mx_create_and_append_dnode.c
void mx_create_and_append_dnode(t_dnode *new_dnode, t_list *new_node, t_wlists *wlists, t_f_stat *dir);

//mx_errors.c
void mx_error_exit(char *err_msg, char ***file_list, char **flags);
void mx_error_usage(char *invalid_flag_args);

//mx_fill_c_widths.c
void mx_fill_c_widths(t_list *f_list, t_c_widths *cwidths);
int mx_intlen(int n);

//mx_fill_file.c
int mx_fill_file_stat(t_f_stat **file_stat, struct stat file_info);
int mx_fill_file_stat_sq(t_f_stat **file_stat, struct stat file_info);

//mx_fill_input.c
void mx_fill_input(char ***file_list, char **flags, char **argv, int argc);

//mx_flags_basic.c
int mx_no_flags(char ***input_list);
int mx_only_flags(char **argv, int argc);

//mx_flags.c
void mx_flag_list(char **flags, char **argv);
void mx_get_flag_args(char ***flag_arguments, char **argv);
void mx_flag_args_to_flags(char ***flag_args, char **flags);
int mx_valid_flags(char *flags);

//mx_free_wlists.c
void mx_free_wlists(t_wlists *wlists);
void mx_free_file_obj(t_f_stat **file_stat);

//mx_free.c
void mx_free_input(char ***file_list, char **flags);
void mx_free_flag_arguments(char ***flag_arguments);

//mx_get_dir_stat.c
t_list *mx_get_dir_stat(char *path, char *flags);
t_list *mx_get_file_stat(char *path, char *flags, int isarg);
char *mx_get_filename(char *path);

//mx_get_f_stat.c
t_list *mx_get_f_stat(char *path, char *flags, int isarg);

//mx_get_file.c
char *mx_get_file_permissions(mode_t st_mode, char *filename);
char mx_get_file_type(mode_t st_mode);
char mx_get_xattr_or_acl(char *filename);

//mx_get.c
int mx_get_max_filename_length(t_list *list);
int mx_get_lm(int n);
int mx_get_terminal_width(void);
void mx_get_mc_list_stats(t_list *list, int col, t_mc_list *mc_list);

//mx_init_wlist.c
void mx_init_wlist(t_wlists *wlists);

//mx_is_hidden.c
int mx_is_hidden(char *filename);

//mx_lists.c
int mx_listlen(t_list *lst);
t_list *mx_listnew(void const *data, size_t data_size);

//mx_new_file_stat.c
t_f_stat *mx_new_file_stat(char *path, char *name);

//mx_print_formatted_list.c
void mx_print_formatted_list(t_list *list, t_c_widths *cwidths, char *flags);
void mx_print_per_lc_usr_grp(t_f_stat *f_stat, t_c_widths *cwidths, char *flags);
void mx_print_file_size(t_f_stat *f_stat, t_c_widths *cwidths);
int mx_max(int a, int b);
void mx_print_l_modif(time_t lm);

//mx_print_multi_column.c
void mx_print_multi_column(t_wlists *wlists);
void mx_print_multi_column_list(t_list *list, t_mc_list *mc_list);
void mx_print_multi_column_dlist(t_list *dlist, int col, int unique_dir);

//mx_print_stats.c
void mx_print_nonexistent(t_list *list);
void mx_print_stats(t_wlists *wlists, char *flags);
void mx_print_long_format(t_wlists *wlists, char *flags);
void mx_print_single_column(t_wlists *wlists, char *flags);

//mx_print.c
void mx_printlast(char const *s);
void mx_print_dir_content(t_list *dir_list, int format, int with_title, char *flags);
void mx_print_content_with_format(t_list *dnode, int format, t_c_widths *cwidths, char *flags);
void mx_print_total(t_list *f_list);

//mx_process.c
void mx_process(char ***files, char **flags);

//mx_put.c
void mx_putnbr_w(int n, int width);
void mx_putnbr(int n);
void mx_putstr_w(char *str, int width, int start);
long long mx_put_abs(long long nbr);

//mx_recursive.c
void mx_recursive(t_wlists *wlists, char *flags);
void mx_single_stream_recursion(t_list *flist, char *flags);
void mx_recursive_lookthrough(t_f_stat *dir, char *flags);
void mx_multi_stream_recursion(t_wlists *wlists, char *flags);

//mx_set_error.c
void mx_set_errno_to_nsfod(char *filename);
void mx_set_errno_to_nopermission(char *dirname);
void mx_set_perror(char *str);

//mx_sort.c
void mx_sort(t_wlists *wlists, char *flags);
void mx_sort_w_list(t_list **list, int ascending, int (*cmp)(t_list *, t_list *, int, int), int is_dir);
void mx_swap(t_list *node1, t_list *node2);
void mx_swap_mem(void *s1, void *s2, size_t size);

#endif
