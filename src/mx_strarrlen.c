#include "../inc/ush.h"

int mx_strarrlen(char **arr) {
    int i = 0;

    if (arr == NULL)
        return 0;
    while (arr[i] != NULL)
        i++;
    return i;
}
