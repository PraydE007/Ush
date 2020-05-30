#include "../inc/ush.h"

int mx_drop_n_char(t_termconf **cfg) {
    t_h_node *clone = (*cfg)->chsn;
    int r_c_pos = (*cfg)->c_pos - 5;
    int size = mx_strlen(clone->buf) + 1;

    if (size > 1 && r_c_pos != -1) {
        size -= 1;
        for (int i = r_c_pos; i < size; i++)
            clone->buf[i] = clone->buf[i + 1];
        clone->buf = (char *)realloc(clone->buf, size);
        if (!(clone->buf)) {
            fprintf(stderr, "%s", MX_EBFLOC);
            return 1;
        }
    }
    return 0;
}
