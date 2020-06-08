#include "../inc/ush.h"

static void home_log_creation(char *dir) {
    char *buf = NULL;
    char *home = NULL;
    char *log = NULL;
    int i = 1;

    log = getlogin();
    for (; dir[i] != '/'; i++);
    buf = mx_strnew(i + 2);
    i = 1;
    buf[0] = '/';
    for (; dir[i] != '/'; i++)
        buf[i] = dir[i];
    buf[i] = '/';
    home = mx_strjoin_free(buf, log);
    setenv("HOME", home, 1);
    setenv("LOGNAME", log, 1);
    mx_strdel(&log);
    mx_strdel(&home);
}

static void pwd_oldpwd_creation(t_ush *ush, char *dir) {
    char **kv = NULL;

    if (getenv("PWD") == 0)
        setenv("PWD", dir, 1);
    setenv("OLDPWD", dir, 1);
    mx_push_back_pwdilda(&ush->pwdilda_list, "PWD", dir);
    mx_push_back_pwdilda(&ush->pwdilda_list, "OLDPWD", dir);
    if (getenv("PATH") == 0) {
        kv = mx_key_value_creation(ush, PH);
        mx_push_back_variable(&ush->variable_list, kv);
        mx_del_strarr(&kv);
    }
}

void mx_constant_variables(t_ush *ush) {
    char dir[256];
    char *buf = NULL;
    int store = 0;

    getcwd(dir, 256);
    if (getenv("HOME") == 0 || getenv("LOGNAME") == 0)
        home_log_creation(dir);
    if (getenv("SHLVL") == 0)
        setenv("SHLVL", "1", 1);
    else {
        buf = getenv("SHLVL");
        store = mx_atoi(buf);
        store++;
        buf = mx_itoa(store);
        setenv("SHLVL", buf, 1);
        mx_strdel(&buf);
    }
    pwd_oldpwd_creation(ush,dir);
    setenv("_", "/usr/bin/env", 1);
}
