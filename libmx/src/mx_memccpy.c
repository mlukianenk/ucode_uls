#include "libmx.h"
 
void *mx_memccpy(void *restrict dst, const void *restrict src,
int c, size_t n) {
    for (;n>0;n--) {
    if (n) {
        register unsigned char *new_dst = dst;
        register const unsigned char *new_src = src;
        if ((*new_dst++ = *new_src++) == c)
        return dst;
        }
    }
    return 0;
} 
