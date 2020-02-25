#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    if(*needle == '\0')
        return (char*) haystack;

    for (int i = 0; i < mx_strlen(haystack); i++) {
            if (*(haystack + i) == *needle) {
                char *ptr = mx_strstr(haystack + i + 1, needle + 1);
                return (ptr) ? ptr -1 : NULL;
            }	

    }
    return NULL;
}

