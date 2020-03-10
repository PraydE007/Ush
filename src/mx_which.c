#include "../inc/ush.h"

static bool is_slash(char *path) {
    bool res = 0;

    for (int i = 0; path[i]; i++)
        if (path[i] == '/')
            res = 1;
    return res;
}

static void print_not_found(char *command, t_ush *ush) {
    mx_printerr(command);
    mx_printerr(" not found\n");
    ush->exit_code = 1;
}

static bool look_in_path(t_ush *ush, char **ways, char *command, bool *flag) {
    bool a = 0;
    bool trig = 0;

    for (int i = 0; ways[i]; i++) {
        if (is_slash(command))
            a = mx_is_command(command, flag, 0);
        else {
            char *path = mx_strjoin(ways[i], "/");
            a = mx_is_command(mx_strjoin_free(path, command), flag, 0);
        }
        if (a == 1) {
            if (!flag[0])
                return a;
            else
                trig = 1;
        }
    }
    if (trig == 0)
        print_not_found(command, ush);
    return a;
}

static int flag_parser(char **command, t_ush *ush, bool *flag) {
    int i = 1;

    for (; command[i]; i++) {
        if (command[i][0] == '-') {
            for (int j = 1; command[i][j]; j++) {
                if (command[i][j] == 'a')
                    flag[0] = 1;
                else if (command[i][j] == 's')
                    flag[1] = 1;
                else {
                    mx_printerr("which: bad option: -");
                    write(2, &command[i][j], 1);
                    mx_printerr("\n");
                    ush->exit_code = 1;
                }
            }
        }
        else
            break;
    }
    return i;
}

void mx_which(t_ush *ush, char **command) {
    char *path = getenv("PATH");
    bool *flag = (bool *)malloc(sizeof(bool) * 2);
    char **ways = mx_strsplit(path, ':');
    int i = flag_parser(command, ush, flag);

    for (; command[i];) {
        if (mx_is_built_in(command[i]) && !flag[1])
            printf("%s: shell built-in command\n", command[i]);
        if (!mx_is_built_in(command[i]) || (mx_is_built_in(command[i])
            && flag[0]))
            look_in_path(ush, ways, command[i], flag);
        i++;
    }
    if (i < 2) {
        mx_printerr("usage: which [-as] program ...\n");
        ush->exit_code = 1;
    }
    free(flag);
    mx_del_strarr(&ways);
}