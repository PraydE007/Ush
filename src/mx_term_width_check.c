#include "../inc/ush.h"

int mx_term_width_check(t_termconf **cfg) {
    (*cfg)->ful_len = mx_strlen((*cfg)->clone->buf) + 4;
    (*cfg)->term_w = mx_get_twidth();
    if ((*cfg)->c_pos < 5)
        (*cfg)->c_pos = 5;
    if ((*cfg)->c_pos > (*cfg)->ful_len)
        (*cfg)->c_pos = (*cfg)->ful_len + 1;
    if ((*cfg)->ful_len >= (*cfg)->term_w)
        mx_buf_drop(&((*cfg)->clone->buf), &((*cfg)->clone->buf_size));
    if ((*cfg)->ful_len > (*cfg)->term_w) {
        fprintf(stderr, "\n\x1b[31m%s\x1b[0m", MX_EBUF);
        return 1;
    }
    return 0;
}
