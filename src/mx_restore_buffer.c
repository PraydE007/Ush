#include "../inc/ush.h"

void mx_restore_buffer(t_termconf *cfg) {
    if (cfg->buf) {
        mx_strdel(&(cfg->buf));
        cfg->buf_size = 1;
        cfg->buf = mx_strnew_x(cfg->buf_size);
    }
}
