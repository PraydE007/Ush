#include "../inc/ush.h"

int mx_read_from_thread(t_ush *ush) {
    char ch = 1;
    char *buf = mx_strnew_x(1);
    int buf_size = 1;

    while (ch != '\0') {
        read(0, &ch, 1);
        if (ch == '\n')
            break;
        if (ch == 1) {
            ush->active = false;
            break;
        }
        mx_push_symbol(&buf, ch, &buf_size);
    }
    mx_push_h_node_back(&(ush->termconf->h_node), buf, buf_size);
    return 0;
}
