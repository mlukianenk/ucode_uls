#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char * new_dst = dst;
    const char * new_src = src;
    size_t i = 0;
    
    if(new_dst <= new_src) {
        for(i = 0; i < len; i++) {
            new_dst[i] = new_src[i];
        }
    }
    else {
        for (i = len; i > 0; i--) {
            new_dst[i - 1] = new_src[i - 1];
        }
    
    }
    return new_dst;
}
