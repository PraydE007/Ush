#include "ush.h"

t_t_node *mx_create_text_node(char *text, int type) {
    t_t_node *node = (t_t_node *)malloc(sizeof(t_t_node));

    node->text = text;
    node->type = type;
    node->next = NULL;
    return node;
}
