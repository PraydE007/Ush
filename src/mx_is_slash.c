#include "../inc/ush.h"

bool mx_is_slash(char *path) {
    bool res = 0;

    for (int i = 0; path[i]; i++)
        if (path[i] == '/')
            res = 1;
    return res;
}
