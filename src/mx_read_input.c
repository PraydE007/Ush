#include "ush.h"

static void push_char(char **buf, int *buf_size, char ch) {
    (*buf_size) += 1;
    (*buf) = (char *)realloc(*buf, (*buf_size));
    (*buf)[*buf_size - 1] = '\0';
    (*buf)[(*buf_size) - 2] = ch;
}

static void drop_char(char **buf, int *buf_size) {
    if ((*buf_size) > 1) {
        (*buf)[(*buf_size) - 2] = '\0';
        (*buf_size) -= 1;
        (*buf) = (char *)realloc((*buf), (*buf_size));
    }
}

static short get_buf_type(char ch) {
    if (32 <= ch && ch <= 126)
        return 0;
    else
        return 1;
}

static void do_stuff(char **buf, int *buf_size, char ch, short type) {
    if (type == 0)
        push_char(buf, buf_size, ch);
    if (type == 1)
        drop_char(buf, buf_size);
}

void mx_read_input(t_ush *ush) {
    char ch = 0;

    if (ush->buf) {
        mx_strdel(&(ush->buf));
        ush->buf_size = 1;
        ush->buf = mx_strnew_x(ush->buf_size);
    }
    tcsetattr(0, TCSAFLUSH, &(ush->termconf->tty));
    mx_printstr("\x1B[s");
    mx_printstr("\x1B[38;05;155m");
    mx_printstr("u$h> ");
    while (1) {
        read(0, &ch, 1);
        mx_printstr("\x1B[u");
        mx_printstr("\x1B[0K");
        if (ch == '\n')
            break;
        do_stuff(&(ush->buf), &(ush->buf_size), ch, get_buf_type(ch));
        mx_printstr("\x1B[38;05;155m");
        mx_printstr("u$h> ");
        mx_printstr("\x1B[0m");
        mx_printstr(ush->buf);
    }
    tcsetattr(0, TCSAFLUSH, &(ush->termconf->savetty));
    mx_printstr("\x1B[38;05;243m");
    mx_printstr("u$h> ");
    mx_printstr(ush->buf);
    mx_printstr("\x1B[0m");
    mx_printstr("\n");
}
