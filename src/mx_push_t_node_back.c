#include "ush.h"

void mx_push_t_node_back(t_t_node **head, char *text) {
    t_t_node *new_node = mx_create_text_node(text);
    t_t_node *p = (*head);

    if (p == NULL)
        (*head) = new_node;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
}
