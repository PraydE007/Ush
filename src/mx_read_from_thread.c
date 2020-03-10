#include "../inc/ush.h"

int mx_read_from_thread(t_ush *ush) {
    char ch;
    char *buf = mx_strnew_x(1);
    int buf_size = 1;

    while (1) {
        read(0, &ch, 1);
        if (ch == '\0' || ch == '\n')
            break;
        mx_push_symbol(&buf, ch, &buf_size);
    }
    ush->termconf->buf = buf;
    ush->termconf->buf_size = buf_size;
    return 0;
}
