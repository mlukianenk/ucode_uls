#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *newptr = s;
    
    for (int i = n - 1; i >= 0; i--) {
        if (newptr[i] == (unsigned char) c) 
            return (char *)newptr + i;
     }
    return NULL;
}
