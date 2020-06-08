#include "../inc/ush.h"
//CHECK COMMENTS
char *mx_sixteen_ez_fix(char **str, int *size) {
    int real_siz = 0;
    char *res = NULL;

    if ((*size) % 16 == 0) {
        real_siz = (*size) / 16;
        (*str) = (char *)realloc(*str, real_siz * 16 + 1);
        (*str)[real_siz * 16] = '\0';
    }
    res = mx_strdup_x(*str);
    return res;
}

// char *mx_sixteen_ez_fix(char **str, int *size) {
//     if ((*size) % 16 == 0) {
//         if (mx_buf_push(str, size, ' '))
//             exit(1);
//     }
//     return mx_strdup_x(*str);
// }
