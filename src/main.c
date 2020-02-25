#include "uls.h"
 

int main(int argc , char *argv[]) {
    char **input_list;
    char *flags;
    input_list = NULL;

    if (argc == 1) {
        if (mx_no_flags(&input_list) == -1)
            mx_error_exit(NULL, &input_list, &flags);
    }
    else {
        mx_flag_list(&flags, argv);
        if (mx_only_flags(argv,argc)) {
            if (mx_no_flags(&input_list) == -1)
                mx_error_exit(NULL, &input_list, &flags);
        }
        else
            mx_fill_input(&input_list, &flags, argv, argc);
    }
    mx_process(&input_list, &flags);
    mx_free_input(&input_list, &flags);
    return 0;
}
