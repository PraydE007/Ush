 #include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src,
                                                            int c, size_t n) {
    char *p_dst = (char *) dst;
    char *p_src = (char *) src;
    size_t i;

    for (i = 0; i < n; i++) {
        p_dst[i] = p_src[i];
        if (p_src[i] == c)
            break;
    }
    if (i == n)
        return NULL;
    i++;
    return p_dst + i;
}
