#include "../inc/ush.h"

static void home_log_creation(char *log, char *home, char *dir) {
    char *buf = NULL;
    int i = 1;

    log = getlogin();
    setenv("LOGNAME", log, 1);
    for (; dir[i] != '/'; i++);
    buf = mx_strnew(i + 2);
    i = 1;
    buf[0] = '/';
    for (; dir[i] != '/'; i++)
        buf[i] = dir[i];
    buf[i] = '/';
    home = mx_strjoin_free(buf, log);
    setenv("HOME", home, 1);
    mx_strdel(&log);
    mx_strdel(&home);
}

static void constant_envariable(t_ush *ush) {
    char dir[256];
    char *log = NULL;
    char *home = NULL;
    char **kv = NULL;

    getcwd(dir, 256);
    setenv("OLDPWD", dir, 1);
    if (getenv("PATH") == 0) {
        kv = mx_key_value_creation(ush, PH);
        mx_push_back_variable(&ush->variable_list, kv);
        mx_del_strarr(&kv);
    }
    if (getenv("PWD") == 0)
        setenv("PWD", dir, 1);
    if (getenv("HOME") == 0 || getenv("LOGNAME") == 0)
        home_log_creation(log, home, dir);
    // mx_strdel(&dir);
}

void mx_constant_variables(t_ush *ush) {
    char *buf = NULL;
    int store = 0;

    constant_envariable(ush);
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
}
