#include "../inc/libmx.h"

char *mx_strdup_x(const char *str) {
    char *copy = NULL;

    if (!str)
        return NULL;
    copy = mx_strnew_x(mx_strlen(str) + 1);
    if (copy)
        copy = mx_strcpy(copy, str);
    return copy;
}
