#ifndef USH_H
#define USH_H

/* DEFINES */



/* -------- */

/* INClUDES */

// FRONT-END
#include <fcntl.h>
#include <termios.h>

#include "libmx/inc/libmx.h"

/* -------- */

/* DECLARATIONS */

typedef struct termios t_term;

typedef struct s_termconf {
    t_term tty;
    t_term savetty;
}              t_termconf;

typedef struct s_ush {
    int exit_code;
    bool active;
    int buf_size;
    char *buf;
    t_termconf *termconf;
}              t_ush;

t_ush *mx_create_ush();
void mx_dealloc_ush(t_ush **ush);

t_termconf *mx_create_termconf();
void mx_read_termconf(t_termconf *termconf);
void mx_dealloc_termconf(t_termconf **termconf);

void mx_read_input(t_ush *ush);

/* -------- */

#endif
