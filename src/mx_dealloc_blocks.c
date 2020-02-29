#include "ush.h"

void mx_dealloc_blocks(t_b_node **head) {
    t_t_node *x = NULL;

    while ((*head))
        mx_pop_block_front(head);
}
