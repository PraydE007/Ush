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
#include <signal.h>
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
    int isInThread;
    int tty_fd;
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

typedef struct s_echo{
    bool E;
    bool e;
    bool n;
    bool end;
}              t_echo;

// check if needs this structure
typedef struct s_export {
    char *key;
    char *value;
    struct s_export *next;
}              t_export;

typedef struct s_pwdilda {
    char *key;
    char *value;
    struct s_pwdilda *next;
}              t_pwdilda;

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
    int shlvl;
    int storage;
    int i;
    int k;
    int size;
    int triger;
    t_env_flags *flags;
    t_b_node *blocks;
    t_termconf *termconf;
    // t_export *export_list;
    t_pwdilda *pwdilda_list;
    t_variable *variable_list;
}              t_ush;

bool mx_check_key_allow(t_ush *ush, char *kay);
bool mx_have_equals(t_ush *ush, char *env);
bool mx_is_builtin(t_ush *ush, char **command);
bool mx_is_built_in(char *str);
bool mx_is_command(char *path, bool *flag, int index);
bool mx_is_pipe (char **command, char *comstr);
bool mx_is_slash(char *path);
bool mx_isvariable (t_ush *ush, char **k_v);
bool mx_path_is (t_ush *ush);
char *mx_buf_safe_realloc(char *src, int *size);
char **mx_command_matrix_creator(t_t_node **comn);
char **mx_export_matrix_creator(char **env);
char **mx_key_value_creation(t_ush *ush, char *env);
char ***mx_pipe_matrix_creator(t_ush *ush, char **command);
char *mx_programm_finder(char *command);
char **mx_strsplit_first_meeting(const char *s, char c);
char *mx_substitution_making(t_ush *ush, char *substion);
char *mx_which_str(char *command);
int mx_blist_len(t_b_node **head);
int mx_count_pipes(char **comn);
int mx_exit(char **command);
int mx_get_twidth();
int mx_read_input(t_ush *ush);
int mx_read_from_thread(t_ush *ush);
void mx_set_signal(void);
void mx_sig_init(void);
int mx_size_of_pipe_matstr(char **comn, int *i, int *j);
int mx_strarrlen(char **arr);
int mx_strcmp_export(const char *s1, const char *s2);
int mx_variable_list_len(t_variable **head);
// t_env *mx_envnode_creation(void);
t_env_flags *mx_create_env_flags(void);
t_variable *mx_creat_variable_node(void);
t_pwdilda *mx_creat_pwdilda_node(void);
void mx_adding_variable(t_ush *ush, char **command, char **kv);
void mx_check_commands(t_ush *ush);
void mx_child_exvprocess(int *pipedes, int *pipedes2, int inout, char **command);
void mx_child_process(t_ush *ush, char **command);
void mx_constant_variables(t_ush *ush);
void mx_dealloc_termconf(t_termconf **termconf);
void mx_dealloc_ush(t_ush **ush);
void mx_del_strararr(char ****arr);
void mx_env(t_ush *ush, char **command);
void mx_env_variable_checking(t_variable **list, char *command);
void mx_error_making(char *comn);
void mx_export(t_ush *ush, char **command);
void mx_outlst(t_ush *ush);
void mx_pipe_process_creator(t_ush *ush, char ***commat);
void mx_pop_back_variable(t_variable **head);
void mx_pop_front_export(t_export **head);
void mx_pop_front_pwdilda(t_pwdilda **head);
void mx_pop_front_variable(t_variable **head);
void mx_pop_specific(t_variable **list, int index);
void mx_process_creator(t_ush *ush, char **commands);
void mx_push_back_export(t_export **export, char **kv);
void mx_push_back_pwdilda(t_pwdilda **list, char *kay, char *value);
void mx_push_back_variable(t_variable **list, char **kv);
void mx_read_environment(t_export **export_list, char **env);
void mx_read_termconf(t_termconf *termconf);
void mx_sub_error_printing(int *pipedes);
void mx_unset(char **command, t_ush *ush);
void mx_which(t_ush *ush, char **command);
void mx_unset(char **command, t_ush *ush);

// ALL TERM OUTPUTS
void mx_rd_print_color(t_termconf **cfg);
void mx_rd_print_pbc(t_termconf **cfg, char *buf);
void mx_rd_print_old(t_termconf **cfg);

// TERM AND USH
int mx_term_width_check(t_termconf **cfg);
// t_env *mx_envnode_creation(void);
t_export *mx_exportnode_creation(void);
t_termconf *mx_create_termconf(void);
t_ush *mx_create_ush();
void mx_open_tty(t_termconf **cfg);
void mx_change_color(t_ush *ush, char **commands);

// BUF FUNCTIONS
int mx_buf_drop(char **buf, int *buf_size);
int mx_drop_n_char(t_termconf **cfg);
int mx_buf_push(char **buf, int *buf_size, char ch);
int mx_push_n_char(t_termconf **cfg, char ch);
char *mx_sixteen_ez_fix(char **str, int *size);
short mx_get_buf_type(unsigned char *ch);
// short mx_get_buf_type(unsigned char ch);
void mx_restore_buffer(t_termconf *cfg);

// TEXT LIST
t_t_node *mx_create_text_node(char *text, int type);
void mx_pop_t_node_front(t_t_node **head);
void mx_push_t_node_back(t_t_node **head, char *text, int type);

// HISTORY DOUBLE LINKED LIST
char *mx_get_history_last_str(t_h_node **h_node);
t_h_node *mx_create_history_node(t_h_node *back, char *buf, int buf_size);
t_h_node *mx_clone_history(t_h_node **h_node);
void mx_print_history(t_termconf *cfg);
void mx_pop_h_node_front(t_h_node **h_node);
void mx_push_h_node_back(t_h_node **h_node, char *buf, int buf_size);

// BLOCK LIST
int mx_set_history_pos(t_h_node **h_node, int type);
int mx_tlist_len(t_t_node **head);
t_b_node *mx_create_block_node(t_t_node *t_node);
t_b_node *mx_clone_blocks(t_b_node **head);
t_b_node *mx_push_block_back(t_b_node **head, t_t_node *t_node);
void mx_dealloc_blocks(t_b_node **head);
void mx_pop_block_front(t_b_node **head);

// STRING OPERATIONS && PARSING
bool mx_control_slash(char **res, char *str, int *res_size);
char *mx_break_on_error(char **str);
char *mx_dollar_parse(char *str, int *piv, int *type);
char *mx_doumrk_parse(char *str, int *piv);
char *mx_get_variable(t_ush *ush, char *var_name);
char *mx_space_parse(char *str, int *piv);
char *mx_sinmrk_parse(char *str, int *piv);
char *mx_slash_parse(char *str, int *piv);
char *mx_subst_dol_parse(char *str, int *piv, int *type);
char *mx_subst_parse(char *str, int *piv, int *type);
char *mx_text_parse(char *str, int *piv);
char *mx_tildastr(t_pwdilda **list, char *tilda);
char *mx_tild_parse(char *str, int *piv, int *type);
int mx_count_slashes(char *str);
int mx_one_slash(char **res, char *str, int *i, int *res_size);
int mx_one_slash_m(char **res, char *str, int *i, int *res_size);
int mx_parse_buf(t_ush *ush);
int mx_push_symbol(char **res, char ch, int *res_size);
int mx_three_slash(char **res, char *str, int *i, int *res_size);
int mx_two_slash(char **res, char *str, int *i, int *res_size);
int mx_two_slash_m(char **res, char *str, int *i, int *res_size);
t_b_node *mx_parse_block(t_t_node **head, int err_ch, int type);
void mx_parse_burnish(t_ush *ush);
void mx_replace_subst(t_ush *ush, t_b_node **node);
void mx_replace_tild(t_pwdilda **list, t_b_node **node);
void mx_replace_variables(t_ush *ush, t_b_node **node);
void mx_text_node_split(t_t_node **node);

/* -------- */

#endif
