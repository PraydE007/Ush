#include "../inc/ush.h"

char *mx_buf_safe_realloc(char *src, int *size) {
    char *res = NULL;

    if ((*size) % 16 == 0)
        (*size) += 1;
    res = realloc(NULL, (*size));
    res = mx_strcpy(res, src);
    res[(*size) - 1] = '\0';
    return res;
}
