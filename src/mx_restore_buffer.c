#include "ush.h"

void mx_restore_buffer(t_ush *ush) {
    if (ush->buf) {
        mx_strdel(&(ush->buf));
        ush->buf_size = 1;
        ush->buf = mx_strnew_x(ush->buf_size);
    }
}
