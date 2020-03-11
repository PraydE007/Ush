#include "../inc/ush.h"

t_ush *mx_create_ush() {
    t_ush *ush = (t_ush *)malloc(sizeof(t_ush));

    ush->active = true;
    ush->equals = false;
    ush->trigger = false;
    ush->exit_code = 0;
    ush->storage = 0;
    ush->shlvl = 0;
    ush->termconf = mx_create_termconf();
    ush->blocks = NULL;
    // ush->export_list = NULL;
    ush->variable_list = NULL;
    return ush;
}
