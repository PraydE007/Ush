#include "../inc/ush.h"

char *mx_sixteen_ez_fix(char **str, int *size) {
    if ((*size) % 16 == 0) {
        if (mx_buf_push(str, size, ' '))
            exit(1);
    }
    return mx_strdup_x(*str);
}
