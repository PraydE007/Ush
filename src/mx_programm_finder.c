#include "../inc/ush.h"

static char **path_creator(void) {
    char **kv = NULL;
    char **pathes = NULL;

    kv = mx_strsplit(PH, '=');
    pathes = mx_strsplit(kv[1], ':');
    mx_del_strarr(&kv);
    return pathes;
}

static char *strdbljoin(char *s1, char *s2, char *s3) {
    char *buf = NULL;
    char *join = NULL;

    buf = mx_strjoin(s1, s2);
    join = mx_strjoin(buf, s3);
    mx_strdel(&buf);
    return join;
}

char *mx_programm_finder(char *command) {
    struct stat lt;
    char **path = NULL;
    char *programm = NULL;


    path = path_creator();
    for (int i = 0; path[i]; i++) {
        programm = strdbljoin(path[i], "/", command);
        // struct stat lt;
        if (stat(programm, &lt) != -1) {
            if ((lt.st_mode & S_IXUSR) == S_IXUSR) {
                break;
            }
        }
        mx_strdel(&programm);
    }
    mx_del_strarr(&path);
    return programm;
}
