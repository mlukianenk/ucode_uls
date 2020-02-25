#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL) { 
        return NULL;
    }	
    int len = mx_strlen(str);
    int begin;
 
    for (begin = 0; mx_is_space(str[begin]); begin++);
    if (begin >= len) {
        char *empty = (char *) malloc(sizeof(char)* 1);
        empty[0] = '\0';
        return empty;
    }
    int end;
    for (end = 0; mx_is_space(str[len - 1 -  end]) && end < len; end++);
    const char * start = str + begin;
    char *trim = mx_strndup(start, len - begin - end);
    return trim;
}
