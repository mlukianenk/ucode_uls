#include "uls.h" 

static int is_dir(char *path);
static int is_nonexistent(t_list *node);
static void process_dir(char *dirpath, char *flags, t_wlists *wlists);

void mx_process(char ***files, char **flags) {
    int i = -1;
    t_wlists wlists;
    t_list *new_node;

    mx_init_wlist(&wlists);
    while ((*files)[++i]) {
        if (is_dir((*files)[i]))
            process_dir((*files)[i], *flags, &wlists);
        else if ((new_node = mx_get_file_stat((*files)[i], *flags, 1))) {
            if (is_nonexistent(new_node))
                mx_append_lst(&(wlists.nonexistent_list), new_node);
            else
                mx_append_lst(&(wlists.file_list), new_node);
        }
    }
    mx_recursive(&wlists, *flags);
    mx_free_wlists(&wlists);
}

static int is_dir(char *path) {
    struct stat file_info;

    if (lstat(path, &file_info) == 0)
        if ((file_info.st_mode & S_IFMT) == S_IFDIR)
            return 1;
    return 0;
}

static int is_nonexistent(t_list *node) {
    return (((t_f_stat*)(node->data))->file_type == 'X');
}

static void process_dir(char *dirpath, char *flags, t_wlists *wlists) {
    t_list	*new_node;
    t_dnode	*new_dnode;

    new_node = mx_get_dir_stat(dirpath, flags);
    if ((new_dnode = (t_dnode*)malloc(sizeof(t_dnode)))) {
        new_dnode->f_list = new_node;
        if ((new_node = mx_get_file_stat(dirpath, flags, 1))) {
            new_dnode->dir_stats = (t_f_stat*)(new_node->data);
            free(new_node);
        }
        new_node = mx_listnew(NULL, 0);
        new_node->data = new_dnode;
        new_node->data_size = sizeof(new_dnode);
        mx_append_lst(&(wlists->dir_list), new_node);
    }
}
