#ifndef USH_H
#define USH_H

/* DEFINES */

#define MX_EBUF "ush: Buffer cannot be longer than terminal width.\n"
#define MX_ETGTN "ush: Could not access the termcap data base.\n"
#define MX_EBFLOC "ush: Buffer cannot allocate enough memory.\n"
#define MX_PIZDA "ush: Syntax error -- '%c'\n"
#define PH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

#define MX_ZER "\x1B[0m"
#define MX_DEF_COL "\x1B[38;05;155m"

#define MX_BLACK "\x1B[30m"
#define MX_RED "\x1B[31m"
#define MX_GREEN "\x1B[32m"
#define MX_YELLOW "\x1B[33m"
#define MX_BLUE "\x1B[34m"
#define MX_MAGENTA "\x1B[35m"
#define MX_CYAN "\x1B[36m"
#define MX_WHITE "\x1B[37m"

/* -------- */

/* INClUDES */

// FRONT-END
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <term.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../libmx/inc/libmx.h"
// #include "libmx.h"

/* -------- */

/* DECLARATIONS */

typedef struct termios t_term;

typedef struct s_h_node {
    struct s_h_node *back;
    char *buf;
    int buf_size;
    struct s_h_node *next;
}              t_h_node;

typedef struct s_termconf {
    t_term tty;
    t_term savetty;
    t_h_node *h_node;
    t_h_node *clone;
    char *buf; // NEED TO DEL
    int buf_size; // NEED TO DEL
    int term_w;
    int ful_len;
    int c_pos;
    char *color;
}              t_termconf;

typedef struct s_t_node {
    char *text;
    int type;
    struct s_t_node *next;
}              t_t_node;

typedef struct s_b_node {
    t_t_node *t_node;
    struct s_b_node *next;
}              t_b_node;

// check if needs this structure
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
}              t_env;

typedef struct s_env_flags {
    bool u;
    bool i;
    bool P;
}              t_env_flags;

// check if needs this structure
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
    bool active;
    bool equals;
    bool trigger;
    int exit_code;
    int storage;
    t_env_flags *flags;
    t_b_node *blocks;
    t_termconf *termconf;
    // t_export *export_list;
    t_variable *variable_list;
}              t_ush;

bool mx_check_key_allow(t_ush *ush, char *kay);
bool mx_is_built_in(char *str);
bool mx_is_command(char *path, bool *flag, int index);
bool mx_is_slash(char *path);
bool mx_check_key_allow(t_ush *ush, char *kay);
bool mx_have_equals(t_ush *ush, char *env);
bool mx_isvariable (t_ush *ush, char **k_v);
char **mx_command_matrix_creator(t_t_node **comn);
char **mx_export_matrix_creator(char **env);
char **mx_key_value_creation(t_ush *ush, char *env);
char **mx_strsplit_first_meeting(const char *s, char c);
char *mx_tildastr(char *tilda);
int mx_blist_len(t_b_node **head);
int mx_exit(char **command);
int mx_get_twidth();
int mx_read_input(t_ush *ush);
int mx_read_from_thread(t_ush *ush);
int mx_strarrlen(char **arr);
int mx_strcmp_export(const char *s1, const char *s2);
int mx_variable_list_len(t_variable **head);
// t_env *mx_envnode_creation(void);
t_variable *mx_variablenode_creation(void);
t_env_flags *mx_create_env_flags(void);
void mx_adding_variable(t_ush *ush, char **command, char **kv);
void mx_check_commands(t_ush *ush);
void mx_dealloc_termconf(t_termconf **termconf);
void mx_dealloc_ush(t_ush **ush);
void mx_env(t_ush *ush, char **command);
void mx_env_variable_checking(t_variable **list, char *command);
void mx_export(t_ush *ush, char **command);
void mx_pop_back_variable(t_variable **head);
void mx_pop_front_export(t_export **head);
void mx_pop_front_variable(t_variable **head);
void mx_pop_specific(t_variable **list, int index);
void mx_process_creator(char **commands);
void mx_push_back_export(t_export **export, char **kv);
void mx_push_back_variable(t_variable **list, char **kv);
void mx_read_environment(t_export **export_list, char **env);
void mx_read_termconf(t_termconf *termconf);
void mx_unset(char **command, t_ush *ush);
void mx_which(t_ush *ush, char **command);
void mx_unset(char **command, t_ush *ush);

// TERM AND USH
t_export *mx_exportnode_creation(void);
// t_env *mx_envnode_creation(void);
int mx_term_width_check(t_termconf **cfg);
t_termconf *mx_create_termconf(void);
void mx_change_color(t_ush *ush, char **commands);
t_ush *mx_create_ush();

// BUF FUNCTIONS
int mx_buf_drop(char **buf, int *buf_size);
int mx_buf_push(char **buf, int *buf_size, char ch);
int mx_push_n_char(t_termconf **cfg, char ch);
int mx_drop_n_char(t_termconf **cfg);
short mx_get_buf_type(unsigned char *ch);
// short mx_get_buf_type(unsigned char ch);
void mx_restore_buffer(t_termconf *cfg);

// TEXT LIST
t_t_node *mx_create_text_node(char *text, int type);
void mx_pop_t_node_front(t_t_node **head);
void mx_push_t_node_back(t_t_node **head, char *text, int type);

// HISTORY DOUBLE LINKED LIST
t_h_node *mx_create_history_node(t_h_node *back, char *buf, int buf_size);
void mx_push_h_node_back(t_h_node **h_node, char *buf, int buf_size);
void mx_pop_h_node_front(t_h_node **h_node);
t_h_node *mx_clone_history(t_h_node **h_node);
char *mx_get_history_last_str(t_h_node **h_node);
void mx_print_history(t_termconf *cfg);

// BLOCK LIST
int mx_tlist_len(t_t_node **head);
int mx_set_history_pos(t_h_node **h_node, int type);
t_b_node *mx_create_block_node(t_t_node *t_node);
void mx_pop_block_front(t_b_node **head);
t_b_node *mx_push_block_back(t_b_node **head, t_t_node *t_node);
t_b_node *mx_clone_blocks(t_b_node **head);
void mx_dealloc_blocks(t_b_node **head);

// STRING OPERATIONS && PARSING
int mx_parse_buf(t_ush *ush);
void mx_parse_burnish(t_ush *ush);
int mx_count_slashes(char *str);
char *mx_break_on_error(char **str);
t_b_node *mx_parse_block(t_t_node **head, int err_ch, int type);
char *mx_space_parse(char *str, int *piv);
char *mx_text_parse(char *str, int *piv);
char *mx_slash_parse(char *str, int *piv);
char *mx_sinmrk_parse(char *str, int *piv);
char *mx_doumrk_parse(char *str, int *piv);
int mx_push_symbol(char **res, char ch, int *res_size);
int mx_one_slash(char **res, char *str, int *i, int *res_size);
int mx_one_slash_m(char **res, char *str, int *i, int *res_size);
int mx_two_slash(char **res, char *str, int *i, int *res_size);
int mx_two_slash_m(char **res, char *str, int *i, int *res_size);
int mx_three_slash(char **res, char *str, int *i, int *res_size);
bool mx_control_slash(char **res, char *str, int *res_size);



/* -------- */

#endif
