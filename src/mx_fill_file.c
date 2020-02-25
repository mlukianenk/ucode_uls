#include "uls.h"

int mx_fill_file_stat(t_f_stat **file_stat, struct stat file_info) {
    struct passwd *pwd;
    struct group *grp;

    if (!((*file_stat)->permissions = mx_get_file_permissions(file_info.st_mode,
                    (*file_stat)->path))) {
        mx_strdel(&((*file_stat)->permissions));
        return (-1);
    }
    (*file_stat)->file_type = (*file_stat)->permissions[0];
    if ((pwd = getpwuid(file_info.st_uid)) != NULL) {
        if (!((*file_stat)->user = mx_strdup(pwd->pw_name)))
            return (-1);
    }
    else if ((!((*file_stat)->user = mx_strdup(mx_itoa(file_info.st_uid)))))
        return (-1);
    if ((grp = getgrgid(file_info.st_gid)) != NULL) {
        if (!((*file_stat)->group = mx_strdup(grp->gr_name)))
            return (-1);
    }
    else if (!((*file_stat)->group = mx_strdup(mx_itoa(file_info.st_gid))))
        return (-1);
    return (mx_fill_file_stat_sq(file_stat, file_info));
}

//АУДИТОР
int mx_fill_file_stat_sq(t_f_stat **file_stat, struct stat file_info) {
    ssize_t r;

    (*file_stat)->link_count = file_info.st_nlink;
    (*file_stat)->file_size = file_info.st_size;
    (*file_stat)->blocks_allocated = file_info.st_blocks;
    (*file_stat)->minor = MX_GETMIN(file_info.st_rdev);
    (*file_stat)->major = MX_GETMAJ(file_info.st_rdev);
    if ((*file_stat)->file_type == 'l') {
        (*file_stat)->link = mx_strnew(file_info.st_size + 1);
        r = readlink((*file_stat)->path,
                (*file_stat)->link, file_info.st_size + 1);
        if (r < 0 || r > file_info.st_size) {
            mx_strdel(&((*file_stat)->link));
            (*file_stat)->link = mx_strnew(23);
            mx_strcpy((*file_stat)->link, "error: target not found");
        }
        else
            (*file_stat)->link[file_info.st_size] = '\0';
    }
    else
        (*file_stat)->link = NULL;
    (*file_stat)->last_modification = file_info.st_mtime;
    return 1;
}
