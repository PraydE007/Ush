#include "../inc/libmx.h"

char *mx_strdup_x(const char *str) {
    char *copy = NULL;

    copy = mx_strnew_x(mx_strlen(str) + 1);
    if (copy == NULL)
        return NULL;
    else
        copy = mx_strcpy(copy, str);
    return copy;
}
