#include "../inc/ush.h"

//CHECK COMMENTS
static char *get_buf(t_ush *ush) {
    t_termconf *cfg = ush->termconf;
    char *str = mx_get_history_last_str(&(cfg->h_node));
    char *res = mx_strdup(str);

    return res;
}

void mx_parse_buf_pro(t_ush *ush) {
    char *text = NULL;
    char *buf = get_buf(ush);

    text = strtok(buf, ";\n");
    while (text != NULL) {
        mx_parse_block_pro(ush, text);
        text = strtok(NULL, ";\n");
    }
    mx_strdel(&text);
    mx_strdel(&buf);
}
