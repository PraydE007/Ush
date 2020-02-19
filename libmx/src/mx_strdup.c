#include "libmx.h"

char *mx_strdup(const char *str) {
    char *copy = NULL;

    copy = mx_strnew(mx_strlen(str));
    if (copy == NULL)
        return NULL;
    else
        copy = mx_strcpy(copy, str);
    return copy;
}
