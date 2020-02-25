#include "uls.h"

int mx_is_hidden(char *filename) {
    int i;

    i = mx_strlen(filename) - 1;
    while (i > 0 && filename[i] != '/')
        i--;
    return (filename[i + 1] == '.');
}
