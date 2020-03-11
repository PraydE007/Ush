#include "../inc/ush.h"

void mx_dealloc_blocks(t_b_node **head) {
    while ((*head))
        mx_pop_block_front(head);
}
