#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *copy = NULL;

    copy = mx_strnew(n);
    if (copy  == NULL)
        return NULL;
    else
        mx_strncpy(copy, s1, n);
    return copy;
}
