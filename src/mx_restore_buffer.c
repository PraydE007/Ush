#include "../inc/ush.h"

// NOT IN USE
void mx_restore_buffer(t_termconf *cfg) {
    if (cfg->chsn->buf) {
        mx_strdel(&(cfg->chsn->buf));
        // cfg->buf_size = 1;
        cfg->chsn->buf = mx_strnew_x(1);
    }
}
