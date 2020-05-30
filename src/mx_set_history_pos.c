#include "../inc/ush.h"

int mx_set_history_pos(t_termconf **cfg, int type) {
    int *h_pos = &((*cfg)->h_pos);

    if (type == 4) {
        if ((*h_pos) > 0) {
            (*h_pos) -= 1;
            (*cfg)->chsn = mx_get_h_node_index(&((*cfg)->clone), (*h_pos));
            (*cfg)->c_pos = mx_strlen((*cfg)->chsn->buf) + 5;
        }
    }
    else {
        if ((*h_pos) < (*cfg)->h_len - 1) {
            (*h_pos) += 1;
            (*cfg)->chsn = mx_get_h_node_index(&((*cfg)->clone), (*h_pos));
            (*cfg)->c_pos = mx_strlen((*cfg)->chsn->buf) + 5;
        }
    }
    return 0;
}
