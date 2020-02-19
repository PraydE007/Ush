#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *buf = NULL;
    char *p_src = (char *) src;
    char *p_dst = (char *) dst;

    buf = (char *)malloc(sizeof(char)*len);
    mx_memcpy(buf, p_src, len);
    mx_memcpy(p_dst, buf, len);
    free(buf);
    return dst;
}
