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

static bool is_getnv(char **adress, char *variable) {
    if (!mx_strcmp(variable, "HOME") && getenv(variable) != 0) {
        (*adress) = mx_strdup_x(getenv("HOME"));
        return true;
    }
    else if (!mx_strcmp(variable, "PWD") && getenv(variable) != 0) {
        (*adress) = mx_strdup_x(getenv("PWD"));
        return true;
    }
    else if (!mx_strcmp(variable, "OLDPWD") && getenv(variable) != 0) {
        (*adress) = mx_strdup_x(getenv("OLDPWD"));
        return true;
    }
    return false;
}

char *mx_tildastr(t_pwdilda **list, char *tilda) {
    char *adress = NULL;

    if (mx_strcmp(tilda, "\0") == 0) {
        if (!is_getnv(&adress, "HOME"))
            adress = mx_strdup(" ");
    }
    else if (mx_strcmp(tilda, "+") == 0) {
        if (!is_getnv(&adress, "PWD"))
            adress = pwdstr(list, "PWD");
    }
    else if (mx_strcmp(tilda, "-") == 0) {
        if (!is_getnv(&adress, "OLDPWD"))
            adress = pwdstr(list, "OLDPWD");
    }
    return adress;
}
