#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *new_dst = (char *)dst;
    char *new_src = (char *)src;


    for (size_t i = 0; i < n; i++) {
        new_dst[i] = new_src[i];
    }
    return dst;
}
