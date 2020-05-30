#include "../inc/ush.h"

char *get_buf(t_ush *ush) {
    t_termconf *cfg = ush->termconf;
    char *str = mx_get_history_last_str(&(cfg->h_node));
    char *res = mx_strdup(str);

    return res;
}

int mx_parse_buf(t_ush *ush) {
    t_t_node *t_node = NULL;
    char *text = NULL;
    char *part = NULL;
    char *buf = get_buf(ush);
    // char *buf = mx_buf_safe_realloc(bff->buf, &(bff->buf_size));

    text = strtok(buf, ";\n");
    while (text != NULL) {
        part = mx_strdup(text);
        mx_push_t_node_back(&t_node, part, 0);
        text = strtok(NULL, ";\n");
    }
    mx_strdel(&text);
    mx_strdel(&buf);
    ush->blocks = mx_parse_block(&t_node, 0, 0);
    while (t_node) // DELETE SEMI COLON
        mx_pop_t_node_front(&t_node);
    if (ush->blocks)
        mx_parse_burnish(ush);
    return ush->blocks != NULL ? 1 : 0;
}
