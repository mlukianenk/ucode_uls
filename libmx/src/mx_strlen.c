#include "libmx.h"

int mx_strlen(const char *s) {
    int i = 0;
    if (!s) {
        return -1;
    }
    for (; s[i] != '\0'; i++);
    return i;
} 
