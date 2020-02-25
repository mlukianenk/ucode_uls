#include "uls.h"

//АУДИТОР
char *mx_get_file_permissions(mode_t st_mode, char *filename) {
    char *permissions;

    if (!(permissions = mx_strnew(11)))
        return (NULL);
    permissions[0] = mx_get_file_type(st_mode);
    permissions[1] = st_mode & S_IRUSR ? 'r' : '-';
    permissions[2] = st_mode & S_IWUSR ? 'w' : '-';
    permissions[3] = st_mode & S_IXUSR ? 'x' : '-';
    permissions[4] = st_mode & S_IRGRP ? 'r' : '-';
    permissions[5] = st_mode & S_IWGRP ? 'w' : '-';
    permissions[6] = st_mode & S_IXGRP ? 'x' : '-';
    permissions[7] = st_mode & S_IROTH ? 'r' : '-';
    permissions[8] = st_mode & S_IWOTH ? 'w' : '-';
    permissions[9] = st_mode & S_IXOTH ? 'x' : '-';
    permissions[10] = mx_get_xattr_or_acl(filename);
    if (st_mode & S_ISUID)
        permissions[3] = (st_mode & S_IXUSR) ? 's' : 'S';
    if (st_mode & S_ISGID)
        permissions[6] = (st_mode & S_IXGRP) ? 's' : 'S';
    if (st_mode & S_ISVTX)
        permissions[9] = (st_mode & S_IXOTH) ? 't' : 'T';
    return (permissions);
}

char mx_get_file_type(mode_t st_mode) {
    if ((st_mode & S_IFMT) == S_IFBLK)
        return ('b');
    else if ((st_mode & S_IFMT) == S_IFCHR)
        return ('c');
    else if ((st_mode & S_IFMT) == S_IFDIR)
        return ('d');
    else if ((st_mode & S_IFMT) == S_IFIFO)
        return ('p');
    else if ((st_mode & S_IFMT) == S_IFLNK)
        return ('l');
    else if ((st_mode & S_IFMT) == S_IFSOCK)
        return ('s');
    else if ((st_mode & S_IFMT) == S_IFREG)
        return ('-');
    else
        return ('?');
}

char mx_get_xattr_or_acl(char *filename) {
    acl_t acl;

    if (listxattr(filename, NULL, 0, XATTR_NOFOLLOW) > 0)
        return ('@');
    acl = acl_get_file(filename, ACL_TYPE_EXTENDED);
    if (acl)
        return ('+');
    return (' ');
}
