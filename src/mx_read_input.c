#include "../inc/ush.h"

static int do_stuff(char **buf, int *buf_size, char ch, short type) {
    if (type == 0)
        return mx_buf_push(buf, buf_size, ch);
    if (type == 1)
        return mx_buf_drop(buf, buf_size);
    return 1;
}

static void on_read_start(t_ush *ush) {
    mx_restore_buffer(ush);
    tcsetattr(0, TCSAFLUSH, &(ush->termconf->tty));
    if (isatty(0) != 0)
        fprintf(stdout, "\x1B[38;05;155mu$h> ");
    fflush(stdout);
}

static int reading_cycle(t_ush *ush) {
    char ch = 0;
    int term = mx_get_twidth();
    int len = 4;

    while (1) {
        read(0, &ch, 1);
        if (ch == '\0')
            exit(1);
        if (ch == '\n')
            break;
        if (do_stuff(&(ush->buf), &(ush->buf_size), ch, mx_get_buf_type(ch)))
            return 1;
        if (mx_term_width_check(ush, &len, &term))
            return 1;
        if (isatty(0) != 0)
            fprintf(stdout, "\r\x1B[0J\x1B[38;05;155mu$h> \x1B[0m%s", ush->buf);
        fflush(stdout);
    }
    return 0;
}

static void on_read_ended(t_ush *ush) {
    tcsetattr(0, TCSAFLUSH, &(ush->termconf->savetty));
    if (isatty(0) != 0)
        fprintf(stdout, "\r\x1B[0J\x1B[38;05;243mu$h> %s\x1B[0m\n", ush->buf);
}

int mx_read_input(t_ush *ush) {
    on_read_start(ush);
    if (reading_cycle(ush))
        return 1;
    on_read_ended(ush);
    return 0;
}
