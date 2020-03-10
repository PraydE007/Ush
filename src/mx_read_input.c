#include "../inc/ush.h"

static int c_cases(t_termconf **cfg, unsigned char ch, short type) {
    if (type == 0) {
        (*cfg)->c_pos += 1;
        return mx_push_n_char(cfg, ch);
    }
    else if (type == 1) {
        (*cfg)->c_pos -= 1;
        return mx_drop_n_char(cfg);
    }
    else if (type == 2)
        (*cfg)->c_pos -= 1;
    else if (type == 3)
        (*cfg)->c_pos += 1;
    else if (type == 4 || type == 5)
        return mx_set_history_pos(&((*cfg)->clone), type);
    return 0;
}

static void on_read_start(t_termconf **cfg) {
    // mx_restore_buffer(cfg); //
    tcsetattr(0, TCSAFLUSH, &((*cfg)->tty));
    fprintf(stdout, "%su$h> ", (*cfg)->color);
    fflush(stdout);
}

static void restore_ch(unsigned char *ch) {
    ch[0] = 0;
    ch[1] = 0;
    ch[2] = 0;
    ch[3] = 0;
}

static int reading_cycle(t_termconf **cfg) {
    unsigned char ch[4] = {0, 0, 0, 0};
    char *buf = NULL;

    while (1) {
        restore_ch(ch);
        read(0, ch, 4);
        if (mx_term_width_check(cfg))
            return 1;
        if (ch[0] == '\n' && !ch[1] && !ch[2] && !ch[3])
            break;
        if (c_cases(cfg, ch[0], mx_get_buf_type(ch)))
            return 1;
        if (mx_term_width_check(cfg))
            return 1;
        buf = (*cfg)->clone->buf;
        fprintf(stdout, "\r\x1B[0J%su$h> %s%s", (*cfg)->color, MX_ZER, buf);
        fprintf(stdout, "\r\x1B[%iC", (*cfg)->c_pos);
        fflush(stdout);
    }
    return 0;
}

static int on_read_ended(t_termconf **cfg) {
    t_h_node *clone = (*cfg)->clone;
    char *new_buf = mx_strdup_x(clone->buf);
    int exit_code = 0;

    tcsetattr(0, TCSAFLUSH, &((*cfg)->savetty));
    fprintf(stdout, "\r\x1B[0J\x1B[38;05;243mu$h> %s%s\n", clone->buf, MX_ZER);
    if (mx_strcmp(new_buf, "\0") != 0)
        mx_push_h_node_back(&((*cfg)->h_node), new_buf, clone->buf_size);
    else {
        mx_strdel(&new_buf);
        exit_code = 1;
    }
    while ((*cfg)->clone)
        mx_pop_h_node_front(&((*cfg)->clone));
    return exit_code;
}

int mx_read_input(t_ush *ush) {
    t_termconf **cfg = &(ush->termconf);
    (*cfg)->clone = mx_clone_history(&((*cfg)->h_node));

    mx_push_h_node_back(&((*cfg)->clone), mx_strnew_x(1), 1);
    if (!isatty(0))
        return mx_read_from_thread(ush);
    on_read_start(cfg);
    if (reading_cycle(cfg))
        return 1;
    if (on_read_ended(cfg))
        return 1;
    return 0;
}
