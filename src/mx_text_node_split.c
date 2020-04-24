#include "../inc/ush.h"

static void insert_last_part(t_t_node **node, t_t_node **last) {
    t_t_node *p = (*node);

    while (p->next)
        p = p->next;
    p->next = (*last);
}

static void clear_subst_node(t_t_node **node) {
    mx_strdel(&((*node)->text));
    (*node)->text = mx_strnew_x(1);
    (*node)->type = 0;
}

void mx_text_node_split(t_t_node **node) {
    t_t_node **next = &((*node)->next);
    t_t_node *split = NULL;
    char *buf = mx_strdup((*node)->text);
    char *text = NULL;
    bool isSpaced = false;

    text = strtok(buf, " \n\0");
    while (text != NULL) {
        if (isSpaced)
            mx_push_t_node_back(&split, mx_strdup_x(" "), -1);
        mx_push_t_node_back(&split, mx_strdup(text), 0);
        text = strtok(NULL, " \n\0");
        isSpaced = true;
    }
    mx_strdel(&text);
    mx_strdel(&buf);
    clear_subst_node(node);
    insert_last_part(&split, next);
    (*node)->next = split;
}
