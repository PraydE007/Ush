#include "ush.h"

t_ush *mx_create_ush() {
    t_ush *ush = (t_ush *)malloc(sizeof(t_ush));

    ush->active = true;
    ush->exit_code = 0;
    ush->buf_size = 1;
    ush->buf = mx_strnew_x(ush->buf_size);
    ush->termconf = mx_create_termconf();
    ush->export_list = NULL;
    ush->variable_list = NULL;
    return ush;
}
