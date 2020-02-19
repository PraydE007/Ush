#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *p_s = (char *) s;

    for (size_t i = n; i > 0; i--) {
        if (p_s[i] == c) {
            return &p_s[i];
        }
    }
    return NULL;
}
