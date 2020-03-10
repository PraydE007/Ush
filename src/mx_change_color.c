#include "../inc/ush.h"

static void set_color(t_ush *ush, char *color) {
    mx_strdel(&(ush->termconf->color));
    if (mx_strcmp(color, "def") == 0)
        ush->termconf->color = mx_strdup(MX_DEF_COL);
    else if (mx_strcmp(color, "black") == 0)
        ush->termconf->color = mx_strdup(MX_BLACK);
    else if (mx_strcmp(color, "red") == 0)
        ush->termconf->color = mx_strdup(MX_RED);
    else if (mx_strcmp(color, "green") == 0)
        ush->termconf->color = mx_strdup(MX_GREEN);
    else if (mx_strcmp(color, "yellow") == 0)
        ush->termconf->color = mx_strdup(MX_YELLOW);
    else if (mx_strcmp(color, "blue") == 0)
        ush->termconf->color = mx_strdup(MX_BLUE);
    else if (mx_strcmp(color, "magenta") == 0)
        ush->termconf->color = mx_strdup(MX_MAGENTA);
    else if (mx_strcmp(color, "cyan") == 0)
        ush->termconf->color = mx_strdup(MX_CYAN);
    else if (mx_strcmp(color, "white") == 0)
        ush->termconf->color = mx_strdup(MX_WHITE);
}

void mx_change_color(t_ush *ush, char **command) {
    char *color;

    if (!command[1])
        return;
    color = command[1];
    set_color(ush, color);
}
