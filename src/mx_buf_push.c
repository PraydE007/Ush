#include "../inc/ush.h"

int mx_buf_push(char **buf, int *buf_size, char ch) {
    (*buf_size) += 1;
    (*buf) = (char *)realloc(*buf, (*buf_size));
    if (!(*buf)) {
        fprintf(stderr, "%s", MX_EBFLOC);
        return 1;
    }
    (*buf)[*buf_size - 1] = '\0';
    (*buf)[(*buf_size) - 2] = ch;
    return 0;
}
