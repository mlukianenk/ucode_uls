#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *new_b = b;

    while(len--) {
        *new_b++ = (unsigned char) c;
    }
    return b;
}
