#include "ush.h"

int mx_buf_drop(char **buf, int *buf_size) {
    if ((*buf_size) > 1) {
        (*buf)[(*buf_size) - 2] = '\0';
        (*buf_size) -= 1;
        (*buf) = (char *)realloc((*buf), (*buf_size));
        if (!(*buf)) {
            fprintf(stderr, "%s", MX_EBFLOC);
            return 1;
        }
    }
    return 0;
}
