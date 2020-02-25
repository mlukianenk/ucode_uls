#include "uls.h"

void mx_init_wlist(t_wlists *wlists) {
    wlists->dir_list = NULL;
    wlists->file_list = NULL;
    wlists->nonexistent_list = NULL;
}
