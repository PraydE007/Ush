#include "../inc/ush.h"

static char *look_in_path(char *command, char **ways) {
    bool *flag = (bool *)malloc(sizeof(bool) * 3);
    flag[0] = 0;
    flag[1] = 1;
    flag[2] = 0;

    for (int i = 0; ways[i]; i++) {
        char *path = mx_strjoin(ways[i], "/");
        path = mx_strjoin(path, command);
        bool trig = mx_is_command(path, flag, 0);
        if (trig)
            return strdup(path);
    }
    return NULL;
}

char *mx_which_str(char *command) {
    char *path = getenv("PATH");
    char *res = NULL;
    char **ways = mx_strsplit(path, ':');

    res = look_in_path(command, ways);
    mx_del_strarr(&ways);
    return res;
}