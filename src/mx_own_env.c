#include "../inc/ush.h"

void  mx_own_env(t_ush *ush, char **command) {
    char **kv = NULL;
    char *buf = NULL;
    char *login = getlogin();
    int store = 0;


    if (getenv("PATH") == 0) {
        kv = mx_key_value_creation(ush, PH);
        mx_push_back_variable(&ush->variable_list, kv);
        mx_del_strarr(&kv);
    }
    if (getenv("HOME") == 0) {
        buf = strjoin("/Users/", login);
        setenv("HOME", buf, 1);
        mx_strdel(&buf);
    }
    if (getenv("LOGNAME") == 0)
        setenv("LOGNAME", login, 1);
    if (getenv("SHLVL") == 0)
        setenv("SHLVL", "1", 1);
    else {
        buf = getenv("SHLVL");
        store = mx_atoi(buf);
        mx_strdel(buf);

    }
    mx_strdel(login);
}
