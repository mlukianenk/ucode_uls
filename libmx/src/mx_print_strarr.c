#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    
    if(!arr || !delim || !*arr) return;
        
    while(*arr) {
        mx_printstr(*arr);
        if (*(arr + 1)) {
            mx_printstr(delim);
        }
        arr++;
    }
    mx_printchar('\n');
}
