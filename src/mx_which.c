#include "../inc/ush.h"

static void printer(char *way, char *command) {
    mx_printstr(way);
    mx_printchar('/');
    mx_printstr(command);
    mx_printchar('\n');
}

static char *look_in_path(t_ush *ush, char **ways, char *command, bool flag_a) {
    struct dirent *lupa = NULL;
    bool trig = 0;
    bool a = 0;
    DIR *directory = NULL;

    for (int i = 0; ways[i]; i++) {
        directory = opendir(ways[i]);
        while ((lupa = readdir(directory)) != NULL) {
            if (mx_strcmp(lupa->d_name, ".") && mx_strcmp(lupa->d_name, "..")
                && !mx_strcmp(lupa->d_name, command)) {
                printer(ways[i], command);
                trig = 1;
                if (!flag_a) {
                    a = 1;
                    break;
                }
            }
        }
        closedir(directory);
        if (a)
            break;
    }
    if (trig == 0) {
        mx_printerr(command);
        mx_printerr(" not found\n");
        ush->exit_code = 1;
    }
    return NULL;
}

void mx_which(t_ush *ush, char **env, char **command) {
    char *path = getenv("PATH");
    bool flag_a = 0;
    bool flag_s = 0;
    int i = 1;

    for (; command[i]; i++) {
        if (command[i][0] == '-') {
            for (int j = 1; command[i][j]; j++) {
                if (command[i][j] == 'a')
                    flag_a = 1;
                else if (command[i][j] == 's')
                    flag_s = 1;
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
    if (command[i]) {
        if (path) {
            char **ways = mx_strsplit(path, ':');
            look_in_path(ush, ways, command[i], flag_a);
            mx_del_strarr(&ways);
        }
    }
    else if (i < 2) {
        mx_printerr("usage: which [-as] program ...\n");
        ush->exit_code = 1;
    }
//    free(path);
}
