#include "../inc/ush.h"

int mx_count_slashes(char *str) {
    int len = 0;

    for (len = 0; len < 4 && str[len] == '\\'; len++);
    return len;
}
