#include "../inc/ush.h"

int mx_set_history_pos(t_h_node **h_node, int type) {
    if (type == 4) {
        if ((*h_node)->back)
            (*h_node) = (*h_node)->back;
    }
    else {
        if ((*h_node)->next)
            (*h_node) = (*h_node)->next;
    }
    return 0;
}
