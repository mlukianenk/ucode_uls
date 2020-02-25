#include "uls.h"

static void clean_flag_list(char **dirty_flags);

//собираем флаги в массив char *flags;

void mx_flag_list(char **flags, char **argv) {
    char **flag_args; //дубликат массива флагов, который мы получаем из аргв

    *flags = NULL;
    mx_get_flag_args(&flag_args, argv);
    if (!flag_args)
        return;
    mx_flag_args_to_flags(&flag_args, flags);
    mx_strdel(flag_args);
    clean_flag_list(flags);
}

//извлекаем из аргв массив флагов, который запиываем в flag_argument

void mx_get_flag_args(char ***flag_arguments, char **argv) {
    int i = 1;

    while (argv[i] && argv[i][0] == '-')
        i++;
    if (i == 1) {
        *flag_arguments = NULL;
        return;
    }
    if (!(*flag_arguments = (char**)malloc(sizeof(char*) * i)))
        mx_error_exit(NULL, NULL, NULL);
    for (int i = 1; argv[i] && argv[i][0] == '-'; i++) {
        if (!((*flag_arguments)[i - 1] = mx_strnew(mx_strlen(argv[i])))) {
            mx_free_flag_arguments(flag_arguments);
            mx_error_exit(NULL, NULL, NULL);
        }
        (*flag_arguments)[i - 1] = mx_strcpy((*flag_arguments)[i - 1], argv[i]);
    }
    (*flag_arguments)[i - 1] = NULL;
}
 
void mx_flag_args_to_flags(char ***flag_args, char **flags) {
    int i = -1;
    char *tmp;

    while ((*flag_args)[++i]) {
        if (mx_valid_flags((*flag_args)[i])) {
            tmp = mx_strjoin(*flags, (*flag_args)[i]);
            mx_strdel(flags);
            *flags = tmp;
        }
        else {
            mx_error_usage((*flag_args)[i]);
            mx_free_flag_arguments(flag_args);
            mx_error_exit(NULL, NULL, flags);
        }
    }
}

int mx_valid_flags(char *flags) {
    int i;

    if (!flags || flags[1] == '\0')
        return (0);
    i = 1;
    for (int i = 1; flags[i] != '\0'; i++) {
        if (flags[i] != 'r' && flags[i] != 'a' && flags[i] != 'R' &&
            flags[i] != 'l' && flags[i] != 't' && flags[i] != 'g' &&
            flags[i] != 'o' && flags[i] != '1' && flags[i] != 'A' &&
            flags[i] != 'S')
            return 0;
    }
    return 1;
}

static void clean_flag_list(char **dirty_flags) {
    char *clean_flags;
    int i = 0;

    if (!(clean_flags = mx_strnew(11)))
        mx_error_exit(NULL, NULL, dirty_flags);
    mx_memset((void*)clean_flags, '_', 11);
    while ((*dirty_flags)[i]) {
        mx_check_sort_flags(&clean_flags, (*dirty_flags)[i]);
        mx_check_display_flags(&clean_flags, (*dirty_flags)[i]);
        clean_flags[0] = (*dirty_flags)[i] == 'R' ? 'R' : clean_flags[0];
        i++;
    }
    mx_strdel(dirty_flags);
    *dirty_flags = clean_flags;
}
