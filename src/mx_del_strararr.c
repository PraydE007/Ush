#include "../inc/ush.h"

void mx_del_strararr(char ****arr) {
    char ***parr = &(**arr);

    if (parr != NULL) {
        for (int i = 0; parr[i] != NULL; i++)
            mx_del_strarr(&parr[i]);
        free(*arr);
        *arr = NULL;
    }
}
