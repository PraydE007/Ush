#include "../inc/ush.h"

int mx_push_n_char(t_termconf **cfg, char ch) {
    t_h_node *clone = (*cfg)->clone;
    int r_c_pos = (*cfg)->c_pos - 6;

    clone->buf_size += 1;
    clone->buf = (char *)realloc(clone->buf, clone->buf_size);
    if (!(clone->buf)) {
        fprintf(stderr, "\x1b[31m%s\x1b[0m", MX_EBFLOC);
        return 1;
    }
    for (int i = clone->buf_size - 1; i > r_c_pos; i--)
        clone->buf[i] = clone->buf[i - 1];
    (*cfg)->clone->buf[r_c_pos] = ch;
    return 0;
}
