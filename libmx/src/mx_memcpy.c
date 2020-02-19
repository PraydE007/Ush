#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *p_dst = (char *) dst;
    char *p_src = (char *) src;

    for (size_t i = 0; i < n; i++)
        p_dst[i] = p_src[i];
    return dst;
}
