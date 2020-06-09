#include "../inc/ush.h"

t_ush *mx_create_ush(void) {
    t_ush *ush = (t_ush *)malloc(sizeof(t_ush));

    ush->active = true;
    ush->equals = false;
    ush->trigger = false;
    ush->exit_code = 0;
    ush->storage = 0;
    ush->i = 0;
    ush->k = 0;
    ush->size = 0;
    ush->triger = 0;
    ush->pid1 = 0;
    ush->pid2 = 0;
    ush->termconf = mx_create_termconf();
    // ush->blocks = NULL;
    ush->pid_list = NULL;
    ush->jobs_list = NULL;
    ush->pwdilda_list = NULL;
    ush->variable_list = NULL;
    return ush;
}
