#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *p_b = (char *) b;

    for (size_t i = 0; i < len; i++)
        *p_b++ = c;
    return b;
}
