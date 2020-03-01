#ifndef USH_H
#define USH_H

/* DEFINES */



/* -------- */

/* INClUDES */

// FRONT-END
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "libmx/inc/libmx.h"
// #include "libmx.h"

/* -------- */

/* DECLARATIONS */

typedef struct termios t_term;

typedef struct s_termconf {
    t_term tty;
    t_term savetty;
}              t_termconf;

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
}              t_env;

typedef struct s_export {
    char *key;
    char *value;
    struct s_export *next;
}              t_export;

typedef struct s_variable {
    char *key;
    char *value;
    struct s_variable *next;
}              t_variable;

typedef struct s_ush {
    int exit_code;
    bool active;
    int buf_size;
    char *buf;
    t_termconf *termconf;
    t_export *export_list;
    t_variable *variable_list;
}              t_ush;

int mx_strarrlen(char **arr);
void mx_check_commands(t_ush *ush, char **line, char **env);
void mx_dealloc_termconf(t_termconf **termconf);
void mx_dealloc_ush(t_ush **ush);
void mx_export(t_export **export_list, char **command, char **env);
void mx_pop_front_export(t_export **head);
void mx_pop_front_variable(t_variable **head);
void mx_process_creator(char **line);
void mx_push_back_export(t_export **export, char **kv);
void mx_read_environment(t_export **export_list, char **env);
void mx_read_input(t_ush *ush);
void mx_read_termconf(t_termconf *termconf);
t_export *mx_exportnode_creation(void);
t_variable *mx_variablenode_creation(void);
// t_env *mx_envnode_creation(void);
t_termconf *mx_create_termconf();
t_ush *mx_create_ush();


/* -------- */

#endif
