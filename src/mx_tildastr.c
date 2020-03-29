#include "../inc/ush.h"

char *mx_tildastr(char *tilda) {
    char *adress = NULL;

    if (mx_strcmp(tilda, "\0") == 0)
        adress = getenv("HOME");
    else if (mx_strcmp(tilda, "+") == 0)
        adress = getenv("PWD");
    else if (mx_strcmp(tilda, "-") == 0)
        adress = getenv("OLDPWD");
    return mx_strdup_x(adress);
}
