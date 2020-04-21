#include "../inc/ush.h"

static char *pwdstr(t_pwdilda **list, char *key) {
    char *adress = NULL;
    t_pwdilda *pl = (*list);

    while (pl) {
        if (mx_strcmp(key, pl->key) == 0)
            adress = mx_strdup(pl->value);
        pl = pl->next;
    }
    return adress;
}

char *mx_tildastr(t_pwdilda **list, char *tilda) {
    char *adress = NULL;

    if (mx_strcmp(tilda, "\0") == 0) {
        if (getenv("HOME") != 0)
            adress = getenv("HOME");
        else
            return adress = mx_strdup("/");
    }
    else if (mx_strcmp(tilda, "+") == 0) {
        if (getenv("PWD") != 0)
            adress = getenv("PWD");
        else
            return adress = pwdstr(list, "PWD");
    }
    else if (mx_strcmp(tilda, "-") == 0) {
        if (getenv("OLDPWD") != 0)
            adress = getenv("OLDPWD");
        else
            return adress = pwdstr(list, "OLDPWD");
    }
    return mx_strdup_x(adress);
}
