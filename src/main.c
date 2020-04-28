#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

char ***line = (char ***)malloc(sizeof(char **) * (8 + 1));
line[8] = NULL;;  
line[0] = (char **)malloc(sizeof(char *) * (3));
line[1] = (char **)malloc(sizeof(char *) * (3));
line[2] = (char **)malloc(sizeof(char *) * (2));
line[3] = (char **)malloc(sizeof(char *) * (3));
line[4] = (char **)malloc(sizeof(char *) * (3));
line[5] = (char **)malloc(sizeof(char *) * (2));
line[6] = (char **)malloc(sizeof(char *) * (2));
line[7] = (char **)malloc(sizeof(char *) * (3));
// line[8] = (char **)malloc(sizeof(char *) * (2));

// int i = -1;
// int pipedes[2];
line[0][0] = mx_strdup("ls");
line[0][1] = mx_strdup("-la");
line[0][2] = NULL;
line[1][0] = mx_strdup("cat");
line[1][1] = mx_strdup( "-e");
line[1][2] = NULL;
line[2][0] = mx_strdup("ls");
line[2][1] = NULL;
line[3][0] = mx_strdup("cat");
line[3][1] = mx_strdup( "-e");
line[3][2] = NULL;
line[4][0] = mx_strdup("ls");
line[4][1] = mx_strdup("-a");
line[4][2] = NULL;
line[5][0] = mx_strdup("cat");
line[5][1] = NULL;
line[6][0] = mx_strdup("cat");
line[6][1] = NULL;
line[7][0] = mx_strdup("ls");
line[7][1] = mx_strdup( "-r");
line[7][2] = NULL;
// line[8][0] = mx_strdup("/.");
// line[8][1] = NULL;

// char *test = NULL;
// char *line = NULL;
// line = "ls -la; v=5; echo $v; ls -a | cat -e";

// test = mx_substitution_making(ush, line);
// printf("%s\n", test);
// mx_strdel(&test);

    mx_constant_variables(ush);
    while (ush->active) {
        if (!mx_read_input(ush))
            mx_parse_buf(ush);
            // pipe(pipedes);
            mx_pipe_process_creator(line);
            // i = -1;
            // mx_pipe_process_creator_secondaddition(ush, line);
        while (ush->termconf->clone)
            mx_pop_h_node_front(&(ush->termconf->clone));
    }

t_variable *list = ush->variable_list;
while (list) {
     printf ("%s=", list->key);
     printf ("%s\n", list->value);
     list = list->next;
}
t_pwdilda *list2 = ush->pwdilda_list;
while (list2) {
     printf ("%s=", list2->key);
     printf ("%s\n", list2->value);
     list2 = list2->next;
}

    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
