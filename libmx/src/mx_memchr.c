#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *newptr = (unsigned char *) s;

    for (size_t i = 0 ; i < n; i++)
        if (newptr[i] == c) 
    return (void*)&newptr[i];  
        
    return NULL;
}
