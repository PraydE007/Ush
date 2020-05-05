#include "../inc/ush.h"

static int c_cases(t_termconf **cfg, unsigned char ch, short type) {
    if (type == 0) {
        (*cfg)->c_pos += 1;
        // return mx_buf_push(&((*cfg)->clone->buf), &((*cfg)->clone->buf_size), (char)ch);
        return mx_push_n_char(cfg, ch);
    }
    else if (type == 1) {
        (*cfg)->c_pos -= 1;
        // return mx_buf_drop(&((*cfg)->clone->buf), &((*cfg)->clone->buf_size));
        return mx_drop_n_char(cfg);
    }
    else if (type == 2)
        (*cfg)->c_pos -= 1;
    else if (type == 3)
        (*cfg)->c_pos += 1;
    else if (type == 4 || type == 5)
        return mx_set_history_pos(&((*cfg)->clone), type);
    else if (type == 101 && (*cfg)->clone->buf_size == 1)
        return 101;
    return 0;
}

static void on_read_start(t_termconf **cfg) {
    // mx_restore_buffer(cfg); //
    tcsetattr(0, TCSAFLUSH, &((*cfg)->tty));
    // fprintf(stdout, "%su$h> ", (*cfg)->color);
    mx_rd_print_color(cfg);
}

static void restore_ch(unsigned char *ch) {
    ch[0] = 0;
    ch[1] = 0;
    ch[2] = 0;
    ch[3] = 0;
}

static int reading_cycle(t_termconf **cfg) {
    unsigned char ch[4] = {0, 0, 0, 0};
    // char ch = 0;
    char *buf = NULL;
    int func_exit = 0;

    while (1) {
        restore_ch(ch);
        // read(0, &ch, 1);
        read(0, ch, 4);
        if (mx_term_width_check(cfg))
            return 1;
        if (ch[0] == '\n' && !ch[1] && !ch[2] && !ch[3])
            break;
        if ((func_exit = c_cases(cfg, ch[0], mx_get_buf_type(ch))))
            return func_exit;
        if (mx_term_width_check(cfg))
            return 1;
        buf = (*cfg)->clone->buf;
        mx_rd_print_pbc(cfg, buf);
    }
    return 0;
}

static int on_read_ended(t_termconf **cfg) {
    t_h_node *clone = (*cfg)->clone;
    char *new_buf = mx_sixteen_ez_fix(&(clone->buf), &(clone->buf_size)); //
    int exit_code = 0;

    tcsetattr(0, TCSAFLUSH, &((*cfg)->savetty));
    mx_rd_print_old(cfg);
    if (mx_strcmp(new_buf, "\0") != 0)
        mx_push_h_node_back(&((*cfg)->h_node), new_buf, clone->buf_size);
    else {
        mx_strdel(&new_buf);
        exit_code = 1;
    }
    return exit_code;
}

int mx_read_input(t_ush *ush) {
    t_termconf **cfg = &(ush->termconf);
    int func_exit = 1;

    (*cfg)->clone = mx_clone_history(&((*cfg)->h_node));
    mx_push_h_node_back(&((*cfg)->clone), mx_strnew_x(1), 1);
    if (!isatty(0))
        return mx_read_from_thread(ush);
    if ((*cfg)->isInThread)
        mx_open_tty(cfg);
    on_read_start(cfg);
    if ((func_exit = reading_cycle(cfg)))
        return func_exit;
    if (on_read_ended(cfg))
        return 1;
    return 0;
}
