#include "ush.h"

int mx_term_width_check(t_ush *ush, int *len, int *term) {
    (*len) = mx_strlen(ush->buf) + 4;
    (*term) = mx_get_twidth();
    if ((*len) >= (*term))
        mx_buf_drop(&(ush->buf), &(ush->buf_size));
    if ((*len) > (*term)) {
        fprintf(stderr, "\n%s", MX_EBUF);
        return 1;
    }
    return 0;
}
