#include "../inc/ush.h"

t_termconf *mx_create_termconf() {
    t_termconf *termconf = (t_termconf *)malloc(sizeof(t_termconf));

    mx_read_termconf(termconf);
    termconf->h_node = NULL;
    termconf->buf_size = 1; // NEED TO DEL
    termconf->buf = mx_strnew_x(termconf->buf_size); // NEED TO DEL
    termconf->term_w = mx_get_twidth();
    termconf->ful_len = 4;
    termconf->c_pos = 0;
    termconf->color = mx_strdup(MX_DEF_COL);
    return termconf;
}
