#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const char *string1 = s1;
    const char *string2 = s2;

    while (n--) {
        if (*string1 != *string2) {
            return *string1 - *string2;
        }
        string1++;
        string2++;
    }
    return 0;
}
